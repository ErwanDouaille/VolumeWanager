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
    LPWSTR pswSession = NULL;
    std::wstring identifier;
    IMMDevice* pDevice = NULL;
    ISimpleAudioVolume *pVolume = NULL;
    IMMDeviceEnumerator* pEnumerator = NULL;
    IAudioSessionEnumerator *pSessionList = NULL;
    IAudioSessionControl *pSessionControl = NULL;
    IAudioSessionControl2 *pSessionControl2 = NULL;
    IAudioSessionManager2* pSessionManager = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);

    hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
    hr = pDevice->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, NULL, (void**)&pSessionManager);

    int cbSessionCount = 0;

    hr = pSessionManager->GetSessionEnumerator(&pSessionList);
    hr = pSessionList->GetCount(&cbSessionCount);

    for (int index = 0; index < cbSessionCount; index++)
    {
        hr = pSessionList->GetSession(index, &pSessionControl);
        hr = pSessionControl->QueryInterface(__uuidof(IAudioSessionControl2), (void**) &pSessionControl2);

        if (pSessionControl2->IsSystemSoundsSession()) {
            hr = pSessionControl2->GetSessionIdentifier(&pswSession);
            identifier = std::wstring(pswSession);
            hr = pSessionControl2->QueryInterface(__uuidof(ISimpleAudioVolume), (void**)&pVolume);
            std::wcout << identifier << std::endl;
        }
    }
}

void VolumeManager::setApplicationVolume(std::string applicationName, float value)
{
    if (applicationName.compare("master") == 0)
    {
        setMasterVolume(value);
    } else
    {

    }
}

void VolumeManager::setMasterVolume(float value)
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
