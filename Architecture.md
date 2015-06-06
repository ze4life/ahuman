[Home](Home.md) -> [Architecture](Architecture.md)



---


# High Level Architecture v3 #

## Overall Architecture ##

aHuman architecture is based on biological model.
See [BiologicalLifeResearch](BiologicalLifeResearch.md).

aHuman framework contains below high-level modules:

| **Module** | Name | **Implements** | **Notes** |
|:-----------|:-----|:---------------|:----------|
| ACTUATORS  | aWee, aYou, aPets, aHuman | set of Sensors and Effectors for different targets | Can interact with external world; there can be different sets of actuators, aPets or aWee can be test/trial one for prototyping aHuman |
| MIND       | mind | intelligence and feeling | in biological model includes brain, feeling components and all tracts |
| PLATFORM   | platform | generic software application functions | contains library components shared across different aHuman executable targets or specific auxiliary executable targets |
| TOOLS      | tools | generic auxiliary executables | using platform and libraries, multiple utilities combined in one executable, like cvs/svn/p4 |
| LIBRARY    | library | ready-to-use libraries | can be project-generated library or external library; other modules are using only binaries and headers |

Possible executables:

  * any actuators set, combined with MIND, PLATFORM and LIBRARY components
  * TOOLS combined with PLATFORM and LIBRARY components
  * executable LIBRARY components

Resulting high-level architecture model is below one:

