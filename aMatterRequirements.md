@@[Home](Home.md) -> [ProjectPlanning](ProjectPlanning.md) -> [aMatterRequirements](aMatterRequirements.md)

Contents:


---


# Overall Features #

## Mocked Functions ##

  * M-01. **aMatter** has <font color='green'>primitive predefined set of effectors</font>**producing representation in external world based on**<font color='green'>predefined set of low-level commands</font>**provided by hardcoded motor strategies
  * M-02.**aMatter**limits effectors actions to ones**<font color='green'>explaining internal representations</font>**by means of**<font color='green'>hardcoded symbolical language</font>*** M-03.**aMatter**has**<font color='green'>primitive predefined hierarchy of behavioural strategies</font>**, on leaf level directly connected with effectors commands**

## Cognition ##

  * C-01. **aMatter** receives information using <font color='green'>predefined set of sensors</font>*** C-02.**aMatter<font color='green'>recognises</font>**received information in real-time mode and calculates recognition**<font color='green'>metric R</font>**reflecting percentage of successfully recognised sensors inputs in given environment
  * C-03.**aMatter<font color='green'>generalises</font>**unrecognised inputs so that R monotonously increases for the same static environment
  * C-04.**aMatter**forms growing set of internal entities, so that specific subset of**<font color='green'>internal entities</font>**, when being in active state, can be treated as a representation of specific external data from sensors, disregarding whether previously perceived or internally inspired
  * C-05.**aMatter**is able to**<font color='green'>forget</font>**internal entities, if not activated for a long time, so that the same input**<font color='green'>triggers</font>**another set of internal entities after a while
  * C-06.**aMatter**forms growing set of**<font color='green'>associations</font>**between internal entities activated about the same time**

## Feeling ##

  * F-01. **aMatter** collects information from <font color='green'>predefined set of embodiment signals</font>**equivalent in purpose with human being, with body treated as related operating system process with all its inherent features and properties
  * F-02.**aMatter**collects**<font color='green'>predefined set of uncertainty metrics</font>**from expectation flow of behavioural strategies**

# Goals Achievement #

## Perception/Self-Learning features ##

### Perception ###

  * Effective Signal Processing
    * MindSensorArea - receptive field averaging and inhibition
    * ThalamusArea - create relay sensory nuclei - **done**
    * ThalamusArea - create inhibitory NeuroPool - **done**
    * Connect PerceptionArea feedback and inhibitory NeuroPool - **done**
    * Connect internal InhibitoryLink from relay NeuroPool and inhibitory NeuroPool - **done**
    * Implement realistic inhibitory properties (150ms inhibition vs 20 ms excitatory non-firing interval)
  * Functional value
    * implement sampling
    * implement subsampling

### Self-Learning ###

  * Mock cortex implementation - to allow development of other components
    * create feed-forward NeuroPool - **done**
    * create spatial pooler - process feed-forward signal from ThalamusArea - **done**
    * create temporal pooler - process fixed-size sequences and derive predicted spatial pooler item - **done**
    * create feedback NeuroPool - **done**
    * apply temporal pooler prediction to feedback NeuroPool and generate cortex feedback signal - **done**
  * Cortex implementation
    * Columnar processing
    * Hierarchical Processing
    * Infinite Temporal Prediciton
    * Focus Processing
    * Attention Processing
    * Event Driven Implementation
  * Functional value
    * implement high-probability predictive sampling and subsampling

## Cognition as Meaningful Sensor Control ##

  * saccadic scene scanning, spacial into temporal-spatial approach
  * novelty, motavation, attention
  * virtuality

## Demonstrate Feeling Feature ##

  * TBD

## Real-Time Neural Networks ##

  * Neural Structures
    * NeuroPool - accumulate arriving action potentials in membrane potential - **done**
    * NeuroPool - time-based dissolving of membrane potential - **done**
    * NeuroPool - postpone firing to minimum time interval after last firing - **done**
  * Signal Processing
    * ExcitatoryLink - project excitatory signal to NeuroPool - **done**
    * ExcitatoryLink - generate excited signal from projection - **done**
    * NeuroSignal - store only activated source items - **done**