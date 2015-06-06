@@[Home](Home.md) -> [DevelopmentEnvironment](DevelopmentEnvironment.md) -> [Subversion](Subversion.md)

![http://ahuman.googlecode.com/svn/images/wiki/procedures/sliksvn.jpg](http://ahuman.googlecode.com/svn/images/wiki/procedures/sliksvn.jpg)

---


Subversion is a version control system.
Also it is an attempt to improve CVS at least for:

  * implement transactional commit
  * allow directory have a version
  * fast creation of branches/tags
  * allow renaming with saving change history

Unfortunately it also has drawbacks if compared to CVS:

  * each file has version of total repository, not own version number
  * branches do not have clear version numbers

**To Do**

Subversion server is installed under google authority.
Development environment should contain Subversion client. Steps to setup console client and optionally GUI client:

  1. Install console Subversion client Slik SVN 1.6.2 from http://www.sliksvn.com/en/download
  1. (optional) Now you can download sources (but will not be able to change them) using command line (as a project member you will you another download command):
```
svn checkout http://ahuman.googlecode.com/svn/trunk/ ahuman-read-only
```
  1. (optional) Install TortoiseSVN 1.6.2 from http://tortoisesvn.net/downloads if you want to look into version information using Windows Explorer
  1. To download code to permanent storing or changes, use command, described at http://code.google.com/p/ahuman/source/checkout, where google will provide you with a link to the page containing your personal password

**Possible Enhancements**

In the current development environment IDE is detached from version control client. It is not good enough. Possible actions are - find Subversion plug-in for Visual C++ or upgrade VC++ to Eclipse where I know such a plug-in exists.