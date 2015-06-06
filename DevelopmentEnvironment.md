@@[Home](Home.md) -> [DevelopmentEnvironment](DevelopmentEnvironment.md)

![http://ahuman.googlecode.com/svn/images/wiki/procedures/deathrow.jpg](http://ahuman.googlecode.com/svn/images/wiki/procedures/deathrow.jpg)

---


## Overview ##

Project framework is based on Visual Studio 2010 Express Edition - free IDE. Subversion is used as a version control system.

## How To Setup Development Environment ##

Finish [Joining the Project](JoinProject.md) quest before trying below

  * [Setup Visual Studio 2010 Express Edition](VisualStudio2010.md)
  * [Setup Subversion](Subversion.md)
  * [Download Sources and Build](Sources.md)
  * [Run and Debug Locally](LocalIDEEnvironment.md)

## Project Structure Guidelines ##

  * Projects are not directly dependent on each other; if dependencies exist, related interfaces and binaries are copied into target project codebase
  * Virtual folders should correspond to directories, except for below cases
    * if folder contains files of different types - e.g. headers and C++, then we can create virtual folders to separate these types - e.g. "include" directory
    * if folder has too many files to manage - we can split files by folders (but better to split files by subdirectories as well)
  * Any project contains typical directories on top level:
    * src - all sources, including C/C++ headers and body files
    * bin - output files should be redirected to this location
    * build - intermediate files, byproducts of build
    * etc - configuration files if any
    * lib - used libraries
  * any project is included in one or more workspaces
    * project corresponds to the build target
    * workspace corresponds to the deployment target and has name:
```
"workspace.<deployment target name>"
```

## Upgrading the Development Environment ##

General IDE requirements:

  * Language is not P-code like Java - these programs work in sandbox and use quite heavy runtime
  * IDE is free
  * Evidence of successful discussion at forum

## Usign External Libraries ##

  * for each research area support several libraries implementing related features
  * each external library should have been committed as is, with all sources
  * customized library should have been specifically marked in the codebase
  * any external library should have wrapper code, functioning as a facade (limiting library scope to only used one and conforming interfaces to aHuman codestyle and design giudelines)

## Decommissioned child pages ##

  * [Setup Microsoft Visual C++ 6.0](MSVC6.md) - stale due to migration to Codelite
  * [Setup Codelite](Codelite.md) - less convenient than Visual Studio