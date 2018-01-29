#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QGridLayout>
#include <QSizeGrip>
#include <QAction>
#include <QDesktopWidget>
#include <QSystemTrayIcon>
#include <QMenu>

#include "mainwindowtitlebar.h"

class MainWindow: public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

signals:
    void WindowTitleChanged();

protected:
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event) override;

private:
    void centerOnScreen();
    void paintEvent(QPaintEvent *event);
    void createTrayIcon();
    void setWindowTitle(const QString &title);

    QGridLayout m_MainLayout;
    MainWindowTitleBar m_TitleBar;
    QPixmap *m_Cache;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessage();
    void closeWindow();
};

#endif
