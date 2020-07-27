#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    IsLeftPress = false;
    IsMainWindowFullScreen = false;

    //窗口标题，不过设置无边框后也不会显示
    setWindowTitle("视频悬浮窗");
    //设置窗口最大最小尺寸
    setMaximumSize(480, 270);
    setMinimumSize(480, 270);
    //设置窗口样式为无边框
    setWindowFlags(Qt::FramelessWindowHint);
    //透明
    setAttribute(Qt::WA_TintedBackground, true);
    //设置透明度(0~1)
    setWindowOpacity(1);
    //设置鼠标形状
    setCursor(Qt::SizeAllCursor);


    QtAV::Widgets::registerRenderers();

    qtav_player = new QtAV::AVPlayer(this);
    qtav_videooutput = new QtAV::VideoOutput(this);

    qtav_player->setRenderer(qtav_videooutput);


    mainlayout = new QGridLayout;
    mainlayout->addWidget(qtav_videooutput->widget());
    mainlayout->setMargin(0);

    widget = new QWidget;
    this->setCentralWidget(widget);
    widget->setLayout(mainlayout);

//    QString file = QFileDialog::getOpenFileName(0, "选择要播放的视频", ".", "视频(*.mp4 *.avi);;All(*.*)");
//    qDebug()<<file;
//    if (file.isEmpty())
//    {
//        QMessageBox *mbox = new QMessageBox(QMessageBox::Information, QString("未选择"), QString("还可以在系统托盘中选择要播放的视频！"));
//        QTimer::singleShot(5000, mbox, SLOT(accept()));
//        mbox->exec();
//    }
    QString file = "./video/test.mp4";
    qtav_player->play(file);

//    my_player->play();

    //实例化菜单
    my_menu = new QMenu;

    //创建菜单项
    my_homePageAction = new QAction("官网", this);
    my_hlepAction = new QAction("帮助", this);
    my_aboutAction = new QAction("关于", this);
    my_upgradeAction = new QAction("检查更新", this);
    my_selectVideoAction = new QAction("选择视频", this);
    my_quitAction = new QAction("退出", this);

    //添加菜单项
    my_menu->addAction(my_homePageAction);
    my_menu->addAction(my_hlepAction);
    my_menu->addAction(my_aboutAction);
    my_menu->addAction(my_upgradeAction);
    my_menu->addAction(my_selectVideoAction);
    my_menu->addSeparator();
    my_menu->addAction(my_quitAction);

    my_trayIcon = new QSystemTrayIcon();
    my_trayIcon->setIcon(QIcon("tray.jpg"));
    my_trayIcon->setContextMenu(my_menu);
    my_trayIcon->show();
    my_trayIcon->setToolTip("MyVideoFloatWindow");
//    my_trayIcon->showMessage("欢迎", "已启动！", QSystemTrayIcon::Information, 1);

//    connect(&my_videoPlayer, SIGNAL(signalCreateVideoFrame(QImage)), this, SLOT(signalGetVideoFrame(QImage)));

    //播放视频
//    my_videoPlayer.setVideo("D:\\视频\\Captures\\视频2.mp4");
//    my_videoPlayer.start();
//    my_player->setMedia(QUrl::fromLocalFile("D:\\视频\\Captures\\视频2.mp4"));
//    my_player->setMedia(QMediaContent(QUrl("https://boringboys-1254394685.cos.ap-shanghai.myqcloud.com/video/video1.mp4")));

    hotkey_hide = new QHotkey(QKeySequence("meta+alt+h"), true);
    hotkey_show = new QHotkey(QKeySequence("meta+alt+s"), true);
    connect(hotkey_hide, &QHotkey::activated, [this](){
        if(!IsMainWindowFullScreen)
        {
            this->setVisible(false);
        }
        else
        {
            this->showNormal();
            this->setCursor(Qt::SizeAllCursor);
            IsMainWindowFullScreen = false;
            this->setVisible(false);
        }
    });
    connect(hotkey_show, &QHotkey::activated, [this](){
        if(!IsMainWindowFullScreen)
        {
            this->showNormal();
            this->activateWindow();
        }
    });

    connect(&hotkeythread, SIGNAL(signalHotKeyPress(int)), this, SLOT(signalHotKeyGet(int)));
    hotkeythread.start();

    connect(my_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconTouchSlot(QSystemTrayIcon::ActivationReason)));
    connect(my_trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClickedSlot()));
    connect(my_quitAction, SIGNAL(triggered(bool)), this, SLOT(quitActionSlot()));
    connect(my_homePageAction, SIGNAL(triggered(bool)), this, SLOT(homePageActionSlot()));
    connect(my_selectVideoAction, SIGNAL(triggered(bool)), this, SLOT(selectVideoActionSlot()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::trayIconTouchSlot(QSystemTrayIcon::ActivationReason type)
{
    switch (type) {
    case QSystemTrayIcon::Trigger:
        this->showNormal();
        this->activateWindow();
        break;
    case QSystemTrayIcon::DoubleClick:
        this->setVisible(false);
        break;
    default:
        break;
    }
}

void MainWindow::messageClickedSlot()
{
    QMessageBox::information(this, "点击了", "点击了！");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->setVisible(false);
    event->ignore();
}

void MainWindow::quitActionSlot()
{
//    QApplication *QApp;
//    QApp->exit(0);
    //退出程序时删除系统托盘图标，否则托盘图标不会及时消失
    delete my_trayIcon;
    exit(1);
}

void MainWindow::homePageActionSlot()
{
    QDesktopServices::openUrl(QUrl("www.auwaves.com"));
}

void MainWindow::selectVideoActionSlot()
{
    QString file = QFileDialog::getOpenFileName(0, "选择要播放的视频", ".", "视频(*.mp4 *.avi);;All(*.*)");
    if (file.isEmpty())
        return;
    qtav_player->play(file);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //按下的是鼠标左键
    if(event->button() == Qt::LeftButton)
    {
        /*鼠标是在窗体上按下时才标记为左键按下并记录位置*/
        /*这么做的原因：如果没有这个条件，当在窗体上按下左键之外的其它按键，并将光标移动到窗体外  */
        /*然后在窗体外按下左键，这时窗体也会跟着同步移动，但是光标始终不在窗体上，本人觉得这样不妥*/
        if(this->geometry().contains(event->globalPos()))
        {
            IsLeftPress = true;
            pos = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //左键按下时才移动
    if(event->buttons() & Qt::LeftButton && IsLeftPress)
    {
        move(event->globalPos()-pos);
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    //释放的是左键
    if(event->button() == Qt::LeftButton)
    {
        IsLeftPress = false;
        event->accept();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F5 && !IsMainWindowFullScreen)
    {
        this->showFullScreen();
        this->setCursor(Qt::ArrowCursor);
        IsMainWindowFullScreen = true;
    }
    else if(event->key() == Qt::Key_Escape && IsMainWindowFullScreen)
    {
        this->showNormal();
        this->setCursor(Qt::SizeAllCursor);
        IsMainWindowFullScreen = false;
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.setBrush(Qt::black);
//    painter.drawRect(0, 0, this->width(), this->height());

//    if(my_image.size().width() <= 0)
//        return;

    //缩放
//    QImage img_draw = my_image.scaled(this->size(), Qt::KeepAspectRatio);
//    int x = this->width() - img_draw.width();
//    int y = this->height() - img_draw.height();

//    x /= 2;
//    y /= 2;

//    painter.drawImage(QPoint(x, y), img_draw);
}

void MainWindow::signalGetVideoFrame(QImage image)
{
//    my_image = image;
    //绘制
    update();
}

void MainWindow::signalHotKeyGet(int signal)
{
    qDebug()<<"子线程的热键"<<signal;
}
