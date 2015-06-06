[Home](Home.md) -> [Architecture](Architecture.md) -> [ArchitectureModelInitial](ArchitectureModelInitial.md)

---


## Original Model ##

Component Design Principles are:

  * All blocks separate code and functions
  * Mentioned features are allocated to blocks and are covered by several ones
  * Features that exist as consequences of denoted interactions among blocks or serving to allow development and debugging, are design features and are not described here
  * Not connected blocks are in fact connected to all blocks and provide general services

![http://ahuman.googlecode.com/svn/images/wiki/development/architecture.jpg](http://ahuman.googlecode.com/svn/images/wiki/development/architecture.jpg)

### Short architecture block explanations ###

Externals:

  * **External World**: abstraction of real world just to show its place, not going to be implemented, though can be mocked for experiments

Components:

  * **Sensors**: Items to create snapshotting specific projections of external world information and to pass corresponding streams into information processing blocks. Sensors are fixed or can be affected by effectors (e.g. we can turn head to give our eyes new view)
  * **Effectors**: Items that somehow affect external world. Process only low-level commands
  * **Command Memory**: drivers to effectors, store NNs with strategies to execute complex commands by means of low-level commands, take into account current internal (known for driver only) state of effectors and provide external (understandable by all blocks) state to operating memory
  * **Operating Memory**: current state of variables
  * **Snapshot Memory**: with a rate dependent on variable, its value is snapshotted to this block to be able to memorised
  * **Logical Memory**: a set of neural networks, representing strategies to solve tasks, comprising experience of Human creature. Uses both self-lean associative memory and knowledge plug-ins
  * **Associative Memory**: Form a binary or ternary associations to memorise snapshotted values of neural variables, based on neural networks
  * **Ready Knowledge**: knowledge plug-ins to avoid building experience from scratch
  * **Hormones**: motivations of "body", meaning here what is derived from the life form of creature
  * **Character**: a set of established internal relations, reactions, activity patterns, criteria to estimate action - like spirit

Framework:

  * **Shell**: program kernel to provide generic services like logging to all blocks and to implement life functions
  * **Channels**: special functions to establish flexible and effective information flow channels information channels between blocks, make them asynchronous, convenient if complex like video-signal and and to avoid direct calls from one block to another (except to shell or channels itself)
  * **Persistence**: file-based database to store the knowledge gained
  * **NN Library**: implementation of known algorithms for neural networks
  * **AI Library**: implementation of known algorithms for artificial intelligence

### Configuration items for development ###

To simplify development, the program could be split into below parts:

  * Part A. **Neural Networking Library**: Known Algorithms
  * Part B. **Artificial Intelligence Library**: Known Algorithms
  * Part C. **Genome**: a set of components to build a system from neural networks
  * Part D. **Sensors and Effectors Drivers**: Translate input/output data from external format into variables
  * Part F. **Framework**. Generic functions, required for any application, and life  functions of the creature
  * Part G. **Generic Library**: Generic-purpose data primitives and functions

Configuration items are defined by part:

  * Part A. Neural Networking Library
    1. **modnnlib**: NN Library
  * Part B. Artificial Intelligence Library
    1. **modailib**: AI Library
  * Part C. Genome
    1. **modheart**: Hormones, Character
    1. **modmind**: Command Memory, Logical Memory, Associative Memory, Operating Memory, Snapshot Memory
    1. **modknowledge**: Ready Knowledge
  * Part D. Sensors and Effectors Drivers
    1. **modmedia**: Sensors, Effectors
  * Part F. Framework
    1. **modengine**: Shell
    1. **moddb**: Persistence
    1. **modio**: Channels
  * Part G. Generic Library
    1. **genrtn**

### Meta Design ###

**Core paradigms for architecture**:

  * [NeuralParadigm](NeuralParadigm.md) - neural networks is chosen as principal method to represent mind functions. It is complemented by non-neural methods to arrange a system from many neural networks and to connect this system to the real world
  * [VariablesParadigm](VariablesParadigm.md) - approach to represent entities of the world in such a way that we can reference them across all modules having attached metadata available immediately, and be free to represent both simple and complex items. Items work as inputs and outputs for numerous neural networks
  * [GenomeParadigm](GenomeParadigm.md) - explains how to build multi-network step-by-step. It introduces neural variables, and uses the ability of neural networks to adopt to new inputs added when training is already done

These paradigms are combined together in below diagram, which presents a step to practical implementation of Human project:

Human is a set of neural networks, connected to sensors and effectors by means of low-level drivers, and genome services, responsible for arranging and adjusting those networks, and generic kernel for necessary but non-intelligent functions

### Open questions ###

  * Not clear whether Neural and Variables paradigms could be effective way to represent learned knowledge. Possibly it should be combined with HTM/MPF technology (research task is open in [Artificial Intelligence Research](ArtificialIntelligenceResearch.md))

### Function / Technology Map ###

| **Module** | **Technology** | **Primary Function** | **Related Problems and Algorithms** |
|:-----------|:---------------|:---------------------|:------------------------------------|
| **modmedia** |                |                      |                                     |
| connectors | hardcoded      | capture/emit signal  | chat client, video-stream, signal processing |
| sensors    | hardtuned htm  | extract variables values | vision, depth, 3d vision, narrow high resolution and wide low resolution |
| effectors  | hardcoded      | affect connectors/externals | speech generator                    |
| commands   | markov process | low-level effectors/sensors control | manupulating unkown objects, reinforcement learning |
| **modknowledge** |                |                      |                                     |
| knowlets   | belief networks | ready-to-use knowledge | associations - ready-to-use object structure and object relations as symbolic associations |
| associations | dynamic htm    | learned associative memory | object associations of any type - as derived and primary |
| **modmind** |                |                      |                                     |
| snapshots  | hardcoded      | throttle and mix to associate | sensor data                         |
| variables  | hardcoded      | primary sensor data capture | internal object values              |
| logic      | markov process | learned high-level strategies | strategies - active objects to actions, reinforcement learning |
| **modheart** |                |                      |                                     |
| feelings   | hardcoded      | internal inherent motivator | emotion vector projections          |
| character  | neural network | feedback for markov process logic | what makes character?               |