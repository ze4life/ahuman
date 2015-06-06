@@[Home](Home.md) -> [SensorsResearch](SensorsResearch.md) -> [CortexAttention](CortexAttention.md)


---


**Attention in the Neocortex**

see 2007 - Model of covert attention and learning

# 2. Background #

## 2.1 Mammalian Neocortex ##

### 2.1.1 Overview of the cortex ###

  * cerebral cortex is neocortex and old structures like hippocampus
  * most intelligent animals have larger absolute and relative neocortex
  * neocortex is responsible for things such as processing sensory information, learning associations, consciousness and working memory (compare to Jeff Hawkins - neocortex is responsible for prediction)
  * after evolution it receives input from all sources and thus can build world model
  * independently of the location on the cortex, it has the same six-layered columnar structure and the same micro-connectivity

### 2.1.2 Learning Feature Representations ###

  * exceptional feature of the motor cortex is that it has power to control the muscles
  * higher levels represent longer lasting actions that are more abstract and consist of many primitive actions
  * when motor cortex attends to some actions, the muscles actually perform those actions
  * when an animal attends to some features in its sensations, the neural representations even in the lowest cortical levels adapt mostly to those features and not to others
  * feedback connections could also help in relating the neural representations to their context and thus give meaning to the raw bottom-up data
    * if the context does not change when the inputs change, the context could teach the neuron that the different inputs are actually instantiations of the same object
    * feedback connections could act as teaching signals for the neurons

### 2.1.3 Attention in Neocortex ###

  * sensory cortex cannot represent all objects existing in the inputs at the same time - there is selective attention
  * neocortex can think about and perceive only few different things simultaneously (covert attention)
  * possible reasons of attention limitation:
    * **neuron has much synaptic information but little activity information** - active state cannot represent all the knowledge of the neuron simultaneously
    * **binding problem** - one simple feature can take part in representing many different things; when two population codes overlap, the features between the objects can get mixed up; the right combinations of features can be found if only few objects are attended at once; the simulated reality must be kept apart from the real world, and different future plans must be kept from interfering with each other
    * invariant reference frame for pattern recognition - the same objects can appear in many different forms (weak)

  * targets of attention are selected based on bottom-up saliency and high-level intentions
  * **saliency** can be:
    * high contrast
    * good continuity
    * unexpectedness - in spatial or temporal context; dangerous or new opportunity
    * attending to salient targets can be reasonable for alive being - improves probability of having real object

  * high-level **intentions** can be:
    * search for certain objects from the visual field
    * can be controlled to target any kind of features, like spatial locations or auditory frequency bands
    * top-down control signals are thought to originate in the **frontal cortex**

  * **biased-competition model of attention** - all attention emerges from local competition between different features in the neural hierarchies; this competition can be biased with top-down signal, allowing for search of certain features
    * competition between different spatial locations works similarly to that between different features
    * if a certain object is given attentional bias, then the location of that object is searched for
    * if the bias is given to some location, then the cortex will recognise the possible object in that location

### 2.1.4 Architecture of Neocortex ###

  * **connections**
    * 1st-order: thalamic -> inputs (layer 4) -> contextual (layers 1-3) -> outputs (layers 5-6) -> higher-order thalamic
    * higher-order: thalamic -> inputs -> contextual -> outputs -> ...

  * **minicolumns** form larger **columns** and **hypercolumns**
  * all neurons within one minicolumn respond roughly to similar stimuli
  * **suggestions**:
    * some layers could represent the true state of the world
    * other layers could represent unexpected novelties
    * some layers could form laterally coherent feature aggregates between neighbouring columns

  * crucial connection type is **feedback connections**
    * more numerous than the bottom-up connections
    * cannot cause activations in the target neurons, but only modulate the activations
    * originate from the near surroundings of that area
    * important set of connections is feedback from the next hierarchical level

  * great amount of contextual input into layer 1 comes from special context mediating **matrix cells** in the thalamus
  * bottom-up circuitry from thalamus to inputs layer (4), to contextual layer (2,3), to outputs layer (5,6) and back to thalamus consists of excitatory neurons
  * **inhibitory connections** can:
    * take part in regulating the activations in the cortex
    * implement competition between excitatory neurons
    * implement contextual “explaining away” of local neural representations

  * there are more global signals, carried by **chemical neuromodulators**, that affect large parts of the cortex similarly; they can modulate both the plasticity and activations in the neurons
    * control learning and memorising
    * control the balance between bottom-up and top-down inference
    * gate the contents of working memory

