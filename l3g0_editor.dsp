# Microsoft Developer Studio Project File - Name="l3g0_editor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=l3g0_editor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "l3g0_editor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "l3g0_editor.mak" CFG="l3g0_editor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "l3g0_editor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "l3g0_editor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "l3g0_editor - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "l3g0_editor - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "l3g0_editor___Win32_Debug"
# PROP BASE Intermediate_Dir "l3g0_editor___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "l3g0_editor___Win32_Debug"
# PROP Intermediate_Dir "l3g0_editor___Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 gdi32.lib user32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "l3g0_editor - Win32 Release"
# Name "l3g0_editor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "level"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\level\lg_level.cpp
# End Source File
# Begin Source File

SOURCE=.\src\level\lg_object.cpp
# End Source File
# Begin Source File

SOURCE=.\src\level\lg_point.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\ARB_Multisample.cpp
# End Source File
# Begin Source File

SOURCE=.\src\l3g0_editor.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lg_buffer_functions.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lg_color.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lg_engine.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lg_font2d.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lg_image.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lg_math.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lg_opengl.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lg_print.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "level_include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\level\lg_level.h
# End Source File
# Begin Source File

SOURCE=.\include\level\lg_object.h
# End Source File
# Begin Source File

SOURCE=.\include\level\lg_point.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\include\ARB_Multisample.h
# End Source File
# Begin Source File

SOURCE=.\include\glext.h
# End Source File
# Begin Source File

SOURCE=.\include\lg_buffer_functions.h
# End Source File
# Begin Source File

SOURCE=.\include\lg_color.h
# End Source File
# Begin Source File

SOURCE=.\include\lg_datatypes.h
# End Source File
# Begin Source File

SOURCE=.\include\lg_engine.h
# End Source File
# Begin Source File

SOURCE=.\include\lg_font2d.h
# End Source File
# Begin Source File

SOURCE=.\include\lg_image.h
# End Source File
# Begin Source File

SOURCE=.\include\lg_math.h
# End Source File
# Begin Source File

SOURCE=.\include\lg_opengl.h
# End Source File
# Begin Source File

SOURCE=.\include\lg_print.h
# End Source File
# Begin Source File

SOURCE=.\include\wglext.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
