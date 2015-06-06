@@[Home](Home.md) -> [ArtificialIntelligenceResearch](ArtificialIntelligenceResearch.md) -> [AssociativeMemoryResearch](AssociativeMemoryResearch.md)

![http://ahuman.googlecode.com/svn/images/wiki/research/associations.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/associations.jpg)

---


Associative Memory (AM) research covers technologies enabling implementation of associative memory which enables thought process and links previous experience to novel situations.

## Technologies ##

  * Kohonen networks

## Types of Associations ##

Feel the difference between:

  * Clear concept can be restored from noisy data
  * Most related concept can be restored by its small part
  * Several concepts can be derived from feature/another concept

## Thoughts ##

**Pribram's model**

  * alternative to the transcortical model of neocortical organization
    * extrinsic sectors (primary projection areas) - neocortical areas whose fibers enter or leave the cerebral hemispheres
    * intrinsic sectors (association areas) - their fibers remain within the cerebrum
  * principal interaction of extrinsic and intrinsic systems occurs at the thalamic level
    * contribution of intrinsic neocortex to the final output of the extrinsic system is mediated by the convergence of influences from both intrinsic and extrinsic systems by subcortical mechanisms
    * intrinsic system may influence also the input of the extrinsic systems by regulation of peripheral sensory mechanisms

## Interesting Pictures ##

  * Human Memory Systems - see [link](http://www.brains-minds-media.org/archive/150/RedaktionBRAIN1120462504.52-1.png)

![http://www.brains-minds-media.org/archive/150/RedaktionBRAIN1120462504.52-1.png](http://www.brains-minds-media.org/archive/150/RedaktionBRAIN1120462504.52-1.png)

  * Cognitive Cycle - see [Link](http://www.brains-minds-media.org/archive/150/RedaktionBRAIN1120462504.52-3.png)

![http://www.brains-minds-media.org/archive/150/RedaktionBRAIN1120462504.52-3.png](http://www.brains-minds-media.org/archive/150/RedaktionBRAIN1120462504.52-3.png)

  * Generic Auto-Associative Memory - see [link](http://www.scholarpedia.org/wiki/images/thumb/d/dc/MoM-Fig1.jpg/300px-MoM-Fig1.jpg)

![http://www.scholarpedia.org/wiki/images/thumb/d/dc/MoM-Fig1.jpg/300px-MoM-Fig1.jpg](http://www.scholarpedia.org/wiki/images/thumb/d/dc/MoM-Fig1.jpg/300px-MoM-Fig1.jpg)

  * Context Binding - see [link](http://psychology.ucdavis.edu/labs/Yonelinas/images/photos/Memory%20Models%20Binding%20of%20Item%20&%20Context%20Model.jpg)

![http://psychology.ucdavis.edu/labs/Yonelinas/images/photos/Memory%20Models%20Binding%20of%20Item%20&%20Context%20Model.jpg](http://psychology.ucdavis.edu/labs/Yonelinas/images/photos/Memory%20Models%20Binding%20of%20Item%20&%20Context%20Model.jpg)

## Articles Review ##


---

#### Multi-Associative Memory in fLIF Cell Assemblies (CA) ####

see [link](http://code.google.com/p/ahuman/source/browse/research/articles/Associative%20Memory/Multi%20Association%20Memory%20-%20Huyck.pdf).

**Based on:**
  * Hebb''s Cell Assembly Theory (CA is neural basis for concepts)
  * network of biologically plausible fLIF (fatiguing, Leaky, Integrate and Fire) neurons

**Introduction, Background:**
  * hypo: Concepts are stored as CAs, associations are connections between CAs
  * concepts connected as 1-1,1-N,N-M
  * associations can be context-sensitive - retrieval of an associated concept can be based on a combination of the base concept and the context
  * AM features: priming, differential associations, timing, gradual learning and change, encoding instances (and others)

**CAs and auto-associative memory**:
  * CA theory: objects, ideas, stimuli and even abstract concepts are represented in the brain by simultaneous activation of large groups of neurons with high mutual synaptic strengths
  * **long-term memory**: neurons are learned by Hebbian rule from mutual activation, gradually assembling into CAs after repeated and persistent activation
  * **short-term memory:** CA is activated when its certain number of neurons is activated, then CA reverberates due to high mutual synaptic strengths
  * CA is a form of auto-associative memory
  * **Hopfield Model**: binary neurons, well-connected network, bidirectional weighted connections, Hebbian learning

**CAs and multi-associative memory**:
  * Psychologically, memories are not stored as individual concepts, but large collections of associated concepts that have many to many connections
  * repeated co-activation of multiple CAs result in the formation of multiple and sequential associations, and sometimes new CAs

**Multi-associative memory models**:
  * **Non-Holographic Associative Memory** (1969): well-connected network that can learn to map input bit patterns to output bit patterns; input CAs are connected to output CAs via learned one way associations
  * **The Linear Associator** (Kohonen, 1977): feed-forward, well connected network;
  * **Multi Modular Associative Memory** (1999): well connected modules, resilient to corrupted input
  * **Valiant model** (2005): random graphs, biologically implausible learning, theoretical model of memorisation and association based on four quantitative parameters associated with the cortex:
    * the number of neurons per concept
    * number of synapses per neuron
    * synaptic strengths
    * number of neurons in total
  * **Interactive activation model** (1981): each concept is represented by a node, and connections are made between nodes to show how closely related these are; not well connected
  * Finally:
    * simulated neural systems can encode multi-associative memories
    * well connected systems are not a good model of the brain
    * use partitioning the system into modules, and sparsely connected random graphs
    * there models do not account for some human characteristics, e.g. context effects

**Computation model for simulation**:

  * fLIF neural network:
```
- fLIF neurons collect activation from pre-synaptic neurons and fire on surpassing a threshold T
- on firing, a neuron loses its activation level, otherwise the activation leaks gradually:
Ait = Ait-1/d + Sum( Wij * Sj ).
d - decay factor.
- firing is a binary event, and activation of Wij is sent to all neurons j to which the firing neuron i has a connection.
- fatiguing causes the threshold to be dynamic:
t+1 = Tt + Ft.
- Ft is positive (F+) if the neuron fires at t and negative (F-) otherwise
```
  * Network architecture:
```
- network is a whole or split into several subnetworks (for some simulations)
- intra-subnet synapses are biologically inspired distance biased connections (most likely excitatory connections to neighbouring neurons)
- subnet is a rectangular array of neurons with distance organized toroidally
- inhibitory connections within a subnet and all inter-subnet connections are set up randomly
- connectivity rule for excitatory neurons; connection i->j exists if Cij=1:
Cij = 1; if r < 1/(d*v)
r - random between 0 and 1
d - the neuronal distance (value=5 works well for all simulations)
v - the connection probability
- long distance intra-network connections are inspired by biological long distance axons with many synapses
- networks are divided into multiple CAs in response to stimuli using unsupervised learning algorithms
- the CAs are orthogonal and represent different concepts, and this is based on training
```