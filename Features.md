@@[Home](Home.md) -> [Features](Features.md)

![http://ahuman.googlecode.com/svn/images/wiki/development/robomouses.jpg](http://ahuman.googlecode.com/svn/images/wiki/development/robomouses.jpg)

---


This page is a place for features already implemented in aHuman project modules.
Modular approach for aHuman is chosen so that modules explain how functionality is split into relatively independent groups. Modules are re-using common libraries, established as a core of aHuman.

## Top Features ##

  * pure software platform to implement brain processes with neural and non-neural elements
  * cortex building block paradigm where all the mind, except framework and libraries, is represented by a set of interconnected neural of belief networks, each network is a kind of abstract Cortex object
  * allows integration of several incompatible implementations of neural networks and belief networks and using them in different cortexes

## Mind Modules ##

  * [MindTargetFeatures](MindTargetFeatures.md) - final application with specific sensors and effectors
  * [MindServiceFeatures](MindServiceFeatures.md) - overall mind management
  * [MindAreaFeatures](MindAreaFeatures.md) - mind area and its lifecycle
  * [MindRegionFeatures](MindRegionFeatures.md) - supporting types of cortex and nuclei architecture
  * [MindMatterFeatures](MindMatterFeatures.md) - software representation of neural networks
  * [MindFrameworkFeatures](MindFrameworkFeatures.md) - supporting interaction of mind modules

## Framework and Libraries ##

  * [FrameworkFeatures](FrameworkFeatures.md) - framework features
  * [PlatformFeatures](PlatformFeatures.md) - generic platform features
  * [genrtnlibFeatures](genrtnlibFeatures.md) - generic library features