### 2.1.5 Purpose of Neocortex ###

  * lots of learning happening in the subcortical structures as well
    * **basal ganglia** are considered to do **reinforcement learning**, which means learning those motor actions that are rewarding
    * **cerebellum** learns to contract the muscles on just the right time instants, resulting in **anticipative actions** and **smooth control**

  * cortex learns invariant representations for the complex information in the raw sensory data
  * additionally to representing the world state, it performs motor actions itself and plans the future
  * cortex incorporates the goals of the animal into its world model, and can thus make good action decisions:
    * motor cortex perceives what the animal does - cortex can associate the evolutionary fixed action patterns to different situations
    * global neuromodulation signals, such as dopamine, mediate information about rewards and punishments
    * working memory in the prefrontal cortex is thought to be gated by subcortical structures, which focuses attention on the animal goals

## 2.2 Models of learning regularities in the world ##

  * cortex is often modelled as using unsupervised learning
  * real cortex does receive teaching signals: the general contextual inputs from the thalamus matrix cells and the neuromodulators

### 2.2.1 Generative models ###

  * generative models try to infer the original causes underlying the sensations
  * generative models assume a physical model F that produces the sensory inputs x:
```
x = F(s) + n
s - the physical causes, vector s can include information about the history of the world
n - sensory noise
```
  * generative models try to learn the world model F, and then use this in inferring the causes s from the inputs
  * **Bayesian network** is example of generative model, hierarchical statistical model
    * can be used to infer the abstract causes from partial sensory inputs
    * inference is computationally demanding

  * **Helmholtz machine**
    * inference/recognition can be done with one feed-forward activation sweep if distinct recognition model is added alongside the generative model
    * recognition model is consistent as learnt at the same time with generative model

  * error function can be the Kullback-Leibler divergence between the real sensory input probability distribution and that of the learnt generative model
  * for dimensionality of real world accurate generative model would be immensely large and slow to learn
  * generative models do not take into account the importance of different real world objects, or causes
  * cortex of the animal must decide what to represent
  * optimal way to make decisions is to maximise the expected utility of the consequences of the actions, leading to **Bayesian decision theory**
    * actions could be the decisions about what objects to represent
    * utilities are the utilities of representing different objects in the case they really exist in the current world state
    * utility of representing an object should be higher for those objects that are relevant for the behaviour of the animal

  * **cortical neural networks** must use information about the utility in two different time scales
    * synaptic weights of the network should be used to represent those aspects of the world that are important (concerns learning and corresponds to the **longer time scale**)
    * faster time scale corresponds to attention - select those targets that are the **most relevant**, for example dangerous or favourable

### 2.2.2 Learning features ###

  * hierarchical pattern recognition network - higher level in the hierarchy learn increasingly invariant, abstract and global features and objects
  * **Neocognitron**
    * able to recognise visual objects despite their location in the picture
    * has a growing translational invariance when moving upward in the hierarchy - by alternating simple-cell and complex-cell layers
    * simple cells represent different features in their inputs
    * complex-cell layers make a dimension reduction by grouping simple cells with the same features in different locations together - complex feature is invariant with respect to the location
    * after dimension reduction, the next levels receive inputs from a larger areas - number of inputs into each area does not vary much; so additionally to higher invariance in higher layers, the units in higher layers also code for larger, more global shapes
    * if learn with **Hebb rule**, choose direction in the multidimensional input space which contains the most variance, or energy - but no reason why the most variant feature in the inputs would be generally the most useful one

  * **Independent component analysis** (ICA) tries to extract statistically independent features from the inputs
    * representing independent features and objects explicitly in different neurons is useful
    * when different neurons learn from the same inputs, they should do not all learn the same features
    * to drives the features apart: **competitive learning** (only the most active neurons learn - e.g. SOM) and **decorrelation**
    * to avoid decreasing information - **adding conscience** - frequent winners decrease their probability to win subsequent competitions
    * decorrelation means removing the correlations between the neural activations

### 2.2.3 Guiding learning with context ###

  * Hebbian-like trace-learning rule:
