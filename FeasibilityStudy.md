[Home](Home.md) -> [ProjectVision](ProjectVision.md) -> [FeasibilityStudy](FeasibilityStudy.md)

---


BREAKTHROUGH

### Biological Problem ###

First, biological system is made up from biological components, which have very deep structure and therefore each item practically can store a lot of details, can have rich representation of related entity.
We can compare this to audio signal which several years ago was recorded only on magnetic media, which has low reliability but has very good representation of original live
audio.
Now we have digital representation for practically all audio data. The reason is its ability to copy w/o distortion and store w/o loss. In early time it was regarded as poor because of low bit-rate metric. Now we have formats with more fine-grained representation (high bit-rate) which is considered by most people as good enough and even having more quality than live concerts.
Let's consider that with some increased level of details we can use good digital representation of biological elements. It could mean that e.g. neuron should have much more complex digital model than we have now in neural networks. Estimated size (excluding connections) is 10 times simple neuron size:
`10 * sizeof(scale_input + scale_output + activation_type + induction_parameters + activation_parameters + input_output_state) ~= 1K`

Second, human AI design is in fact adopted to use biological components, and copying this design in digital AI can be a big mistake, because digital components and interfaces, that we are able to construct, may be unable to repeat some critical fundamental properties of biological components.
If this is the case, then it can leave us the only way - to have a different set of components with different properties, which, as a whole, in theory can possess the features comparable in power with those of human.

### Size Problem ###

Size roughly is size of neurons plus size of connections. Size of neurons is `1K * 100G = 100T` bytes. Connection size is `100T * sizeof(input identification + weight) = 100T * 16 bytes = 1600T bytes`.
Finally let's use 1000T bytes as the estimation for HI.

AI has online (operating memory) and offline (hard disk) storages. Ordinary computer can have 1Gb memory used by single program, and 1Tb to store on disk. For AI created "in personal lab" it would be useful to limit this to 500Mb operation memory and 100Gb on disk with rare disk-to-memory operations.

Let's use 100Gb as the estimation for AI and it can be expressed as 10000 times lesser storage than HI. Therefore to be able to be on par with human, AI should have very compact representation of the same knowledge. We cannot create a copy of HI NN using so little resources. That's why we need to use rough model instead of original NN - i.e. classic symbolical AI, which is efficient enough and in the same time very compact, though it does not have good generalization. It can be named "knowlets" - ready-to-use knowledge.

AI memory contains NNs and knowlets. We can use last for areas not important for personality. Practically AI can be named "live" it is has good personality, and it will be only fanny "programm", if it shows intelligence features w/o personality. Hence personality-related mind areas have to be represented as NNs in AI, while all others can be knowlets.
Max size of `NNs is 500Mb / 1K = 500K` neurons. It consists `500K / 100G  = 1 / 2000 = 0.05%` of original HI.
Disk space can be used for inactive knowlets. Operating memory is for the active knowlets, maximum of `500Mb which is 10K * ( 500Mb / 1000T ) = 5T / 1000T = 0.5%` of original HI.
After rounding we can say that active AI contains `0.1% HI in the form of NNs (total 500K neurons), 1% HI in the form of active knowlets of HI and 98.9% HI in the form of passive knowlets`.

We can develop knowlets "in lab" as components, e.g. by using pairs of {knowlet,NN}, where NN is trained separately then somehow converted to the logical form of knowlet, then knowlet is used as plug-in in AI

In fact it is just like human can have artificial legs, ears, but remains being an intelligent.

### CPU Problem ###

Searching via Internet for a while gave me the estimation of 30M human mind neurons active in parallel. It could be enough just to assess our CPU problem.
Each neuron is able to emit about 100 signals per second. If we forget about Biological problem, then it gives us 3G operations per second.
1G simple a+b ops takes about 3 seconds. If we use sigmoid activation function for our artificial neuron, we will use at least one exponent calculation - it takes 200ms for 1M operations, or 20 seconds for 1G. So human mind works at least 100 times faster than my computer.
If we will use more complex neuron structure, it will give us 1000 times favor of human mind over my computer. I'm afraid we cannot communicate with creature having mental processes 1000 times slower than ours. Also it will be hard for our AI to span many computers as described in science fiction. It is probably the possible alternative, but such a multi-agent structure will be much more complex to construct, debug and deploy.

The only way remaining is to reduce a number of operations. The most marginal on this way is the well-known classical symbolic AI theory, which utilizes logic and micro-worlds (i.e. rough models) to build AI. Symbolic AI uses relatively small memory in the form of ready-to-use knowledge for behavior, motorics and mental processes. Most of research community are thinking it is a false approach, because of not "having grounds", able to stuck in uncommon situations - opposing to "connectivist" approach, relying on human-like neural networks.

Therefore we came to basic limitations - we do need fuzzy logic and neural networks, we should reduce neural network activity 1000 times, and we should keep overall activity on par with human mind.

It gives us the below idea - limit active neurons to 30K in 500K NN with inactive neurons - implement "focus" feature with 30K / 500K = with 6% active neurons.

### Feeling Problem ###

