# Microsoft Developer Studio Project File - Name="EMCommon_Library" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=EMCommon_Library - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EMCommon_Library.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EMCommon_Library.mak" CFG="EMCommon_Library - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EMCommon_Library - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EMCommon_Library - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/EMCommon_Library", FLGAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "EMCommon_Library - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "EMCommon_Library___Win32_Release"
# PROP BASE Intermediate_Dir "EMCommon_Library___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "EMCommon_Library___Win32_Release"
# PROP Intermediate_Dir "EMCommon_Library___Win32_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EMCOMMON_LIBRARY_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EMCOMMON_LIBRARY_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 .\lib\EMDebug_Library.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /pdb:none /machine:I386 /out:"\SourceSafe\ReleaseBuild\EMCommon_Library.dll" /implib:"\SourceSafe\ReleaseBuild\lib\EMCommon_Library.lib"

!ELSEIF  "$(CFG)" == "EMCommon_Library - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "EMCommon_Library___Win32_Debug"
# PROP BASE Intermediate_Dir "EMCommon_Library___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "EMCommon_Library_files"
# PROP Intermediate_Dir "EMCommon_Library_files"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EMCOMMON_LIBRARY_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EMCOMMON_LIBRARY_EXPORTS" /D "DEBUG_VERSION" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 .\lib\EMDebug_Library.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /out:"EMCommon_Library.dll" /implib:"lib/EMCommon_Library.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "EMCommon_Library - Win32 Release"
# Name "EMCommon_Library - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Components\EMApplication.cpp
# End Source File
# Begin Source File

SOURCE=.\Framework\Gui\EMBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\Components\EMException.cpp
# End Source File
# Begin Source File

SOURCE=.\Components\EMExceptionHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\Framework\EMListener.cpp
# End Source File
# Begin Source File

SOURCE=.\Framework\EMListenerRepository.cpp
# End Source File
# Begin Source File

SOURCE=.\Components\Gui\EMRect.cpp
# End Source File
# Begin Source File

SOURCE=.\Framework\EMSemaphore.cpp
# End Source File
# Begin Source File

SOURCE=.\Framework\EMThread.cpp
# End Source File
# Begin Source File

SOURCE=.\Framework\EMThreadListener.cpp
# End Source File
# Begin Source File

SOURCE=.\Framework\Gui\EMWinBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\Framework\EMWinMessagePump.cpp
# End Source File
# Begin Source File

SOURCE=.\Framework\EMWinSemaphore.cpp
# End Source File
# Begin Source File

SOURCE=.\Framework\EMWinThread.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Components\EMApplication.h
# End Source File
# Begin Source File

SOURCE=.\Framework\Gui\EMBitmap.h
# End Source File
# Begin Source File

SOURCE=.\Components\EMException.h
# End Source File
# Begin Source File

SOURCE=.\Components\EMExceptionHandler.h
# End Source File
# Begin Source File

SOURCE=.\Framework\EMListener.h
# End Source File
# Begin Source File

SOURCE=.\Framework\EMListenerRepository.h
# End Source File
# Begin Source File

SOURCE=.\Components\Gui\EMRect.h
# End Source File
# Begin Source File

SOURCE=.\Framework\EMSemaphore.h
# End Source File
# Begin Source File

SOURCE=.\Framework\EMThread.h
# End Source File
# Begin Source File

SOURCE=.\Framework\EMThreadListener.h
# End Source File
# Begin Source File

SOURCE=.\Framework\Gui\EMWinBitmap.h
# End Source File
# Begin Source File

SOURCE=.\Framework\EMWinMessagePump.h
# End Source File
# Begin Source File

SOURCE=.\Framework\EMWinSemaphore.h
# End Source File
# Begin Source File

SOURCE=.\Framework\EMWinThread.h
# End Source File
# End Group
# Begin Group "lib"

# PROP Default_Filter "*.lib"
# Begin Source File

SOURCE=.\lib\EMCommon_Library.lib
# End Source File
# End Group
# Begin Source File

SOURCE=.\EMCommon_Library.dll
# End Source File
# End Target
# End Project