```
dw = x * y`, 
y' is a leaky integrator of the neuron’s activation
even if y goes to zero, the activation stays on for a short time in y'
```
  * recognition of certain objects in one time instant guides classifying the next inputs to the same objects - slow feature analysis (SFA)
  * spatial context can mediate information both within one sense and from other senses
  * learning of behaviourally meaningful aspects of the world
    * contextual information from the motor cortex could help all the other parts of the cortex to learn motorically relevant representations
    * contextual signals from the subcortical structures could allow for relating primitive emotional and instinct information to the cortical representations

  * matrix cells in the thalamus are known to mediate **very general contextual** information to all parts of the cortex
  * lateral and top-down feedback connections in the cortex itself probably mediate much contextual information between different cortical areas
  * **denoising source separation** (DSS) - generic feature learning framework
    * sparse ICA, SFA and CCA components can be learnt with DSS
```
1. Sphere the inputs.
2. Extract activations of features from the inputs.
3. Use prior information about the features to denoise the activations.
4. Adapt the features with the denoised activations in Hebbian style. Keep the feature vectors as unit length.
```

## 2.3 Models Of Attention ##

### 2.3.1 Dynamical neural networks ###

  * cortex is not a static feature extractor or a pattern recognition system, but dynamical system
  * state of the cortex affects perception
    * past inputs affect perception, because the cortex can do **temporal pattern recognition**
    * cortex has its own **intentions**

  * **Helmholtz machine through time** - temporal pattern recognition network; feed-forward fashion - has a “state”, but the higher layers do not have any effect on the lower ones
  * **hierarchical predictive-coding models**
    * class of models which use top-down connections alongside bottom-up ones to analyse both static and temporal inputs
    * each level tries to predict the activations in the lower levels, which then send the prediction error back to the higher levels
    * network converges to a state where the prediction error is minimised at each level
    * explain **extra-classical receptive fields**, such as those of **end-stopping cells** in V1
    * hierarchy in these models can integrate information temporally and spatially
    * neurons make compromise between the **lower level error**, the **current activation** and the **prediction from the higher layer** - leads to holistic, coherent interpretation of the inputs in a Gestalt style
    * neurons do not feed their actual activations, but only the prediction errors, to the higher layers - these neurons are experts in **focusing attention to novel features** in the world
    * they try to learn everything in the inputs equally well - do not have attention.

### 2.3.2 Controlling the targets of attention ###

  * visual attention modelled using **predefined bottom-up saliency** for the targets
    * new input (image) is first filtered with some constant filters (e.g. low pass filters with dimension reduction, detectors of discontinuities in the colour hues), which notice **salient locations** in the image
    * attention can select the most **salient location first**; then if the target is not recognised, or is not interesting, attention can jump to the second target

  * model in Olshausen - uses attention to achieve **invariant pattern recognition**
    * attention selects the target, then a **shifter circuit network** transforms it into a scale and translation invariant constant reference frame - after this object can be recognised
    * without attention, the constant reference frame could not be used because different objects are in different locations or have different scales

  * problem with this kind of approach is that the **a priori rules** for salient targets must be predefined for each kind of data
  * cortex should learn to use the relevancy of different objects to select the targets of attention

### 2.3.3 Models with emerging attention ###

  * no central decision maker exists who chooses the targets of attention
  * **global, coherent attention** can emerge **iteratively** in a network where **local parts make their own decisions** about their representations; when the perceptual network controls the targets of its attention itself, the targets can better adapt to the world
  * Lee and Mumford model resembles the predictive-coding networks
    * integrates contextual information iteratively for forming a coherent interpretation of the inputs
    * uses **particle filtering** for keeping several alternative hypotheses alive simultaneously
    * network also discards the most improbable particles (hypotheses)and finds a single most probable interpretation to the inputs - can be called **selective attention**, because the network represents only some information of the inputs
    * selection gives more representational power to holistic, Gestalt like objects, than the pure generative models give

  * **biased-competition model** of attention works similarly
    * local competition between features leads to emergence of global attention
    * model adds top-down bias that can guide the network to work in goal-oriented way (e.g. the bias can start a search of a certain object in the visual cortex)

  * **Deco and Rolls model** - based on Visnet network, which is a hierarchical model of the visual cortex
    * uses Hebbian-like trace-learning rule for learning invariances
    * extends Visnet to have top-down connections mediating the biases for local competition - produces attention
    * if image contains many objects, representations of different objects will compete
    * initially, features will be processed from all the objects - then the feedback connections alongside the local competition cause increasing **perceptual grouping of continuous shapes**
    * process proceeds to a phase where the whole objects compete, and the winner will be recognised
    * activity patterns in the whole network corresponding to different objects can be considered as **attractors** in a high-dimensional activation space
    * network can consider all the different interpretation possibilities in parallel

  * **biased-competition models** guide the representational capacity into useful objects; in the real cortex, learning is strongest from the attended sources; these models do not use the utility of learning Gestalt like coherent objects as much as the hierarchical predictive coding models, because feedback connections are absent during learning

### 2.3.4 Autoassociative memory in selective attention ###

  * attention can emerge from the competition between different attractors - auto-associative memories can be used to implement this competition
    * set of memory vectors become attractors
    * if the network is given a noisy or incomplete memory vector as input, it can restore the original one
    * if it is given a mixture of many memories, it can select which one of them to restore

  * **Hopfield network** is a simple auto-associative network for binary memory vectors
    * has one neural layer, where each neuron has symmetric connections with each other
    * the number of memory vectors that can be stored to a Hopfield network is approximately 14% of the vector dimensionality
    * capacity will increase even if the memory vectors are artificially sparsified - in the competitive Hopfield neural network (CHNN); memory vectors are divided into smaller parts and winner-take-all competition is applied within parts

## 2.4 Combining attention and learning ##

### 2.4.1 Models where attention guides learning ###

  * attention is known to be an essential guide of learning in the real cortex
    * if attention focuses on important targets, then those things will also be learnt
    * learning distinct objects is also easier with selective attention - if the objects are introduced one at a time, and not simultaneously
    * but how can attention select the objects before the network has learnt to recognise them?

  * **adaptive resonance theory** (ART) uses attention to guide learning even when the objects have not been properly learnt
    * tries to find similarities between the rudimentary learnt objects and the new inputs, and then update the representation of the most similar object to resemble more the present input
    * attention and pattern recognition develop simultaneously, and accelerate each other’s learning
    * higher learning rates can be used because even rudimentary selective attention screens interfering noise away
    * ART uses attention in adapting the features

  * **EXIT model** uses attention in learning of associations between distinct features
    * attention enables higher learning rates, because there are no interfering objects

### 2.4.2 What is missing from the models ###

  * ART is the only model that has attention and learning working concurrently and supporting each other
    * however, it does not include contextual learning and does not operate by the biased-competition principle
    * **solution - models that have cortex like architecture and dynamics that use co-operating learning and attention**

# 3. Model #

  * combines **emergent attention and learning** - can exist alone, but improved if support each other
    * attention increases the learning efficiency
    * attention determines the targets for learning
    * learning forms objects that be easily attended to

![http://ahuman.googlecode.com/svn/images/wiki/research/cortex/attention.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/cortex/attention.jpg)

  * how attention guides learning:
    * network makes probabilistic inference of the momentary world state - combines the utility of representing different things into this inference, so it can **choose the target of attention** with Bayesian decision theory
    * network then learns from this target
    * by time, the network **learns to represent those things that are behaviourally relevant**

  * model does not use explicit utility
    * attention is a desired property, so only a **limited set of features** should be represented at a time
    * neighbouring parts of the network should choose **coherent features**
    * features should have strong **connections to goal-oriented modules**, such as motor cortex

  * even if the network would not need to do any action selection, **selective attention would improve learning**
    * neurons that try to learn to generalise from different instances of the same object can be sure that their inputs do not have distracting information
    * this quality is exploited in ART - the complex interferences between the objects and all their combinations do not have to be learnt

  * as by Deco and Rolls, learning is also enabled when using the network in perception
    * for efficiency on higher level - biased competition is not implemented with detailed connections, but with an algorithm that resembles competitive Hopfield neural network (CHNN)

## 3.1 Outline of the Model ##

  * See picture below:
    * thick black lines are neuronal groups that have internal competition
    * black arrows are bottom-up connections
    * purple arrows are connections mediating contextual bias

![http://ahuman.googlecode.com/svn/images/wiki/research/cortex/network.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/cortex/network.jpg)

  * model is a hierarchical neural network with inputs from two different modalities, visual and auditory
    * network should learn to represent increasingly abstract and global information in its high layers
    * layers are divided into distinct information processing units - correspond to CHNN units so that neurons within one such unit compete with each other
    * within one unit, neurons also receive the same set of feed-forward inputs (the black arrows) - they learn to represent different features in these inputs
    * information processing units could roughly correspond to hypercolumns of the real cortex
    * there are contextual inputs (the purple arrows) which correspond to auto-associative (CHNN) connections
    * in addition to coming from other neurons in the network, the context can come from outside the cortex; it can also have information about past activities of neurons

  * no distinct learning and operation modes in this model - network learns all the time, while perceiving the world, selecting actions and so on
  * behaviour of the network looks different on **different time scales**
    * on **perceptual time scale**, the network tries to represent those objects that are both present in the world and are important
    * on an **intermediate longer time scale**, it looks like an auto-associative memory - network learns the world knowledge as associations fast into the contextual connections
    * on **long time scale** the network adapts its features to code the most important parts of the world

**Perceptual time scale**

  * operation of the network is very similar to that in the model developed by Deco and Rolls
    * neurons calculate their corresponding features from the inputs
    * at the same time, there is local competition, so that **only the most active features get through to the next layers**
    * competition is **biased with the contextual associations**
    * biased competition can give birth to **“bottom-up attention”** that selects salient targets from the inputs, and to **“top-down attention”** where the cortex’s high-level intentions guide perception - winning activation patterns usually result from both kinds of effects
    * bottom-up saliency in this case means **coherent large shapes** where neighbouring areas can **support each other by associations** - Gestalt principles of perception

**Associative memory time scale**

  * bottom-up inputs suggest potential features to the network
    * lateral connections work as an auto-associative memory (like CHNN) which classifies the inputs into familiar feature patterns - network can categorise different instances of familiar objects into similar activation patterns
    * even if single neurons would not have learnt to represent some invariances well, the neural population can represent them

  * learning lateral associations is slower than usual one-shot learning of auto-associative memories
    * recall of past memories is softer - it is only a biasing effect
    * if all the activation patterns the network can represent were some memories, it could not learn or perceive anything new

  * when learning is slightly slower than one-shot learning, it is not affected much from a single appearance of some feature combination, but if that combination is experienced for a couple of times, it will form a memory in the lateral connections
  * memories of different activation patterns can be seen as **symbols** in the network
    * network receives continuous sensory inputs which it learns to categorise into more discrete neural patterns
    * because of slow learning and soft competition, these symbols can adapt to the world where the agent lives
    * appropriate abstraction levels and generalisation strength emerge in the network
    * if the world contains strong regularities between many simultaneous features, the network will produce few large symbol codes, which include many neurons representing different features
    * if the world contains many small objects, the network will develop more and smaller symbol codes than in the previous case

**Longest time scale**

  * features the neurons represent are adapted to the world using on-line DSS, with biased-competition as denoising
    * results in learning features that are sparse, invariant and contextually coherent
    * sparse features result from competition in general, because it makes the activity statistics sparse which leads to learning of sparse features as in the model by Olshausen and Field
    * learning invariances happens in the dimension reduction layers with the supervision from the context, as in the model by Valpola

  * when a neural population recognises a symbol, it works as a target for learning of individual neurons
    * lateral connections can learn different symbols quite fast - adaptation of bottom-up weights transfers this information slowly into the features
    * the same contextual guidance results also in features that have the most mutual information across different modalities, as in the model by Becker and Hinton
    * because the features are then related to those of the motor cortex and working memory (controlled by subcortical structures) - all inference becomes goal-oriented in  the network

  * mutual-information maximisation has an additional benefit of noise reduction
    * real events in the world usually cause sensations in many modalities, while noise can be uncorrelated between modalities
    * features that relate to features from other modalities have a smaller probability of being modality-specific noise

**Finally**

  * local processing units do the following things
    * units make **probabilistic inference** about the state of the world; bottom-up inputs are the measurements for which the network tries to find true physical causes; different neurons code different causes, or input features; in Bayesian terms, the **likelihood of the features is calculated from the bottom-up inputs**, and the **prior is calculated from the context**
    * units combine utility information to the probabilities of different neurons, following Bayesian decision theory; **contextual inputs are considered as signals of utility**, in addition to mediating probabilistic information
    * units make decisions about what to represent - implemented by competition between the neuronal activities
    * features and lateral associations adapt to those features that have been chosen to be represented

  * consequences if some of these mechanisms were not in the model
    * **no competition** - attention would not emerge; additionally, generalisation would get weaker in the network, even when there are lateral connections teaching generalisation; competition between the neurons is an active categorisation mechanism
    * **no bottom up feature learning** - if the bottom-up weights were constant and random, the lateral connections could still learn associations between random features, and symbols could emerge; this was tested with simulations; the result was that the symbols were much weaker than with adaptive features; as competition directs attention to some neurons, the symbols become stronger when the neurons code explicitly some real world features
    * **learning all structure in the world, without guidance from attention** - a smaller portion of the representational capacity would be allocated for those things that have high relevance; moreover, learning would become more difficult when there are multiple objects present simultaneously

## 3.2 How to handle temporal sequences ##

  * **present model handles only static sensory inputs**
  * model could be extended to handle dynamic sensory data by using the contextual associators as predictors for future inputs
    * temporal continuity gives evidence for the existence of a feature
    * utility of representing that feature may decrease when the system already knows about it
    * therefore the system should do novelty filtering, suppress those features that can be predicted
    * representing surprising events often have high utility - in animals attention is known to focus on surprising events

  * combining the support for continuous features and novelty filtering could be implemented by using two different neuron sets in each processing unit
    * first set would learn and represent continuous dynamics
    * this layer would feed the second layer, which would filter novelties, guided by the context

## 3.3 Example of learning and perception with the model ##

  * assume that network is planted in a brain of a robot which stands still on a spot and manipulates objects with its arms
  * network consists of visual and motor hierarchies
  * motor inputs are the motor commands for moving the arms, that initially originate from outside the cortex model
  * contextual bias from the motor cortex will make the visual cortex learn mostly nearby objects - far-away mountains, clouds or trees, the motor signals will never correlate with them
    * visual cortex will represent mostly those features that are behaviourally meaningful
    * lower levels get the strongest bias from the higher levels when there are nearby objects present - even the primitive visual features will be tuned mostly for those, and not to background tree leaves - will be considered as noise

  * invariance classes will also be affected by the motor signals
    * apart from translation, rotation and scale invariances, there may develop some neural patterns that respond invariantly to potentially graspable shapes
    * if there are many different objects and shape instances that can be grasped with similar motor commands, the invariance can help in recognising those

![http://ahuman.googlecode.com/svn/images/wiki/research/cortex/perception.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/cortex/perception.jpg)

  * target of attention is developed iteratively, information gets integrated from all sources
    * different parts of the network receive inputs from objects A, B and C, which are behaviourally meaningful and have been learnt, and irrelevant information N such as background noise
    * upper level of the network receives contextual bias that supports object A
    * motor cortex could be doing something with this object

  * **Step 1** - the inputs get to the first level
    * processing units do not have features tuned for noise, so none of them will decide to represent it
    * when one unit receives inputs from two different objects, competition chooses the larger activations to be represented

  * **Step 2** - the initial first level activations go to the second level
    * bias for A causes it to have stronger representation than B, even when its bottom-up signal is weaker
    * meanwhile, the lateral connections in the first level form a B-symbol, which overrides C

  * **Step 3** - the information flows back from the second level to the first
    * there A and B have both lateral and top-down bias, but A has stronger top-down bias
    * so it will override B

  * **Step 4** - A and B feed the second level equally strongly, bias for A causes it to win the competition

  * **Summary**
    * noise was not represented at all
    * object C was represented only weakly in the first level, because it did not have any contextual support
    * A and B had lateral support, but A had additional external support, which caused high level attention to focus on it

## 3.4 Implementation details ##

### 3.4.1 Calculating activations in one processing unit ###

  * activations of the neurons are scalar numbers, updated on discrete time step
  * one processing unit at a time calculates new activations for its neurons by computing
all the below steps:
    * it **computes preactivations** for the neurons first
    * then it **combines the contextual association** into those
    * then it does **competition between correlating elements** and finally **competition between all elements**
    * then, depending on the phase in iterations on the whole network level, it may **adapt the features, lateral associators and the rest of the parameters**

![http://ahuman.googlecode.com/svn/images/wiki/research/cortex/steps.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/cortex/steps.jpg)

  * inputs to the processing units should be spherically symmetric, in order to give the contextual modulation the power to affect both long-term learning, as in DSS, and instantaneous selection of features
    * the primary input to the lowest level of the network is sphered separately on each patch that feeds distinct processing units
    * done by initially measuring the means and covariance matrices from a set of inputs, and then removing the means and doing PCA sphering
    * in PCA sphering, the data is projected to the uncorrelated principal components, and then scaled to have unit variance
    * this kind of sphering is not done for data travelling between the processing units
    * instead, decorrelation and competition should make the outputs from the processing units sufficiently close to spherical
    * however, there may remain quite strong correlations between elements from different units
    * if these correlations were removed with adaptive sphering, learning could improve, but the implementation would become more difficult

  * **compute pre-activations**
```
calculate the feature pre-activation vector Yp from the bottom-up input vector Xb:

