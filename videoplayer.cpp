#include "videoplayer.h"

#include <iostream>
#include <QDebug>

extern "C"
{
    #include "libavcodec/avcodec.h"
//    #include "libavformat/avformat.h"
//    #include "libavutil/pixfmt.h"
//    #include "libswscale/swscale.h"
}

VideoPlayer::VideoPlayer()
{

}

VideoPlayer::~VideoPlayer()
{

}

void VideoPlayer::play()
{
    start();
}

void VideoPlayer::run()
{

}
