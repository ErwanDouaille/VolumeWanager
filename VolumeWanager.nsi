############################################################################################
#      NSIS Installation Script created by NSIS Quick Setup Script Generator v1.09.18
#               Entirely Edited with NullSoft Scriptable Installation System                
#              by Vlasis K. Barkas aka Red Wine red_wine@freemail.gr Sep 2006               
############################################################################################

!define APP_NAME "VolumeWanager"
!define COMP_NAME "Douaille Erwan"
!define WEB_SITE "https://github.com/ErwanDouaille/VolumeWanager"
!define VERSION "1.0.0.0"
!define COPYRIGHT "Douaille Erwan © 2018"
!define DESCRIPTION "Application"
!define INSTALLER_NAME "C:\Users\douai\Desktop\Output\VolumeWanager\setup.exe"
!define MAIN_APP_EXE "VolumeWanager.exe"
!define INSTALL_TYPE "SetShellVarContext all"
!define REG_ROOT "HKLM"
!define REG_APP_PATH "Software\Microsoft\Windows\CurrentVersion\App Paths\${MAIN_APP_EXE}"
!define UNINSTALL_PATH "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"

!define REG_START_MENU "Start Menu Folder"

var SM_Folder

######################################################################

VIProductVersion  "${VERSION}"
VIAddVersionKey "ProductName"  "${APP_NAME}"
VIAddVersionKey "CompanyName"  "${COMP_NAME}"
VIAddVersionKey "LegalCopyright"  "${COPYRIGHT}"
VIAddVersionKey "FileDescription"  "${DESCRIPTION}"
VIAddVersionKey "FileVersion"  "${VERSION}"

######################################################################

SetCompressor ZLIB
Name "${APP_NAME}"
Caption "${APP_NAME}"
OutFile "${INSTALLER_NAME}"
BrandingText "${APP_NAME}"
XPStyle on
InstallDirRegKey "${REG_ROOT}" "${REG_APP_PATH}" ""
InstallDir "$PROGRAMFILES\VolumeWanager"

######################################################################

!include "MUI.nsh"

!define MUI_ABORTWARNING
!define MUI_UNABORTWARNING

!insertmacro MUI_PAGE_WELCOME

!ifdef LICENSE_TXT
!insertmacro MUI_PAGE_LICENSE "${LICENSE_TXT}"
!endif

!insertmacro MUI_PAGE_DIRECTORY

!ifdef REG_START_MENU
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "VolumeWanager"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${REG_ROOT}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${UNINSTALL_PATH}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${REG_START_MENU}"
!insertmacro MUI_PAGE_STARTMENU Application $SM_Folder
!endif

!insertmacro MUI_PAGE_INSTFILES

!define MUI_FINISHPAGE_RUN "$INSTDIR\${MAIN_APP_EXE}"
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM

!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

######################################################################
Section -Prerequisites
  SetOutPath $INSTDIR\Prerequisites
  MessageBox MB_YESNO "Install Arduino Drivers?" /SD IDYES IDNO endActiveSync
    File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\dpinst-amd64.exe"
    ExecWait "$INSTDIR\driver\dpinst-amd64.exe"
    Goto endActiveSync
  endActiveSync:
SectionEnd

######################################################################
Section -MainProgram
${INSTALL_TYPE}
SetOverwrite ifnewer
SetOutPath "$INSTDIR"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\libgcc_s_dw2-1.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\libstdc++-6.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\libwinpthread-1.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\Qt5Core.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\Qt5Gui.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\Qt5SerialPort.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\Qt5Widgets.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\settings.ini"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\VolumeWanager.exe"
SetOutPath "$INSTDIR\styles"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\styles\qwindowsvistastyle.dll"
SetOutPath "$INSTDIR\platforms"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\platforms\qwindows.dll"
SetOutPath "$INSTDIR\imageformats"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\imageformats\qjpeg.dll"
SetOutPath "$INSTDIR\driver"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\arduino.cat"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\arduino.inf"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\dpinst-amd64.exe"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\dpinst-x86.exe"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\README.txt"
SetOutPath "$INSTDIR\driver\x86"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\x86\libusb0.sys"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\x86\libusb0_x86.dll"
SetOutPath "$INSTDIR\driver\license\libusb0"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\license\libusb0\installer_license.txt"
SetOutPath "$INSTDIR\driver\ia64"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\ia64\libusb0.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\ia64\libusb0.sys"
SetOutPath "$INSTDIR\driver\FTDI USB Drivers"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\ftd2xx.h"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\ftdibus.cat"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\ftdibus.inf"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\ftdiport.cat"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\ftdiport.inf"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\LogoVerificationReport.pdf"
SetOutPath "$INSTDIR\driver\FTDI USB Drivers\Static\i386"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\Static\i386\ftd2xx.lib"
SetOutPath "$INSTDIR\driver\FTDI USB Drivers\Static\amd64"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\Static\amd64\ftd2xx.lib"
SetOutPath "$INSTDIR\driver\FTDI USB Drivers\i386"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\i386\ftbusui.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\i386\ftcserco.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\i386\ftd2xx.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\i386\ftd2xx.lib"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\i386\ftdibus.sys"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\i386\ftlang.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\i386\ftser2k.sys"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\i386\ftserui2.dll"
SetOutPath "$INSTDIR\driver\FTDI USB Drivers\amd64"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\amd64\ftbusui.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\amd64\ftcserco.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\amd64\ftd2xx.lib"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\amd64\ftd2xx64.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\amd64\ftdibus.sys"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\amd64\ftlang.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\amd64\ftser2k.sys"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\FTDI USB Drivers\amd64\ftserui2.dll"
SetOutPath "$INSTDIR\driver\amd64"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\amd64\libusb0.dll"
File "C:\Users\douai\Desktop\FINAL\VolumeWanager\driver\amd64\libusb0.sys"
SectionEnd

