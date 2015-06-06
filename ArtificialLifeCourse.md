@@[Home](Home.md) -> [ArtificialLifeResearch](ArtificialLifeResearch.md) -> [ArtificialLifeCourse](ArtificialLifeCourse.md)

---


# Artificial Life Course Essentials #

### 1. Introduction to Artificial Life ###

  * What is Life (hydro-carbon chains?)
  * What is Intelligence (faculty of thought and reason?)
  * What is Artificial Life
    * man-made, not unreal
    * bottom-up, not top-down (means emerging from low-level interaction)
    * life "as it is", and "as it might be"
  * "Artificial" is related to components, not to emergent processes
  * "Big" claim that proper primitives with human-like functions will support process, that will be "alive" in the same meaning as for natural organisms (WRONG INTENTION FROM MY POINT OF VIEW - if we repeat human, it will be just a human - and we already know how to repeat human)
  * Applications:agent-based modeling (consumer markets, traffic flow), robotics, artificial worlds
  * **Mind parts**
    * Visual cortex / Occipital lobe / Parietal lobe / Primary auditory cortex / Temporal lobe / Somatic sensory cortex
    * Frontal lobe / Vocalization / Vocalization region of motor area / Motor area (precentral gyrus) - leg, arm, face / Supplementary motor area
    * Central sulcus / Broca's area / Sylvian tissue / Wernicke's area / Angular gyrus / Arcuate fasciculus
  * Damage of Occipital lobe leads to inability to dream
  * Damage of Visual cortex leads to lack of depth perception and inability to assemble parts into whole

