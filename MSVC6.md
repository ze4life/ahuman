@@[Home](Home.md) -> [DevelopmentEnvironment](DevelopmentEnvironment.md) -> [MSVC6](MSVC6.md)

---


This IDE is used to create the code and build. Human sources are arranged as a set of Visual C++ projects, better name them by targets - applications or libraries to avoid confusion. All the codebase is stored in $/sources and $/branches - see Download Sources and Build to find exact codebase layout.
Library

Each library package contains binaries for debug and release and sources to describe interfaces. Library can use another libraries, providing no loop in library dependencies.
Application

Each application package contains binaries for debug and release, and is represented by one or more operating system processes in run-time. Application can use libraries.
Internal Distributives and Dependencies

IDE allows to perform a build for distinct library or application. After a build library or application is represented by distributive package. All intermediate distributive packages are stored in Subversion repository in $/builds.

To use the library, you need to explicitly commit its distributive to the codebase of the application or library which uses given library. This is a bit inconvenient, but promotes to use larger modules, and to delimit parts which we rarely need to change simultaneously.
To Do

  * Prepare VC++ 6.0 installation package and MSDN installation package
  * Install VC++ 6.0
  * On completion, you will be asked to install MSDN - do it now, otherwise you will not be able to have context queries to MSDN from VC++
  * Leave default parameters, but I'd recommend to change coloring for strings and comments

Possible Enhancements

  * Probably VC 6.0 should be replaced with Eclipse
  * To have strong build most promising is ant tool