######################################################################

Section -Icons_Reg
SetOutPath "$INSTDIR"
WriteUninstaller "$INSTDIR\uninstall.exe"

WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Run" "VolumeWanager" "$INSTDIR\${MAIN_APP_EXE}"
WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "VolumeWanager" "$INSTDIR\${MAIN_APP_EXE}"

!ifdef REG_START_MENU
!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
CreateDirectory "$SMPROGRAMS\$SM_Folder"
CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$SMPROGRAMS\$SM_Folder\Uninstall ${APP_NAME}.lnk" "$INSTDIR\uninstall.exe"

!ifdef WEB_SITE
WriteIniStr "$INSTDIR\${APP_NAME} website.url" "InternetShortcut" "URL" "${WEB_SITE}"
CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME} Website.lnk" "$INSTDIR\${APP_NAME} website.url"
!endif
!insertmacro MUI_STARTMENU_WRITE_END
!endif

!ifndef REG_START_MENU
CreateDirectory "$SMPROGRAMS\VolumeWanager"
CreateShortCut "$SMPROGRAMS\VolumeWanager\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$SMPROGRAMS\VolumeWanager\Uninstall ${APP_NAME}.lnk" "$INSTDIR\uninstall.exe"

!ifdef WEB_SITE
WriteIniStr "$INSTDIR\${APP_NAME} website.url" "InternetShortcut" "URL" "${WEB_SITE}"
CreateShortCut "$SMPROGRAMS\VolumeWanager\${APP_NAME} Website.lnk" "$INSTDIR\${APP_NAME} website.url"
!endif
!endif

WriteRegStr ${REG_ROOT} "${REG_APP_PATH}" "" "$INSTDIR\${MAIN_APP_EXE}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayName" "${APP_NAME}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "UninstallString" "$INSTDIR\uninstall.exe"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayIcon" "$INSTDIR\${MAIN_APP_EXE}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayVersion" "${VERSION}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "Publisher" "${COMP_NAME}"

!ifdef WEB_SITE
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "URLInfoAbout" "${WEB_SITE}"
!endif
SectionEnd

######################################################################

