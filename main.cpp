#include <iostream>
#include <synchapi.h>

extern "C" {

#include <avcodec.h>
#include <pixfmt.h>
#include <avformat.h>
#include <avfilter.h>

}
using namespace std;


int openinput(AVFormatContext **avFormatContext, const string &url) {
    *avFormatContext = avformat_alloc_context();
    (*avFormatContext)->interrupt_callback.callback = [](void *) -> int {
        int x=av_gettime();
        cout << "KKK"<< x << endl;
        return 0;
    };
    int ret = avformat_open_input(avFormatContext, url.c_str(), nullptr, nullptr);
    if (ret < 0) {
        av_log(nullptr, AV_LOG_ERROR, "OPEN FAILED");
        return -1;
    }
    ret = avformat_find_stream_info(*avFormatContext, nullptr);
    if (ret >= 0)
        av_log(nullptr, AV_LOG_ERROR, "READ SUCCESS");
    else
        av_log(nullptr, AV_LOG_ERROR, "READ FAILED");
    return ret;
}

int main() {

    avformat_network_init();
    AVFormatContext *avFormatContext = nullptr;

    int ret = openinput(&avFormatContext, R"(C:\Users\Fullinpe\Desktop\out.mp4)");
    if(avFormatContext)
        ret = avFormatContext->streams[0]->nb_frames;
    cout << ret << endl;

    Sleep(2000);

    avformat_free_context(avFormatContext);

    return 0;
}
