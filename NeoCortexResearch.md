@@[Home](Home.md) -> [NeoCortexResearch](NeoCortexResearch.md)

![http://ahuman.googlecode.com/svn/images/wiki/research/htm-research.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/htm-research.jpg)

---




Neocortex research covers activities to create functional and architectural requirements for building block of aHuman kernel - cortex, which is responsible for implementing intelligence and conscious behaviour in aHuman.

Research is required because neither Numenta (closed implementation, AI, not AL goals) nor open source cortex libraries (very simple, wrong direction) do not fit needs for aHuman project.

HTM/Memory Prediction theory is selected as baseline approach to implement Cortex element.
On project level Cortex is regarded as synonym to region of Neocortex from HTM theory.

Generic approach to research seems to be below one:

![http://ahuman.googlecode.com/svn/images/wiki/research/cortex/cortexprocess.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/cortex/cortexprocess.jpg)

# Terms #

**World-wide terms**

  * **cerebral cortex** = neocortex (6 layers) + some old brain structures (nuclia-based), e.g. hippocampus and olfactory cortex
  * **covert attention** - neocortex can both think about and perceive only a few different things simultaneously
  * **overt attention** - physically orienting toward some targets

**Project-level terms**

  * **cortex** - synonym to region of Neocortex from HTM theory

# Model #

## Cortex Implementation and Review ##

TBD

## Cortex Computational Model ##

  * [Computational Cortex Model](ComputationalCortexModel.md)

## Cortex Requirements ##

**Cortex as a whole**
  * cortex should take into account inputs/outputs regarding
    * sensory perception
    * sensor control / overt attention
    * covert attention in perception / expectation feedback
    * effector control
    * executive attention / temporal organization of actions
    * personality modulation
    * body feeling
    * body actions feedback
    * mental feeling
    * generating emotions
    * lifecycle modulation
  * send cortex region primary output to several targets - cortex regions or nuclei
  * linking unexpected perception to upper region attentional input

**Cortex region**
  * several inputs
  * expectation input from upward region
  * spatial unsupervised learning, generates one-step sequences
  * temporal supervised learning, used by upper layers or hippocampus
  * input projects to the whole input area, but with different density
  * specific input for emotional modulation
  * specific input for lifecycle modulation
  * attentional input
  * input priorities
  * inhibitory input
  * one primary output
  * one downward expectation output
  * HTM inside (delayed input, columns, matching, pattern building, expectation generation)

## Biological Cortex Model ##

  * [Biological Cortex Model](BiologicalCortexModel.md)

**cortex layers**

![http://ahuman.googlecode.com/svn/images/wiki/research/cortex/layerlinks.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/cortex/layerlinks.jpg)

  * see other pictures at [BiologicalCortexModel](BiologicalCortexModel.md)

## Biological Cortex Features ##

**Numbers**
  * neocortex has 10 times more feedback connections than feed forward ones
  * one neuron has max speed of 10ms
  * can recognise picture in 1 second hence having no more than 100-hop sequences
  * cortex layers
    * neocortex has exactly 6 layers
    * allocortex (almost all limbic system) - less than 6 layers
    * archicortex (hippocampus) - 3 layers
    * paleocortex (subiculum, piriform, cingulate) - 3-5 layers
  * neocortex is 2mm thick and covers both hemispheres of human's head
  * neocortex area is 0.2 m2
  * neocortex has 2-5 million neocortical columns
  * neocortex has 300-500M micro-columns
  * neocortical column has ~50K neurons
  * neocortical minicolumn has 80-250 neurons
  * neocortical columns are patches of neocortex with a diameter of about 0.5 mm and a depth of 2 mm
  * HI has 25 connections per neuron in average
  * HI operates at around 10^15 computations per seconds
  * neural density is 100K n/mm3
  * optical nerve has 1M axons
  * auditory nerve has 30K axons
  * human DNA has 20-25K genes
  * between regions, in myelin insolation, signal is spreading via axon with 200 miles/hour = 9 cm/ms
  * synapses relating to vision peak at ~10 months, density of synapses then declines and stabilises ~10 years of age
  * neocortex contains two primary types of neurons, ~80% excitatory pyramidal neurons, and ~20% inhibitory interneurons
  * corpus callosum connects left and right brain and contains 200 (men)-250M (women) axons
  * there are as many as 50 times more glia than neurons in CNS
  * action potential travels along the axon quickly, moving at rates up to 150 meters per second
  * neuron's membrane potential (resting potential) is about -70 millivolts
  * it takes 250 ms between sensor signal and conscious perception
  * cerebellum constitutes only 10% of brain by volume, but has 50% by number of neurons

**Functions**
  * unsupervised learning of abstraction hierarchies for representing the structure in the world
  * learning invariant representations
  * covers both sensors and effectors
  * uses the same algorithm with local adjustments
  * learns - to predict the future, filter unnecessary information away, generalise
  * forms associations
  * cat can live without cortex, human cannot - cortex has too much responsibility for muscles
  * cortex implements selective attention
  * cortex has long-term (episodic) memory along hippocampus
  * cortex learns about rewarding features, on par with basal ganglia
  * teaching signals are contextual inputs from the thalamus matrix cells and the neuromodulators
  * extra plasticity in critical period
  * global neuromodulation signals mediate information about rewards and punishments

**Overall neocortex use cases**

  * perception with/without training
  * expected/unexpected perception
  * conscious/unconscious perception
  * default/focused perception
  * remember episodic memory
  * direct/associative recall of episodic memory
  * sensor/motor action selection
  * sensor control in perception/motor control in execution
  * emotional perception/execution modulation
  * emotional dreaming
  * imagination

# External Research #

## External Cortex Research Review ##

  * [GrossbergModels](GrossbergModels.md) - subcortical predictive dynamics article review
  * [PrefrontalCortexReview](PrefrontalCortexReview.md) - neuroscience findings overview and implications from book by Joaquin Fuster - The Prefrontal Cortex
  * [OnIntelligenceReview](OnIntelligenceReview.md) - Insights from book by Jeff Hawkins - On Intelligence
  * [OnIntelligenceRewritten](OnIntelligenceRewritten.md) - Rewritten [OnIntelligenceReview](OnIntelligenceReview.md) page - by design components
  * [NumentaResearch](NumentaResearch.md) - Analyze results of research by Numenta
  * [CortexAttention](CortexAttention.md) - Model of covert attention in cortex
  * [InternalRepresentationResearch](InternalRepresentationResearch.md) - Produce internal representation of perceived sensor data
  * [MemoryFormation](MemoryFormation.md) - Memory formation in humans
  * [CorticalLearningAlgorithms](http://numenta.com/htm-overview/education/HTM_CorticalLearningAlgorithms.pdf) - 2011 article covering current neocortex paradigm of Numenta

## External Cortex Research Links ##

  * http://www.foresight.org/nanodot/?p=3702
  * simple features such as color, brightness, motion and form - see [amex](http://www.sciencedaily.com/releases/2007/03/070314134812.htm)

## 2010 Jeff Hawkins ideas ##

see [Link](http://www.numenta.com/htm-overview/education/jeff-2010-smithgroup-lecture.php)

  * Biology data - 5 layers (plus 1 connectivity)
    * cells in columns have similar response properties
    * majority of connections are within layer
    * feed-forward connections are few but strong
    * layers 4 and 3 are primary feed-forward layers, layer 4 disappears if ascend hierarchy
  * Hypothesis
    * common mechanism in each layer
    * each layer is a sequence memory - learns transitions of sparse distributed patterns
    * layer 4 learns first order transitions - spatial inference, simple cells
    * layer 3 learns variable order transitions - time-based inference, complex cells
    * layer 5 motor
    * layers 2,6 - feedback, attention
    * all column cells fire when not predicted
  * Real neuron
    * proximity dendrites - linear summation, feed-forward, Nx100 synapses
    * distal dendrites - dozens of regions, non-linear integration, lateral connections, Nx1K synapses
    * ongoing forming and unforming of synapses
    * variable spike rate

![http://ahuman.googlecode.com/svn/images/wiki/research/cortex/htmneuron.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/cortex/htmneuron.jpg)

  * http://www.pyung-an.com/tcm-info/Mri-acu/mri-acu.htm

![http://www.pyung-an.com/tcm-info/Mri-acu/Fig6.jpg](http://www.pyung-an.com/tcm-info/Mri-acu/Fig6.jpg)

![http://www.pyung-an.com/tcm-info/Mri-acu/Fig7.jpg](http://www.pyung-an.com/tcm-info/Mri-acu/Fig7.jpg)

  * http://www.frontiersin.org/computational_neuroscience/10.3389/fncom.2011.00001/full

## Open Source Libraries ##
  * https://wiki.aalto.fi/display/SYNB/Neocortex
  * Source Forge Neocortex http://neocortex.sourceforge.net/
  * OpenCV http://opencv.willowgarage.com/wiki/
  * iLab http://ilab.usc.edu/toolkit/