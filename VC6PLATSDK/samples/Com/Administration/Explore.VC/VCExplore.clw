; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "VCExplore.h"

ClassCount=10
Class1=CVCExploreApp
Class2=CVCExploreDlg
Class3=CAboutDlg

ResourceCount=11
Resource1=IDD_INSTALL_APPLICATION
Resource2=IDR_MAINFRAME
Resource3=IDD_APP_UTILITY
Resource4=IDD_VCEXPLORE
Resource5=IDD_ABOUTBOX
Resource6=IDD_EXPORT_APPLICATION
Resource7=IDD_UTILITIES
Resource8=IDD_CONNECT
Resource9=IDD_INSTALL_COMPONENT
Resource10=IDD_IMPORT_COMPONENT
Class4=CAppUtilDlg
Class5=CConnectDlg
Class6=CAppExportDlg
Class7=CCompImportDlg
Class8=CAppInstallDlg
Class9=CCompInstallDlg
Class10=CUtilitiesDlg
Resource11=IDR_TOOLBAR_MAIN

[CLS:CVCExploreApp]
Type=0
HeaderFile=VCExplore.h
ImplementationFile=VCExplore.cpp
Filter=N

[CLS:CVCExploreDlg]
Type=0
HeaderFile=VCExploreDlg.h
ImplementationFile=VCExploreDlg.cpp
Filter=D
LastObject=CVCExploreDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=VCExploreDlg.h
ImplementationFile=VCExploreDlg.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_APPLICATION_ICON,static,1342177539
Control2=IDC_APPLICATION_TITLE,static,1342308480
Control3=IDC_APPLICATION_COPYRIGHT,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_APPLICATION_VERSION,static,1342308352

[DLG:IDD_EXPORT_APPLICATION]
Type=1
Class=CAppExportDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_FRAME_EXPORT_CLIENT_ONLY,button,1342177287
Control4=IDC_RADIO_DO_NOT_EXPORT_USERS,button,1342177289
Control5=IDC_RADIO_EXPORT_USERS,button,1342177289
Control6=IDC_RADIO_EXPORT_CLIENTS,button,1342177289
Control7=IDC_CHECK_OVERWRITE_FILES,button,1342242819
Control8=IDC_LABEL_APPLICATION_ID,static,1342308352
Control9=IDC_EDIT_APPLICATION_ID,edit,1350631552
Control10=IDC_LABEL_EXPORT_PATH,static,1342308352
Control11=IDC_EDIT_EXPORT_PATH,edit,1350631552
Control12=IDC_BUTTON_EXPORT_PATH_SEARCH,button,1342242816

[DLG:IDD_INSTALL_APPLICATION]
Type=1
Class=CAppInstallDlg
ControlCount=19
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_FRAME_INSTALL_OPTIONS,button,1342177287
Control4=IDC_RADIO_INSTALL_WITHOUT_USERS,button,1342177289
Control5=IDC_RADIO_INSTALL_WITH_USERS,button,1342177289
Control6=IDC_CHECK_OVERWRITE_FILES,button,1342242819
Control7=IDC_LABEL_APPLICATION_FILE,static,1342308352
Control8=IDC_EDIT_APPLICATION_FILE,edit,1350631552
Control9=IDC_LABEL_INSTALL_DIRECTORY,static,1342308352
Control10=IDC_EDIT_INSTALL_DIRECTORY,edit,1350631552
Control11=IDC_BUTTON_INSTALL_DIRECTORY_SEARCH,button,1342242816
Control12=IDC_BUTTON_APPLICATION_FILE_SEARCH,button,1342242816
Control13=IDC_CHECK_REMOTE_SERVER_INSTALL,button,1342242819
Control14=IDC_LABEL_REMOTE_SERVER_NAME,static,1342308352
Control15=IDC_EDIT_REMOTE_SERVER_NAME,edit,1350631552
Control16=IDC_LABEL_UID,static,1342308352
Control17=IDC_EDIT_UID,edit,1350631552
Control18=IDC_LABEL_PWD,static,1342308352
Control19=IDC_EDIT_PWD,edit,1350631584

[DLG:IDD_VCEXPLORE]
Type=1
Class=CVCExploreDlg
ControlCount=17
Control1=IDC_FRAME_CATALOG_INFO,button,1342177287
Control2=IDC_LABEL_COMPUTER_NAME_DESC,static,1342308352
Control3=IDC_LABEL_COMPUTER_NAME_VALUE,static,1350701057
Control4=IDC_LABEL_COLLECTION_NAME_DESC,static,1342308352
Control5=IDC_LABEL_COLLECTION_NAME_VALUE,static,1350701057
Control6=IDC_FRAME_RELATED_COLLECTIONS,button,1342177287
Control7=IDC_LIST_RELATED_COLLECTIONS,listbox,1352728835
Control8=IDC_FRAME_PREVIOUS_COLLECTIONS,button,1342177287
Control9=IDC_LIST_PARENT_COLLECTIONS,listbox,1352728833
Control10=IDC_FRAME_OBJECTS_AND_PROP_INFO,button,1342177287
Control11=IDC_LABEL_OBJECTS_DESC,static,1342308352
Control12=IDC_LABEL_PROPERTIES_DESC2,static,1342308352
Control13=IDC_LIST_OBJECTS,listbox,1352728833
Control14=IDC_LIST_PROPERTIES,listbox,1352728833
Control15=IDC_LABEL_PROPERTY_VALUE_DESC,static,1342308352
Control16=IDC_EDIT_PROPERTY_VALUE,edit,1350631552
Control17=IDC_BUTTON_SET_PROPERTY,button,1342242816

