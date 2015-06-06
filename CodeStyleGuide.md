@@[Home](Home.md) -> [CodeStyleGuide](CodeStyleGuide.md)


![http://ahuman.googlecode.com/svn/images/wiki/procedures/codestyle.jpg](http://ahuman.googlecode.com/svn/images/wiki/procedures/codestyle.jpg)

---


## What is The Code Style and Why We Need It ##

  * Code style is the only way to share code
  * Good code style helps to develop complex programs

## Naming Convention ##

  * use http://en.wikipedia.org/wiki/CamelCase as a direction
  * name variables, functions as varName, doSelfDescriptiveAction
  * name classes, typedefs, enums, structs as TypeName
  * name constants, defines, as MAXNAME
  * name files in lower case, as filename.h
    1. name headers by functional area, as aidb.h
    1. name source files by class, use one file per class, as nnlayer.cpp

## Formatting ##

  * align function body with 8-char tabs
  * use spaces to delimit any text, except function name, from brackets and commas
  * use spaces before and after '='
  * use empty lines to delimit closely related groups of code lines (code block)
  * use the doxygen style function header comments.

## Comments ##

  * use one-line comments for every code block
  * try write comments in such way that they represent sequential specification of function if delete the code
  * use area delimiter to split file into groups of functions of very different matter - e.g. header references, interface functions, internal implementation functions, standard interface implementation, such as Object