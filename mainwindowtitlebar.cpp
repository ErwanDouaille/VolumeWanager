#include "mainwindowtitlebar.h"

MainWindowTitleBar::MainWindowTitleBar(QWidget *parent)
    : QWidget(parent),
      m_Title(this),
      m_Close(this)
{
    connect(&m_Close, SIGNAL(clicked()), this, SLOT(close()));
    setFixedHeight(33);
    m_Cache = NULL;
    m_Title.setStyleSheet("color: white; font-family: Sans; font-weight: bold; font-size: 14px");
    updateWindowTitle();
}

void MainWindowTitleBar::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    delete m_Cache;
    m_Cache = new QPixmap(size());
    m_Cache->fill(Qt::transparent);
    m_Title.move(28, 4);
    m_Title.resize(width() - 116, 29);
    m_Close.move(width()-28 , 9);
}

void MainWindowTitleBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if(m_Cache != NULL)
    {
        QPainter painter(this);
        painter.drawPixmap(0, 0, *m_Cache);
    }
}

void MainWindowTitleBar::updateWindowTitle()
{
    m_Title.setText(window()->windowTitle());
}

void MainWindowTitleBar::close()
{
    emit closeWindow();
}

void MainWindowTitleBar::mousePressEvent(QMouseEvent *event)
{
    m_Diff = event->pos();
    setCursor(QCursor(Qt::SizeAllCursor));
}

void MainWindowTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    setCursor(QCursor(Qt::ArrowCursor));
}

void MainWindowTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p = event->globalPos();
    window()->move(p - m_Diff);
}

