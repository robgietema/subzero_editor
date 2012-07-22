# Microsoft Developer Studio Project File - Name="l3g0_conv" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=l3g0_conv - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "l3g0_conv.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "l3g0_conv.mak" CFG="l3g0_conv - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "l3g0_conv - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "l3g0_conv - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "l3g0_conv - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "l3g0_conv - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "l3g0_conv___Win32_Debug"
# PROP BASE Intermediate_Dir "l3g0_conv___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "l3g0_conv___Win32_Debug"
# PROP Intermediate_Dir "l3g0_conv___Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 gdi32.lib user32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "l3g0_conv - Win32 Release"
# Name "l3g0_conv - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "3ds"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\3ds\camera.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\color_24.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\color_f.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\face_array.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\face_smoothing.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\file_3ds.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\float_percentage.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\int_percentage.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\light.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\light_off.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\lin_color_24.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\lin_color_f.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\local_axis.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\m3d_version.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\m3dmagic.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\master_scale.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_ambient.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_bump_display_per.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_bump_map.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_diffuse.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_entry.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_map_blur.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_map_filename.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_map_options.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_map_rotation.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_name.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_reflect_blur.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_self_illum.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_shading.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_shin_strength.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_shininess.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_specular.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_tex1_map.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_trans_falloff.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_transparency.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mat_wire_thickness.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mdata.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\mesh_version.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\msh_mat_group.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\n_tri_object.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\named_object.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\point_array.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\spotlight.cpp
# End Source File
# Begin Source File

SOURCE=.\src\3ds\tex_verts.cpp
# End Source File
# End Group
# Begin Group "bricklib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\bricklib\lg_bricklib.cpp
# End Source File
# Begin Source File

SOURCE=.\src\bricklib\lg_bricklibentry.cpp
# End Source File
# End Group
# Begin Group "objectlib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\objectlib\lg_brick.cpp
# End Source File
# Begin Source File

SOURCE=.\src\objectlib\lg_object.cpp
# End Source File
# Begin Source File

SOURCE=.\src\objectlib\lg_objectgroup.cpp
# End Source File
# Begin Source File

SOURCE=.\src\objectlib\lg_objectlib.cpp
# End Source File
# End Group
# Begin Group "scene"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\scene\lg_objectinstance.cpp
# End Source File
# Begin Source File

SOURCE=.\src\scene\lg_scene.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\ARB_Multisample.cpp
# End Source File
# Begin Source File

SOURCE=.\src\l3g0_conv.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lg_buffer_functions.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lg_color.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lg_font2d.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lg_image.cpp
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
# Begin Group "3ds_include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\3ds\3ds.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\camera.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\chunks.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\color_24.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\color_f.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\face_array.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\face_smoothing.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\file_3ds.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\float_percentage.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\int_percentage.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\light.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\light_off.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\lin_color_24.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\lin_color_f.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\local_axis.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\m3d_version.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\m3dmagic.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\master_scale.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_ambient.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_bump_display_per.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_bump_map.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_diffuse.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_entry.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_map_blur.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_map_filename.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_map_options.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_map_rotation.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_name.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_reflect_blur.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_self_illum.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_shading.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_shin_strength.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_shininess.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_specular.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_tex1_map.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_trans_falloff.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_transperancy.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mat_wire_thickness.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mdata.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\mesh_version.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\msh_mat_group.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\n_tri_object.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\named_object.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\point_array.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\spotlight.h
# End Source File
# Begin Source File

SOURCE=.\include\3ds\tex_verts.h
# End Source File
# End Group
# Begin Group "bricklib_include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\bricklib\lg_bricklib.h
# End Source File
# Begin Source File

SOURCE=.\include\bricklib\lg_bricklibentry.h
# End Source File
# End Group
# Begin Group "objectlib_include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\objectlib\lg_brick.h
# End Source File
# Begin Source File

SOURCE=.\include\objectlib\lg_object.h
# End Source File
# Begin Source File

SOURCE=.\include\objectlib\lg_objectgroup.h
# End Source File
# Begin Source File

SOURCE=.\include\objectlib\lg_objectlib.h
# End Source File
# End Group
# Begin Group "scene_include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\scene\lg_objectinstance.h
# End Source File
# Begin Source File

SOURCE=.\include\scene\lg_scene.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\include\ARB_Multisample.h
# End Source File
# Begin Source File

SOURCE=.\include\l3g0_conv.h
# End Source File
# Begin Source File

SOURCE=.\include\lg_buffer_functions.h
# End Source File
# Begin Source File

SOURCE=.\include\lg_color.h
# End Source File
# Begin Source File

SOURCE=.\include\lg_font2d.h
# End Source File
# Begin Source File

SOURCE=.\include\lg_image.h
# End Source File
# Begin Source File

SOURCE=.\include\wglext.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
