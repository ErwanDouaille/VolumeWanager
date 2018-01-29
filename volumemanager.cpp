#include "volumemanager.h"

VolumeManager::VolumeManager(QObject *parent) : QObject(parent)
{
    CoInitialize(NULL);
}

VolumeManager::~VolumeManager()
{
    CoUninitialize();
}

void VolumeManager::listSessions()
{
    HRESULT hr = S_OK;

    IMMDevice* pDevice = NULL;
    IMMDeviceEnumerator* pEnumerator = NULL;
    IAudioSessionControl* pSessionControl = NULL;
    IAudioSessionControl2* pSessionControl2 = NULL;
    IAudioSessionManager2* pSessionManager = NULL;

    // Create the device enumerator.
    hr = CoCreateInstance(
                __uuidof(MMDeviceEnumerator),
                NULL, CLSCTX_ALL,
                __uuidof(IMMDeviceEnumerator),
                (void**)&pEnumerator);

    // Get the default audio device.
    hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
    hr = pDevice->Activate(__uuidof(IAudioSessionManager2),
                           CLSCTX_ALL,
                           NULL, (void**)&pSessionManager);

    hr = pSessionManager->GetAudioSessionControl(0, FALSE, &pSessionControl);

    // Get the extended session control interface pointer.
    hr = pSessionControl->QueryInterface(__uuidof(IAudioSessionControl2), (void**) &pSessionControl2);

    // Check whether this is a system sound.
    hr = pSessionControl2->IsSystemSoundsSession();

    int cbSessionCount = 0;
    LPWSTR pswSession = NULL;

    IAudioSessionEnumerator* pSessionList = NULL;

    hr = pSessionManager->GetSessionEnumerator(&pSessionList);
    hr = pSessionList->GetCount(&cbSessionCount);
    std::cout << cbSessionCount << std::endl;
    for (int index = 0 ; index < cbSessionCount ; index++)
    {
        hr = pSessionList->GetSession(index, &pSessionControl);
        hr = pSessionControl->GetDisplayName(&pswSession);
        std::wcout << "Session Name: " <<  pswSession << std::endl;
        hr = pSessionControl->GetIconPath(&pswSession);
        std::wcout << "Icon path Name: " <<  pswSession << std::endl;
    }

    pSessionList->Release();
    pSessionManager->Release();
    pSessionControl2->Release();
    pSessionControl->Release();
    pEnumerator->Release();
    pDevice->Release();
}

void VolumeManager::changeMasterVolume(float value)
{
    HRESULT hr;
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    IAudioEndpointVolume *endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    hr = endpointVolume->SetMasterVolumeLevelScalar(value, NULL);
    endpointVolume->Release();
}
