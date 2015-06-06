@@[Home](Home.md) -> [Architecture](Architecture.md) -> [ArchitectureModelV2](ArchitectureModelV2.md)



---


Up to the moment several models were created, addressing different sides.
Latest models include more enhanced understanding of subject area.
I regard ENTHORINAL cortex separate from NEOCORTEX, though from neurobiology point of view, it is neocortex as well. It is done to stress its close relation to HIPPOCAMPUS.
Jeff Hawkins, in turn, regards neurobiology neocortex, THALAMUS and HIPPOCAMPUS as sufficient set of elements to explain functions of human intelligence.
All brain parts, except HYPOTHALAMUS and CEREBELLUM, exist in both left and right hemispheres. Purely biological parts, like Pineal Gland are not present in model, even in aggregated form.

## Mapping To Human Body ##

![http://ahuman.googlecode.com/svn/images/wiki/development/humanmind.jpg](http://ahuman.googlecode.com/svn/images/wiki/development/humanmind.jpg)

## Brain Components ##

Informational model of real brain (actually left body is connected to right brain - but it does not bring any difference from model perspective):

![http://ahuman.googlecode.com/svn/images/wiki/research/brain/RealBrain.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/brain/RealBrain.jpg)

Below aggregated model demonstrates spinal cord role and principal mind flows.
NEOCORTEX from above model is split into CT/CORTEX and FC/FRONTAL CORTEX.
Left and right items are shown as double blocks.

![http://ahuman.googlecode.com/svn/images/wiki/research/brain/AggregatedBrain.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/brain/AggregatedBrain.jpg)

Model reflects cognitive, conscious and biological processes.
Cognition is mostly related to neocortex, including recognition and learning.
Find more detailed informational model of components which implement cognition:

![http://ahuman.googlecode.com/svn/images/wiki/research/brain/CortexLinks.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/brain/CortexLinks.jpg)

## Current understanding ##

Last findings:

Now the role and interrelationships of major scientific areas - Artificial Life, Artificial Intelligence, Cognition, Neurobiology - are quite clear and the design is based on:

  * Plausible compared to human - local connections, major components are based on human design
  * Design should allow using ordinary computer, not Blue Brain one
  * All design items on first level should be based on limitations and existing human design - no attempt to descend to certain final component model
  * Design should take into account priority of life features over intelligence features
  * Items should demonstrate ability to adopt to environment "by design"

![http://ahuman.googlecode.com/svn/images/wiki/development/mindmap.jpg](http://ahuman.googlecode.com/svn/images/wiki/development/mindmap.jpg)

## Function / Technology Map ##

| **Module / Component Set** | **Primary Function** | **Related Problems and Algorithms** |
|:---------------------------|:---------------------|:------------------------------------|
| **engine**                 | startup sequence and component management |                                     |
| **modbody**                |                      |                                     |
| physiology                 | positioning of sensors and effectors |                                     |
| biology                    | internal senses and motivation |                                     |
| sensors                    | produce raw sensor flow | chat reader, video-stream, signal processing |
| effectors                  | pre-defined sets of actions in environment | chat writer, primary feedback       |
| **modbrain**               | multi-neurex map and its evolution |                                     |
| **modmedia**               | physical access to external environment |                                     |
| **modcognition**           |                      |                                     |
| neocortex                  | perception of sensor data |                                     |
| associations               | associative memory   | inferior temporal cortex (ITC)      |
| **modintelligence**        |                      |                                     |
| behavior                   | rational intentions from perception |                                     |
| motor                      | effectors control    |                                     |
| **svcdb**                  | persistence services |                                     |
| **svcio**                  | internal communications | JMS/COM-style                       |
| **lib**                    |                      |                                     |
| libgen                     | low-level generic algorithms and data primitives |                                     |
| libnn                      | neural networks of various types | HMM, ANN                            |
| libbn                      | belief networks      | HTM                                 |

**Major Diagram Features**:

  * Diagram is the same for biological human and for artificial life
  * Body is regarded as consisting of non-overlapping brain, physiology and biology parts
    * **physiology** - physiological part is not having any information processing, but serve for direct converting neural signals to musculus changes or transform light into eye signals (not including any pattern processing, capture only); in aHuman it can be created as hard-coded, non-adoptable software without loss of Artificial Life features
    * **biology** - non-brain biological part represents human component and subsystems, which implement human as biological being - reproductive system, feed subsystem, blood subsystem and others; in aHuman it has meaning only for functions that link brain and body - like metabolism, pain feedback
    * **brain** is a biological part intended to support mind operations; in aHuman it is represented by computer science solutions and algorithms based primarily on connectivists principles
  * Mind on brain
    * mind is shown as cognition and intelligence functions, implemented on brain
    * several functions were identified by software model of brain