Yp = F( Wb * Xb ) * g, where

F - pre-activation function for neurons, 
Implementation sets negative values to zero.
Activation function does not have to modulate the features into being sparse, 
as the lateral competition will do that.

Wb - feature (bottom-up) weight matrix

g - slowly adapting sensitisation-gain vector of the neurons
Tries to make the neurons average activity levels equal.

Consequences: 
The network activations are maximally informative in the Shannon information sense. 
If the input data has some frequent features, the network will use more neurons 
to represent different aspects of that feature. This way, the representation resolution
is better for those features than for rare ones.
For learning, the sensitisation-gains work as the conscience in (Desieno, 1988). 
The neurons learn equally often, and each neuron will represent something useful 
instead of getting stuck to noise features.
Without sensitisation, the contextual associators would be biased toward the variances 
of the units. With sensitisation, they are better tuned to the information in 
their outputs.
With sensitisation, all the neurons are used in representation, learning and associations 
and an “effective number of neurons” in the network becomes maximal.
```

  * **combines the contextual association**
```
calculate bias B:

B = Wl * Xl, where

Xl - contextual or lateral inputs
Wl - weight matrix, trained with supervised learning, 
using pre-activation vector Yp as target

Reason for using supervised learning instead of Hebbian learning is that now it is 
easier to extend the associators from linear to non-linear - will increase the memory
capacity of the whole network and enable the recognition of more complex objects.

