#ifndef SERIALCONNECTION_H
#define SERIALCONNECTION_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtSerialPort/QtSerialPort>
#include <iostream>
#include <thread>

class SerialConnection : public QObject
{
    Q_OBJECT
public:
    explicit SerialConnection(QObject *parent = nullptr);
    ~SerialConnection();
    bool running() const;
    void setRunning(bool running);

protected:
    std::thread m_thread;
    bool m_running = true;

    void parseData(QByteArray message);
    void run();

signals:
    void volumeChanged(int id, int value);
};

#endif // SERIALCONNECTION_H
