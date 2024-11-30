# Microsoft Developer Studio Project File - Name="libncl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libncl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libncl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libncl.mak" CFG="libncl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libncl - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libncl - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libncl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libncl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "libncl - Win32 Release"
# Name "libncl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\nxsassumptionsblock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsblock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\nxscharactersblock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsdatablock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsdiscretedatum.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsdiscretematrix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsdistancedatum.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsdistancesblock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsexception.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsreader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\nxssetreader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsstring.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\nxstaxablock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\nxstoken.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\nxstreesblock.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\ncl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsassumptionsblock.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsblock.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxscharactersblock.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsdatablock.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsdefs.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsdiscretedatum.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsdiscretematrix.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsdistancedatum.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsdistancesblock.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsexception.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsindent.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsreader.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxssetreader.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxsstring.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxstaxablock.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxstoken.h
# End Source File
# Begin Source File

SOURCE=..\..\src\nxstreesblock.h
# End Source File
# End Group
# End Target
# End Project