Problem of supervised learning:
When some contextual inputs can explain the targets, there is no further learning.
Usually the top-down context correlates more with the activations than the lateral
context, and the lateral connections do not learn much anything. They would still be
important. Therefore two different associators are used, one for each type of context.
Both associators learn with supervised learning independently

Then predictions from associators are combined with pre-activations - 
to get biased pre-activation vector Yb:

Yb = Yp * ( 1 + Sum(m * Fm(B)) ), where

function fm sets the negative values to zero, scales b to have a maximum 
value 1 - prevents lateral positive feedback loops which could take take activations 
into infinity, from forming. m are modulation coefficients - 1 for lateral bias and 
0.5 for top-down bias. Biases are not added to the pre-activations, but they modulate
them - plain bias cannot give birth to activations and the network cannot start 
to hallucinate
```

  * **competition between correlating elements**
```
Decorrelation step prevents the neurons from learning the same features.
Additionally, it makes the output of the unit closer to being spherical.
```

  * **competition between all elements**
```
Adds force that tries to keep the features separate, but that force alone was too weak.
All the features in one unit learnt to represent only a few different features.
Competition is not winner-takes-all type, so it can leave simultaneous activation 
for correlating neurons.
Decorrelation was not complete so that the resulting activations would satisfy
some decorrelation equation. Instead, only one step anti-Hebbian decorrelation used.