Let's clarify what is the feeling.
When speaking about human thinking we can use below non-overlapping grouping of activities in our mind:
  * logical thinking
  * recognizing emotions in sensor data
  * generating of non-emotional behavior
  * generating emotional enrichment of behavior
  * feeling
The emotion is typical human expression of feeling.

Human feeling is internal state of HI representing internal motivation system, can be:
  * **inborn**, hence autonomous from external world - almost sure only body signals can be inborn. Examples are:
    * I want to eat - simple body signal
    * I feel pain - simple body signal
  * **internal state representing desired behavior**. To explain that, let's consider human mind as many Markov processes, each for different typical behavior, with learned state-to-action mapping. Input is matched to one or more process and one or more actions are selected which incline us to do smth - i.e. desired behavior. Examples are:
    * I want ice cream - simple strategy, based on body motivation
    * I love you - complex body motivation combined with complex social strategy
    * I'm happy - complex body motivation combined with zero-error expected/actual signal

Almost sure that AI w/o feeling is treated by people only as machine, more or less stupid. Therefore feeling is critical for personality. Having equivalent to body signals also seems essential for personality. Without body signals the mind is only reflective to external world and AI probably will be unable to build identify.
Body signals serve as input for reward value function in reinforcement learning. Examples are pain, hunger, sexual pleasure, parental instinct. What AI internal motivators will be sufficient to build identify? (open question)

Currently computer software doesn't have feeling as part of design, but it does not mean that computer program cannot implement feeling. If AI will implement feeling, then it means:
  * it will be different from HI, because of human embodiment and related biological-inspired motivations
  * the same feeling can be expressed via both human and non-human emotions - it is a different matter
  * some feelings, quite different from HI, it will not be able to express using human emotions
  * until meeting several AIs together and only allowing to communicate with humans, it will lead to the part of internal state never expressed "as is" and affecting behavior

What is a place for feeling in AI - can it be separate component or it should be ingrained as additional features in other components?
From above:
  * create internal artificial motivators - e.g. knowledge growth (as pleasure), prediction quality (as happiness), code interventions (as pain)
  * connect internal motivation components to multiple networks in form of internal reward function
  * internal reward function is used as means to train a system of feedback recognition
  * feedback recognition system provides reward signal to learn all other strategies
  * any strategy has expected/actual error signal which is part of feeling

### Motivation Problem ###

Motivation Problem is mostly explained in Feeling Problem.
Generally we can split motivation into:
  * **inborn motivation**: HI body signals - exist by design. AI should have hardcoded signals to implement embodiment
  * **curiosity motivation**: exploration behavior in Markov networks
  * **expectation motivation**: expected activity derived from active Markov networks
  * **direct external motivation**: external events intended to play motivational role

Which AI embodiment signals to implement? Let's answer what is the role of HI embodiment signals. Particularly HI embodiment signals represent reward function for human behavior - if you behave properly - you will have lunch, sex and health, providing "behave properly" - is designed by God.
For AI we play God's role, so let's use above feature - Service For People. What embodiment signals can be the best motivators to force AI to provide service for people?
These signals should be personal indirect motivators, requiring to involve Service For People function. Also in HI signals are not constant but appear/disappear and have different attitude from time to time.

