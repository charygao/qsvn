; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppId=QSvn
AppName=QSvn
AppVerName=QSvn {#QSvnVersionString}
AppPublisher=Andreas Richter
AppPublisherURL=http://www.anrichter.net/projects/qsvn
AppSupportURL=http://www.anrichter.net/projects/qsvn
AppUpdatesURL=http://www.anrichter.net/projects/qsvn
DefaultDirName={pf}\QSvn
DefaultGroupName=QSvn
AllowNoIcons=yes
LicenseFile={#QSvnSourceDir}\licenses\COPYING
InfoBeforeFile={#QSvnSourceDir}\..\README
InfoAfterFile={#QSvnSourceDir}\..\ChangeLog
OutputDir={#QSvnBinDir}\..\setup\
OutputBaseFilename=qsvn-{#QSvnVersionNumber}
Compression=lzma
SolidCompression=yes
VersionInfoCompany=Andreas Richter
VersionInfoCopyright=2004 - 2008
VersionInfoDescription=QSvn Installation
VersionInfoVersion={#QSvnVersionNumber}

WizardImageFile=ImageFile.bmp
WizardSmallImageFile=SmallImageFile.bmp

[Tasks]
Name: desktopicon; Description: {cm:CreateDesktopIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked
Name: quicklaunchicon; Description: {cm:CreateQuickLaunchIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked

[Files]
;ProgramFiles
Source: {#QSvnBinDir}\qsvn.exe; DestDir: {app}; Flags: ignoreversion
Source: {#QSvnBinDir}\qsvn.exe.manifest; DestDir: {app}; Flags: ignoreversion
Source: {#QSvnBinDir}\svnqt.dll; DestDir: {app}; Flags: ignoreversion
;TextFiles
Source: {#QSvnSourceDir}\..\README; DestDir: {app}; Flags: ignoreversion
Source: {#QSvnSourceDir}\..\ChangeLog; DestDir: {app}; Flags: ignoreversion
Source: {#QSvnSourceDir}\licenses\COPYING; DestDir: {app}\licenses; Flags: ignoreversion
Source: {#QSvnSourceDir}\licenses\APR.license; DestDir: {app}\licenses; Flags: ignoreversion
Source: {#QSvnSourceDir}\licenses\BerkeleyDB.license; DestDir: {app}\licenses; Flags: ignoreversion
Source: {#QSvnSourceDir}\licenses\OpenSSL.license; DestDir: {app}\licenses; Flags: ignoreversion
Source: {#QSvnSourceDir}\licenses\Subversion.license; DestDir: {app}\licenses; Flags: ignoreversion
;QtFiles
Source: {#QtBinaryDir}\QtCore4.dll; DestDir: {app}; Flags: ignoreversion
Source: {#QtBinaryDir}\QtGui4.dll; DestDir: {app}; Flags: ignoreversion
Source: {#QtBinaryDir}\QtSql4.dll; DestDir: {app}; Flags: ignoreversion
Source: {#QtBinaryDir}\QtSvg4.dll; DestDir: {app}; Flags: ignoreversion
;QtPlugins
Source: {#QtPluginsDir}\imageformats\qsvg4.dll; DestDir: {app}\imageformats; Flags: ignoreversion
;SubversionFiles
Source: {#SvnBinDir}\intl3_svn.dll; DestDir: {app}; Flags: ignoreversion
Source: {#SvnBinDir}\libapr-1.dll; DestDir: {app}; Flags: ignoreversion
Source: {#SvnBinDir}\libapriconv-1.dll; DestDir: {app}; Flags: ignoreversion
Source: {#SvnBinDir}\libaprutil-1.dll; DestDir: {app}; Flags: ignoreversion
Source: {#SvnBinDir}\libdb44.dll; DestDir: {app}; Flags: ignoreversion
Source: {#SvnBinDir}\libeay32.dll; DestDir: {app}; Flags: ignoreversion
Source: {#SvnBinDir}\libsasl.dll; DestDir: {app}; Flags: ignoreversion
Source: {#SvnBinDir}\libsvn_client-1.dll; DestDir: {app}; Flags: ignoreversion
Source: {#SvnBinDir}\libsvn_delta-1.dll; DestDir: {app}; Flags: ignoreversion
Source: {#SvnBinDir}\libsvn_diff-1.dll; DestDir: {app}; Flags: ignoreversion
Source: {#SvnBinDir}\libsvn_fs-1.dll; DestDir: {app}; Flags: ignoreversion
Source: {#SvnBinDir}\libsvn_ra-1.dll; DestDir: {app}; Flags: ignoreversion
Source: {#SvnBinDir}\libsvn_repos-1.dll; DestDir: {app}; Flags: ignoreversion
Source: {#SvnBinDir}\libsvn_subr-1.dll; DestDir: {app}; Flags: ignoreversion
Source: {#SvnBinDir}\libsvn_wc-1.dll; DestDir: {app}; Flags: ignoreversion
Source: {#SvnBinDir}\ssleay32.dll; DestDir: {app}; Flags: ignoreversion
;MSVC-Redistributables
Source: {#QSvnSourceDir}\setup\Microsoft.VC90.CRT\*.*; DestDir: {app}\Microsoft.VC90.CRT; Flags: ignoreversion
Source: {#QSvnSourceDir}\setup\Microsoft.VC90.CRT\*.*; DestDir: {app}\imageformats\Microsoft.VC90.CRT; Flags: ignoreversion

[INI]
Filename: {app}\qsvn.url; Section: InternetShortcut; Key: URL; String: http://www.anrichter.net/projects/qsvn

[Icons]
Name: {group}\QSvn; Filename: {app}\qsvn.exe
Name: {group}\{cm:ProgramOnTheWeb,QSvn}; Filename: {app}\qsvn.url
Name: {group}\{cm:UninstallProgram,QSvn}; Filename: {uninstallexe}
Name: {userdesktop}\QSvn; Filename: {app}\qsvn.exe; Tasks: desktopicon
Name: {userappdata}\Microsoft\Internet Explorer\Quick Launch\QSvn; Filename: {app}\qsvn.exe; Tasks: quicklaunchicon

[Run]
Filename: {app}\qsvn.exe; Description: {cm:LaunchProgram,QSvn}; Flags: nowait postinstall skipifsilent

[UninstallDelete]
Type: files; Name: {app}\qsvn.url
