#ifndef VOLUMEMANAGER_H
#define VOLUMEMANAGER_H

#include <QObject>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audiopolicy.h>
#include <iostream>
#include <string>
#include <regex>
#include <vector>

class VolumeManager : public QObject
{
    Q_OBJECT
public:
    explicit VolumeManager(QObject *parent = nullptr);
    ~VolumeManager();

    std::vector<std::string> getAvailableSessions();

    void setMasterVolume(float value);
    void setApplicationVolume(std::string applicationName, float value);

public slots:
    void appVolumeChanged(std::string appName, int value);
};


#endif // VOLUMEMANAGER_H
