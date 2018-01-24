#include "mainwindow.h"

#include <QAction>
#include <QCoreApplication>
#include <QCloseEvent>

MainWindow:: MainWindow()
{
    createTrayIcon();

    setWindowTitle(tr("Volume Wanager"));
    resize(400, 300);
}

void  MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible())
    {
        hide();
        event->ignore();
    }
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
