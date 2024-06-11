#ifndef EYERLIB_EYERAVFFMPEGHEADER_HPP
#define EYERLIB_EYERAVFFMPEGHEADER_HPP

extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libavutil/audio_fifo.h>
#include <libavutil/avutil.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libavutil/pixdesc.h>
#include <libavutil/imgutils.h>
#include <libavutil/md5.h>
#include <libswscale/swscale.h>
#include <libavutil/samplefmt.h>
#include <libavutil/version.h>
}

#endif //EYERLIB_EYERAVFFMPEGHEADER_HPP
