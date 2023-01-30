#include "EyerAVReader.hpp"

#include "EyerAVReaderPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"
#include "EyerAVStreamPrivate.hpp"

#include "EyerAVPixelFormat.hpp"

namespace Eyer {
    /*
    FILE * f = nullptr;
    static int read_packet(void *opaque, uint8_t *buf, int buf_size)
    {
        if(f == nullptr){
            f = fopen("/Users/bytedance/Desktop/ZZZ.mp4", "rb");
        }

        int ret = fread(buf, 1, buf_size, f);

        printf("want: %d, fread: %d\n", buf_size, ret);

        return ret;
    }

    static int64_t seek(void *opaque, int64_t offset, int whence)
    {
        if(f == nullptr){
            f = fopen("/Users/bytedance/Desktop/ZZZ.mp4", "rb");
        }

        if(whence == AVSEEK_SIZE){
            return 36479332;
        }

        fseek(f, offset, SEEK_SET);
        return offset;
    }
    */
    EyerAVReader::EyerAVReader(EyerString _path) {
        piml = new EyerAVReaderPrivate();

        piml->path = _path;

        // av_register_all();
        avformat_network_init();

        piml->formatCtx = avformat_alloc_context();

        /*
        constexpr int32_t buffer_size = 16384; // 16 KByte
        unsigned char * buffer = new unsigned char[buffer_size];
        piml->formatCtx->pb = avio_alloc_context(buffer, buffer_size, 0, nullptr, read_packet, NULL, seek);
        */
    }

    EyerAVReader::~EyerAVReader() {
        if (piml->formatCtx != NULL) {
            Close();
            avformat_free_context(piml->formatCtx);
            piml->formatCtx = NULL;
        }
        if (piml != nullptr) {
            delete piml;
            piml = nullptr;
        }
    }

    int EyerAVReader::Open() {
        AVDictionary *option = nullptr;
        // av_dict_set(&option, "decryption_key", "5c1622f4736f4f60a545d048271ebab1", 0);

        int ret = avformat_open_input(&piml->formatCtx, piml->path.c_str(), NULL, &option);
        if (ret) {
            // TODO Error Code
            return ret;
        }

        avformat_find_stream_info(piml->formatCtx, NULL);
        av_dump_format(piml->formatCtx, 0, piml->path.c_str(), 0);

        // piml->formatCtx->streams[0]->codecpar->extradata

        return ret;
    }

    int EyerAVReader::Close() {
        avformat_close_input(&piml->formatCtx);
        return 0;
    }

    int EyerAVReader::GetStreamCount()
    {
        return piml->formatCtx->nb_streams;
    }

    int EyerAVReader::GetStream(EyerAVStream & stream, int index)
    {
        stream.piml->stream_id  = piml->formatCtx->streams[index]->index;
        stream.piml->timebase   = piml->formatCtx->streams[index]->time_base;
        stream.piml->duration   = piml->formatCtx->streams[index]->duration * 1.0 * stream.piml->timebase.num / stream.piml->timebase.den;

        EyerString name = EyerAVPixelFormat::GetByFFmpegId(piml->formatCtx->streams[index]->codecpar->format).GetName();

        return avcodec_parameters_copy(stream.piml->codecpar, piml->formatCtx->streams[index]->codecpar);
    }

    EyerAVStream EyerAVReader::GetStream(int index)
    {
        EyerAVStream stream;
        GetStream(stream, index);
        return stream;
    }

    int EyerAVReader::GetTimebase(EyerAVRational & timebase, int streamIndex)
    {
        timebase.num = piml->formatCtx->streams[streamIndex]->time_base.num;
        timebase.den = piml->formatCtx->streams[streamIndex]->time_base.den;
        return 0;
    }

    double EyerAVReader::GetDuration()
    {
        return piml->formatCtx->duration / AV_TIME_BASE;
    }

    int EyerAVReader::Seek(double time)
    {
        /**
        * Seek to the keyframe at timestamp.
        * 'timestamp' in 'stream_index'.
        *
        * @param s media file handle
        * @param stream_index If stream_index is (-1), a default
        * stream is selected, and timestamp is automatically converted
        * from AV_TIME_BASE units to the stream specific time_base.
        * @param timestamp Timestamp in AVStream.time_base units
        *        or, if no stream is specified, in AV_TIME_BASE units.
        * @param flags flags which select direction and seeking mode
        * @return >= 0 on success
        */
        int64_t t = time * AV_TIME_BASE;
        int ret = av_seek_frame(piml->formatCtx, -1, t, AVSEEK_FLAG_BACKWARD);
        return ret;
    }

    int EyerAVReader::Read(EyerAVPacket * packet)
    {
        int ret = av_read_frame(piml->formatCtx, packet->piml->packet);
        if(!ret){
            int streamIndex = packet->GetStreamIndex();

            int64_t start_time = piml->formatCtx->streams[streamIndex]->start_time;
            packet->piml->packet->pts -= start_time;

            int64_t pts = packet->GetPTS();
            packet->piml->secPTS = pts * av_q2d(piml->formatCtx->streams[streamIndex]->time_base);
        }
        return ret;
    }

    int EyerAVReader::Read(EyerAVPacket & packet)
    {
        int ret = av_read_frame(piml->formatCtx, packet.piml->packet);
        if(!ret){
            int streamIndex = packet.GetStreamIndex();
            int64_t start_time = piml->formatCtx->streams[streamIndex]->start_time;
            if(start_time != AV_NOPTS_VALUE){
                packet.piml->packet->pts -= start_time;
            }
            int64_t pts = packet.piml->packet->pts;
            if(pts != AV_NOPTS_VALUE){
                packet.piml->secPTS = pts * av_q2d(piml->formatCtx->streams[streamIndex]->time_base);
            }

            /*
            uint8_t * buf       = (uint8_t *)packet.piml->packet->data;
            uint8_t * sidebuf   = (uint8_t *)packet.piml->packet->side_data->data + 8;

            int keyframe  = !(buf[0] & 1);
            int profile   =  (buf[0]>>1) & 7;
            int invisible = !(buf[0] & 0x10);

            int sidekeyframe  = !(sidebuf[0] & 1);
            int sideprofile   =  (sidebuf[0]>>1) & 7;
            int sideinvisible = !(sidebuf[0] & 0x10);
            */
            // EyerLog("key: %2d, %5d   xxxxxxxxxxxxx  key: %2d, %5d\n", keyframe, packet.piml->packet->size, sidekeyframe, packet.piml->packet->side_data->size);
        }
        return ret;
    }

    EyerSmartPtr<EyerAVPacket> EyerAVReader::Read(int & ret)
    {
        EyerAVPacket * packetPtr = new EyerAVPacket();
        EyerSmartPtr<EyerAVPacket> packet(packetPtr);
        ret = Read(packetPtr);
        return packet;
    }

    int EyerAVReader::GetVideoStreamIndex() const
    {
        if(piml->formatCtx == nullptr){
            return -1;
        }
        int videoStream = av_find_best_stream(piml->formatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
        return videoStream;
    }

    int EyerAVReader::GetAudioStreamIndex() const
    {
        if (piml->formatCtx == nullptr) {
            return -1;
        }
        int audioStream = av_find_best_stream(piml->formatCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
        return audioStream;
    }
}