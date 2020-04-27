#include <iostream>
#include <synchapi.h>

//#include "AvUtils.h"

extern "C" {
#include <swscale.h>
#include <avdevice.h>
#include <avcodec.h>
#include <pixfmt.h>
#include <avformat.h>
#include <avfilter.h>

}
using namespace std;


int main() {

//    avformat_network_init();
//    AVFormatContext *avFormatContext = nullptr;
//
//    int ret = openinput(&avFormatContext, R"(C:\Users\Fullinpe\Desktop\out.mp4)");
//    if(avFormatContext)
//        ret = avFormatContext->streams[0]->nb_frames;
//    cout << ret << endl;
//
//    Sleep(2000);
//
//    avformat_free_context(avFormatContext);

    avdevice_register_all();

    AVFormatContext *cam = nullptr;
    AVInputFormat *iformat = av_find_input_format("dshow");
    string url = "video=USB2.0 HD UVC WebCam:audio=麦克风 (Realtek High Definition Audio)";
    if (avformat_open_input(&cam, url.c_str(), iformat, nullptr) != 0) {
        printf("Couldn't open input stream.\n");
    }
    /* retrieve stream information */
    if (avformat_find_stream_info(cam, nullptr) < 0) {
        fprintf(stderr, "Could not find stream information\n");
        exit(1);
    }

//    AVFormatContext *cam = AvUtils::openCamera("video=USB2.0 HD UVC WebCam:audio=麦克风 (Realtek High Definition Audio)");

    if (cam) {   //---------------------------------------------

        int videoindex = -1;
        for (int i = 0; i < cam->nb_streams; i++) {
            if (cam->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
                videoindex = i;
            }
        }
        if (videoindex == -1) {
            printf("Couldn't find a video stream.\n");
            return -1;
        }
        AVCodecContext *pCodecCtx = cam->streams[videoindex]->codec;
        AVCodec *pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
        if (pCodec == NULL) {
            printf("Codec not found.\n");
            return -1;
        }
        if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
            printf("Could not open codec.\n");
            return -1;
        }
        AVFrame *pFrame, *pFrameYUV;
        pFrame = av_frame_alloc();
        pFrameYUV = av_frame_alloc();
        uint8_t *out_buffer = (uint8_t *) av_malloc(
                avpicture_get_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height));
        avpicture_fill((AVPicture *) pFrameYUV, out_buffer, AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);
        int ret, got_picture;
        AVPacket *packet = (AVPacket *) av_malloc(sizeof(AVPacket));
        FILE *fp_yuv = fopen("output.yuv", "wb");
        struct SwsContext *img_convert_ctx;

        AVPixelFormat pixFormat;
        switch (cam->streams[0]->codec->pix_fmt) {
            case AV_PIX_FMT_YUVJ420P :
                pixFormat = AV_PIX_FMT_YUV420P;
                break;
            case AV_PIX_FMT_YUVJ422P  :
                pixFormat = AV_PIX_FMT_YUV422P;
                break;
            case AV_PIX_FMT_YUVJ444P   :
                pixFormat = AV_PIX_FMT_YUV444P;
                break;
            case AV_PIX_FMT_YUVJ440P :
                pixFormat = AV_PIX_FMT_YUV440P;
                break;
            default:
                pixFormat = *cam->streams[0]->codec->codec->pix_fmts;
                break;
        }

        img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pixFormat, pCodecCtx->width,
                                         pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
        ///这里打印出视频的宽高
        fprintf(stderr, "w= %d h= %d\n", pCodecCtx->width, pCodecCtx->height);
        ///我们就读取100张图像
        for (int i = 0; i < 5; i++) {
            if (av_read_frame(cam, packet) < 0) {
                break;
            }
            if (packet->stream_index == videoindex) {
                ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
                if (ret < 0) {
                    printf("Decode Error.\n");
                    return -1;
                }
                if (got_picture) {
                    sws_scale(img_convert_ctx, (const uint8_t *const *) pFrame->data, pFrame->linesize, 0,
                              pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
                    int y_size = pCodecCtx->width * pCodecCtx->height;
                    fwrite(pFrameYUV->data[0], 1, y_size, fp_yuv);    //Y
                    fwrite(pFrameYUV->data[1], 1, y_size / 4, fp_yuv);  //U
                    fwrite(pFrameYUV->data[2], 1, y_size / 4, fp_yuv);  //V
                }
            }
            av_free_packet(packet);
        }
        sws_freeContext(img_convert_ctx);
        fclose(fp_yuv);
        av_free(out_buffer);
        av_free(pFrameYUV);
        avcodec_close(pCodecCtx);
        avformat_close_input(&cam);
//        printf("%d*%d\n", cam->streams[0]->codecpar->width, cam->streams[0]->codecpar->height);

    }

    return 0;
}
