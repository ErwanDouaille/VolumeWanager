#include "serialconnection.h"

SerialConnection::SerialConnection(QObject *parent) : QObject(parent)
{
    m_thread = std::thread(&SerialConnection::run, this);
}

SerialConnection::~SerialConnection()
{
    m_running = false;
    if(m_thread.joinable())
        m_thread.join();
}

bool SerialConnection::running() const
{
    return m_running;
}

void SerialConnection::setRunning(bool running)
{
    m_running = running;
}

void SerialConnection::run()
{
    while(m_running)
    {
        foreach ( const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            if (info.description().compare("Arduino Leonardo") == 0)
            {
                QSerialPort serial;
                serial.setPort(info);
                serial.setBaudRate(QSerialPort::Baud9600);
                serial.setDataBits(QSerialPort::Data8);
                if (serial.open(QIODevice::ReadOnly))
                {
                    serial.setDataTerminalReady(true);
                    serial.setRequestToSend(true);
                    if(serial.waitForReadyRead(2000))
                    {
                        QByteArray byteArray = serial.readAll();
                        parseData(byteArray);
                    }
                    serial.close();
                }
            }
        }
    }
}

void SerialConnection::parseData(QByteArray message)
{
    std::string s = message.toStdString();
    std::string delimiter = " ";

    std::vector<std::string> arguments;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        arguments.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    arguments.push_back(s);

    int id = -1;
    int value = -1;
    int tmp = -1;
    if (arguments.size() != 2)
        return;
    foreach (s, arguments) {
    std::cout << s << " ";
    }
    std::cout << "size " << arguments.size()<< std::endl;
    try {
        foreach (s, arguments) {
            tmp = std::stoi(s.substr(s.find("=") + 1));
            if (s.find("id") != std::string::npos)
                id = tmp;
            if (s.find("value") != std::string::npos)
                value = tmp;
        }

        if (tmp != -1)
        {
            std::cout << "emit " << id << " " << value << std::endl;
            emit volumeChanged(id, value);
        }
    } catch (std::invalid_argument err)
    {
        std::cerr << "received corrupted datas ... " << std::endl;
        std::cerr << tmp << " " << id << " " << value <<std::endl;
    }
}
