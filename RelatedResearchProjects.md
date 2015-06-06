@@[Home](Home.md) -> [RelatedResearchProjects](RelatedResearchProjects.md)

![http://ahuman.googlecode.com/svn/images/wiki/research/flying-saucer.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/flying-saucer.jpg)

---


This page is intended to collect the information regarding all projects related to artificial life or artificial intelligence.


---



# General References #

  * [Wikipedia - List of artificial intelligence projects](http://en.wikipedia.org/wiki/List_of_artificial_intelligence_projects)
  * [Artificial Intelligence Implementations](implementations.md)
  * [Contributors](contributors.md)

# Categories #

## Interesting Videos ##

  * [Monica Anderson: "A New Direction in AI Research" at Foresight 2010 Conference](http://vimeo.com/9508466)
```
Eye:
Subconscious - Undestanding - 10MBit/sec
Conscious - Reasoning - 100 bits/sec.
```
  * [Milo, the Artificial Intelligence Boy](http://www.metacafe.com/watch/2959176/life_on_line_9_milo_the_artificial_intelligence_boy/)

## Chats ##

  * [iGod](http://www.titane.ca/concordia/dfar251/igod/main.html)

## Full-Scale Frameworks ##

  * [Blue Brain Project](http://bluebrain.epfl.ch/) - the first comprehensive attempt to reverse-engineer the mammalian brain, in order to understand brain function and dysfunction through detailed simulations
```
Computer simulations in neuroscience hold the promise of dramatically enhancing the
scientific method by providing a means to test hypotheses using predictive models of
complex biological processes where experiments are not feasible. Of course, simulations
are only as good as the quality of the data and the accuracy of the mathematical
abstraction of the biological processes. The first phase of the Blue Brain Project
therefore started after 15 years of systematically dissecting the microanatomical,
genetic and electrical properties of the elementary unit of the neocortex – a single
neocortical column, which is a little larger than the head of a pin. From the data
gathered from 15,000 experiments in rat somatosensory cortex, it became possible to begin
constructing a model of this part of the brain.

The project has focused, however, not only on building a model of the neocortical column,
but on developing a generic facility that could allow rapid modeling, simulation and
experimentation of any brain region, if the data can be measured and provided according
to specifications. The facility has been used to build the first model of the neocortical
column, which consists of 10,000 3D digitizations of real neurons that are populated with
model ion channels constrained by the genetic makeup of over 200 different types of
neurons. A parallel supercomputer  is used to build the model and perform the experiments
so that the behavior of the tissue can be predicted through simulations.

With the present simulation facility, the technical feasibility to model a piece of
neural tissue has been demonstrated. The next steps will involve expansion of the project
in two directions. First, the Blue Brain team is intensifying its efforts to extend the
facility to support modeling of the subcellular domain, which will integrate additional
levels of biological detail into the existing neocortical column model. Incorporating the
molecular level structures, processes and effects is an important step towards
pharmacological and medical research “in silico”. Second, the facility will be extended
to integrate details of larger portions of cortex and other brain structures. Ultimately,
given additional resources, the facility can be extended to permit whole brain modeling,
simulation and experimentation. 
```
  * [Biota.org](http://www.biota.org) - The Artificial Life Project
```
Biota.org was created in 1996 to promote and assist in the engineering of artificial life: complete, biologically-inspired, synthetic ecosystems and organisms.
This involved the creation and deployment of digital tools and environments for simulation, research, and learning about living systems both natural and artificial.
These tools ranged from simple genetic algorithms to full multi-user virtual environments.
The dissemination of interdisciplinary concepts is an important aspect of promoting the field of artificial life.
To this end, Biota.org welcomes members from all scientific disciplines including
evolutionary science, microbiology, medicine, computer science, robotics, nano-technology, palaeontology, social science, and artificial intelligence.
Biota also encourages artists, technologists, philosophers, and educators to join in and
add their input to the developing body of experimental work. 
```

  * [Noble Ape](http://http://www.nobleape.com), [nobleapesim](http://code.google.com/p/nobleapesim) - create a detailed biological environment and a cognitive simulation
```
It features a number of autonomous simulation components including a landscape simulation, 
biological simulation, weather simulation, sentient creature (Noble Ape) simulation and 
a simple intelligent-agent scripting language (ApeScript). 
The cognitive simulation is relatively central to the hardcoded version of 
the Simulation and optional (on by default) in the ApeScript version of the sentient simulation. 
This gives some freedom in the agent simulation method used through ApeScript. 
Advanced ApeScript users may turn the cognitive simulation off and uses the "brain space" as actual memory.

The landscape (physics) and weather simulations are autonomous components of the Noble Ape Simulation too. 
The weather simulation can work in either flat or spherical environments similar to the landscape simulation.

The biological simulation is based on quantum mechanics.
The landscape shape (height values, surface area, slopes, angle to simulated sun) 
can be the source of all the biological properties of the environment.
This means for any landscape, a (long term) stable biological environment can exist and
include a wide variety of plants and animals in the simulated ecosystem. 
```

## Soft/Cognition ##

  * [OpenCV](http://opencv.willowgarage.com/wiki/) - a library of programming functions for real time computer vision
```
OpenCV is released under a BSD license, it is free for both academic and commercial use.
The library has >500 optimized algorithms (see figure below).
It is used around the world, has >2M downloads and >40K people in the user group.
Uses range from interactive art, to mine inspection, stitching maps on the web on through advanced robotics. 
```

  * [Source Forge NeoCortex](http://neocortex.sourceforge.net/) - An implementation of memory-prediction framework applied for image recognition. Based on Jeff Hawkins' book On Intelligence
```
It models the high-level hierarchical architecture of human neocortex and uses Bayesian belief revision for making predictions
```

  * [Implementation of HTM](http://code.google.com/p/htm)
```
This software is based upon or includes certain works and algorithms related to hierarchical temporal memory ("HTM") technology published by Numenta Inc. 
```

## Soft/Connectivism ##

  * [aamas08](http://code.google.com/p/aamas08) - assignment of the Autonomous Agents and Multi Agent Systems (AAMAS) course of the MAPi joint doctoral program
```
Objective:
 * Use a recurrent neural network to control the movements of a tadpole, swimming in a pond. 

Current Features:
 * Homeostasis
 * Proprioception
 * Neural Plasticity
 * Data Logging
 * Various kinds of charts
     o Neural Evolution
     o Neural Connections
     o Neural Histogram
     o Timeseries charts
     o 2D Macro Visualization 
 * Flexible Interface (charts can be maximized, closed and dragged around) 
```
  * [Joone](http://www.jooneworld.com/) - Neural net framework written in Java(tm)
```
It's composed by a core engine, a GUI editor and a distributed training environment and
can be extended by writing new modules to implement new algorithms or architectures starting from base component
```

## Soft/Evolution-related ##

  * [Polyworld](http://sourceforge.net/projects/polyworld) - one of the earliest and one of the most sophisticated artificial worlds developed to study Artificial Life and Artificial Intelligence
```
Polyworld is a computational ecology that I developed to explore issues in Artificial Life. 
Simulated organisms reproduce sexually, fight and kill and eat each other, eat the food that grows throughout the world,
and either develop successful strategies for survival or die.
An organism entire behavioral suite (move, turn, attack, eat, mate, light) is controlled 
by its neural network "brain". 

Each brain architecture - its neural wiring diagram - is determined from its genetic code, 
in terms of number, size, and composition of neural clusters (excitatory and inhibitory neurons) and 
the types of connections between those clusters (connection density and topological mapping). 
Synaptic efficacy is modulated via Hebbian learning, so, in principle, the organisms have the ability 
to learn during the course of their lifetimes. 
The organisms perceive their world through a sense of vision, provided by a computer graphic 
rendering of the world from each organism point of view. 

The organisms physiologies are also encoded genetically, so both brain and body, and
thus all components of behavior, evolve over multiple generations. 
A variety of "species", with varying individual and group survival strategies have
emerged in various simulations, displaying such complex ethological behaviors as
swarming/flocking, foraging, and attack avoidance.
```
  * [floatworld](http://code.google.com/p/floatworld) - neural-network based artificial life environment for simulating evolution
```
Floatworld is an artificial life environment in which 'creatures' compete for space and energy. 
Each creature is controlled by a neural network, and harvests energy in order to reproduce. 
Random mutation and natural selection result in the evolution of different strategies.
```
  * [simulution](http://code.google.com/p/simulution) - Evolution Simulation
```
Simulution is a project designed to emulate evolution of various life forms through simple defined rules and AI logic.
In contrary to traditional applications, the interaction and development of the life-forms living in this world will be presented in a real-time feed through a web browser. 
```
  * [genobots](http://code.google.com/p/genobots) - creating life++
```
RoboCom-like project with evolution
```

## Soft/Colony life ##

  * [flockediflock](http://code.google.com/p/flockediflock) - flocking algorithms
```
Giving a go on flocking algorithms, rendered by a very basic 3d engine.
The aim is to gain understanding of the workings of flocking.
This project should at its term contain preys and predators that will switch behaviors depending on the situation.
```
  * [brainbugz](http://code.google.com/p/brainbugz) - Behavioural Animation System for Maya Particles
```
Brainbugz is a set of Maya nodes which allow you to control particles using common artificial life techniques.
```
  * [yajalife](http://code.google.com/p/yajalife) - Yet another Java artificial life simulator
```
Roving computer programs seek out resources (CPU cycles) on a 2-D grid, in order to generate imperfect offspring.
Evolution occurs. This was inpired by the popular Avida alife program.
```
  * [velaldin](http://code.google.com/p/velaldin) - The Vélaldin framework is a development environment for emergent phenomena and complex system simulations.
```
Vélaldin is an open-source engine for developing structures with emergent properties.
Based on the basic concept of cellular automata, Vélaldin offers a new approach to emergence research through an abstract representation of cells —
leaving it up to the developer to determine the features, rules and states of cells in whatever way is required. 
```

## Hard ##

  * [Human AI Project](http://www.humanaiproject.org/) - Informational page concerning Human Artificial Intelligence and robotics.

  * [Neurorobotics](http://www.scholarpedia.org/article/Neurorobotics) - Brain-based device with a simulated cerebellum for predictive motor control

## Wet ##

  * [cyberneticbacteria](http://code.google.com/p/cyberneticbacteria) - an art project involving communicating bacteria, RFID tags, bluetooth phones and an artificial life simulation
```
The world’s first "prokaryotic scale free network" has been initiated. 
The scientist, unconcerned with the ethical implications of his experiment and also unaware of the artist’s intentions, 
never anticipated that the fusion of the Earth’s global bacterial communications network,
with that of human origin would lead to the evolution of a novel and chimeric life form.
A new kind of pathogen mutated by the Bluetooth, RFID and Packet Data surveilled in the gallery.
Dublin became the centre of the epidemic, and the origin of a new life form able to subvert both biology and technology.
What followed was inevitable.
What else would a creature with access to: humanity’s entire digital knowledge; the genetic toolbox that drives evolution;
the sophistication of the pathogen; and intimate awareness of our vulnerabilities do? 
```

## Microworlds ##

  * [elsass](http://code.google.com/p/elsass) - 2D artificial life ecosystem simulation
```
Simulates 2D terrain water flow, weather, plant growth as well as animal senses and behavior.
Uses Chipmunk physics library and Clanlib for GUI. This is not your typical "matrix of colorful pixels" alife simulation. 
More like aiming to be environment for persistent and meaninful video game world.
```
  * [ekology](http://code.google.com/p/ekology) - an ecosystem simulation framework
```
EKology is a Java framework to create simulations of any modelled ecosystem.
It can be used for model & final state machine testing and optimization, visual simulation or just for fun :).
As part of my final thesis I developed not only the framework itself, but also a version of the fungus eater problem.
Here the proposed solution is based on artificial life and evolutionary processes.
```
  * [efall](http://code.google.com/p/efall) - Egedede Free Artifical Life Lab
```
The aim of this project is to create a world where "animals" will live. The aim is to make them free as possible. 
They should have a brain. They would reproduce with each other 
```

## Misc ##

  * [ob-flash](http://code.google.com/p/ob-flash) - an artificial chemistry puzzle and experimentation kit, implemented in Flash
```
A 2D world of bouncing atoms is directed by adding simple reactions, such as:  a3+b7 -> a4b4
With the right reactions you can create replicating molecules and evolution.
ob-flash is still at a very early stage. There's a moving prototype here but that's about it. 
```
  * [freality](http://code.google.com/p/freality) - lots of experimental code on a variety of subjects. Some highlighted packages:
```
ai
 - control networks
 - pattern matching 
al
 - genetics 
logic (predicate logic statements)
ml (machine learning)
 - backpropagation neural network
 - naive bayes 
social
 - economics
 - highway traffic 
```