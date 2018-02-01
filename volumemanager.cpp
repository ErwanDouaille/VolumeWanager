#include "volumemanager.h"

VolumeManager::VolumeManager(QObject *parent) : QObject(parent)
{
    CoInitialize(NULL);
}

VolumeManager::~VolumeManager()
{
    CoUninitialize();
}


std::vector<std::string> VolumeManager::getAvailableSessions()
{
    std::vector<std::string> list;
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

            std::string wholePath( identifier.begin(), identifier.end() );
            std::regex e(".*\\\\(.*)\\..*$");
            std::smatch sm;
            std::regex_match(wholePath.cbegin(), wholePath.cend(), sm, e);
            list.push_back(sm[1]);
            std::cout << sm[1] << std::endl;
        }
    }
    pDevice->Release();
    pVolume->Release();
    pEnumerator->Release();
    pSessionList->Release();
    pSessionControl->Release();
    pSessionControl2->Release();
    pSessionManager->Release();
    return std::vector<std::string>();
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
    defaultDevice->Release();
    deviceEnumerator->Release();
}
