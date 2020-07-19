#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QApplication>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>
#include <QMessageBox>
#include <QWidget>
#include <QGridLayout>
#include <QMouseEvent>
#include <QDesktopServices>
//用ffmpeg实现的视频播放器
#include "videoplayer.h"
#include <QImage>
#include <QPainter>
#include <QPaintEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //系统托盘
    QSystemTrayIcon *my_trayIcon;
    //菜单
    QMenu *my_menu;
    //菜单项
    QAction *my_homePageAction;
    QAction *my_hlepAction;
    QAction *my_aboutAction;
    QAction *my_upgradeAction;
    QAction *my_quitAction;
    //widget
    QWidget *widget;
    //布局
    QGridLayout *mainlayout;
    //MediaPlayer//播放器
    VideoPlayer my_videoPlayer;
    QImage my_image;
    //坐标
    QPoint pos;
    //一些判断标志
    bool IsLeftPress;

protected:
    //关闭事件
    void closeEvent(QCloseEvent *event);
    //鼠标事件
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    //绘制
    void paintEvent(QPaintEvent *event);

private slots:
    void trayIconTouchSlot(QSystemTrayIcon::ActivationReason type);
    void messageClickedSlot();
    void quitActionSlot();
    void homePageActionSlot();

    void signalGetVideoFrame(QImage image);
};

#endif // MAINWINDOW_H
