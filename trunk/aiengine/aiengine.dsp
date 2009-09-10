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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../common/include" /I "src\include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "TIXML_USE_STL" /YX /FD /c
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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../generic/include" /I "src\include" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "TIXML_USE_STL" /FR /YX /FD /GZ /c
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

SOURCE=.\src\include\generic\__gen.h
# End Source File
# Begin Source File

SOURCE=.\src\include\generic\_gencach.h
# End Source File
# Begin Source File

SOURCE=.\src\include\generic\_gencube.h
# End Source File
# Begin Source File

SOURCE=.\src\include\generic\_gendata.h
# End Source File
# Begin Source File

SOURCE=.\src\include\generic\_genhuge.h
# End Source File
# Begin Source File

SOURCE=.\src\include\generic\_genmap.h
# End Source File
# Begin Source File

SOURCE=.\src\include\generic\_genmisc.h
# End Source File
# Begin Source File

SOURCE=.\src\include\generic\_genmsh.h
# End Source File
# Begin Source File

SOURCE=.\src\include\generic\_genos.h
# End Source File
# Begin Source File

SOURCE=.\src\include\generic\_genplat.h
# End Source File
# Begin Source File

SOURCE=.\src\include\generic\_genset.h
# End Source File
# Begin Source File

SOURCE=.\src\include\generic\_genstr.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\include\aibasetypes.h
# End Source File
# Begin Source File

SOURCE=.\src\include\aidb.h
# End Source File
# Begin Source File

SOURCE=.\src\include\aiengine.h
# End Source File
# Begin Source File

SOURCE=.\src\include\aiheart.h
# End Source File
# Begin Source File

SOURCE=.\src\include\aihtmlib.h
# End Source File
# Begin Source File

SOURCE=.\src\include\aiio.h
# End Source File
# Begin Source File

SOURCE=.\src\include\aiknowledge.h
# End Source File
# Begin Source File

SOURCE=.\src\include\aimedia.h
# End Source File
# Begin Source File

SOURCE=.\src\include\aimind.h
# End Source File
# Begin Source File

SOURCE=.\src\include\ainnlib.h
# End Source File
# Begin Source File

SOURCE=.\src\include\aiobject.h
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
# Begin Group "moddb"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\moddb\aidb_impl.h
# End Source File
# Begin Source File

SOURCE=.\src\moddb\db.cpp
# End Source File
# Begin Source File

SOURCE=.\src\moddb\dbcursor.cpp
# End Source File
# Begin Source File

SOURCE=.\src\moddb\dbfile.cpp
# End Source File
# Begin Source File

SOURCE=.\src\moddb\dbrecordheader.cpp
# End Source File
# Begin Source File

SOURCE=.\src\moddb\dbrecordset.cpp
# End Source File
# End Group
# Begin Group "modio"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\modio\aiio_impl.h
# End Source File
# Begin Source File

SOURCE=.\src\modio\channel.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modio\io.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modio\message.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modio\publisher.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modio\queue.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modio\subscription.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modio\xmlcall.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modio\xmlmessage.cpp
# End Source File
# End Group
# Begin Group "modengine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\modengine\aiengine_impl.h
# End Source File
# Begin Source File

SOURCE=.\src\modengine\engine.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\fileutils.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\logger.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\logmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\logsettings.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\logsettingsitem.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\math.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\multiindexiterator.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\object.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\objectfield.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\random.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\runtimeexception.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\scale.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\serializeobject.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\string.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\timer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\tinyxml.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\tinyxml.h
# End Source File
# Begin Source File

SOURCE=.\src\modengine\tinyxmlerror.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\tinyxmlparser.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modengine\xml.cpp
# End Source File
# End Group
# Begin Group "modnnlib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\modnnlib\_wallpaper.txt
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\ainnlib_impl.h
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\ainnlib_implfunc.h
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\ainnlib_implnet.h
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\ainnlib_implnn.h
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\ainnlib_implstrategy.h
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nn.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnactivationfunction.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnerrorfunction.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnfinder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnfinderfactory.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnfinderfactorysample.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nninductionfunction.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnlib.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnlibdebug.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnneuron.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnregression.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnregressionfactory.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnsample.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnsamples.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnscanpoint.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnstopfunction.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnstrategy.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnstrategybackpropagation.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnstrategyhelper.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnstrategyscan.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnstrategyscaniteration.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnvalidatefunction.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnvariable.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnvariablecategory.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnvariables.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnvariablescontainer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnvariablesimple.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modnnlib\nnweights.cpp
# End Source File
# End Group
# Begin Group "modhtmlib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\modhtmlib\aihtmlib_impl.h
# End Source File
# Begin Source File

SOURCE=.\src\modhtmlib\htmlib.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modhtmlib\htmlibdebug.cpp
# End Source File
# End Group
# Begin Group "modmedia"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\modmedia\aimedia_impl.h
# End Source File
# Begin Source File

SOURCE=.\src\modmedia\listener.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modmedia\media.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modmedia\socketconnection.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modmedia\sockserver.cpp
# End Source File
# End Group
# Begin Group "modmind"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\modmind\aimind_impl.h
# End Source File
# Begin Source File

SOURCE=.\src\modmind\mind.cpp
# End Source File
# End Group
# Begin Group "modknowledge"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\modknowledge\aiknowledge_impl.h
# End Source File
# Begin Source File

SOURCE=.\src\modknowledge\knowledge.cpp
# End Source File
# End Group
# Begin Group "modheart"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\modheart\aiheart_impl.h
# End Source File
# Begin Source File

SOURCE=.\src\modheart\emotion.cpp
# End Source File
# Begin Source File

SOURCE=.\src\modheart\heart.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\_wallpaper.txt
# End Source File
# Begin Source File

SOURCE=.\src\main.cpp
# End Source File
# End Target
# End Project
