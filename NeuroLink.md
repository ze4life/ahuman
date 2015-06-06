@@[Home](Home.md) -> [Architecture](Architecture.md) -> [MindArchitecture](MindArchitecture.md) -> [NeuroLink](NeuroLink.md)



---


## Services ##

  * NeuroLink implements bundle of fibers
    * each fiber corresponds to part of axon starting after initial axon segment (which can be modulated by connection) and includes all axon endings, while dendrite with its receptors is part of NeuroPool (set of neurons)
    * one fiber is connected to the only source neuron
    * one fiber is connected to the set of destination neurons topologically close to each other (receptive field)
  * NeuroLink implements neurotransmitter which affects:
    * transmission speed
    * affected receptors
    * receptor thresholds
  * NeuroLink takes into account receptive field effect
  * NeuroLink implements Hebb's learning

## Implementation ##

  * NeuroLink connects MindRegion to MindRegion
    * MindRegion can be specific MindSensor, MindEffector or standard mind regions
    * each pair of interconnected regions can have several NeuroLink items representing connections of different region parts with specific projection properties
    * interface to source part of region is NeuroLinkSource
    * interface to target part of region is NeuroLinkTarget
    * when MindMessage delivers NeuroSignal to specific region referencing NeuroLink, region can decide to use default NeuroLink projection logic to apply NeuroSignal to specific NeuroPool within MindRegion
    * cortex inter-layer connections can be be specified as NeuroLink set
    * implements intra-cortical, cortico-cortical, cortico-nuclei, inter-nuclei connections
    * signal flows across NeuroLink in one direction
    * source NeuroPool and destination NeuroPool can be of the same or of different MindRegion
  * NeuroLink uses the same neurotransmitter for all fibers
  * one event - one transmission across all fibers
    * activation blocks fired axon branch for a certain time
  * each destination cell has equivalent receptive field - representing set of incoming fibers
    * strength of connections (weights) is part of NeuroPool information but not NeuroLink
    * affected neuron is selected by receptive field size and maximum action potential
  * NeuroLink does not store individual axons
    * NeuroLink is stateless
    * NeuroLink stores only properties of mapping
    * source and destination neurons are selected dynamically based on topological projection
    * axon terminal branches are replaced by destination neuron receptive field state set, which accumulates action potential until threshold
  * NeuroLink ends are 2-dimensional rectangular areas
    * areas can be of different size
    * related NeuroPool can have complex 3-dimensional physical form and size, but it should provide rectangular input or output interface