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
    //demo
    int index = 1;
    while(true)
    {
        emit signalCreateVideoFrame(QImage("imgs/"+QString::number(index)+".jpg"));
        index += 1;
        if(index > 10)
        {
            index = 1;
        }
        sleep(1);

    }
}