Decorrelated feature vector Yd:

Yd = Fa( Yb - a * Wa * Yb ), where

Fa - sets negative values to zero.
Wa - anti-Hebbian weight matrix measuring the correlations between neurons.
a - decorrelation strength
In the experiments, decorrelation strength a=0.1 was not sufficient for keeping
the features separate, but value a=1 was.

Goal of competition is to choose the most active features, but it should not be 
too severe, like winner-takes-all competition. If it were, the network could get stuck 
in the initial decisions, and the iterative integration of information could not find 
the best features to represent.
There are many ways to implement this kind of soft competition. 
A popular method is softmax activation function:

Y = ( exp(p * Xi) )T / Sum( exp(p * Xi) ), where

p - competition strength
X - sparsified vector.

Relative competition between two elements is always the same despite the activations 
of other features. If there is only one large activation, it will drive all the other
activations near zero, resulting in winner-takes-all competition.

Another popular method is to use inhibitory connections between the neurons, and drive 
the activations iteratively to a stable point, in a similar manner as decorrelation 
is done in. Finding a stable point in these fixed-point equations may take
many iterations and is thus computationally slow.
```

  * **calculating sparsity measure**
```
Following method used:
Calculate a sparsity measure Ms for the activation pattern.
Update the activations with gradient descent until they are sparse enough.
if the pattern is already sparse in the beginning, there is no competition.
On arbitrary patterns, a typical number of competition iterations needed was from 2 to 8.

