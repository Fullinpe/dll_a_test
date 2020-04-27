//
// Created by Fullinpe on 2020/4/26.
//

#ifndef FIRST_QT_AVUTILS_H
#define FIRST_QT_AVUTILS_H
#include "iostream"
extern "C"{
#include <avformat.h>
#include <pixdesc.h>
#include <timestamp.h>
#include <imgutils.h>

};

class AvUtils {

public:

    static AVFormatContext *&openCamera(const std::string& url);

    static int open_codec_context(int *stream_idx, AVCodecContext **dec_ctx, AVFormatContext *fmt_ctx, AVMediaType type);

    static int decode_packet(int *got_frame, int cached);
};


#endif //FIRST_QT_AVUTILS_H
