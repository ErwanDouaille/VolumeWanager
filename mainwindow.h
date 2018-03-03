#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QGridLayout>
#include <QSizeGrip>
#include <QAction>
#include <QDesktopWidget>
#include <QPushButton>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QComboBox>
#include <QVBoxLayout>

#include "mainwindowtitlebar.h"
#include "volumemanager.h"
#include "serialconnection.h"

const int WIDTH = 600;
const int HEIGHT = 170;


class MainWindow: public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event) override;
    void initVolumeWanager();
    void initGUI();
    void centerOnScreen();
    void paintEvent(QPaintEvent *event);
    void createTrayIcon();
    void setWindowTitle(const QString &title);
    void refreshSessionList();
    std::string getApplicationNameFor(int id);

    QGridLayout m_MainLayout;
    MainWindowTitleBar m_TitleBar;
    QPixmap *m_Cache;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    VolumeManager * vm;
    SerialConnection * sc;
    QPushButton* refreshButton;
    QComboBox* sessionList0;
    QComboBox* sessionList1;
    QComboBox* sessionList2;
    QComboBox* sessionList3;

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessage();
    void closeWindow();
    void volumeChanged(int id, int value);
    void refreshAppList();


signals:
    void WindowTitleChanged();
    void appVolumeChanged(std::string appName, int value);
};

#endif
