#include "mainwindowbutton.h"

MainWindowButton::MainWindowButton(QWidget *parent) : QAbstractButton(parent),
    m_State  (STATE_NORMAL),
    m_Normal (NULL),
    m_Hovered(NULL),
    m_Clicked(NULL)
{
    resize(20,20);
}

MainWindowButton::~MainWindowButton()
{
    delete m_Normal ;
    delete m_Hovered;
    delete m_Clicked;
}

void MainWindowButton::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    InitPixmaps();
}

void MainWindowButton::paintEvent(QPaintEvent  *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    if(isEnabled())
    {
        switch(m_State)
        {
        case STATE_NORMAL:
            if(m_Normal  != NULL) painter.drawPixmap(0, 0, *m_Normal );
            break;
        case STATE_HOVERED:
            if(m_Hovered != NULL) painter.drawPixmap(0, 0, *m_Hovered);
            break;
        case STATE_CLICKED:
            if(m_Clicked != NULL) painter.drawPixmap(0, 0, *m_Clicked);
            break;
        }
    }
    else
        if(m_Normal != NULL) painter.drawPixmap(0, 0, *m_Normal);
}

void MainWindowButton::InitPixmaps()
{
    InitPixmap(&m_Normal );
    InitPixmap(&m_Hovered);
    InitPixmap(&m_Clicked);
    InitClose();
}

void MainWindowButton::InitPixmap(QPixmap **pixmap)
{
    delete *pixmap;
    *pixmap = new QPixmap(size());
    (*pixmap)->fill(Qt::transparent);
}


void MainWindowButton::InitClose()
{
    /********** Button's symbol **********/
    QLine symbol1(QPoint(          5, 5), QPoint(width() - 9, height() - 9));
    QLine symbol2(QPoint(width() - 9, 5), QPoint(          5, height() - 9));
    /*************************************/
    QColor gradientStart(  0,   0,   0,   0);
    QColor gradientEnd  (  0,   0,   0, 220);
    QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
    linearGrad.setColorAt(0, gradientStart);
    linearGrad.setColorAt(1, gradientEnd  );
    QLinearGradient invertlinearGrad(QPointF(0, 0), QPointF(0, height()));
    invertlinearGrad.setColorAt(0, gradientEnd  );
    invertlinearGrad.setColorAt(1, gradientStart);
    QPainter painter;

    /********** Normal **********/
    painter.begin(m_Normal);
    painter.setPen  (QPen(Qt::black   ));
    painter.setBrush(QBrush(linearGrad));
    painter.drawEllipse( 0, 0, width()-5, height()-5);
    painter.setPen(QPen(QBrush(Qt::black), 2.0));
    painter.drawLine(symbol1);
    painter.drawLine(symbol2);
    painter.end();
    /****************************/

    /********** Hovered **********/
    painter.begin(m_Hovered);
    painter.setPen  (QPen  (Qt::black ));
    painter.setBrush(QBrush(linearGrad));
    painter.drawEllipse( 0, 0, width()-5, height()-5);
    painter.setPen(QPen(QBrush(Qt::white), 2.0));
    painter.drawLine(symbol1);
    painter.drawLine(symbol2);
    painter.end();
    /*****************************/

    /********** Clicked **********/
    painter.begin(m_Clicked);
    painter.setPen  (QPen  (Qt::black       ));
    painter.setBrush(QBrush(invertlinearGrad));
    painter.drawEllipse( 0, 0, width()-5, height()-5);
    painter.setPen(QPen(QBrush(Qt::white), 2.0));
    painter.drawLine(symbol1);
    painter.drawLine(symbol2);
    painter.end();
    /*****************************/
}

void MainWindowButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_State = STATE_HOVERED;
    update();
}

void MainWindowButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_State = STATE_NORMAL;
    update();
}

void MainWindowButton::mousePressEvent(QMouseEvent *event)
{
    QAbstractButton::mousePressEvent(event);
    m_State = STATE_CLICKED;
    update();
}

void MainWindowButton::mouseReleaseEvent(QMouseEvent *event)
{
    QAbstractButton::mouseReleaseEvent(event);
    if(underMouse()) m_State = STATE_HOVERED;
    else             m_State = STATE_NORMAL;
    update();
}
