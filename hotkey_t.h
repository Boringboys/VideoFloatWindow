#ifndef HOTKEY_H
#define HOTKEY_H

#include <QThread>
#include <QHotkey>
#include "common.h"

class Hotkey_T : public QThread
{
    Q_OBJECT

public:
    Hotkey_T();
    ~Hotkey_T();

    inline void play();

private:
    QHotkey *hotkey_threadtest;

signals:
    void signalHotKeyPress(int signal);

private slots:
    void testHotKeyPressSlot();

protected:
    void run();
};

#endif // HOTKEY_H
