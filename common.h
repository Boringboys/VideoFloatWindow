#ifndef COMMON_H
#define COMMON_H

#include <QObject>

class Common:public QObject
{
    Q_OBJECT

public:
    enum HotKeySignal
    {
        Hide = 0,
        Show,
    };
    Q_ENUM(HotKeySignal)
};


#endif // COMMON_H
