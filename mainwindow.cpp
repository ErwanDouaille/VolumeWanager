#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent) , m_TitleBar(this)
{
    m_Cache = NULL;
    m_sSettingsFile = QApplication::applicationDirPath() + "/settings.ini";
    connect(this, SIGNAL(WindowTitleChanged()), &m_TitleBar, SLOT(updateWindowTitle()));
    connect(&m_TitleBar, SIGNAL(closeWindow()), this, SLOT(closeWindow()));

    setMinimumSize(WIDTH,HEIGHT);
    setMaximumSize(WIDTH,HEIGHT);
    setFixedSize(WIDTH, HEIGHT);
    resize(WIDTH, HEIGHT);
    setWindowTitle(tr("Volume Wanager"));
    setWindowFlags(Qt::FramelessWindowHint);

    m_MainLayout.setMargin(0);  // No space between window's element and the border
    m_MainLayout.setSpacing(0); // No space between window's element
    setLayout(&m_MainLayout);
    
    m_MainLayout.addWidget(&m_TitleBar, 0, 0, 1, 9, Qt::AlignTop);
    m_MainLayout.setRowStretch(1, 1);
    setAttribute(Qt::WA_TranslucentBackground);
    createTrayIcon();
    initVolumeWanager();
    initGUI();
}

void MainWindow::initVolumeWanager()
{
    vm = new VolumeManager();
    vm->getAvailableSessions();
    sc = new SerialConnection();
    QObject::connect(sc, SIGNAL(volumeChanged(int, int)), this, SLOT(volumeChanged(int, int)));
    QObject::connect(this, SIGNAL(appVolumeChanged(std::string, int)), vm, SLOT(appVolumeChanged(std::string, int)));
}

void MainWindow::initGUI()
{
    // Not proud of the design .. but anyway, it gonna be static
    comboBoxList.push_back(new QComboBox());
    comboBoxList.push_back(new QComboBox());
    comboBoxList.push_back(new QComboBox());
    comboBoxList.push_back(new QComboBox());

    refreshButton = new QPushButton();
    QIcon icon = QIcon(":/ressources/icons/ic_refresh_white_24dp.png");
    refreshButton->setIcon(icon);
    refreshButton->setFlat(true);
    QObject::connect(refreshButton, SIGNAL(clicked()), this, SLOT(refreshAppList()));

    QPixmap* pixmap_img = new QPixmap(":/ressources/images/button.png");
    m_MainLayout.addWidget(refreshButton, 1, 8, 1,1, Qt::AlignTop);

    QLabel* label_img0  = new QLabel(this);
    label_img0->setPixmap(pixmap_img->scaled(60,60,Qt::KeepAspectRatio));
    QLabel* label_img1  = new QLabel(this);
    label_img1->setPixmap(pixmap_img->scaled(60,60,Qt::KeepAspectRatio));
    QLabel* label_img2  = new QLabel(this);
    label_img2->setPixmap(pixmap_img->scaled(60,60,Qt::KeepAspectRatio));
    QLabel* label_img3  = new QLabel(this);
    label_img3->setPixmap(pixmap_img->scaled(60,60,Qt::KeepAspectRatio));

    m_MainLayout.addWidget(new QLabel(), 3, 7, 1,1, Qt::AlignCenter);

    m_MainLayout.addWidget(label_img0, 2, 1, 1, 1, Qt::AlignCenter);
    m_MainLayout.addWidget(comboBoxList.at(0), 4, 1, 1,1, Qt::AlignCenter);

    m_MainLayout.addWidget(label_img1, 2, 3, 1, 1, Qt::AlignCenter);
    m_MainLayout.addWidget(comboBoxList.at(1), 4, 3, 1,1, Qt::AlignCenter);

    m_MainLayout.addWidget(label_img2, 2, 5, 1, 1, Qt::AlignCenter);
    m_MainLayout.addWidget(comboBoxList.at(2), 4, 5, 1,1, Qt::AlignCenter);

    m_MainLayout.addWidget(label_img3, 2, 7, 1, 1, Qt::AlignCenter);
    m_MainLayout.addWidget(comboBoxList.at(3), 4, 7, 1,1, Qt::AlignCenter);

    m_MainLayout.addWidget(new QLabel(), 5, 7, 1,1, Qt::AlignCenter);

    refreshSessionList();
    loadSettings();
    for(std::vector<QComboBox*>::iterator it = comboBoxList.begin(); it != comboBoxList.end(); it++)
        QObject::connect((*it), SIGNAL(currentTextChanged(QString)), this, SLOT(selectionChanged(QString)));

}

void MainWindow::refreshSessionList()
{
    for(std::vector<QComboBox*>::iterator it = comboBoxList.begin(); it != comboBoxList.end(); it++)
        QObject::disconnect((*it), SIGNAL(currentTextChanged(QString)), this, SLOT(selectionChanged(QString)));

    std::vector<std::string> list = vm->getAvailableSessions();
    for(std::vector<QComboBox*>::iterator it = comboBoxList.begin(); it != comboBoxList.end(); it++)
        (*it)->clear();
    for(std::vector<std::string>::iterator it = list.begin(); it != list.end(); it++)
    {
        for(std::vector<QComboBox*>::iterator item = comboBoxList.begin(); item != comboBoxList.end(); item++)
            (*item)->addItem(QString::fromStdString(*it));
    }
    loadSettings();
    for(std::vector<QComboBox*>::iterator it = comboBoxList.begin(); it != comboBoxList.end(); it++)
        QObject::connect((*it), SIGNAL(currentTextChanged(QString)), this, SLOT(selectionChanged(QString)));

}

void MainWindow::loadSettings()
{
    QSettings* settings = new QSettings(m_sSettingsFile, QSettings::IniFormat);
    QString value;
    for (int i = 0; i < 4; i++)
    {
        value = settings->value("id" + QString::number(i), "").toString();
        int index = comboBoxList.at(i)->findText(value);
        if ( index != -1 ) {
           comboBoxList.at(i)->setCurrentIndex(index);
        } else
        {
            comboBoxList.at(i)->addItem(value);
            comboBoxList.at(i)->setCurrentText(value);
        }
    }
}

void MainWindow::saveSettings()
{
    QSettings* settings = new QSettings(m_sSettingsFile, QSettings::IniFormat);
    for (int i = 0; i < comboBoxList.size(); i++)
    {
        settings->setValue("id" + QString::number(i), comboBoxList.at(i)->currentText());
    }
    settings->sync();
}

std::string MainWindow::getApplicationNameFor(int id)
{
    switch (id) {
    case 0:
        return comboBoxList.at(id)->currentText().toStdString();
    case 1:
        return comboBoxList.at(id)->currentText().toStdString();
    case 2:
        return comboBoxList.at(id)->currentText().toStdString();
    case 3:
        return comboBoxList.at(id)->currentText().toStdString();
    }
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
        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
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

void MainWindow::volumeChanged(int id, int value)
{
    std::string appName = getApplicationNameFor(id);
    emit appVolumeChanged(appName, value);
}

void MainWindow::refreshAppList()
{
    refreshSessionList();
}

void MainWindow::selectionChanged(QString)
{
    saveSettings();
}

void  MainWindow::createTrayIcon()
{
    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    QIcon icon = QIcon(":/ressources/icons/ic_surround_sound_white_24dp.png");
    setWindowIcon(icon);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip(tr("Volume Wanager"));
    trayIcon->show();

    connect(trayIcon, &QSystemTrayIcon::activated, this, & MainWindow::iconActivated);
}
