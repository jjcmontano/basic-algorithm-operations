; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSizedSplitterWnd
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ConverterXP.h"
LastPage=0

ClassCount=9
Class1=CConverterXPApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_MAINFRAME (English (U.S.))
Class2=CChildView
Class5=CDirTreeView
Class6=CFileListView
Class7=CResultView
Class8=zzz
Class9=CSizedSplitterWnd
Resource4=IDD_ABOUTBOX (English (U.S.))

[CLS:CConverterXPApp]
Type=0
HeaderFile=ConverterXP.h
ImplementationFile=ConverterXP.cpp
Filter=N

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=ConverterXP.cpp
ImplementationFile=ConverterXP.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_APP_ABOUT
CommandCount=13
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
CommandCount=13
Command4=ID_EDIT_UNDO
Command13=ID_PREV_PANE


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CDirTreeView]
Type=0
HeaderFile=DirTreeView.h
ImplementationFile=DirTreeView.cpp
BaseClass=CScrollView
Filter=C

[CLS:CFileListView]
Type=0
HeaderFile=FileListView.h
ImplementationFile=FileListView.cpp
BaseClass=CScrollView
Filter=C

[CLS:CResultView]
Type=0
HeaderFile=ResultView.h
ImplementationFile=ResultView.cpp
BaseClass=CScrollView
Filter=C

[CLS:zzz]
Type=0
HeaderFile=zzz.h
ImplementationFile=zzz.cpp
BaseClass=splitter
Filter=T

[CLS:CSizedSplitterWnd]
Type=0
HeaderFile=SizedSplitterWnd.h
ImplementationFile=SizedSplitterWnd.cpp
BaseClass=CSplitterWnd
Filter=C
VirtualFilter=pWC
LastObject=CSizedSplitterWnd

