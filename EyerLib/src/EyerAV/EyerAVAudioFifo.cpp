#include "EyerAVAudioFifo.hpp"

#include "EyerAVAudioFifoPrivate.hpp"
#include "EyerAVFramePrivate.hpp"

namespace Eyer
{
    EyerAVAudioFifo::EyerAVAudioFifo(
            EyerAVSampleFormat sampleFormat,
            EyerAVChannelLayout channelLayout,
            int sampleRate)
    {
        piml = new EyerAVAudioFifoPrivate();
        piml->fifo = av_audio_fifo_alloc(
                (AVSampleFormat)sampleFormat.ffmpegId,
                EyerAVChannelLayout::GetChannelLayoutNBChannels(channelLayout),
                sampleRate
                );

        piml->sampleFormat = sampleFormat;
        piml->channelLayout = channelLayout;
        piml->sampleRate = sampleRate;
    }

    EyerAVAudioFifo::~EyerAVAudioFifo()
    {
        if(piml->fifo != nullptr){
            av_audio_fifo_free(piml->fifo);
            piml->fifo = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerAVAudioFifo::PutAVFrame(EyerAVFrame & avFrame)
    {
        av_audio_fifo_write(piml->fifo,
                            (void **)avFrame.piml->frame->data,
                            avFrame.piml->frame->nb_samples
        );
        return 0;
    }

    int EyerAVAudioFifo::GetAVFrame(EyerAVFrame & frame, int sampleNB)
    {
        int size = av_audio_fifo_size(piml->fifo);
        if(size < sampleNB){
            return -1;
        }

        frame.piml->frame->channel_layout       = piml->channelLayout.GetFFmpegId();
        frame.piml->frame->channels             = av_get_channel_layout_nb_channels(frame.piml->frame->channel_layout);
        frame.piml->frame->sample_rate          = piml->sampleRate;
        frame.piml->frame->format               = piml->sampleFormat.ffmpegId;
        frame.piml->frame->nb_samples           = sampleNB;
        av_frame_get_buffer(frame.piml->frame, 1);

        av_audio_fifo_read(piml->fifo, (void **)frame.piml->frame->data, frame.piml->frame->nb_samples);

        return 0;
    }
}