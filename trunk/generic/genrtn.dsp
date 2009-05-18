# Microsoft Developer Studio Project File - Name="genrtn" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=genrtn - Win32 Memory
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "genrtn.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "genrtn.mak" CFG="genrtn - Win32 Memory"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "genrtn - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "genrtn - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "genrtn - Win32 Memory" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/OLAP/CLI/W_SYS/GENRTN.LIB", TQXAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "genrtn - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "genrtn__"
# PROP BASE Intermediate_Dir "genrtn__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "release"
# PROP Intermediate_Dir "release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x419
# ADD RSC /l 0x419
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\genrtn.lib"

!ELSEIF  "$(CFG)" == "genrtn - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "genrtn_0"
# PROP BASE Intermediate_Dir "genrtn_0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /GX /Z7 /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /Fr /YX
# ADD BASE RSC /l 0x419
# ADD RSC /l 0x419
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\genrtnd.lib"

!ELSEIF  "$(CFG)" == "genrtn - Win32 Memory"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "genrtn___Win32_Memory"
# PROP BASE Intermediate_Dir "genrtn___Win32_Memory"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Memory"
# PROP Intermediate_Dir "Memory"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "RFC_MEMCHECK" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MTd /W3 /GX /Z7 /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "RFC_MEMCHECK" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x419
# ADD RSC /l 0x419
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\COMMON\LIB\genrtnm.lib"
# ADD LIB32 /nologo /out:"lib\genrtnmd.lib"

!ENDIF 

# Begin Target

# Name "genrtn - Win32 Release"
# Name "genrtn - Win32 Debug"
# Name "genrtn - Win32 Memory"
# Begin Group "source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\_gen_blb.c
# End Source File
# Begin Source File

SOURCE=.\_gen_cb.c
# End Source File
# Begin Source File

SOURCE=.\_gen_cch.c
# End Source File
# Begin Source File

SOURCE=.\_gen_cnv.c
# End Source File
# Begin Source File

SOURCE=.\_gen_hm.c
# End Source File
# Begin Source File

SOURCE=.\_gen_lst.c
# End Source File
# Begin Source File

SOURCE=.\_gen_map.c
# End Source File
# Begin Source File

SOURCE=.\_gen_mem.c

!IF  "$(CFG)" == "genrtn - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "genrtn - Win32 Debug"

!ELSEIF  "$(CFG)" == "genrtn - Win32 Memory"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_gen_msh.c
# End Source File
# Begin Source File

SOURCE=.\_gen_opt.c
# End Source File
# Begin Source File

SOURCE=.\_gen_ptr.c
# End Source File
# Begin Source File

SOURCE=.\_gen_qs.c
# End Source File
# Begin Source File

SOURCE=.\_gen_ra.c
# End Source File
# Begin Source File

SOURCE=.\_gen_rai.c
# End Source File
# Begin Source File

SOURCE=.\_gen_rd.c
# End Source File
# Begin Source File

SOURCE=.\_gen_rl.c
# End Source File
# Begin Source File

SOURCE=.\_gen_rmn.c
# End Source File
# Begin Source File

SOURCE=.\_gen_rs.c
# End Source File
# Begin Source File

SOURCE=.\_gen_rsu.c
# End Source File
# Begin Source File

SOURCE=.\_gen_rsw.c
# End Source File
# Begin Source File

SOURCE=.\_gen_set.c
# End Source File
# Begin Source File

SOURCE=.\_gen_unx.c

!IF  "$(CFG)" == "genrtn - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "genrtn - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "genrtn - Win32 Memory"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_gen_win.c
# End Source File
# Begin Source File

SOURCE=.\_gen_wrs.c
# End Source File
# End Group
# Begin Group "include"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\include\__gen.h
# End Source File
# Begin Source File

SOURCE=.\include\_gencach.h
# End Source File
# Begin Source File

SOURCE=.\include\_gencube.h
# End Source File
# Begin Source File

SOURCE=.\include\_gendata.h
# End Source File
# Begin Source File

SOURCE=.\include\_genhuge.h
# End Source File
# Begin Source File

SOURCE=.\include\_genmap.h
# End Source File
# Begin Source File

SOURCE=.\include\_genmisc.h
# End Source File
# Begin Source File

SOURCE=.\include\_genmsh.h
# End Source File
# Begin Source File

SOURCE=.\include\_genos.h
# End Source File
# Begin Source File

SOURCE=.\include\_genplat.h
# End Source File
# Begin Source File

SOURCE=.\include\_genset.h
# End Source File
# Begin Source File

SOURCE=.\include\_genstr.h
# End Source File
# End Group
# Begin Group "lib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lib\genrtnmd.lib
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\lib\genrtn.lib
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\lib\genrtnd.lib
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "stacktrace"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\stacktrace\Array.h
# End Source File
# Begin Source File

SOURCE=.\stacktrace\MapFile.cpp
# End Source File
# Begin Source File

SOURCE=.\stacktrace\MapFile.h
# End Source File
# Begin Source File

SOURCE=.\stacktrace\MapFileEntry.cpp
# End Source File
# Begin Source File

SOURCE=.\stacktrace\MapFileEntry.h
# End Source File
# Begin Source File

SOURCE=.\stacktrace\printStackTrace.cpp
# End Source File
# Begin Source File

SOURCE=.\stacktrace\printStackTrace.h
# End Source File
# Begin Source File

SOURCE=.\stacktrace\StackTrace.cpp
# End Source File
# Begin Source File

SOURCE=.\stacktrace\StackTrace.h
# End Source File
# Begin Source File

SOURCE=.\stacktrace\TextFile.cpp
# End Source File
# Begin Source File

SOURCE=.\stacktrace\TextFile.h
# End Source File
# End Group
# End Target
# End Project
