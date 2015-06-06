@@[Home](Home.md) -> [DesignStyleGuide](DesignStyleGuide.md)

![http://ahuman.googlecode.com/svn/images/wiki/procedures/applehand.jpg](http://ahuman.googlecode.com/svn/images/wiki/procedures/applehand.jpg)

---


## What is Design Style Guide ##

This is a very important page which is intended to incline us to the right design wherever it is applied. Practically this page should contain answers for Human project on:

  * What is the design, where the design ends and where fair coding begins
  * What are the basic steps to have any design
  * How to integrate several design solutions done by different team members
  * What is to be documented on Wiki, in comments

## What is the design ##

To be away from philosophy and referencing great guys, let me say what is essential from my experience:

  * **design represents a certain construction idea and encapsulates it in certain language/build terms**. No design without idea. The idea is implemented using specific algorithm. When the corresponding items are created, in the remaining code you can forget this idea and its implementation and see only specific application service. If you follow this rule then you can change the idea/design decision without affecting much code
  * **design has value when aligned with specific set of named things**. For example, design pattern is described as set of classes and interfaces, architectural solution described as a set of configuration items

Well, I vote for evolutionary design versus Big Bang one

## How To ##

  * find what decision you want to encapsulate
  * place the design considerations on Wiki in task speclet - pro/contra
  * describe design implementation
  * reduce it at maximum, leaving only absolutely necessary words
  * read it/make it self-convincing

## Compound Design ##

  * do not force clients of your service to follow extra flow, leave only absolutely necessary requirements on how and when use your service
  * if you initiated the refactoring and it will lead to changes in some other components - be ready to perform the changes and you need to agree with the owner of affected code

## Design Details ##

  * all the information you want to specify but that is subject to reduction as specified in How To, you can place in the code in form of comments in headers (should be focused on user's needs) and implementation sources (internal view, help to next refactoring)

## Low-level Wide-spread Design Solutions ##

  * do not use STL, at least widely
  * use logging for debugging purposes:
    1. do not comment out logging after debug ended, use log level and log grouping
    1. for classes with complex code keep logging in helper class, encapsulating format and log details