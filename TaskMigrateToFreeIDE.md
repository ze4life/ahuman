@@[Home](Home.md) -> [ProjectPlanning](ProjectPlanning.md) -> [TaskMigrateToFreeIDE](TaskMigrateToFreeIDE.md)

---


## What ##

  * Select proper IDE
  * Replace MSDEV build scripts with new ones
  * Attach Subversion plugin
  * Create default workspace settings
  * Migrate GUI project

## How ##

  * After close look Eclipse has been rejected because it is much more Java, but has weaknesses for C++ - too slow, debug is unavailable
  * Codelite is chosen as next target IDE for migration

findings:
  * Except Codelite itself, MinGW required and OpenSSH (used for Clean)
  * -static required to avoid MinGW runtime dlls to be used
  * link order should used accurately - e.g. aiconsole requires first linking to aiapi, then to ws2\_32

changes in the code:
  * "for( int x" - x now is inside for block, not visible outside
  * when passing class function as argument from class method, g++ requires using construction:
```
"&<class>::<function>"
```
  * "thread" keyword is unsupported by g++, changed to Tls function calls
  * g++ has found several errors in unused template functions
  * now commented C++ handling of SEH exceptions - TBD
  * static string data require const keyword in g++
  * more strict checking is for pointer conversions in C++ under g++ - unable to convert implicitly `void*` to `char*`
  * varargs is no more supported in g++ - replaced with stdarg version (in fact varargs existed before because of UNIX compatibility issues)
  * varargs now puts char/short as int to stack
  * generic headers have been updated - checked in new generic version to aiengine
  * not resolved question - moment type is now stale - its calendar limit is overdue
  * found non-english constants for calendar terms - replaced with english ones
  * unicode constant is not `ushort*` - forced conversions, needs investigations - TBD
```
L"<string>"
```
  * for g++ HINSTANCE is not `void*`
  * min, max macros are defined in system headers - added #ifndef blocks
  * `__int64` is replaced with long long int
  * C-level MSDEV-specific `__try/__catch` was replaced with try/catch - don't know about impact on functionality

change, done by the way - all projects now conform to common structure rules - see related section at [DevelopmentEnvironment](DevelopmentEnvironment.md)