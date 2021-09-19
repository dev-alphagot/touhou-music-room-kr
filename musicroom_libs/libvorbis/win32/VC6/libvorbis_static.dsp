# Microsoft Developer Studio Project File - Name="libvorbis_static" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libvorbis_static - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "libvorbis_static.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "libvorbis_static.mak" CFG="libvorbis_static - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "libvorbis_static - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "libvorbis_static - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libvorbis_static - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "libvorbis_static___Win32_Release"
# PROP BASE Intermediate_Dir "libvorbis_static___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /Gz /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "STDCALL" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"libvorbis_static_stdcall.lib"

!ELSEIF  "$(CFG)" == "libvorbis_static - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libvorbis_static___Win32_Debug"
# PROP BASE Intermediate_Dir "libvorbis_static___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Gz /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "STDCALL" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"libvorbis_static_stdcall_d.lib"

!ENDIF 

# Begin Target

# Name "libvorbis_static - Win32 Release"
# Name "libvorbis_static - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\lib\analysis.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\barkmel.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\bitrate.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\block.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\codebook.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\envelope.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\floor0.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\floor1.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\info.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\lookup.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\lpc.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\lsp.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\mapping0.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\mdct.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\psy.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\registry.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\res0.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\sharedbook.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\smallft.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\synthesis.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\vorbisenc.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\window.c
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\lib\backends.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\bitrate.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\codebook.h
# End Source File
# Begin Source File

SOURCE=..\..\include\vorbis\codec.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\codec_internal.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\envelope.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\floor_all.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\books\floor\floor_books.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\highlevel.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\lookup.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\lookup_data.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\lpc.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\lsp.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\masking.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mdct.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\misc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\libogg\include\ogg\ogg.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\os.h
# End Source File
# Begin Source File

SOURCE=..\..\..\libogg\include\ogg\os_types.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\psy.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\psych_11.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\psych_16.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\psych_44.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\psych_8.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\registry.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\books\coupled\res_books_51.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\books\coupled\res_books_stereo.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\books\uncoupled\res_books_uncoupled.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\residue_16.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\residue_44.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\residue_44p51.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\residue_44u.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\residue_8.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\scales.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\setup_11.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\setup_16.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\setup_22.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\setup_32.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\setup_44.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\setup_44p51.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\setup_44u.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\setup_8.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\modes\setup_X.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\smallft.h
# End Source File
# Begin Source File

SOURCE=..\..\include\vorbis\vorbisenc.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\window.h
# End Source File
# End Group
# End Target
# End Project
