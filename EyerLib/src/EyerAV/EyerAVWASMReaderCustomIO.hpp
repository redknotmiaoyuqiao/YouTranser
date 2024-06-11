#ifndef EYERLIB_EYERAVWASMREADERCUSTOMIO_HPP
#define EYERLIB_EYERAVWASMREADERCUSTOMIO_HPP

#ifdef EYER_PLATFORM_EMSCRIPTEN

#include "EyerCore/EyerCore.hpp"

#include "EyerAVReaderCustomIO.hpp"
#include "EyerWASMHttp/EyerWASMHttp.hpp"
#include "EyerWASMIndexedDB/EyerWASMIndexedDBHeader.hpp"

namespace Eyer
{
    class EyerAVWASMReaderCustomIO : public EyerAVReaderCustomIO
    {
    private:
        static EyerLRUCache<EyerString, std::shared_ptr<EyerBuffer>> blockMemCache;
    public:
        EyerAVWASMReaderCustomIO(const EyerString & _url);

        virtual int Read(uint8_t * buf, int buf_size) override;
        virtual int64_t Seek(int64_t offset, int whence) override;

        int64_t GetFileSize();

    private:
        int64_t m_currentPos = 0;
        int64_t m_fileSize = 0;
        EyerString m_url = "";

        const int BLOCK_SIZE = 1024 * 1024 * 1;

        int64_t GetBlockStartPos (int64_t currentPos, int64_t fileSize);
        int64_t GetBlockSize (int64_t blockStartPos, int64_t fileSize);
    };
}

#endif

#endif //EYERLIB_EYERAVWASMREADERCUSTOMIO_HPP
