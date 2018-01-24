#include <QApplication>
#include <QMessageBox>

#include <windows.h>
#include <iostream>

#include "mainwindow.h"
#include "volumemanager.h"

int testHID()
{
    UINT nDevices = 0;
    int ret;
    GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST));

    if (nDevices < 1)
    {
        std::cerr << "No device connected" << std::endl;
        return 0;
    }

    PRAWINPUTDEVICELIST pRawInputDeviceList = new RAWINPUTDEVICELIST[sizeof(RAWINPUTDEVICELIST) * nDevices];
    if (pRawInputDeviceList == NULL)
    {
        std::cerr << "Could not allocated device list" << std::endl;
        return 0;
    }

    ret = GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST));
    if (ret < 0)
    {
        std::cerr << "Cannot access device list" << std::endl;
        delete pRawInputDeviceList;
        return 0;
    }

    for (UINT i = 0; i < nDevices; i++)
    {
        UINT nBufferSize = 0;
        ret = GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, NULL, &nBufferSize);
        if (ret < 0)
        {
            std::cerr << "Cannot access to device name size" << std::endl;
            continue;
        }

        WCHAR* wcDeviceName = new WCHAR[nBufferSize + 1];
        if (wcDeviceName == NULL)
        {
            std::cerr << "Bad allocation for device name" << std::endl;
            continue;
        }

        ret = GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, wcDeviceName, &nBufferSize);
        if (ret < 0)
        {
            std::cerr << "Cannot access to device name" << std::endl;
            delete wcDeviceName;
            continue;
        }

        RID_DEVICE_INFO rdiDeviceInfo;
        rdiDeviceInfo.cbSize = sizeof(RID_DEVICE_INFO);
        nBufferSize = rdiDeviceInfo.cbSize;

        // Get Device Info
        ret = GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICEINFO, &rdiDeviceInfo, &nBufferSize);
        if (ret < 0)
        {
            std::cerr << "Cannot read device information" << std::endl;
            continue;
        }

        if (rdiDeviceInfo.dwType == RIM_TYPEHID)
        {
            std::cout << "------------------------------------" << std::endl;
            std::cout << "Device : " << i + 1 << std::endl;
            std::cout << "Device Name: " << wcDeviceName << std::endl;
            std::cout << "Vendor Id:" << rdiDeviceInfo.hid.dwVendorId << std::endl;
            std::cout << "Product Id:" << rdiDeviceInfo.hid.dwProductId << std::endl;
            std::cout << "Version No:" << rdiDeviceInfo.hid.dwVersionNumber << std::endl;
            std::cout << "Usage for the device: " << rdiDeviceInfo.hid.usUsage << std::endl;
            std::cout << "Usage Page for the device: " << rdiDeviceInfo.hid.usUsagePage << std::endl;
            std::cout << std::endl;
        }

        delete wcDeviceName;
    }
    delete pRawInputDeviceList;
}

int main(int argc, char *argv[])
{
    testHID();
    VolumeManager * vm = new VolumeManager();
    vm->changeMasterVolume(0.3);

    return 0;
    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"), QObject::tr("I couldn't detect any system tray on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    MainWindow window;
    window.show();
    return app.exec();
}
