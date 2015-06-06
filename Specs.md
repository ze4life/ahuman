@@[Home](Home.md) -> [Specs](Specs.md)

![http://ahuman.googlecode.com/svn/images/wiki/development/design.jpg](http://ahuman.googlecode.com/svn/images/wiki/development/design.jpg)

---

## Body / Primary Sensors ##

  * Design is based on [SensorsResearch](SensorsResearch.md)

**Inputs:**
  * primary input - implemented, event-driven verified, polling not verified - TBD
  * sensor control - defined, not connected to anything - TBD
  * perception feedback - not defined - TBD after having cognition

**Outputs:**
  * primary output - implemented
  * control feedback - not defined - TBD
  * exposed control state properties - not defined - TBD

## Cognition / Neocortex ##

**Inputs**
  * primary input - implemented, from sensors via IO channel, one cortex per one sensor
  * expectation input - not defined
  * adoption control - not defined

**Outputs**
  * primary outputs - not defined - TBD
  * feedback output - predicted sensor data, not defined

## Image Search Knowledge Base ##
  * [Image search Knowledge Base](ImageSearchKB.md)

## Chat Interface ##
  * [Chat Interface](ChatInterface.md)

## Media ##
  * [Network Listeners](NetworkListeners.md)
  * [Active Sockets](ActiveSockets.md)
  * [Network Protocols Supported](MediaProtocols.md)

## Re-used Projects ##

  * **[HTM implementation](http://sourceforge.net/projects/neocortex)** - Source Forge project
  * **StackTrace** - Copyright (c) 2001 Jani Kajala
  * **[FANN library](http://leenissen.dk/fann)** - Copyright (C) 2003 Steffen Nissen (lukesky@diku.dk)
  * **[tinyxml](http://www.sourceforge.net/projects/tinyxml)** - Original code (2.0 and earlier) copyright (c) 2000-2006 Lee Thomason (www.grinninglizard.com)
  * **[RebeccaAIML](http://rebecca-aiml.sourceforge.net)** - Source Forge Project
  * **[GraphViz](http://www.graphviz.org/)** - Tool to generate complex graphs from text script using command line

Guys, thank you for your ideas and efforts.