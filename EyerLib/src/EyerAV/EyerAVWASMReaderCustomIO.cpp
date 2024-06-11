#include "EyerAVWASMReaderCustomIO.hpp"

#ifdef EYER_PLATFORM_EMSCRIPTEN
namespace Eyer
{
    EyerLRUCache<EyerString, std::shared_ptr<EyerBuffer>> EyerAVWASMReaderCustomIO::blockMemCache(10);

    EyerAVWASMReaderCustomIO::EyerAVWASMReaderCustomIO(const EyerString & _url)
        : m_url (_url)
    {

    }

    int EyerAVWASMReaderCustomIO::Read(uint8_t * buf, int buf_size) {
        int64_t fileSize = GetFileSize();
        if(m_currentPos >= fileSize){
            return 0;
        }

        int64_t blockStartPos = GetBlockStartPos(m_currentPos, fileSize);
        int64_t blockSize = GetBlockSize(blockStartPos, fileSize);

        EyerString key = m_url + "_" + EyerString::Number(blockStartPos) + "_" + EyerString::Number(blockSize);
        EyerLog("key: %s\n", key.c_str());

        std::shared_ptr<EyerBuffer> buffer = nullptr;

        // Get From Memory
        buffer = blockMemCache.Get(key);

        // Get From IndexedDB
        if(buffer == nullptr){
            EyerWASMIndexedDB indexedDb("EyerMediaCache");
            indexedDb.Open();

            EyerWASMBuffer indexedDBBuffer;
            int64_t contentLength = 0;
            int64_t rangeLength = 0;
            int ret = indexedDb.Get(key.c_str(), indexedDBBuffer, &contentLength, &rangeLength);
            if(!ret){
                buffer = std::make_shared<EyerBuffer>();
                buffer->Clear();
                buffer->Append(indexedDBBuffer.GetPtr(), indexedDBBuffer.GetBufferSize());
                blockMemCache.Put(key, buffer);
            }
            indexedDb.Close();
        }
        // Get From Network
        if(buffer == nullptr){
            Eyer::EyerWASMHttp wasmHttp(m_url.c_str(), blockStartPos, blockStartPos + blockSize - 1);
            wasmHttp.Send();
            wasmHttp.WaitHttpHeader();
            wasmHttp.WaitHttpBody();
            int httpStatus = wasmHttp.GetHttpStatus();
            if(httpStatus >= 200 && httpStatus < 300){
                // wasmHttp.GetBuffer();
                buffer = std::make_shared<EyerBuffer>();
                buffer->Clear();
                buffer->Append(wasmHttp.GetBuffer(), wasmHttp.GetBufferLen());
                blockMemCache.Put(key, buffer);

                EyerWASMIndexedDB indexedDb("EyerMediaCache");
                indexedDb.Open();
                indexedDb.Put(key.c_str(), buffer->GetPtr(), buffer->GetLen(), wasmHttp.GetContentLength(), wasmHttp.GetRangeLength());
                indexedDb.Close();
            }
        }
        if(buffer != nullptr){
            int size = std::min(buf_size, (int)(blockSize + blockStartPos - m_currentPos));
            memcpy(buf, buffer->GetPtr() + (m_currentPos - blockStartPos), size);
            m_currentPos += size;
            return size;
        }
        return 0;
    }

#define AVSEEK_SIZE 0x10000
    int64_t EyerAVWASMReaderCustomIO::Seek(int64_t offset, int whence) {
        int64_t fileSize = 0;
        if (whence == AVSEEK_SIZE) {
            fileSize = GetFileSize();
            return fileSize;
        }
        int64_t new_pos = 0;

        switch (whence) {
            case SEEK_SET: new_pos = 0 + offset; break;
            case SEEK_CUR: new_pos = m_currentPos + offset; break;
            case SEEK_END: new_pos = fileSize - 1 + offset; break;
            default: break;
        }

        if ((fileSize > 0 && new_pos >= fileSize)|| new_pos < 0) {
            return -1;
        }
        m_currentPos = new_pos;
        return m_currentPos;
    }

    int64_t EyerAVWASMReaderCustomIO::GetFileSize()
    {
        if(m_fileSize > 0){
            return m_fileSize;
        }

        EyerWASMIndexedDB indexedDb("EyerMediaCache");
        indexedDb.Open();
        EyerString key = m_url + "_filesize";

        EyerWASMBuffer indexedDBBuffer;
        int64_t contentLength = 0;
        int64_t rangeLength = 0;
        int ret = indexedDb.Get(key.c_str(), indexedDBBuffer, &contentLength, &rangeLength);
        if(!ret){
            m_fileSize = contentLength;
            EyerLog("contentLength: %lld, rangeLength: %lld\n", contentLength, rangeLength);
            return m_fileSize;
        }

        Eyer::EyerWASMHttp wasmHttp(m_url.c_str(), 0, 20);
        wasmHttp.Send();
        wasmHttp.WaitHttpHeader();
        wasmHttp.WaitHttpBody();
        int httpStatus = wasmHttp.GetHttpStatus();
        if(httpStatus >= 200 && httpStatus < 300){
            m_fileSize = wasmHttp.GetRangeLength();
        }

        if(m_fileSize <= 0){
            Eyer::EyerWASMHttp wasmHttp(m_url.c_str(), -1, -1);
            wasmHttp.Send();
            wasmHttp.WaitHttpHeader();
            wasmHttp.Abort();
            wasmHttp.WaitHttpBody();
            if(wasmHttp.GetContentLength() > 0){
                m_fileSize = wasmHttp.GetContentLength();
            }
        }

        uint8_t buf[5];
        memset(buf, 0, 5);
        indexedDb.Put(key.c_str(), buf, 5, m_fileSize, m_fileSize);
        indexedDb.Close();

        return m_fileSize;
    }

    int64_t EyerAVWASMReaderCustomIO::GetBlockStartPos (int64_t currentPos, int64_t fileSize)
    {
        int blockCount = fileSize / BLOCK_SIZE;
        if(fileSize % BLOCK_SIZE > 0){
            blockCount = blockCount + 1;
        }
        int64_t pos = 0;
        for(int i=0; i<blockCount; i++){
            int64_t start = i * BLOCK_SIZE;
            int64_t end = start + BLOCK_SIZE - 1;
            if(end >= fileSize){
                end = fileSize - 1;
            }
            if(currentPos >= start && currentPos <= end){
                pos = start;
                break;
            }
        }
        return pos;
    }

    int64_t EyerAVWASMReaderCustomIO::GetBlockSize (int64_t blockStartPos, int64_t fileSize)
    {
        if(fileSize <= blockStartPos) {
            return 0;
        }
        if(fileSize - blockStartPos >= BLOCK_SIZE) {
            return BLOCK_SIZE;
        }
        return fileSize - blockStartPos;
    }
}

#endif