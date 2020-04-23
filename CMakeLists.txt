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
##        -Wl,-Bstatic -lstdc++ -lgcc_eh -lpthread -Wl,-Bdynamic
#)


target_link_libraries(dll_a_test libavcodec.lib)
target_link_libraries(dll_a_test libavformat.lib)
target_link_libraries(dll_a_test libavdevice.lib)
target_link_libraries(dll_a_test libavutil.lib)
target_link_libraries(dll_a_test libavfilter.lib)
target_link_libraries(dll_a_test libpostproc.lib)
target_link_libraries(dll_a_test libswscale.lib)
target_link_libraries(dll_a_test libswresample.lib)