[DLG:IDD_INSTALL_COMPONENT]
Type=1
Class=CCompInstallDlg
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LABEL_APPLICATION,static,1342308352
Control4=IDC_COMBO_APPLICATION,combobox,1344340227
Control5=IDC_LABEL_COMPONENT,static,1342308352
Control6=IDC_EDIT_COMPONENT,edit,1350631552
Control7=IDC_BUTTON_COMPONENT_SEARCH,button,1342242816
Control8=IDC_LABEL_TYPE_LIBRARY,static,1342308352
Control9=IDC_EDIT_TYPE_LIBRARY,edit,1350631552
Control10=IDC_BUTTON_TYPE_LIBRARY,button,1342242816
Control11=IDC_LABEL_PROXY_STUB_DLL,static,1342308352
Control12=IDC_EDIT_PROXY_STUB_DLL,edit,1350631552
Control13=IDC_BUTTON_PROXY_STUB_DLL,button,1342242816

[DLG:IDD_IMPORT_COMPONENT]
Type=1
Class=CCompImportDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_FRAME_IMPORT_BY,button,1342177287
Control4=IDC_RADIO_PROG_ID,button,1342177289
Control5=IDC_RADIO_CLSID,button,1342177289
Control6=IDC_LABEL_APPLICATION,static,1342308352
Control7=IDC_COMBO_APPLICATION,combobox,1344340227
Control8=IDC_LABEL_COMPONENT,static,1342308352
Control9=IDC_EDIT_COMPONENT,edit,1350631552

[DLG:IDD_CONNECT]
Type=1
Class=CConnectDlg
ControlCount=6
Control1=IDOK,button,1342373889
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342308359
Control4=IDC_RADIO_THIS_COMPUTER,button,1342177289
Control5=IDC_RADIO_REMOTE_COMPUTER,button,1342177289
Control6=IDC_EDIT_REMOTE_COMPUTER_NAME,edit,1350631552

[DLG:IDD_APP_UTILITY]
Type=1
Class=CAppUtilDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LABEL_APPLICATION_ID,static,1342308352
Control4=IDC_EDIT_APPLICATION_ID_VALUE,edit,1350631552
Control5=IDC_BUTTON_APPLICATON_ID_SEARCH,button,1342242816

[DLG:IDD_UTILITIES]
Type=1
Class=CUtilitiesDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_FRAME_UTILITY_OPTIONS,button,1342177287
Control4=IDC_RADIO_START,button,1342177289
Control5=IDC_RADIO_STOP,button,1342177289
Control6=IDC_RADIO_REFRESH,button,1342177289

[TB:IDR_TOOLBAR_MAIN]
Type=1
Class=?
Command1=ID_TBTN_CONNECT
Command2=ID_TBTN_REFRESH
Command3=ID_TBTN_NEW
Command4=ID_TBTN_SAVE
Command5=ID_TBTN_DELETE
Command6=ID_TBTN_START_APP
Command7=ID_TBTN_STOP_APP
Command8=ID_TBTN_INSTALL_APP
Command9=ID_TBTN_EXPORT_APP
Command10=ID_TBTN_INSTALL_COMPONENT
Command11=ID_TBTN_IMPORT_COMPONENT
Command12=ID_TBTN_UTILITY
Command13=ID_TBTN_ABOUT
CommandCount=13

[CLS:CAppUtilDlg]
Type=0
HeaderFile=AppUtilDlg.h
ImplementationFile=AppUtilDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAppUtilDlg

[CLS:CConnectDlg]
Type=0
HeaderFile=ConnectDlg.h
ImplementationFile=ConnectDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_REMOTE_COMPUTER_NAME

[CLS:CAppExportDlg]
Type=0
HeaderFile=AppExportDlg.h
ImplementationFile=AppExportDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAppExportDlg

[CLS:CAppInstallDlg]
Type=0
HeaderFile=AppInstallDlg.h
ImplementationFile=AppInstallDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAppInstallDlg
VirtualFilter=dWC

[CLS:CCompInstallDlg]
Type=0
HeaderFile=CompInstallDlg.h
ImplementationFile=CompInstallDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[CLS:CUtilitiesDlg]
Type=0
HeaderFile=UtilitiesDlg.h
ImplementationFile=UtilitiesDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CUtilitiesDlg
VirtualFilter=dWC

[CLS:CCompImportDlg]
Type=0
HeaderFile=compimportdlg.h
ImplementationFile=compimportdlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCompImportDlg

