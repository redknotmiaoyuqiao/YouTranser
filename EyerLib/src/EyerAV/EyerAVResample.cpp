#include "EyerAVResample.hpp"

#include "EyerAVResamplePrivate.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerAVFramePrivate.hpp"
#include "EyerMath/EyerMath.hpp"

namespace Eyer
{
    EyerAVResample::EyerAVResample()
    {
        piml = new EyerAVResamplePrivate();
    }

    EyerAVResample::~EyerAVResample()
    {
        if(piml->inputFifo != nullptr){
            av_audio_fifo_free(piml->inputFifo);
            piml->inputFifo = nullptr;
        }
        if(piml->outputFifo != nullptr){
            av_audio_fifo_free(piml->outputFifo);
            piml->outputFifo = nullptr;
        }
        if(piml->swrCtx != nullptr){
            swr_free(&piml->swrCtx);
            piml->swrCtx = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerAVResample::Init(
            EyerAVChannelLayout     _outputChannelLayout,
            EyerAVSampleFormat      _outputSampleFormat,
            int                     _outputSamplerate,

            EyerAVChannelLayout     _inputChannelLayout,
            EyerAVSampleFormat      _inputSampleFormat,
            int                     _inputSamplerate
    )
    {
        piml->inputSamplerate = _inputSamplerate;
        piml->outputSamplerate = _outputSamplerate;
        piml->inputChannelLayout = _inputChannelLayout;
        piml->outputChannelLayout = _outputChannelLayout;
        piml->inputSampleFormat = _inputSampleFormat;
        piml->outputSampleFormat = _outputSampleFormat;

        piml->swrCtx = swr_alloc_set_opts(
                NULL,
                piml->outputChannelLayout.GetFFmpegId(),
                (AVSampleFormat)piml->outputSampleFormat.ffmpegId,
                piml->outputSamplerate,

                piml->inputChannelLayout.GetFFmpegId(),
                (AVSampleFormat)piml->inputSampleFormat.ffmpegId,
                piml->inputSamplerate,

                0,
                NULL
        );
        swr_init(piml->swrCtx);

        int channels = av_get_channel_layout_nb_channels(piml->inputChannelLayout.GetFFmpegId());
        piml->inputFifo = av_audio_fifo_alloc((AVSampleFormat)piml->inputSampleFormat.ffmpegId, channels, piml->inputSamplerate);

        channels = av_get_channel_layout_nb_channels(piml->outputChannelLayout.GetFFmpegId());
        piml->outputFifo = av_audio_fifo_alloc((AVSampleFormat)piml->outputSampleFormat.ffmpegId, channels, piml->outputSamplerate);

        if(piml->inputSamplerate != piml->outputSamplerate){
            int commonDivisor = Eyer::Eath::GetGreatestCommonDivisor(piml->inputSamplerate, piml->outputSamplerate);
            piml->inputBlockSize = piml->inputSamplerate / commonDivisor;
            piml->outputBlockSize = piml->outputSamplerate / commonDivisor;
        }
        else {
            piml->inputBlockSize = 1024;
            piml->outputBlockSize = 1024;
        }

        EyerLog("Input: %d\n", piml->inputBlockSize);
        EyerLog("Output: %d\n", piml->outputBlockSize);

        return 0;
    }

    int EyerAVResample::PutAVFrame(EyerAVFrame & frame)
    {
        av_audio_fifo_write(piml->inputFifo,
                            (void **)frame.piml->frame->data,
                            frame.piml->frame->nb_samples
                            );


        while(1){
            int inputSize = av_audio_fifo_size(piml->inputFifo);
            if(inputSize < piml->inputBlockSize) {
                break;
            }
            // 读取，重裁样
            // 分配 48000 的空间
            EyerAVFrame inputFrame;
            inputFrame.piml->frame->channel_layout      = piml->inputChannelLayout.GetFFmpegId();
            inputFrame.piml->frame->channels            = av_get_channel_layout_nb_channels(inputFrame.piml->frame->channel_layout);
            inputFrame.piml->frame->sample_rate         = piml->inputSamplerate;
            inputFrame.piml->frame->format              = piml->inputSampleFormat.ffmpegId;
            inputFrame.piml->frame->nb_samples          = piml->inputBlockSize;
            av_frame_get_buffer(inputFrame.piml->frame, 1);

            av_audio_fifo_read(piml->inputFifo, (void **)inputFrame.piml->frame->data, inputFrame.piml->frame->nb_samples);

            EyerAVFrame outputFrame;
            outputFrame.piml->frame->channel_layout     = piml->outputChannelLayout.GetFFmpegId();
            outputFrame.piml->frame->channels           = av_get_channel_layout_nb_channels(outputFrame.piml->frame->channel_layout);
            outputFrame.piml->frame->sample_rate        = piml->outputSamplerate;
            outputFrame.piml->frame->format             = piml->outputSampleFormat.ffmpegId;

            int ret = swr_convert_frame(piml->swrCtx, outputFrame.piml->frame, inputFrame.piml->frame);

            av_audio_fifo_write(piml->outputFifo, (void **)outputFrame.piml->frame->data, outputFrame.piml->frame->nb_samples);
        }

        return 0;
    }

    int EyerAVResample::PutAVFrameNULL()
    {
        int inputSize = av_audio_fifo_size(piml->inputFifo);
        int length = inputSize % piml->inputBlockSize;
        if(length > 0){
            // 添加补齐数据
            EyerAVFrame inputFrame;
            inputFrame.piml->frame->channel_layout      = piml->inputChannelLayout.GetFFmpegId();
            inputFrame.piml->frame->channels            = av_get_channel_layout_nb_channels(inputFrame.piml->frame->channel_layout);
            inputFrame.piml->frame->sample_rate         = piml->inputSamplerate;
            inputFrame.piml->frame->format              = piml->inputSampleFormat.ffmpegId;
            inputFrame.piml->frame->nb_samples          = length;
            av_frame_get_buffer(inputFrame.piml->frame, 16);

            EyerLog("Fill : %d\n", inputFrame.piml->frame->nb_samples);
            // TODO 清0
            // Planner
            /*
            for(int i=0;i<inputFrame.piml->frame->channels;i++){
                int bytes = av_get_bytes_per_sample((AVSampleFormat)inputFrame.piml->frame->format);
                memset(inputFrame.piml->frame->data[i], 0, inputFrame.piml->frame->nb_samples * bytes);
            }
            */

            // PutAVFrame(inputFrame);
        }
        return 0;
    }

    int EyerAVResample::GetLastFrame(EyerAVFrame & frame, int frameSize)
    {
        int size = av_audio_fifo_size(piml->outputFifo);
        if(size < frameSize){
            int length = frameSize - size;
            EyerAVFrame fillFrame;
            fillFrame.piml->frame->channel_layout       = piml->outputChannelLayout.GetFFmpegId();
            fillFrame.piml->frame->channels             = av_get_channel_layout_nb_channels(fillFrame.piml->frame->channel_layout);
            fillFrame.piml->frame->sample_rate          = piml->outputSamplerate;
            fillFrame.piml->frame->format               = piml->outputSampleFormat.ffmpegId;
            fillFrame.piml->frame->nb_samples           = length;
            av_frame_get_buffer(fillFrame.piml->frame, 16);
            /*
            for(int i=0;i<fillFrame.piml->frame->channels;i++){
                int bytes = av_get_bytes_per_sample((AVSampleFormat)fillFrame.piml->frame->format);
                memset(fillFrame.piml->frame->data[i], 0, fillFrame.piml->frame->nb_samples * bytes);
            }
            */
            EyerLog("Fill : %d\n", fillFrame.piml->frame->nb_samples);
            av_audio_fifo_write(piml->outputFifo, (void **)fillFrame.piml->frame->data, fillFrame.piml->frame->nb_samples);
            GetFrame(frame, frameSize);
        }

        return 0;
    }

    int EyerAVResample::GetFrame(EyerAVFrame & frame, int frameSize)
    {
        int size = av_audio_fifo_size(piml->outputFifo);
        if(size < frameSize){
            return -1;
        }

        frame.piml->frame->channel_layout       = piml->outputChannelLayout.GetFFmpegId();
        frame.piml->frame->channels             = av_get_channel_layout_nb_channels(frame.piml->frame->channel_layout);
        frame.piml->frame->sample_rate          = piml->outputSamplerate;
        frame.piml->frame->format               = piml->outputSampleFormat.ffmpegId;
        frame.piml->frame->nb_samples           = frameSize;
        av_frame_get_buffer(frame.piml->frame, 1);

        av_audio_fifo_read(piml->outputFifo, (void **)frame.piml->frame->data, frame.piml->frame->nb_samples);

        return 0;
    }
}