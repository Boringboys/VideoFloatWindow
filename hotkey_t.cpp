#include "hotkey_t.h"

Hotkey_T::Hotkey_T()
{

}

Hotkey_T::~Hotkey_T()
{

}

void Hotkey_T::play()
{
    start();
}

void Hotkey_T::run()
{
    hotkey_threadtest = new QHotkey(QKeySequence("meta+alt+l"), true);
    connect(hotkey_threadtest, &QHotkey::activated, [this]{
       testHotKeyPressSlot();
    });
    exec();
}

void Hotkey_T::testHotKeyPressSlot()
{
    emit signalHotKeyPress(1);
}
