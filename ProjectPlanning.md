@@[Home](Home.md) -> [ProjectPlanning](ProjectPlanning.md)

![http://ahuman.googlecode.com/svn/images/wiki/research/planning.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/planning.jpg)



---


# Project Phases / Steps #

A lot is to be done on Wiki, but generally it is in a good shape:

## 1. Create project Wiki - **done** ##

The most active stage is this one:

## 2. Create coding framework and define most essential features ##

Phase Goals:
  * Setup stable and transparent (documented) development environment
  * Freeze vision
  * Create exact high-level design, which fits the vision
  * Create component diagram, with one main function per component
  * Choose AI technology set for each of the component
  * Specify component interface

See [aFramework Requirements and Status](aFrameworkRequirements.md)


---


Real coding currently can be done for below only:

## 3. Create **aMatter** ##

Phase Goals:
  * Demonstrate Perception/Self-Learning features
  * Demonstrate Cognition as meaningful sensor control
  * Demonstrate Feeling Feature
  * Implement above core functions using real-time neural networks

See [aMatter Requirements and Status](aMatterRequirements.md)


---


Until completion of previous steps any activity for below ones should be avoided:

## 4. Create **aChild** ##

Phase Goals:
  * Demonstrate Personality Features
  * Demonstrate Thinking Process
  * Persisting of learned experience
  * Running shared live instance

See [aChild Requirements and Status](aChildRequirements.md)

## 5. Create **aHuman** ##

Phase Goals:
  * Demonstrate competence in specific area
  * Demonstrate ability to bring value

See [aHuman Requirements and Status](aHumanRequirements.md)


---


# Development Approach #

  * Generally do not use Open Sources tools and libraries, only design elements
  * Increase level of complexity step by step
  * Perception -> Reflection -> Cognition -> Consciousness

## Current Challenges ##

General:

  * implementing near-human congition with limited resources
  * sustained learning

Realtime Neural Networks:

  * receptive field processing
  * regular circuits in non-cortex nucleus
  * store and recall
  * interneurons

Physiology:

  * sensor control circuit
  * feeling circuits
  * stream of consciousness
  * networks of interneurons

Cognition:

  * cortex model - external connectors and their functional roles, NeuroPool items and their connectivity, temporal dynamics
  * association memory technology
    * a lot of entities
    * time-based links
    * linking distant items
    * multi-hop associations

## Using Third-party Libraries ##

Generally we have below options:
  * don't use a copy of external code to implement 3-d party library functions (not suitable if take into account the complexity of aHuman task)
  * use library code as a reference to understand algorithms and implement the same with required amendments (the way chosen when project has been started)
  * use library as is, in form of committed binaries and headers or as full sources

Last one is the way that looks to me most effective now.
To keep it consistent with our architecture:
  * never use external library API directly, do it only via facade interface
  * support having in the codebase several libraries for the same purpose, e.g. several neural network implementations, and related wrappers in facade to address different coding style and design approaches

## Current Activities ##

  * see [ProjectTasks](ProjectTasks.md)

## Future Features ##

  * [Local Watcher](FutureFeatureLocalWatcher.md)