![http://ahuman.googlecode.com/svn/images/wiki/development/hla-v3.jpg](http://ahuman.googlecode.com/svn/images/wiki/development/hla-v3.jpg)

## Mind HLA ##

Mind is a sole part of aHuman and has its own layered HLA:

  * See [MindArchitecture](MindArchitecture.md)
  * mind component hierarchy can be sliced to present optimal level of functional items - set of mind regions
  * consider all the mind regions and links as produced by specific set of mind services, where one service is aimed to create specific set of circuit patterns in order to implement specific mental function
  * mind area is a group of mind regions and their links which are produced by specific mind service
  * neurolink implements excitatory and inhibitory neurotransmitters and neuromodulators, resulting in different timing and mode of signal propagation

| **Layer** | **Key Components** | **Implements** |
|:----------|:-------------------|:---------------|
| mind target | MindTarget, MindSensor, MindEffector | Mind target framework and lifecycle. Provides facade interfaces to specific target, isolates of mind and platform design |
| mind service | MindService, MindNet | High-level mind construction and service lifecycle implementation, factory for specific mind components, establish and maintain wide neural networks. Handles mind birth, growth and wake/sleep cycle |
| mind area | MindArea and specific areas in unified aHuman mind | Lifecycle of mind areas, regional nature and structure of unified mind. Sole mind architecture based on underlying technologies of next layers |
| mind region | MindRegion and specific region types of cytoarchitecture | Connectivity architecture of specific mind tissue types - cortex, nuclei and nerve system. Based on low-level neural components |
| mind matter | NeuroSignal, NeuroPool, NeuroLink and specific implementations according to neurotransmitter systems | Neuron types, neural networks, neurotransmitters. Effective representation of low-level mind state |
| auxiliary mind objects | MindAreaLink, MindRegionLink, MindActiveMemory, MindMessage, MindSpace, MindLocation, MindMap | Principal mind connectivity and thought flow. Effective execution of network signal propagation. Geometry of the mind - one more real dimension in brain modeling |

## Platform HLA ##

Platform contains multiple services and split on HLA level to components as well:

| **Component** | **Main Class** | **Implements** | **Depends on** |
|:--------------|:---------------|:---------------|:---------------|
| services      | ServiceManager | base types, plain and template classes, logging, exception handling, service and platform lifecycle | -              |
| environment   | EnvService     | Handling environment, including configuring, deployed instance, operating system and other available resources | -              |
| objects       | ObjectService  | Unified objects and object persistence, object types | -              |
| math          | MathService    | Specific mathematical calculations | -              |
| persisting    | PersistingService | Persistence of memory in filesystem space | objects        |
| threads       | ThreadService  | multi-threading environment, CPU management, performance monitoring | objects        |
| messaging     | MessagingService | Internal decoupling mechanism to arrange manageable numerous interactions among components | objects, threads |
| media         | MediaService   | Communicating with external world using standard protocols with non-aHuman services or internal aHuman protocol with aHuman tools | objects, threads, messages |
| scheduling    | SchedulerService | Running configured tasks regularly | objects, threads, messages |
| statistics    | StatService    | Collecting performance statistics | objects, scheduling, messages |
| adminapi      | AdminApi       | API to access internal aHuman components and run tests or specific operations | media          |
| testing       | TestService    | Testing and debugging support | objects, messaging |

## HLA State and Development ##

  * rates: 1-5

| **Layer/Module** | **Design Rate** | **Code Rate** | **Advances and TBD** |
|:-----------------|:----------------|:--------------|:---------------------|
| ACTUATORS        | 2 **focus**     | 2 **focus**   | **adv**: unified sensor model, filesyswalker, **tbd**: overt and covert attention, digital-neural protocol |
| MIND             |                 |               |                      |
| mind target      | 2               | 1 **focus**   | **adv**: separated by design, **tbd**: full lifecycle implementation in HLAv3 |
| mind service     | 3               | 1 **focus**   | **adv**: biomodel, **tbd**: layered architecture, transition to HLAv3 |
| mind area        | 2 **focus**     | 1             | **adv**: cortex types, **tbd**: neocortex area design |
| mind region      | 2 **focus**     | 1 **focus**   | **adv**: HTM, reqs, features, **tbd**: complete neocortex region model |
| mind matter      | 2               | 2 **focus**   | **adv**: sourceforge cortex, fann, **tbd**: trial neocortex implementation |
| mind space       | 1               | 1             | **adv**: locations, **tbd**: - |
| mind stream      | 2 **focus**     | 2 **focus**   | **adv**: -, **tbd**: link hierarchy, HTM links |
| PLATFORM         | 3               | 3             | **adv**: life cycle, component-based code, HLAv3 codebase, **tbd**: - |
| TOOLS            | 2               | 2             | **adv**: aiconsole, **tbd**: - |
| LIBRARY          | 2               | 2             | **adv**: opencortex, fann, genrtn, chat, opencv **tbd**: - |

## Limitations ##

Feasibility Study gives us below limitations for aHuman design:

  * don't try to replicate human design exactly
  * use high-quality model of NN with 1Kb memory per neuron
  * use NNs for personality areas and knowlets for others
  * use 500K neurons in operating memory (0.05% of HI)
  * use 30K focused neurons (6% of AI NNs)
  * develop knowlets as plug-ins
    * use up to 500M in operating memory for activated knowlets (0.5% of HI)
    * remaining inactive knowlets can use up to 100Gb disk space
  * separate feeling from emotions
  * treat feeling as internal motivation system
    * use broken Markov network as a "pain" body signal
    * use sensor data consumed to adjust Markov network as "feed" body signal
    * use expected action in Markov network as internal motivator
    * curiosity is exploration action in Markov network
    * derive new "uncertainty" body signal as mismatch between expected/suggested action and actual action
  * don't create Markov networks initially, create HMM factories to construct networks
  * create learning cycle based on body signals
    * construct body reward function from body signals
    * create system of feedback recognition, train it using body reward function
    * create feedback reward function as output of feedback recognition system
    * use feedback reward function to learn all active Markov networks

## Ideas inspired by coding ##

  * mind consists of mind areas
  * mind area consists of neural networks of various types
  * single AI component is responsible for specific area and defines how it is constructed from networks - shape, used network types, sizes and inter-area links
  * brain holds mind
  * brain defines how areas are connected
  * brain contains thread pool, executing elementary operations
  * elementary operation is either network input/output calculation or link walkthough
  * any operation leads to learning - either inside one network, or inside link
  * networks can be of small typical size - e.g. 300 neurons, and thread pool can be 100 threads executing their operations and then sleeping for a while
  * networks porcessed in the same time mean "mind focus"
  * after processing focus is changed

# Stale Models #

  * [HLA version 1](ArchitectureModelInitial.md)
  * [HLA version 2](ArchitectureModelV2.md)