<table>
<tr>
<td>
<img src='http://ahuman.googlecode.com/svn/images/wiki/research/course/01.mind.jpg' />
</td>
<td>
<img src='http://ahuman.googlecode.com/svn/images/wiki/research/course/01.motorman.jpg' />
</td>
</tr>
</table>

  * Also find one more homunculus picture - see [link](http://www.flickr.com/photos/kriggs/421933382/)

![http://farm1.static.flickr.com/130/421933382_2ae5c1bec2.jpg](http://farm1.static.flickr.com/130/421933382_2ae5c1bec2.jpg)

  * **Motor Cortex Map** (see Motor Cortex Homunculus):
    * Toes / Ankle / Knee / Hip / Trunk / Shoulder / Elbow / Wrist / Hand
    * Fingers: Little / Ring / Middle / Index / Thumb
    * Neck / Brow / Eyelid and eyeball / Face
    * Vocalization: Lips / Jaw / Tongue / Swallowing
  * ANNs capture key features of biological neural networks (connectionism) using:
    * Hebbian learning
    * Suitable wiring diagram
  * How to proceed
    * Genetic Algorithms (computational realm)
    * Natural Selection (biological realm)
    * Any little niche, survive, reproduce, adopt to changes
    * Provide suitably rich physics, adequate energy
    * Use biologically inspired models: rich genetic structure, ontogeny (process), environment, invoke evolution, wait
  * We are our bodies and it is a process, not substrate
  * Machine intelligence not equal to natural intelligence

### 2. Is It Alive ###

  * Artificial Life is broader - whether biological science can help?
  * What is Life:
    * Neumann / information flow
    * Monod / form and function resulted from evolution not design, carried from one generation to another, derived from internal self-description
  * **Farmer & Belin's criteria**:
    * Pattern in spacetime (continuum property of organizational patterns)
    * Self-reproduction (not right for mule)
    * Information storage of a self-representation (DNA) (not right for prion)
    * Metabolism (converts matter and energy from the environment into the pattern and activities of the organism)
    * Functional interactions with the environment
    * Interdependence of parts (rock can be split, human will be killed) (not right for virus)
    * Stability under perturbations
    * The ability to evolve (existence if lineage) (not right for virus)
  * **Wet Artificial Life**
    * Man-made - plant breeding, animal husbandry, and pet domestication
    * Genetic engineering - more radical
    * Primordial soup
    * Test tube evolution (amplify desired evolution)
    * Minimal bacterial genome
    * Synthetic biology
  * **Self-Organization**
    * Increasing differentiation of parts
    * Increasing integration of these parts
    * Underlies the spontaneous formation of structure
    * Antagonist of entropy
  * **Evolution**
    * Darwinian - information is passed only via genetic information (biological)
    * Lamarckian - information learned during an organism’s lifetime was also passed from one generation to the next
    * Genetic Engineering - allow Lamarckian evolution for biological organisms
    * Artificial Life - allow Lamarckian evolution for artificial organisms

### 3. Introduction to Genetic Algorithms ###

  * IGNORE - AT FIRST LEVEL OF MODELING, EVOLUTION CANNOT AFFECT PERSONALITY

### 4. Simulated Evolution ###

  * IGNORE - MODELING EVOLUTION IS APART FROM PERSONALITY

### 5. Neural Networks - Definitions ###

  * NN - are:
    * systems to use HI organizational principles
    * elements operating in parallel
    * nodes function like nodes in natural neuron
    * distributed computation

<table>
<tr>
<td>
<img src='http://ahuman.googlecode.com/svn/images/wiki/research/course/05.neuron.jpg' />
</td>
<td>
<img src='http://ahuman.googlecode.com/svn/images/wiki/research/course/05.neuronbiomodel.jpg' />
</td>
</tr>
</table>

  * How big is a human brain
    * 10-100G neurons
    * 100-10K synapses per neuron
    * 1-1000T synapses total
    * reasonable ballpark values - 100G neurons, 100T synapses
    * Intel - 10G transistors in chip in 2010 (different matter - parallel, but not neurons)
  * Neural activity
    * temporal parameters (e.g. spike timing, spite frequency) have meaning
    * spike timing - 100-150 spikes/sec depending on strength of stimulus
  * Learning
    * knowledge is represented by strength of synaptic connections, hence "connectionism"
    * supervised/reinforcement/unsupervised
    * MADALINE and delta-rule are used to eliminate echo in phone
  * Great models
    * SOM/Kohonen Map (unsupervised representing multi-dimensional input with low-dimensional discretized view, based on topological properties)
    * ART (object identification and recognition generally occur as a result of the interaction of 'top-down' observer expectations with 'bottom-up' sensory information)
    * Hopfield (associative memory)
    * Simulated annealing (solving combinatorial optimization problems)
    * Boltzmann Machine

### 6. Neural Networks - Association and Hebb ###

  * Thought Processes
    * perceptual generalization (the ability to place different stimulus patterns in the same category, despite large variability between members of the category)
    * permanence of learning
    * attention
  * Brain Processes
    * physiological law of habit among the neural elements is what runs the train
    * the order of presentation of the mind’s materials is due to cerebral physiology alone
    * free will is the volitional act of emphasizing, reinforcing, or protracting the thoughts which the associative machinery introduces
  * Partial Recall
    * memory decay
    * memory reinforcement
  * Influences on recall
    * frequency of association (habit)
    * recency of association
    * vividness
    * congruity in emotional tone
    * similarity
    * accident
  * “attractor” models of brain activity (Hopfield, Grossberg, Anderson, and others)
    * relatively stable and long-lasting neural activity patterns, important for thought and memory
    * repeated stimulation of specific receptors will lead slowly to the formation of an ‘assembly’ of association-area cells, which can act briefly as a closed system after stimulation has ceased
    * this prolongs the time during which the structural changes of learning can occur and constitutes the simplest instance of a representative process (image or idea)

<table>
<tr>
<td>
<img src='http://ahuman.googlecode.com/svn/images/wiki/research/course/06.hebb.jpg' />
</td>
<td>
<ul><li>A, B, and C happen to regularly be fired by a particular visual stimulus<br>
</li><li>If D, E, and X happen to fire at the right times, connections AE, BC, BD, etc. are strengthened and increase likelihood of coordinated firing<br>
</li><li>Resulting in an assembly of cells that reverberate in response to a stimulus, causing further strengthening of connections<br>
</td>
</tr>
</table></li></ul>

### 7. Introduction to Information Theory ###

  * Probability
    * Random experiment
    * Elementary outcomes
    * Sample space
    * Frequency / Law of large numbers
    * Subtraction Rule:
```
P(NOT a) = 1 - P(a)
```
    * Event
    * Addition Rule:
```
P(a OR b) = P(a) + P(b) - P(a AND b)
```
    * Joint Probability:
```
P(a AND b) = P(a,b)
```
    * Conditional Probability:
```
P(a|b) = P(a AND b) / P(b)
```
    * Multiplication Rule:
```
P(a AND b) = P(a|b) * P(b) = P(b|a) * P(a)
```
    * Statistical Independence:
```
P(a|b) = P(a), P(b|a) = P(b)
```
    * Marginal Probability: P(x) - ignore information about other events
  * Shannon Theory
```
S = k log W: Entropy = Boltzmann’s-constant * log( function of # of possible micro-states )
I = K log Ω: Entropy = constant (usually dropped) * log( function of # of possible micro-states )
```
    * physical entropy to informational entropy: 1 electron volt / kelvin = 16,743 bits
    * The language models just discussed and many other symbol sources can be described as Markov processes (stochastic processes in which future states depend solely on the current state, and not on how the current state was arrived at)
    * The information produced by a given symbol is exactly the amount by which we reduce our uncertainty about that symbol when we observe it
    * The only H (measure of uncertainty) satisfying properties:

```
        n
H = - K ∑ pi log pi
       i=1

K is a positive constant

e.g. for two possibilities:

H = - (p log p + q log q)
```

  * Joint Entropy:

```
H(x,y) = - ∑ p(xi,yj) log p(xi,yj)
          i,j

H(x,y) ≤ H(x) + H(y)
```

  * Conditional Entropy:

```
H(y|x) = - ∑ p(xi) p(yj|xi) log p(yj|xi)
H(y|x) = - ∑ p(xi,yj) log p(yj|xi)

H(y) ≥ H(y|x)

HMax = log n
```

  * Normalized Entropy (relative entropy):

```
Ho(x) = H(x) / HMax
```

  * Mutual Information

```
I(x,y) = ∑ p(xi,yj) log [ p(xi,yj) / p(xi)p(yj) ]

I(x,y) = H(x) - H(x|y) = H(y) - H(y|x)
I(x,y) >= 0
I(x,y) = I(y,x)

Probability and Uncertainty:
marginal: H(x) = - ∑ p(xi) log p(xi)
joint: H(x,y) = - ∑ p(xi,yj) log p(xi,yj)
conditional: H(y|x) = - ∑ p(xi,yj) log p(yj|xi)
mutual: I(x,y) = ∑ p(xi,yj) log [ p(xi,yj) / p(xi)p(yj) ]
```

### 8. Hebbian Learning and Information Theory ###

  * Self-organization of brain maps
    * Consistent with the way processing is done in the brain
    * Should preferentially represent high-probability stimuli
    * Based on local interactions (no global control)

```
von der Malsburg (1973) neuron activation rule:
dHk(t)/dt = −αkHk(t) + ∑ plkHl(t) + ∑ sikAi(t)
           activation    lateral    connections from
              decay    connections  "retinal" layer

The Shannon information rate (the average information transmitted from L to M per message):
R = ∑∑ P(L,M) log[ P(L,M) / P(L)P(M) ] = H(L) - H(L|M) = H(M) - H(M|L)

 - P(L) is the probability of the input message being L
 - P(M) is the probability of the output message being M
 - P(L,M) is the joint probability of the input being L and the output being M

For the case in which P(L) is uniform over L:
R = - ∑M [A(M)/A] log[A(M)/A] - (γν/A) ∑M s(M)

 - P(M) = A(M) / A
 - P(M|L) log P(M|L) is zero except for borderline L
 - γ is a positive number whose value depends on the details of the noise process, and which determines P(M|L) for borderline L as a function of distance from the border
```

  * tends to produce maps in which regions of the input space that are activated more frequently are given greater representation in the output space
  * Hebb-type rule can also be shown to maximize information in M about L, by showing that it minimizes uncertainties in L given M, in an LMSE (Least Mean Squared Error) sense

```
The linear response rule:
M = a1 + ∑Lc

Potential range of Hebb-type rules:
∆ci = a2LiM + a3Li + a4M + a5

a2-5 are arbitrary constants (a2 > 0)
```

### 9. Spiking Neuron Models ###

![http://ahuman.googlecode.com/svn/images/wiki/research/course/09.activation.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/course/09.activation.jpg)

  * **Level 1. Detailed compartmental models**
    * Realistic spatial structure
    * Supports dendritic computation and axonal signal filtering (coincidence detection, motion detection, gain modulation)
    * Computationally expensive (single cell mostly)
  * **Level 2. Reduced compartmental models**
    * Can model temporal aspects of learning and spiking
    * Have been used to model short term memory, cortical gamma oscillations, slow-wave sleep oscillations
    * Still computationally expensive (max around 3,000 cells)
  * **Level 3. Single-compartment models**
    * Model phasic, chattering, tonic, and adaptive spiking, relating cell characteristics to observed spike trains
    * Capture “synaptic noise” effects on probabilistic spiking, neuron sensitivity, network stability
    * Computationally tractable (100,000s to 1011 neurons)
  * **Level 4. Cascade models**
    * Concatenation of linear filters, nonlinear transformations, and random processes
    * Used to model visual system, simultaneous adaptation to mean light intensity and light contrast, other features
    * Ignore dynamics that do affect experimental outcomes
  * **Level 5. Black-box models**
    * Model signal-processing characteristics with no consideration of physical machinery
    * May reveal general operating points, how inputs modify responses
    * Have revealed that sensory neurons operate close to their information-theoretic limit, and how neurons may shift their input-output curves to achieve this

  * Ways to model neuron
```
1. (Leaky) Integrate & Fire (I&F):
v’ = I + a - b v
if v ≥ vthresh then fire and reset v = c

Four floating-point operations, plus one compare, per ms.
3 of the 20 identified behaviors.

2. Integrate & Fire with Adaptation (I&FA)
v’ = I + a - b v + g (d - v)
if v ≥ vthresh then fire and reset v = c
g’ = (e δ(t) - g) / τ

10 floating-point operations, plus compare, per ms
5 of 20 identified behaviors.

3. Integrate & Fire or Burst (I&FB)
v’ = I + a - b v + g H(v - vh) h (vT - v)
if v ≥ vthresh then fire and reset v = c
h’ = { -h / τ- , if v > vh
(1 - h) / τ+ , if v < vh

Between 9 and 13 operations per ms (depending on v)
9 to 11 behaviors still unmodeled.

4. Resonate & Fire (R&F)
z’ = I + (b + iω) z
if Im(z) ≥ athresh then fire and reset z = z0(z)
10 operations, plus compare, per ms
9 behaviors unmodeled

5. Quadratic Integrate & Fire (QI&F)
v’ = I + a (v - vrest) (v - vthresh)
if v ≥ vpeak then fire and reset v = vreset
7 operations, plus compare, per ms
15 of the 20 behaviors

6. Izhikevich spiking model (ISM)
v’ = 0.04 v2 + 5 v + 140 - u + I
u’ = a (bv - u)
if v ≥ 30 mv then has fired, so reset:
v = c
u = u + d

13 floating point operations, plus compare, per ms in
most regimes
all 20 behaviors with different parameters

7. FitzHugh-Nagumo
v’ = a + b v + c v2 + d v3 - u
u’ = ε (ev - u)

18 floating point operations, per step
10 of the defined 20

8. Hindmarsh-Rose
v’ = u - F(v) + I - w
u’ = G(v) - u
w’ = (H(v) - w) / τ

30 floating point operations, per step
17 of the 20 behaviors

9. Morris-Lecar
60 floating-point ops per step
6 to 8 behaviors unmodeled

10. Wilson polynomial neurons

45 floating-point ops per step, but requires
Can theoretically produce all 20 behaviors

11. Hodgkin-Huxley
120 floating-point ops per step
all 20 behaviors
```

![http://ahuman.googlecode.com/svn/images/wiki/research/course/09.spiketable.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/course/09.spiketable.jpg)

  * processing power:
    * 1,000 cortical spiking neurons in real time in MATLAB on a 1 GHz desktop PC
    * 20,000 neurons in real time in C on a 1 GHz desktop PC
    * 100,000 neurons with axonal delays and STDP learning
    * detailed thalamo-cortical system with 1011 spiking neurons (size of the human brain), 6-layer cortical micro-circuitry, specific, non-specific, and reticular thalamic nuclei.” - one second of simulation took over a month on a cluster of 27 3 GHz processors

### 10. Evolution and Learning ###

  * IGNORE - MODELING EVOLUTION IS APART FROM PERSONALITY

### 11. Organisms, Simulated and Real ###

  * Testudo

![http://ahuman.googlecode.com/svn/images/wiki/research/course/10.testudo.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/course/10.testudo.jpg)

  * Kinds of Minds
    * Ground Floor: Darwinian Creatures / niches / phenotypic plasticity
    * Second Floor: Skinnerian Creatures / Associationism, Behaviorism, and Connectionism / prediction and preselection
    * Third Floor: Popperian Creatures / accumulation of accurate information about the world / reasoning about our own artifacts
    * Fourth Floor: Gregorian Creatures / designed elements of the environment, culture and tools enable both creator and consumer / categorization leads to symbolic thought

### 12. Intelligence as an Emergent Phenomenon ###

  * Intelligence
    * it would be convenient if intelligence were an emergent behavior of randomly connected neurons in the same sense that snowflakes and whirlpools are emergent behaviors of water molecules
    * it might then be possible to build a thinking machine just by hooking up a sufficient number of neurons in a suitably architected network
    * if true, it allows for the possibility of constructing intelligence without first understanding it
    * an emergent system would not be intelligent in and of itself, but rather a “metabolic substrate” in which intelligence would grow
  * Symbiosis
    * all modern biological life is a symbiotic combination of two very different self-reproducing systems—drops of oil and free-floating DNA
    * choosing between emergence and symbolic computation in the study of intelligence is like choosing between metabolism and genetic replication in the study of life
    * it would need to provide those emergent properties that are necessary to support the operations of thought
  * Size
    * synapses - 10000 Tbit
    * measure the information in symbolic knowledge by statistical sampling
    * how many facts in the Encyclopaedia Britannica are known by an individual
    * game of 20 questions - knowledge in common between the two players is on the order of 2^20 bits, or about one 1 Mbits
    * estimate the average rate of information acquisition and multiply by lifespan - a 20 year old human, learning at the maximum rate for 16 hours/day (and never forgetting) would know less than 50 billion bits of information, or 50 Gbit
    * memorizing about 33 bits/second
    * intelligent machine would require about 1Gbit of storage, plus or minus two orders of magnitude
  * Speed
    * efficiently stored representation means any representation requiring only a multiplicative constant of storage over the number of bits of information
    * given a representation of acquired intelligence with a “realistic” representation efficiency of 10%, and a need to access all of that information 10 times/sec…
    * 1 Gbit of memory would require a memory bandwidth of about 100 Gbit/sec - corresponds to about one bit/sec per neuron in the cerebral cortex
    * 1.25 GHz frontside bus speeds with standard DDR SDRAM in modern computers could access memory at about 80 Gbit/sec (160 Gbit in common dual-processor, dual-bus configurations)
  * What sensory-motor functions are necessary to sustain symbolic intelligence?
    * damages to certain parts of visual cortex impair binocular fusion, but demonstrate no obvious impairment of cognitive function
    * all sensory-motor apparatus is unnecessary to thought
  * Understanding
    * classes of man-made systems: Neural networks, Spin glasses, Cellular automata, Evolutionary systems, Adaptive automata
    * disciplines providing useful information: Neurophysiology, Cognitive psychology, Evolutionary biology
    * theoretical work proceeds in: Logic and computability, Linguistics, Dynamical systems theory

### 13. Evolving Intelligence ###

  * Evolution
    * Evolutionary Algorithms (GA)
    * Evolutionary Constraints (by previous constraints)
    * Evolve a suitable neural architecture
    * Speciation = ƒ (population isolation)
    * Altruism = ƒ (genetic similarity)
  * Nervous Systems
    * controlling behavior on all levels in all organisms more complex than plants
    * some behavior is innate (wiring diagram)
    * some behavior is learned (phenotypic plasticity)
  * Brain maps
    * consistency along large populations
    * injury to hippocampus can cause a loss of ability to store new memories
    * lesions of prefrontal cortex can eliminate ability to plan for the future, make rational decisions, and process emotion
    * Moderate stroke damage to occipital lobe can induce rare Charcot-Wilbrand syndrome (loss of dreams)
    * scarcity of tissue in localized portion of visual system is method of action for gene disorder, Williams Syndrome (lack of depth perception, inability to assemble parts into wholes)
  * Graduated Intelligence
    * consciousness is not an all-or-none property, but it is graded: to varying degrees, it should exist in most natural (and artificial) systems
    * evidence exists for self-awareness in humans, chimpanzees, orangutans, and elephants

![http://ahuman.googlecode.com/svn/images/wiki/research/course/13.subjects.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/course/13.subjects.jpg)

  * Polyworld
    * computational ecology
    * organisms have genetic structure and evolve over time
    * organisms have simulated physiologies and metabolisms
    * organisms have neural network "brains" (arbitrary, evolving architecture, Hebbian learning)
    * perceive environment through vision
  * Physiology and Metabolism
    * Energy is expended by behavior & neural activity
    * Size and strength affect behavioral energy and energy costs to opponent when attacking)
    * Neural complexity affects mental energy costs
    * Size affects maximum energy capacity
    * Energy is replenished by eating food (or other organisms)
    * Health energy is distinct from Food-Value energy
    * Body is scaled by size and maximum speed
  * Perception: Neural System Inputs
    * Vision
    * Internal energy store
    * Random noise
  * Alive by Farmer & Belin
    * Life is a pattern in spacetime, rather than a specific material object
    * Self-reproduction
    * Information storage of a self-representation
    * A metabolism
    * Functional interactions with the environment
    * Interdependence of parts
    * Stability under perturbations.
    * The ability to evolve
  * Information and complexity
    * 1 electron volt / kelvin = 16,743 bits
    * converting one electron-volt of energy into heat (298K), will produce 56 bits
    * energy is free information, living systems reduce entropy
    * λ = # rules leading to nonquiescent state / # rules
    * Wolfram classes: I (fixed), II (periodic), III (chaotic), IV (complex)
  * Integration
```
I(X) = ΣH{xi} − H(X) >= 0
MI(x1,x2) = H(x1) + H(x2) – H(x1x2)
H{xi} is the entropy of the ith individual element xi
```

![http://ahuman.googlecode.com/svn/images/wiki/research/course/13.complexity.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/course/13.complexity.jpg)

  * Complexity categories
    * number of different parts (genes, cells, organs)
    * number of different interactions between parts
    * number of hierarchical levels
    * number of parts or interactions at a given scale