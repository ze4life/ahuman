@@[Home](Home.md) -> [DevelopmentEnvironment](DevelopmentEnvironment.md) -> [Codelite](Codelite.md)

---


## Install Codelite ##

  * Download installation distributive for Windows
  * Run it, I would suggest to use directory like K:\tools for this, not Program Files
  * Installation will setup Codelite, MinGW (open source compiler/linker etc), UnitTest

## Install wxWidgets (under Windows XP) ##

  * download wxMSW-2.8.10.zip from http://prdownloads.sourceforge.net/wxwindows/wxMSW-2.8.10.zip (see link at http://www.wxwidgets.org/downloads/ under Source Archives -> wxMSW - installer for Windows, with manual (other formats: **zip**))
  * unzip it to (e.g.) K:\tools (zip contains single folder `wxMSW-2.8.10`) - so finally you have `K:\tools\wxMSW-2.8.10 and build,lib,src,...` as a next layer
  * build - static versions for debug and release:
    * go to `K:\tools\wxMSW-2.8.10\build\msw\`
    * create build.bat there:
```
@ECHO OFF
set PATH=K:\tools\MinGW-4.4.0\bin;K:\tools\MinGW-4.4.0\lib
mingw32-make -f makefile.gcc UNICODE=0 SHARED=0 MONOLITHIC=1 BUILD=debug
mingw32-make -f makefile.gcc UNICODE=0 SHARED=0 MONOLITHIC=1 BUILD=release
mingw32-make -f makefile.gcc UNICODE=1 SHARED=0 MONOLITHIC=1 BUILD=debug
mingw32-make -f makefile.gcc UNICODE=1 SHARED=0 MONOLITHIC=1 BUILD=release
```
    * execute build.bat - it will create:
```
K:\tools\wxMSW-2.8.10\lib\gcc_lib\libwxmsw28.a
K:\tools\wxMSW-2.8.10\lib\gcc_lib\libwxmsw28d.a
K:\tools\wxMSW-2.8.10\lib\gcc_lib\libwxmsw28u.a
K:\tools\wxMSW-2.8.10\lib\gcc_lib\libwxmsw28ud.a
K:\tools\wxMSW-2.8.10\lib\gcc_lib\mswu\
K:\tools\wxMSW-2.8.10\lib\gcc_lib\mswud\
K:\tools\wxMSW-2.8.10\lib\gcc_lib\msw\
K:\tools\wxMSW-2.8.10\lib\gcc_lib\mswd\

(can be deleted after build to free 500Mb on disk)
K:\tools\wxMSW-2.8.10\build\msw\gcc_msw\
K:\tools\wxMSW-2.8.10\build\msw\gcc_mswd\
K:\tools\wxMSW-2.8.10\build\msw\gcc_mswu\
K:\tools\wxMSW-2.8.10\build\msw\gcc_mswud\
```
  * manually copy `K:\tools\wxMSW-2.8.10\include\wx\msw\setup.h` to `K:\tools\wxMSW-2.8.10\include\wx\setup.h`
  * in Codelite open Settings -> Environment Variables and add WXWIN with value `K:\tools\wxMSW-2.8.10`

## Configuring wxWidgets-based project (e.g. Htmview) ##
  * Global Settings:
```
Compiler/Additional Search Path=.;K:/tools/wxMSW-2.8.10/include
Linker/Options=-static
```
  * Debug Settings:
```
Compiler/Compiler Options=-g;$(shell wx-config --wxcfg=gcc_lib/mswud --cxxflags --static=yes --unicode=no --debug=yes)
Compiler/Preprocessor=__WX__
Linker/Options=$(shell wx-config --wxcfg=gcc_lib/mswud --static=yes --debug=yes --libs --unicode=no)
```
  * Release Settings:
```
Compiler/Compiler Options=-g;$(shell wx-config --wxcfg=gcc_lib/mswu --cxxflags --static=yes --unicode=no --debug=no)
Compiler/Preprocessor=__WX__
Linker/Options=$(shell wx-config --wxcfg=gcc_lib/mswu --static=yes --debug=no --libs --unicode=no)
```