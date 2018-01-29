#ifndef MAINWINDOWTITLEBAR_H
#define MAINWINDOWTITLEBAR_H

#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include "mainwindowbutton.h"

class MainWindowTitleBar : public QWidget
{
    Q_OBJECT

public:
    MainWindowTitleBar(QWidget *parent = 0);

public slots:
    void updateWindowTitle();
    void close();

signals:
    void closeWindow();

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent (QPaintEvent  *event);
    void mousePressEvent  (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent   (QMouseEvent *event);
private:
    QPixmap *m_Cache;
    QLabel m_Title;
    MainWindowButton m_Close;
    QPoint m_Diff;
};
#endif // MAINWINDOWTITLEBAR_H

