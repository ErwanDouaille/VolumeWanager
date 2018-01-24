#ifndef VOLUMEMANAGER_H
#define VOLUMEMANAGER_H

#include <QObject>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audiopolicy.h>
#include <iostream>

class VolumeManager : public QObject
{
    Q_OBJECT
public:
    explicit VolumeManager(QObject *parent = nullptr);
    ~VolumeManager();

    void changeMasterVolume(float value);
    void enumerateSessions();
signals:

public slots:
};


#endif // VOLUMEMANAGER_H
