#ifndef VOLUMEMANAGER_H
#define VOLUMEMANAGER_H

#include <QObject>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audiopolicy.h>
#include <iostream>
#include <string>
#include <regex>

class VolumeManager : public QObject
{
    Q_OBJECT
public:
    explicit VolumeManager(QObject *parent = nullptr);
    ~VolumeManager();

    void listSessions();

    void setMasterVolume(float value);
    void setApplicationVolume(std::string applicationName, float value);
};


#endif // VOLUMEMANAGER_H
