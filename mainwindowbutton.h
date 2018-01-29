#ifndef MAINWINDOWBUTTON_H
#define MAINWINDOWBUTTON_H

#include <QPixmap>
#include <QPainter>
#include <QAbstractButton>

class MainWindowButton : public QAbstractButton
{
    Q_OBJECT

public:
    MainWindowButton(QWidget *parent = 0);
    ~MainWindowButton();

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent (QPaintEvent  *event);
    void enterEvent       (QEvent      *event);
    void leaveEvent       (QEvent      *event);
    void mousePressEvent  (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    enum ButtonState
    {
        STATE_NORMAL, STATE_HOVERED, STATE_CLICKED
    };

    ButtonState m_State  ;
    QPixmap    *m_Normal ;
    QPixmap    *m_Hovered;
    QPixmap    *m_Clicked;

    void InitPixmaps();
    void InitPixmap(QPixmap **pixmap);
    void InitClose();
};

#endif // MAINWINDOWBUTTON_H