Section Uninstall
${INSTALL_TYPE}
Delete "$INSTDIR\libgcc_s_dw2-1.dll"
Delete "$INSTDIR\libstdc++-6.dll"
Delete "$INSTDIR\libwinpthread-1.dll"
Delete "$INSTDIR\Qt5Core.dll"
Delete "$INSTDIR\Qt5Gui.dll"
Delete "$INSTDIR\Qt5SerialPort.dll"
Delete "$INSTDIR\Qt5Widgets.dll"
Delete "$INSTDIR\settings.ini"
Delete "$INSTDIR\VolumeWanager.exe"
Delete "$INSTDIR\styles\qwindowsvistastyle.dll"
Delete "$INSTDIR\platforms\qwindows.dll"
Delete "$INSTDIR\imageformats\qjpeg.dll"
Delete "$INSTDIR\driver\arduino.cat"
Delete "$INSTDIR\driver\arduino.inf"
Delete "$INSTDIR\driver\dpinst-amd64.exe"
Delete "$INSTDIR\driver\dpinst-x86.exe"
Delete "$INSTDIR\driver\README.txt"
Delete "$INSTDIR\driver\x86\libusb0.sys"
Delete "$INSTDIR\driver\x86\libusb0_x86.dll"
Delete "$INSTDIR\driver\license\libusb0\installer_license.txt"
Delete "$INSTDIR\driver\ia64\libusb0.dll"
Delete "$INSTDIR\driver\ia64\libusb0.sys"
Delete "$INSTDIR\driver\FTDI USB Drivers\ftd2xx.h"
Delete "$INSTDIR\driver\FTDI USB Drivers\ftdibus.cat"
Delete "$INSTDIR\driver\FTDI USB Drivers\ftdibus.inf"
Delete "$INSTDIR\driver\FTDI USB Drivers\ftdiport.cat"
Delete "$INSTDIR\driver\FTDI USB Drivers\ftdiport.inf"
Delete "$INSTDIR\driver\FTDI USB Drivers\LogoVerificationReport.pdf"
Delete "$INSTDIR\driver\FTDI USB Drivers\Static\i386\ftd2xx.lib"
Delete "$INSTDIR\driver\FTDI USB Drivers\Static\amd64\ftd2xx.lib"
Delete "$INSTDIR\driver\FTDI USB Drivers\i386\ftbusui.dll"
Delete "$INSTDIR\driver\FTDI USB Drivers\i386\ftcserco.dll"
Delete "$INSTDIR\driver\FTDI USB Drivers\i386\ftd2xx.dll"
Delete "$INSTDIR\driver\FTDI USB Drivers\i386\ftd2xx.lib"
Delete "$INSTDIR\driver\FTDI USB Drivers\i386\ftdibus.sys"
Delete "$INSTDIR\driver\FTDI USB Drivers\i386\ftlang.dll"
Delete "$INSTDIR\driver\FTDI USB Drivers\i386\ftser2k.sys"
Delete "$INSTDIR\driver\FTDI USB Drivers\i386\ftserui2.dll"
Delete "$INSTDIR\driver\FTDI USB Drivers\amd64\ftbusui.dll"
Delete "$INSTDIR\driver\FTDI USB Drivers\amd64\ftcserco.dll"
Delete "$INSTDIR\driver\FTDI USB Drivers\amd64\ftd2xx.lib"
Delete "$INSTDIR\driver\FTDI USB Drivers\amd64\ftd2xx64.dll"
Delete "$INSTDIR\driver\FTDI USB Drivers\amd64\ftdibus.sys"
Delete "$INSTDIR\driver\FTDI USB Drivers\amd64\ftlang.dll"
Delete "$INSTDIR\driver\FTDI USB Drivers\amd64\ftser2k.sys"
Delete "$INSTDIR\driver\FTDI USB Drivers\amd64\ftserui2.dll"
Delete "$INSTDIR\driver\amd64\libusb0.dll"
Delete "$INSTDIR\driver\amd64\libusb0.sys"
 
RmDir "$INSTDIR\driver\amd64"
RmDir "$INSTDIR\driver\FTDI USB Drivers\amd64"
RmDir "$INSTDIR\driver\FTDI USB Drivers\i386"
RmDir "$INSTDIR\driver\FTDI USB Drivers\Static\amd64"
RmDir "$INSTDIR\driver\FTDI USB Drivers\Static\i386"
RmDir "$INSTDIR\driver\FTDI USB Drivers"
RmDir "$INSTDIR\driver\ia64"
RmDir "$INSTDIR\driver\license\libusb0"
RmDir "$INSTDIR\driver\x86"
RmDir "$INSTDIR\driver"
RmDir "$INSTDIR\imageformats"
RmDir "$INSTDIR\platforms"
RmDir "$INSTDIR\styles"
 
Delete "$INSTDIR\uninstall.exe"
!ifdef WEB_SITE
Delete "$INSTDIR\${APP_NAME} website.url"
!endif

RmDir "$INSTDIR"

!ifdef REG_START_MENU
!insertmacro MUI_STARTMENU_GETFOLDER "Application" $SM_Folder
Delete "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk"
Delete "$SMPROGRAMS\$SM_Folder\Uninstall ${APP_NAME}.lnk"
!ifdef WEB_SITE
Delete "$SMPROGRAMS\$SM_Folder\${APP_NAME} Website.lnk"
!endif
Delete "$DESKTOP\${APP_NAME}.lnk"

RmDir "$SMPROGRAMS\$SM_Folder"
!endif

!ifndef REG_START_MENU
Delete "$SMPROGRAMS\VolumeWanager\${APP_NAME}.lnk"
Delete "$SMPROGRAMS\VolumeWanager\Uninstall ${APP_NAME}.lnk"
!ifdef WEB_SITE
Delete "$SMPROGRAMS\VolumeWanager\${APP_NAME} Website.lnk"
!endif
Delete "$DESKTOP\${APP_NAME}.lnk"

RmDir "$SMPROGRAMS\VolumeWanager"
!endif

DeleteRegKey ${REG_ROOT} "${REG_APP_PATH}"
DeleteRegKey ${REG_ROOT} "${UNINSTALL_PATH}"
SectionEnd

######################################################################