Sparsity of a random variable x can be measured with any convex function f - then the measure is Ms:

Ms = E( f(x^2) ), used f(x^2) = -abs(x)

Instead of expectation, the elements in the activation pattern are averaged. In order 
to make this measure insensitive for the general size of the activation, the measure 
was divided by the norm of the pattern:

Ms(Y) = -Sum(Yi) / ||Y||

Elements of Y are known to be non-negative
Gradient of this measure is directly proportional to 1 vector, which has 1 as all the elements.

Algorithm for sparsifying vector y in its whole:

1. Calculate the sparsity measure Ms from Y
2. If the vector is sparser than before set limit, jump to the end. Otherwise continue.
3. Update Y = -Y - a * max(Y). Set all negative elements of Y to zero and jump back to step 1.

A fast, but still not too crude, method results from  being for example 0:2. 
The sparsity limit can be determined by constructing a model vector that is as sparse 
as is wanted, and then calculating the measure from it. If only few elements of 
the model vector are active, the sparsity limit will be high and competition strong.

Very strong competition will generalise well. Small changes in the inputs will lead to
similar representations. However, the stronger the competition, the less sensitive 
it is to changes in contextual guidance. A good compromise model vector should be 
clearly sparse, but still have more than one active neuron.

After competition, the final activations y are ready. These can then be used by 
other processing units as bottom-up input or context. They are also used to adapt 
the sensitisation-gains g, anti-Hebbian weights Wa and bottom-up weights Wb.
```

### 3.4.2 The order in which the different units operate ###

  * for one distinct input vector, the whole network must be ran for a couple of iterations, so that coherent attention has time to emerge
    * for dynamic input data, one iteration per each input could suffice

  * there are a few different alternatives for the order in which the processing units could operate
    * one alternative would be to have no order between the units, but to run all the units simultaneously
    * this can be done by running them in arbitrary order one at a time, but using the neural activations of the previous time step as inputs
    * in this case, the first level units would be iterated many times before the high level units receive the same inputs
    * emergence of coherent attention would take a long time (computationally)

  * following order used:
    * first run all the units of the first level in a random order, then the next level and so on to the top
    * then the levels are ran in a reverse order - in this order, all the units have to be ran two times to get the information from the inputs to the highest level, and then the contextual information from the high levels back to the bottom
    * for static input data, 2–5 iterations used of this order per input

### 3.4.3 Learning in the unit ###

  * adaptive elements in the units are not trained each time the unit calculates new activations - instead, they are trained only just before introducing a new input to the network
    * thus, learning happens after global attention has emerged, taking advantage of all the benefits of attentional learning

  * bottom-up weights learn with the Hebbian rule:
```
dWb = nb * Y * X
```

  * after updating, the rows are scaled to unit vectors
    * the learning rate nb should be small - otherwise the weights would not converge, but they could jump forever between different features
    * in the experiments nb=0.0001 is used. Learning does not have to be strictly on-line
    * instead, the weight changes can be accumulated for, say 10–500, iterations, and then update the real weights and scale them to unit vectors
    * this saves computation time and can make learning converge more smoothly

  * for sensitisation, the variances (actually sums of squares) of feature activations must be measured, too
...

**finally**:
  * artificial data as inputs
  * do not learn dynamics from the world
  * computationally ineffective