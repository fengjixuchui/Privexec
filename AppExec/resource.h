///
#ifndef RESOURCE_H
#define RESOURCE_H
#include "..\include\version.h"
#define IDI_APPLICATION_ICON 101
#define IDD_APPLICATION_DIALOG 102

#define IDM_APPEXEC_ABOUT 1000
#define IDS_APPCONTAINER_NAME 1001
#define IDE_APPCONTAINER_NAME 1002
#define IDC_ENABLE_LPAC 1003
#define IDS_ENABLE_LPAC 1004
#define IDC_COMMAND_STATIC 1005
#define IDC_COMMAND_EDIT 1006
#define IDB_COMMAND_TARGET 1007
#define IDB_EXECUTE_BUTTON 1008
#define IDB_EXIT_BUTTON 1009
#define IDS_APPSTARTUP 1010
#define IDE_APPSTARTUP 1011
#define IDB_APPSTARTUP 1012
#define IDS_APPCONTAINER_ACL 1013
#define IDE_APPCONTAINER_ACL 1014
#define IDS_CAPABILITIES_LIST 1015 // recommended
#define IDL_APPCONTAINER_LISTVIEW 1016
#define IDE_APPEXEC_INFO 1017
#define IDS_HELPMSG 1018
#define IDL_APPEXEC_DESC 1019
#define IDM_APPTHEME 1020

#define IDB_APPX_IMPORT 1021

#define CS_LISTVIEW                                                            \
  WS_BORDER | WS_VSCROLL | WS_TABSTOP | LVS_REPORT | LVS_NOCOLUMNHEADER

#define CS_BASE                                                                \
  BS_PUSHBUTTON | BS_TEXT | BS_DEFPUSHBUTTON | BS_CHECKBOX | BS_AUTOCHECKBOX | \
      WS_CHILD | WS_OVERLAPPED | WS_VISIBLE

#define CS_EDIT                                                                \
  ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | ES_LEFT |   \
      WS_VSCROLL

// Next default values for new objects
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE 103
#define _APS_NEXT_COMMAND_VALUE 40001
#define _APS_NEXT_CONTROL_VALUE 1008
#define _APS_NEXT_SYMED_VALUE 101
#endif
#endif

#endif
