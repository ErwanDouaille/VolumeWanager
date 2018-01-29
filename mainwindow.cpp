#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent) , m_TitleBar(this)
{
    m_Cache = NULL;
    connect(this, SIGNAL(WindowTitleChanged()), &m_TitleBar, SLOT(updateWindowTitle()));
    connect(&m_TitleBar, SIGNAL(closeWindow()), this, SLOT(closeWindow()));

    setMinimumSize(512,512);
    setMaximumSize(512,512);
    setFixedSize(512, 512);
    resize(512, 512);
    setWindowTitle(tr("Volume Wanager"));
    setWindowFlags(Qt::FramelessWindowHint);

    m_MainLayout.setMargin(0);  // No space between window's element and the border
    m_MainLayout.setSpacing(0); // No space between window's element
    setLayout(&m_MainLayout);

    m_MainLayout.addWidget(&m_TitleBar, 0, 0, 1, 1);
    m_MainLayout.setRowStretch(1, 1);
    setAttribute(Qt::WA_TranslucentBackground);
    createTrayIcon();
}

void MainWindow::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    centerOnScreen();
}

void  MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible())
    {
        hide();
        event->ignore();
    }
}

void MainWindow::centerOnScreen()
{
    QDesktopWidget screen;

    QRect screenGeom = screen.screenGeometry(this);

    int screenCenterX = screenGeom.center().x();
    int screenCenterY = screenGeom.center().y();

    move(screenCenterX - width () / 2,
         screenCenterY - height() / 2);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if(m_Cache != NULL)
    {
        QPainter painter(this);
        painter.drawPixmap(0, 0, *m_Cache);
    }
}

void MainWindow::setWindowTitle(const QString &title)
{
    QWidget::setWindowTitle(title);
    emit WindowTitleChanged();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    delete m_Cache;
    m_Cache = new QPixmap(size());
    m_Cache->fill(Qt::transparent);

    QPainter painter(m_Cache);
    QPolygon background;
    background << QPoint(           0,            16)
               << QPoint(          16,             0)
               << QPoint(width() -  1,             0)
               << QPoint(width() -  1, height() - 17)
               << QPoint(width() -  17, height() - 1)
               << QPoint(          0, height() -  1);

    painter.setBrush(QPixmap(":/ressources/images/background.jpg"));
    painter.drawPolygon(background);
}

void  MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        setVisible(!isVisible());
        break;
    case QSystemTrayIcon::MiddleClick:
        showMessage();
        break;
    default:
        ;
    }
}

void  MainWindow::showMessage()
{
    trayIcon->showMessage("Test Title", "Hello world", QSystemTrayIcon::NoIcon, 2000);
}

void MainWindow::closeWindow()
{
    closeEvent(new QCloseEvent());
}

void  MainWindow::createTrayIcon()
{
    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    QIcon icon = QIcon(":/ressources/icons/ic_surround_sound_black_24dp.png");
    setWindowIcon(icon);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip(tr("Volume Wanager"));
    trayIcon->show();

    connect(trayIcon, &QSystemTrayIcon::activated, this, & MainWindow::iconActivated);
}