AI candidate embodiment signals are:
  * health, explained in terms of percentage of broken Markov networks, where "broken" is state when probability of wrong answer is above some pre-defined limit (keep in mind that newborn AI should have few networks existing, so infant is very healthy despite little knowledge; this metric is highly related to proper interaction with external world
  * feed, explained in terms of consumed useful information; information is treated as "useful" if it caused update of any Markov network; it is internal metric closely related to successful interaction with external world

Personality is emerged from inborn motivations and enriched by expectation motivations.
Learning is direct consequence of presence of Markov networks and is guided by curiosity motivations.
Direct external motivation is part of two-way interaction (communication) with external world.

Still the problem is why Markov networks do exist - it is inevitable that there are some HMM factories existing by design.

### Sensitivity Problem ###

Questions are:
  * What is the function of sensor
  * What computer resources can be allocated to sensors
  * What sensors are required for personality?
  * What input and output characteristics sensors have

**Let's answer what we name sensors.**

Sensors convert external entities into internal entities. Just after birth, internal entity set is empty (at least for vision). So sensors capture external signal, perform transformation to internal entities, create and maintain this set of internal entities. Is microphone is audio sensor like ear? - No, it is only audio capture device.

Where is the boundary between sensors and other mind components? Sensors supply set of primitives representing patterns in terms of input signal - e.g. rectangular bright area with text items, but not a computer monitor.
Sensors do not cover associations and causes. Sensors do represent cause projections into sensor media.

Functions of sensors:
  * external (generated/transmitted by non-part of AI) signal capture
  * media pattern generalization
  * media pattern recognition

Let's list HI sensors:
  * exteroceptive traditional: sight, hearing, touch, smell, taste
  * additional exteroceptive strong: nociception (pain), equilibrioception (balance), proprioception & kinaesthesia (joint motion and acceleration), sense of time, thermoception (temperature differences)
  * additional exteroceptive weak: magnetoception (direction)
  * interoceptive: pulmonary stretch receptors, chemoreceptor trigger zone, cutaneous receptors, stretch receptors in the gastrointestinal tract, sensory receptors in the esophagus, sensory receptors in pharynx mucosa, sensory receptors in the urinary bladder and rectum, stretch sensors that sense dilation of various blood vessels

Also it would be useful to list non-human sensors:
  * analogous: echolocation, dogs smell, cats vision, ctenophora balance receptor
  * different: electroception, pressure detection, current detection, polarized light direction/detection, slit sensillae of spiders, plant vibration/light/water/scents sensors

We can use common for AI and HI role-based complete classification of sensors: self-care, self-control, knowledge capture. Let's consider each category separately.

**self-care** senses.

HI - smell, taste, nociception (pain), thermoception (temperature differences), sense of time, interoceptive sensors.

These type of sensors exists for:
  * feed
  * life-care
  * simple reliable reward function (e.g. father using a belt to adjust son's behavior, or mother kissing her child for good to learn kindness)

We can care about feed and life-care - as good parents, though truly good parents let child to fall to have learned experience.
In the same time looks like nobody tried to learn his children w/o simple reward function motivation.

Finally - for AI we need direct input to reward function accessible externally with certain limitations by anybody having contact.

**self-control** senses.

HI - equilibrioception (balance), proprioception & kinaesthesia (joint motion and acceleration), magnetoception (direction), touch

For AI we need to create controller with its own sensor data for each effector.
For the beginning we can say we use one-to-use relationship between controllers and effectors. Controller should be able to adjust low-level effector operations based on obtained sensor data, without involving remaining mind areas.

**knowledge capture** senses.

HI - sight, hearing

Why "knowledge capture"?
Consider sequence - external signal data -> facts extracted, expressed in internal terms -> generalized representation of facts in neural network = knowledge. No other processing is included - merging data from different senses, mapping to external entities/causes are beyond sensors.
Why other sensors are not named "knowledge capture"? Because their primary role is different - consider self-care and self-control as sensor-related plus reward function role for internal motivation system, while knowledge capture sensors are connected to internal mind areas, containing external world representation.

Sensors span 12% of HI mind.
HI receives all the information via its sensors. Also this information is used to adopt sensors to external world. We can say 5 year-old child HI has its sensors finalized, because it is able to extract any details from any picture, able to speak, understand music, voice, and have all other senses in quite mature state.
In the same time the child does not understand abstract concepts and doesn't have any knowledge that education will give him later (any "symbolic AI" stuff).

12% of HI is 120Tb.
If exclude sleep time, it will give us minimum data flow = `120T / (365 * 5 * 10 * 3600) = 2Mb/sec`. In fact we should multiply this by 3, to say that only after repeating some pattern 3 times we save it in the sensor recognition area.
So after consuming 6Mb per second during 5 years child will complete his/her sensor training.

Let's consider using HTM to implement knowledge capture sensors.
The CPU used for operations in HTM is:
```
HTM_learn_time = number_of_viewed_patterns * one_pattern_process_elops * add_time
one_pattern_process_elops = sum_by_layer( spatial_pooler_elops + temporal_pooler_elops ) = sum_spatial_pooler_elops_by_layer + sum_temporal_pooler_elops_by_layer
layer_area_size = layer_input_size / layer_output_size

spatial_pooler_elops = 1/2 * layer_area_size * layer_output_size * log2( layer_spatial_memory )
temporal_pooler_elops = 1/2 * layer_output_size * layer_temporal_size * log2( layer_temporal_memory )

If consider:
layer_spatial_memory = const
layer_temporal_memory = const
layer_area_size = const
final layer layer_output_size = 1 

Then
sum_spatial_pooler_elops_by_layer = 1/2 * sum( layer_area_size^layer_pos ) * log2( layer_spatial_memory ) = 
1/2 * ( layer_area_size^(layer_count + 1) - 1 ) / ( layer_area_size - 1 ) * log2( layer_spatial_memory ) ~= 
1/2 * layer_area_size^layer_count * log2( layer_spatial_memory )

sum_temporal_pooler_elops_by_layer = 
1/2 * layer_area_size^layer_count * layer_temporal_size/layer_area_size * log2( layer_temporal_memory )

one_pattern_process_elops = 1/2 * layer_area_size^layer_count * ( log2( layer_spatial_memory ) + layer_temporal_size/layer_area_size * log2( layer_temporal_memory ) )

if layer_temporal_size << layer_area_size then
one_pattern_process_elops = 1/2 * layer_area_size^layer_count * log2( layer_spatial_memory ) = 
1/2 * initial_input_size * log2( layer_spatial_memory ) elops

number_of_patterns_in_second = 1/3G / (1/2 * initial_input_size * log2( layer_spatial_memory )) = 
2/3G / ( initial_input_size * log2( layer_spatial_memory ) )
```

Sensors designs differ by:
  * nature of input signal
  * inputs selectivity
  * transformation complexity
  * output capacity
  * throughput
