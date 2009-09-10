# Microsoft Developer Studio Project File - Name="aiengine" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=aiengine - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "aiengine.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "aiengine.mak" CFG="aiengine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "aiengine - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "aiengine - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "aiengine - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "include" /I "../common/include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "TIXML_USE_STL" /YX /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib genrtn.lib ws2_32.lib /nologo /subsystem:console /machine:I386 /libpath:"lib/release"

!ELSEIF  "$(CFG)" == "aiengine - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "include" /I "../generic/include" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "TIXML_USE_STL" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 genrtnd.lib ws2_32.lib kernel32.lib /nologo /subsystem:console /profile /map /debug /machine:I386 /libpath:"lib/debug"
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "aiengine - Win32 Release"
# Name "aiengine - Win32 Debug"
# Begin Group "include"

# PROP Default_Filter ""
# Begin Group "generic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\generic\__gen.h
# End Source File
# Begin Source File

SOURCE=.\include\generic\_gencach.h
# End Source File
# Begin Source File

SOURCE=.\include\generic\_gencube.h
# End Source File
# Begin Source File

SOURCE=.\include\generic\_gendata.h
# End Source File
# Begin Source File

SOURCE=.\include\generic\_genhuge.h
# End Source File
# Begin Source File

SOURCE=.\include\generic\_genmap.h
# End Source File
# Begin Source File

SOURCE=.\include\generic\_genmisc.h
# End Source File
# Begin Source File

SOURCE=.\include\generic\_genmsh.h
# End Source File
# Begin Source File

SOURCE=.\include\generic\_genos.h
# End Source File
# Begin Source File

SOURCE=.\include\generic\_genplat.h
# End Source File
# Begin Source File

SOURCE=.\include\generic\_genset.h
# End Source File
# Begin Source File

SOURCE=.\include\generic\_genstr.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\include\aibasetypes.h
# End Source File
# Begin Source File

SOURCE=.\include\aidb.h
# End Source File
# Begin Source File

SOURCE=.\include\aiengine.h
# End Source File
# Begin Source File

SOURCE=.\include\aiexpert.h
# End Source File
# Begin Source File

SOURCE=.\include\aiheart.h
# End Source File
# Begin Source File

SOURCE=.\include\aiio.h
# End Source File
# Begin Source File

SOURCE=.\include\aiknowledge.h
# End Source File
# Begin Source File

SOURCE=.\include\aimedia.h
# End Source File
# Begin Source File

SOURCE=.\include\aimind.h
# End Source File
# Begin Source File

SOURCE=.\include\aiobject.h
# End Source File
# End Group
# Begin Group "moddb"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\moddb\aidb_impl.h
# End Source File
# Begin Source File

SOURCE=.\moddb\db.cpp
# End Source File
# Begin Source File

SOURCE=.\moddb\dbcursor.cpp
# End Source File
# Begin Source File

SOURCE=.\moddb\dbfile.cpp
# End Source File
# Begin Source File

SOURCE=.\moddb\dbrecordheader.cpp
# End Source File
# Begin Source File

SOURCE=.\moddb\dbrecordset.cpp
# End Source File
# End Group
# Begin Group "modheart"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modheart\aiheart_impl.h
# End Source File
# Begin Source File

SOURCE=.\modheart\emotion.cpp
# End Source File
# Begin Source File

SOURCE=.\modheart\heart.cpp
# End Source File
# End Group
# Begin Group "modio"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modio\aiio_impl.h
# End Source File
# Begin Source File

SOURCE=.\modio\channel.cpp
# End Source File
# Begin Source File

SOURCE=.\modio\io.cpp
# End Source File
# Begin Source File

SOURCE=.\modio\message.cpp
# End Source File
# Begin Source File

SOURCE=.\modio\publisher.cpp
# End Source File
# Begin Source File

SOURCE=.\modio\queue.cpp
# End Source File
# Begin Source File

SOURCE=.\modio\subscription.cpp
# End Source File
# Begin Source File

SOURCE=.\modio\xmlcall.cpp
# End Source File
# Begin Source File

SOURCE=.\modio\xmlmessage.cpp
# End Source File
# End Group
# Begin Group "modknowledge"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modknowledge\aiknowledge_impl.h
# End Source File
# Begin Source File

SOURCE=.\modknowledge\knowledge.cpp
# End Source File
# End Group
# Begin Group "modmind"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modmind\aimind_impl.h
# End Source File
# Begin Source File

SOURCE=.\modmind\mind.cpp
# End Source File
# End Group
# Begin Group "modmedia"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modmedia\aimedia_impl.h
# End Source File
# Begin Source File

SOURCE=.\modmedia\listener.cpp
# End Source File
# Begin Source File

SOURCE=.\modmedia\media.cpp
# End Source File
# Begin Source File

SOURCE=.\modmedia\socketconnection.cpp
# End Source File
# Begin Source File

SOURCE=.\modmedia\sockserver.cpp
# End Source File
# End Group
# Begin Group "modexpert"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modexpert\aiexpert_impl.h
# End Source File
# Begin Source File

SOURCE=.\modexpert\aiexpert_implfunc.h
# End Source File
# Begin Source File

SOURCE=.\modexpert\aiexpert_implnet.h
# End Source File
# Begin Source File

SOURCE=.\modexpert\aiexpert_implnn.h
# End Source File
# Begin Source File

SOURCE=.\modexpert\aiexpert_implstrategy.h
# End Source File
# Begin Source File

SOURCE=.\modexpert\expert.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\expertdebug.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nn.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnactivationfunction.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnerrorfunction.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnfinder.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnfinderfactory.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnfinderfactorysample.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nninductionfunction.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnneuron.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnregression.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnregressionfactory.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnsample.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnsamples.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnscanpoint.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnstopfunction.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnstrategy.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnstrategybackpropagation.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnstrategyhelper.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnstrategyscan.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnstrategyscaniteration.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnvalidatefunction.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnvariable.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnvariablecategory.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnvariables.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnvariablescontainer.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnvariablesimple.cpp
# End Source File
# Begin Source File

SOURCE=.\modexpert\nnweights.cpp
# End Source File
# End Group
# Begin Group "modengine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modengine\aiengine_impl.h
# End Source File
# Begin Source File

SOURCE=.\modengine\engine.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\fileutils.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\logger.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\logmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\logsettings.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\logsettingsitem.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\math.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\multiindexiterator.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\object.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\objectfield.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\random.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\runtimeexception.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\scale.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\serializeobject.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\string.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\timer.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\tinyxml.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\tinyxml.h
# End Source File
# Begin Source File

SOURCE=.\modengine\tinyxmlerror.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\tinyxmlparser.cpp
# End Source File
# Begin Source File

SOURCE=.\modengine\xml.cpp
# End Source File
# End Group
# Begin Group "etc"

# PROP Default_Filter "*.xml"
# Begin Source File

SOURCE=.\etc\database.xml
# End Source File
# Begin Source File

SOURCE=.\etc\logging.xml
# End Source File
# Begin Source File

SOURCE=.\etc\main.xml
# End Source File
# End Group
# Begin Source File

SOURCE=.\_wallpaper.txt
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# End Target
# End Project
