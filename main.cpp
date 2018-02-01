#include <QApplication>
#include <QMessageBox>
#include <windows.h>
#include <QDebug>

#include "mainwindow.h"
#include "volumemanager.h"

int main(int argc, char *argv[])
{
//    QApplication app(argc, argv);

//    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
//        QMessageBox::critical(0, QObject::tr("Systray"), QObject::tr("I couldn't detect any system tray on this system."));
//        return 1;
//    }
//    QApplication::setQuitOnLastWindowClosed(false);

//    MainWindow window;
//    window.show();
    VolumeManager * vm = new VolumeManager();
    vm->getAvailableSessions();
//    return app.exec();
}
