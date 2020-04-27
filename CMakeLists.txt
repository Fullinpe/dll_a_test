cmake_minimum_required(VERSION 3.15)
project(dll_a_test)

set(CMAKE_CXX_STANDARD 14)

link_directories(ffmpeg-4.2.2/lib)

include_directories(ffmpeg-4.2.2/include/libavcodec ffmpeg-4.2.2/include/libavdevice ffmpeg-4.2.2/include/libavfilter ffmpeg-4.2.2/include/libavformat
        ffmpeg-4.2.2/include/libavutil ffmpeg-4.2.2/include/libpostproc ffmpeg-4.2.2/include/libswresample ffmpeg-4.2.2/include/libswscale ffmpeg-4.2.2/include)


#add_library(dll_a_test main.cpp)
add_executable(dll_a_test main.cpp)

#target_link_libraries(
#        dll_a_test
#        -Wl,-Bstatic                       #以下为静态库
#        -Wl,--start-group
#        -lm -lz -lsecur32 -lws2_32
#        -luser32 -lbcrypt
#        -liconv -lm -lz -lole32 -luser32
#        -lavformat
#        -lavdevice
#        -lavfilter
#        -lavcodec
#        -lavutil
#        -lpostproc
#        -lswscale
#        -lswresample
#        -Wl,--end-group
#        -lstdc++ -lgcc_eh -lpthread
##        -Wl,-Bdynamic                      #以下为动态库
#)

target_link_libraries(
        dll_a_test
        avformat
        avdevice
        avfilter
        avcodec
        avutil
        postproc
        swscale
        swresample
        #        avcodec-58 avdevice-58 avfilter-7 avformat-58 avutil-56 postproc-55 swresample-3 swscale-5
)
