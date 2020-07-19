#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QThread>
#include <QImage>

class VideoPlayer : public QThread
{
    Q_OBJECT

public:
    VideoPlayer();
    ~VideoPlayer();

    void setVideo(const QString &videoPath)
    {
        this->videoPath = videoPath;
    }

    inline void play();

signals:
    void signalCreateVideoFrame(QImage image);

protected:
    void run();

private:
    QString videoPath;
};

#endif // VIDEOPLAYER_H
