@@[Home](Home.md) -> [NeoCortexResearch](NeoCortexResearch.md) -> [OnIntelligenceReview](OnIntelligenceReview.md)

---

Below are most interesting thoughts, from my point of view, of really great book by Jeff Hawkins, well-known author of HTM theory and founder of Numenta company, which tries to build commercial products from theory of neocortex.



# Chapter 1. Artificial Intelligence #

  * many people believe that AI is alive and just waiting for enough computing power; AI suffers from fundamental flaw of not addressing intelligence and understanding
  * AI can produce useful products but not intelligent machines
  * Turing's test for intelligence absolutely wrong - trying to produce human-like behaviour
  * Chinese Room argument - without understanding Chinese symbols you cannot understand Chinese language
  * **AI researchers do not attempt to understand brain**

# Chapter 2. Neural Networks #

  * neural networks are based on real nervous system
  * still, neural networks do not account: rapidly changing streams of information, importance of feedback (feedback connections are 10 times greater than feed-forward) and physical architecture of the brain (neocortex is not simple)
    * back-propagation is not like feedback as used only for supervised learning
  * **neural networks settled on over-simplified models** - connectionists
  * neural networks research stopped to evolve, declaring brain-like while being far from it
  * the same problem as in AI - focus on behaviour - correct or desired output
  * **behaviour is manifestation of intelligence but not primary definition of being intelligent**
  * major result - invention of auto-associative memory (Hopfield networks), having feedbacks and able to store delays on feedback connections; but these are ignored
  * neuroscientists create mind maps, trying to find where certain activity arises but not how
  * functionalists: function is important, not media; if replace brain with artificial neurons, it will do the same
  * **kludge** - programs, written without foresight
  * cognitive wheel - invented by human, not by nature; but intelligence is internal property of brain - so need to understand it, not emulating just behaviour

# Chapter 3. Human Brain #

  * **neocortex** - thin sheet of neural tissue enveloping older parts of brain
  * intelligence occurs in neocortex; other parts make human being
    * all essential aspects of intelligence occur in the neocortex, with important roles also played by thalamus and hippocampus
  * neocortex is 6 layers total of 2 mm thick
  * size of neocortex reflects **level of intelligence**
  * neocortex has very high density of neurons
    * 1mm x 1mm square area has 100K neurons; total 30G neurons in neurocortex
  * **neocortex is the same across all its surface**
  * neuroscientists thought neurocortex consists of functional areas
    * functional areas are the same for almost all people
  * **neocortex functional areas are arranged in branching hierarchy**
    * hierarchy is nothing related to physical locations but how regions are connected
    * lower areas feed information up to higher areas by way of a certain neural pattern of connectivity, while higher areas send feedback back to lower areas using a different connection pattern; there are also lateral connections between areas in separate branches
    * **lower functional areas are primary sensory areas** - where sensory information arrives in the neocortex, e.g. V1 (primary visual area) - which feeds to V2, V4 (objects of medium complexity), IT, MT (motion) and others; the same for other sensors - A1 (auditory), S1 (somatosensory)
  * **sensory information passes into association areas** - areas receiving information from several senses; their functions remain unclear
  * **areas in frontal lobe create motor output**; they are also hierarchically arranged
    * lowest area, M1, sends connections to the spinal cord and directly drives muscles
    * higher areas feed sophisticated motor commands to M1
  * **information flows both ways - from sensors to muscles and vice versa**
    * **much more information flows as a feedback than from senses**
  * neuron has body, axon and dendrites; axon connecting of one neuron to dendrite of another neuron, forms a connection - synapse
    * synapse can be excitatory or inhibitory
    * strength of synapse changes depending on behaviour of two neurons (Hebbian learning)
    * new synapses can be created
    * changes in synapses causes memories to be stored
  * 8 of 10 neurons are pyramidal cells
    * each sends lengthy axon laterally to distant areas, or down to lower brain structures like thalamus
    * each pyramidal cell has 1-10K synapses; it makes total of 30T synapses
  * top layer of neocortex is a lot of axons but few cells
  * **neocortex makes the same operation in all its areas**
    * differences arise from how areas are connected to each other and to other parts of central neural system
    * the same algorithm - for vision, hearing and so on
  * neocortex is dividing itself on functional areas long into childhood, based purely on experience
    * by experiments in newborn animal areas interchanged surgically
    * **no areas in neocortex are unused** even if some senses are not functioning (blind)
    * **genes define architecture of neocortex**, but within this structure mind is high flexible
  * cortical algorithm can be deployed in novel ways, with novel senses in machined cortical senses, outside of biological brains
  * **data from different senses are sent to the cortex in the same way as spatial and temporal patterns**
    * visual information sent via 100M-fiber cable, with transit through thalamus to V1 (V.S.: a bit incorrect, exact picture is that 100M photoreceptors are converted by retina into 1.3M fibers of optic cable which is split in the middle into several branches and 1M fibers go to thalamus LGN and further to V1)
    * sound is carried via 30K-fiber cable through old mind areas to A1
    * spinal cord carries touch and internal sensations information via 1M-fiber cable to S1
    * it is important where patterns enter neocortex
  * vision relies on temporal patterns
    * 3 times per second eyes make sudden movement - saccade, then stop - fixation
    * pattern arriving to V1 is completely different with each saccade
    * time is a central component of a vision
  * sound has spatial patterns by means of different sequences activating different regions of cochlea bone; it changes in time - resulting in spatial-temporal patterns
  * ability to make complex use of touch depends on continuous time-varying patterns of touch sensation
  * **neocortex uses only patterns and extremely flexible**
    * it even does not know where body ends
    * it can quickly adopt to changes in the body
    * sensory substitution - if project camera image to sensing area, blind can see
  * **brain is pattern machine**
    * it does not depend on any specific sense to be intelligent
    * **brain perceives model of the world not the real world**
    * that's why no much difference from perception of written and spoken languages

# Chapter 4. Memory #

  * **external world patterns stream, via old brain, into neocortex**
  * **brain-as-computer analogy is wrong**
    * neurons are quite slow - 5ms per operation = 200 ops/sec
    * AI society says computer is unable to emulate mind because it is parallel
    * try 100-step rule - e.g. you can recognise image in less than second - in 100 steps; even parallel computers will not be able to do this in 100 steps
    * brain does not compute answer but extract it from memory
  * **neocortex is memory system, not a computer**
  * consider task of catching ball
    * human does this easily; almost impossible to teach robot arm to do this - it requires fast 3D vision, computing ball path and computing robot arm movement
    * brain uses memory of muscle commands: 1) memory recalled by sight of ball 2) recalls temporal sequence of muscle commands and 3) retrieved memory adjusted to accommodate the particulars of the moment - ball's actual path and body position
    * brain handles variances by using invariant representations in the neocortex, not by differential equations
  * **difference between neocortical memory and computer memory**
    * neocortex stores sequences of patterns
    * neocortex recalls patterns auto-associatively
    * neocortex stores patterns in and invariant form
    * neocortex stores patterns in a hierarchy
  * **sequence of patterns:**
    * impossible to think about anything complex if not series events or thoughts
    * one pattern evoke the next pattern
    * with a conscious effort we can jump, but then follow temporal sequence
    * memory recall follows pathway of associations
    * e.g. alphabet - sequence of patterns, hard to recall in reverse order
    * memory of tunes contain temporal sequences: if start from specific note, can play forward but not backward; cannot recall all the tune at once
    * all memories can be extracted with proper cues - even those that haven't thought for many years
    * only few neurons and synapses are active in the moment; one active set replaced with another set by sequences
  * **auto-associative recall:**
    * recall complete pattern when given only partial or distorted pattern
    * recall spatial items and temporal sequences - brain is not confused seeing part of object
    * during conversation we do not hear some words which we perceive
    * recall by middle or by end of sequence
    * if you think about smth and instantly see your friend - recall occurs - you are unavoidably switching to related sequences
    * random thoughts never occur - thought means chain of memories; non-deterministic
  * **invariant representations:**
    * brain remembers important relationships in the world independent from the details
    * AI auto-associative memories are failed when we move, rotate, scale picture, while it is not a problem for cortex
    * we perceive something as constant when patterns are novel (never seen) or changing
    * we use **invariant representation** to refer to internal brain representation
    * if show face in various positions - on some upper level activates the same neurons
    * it should be easy - we use it automatically and it is very fast - but it is one of the biggest problems for science and no power computer can solve it
    * Plato asked long ago - how we understand ideal circle or dog concepts?
    * you can create signature with hand or elbow - it will be different but you play the same abstract motor program - invariant representation in motor cortex - motor command
    * consider tune - you recognize tune as the same if started from different notes (transposed) - you can play known tune from some note even if you never heard it from this note; it means tune is stored by intervals not by absolute notes
    * in recognising faces we consider spatial intervals - size of eye compared to size of nosed; colour of hair compared to colour of eye
    * memory storing, recall and recognition occurs on level of invariant forms
  * **memory prediction occurs by combining current inputs and invariant representations**

# Chapter 5. A New Framework of Intelligence #

  * we can understand smth but without any actions
  * **what we perceive is a combination of sense and memory-derived predictions**
  * **altered door experiment**
    * smth in the door you open every day is changed (one of dozens parameters)
    * you will quickly detect that something is wrong
    * brain makes low-level sensory prediction about what is expected
    * sense neurons become active in advance of actual input
    * expectation violation will cause you to take notice
  * **correct prediction result in understanding**
  * **incorrect prediction result in confusion and prompt you to pay attention**
  * **prediction is primary function of the neocortex and the foundation of intelligence**
  * **behaviour is by-product of prediction**
  * examples - step on broken stair, music song in album; pleasant sensation of mild uncertainty when you listen album on random shuffle
  * prediction is not exact - our **mind makes probabilistic predictions** - please take me... "salt", "pepper" but not "sidewalk"
  * in music you never heard before - you have strong expectations (beats, rhythm...)
  * we see what we expect to see as often as we see what we really see - e.g. we see picture over blind spot in the eye - place where eye nerve goes; holes are in different locations but we do not see black hole even when we close one eye
  * consider saccade and person having extra nose instead of one eye
  * human brain is more intelligent because it can make predictions about more abstract kinds of patterns and longer temporal pattern sequences
  * you can predict smth (e.g. smbd who wants you to make smth)
    * you do not know how it will be exposed but you expect it
    * **higher intelligence is not a different kind of process from perceptual intelligence**
  * intelligence is measured by the capacity to remember and predict patterns
  * intelligent understanding and behaviour are completely separate
  * **neocortex appeared after animals already evolved sophisticated behaviour**
    * in the beginning neocortex served to efficiently use existing behaviour, not to create new behaviour
    * 100M years ago were animals with complex behaviour
    * difference between human and reptile - large cortex
    * human has old (primitive) brain - ancient structures in the brain - for blood pressure, hunger, sex, emotions and many aspects of moving
    * neocortex appeared 10M years ago, only mammals have it
    * only 2M years ago neocortex has expanded dramatically - relatively new structure
    * cortex not only remember sense data but behaviour produced by old mind
  * our motor and planning abilities vastly exceed those of of animals
    * neocortex generates sophisticated behaviour unique to humans
    * neocortex algorithm is so powerful that with little rewire it can create new, sophisticated behaviour
    * neocortex can make accurate sensory predictions only if it knows what behaviours are being performed
    * brain first moves the arm then predicts what it will see
  * our brains are connected differently
    * back part contains inputs where sense data arrive - eyes, ears...
    * front part contains high-level planning, thought, and motor cortex
  * most animals rely on older parts, human cortex usurped most of motor control
  * if you damage motor cortex - human becomes paralysed
  * dolphins have big neocortex but not so connected to motor areas
  * **intelligence started as memory system added prediction**
  * neocortex evolved in size and it started to interact with motor system of the old brain
  * all this is **memory-prediction framework**
  * Alan Turing was wrong: **prediction, not behaviour, is the proof of intelligence**

# Chapter 6. How The Cortex Works #

  * brain theory is like solving giant puzzle - because of many low-level facts; theory is incomplete - some facts are not understood yet
  * **top-down approach** - find how cortex can memorise and and store sequences, make predictions, form invariant representations, create and store model of world, independent of changing circumstances

## Invariant representations ##

  * visual regions, involved in recognition of object - V1, V2, V4, IT
    * V1 has input of 1M axons from optical nerve
  * cortex is a big sheet of tissue containing functional areas
    * regions are connected by large bundles of axons, transferring information all in once
    * collective activity of bundle is named **pattern**
  * saccades create too different images because of fovea and jerking shifts; still you do not aware about these changes
  * V1 area neurons have **receptive fields**
    * each neuron knows about pinsize portion of visual space; but nothing about faces, cars and so on
    * each neuron is tuned for specific form of patterns - e.g. line or edge
    * from one fixation neurons will fire strongly, from others - weakly or not at all
  * in IT we find cells that become and stay active when objects is appearing on visual field, e.g. face
    * IT cell's receptive field covers most of visual space and fires from faces
    * in 4 areas cells changing from rapidly changing, spatially specific tiny feature recognition cells to constantly firing, spatially non-specific, object-recognition cells - invariant representation of faces
    * no computer still solved this problem with robustness and generality
    * bundles of feedback axons, more than feed-forward, go from higher regions like IT to V2, V4, V1
    * prediction requires comparison between expectation and actual input
  * in real human mind regions are interconnected in all sorts of ways
    * **majority of human cortex consists of association area**
  * we see the same feedback, prediction and invariant recall in auditory cortex
    * we cannot recognise object in one pattern of input, not like vision
    * neural activity for objects must last longer than individual input patterns
    * pattern coming from your ear or touch sensors does not contain sufficient information at any one point of time what you are hearing or feeling
  * the higher up in the cortex you go, the fewer changes over time you should see
    * in vision we have also ability to recognize spatial patterns; but normal vision requires constant eye movement

## Integrating the senses ##

  * you can have **visual sensor data expectations emerged from auditory signal**
    * information flows up auditory hierarchy to association area connecting vision and hearing
    * representation then flows back down visual and auditory hierarchies, causing both visual and auditory predictions
    * this kind of **multi-sensory prediction** occurs all the time
  * information simultaneously flows up and down sensory hierarchies to create unified sensory experience involving prediction in all senses
    * entire neocortex, all sensory and association areas, acts as one
  * all predictions are **learned by experience**
    * if there are consistent patterns among inputs, cortex will use them to predict future events
  * motor cortex behaves in almost the same way as sensory region
  * input to sensory area can flow to association area, which can lead to a pattern flowing down the motor cortex, resulting in behaviour
    * in sensory cortex we say predictions, in motor we say commands
    * **no pure sensory or motor area** (V2 visual area controls eye muscles)

## A new view of V1 ##

  * higher regions of cortical hierarchy form invariant representations
    * why only at the top? - **cortex is the same everywhere**
    * there are V1, V2, V4, IT regions - every is regarded is continuous, covering all visual area, IT at the top
  * classical view - V1 extracts low-level primitives, then V2, V4 and invariance created only in IT
    * why IT so special?
  * consider you see face in one corner of V1 or, next time, in another corner
    * these parts are distant and are not connected, still do similar action
    * all high regions receive inputs from many other regions, while V1 is connected only to V2 - why it is different?
  * solution: **V1, V2, V4 should be viewed as collections of many smaller regions**
    * V1 area is the size of passport and it is made up of numerous separate little areas, connected to neighbours only indirectly via higher regions
    * **IT is single region having birds-eye view of entire visual world**
    * every region has a converged set of input regions  and sends projections back as predictions
    * each V1 region can be regarded as separate sensory stream
    * V2 and V4 are visual association areas
  * **every region forms invariant representations** = with only part of world and basic vocabulary, but do the same job as IT

## A model of the world ##

  * all objects are composed of subobjects that occur consistently together
    * we assign a name to set of features that consistently travel together
  * design of cortex and its learning method discover hierarchical relationships in the world
    * higher regions of cortex are maintaining representation of high-level structures while lower regions are maintaining representations of more detailed objects
    * hierarchy allows to know that you listen to song and album of music in the same time
    * higher regions are tracking big picture while lower levels are actively dealing with fast-changing, small details
  * we can see, hear, touch only tiny part of the world in one moment, so **information flows as sequence of patterns**
  * sequence is set of patterns that generally accompany together, but **not always in a fixed order**
    * components of face are can look at are checked in different order
  * real-time world objects can be abstract - e.g. word or theory
    * **brain treats physical or abstract objects in the same way**
  * predictability is definition of reality - predictable sequence of patterns must be part of larger object that really exists
    * regions assign names to predictable sequences and pass names to higher regions

## Sequences of sequences ##

  * as information moves up, we see fewer and fewer changes over time
  * each cortical region has a name for known sequence - **set of cells remaining active while sequence is playing**
  * if sequence is recognized, no details are passed to higher region
  * lower region can recognize sequence of sounds comprising phoneme, higher region will recognize sequence of phonemes comprising word, then phrases and so on - sequences of sequences
  * if move down - stable patterns get **"unfolded" into patterns**
  * consider you have memorised some speech and want to recite it
    * speech is unfolded in one region into sequence of phrases, next region - into sequence of words
    * then sequence splits and travels down auditory hierarchy and motor hierarchy
    * motor hierarchy ends with commands to muscles to make sounds
    * (auditory path makes expectations which assist to control motor!)
    * invariance makes possible to type speech instead of speak - taking a different path from some level down another region of motor cortex
    * single memory of speech can take many behavioral forms - in any region invariant pattern can bifurcate and follow different path down
  * for efficiency, representations of simple objects are reused among higher-level sequences - for both sensory and motor cortex regions
  * when you perceive complex object using saccades, predictions about result of each saccade are cascading down your visual hierarchy
    * sequence of saccades is not fixed and depends on your own (what it means - sick!) actions
  * how sequences are memorised and represented is like military hierarchy - consider general saying to move army to another location
    * high-level command is unfolded into more detailed sequences down the chain of command
    * lower-level commanders recognize it means known sequence of steps in their responsibility
    * at the bottom it resulted in thousands of different actions
    * reports of what happened are generated at each level
    * reports are aggregated and reported on the top as "moving to given location is ok"
    * if something is going wrong and cannot be handled by subordinates - issue raises up until someone knows what to do next - knows how to handle it and does not see this as an exception (actually in reality I think it happens differently - upper guy asks what is the impact - what will not be done or when it could be done in terms of upper plan - then he checks whether his plan is flexible enough in terms of keeping more upper commitments, if not - forwards up the command chain; if plan have to be changed - new commands are generated)
    * **other possibility is to have plan B - thing is unexpected for privates, but expected for upper commander**
  * in cortex, **when events are not anticipated, regions consider it as errors**, then information is progressed up the cortical hierarchy until some region can handle this (if V1 cannot recognize picture - I think it is forwarded to hippocampus which causes having episodic memory)

  * a number of possible patterns is tremendous, **region sees only tiny part in its lifetime**
  * region first classifies inputs as one of limited number of possibilities (**spatial pattern**) and then looks for sequences (**temporal pattern**)
    * each input pattern is different from stored patterns
    * brain **must** classify even if no obvious choice
    * both classification and sequence formation are necessary for **invariant representations and all regions do them**
    * some spoken or written words are not recognisable beyond of context
  * memory of sequences allows not only to resolve ambiguity, but also to predict next input
  * cortex region learns how to **modify its classifications**
    * bucket can change its meaning to allow best fit next times - cortex is flexible
    * forming new classifications and sequences is how you remember this world
  * **sequence name is composed of spatial names** (insight?)
  * our brain **does not remember snapshots of retina**
    * memories of object are distribute over hierarchy
    * typical cortex learns sequences if internal representations, which are themselves sequences of invariant memories
    * unlike camera, brain stores world as is (behaves), not as it appears
    * **stored sequences reflect real invariant structure of the world itself**
    * order is determined by the world structure

## What a region of cortex looks like ##

  * method to learn and recall sequences is most essential element in forming invariant representations
  * cortical regions vary in size, largest are in primary sensory areas - the size of letters
  * density and shape of cells differs from top to bottom of cortex tissue which defines layers
    * layer 1 has very few cells, **consists primarily of axons running parallel to cortical surface**
    * layer 2 has **many tightly packed pyramidal cells**
    * layer 3 is like layer 2
    * layer 4 has **star-shaped cells**
    * layer 5 has regular pyramidal cells and **extra-big pyramidal cells**
    * layer 6 has some other unique cell types
  * vertically cortex is split into **columns** (there are micro-columns, columns and hyper-columns)
    * layers within column are connected by axons, that run up and down
    * vertically aligned cells in each column tend to become active for the same stimulus
    * different columns in V1 respond for different elementary shapes
    * active cell in layer 4 causes cells in layers 2 and 3 to become active, which cause cells in layers 5 and 6 to become active
    * neocortex is like very dense thin brush covered from one side with long extra-thin hairs - layer 1
    * information mostly flows vertically in 2-6 layers and horizontally in layer 1
  * 90% of synapses within each column come from places outside the columns itself
    * some are lateral - from neighbouring columns
    * others come from halfway across the brain
  * **column is basic unit of prediction** (primary point of the book)
    * to predict the next note of the song you need to know **song name, where you are in the song, last note and how much time passed from last note**
  * **upward flow** - from lower regions to upper regions in cortical hierarchy
    * converging inputs from lower regions arrive at **layer 4 - main input layer**; by the way inputs make synapses in layer 6
    * layer 4 sends projections to layers 2 and 3 within the same column
    * many layer 2 and 3 cells send axons to input layer of the next higher region
  * **downward flow** - from upper regions to lower regions
    * layer 6 project to layer 1 in the lower regions
    * in layer 1 of lower region axons  spread over long distances and can activate many columns
    * cells in layers 2, 3, 5 have dendrites in layer 1 and can be excited by feedback
    * layers 2 and 3 axons form synapses in layer 5 before leaving cortex and can excite layers 5 and 6 cells
    * downward flow started in layer 6, then has multiple-path branch in layer 1 of lower region; some cells in layers 2, 3 and 5 are excited; some them excite layer 6 cells; which projects to next lower region and so on
    * signal in axons, coming from layer 6, is spreading with speed of **200 miles/hour**
  * why information is spread across layer 1
    * need to convert internal representation into specific prediction
    * requires ability to decide which way to send signal as it propagates down the hierarchy
    * remember we can say word in memory or write it
    * when hear note of melody, brain has to take one of specific intervals and convert to next note
    * layer 1 does the work of branching
  * another indirect method of region communication - to implement **auto-associative memory**
    * consider Hopfield networks - recurrent, when output of group of artificial neurons is fed back with delay to all neurons, causing **ability to learn sequences of patterns**
    * as per Jeff Hawkins, the same is for cortex but with **columns instead of neurons**
    * output of all columns is fed back to layer 1
    * layer 1 contains information which columns were just active in this region
    * large layer 5 cells in M1 make direct contact with muscles and spinal cord
    * in V2 and V4 **large layer 5 cells project to the part of brain that moves eyes**
  * axons in large layer 5 cells are split in two, one branch goes to thalamus
    * thalamus receives many axons from every part of cortex and sends axons back to same areas
    * thalamus is essential for normal living - cannot think with damaged thalamus
    * there are couple of paths from thalamus to cortex
    * one path starts from large layer 5 cells that projects to non-specific thalamic cells
    * non-specific thalamic cells back to layer 1 over many cortex regions
    * this circuit is exactly delayed feedback to learn sequences
  * layer 1 has two inputs
    * active columns spread activity across layer 1 via thalamus
    * first inputs are **"name of the song"** - inputs from above
    * second inputs are **"where we are in the song"** - delayed activity from active columns
    * thus layer 1 contains full information to make prediction if apply to invariant representation in the region
  * after all cortex can learn and recall **multiple sequences of patterns**

## How cortex region works: details ##

  * there are 3 circuits in mind
    * **converging patterns** going up the hierarchy
    * **diverging patterns** going down  hierarchy
    * **delayed feedback** though thalamus
  * questions
    * how cortex region **classifies its inputs** - like buckets
    * how cortex region **learns sequences** of patterns
    * how cortex region **forms constant pattern** - sequence "name"
    * how cortex region **makes specific predictions**
  * assume cortex **column represents one bucket** (in real brain nothing is represented by one neuron or one column)
    * layer 4 cells fire if inputs from below regions have pattern for this bucket
    * inputs are often ambiguous and several columns can fit the same inputs, still cortex needs to decide which one is correct
    * column with strong input should prevent other columns from firing (I think electrical mechanism is in action - all columns receive inputs simultaneously, but each has its own level of matching its pattern - match factor causing accumulating energy; this energy fills neuron body, until it fires; greater match factor makes most matching column to fire first; firing quickly changes electrical potentials - which makes connections inhibitory)
    * brain have **inhibitory cells** - inhibit other neurons in a neighbourhood of cortex - one winner
    * inhibitory cells affect only area surrounding column - so many columns are still activated simultaneously
    * to make it simple - let's think only one winner column exists
  * consider **storing of sequence of patterns**
    * consider one layer 4 cell fired - causing layers 2 and 3 cells to fire, then layer 5, then layer 6 - finally all column becomes active
    * 2,3,5 cells have many synapses in layer 1 - if they are active when cells fire, then synapses become more strong according to Hebb
    * if this occurs often, **synapses become strong enough** and can activate 2,3,5 cells even if layer 4 cells are not active - cells learn to anticipate when to fire based on patterns in layer 1 - means **prediction**
    * half of inputs for layer 1 are from layer 5 of neighbouring columns and regions - representing what was happening moments before - columns were active before this column becoming active - last state that was successfully perceived
    * **if the order of patterns is consistent over time - columns will learn the order** - columns will fire one after another in proper sequence
    * other half of inputs for layer 1 comes from layer 6 in higher regions - more static, represents name of higher sequence currently perceived
    * finally - layer 1 represents both **name of sequence** (from upper region) and **last item in the sequence** (from all columns in this region); particular column can be shared among many different sequences without getting confused; **columns learn to fire in right context and in correct order**
    * 90% of column synapses are from other columns, most of them are not from layer 1; e.g. 2,3,5 cells have thousands of synapses from both layer 1 and from neighbouring columns - from the same layer; activity in nearby columns is highly correlated
  * consider **forming name for a learned pattern**
    * what information is sent to higher region
    * layers 2 and 3 cells send axons to higher region - activity of these cells is input to higher region; **before sequence is learned, details are passed**; but for hierarchy to work constant pattern should be relayed during learned sequence - sequence name, not the details
    * **layers 2 and 3 outputs are turned off when column predicts its activity**
    * no final understanding how it occurs - below is favourite (for Jeff Hawkins) plausible method
    * assume layer 3 consists of layers 3a and 3b (used by some anatomists)
    * assume **layer 2 cells learns to stay on during learned sequence** - all cells, as a group, represent **name of sequence** - if sequence contains 3 patterns, then cells stay active as we are within all 3 patterns
    * assume **layer 3b cells fire when prediction for outputs was incorrect** - unexpected pattern
    * before learning layer 3b fires and layer 2 is quiet, after learning vice versa
    * assume **layer 3a cells, having dendrites in layer 1, are inhibitory and prevent layer 3b from firing** when layer 1 contains appropriate pattern
  * how to **keep layer 2 cells active** throughout all patterns of known sequence
    * this is difficult as layer 2 cells should stay active even when their columns are not active
    * assume layer 2 cells form preferentially with layer 6 axons from higher region
    * when higher region sends  pattern down to layer 1 of this region, layer 2 cells become active, representing all columns that are member of sequence
    * since layer 2 also project back to higher region, they  form **semi-stable group of cells** (actually they don't just stay active - but fire synchronously in a rhythm)
    * name predicted by higher region stays active (actually it means cells represent downward signal, not upward - but my suggestion - **cells stay active only if supported by sequence patterns**)
  * above are basic operations for forming invariant representations

  * questions:
    * how to make **predictions about events we have never seen before**
    * how to **decide about multiple interpretations**
    * how region makes **specific prediction from invariant memories**
  * use last specific information to **convert invariant prediction into specific prediction** - in other words combine feedforward (active input) with feedback (prediction in an invariant form)
    * consider melody and columns representing possible intervals - C-E, C-G, D-A, etc. (includes starting note)
    * assume higher region expects musical interval - fifth - it causes layer 2 cells to fire for all columns with interval of fifth
    * inputs to the region are specific notes, and if you see D - then all columns starting from D, have partial input
    * intersection of two sets gives us D-A interval which is activated
  * how to **find intersection**
    * layers 2,3 axons form synapses in layer 5
    * layer 4 axons from lower regions make synapses in layer 6
    * layer 6 cells receiving both active inputs - will fire - **represents specific prediction of what is happening**
    * layer 6 cell is active either if column event is **occurring or will occur**
    * layer 6 cell **represents interpretation of the world** regardless of whether it is true or just **imagined**
    * this mechanism resolves ambiguities from sensory inputs
    * **intersection is what we perceive**
    * it is how we split motor stream to either write or speak memorised word
  * in addition to projection to lower regions, layer 6 cells can send their output back into layer 4 of the same column
    * our **predictions become inputs**
    * it is **the way we have dreaming or thinking** - folded feedback or imagining

  * what we see, hear or feel is highly dependent on our own actions - how can we predict sensory input if it depends on our actions?
    * to predict what we will sense next (to interpret what we sense) we need to know what actions we are undertaking
    * **motors/behaviour and sensors/perception are highly interdependent**
    * **perception and behaviour are almost the same** - most of regions participate in creation of movement
    * layer 5 cells project both to upper region layer 1 via thalamus and to **motor areas of the old brain** - thus **sensory and motor just happened are both available in layer 1**
  * motor behaviour is also represented as **hierarchy of invariant representations**
    * you generate movement required for particular action by **thinking of doing that in detail-invariant form**
    * in downward flow it gets translated into complex and detailed sequences - in both sensory and motor hierarchies
    * if region IT of visual cortex is perceiving nose, the mere **act of switching to representation for eye will generate saccade necessary to make this prediction a reality**
    * particular saccade depends of where the face is - close face requires large saccade
    * details of saccade are determined as prediction of seeing eye moves toward V1
    * when your own behaviour is involved, your **predictions not only  precede sensation, they determine sensation**
    * as cascading prediction unfolds, it **generates motor commands necessary to fulfil the prediction**
    * **unfolding of sequences causes thinking, predicting and doing**
    * it is goal-oriented behaviour - holy grail of robotics, built into cortex
    * we can turn off our motor behaviour (how?!) - think of seeing without actually seeing this or think about going without actually doing this
    * **thinking of doing something is literally start of how we do it**

## Flowing up and flowing down ##

  * each region tries to interpret its inputs as **part of known sequence of patterns**
    * columns try to anticipate their activity; if succeeded they pass on stable "name" pattern
    * unexpected patterns passed (as is, how?) to next higher region - layer 3b cells, that were not part of expected sequence, fire (only part of pattern propagates?)
    * higher region can understand unexpected pattern as next part of its own sequence
    * if higher region is not able to recognize (maybe predict as inputs can be unique?) pattern, then it propagates up until some higher region can interpret it as part of its normal sequence and generates prediction (maybe hippocampus can recognize earlier that it is novel data and cannot be recognized by any layer? Also consider modulation connections that can force brain other pass errors up or just ignore)
    * the higher unexpected pattern goes up, the more regions get involved
    * after higher region generates prediction, it flows down
    * if prediction is not right, error is generated and will climb up the hierarchy until interpreted
    * finally: **observed patterns flow up and predictions flow down**
  * in known and predictable world, only few regions are involved and predictions occur in the lower regions; **you can think about something else** while doing smth
  * **in novel situation, most of the cortex is attending to novel events and you are unable to think about anything else**
  * consider "aha" moment - **sensation of sudden comprehension**
    * for instance you are looking to ambiguous picture, trying to understand what is drawn there
    * eyes scan everywhere (saccades for variants?)
    * high-level cortex tries a lot of hypotheses but related predictions conflict with input and cortex tries again - during this time brain is totally occupied
    * after all you get right prediction and in less than second each region is given sequence that fits the data

## Can feedback really do that ##

  * connections in cortical hierarchy are **reciprocal**
    * if region A projects to region B, then B projects to A as well
    * there are more axons going back than forward
  * still prevailing paradigm is that feedback plays minor, "modulatory" role; not widely agreed that feedback can instantly and accurately cause layer 2 to fire
    * feedback signal is spread over large areas of layer 1
    * brain has several modulatory signals like alertness
    * synapses close to cell body have strong influence on cell firing, but vast majority of synapses are far from body and scientists believe effect of distant synapse would dissipate when reaches cell body
  * **feed-forward flow goes by synapses that are close to cell bodies**
  * **feed-back flow goes by synapses that are far from cell bodies**
    * layers 2,3,5 cells send dendrites into layer 1 and form many synapses there - but only few for particular layer 1 fiber
    * layer 1 has mass of synapses but they are far from cell bodies
  * resolution to dilemma - neurons behave differently from classical model
    * synapses on distant thin dendrites can play active and highly specific role in firing
    * if there were **two synapses close to each other on thin dendrite, they act as "coincidence detector"** - if receive input spike in the same small time window, they can have large effect on cell despite they are far from cell body
  * massive feedback and multiple synapses cannot be just for modulation
    * they allow to learn hundreds of precise coincidences on feedback fibers
    * it means that any particular feature can be associated with thousands of objects and sequences

## How the cortex learns ##

  * **learning and memory occur in all layers, in all columns, in all regions**
    * Hebbian learning - fire together, wire together
    * some synapses change strength in response to small variation in the timing of neural signals, some changes are short-lived, some changes are long-lived
    * auto-associative **classical Hebbian learning algorithm** can learn spatial patterns and sequences of patterns, but **cannot handle variations**
    * HTM theory get around this limitation using **hierarchy of auto-associative memories and specific columnar architecture**
  * after you are born your cortex needs to learn all the structure of the world
  * two basic interacting components of learning: **forming classifications of patterns and building sequences**
  * basics of forming sequences is to group patterns which are parts of the same object
    * one way to is to group patterns **occurring contiguously in time** - e.g. if you slowly turn some object in your hands, your brain knows it is the same object and associates with different visual patterns
    * another way you need **outside instruction** - e.g. to learn that apples and bananas are fruits, you need external teacher
    * either way your brain slowly builds sequences of patterns that belong together
    * **as region learns sequences, inputs to the next region changes** from individual patterns to groups of patterns - from letters to words, from notes to melodies
    * as inputs to higher region become more object-oriented, higher region can now learn sequences of higher-order objects
  * **during repetitive learning, representations of objects move down the cortical hierarchy** (remain in upper, replicate?)
    * **early years of life memories of world first form in higher regions of cortex**, then they are re-formed in lower parts of hierarchy
    * patterns are not moved - brain has to re-learn patterns
    * as simple representations move down, region at the top can start learn more complex and subtle patterns
  * not suggesting that all memories start at the top of the cortex
    * **layer 4 pattern classification starts at the bottom and moves up** (not clear)
    * as it does, we start forming sequences, then sequences move down
    * **memory of sequences re-form lower and lower in the cortex**
  * consider learning to read
    * we start learning we reading **one letter at a time**
    * after years of practice a person can read quickly
    * we get to the point when **we don't see individual letters but instead recognise entire words and even phrases at a glance**
  * do we see letters while reading by words?
    * yes - but recognition of letters occurs in V2 or V4
    * **in IT no letters are represented**
  * another example - music
    * start from single notes
    * we learn to perceive melody as a major structure, detailed sequences have been memorized lower down
    * this type of learning occurs in **both motor and sensory areas**
  * young brain is slower to recognise inputs and slower to make motor commands
    * **young brain has not yet formed complex sequences at the top and therefore cannot recognise and play back complex patterns**
    * child's language is simple, his music is simple and social interactions are simple
  * when you study particular set of objects over and over, cortex moves memory representations lower
    * it frees up the top for more subtle, complex relationships (frees?)
    * **this is what makes an expert**
  * experienced business manager can readily see flaws and advantages of organisation, whereas novice manager can't understand this
    * novice's model is not sophisticated
    * we start by learning the basics, the simplest structure
    * **after practice we can learn higher-order structure**
    * experts have brains that can see structure of structure and patterns of patterns beyond what others do
    * **talents and genius have genetic differences** that allow them to have high-level patterns, you cannot be genius by practice

## The hippocampus: on top of it all ##

  * brain parts communicating with neocortical sheet (what about cingulate gyrus?)
    * **basal ganglia** - primitive motor system (action selection, inhibition of motor systems, controlled by pre-frontal cortex, consists of striatum, substantia nigra and subthalamic nucleus); neocortex is responsible for all complex motor sequences and can control all limbs, basal ganglia is not important for intelligence
    * **cerebellum** - learned precise timing relationships of events; human without cerebellum is pretty normal except unnatural moving
    * **hippocampus** - stores memories of specific events and places
    * neocortex function can be described independently of basal ganglia and cerebellum, but not of hippocampus; **without hippocampus you cannot form new memories** (H.M. patient), but be normal for anything else
  * hippocampus is essential for learning, common view is that new memories are formed there, and **only in few days, weeks, months these memories are transferred to neocortex**
    * but **sensory data goes to the cortex without first passing though hippocampus**
    * connections between hippocampus and neocortex suggest that **hippocampus is the top region of neocortex**, not separate structure
    * over evolution neocortex appeared as additional level between old brain and hippocampus
    * hippocampus connects to many parts of old brain
  * pattern that is truly novel will escalate further and further up the hierarchy
    * when you reach the top, what you have is the data that cannot be understood (partial pattern, part of input!) - truly new and unexpected
    * these new data items are stored in hippocampus
    * new data will not be stored forever - either it will be transferred to neocortex, or will be eventually lost
    * if you have generally not novel data - it will be not memorised as episodical memory
    * the more you know the less you remember
  * hippocampus is good in quickly storing whatever pattern it sees
    * hippocampus can recall novel memories, allowing them to store in cortical hierarhcy in a while
    * you can **instantly remember novel event in hippocampus**
    * you will **permanently remember something in cortex only** if you will permanently expirience it over and over, **either in reality or by thinking of it**

## An alternate path up the hierarchy ##

  * cortex has second major path for passing information from region to region, up the hierarchy (not skip levels?)
    * path starts with **layer 5 cells that project to thalamus** and then to next higher region
    * **if two regions connected directly, they are also connected via thalamus**
    * information is passed **only up the hierarchy, not down**
  * second path has **two modes of operation, depending on thalamus cells**
    * in one mode, path is mostly closed
    * in another mode, information flows accurately between regions
  * consider word **imagination**
    * it can be perceived in one fixation
    * now look into 'i' letter in the middle
    * now look at the dot over that 'i' letter
    * **eyes receive the same information from V1 but IT region perceives different things, different level of details**
    * IT knows and able to recognise all three objects
    * when you perceive whole word, V4, V2, V1 handle the details, IT knows only about word
    * you can perceive letters **if you choose** - you do **attentional shift**
  * Jeff Hawkins assumes that alternative way through thalamus is the mechanism to attend to details that normally we wouldn't notice - **focus our perceptions**
    * it bypasses grouping of sequences and sends raw data to the next higher region
  * alternate pathway can be turned on in one of two ways
    * one is by signal from the higher region - command to attend to details
    * second is a large, unexpected signal from below
    * if the input to alternative way is strong enough, lower region sends wake-up signal to higher region, which turns on the pathway
    * if you see to the face with strange mark on the nose, your attention will be drawn to the mark
    * now you see the mark, not the face - it can occupy all your attention
  * often, however, errors aren't string enough to open the alternate pathway - e.g. we sometimes don't notice that word was misspelled

## Closing thoughts ##

  * new scientific framework requires to look for simplest concepts capable of uniting explaining large quantities of disparate facts
    * model was simplified, maybe with ignoring important facts and mistakes as a result
    * brain is very complex
    * still JH believes framework is generally correct
  * people do not believe that human is just a **hierarchical memory system**
    * cortex is not made of super-fast components and cortex rules are simple enough
    * however, cortex has hierarchical structure, containing billions of neurons and trillions of synapses
    * if we do not believe that cortex can create consciousness, it is because of inadequate intuitive sense of capacity and power of cortex

# Chapter 7. Consciousness and Creativity #

  * below are most interesting questions where cortex framework can provide some answers and insights

## Are animals intelligent? ##

  * is a cat intelligent, when intelligence begin in evolutionary time
  * **the world has structure and is therefore predictable**
    * the world is not random, nor is it homogeneous
    * memory, prediction and behaviour are meaningless, if world has no structure
    * **any behaviour, from human to worm, is means to exploit world structure for the benefit of reproduction**
    * one-cell animal is intelligent because is uses DNA for learning, memory and prediction
  * memory and prediction are used by all living things, including plants, with continuum of methods and sophistication in doing that
    * plants do not think, their behaviour is automatic
    * plants have chemical communication system which is much slower than neurons
    * in animals, connections between neurons are modifiable - neuron can send signal or not send signal depending on what happened recently - it means learning within life of the same organism, **neural system has plasticity**
  * all mammals have old brain and neocortex on top of it
    * in terms of evolution, neocortex is most recent neural tissue
    * with hierarchical structure, invariant representations and prediction by analogy, cortex allows mammals to exploit much more of structure of the world, comparing to animal without neocortex
    * fish will never learn to avoid nets or build tools to cut nets
    * all mammals are intelligent, to a different degree

## What's different about human intelligence? ##

  * **human neocortex is larger than one of monkey or dog**
    * larger neocortex is able to learn more complex model of the world, more structure on structure
    * cat has no concept of the world outside house
  * **humans have language**
    * language is just a set of patterns, syntax and semantics are like hierarchies of objects in the world
    * through language one human can invoke memories and create and create new mental objects in another human
    * development of language requires large neocortex (see Broka's area, Wernike's area), more developed motor cortex and musculature
    * language is means by which we pass what we know about the world from generation to generation (compare to Internet)
  * **intelligence has three epochs of evolution**
    * first - when DNA was used to store memory
    * second - using modifiable nervous system, that could quickly form memories
    * third, unique to humans (it is a question as other animals do have language as well) - invention of language and expansion of neocortex
    * **humans are the only creatures who are able to transfer knowledge broadly within our populace**

## What is creativity? ##

  * many people see creativity as something a machine couldn't do
  * creativity is not something that occurs in a particular region of cortex
    * nor is it like emotions or balance that are in old brain
    * **creativity is inherent property of every region of cortex**
    * it is necessary component of prediction
  * **creativity is making predictions by analogy**
    * creativity occurs along continuum
    * in simple case it can be hearing the same song in a new key - lowest levels of cortex
    * in complex case it can be composing symphony in a brand-new way - highest levels of cortex
  * **everyday perception is similar to genius act**
    * we create invariant memories, use them to make predictions
    * we we make predictions of future events that are always somewhat different from what we have seen before
    * our invariant memories are sequences of events
    * we make predictions by combining invariant memory recall of what should happen next with existing details
    * **prediction is the application of invariant memory sequences to new situations**
    * **all cortical predictions are predictions by analogy**
  * prediction by analogy, creativity, is so pervasive we normally don't notice it
  * **we believe that we do creativity if we apply prediction by analogy in high level of abstraction - when it makes uncommon predictions, using uncommon analogies**
  * **highly creative works of art are appreciated because they violate our predictions**
    * too much familiarity is kitsch
    * too much uniqueness is jarring
    * great music uses simple almost well-known patterns on low-level, while with a lot of uniqueness on high levels
  * **you might see analogy between two normally unrelated events**
    * if you are poet - you might have new metaphor
    * if you are scientist of engineer - you might have new solution for long-standing problem
  * **creativity is mixing and matching patterns of everything you have experienced in your lifetime** (not shared with many people!)

## Are some people more creative than others? ##

  * if all brains are inherently creative, why are there differences in our creativity?
  * **nurture** - everyone has different life experiences
    * develops different models and memories of the world, leading to different analogies and predictions
    * people are more creative in areas based on environment they grew up in
    * **our predictions and talents are built upon our experiences**
    * expertise is large practice, simple patterns are learned on lower levels of cortex, higher levels learn complex patterns
    * (I think that level of creativity is limited as we have fixed number of levels in cortical hierarchy, and limited ability to keep relations between complex and simple patterns, added to forgetting and averaging of memories)
  * **nature** - brains exhibit physical variation
    * size of regions is genetically determined, e.g. V1 can differ in size 3 times from one person to another
    * lateral connectivity between hemispheres can be different, e.g. women have much stronger lateral connectivity
    * Albert Einstein had mind with more support cells - glia - per neuron, than average; his parietal lobe (associative) was 15% wider than most other brains

## Can you train yourself to be more creative? ##

  * you can foster finding useful analogies when working on problems
    * assume up front that **there is an answer**
    * persist in thinking about the problem for an **extended period of time**
    * give your brain **time and space** to discover solution
    * find **different ways** to look at the problem to increase likelihood of seeing analogy
    * take **parts of the problem and re-arrange** them
    * if you get stuck on a problem, **go away for a little while**, then start again, re-phrasing the problem anew
    * ponder the problem often, but **do other things** in the same time
  * when create interface for people, solution can be not intuitive, and need extra learning, but **people will use it because it works**
    * our **brains hate unpredictability**, and we do not like systems that make stupid mistakes
    * people claim that computers should adapt to users - it is not always true
    * our brains prefer systems that are consistent and predictable, and we like learning new skills
    * (from my experience, we like learning new way if we see that old way doesn't work)

## Can creativity lead me astray? Can I fool myself? ##

  * **false analogy is always a danger**
  * having reduced model and its analogy, you can convince yourself that model is correct
    * brain always builds models and makes creative predictions, but they can easily be specious as valid
    * if correct correlations cannot be found, **mind is happy to accept false analogy**

## What is consciousness? ##

  * many neuroscientists regard consciousness as subject of philosophy bordering on pseudo-science
  * **consciousness is simply what it feels like to have a cortex**
  * most people think that consciousness is  magical sauce added on top of physical brain
  * we can break consciousness into two major categories
    * one is similar to **self-awareness - everyday notion of being conscious**
    * second is **qualia - feelings associated with sensation are somehow independent of sensory input**
  * first - conscious is like self-aware
    * more precise to say - this meaning of consciousness is **synonymous with forming declarative memories**
    * declarative memories can be recalled and told to someone else, expressed verbally
    * where you was last weekend is declarative memory
    * **how to balance bicycle has mostly to do with neural activity in the old brain, so it is not declarative memory**
    * consider if erase your yesterday's memory - before erasing you can say you were conscious yesterday, after erasing you do not remember about it at all and regard yourself unconscious as if being asleep
    * **consciousness is not absolute but depends on having a memory in the time of question**
  * second - consciousness as qualia
    * qualia is often re-phrased as Zen-like questions - "Does red look the same to me as it does for you?"
    * re-phrasing to equivalent but more scientific - **why do different senses seem qualitatively different** (obviously different question!)
    * why sight seems different from hearing and touch - if cortex is dealing only with patterns, all senses should look like the same
    * people with dis-function can feel some sounds having colour - **qualitative aspect of a sense is not immutable**
    * hearing, touch and vision are handled differently below the cortex
    * **hearing has sub-cortical structures that process auditory patterns before they reach cortex**
    * somatosensory patterns also travel through subcortical areas, unique to somatic senses
  * two possibilities of having qualia
    * first - qualia, like emotions, are **not mediated purely by neocortex** and bound up with subcortical areas, having unique wiring and tied to emotion centers
    * second - **differences in the patterns** themselves dictates how you experience qualitative aspects of information - optic nerve has 1M fibers and carries quite a lot of spatial information, auditory nerve has 30K fibers and carries more temporal information
  * related to consciousness are **notions of mind and soul**
    * you can say "if I were not in this body"
    * feeling of mind independent if physicalness is natural consequence of how neocortex works
    * cortex creates model of world in its hierarchical memory
    * **thoughts are what occur when this model runs on its own - memory recall leads to predictions, which act like sensory inputs, which lead to new memory recall and so on**
    * to the cortex, our body is just part of external world (I do think it is not correct as cortex is tightly controlled by feelings, bound to body image)
    * brain is quiet is dark box, which knows about world only via patterns - no special distinction where body ends and other world begins
    * cortex has no ability to model brain itself because there are **no senses in the brain itself** (we experience no sensation when surgeon cuts our brain)
    * thus we can see why our thoughts appear independent of our bodies, why it feels like we have independent mind or soul
    * **cortex builds a model of body, but cannot build a model of brain**
    * **mind is independent from body but not from brain** (strictly speaking, we do not think that nervous system in our body is part of our mind - but I believe it is)
    * one can lose arm but feel he has it
    * one can have cortical trauma ad lose model of arm, but have it
    * **if our brains dies, so does and our mind**

## What is imagination? ##

  * conceptually imagining is simple
    * patterns flow into each cortical area either from senses or from lower areas
    * each cortical area creates predictions which are sent back down the hierarchy
    * to imagine something you **let your predictions turn around and become inputs**
    * **imagining is another word for planning**
    * prediction permits us to **know consequences of our actions before we do them**
  * imagining requires **neural mechanism for turning prediction into input**
    * from Chapter 6 - cells in **layer 6 are where precise prediction occurs**
    * layer 6 projects down to lower levels (layer 2), but also back to layer 4 (inputs)
    * Stephen Grossberg (cortical modeller) calls it "folded feedback"
    * **if you close eyes and imagine hippopotamus, your visual area will become active - you see what you imagine**

## What is reality? ##

  * people worry - doesn't  the world exist outside my head
    * world is real, but your understanding of the world and your responses are biased on predictions coming from your internal model
    * at any moment of time you directly sense only tiny part of the world
    * most of what you perceive is not coming through your senses, but generated internally
    * question "what is reality" is a matter of how accurately our cortical model reflects true nature of the world
  * many aspects of the world are so consistent that nearly every human has the same internal model of them
    * simple physical properties of the world are learned consistently by all people
    * much of model is based on custom, culture, and parents - these parts of model can be totally different for different people
    * studies show that Asians and Westerners perceive space and objects differently - Asians attend more to space between objects, whereas Westerners mostly attend to objects
    * model of the world can't be correct in some absolute universal way, even it can seem correct to an individual
  * your culture and family teach you stereotypes
    * stereotype is synonym for invariant memory or invariant representation
    * prediction by analogy is pretty much the same as judgement by stereotype
    * thinking by stereotypes is unavoidable because it is how the cortex works
    * the way to eliminate harm from stereotypes is to teach children to recognise false stereotypes, be empathetic, and be skeptical

**Finally:**

  * mind is just a label of what brain does
  * mind is not separate thing that manipulates or coexists with cells in the brain
  * neurons are just cells

# Chapter 8. The Future of Intelligence #

  * hard to predict ultimate uses of new technology - often unexpected and more far-reaching than our imaginations can first grasp
  * predicting future of technology more than few years is impossible
  * but there are certain broad and useful conclusions

## Can we build intelligent machines? ##

  * yes, but intelligent machines will not act as humans or even interact in human-like way
    * human mind is created not only by the neocortex, but also by **emotional system of old brain and by complexity of human body** - to be like human, you need all this
    * to pass Turing test, you need to have most of human experiences and emotions
  * given the cost and effort to build humanoid robots, it is difficult to see how they could be practical
  * recipe for building intelligent machines:
    * **start with set of** senses (can be different from human and totally novel) to extract patterns from the world
    * **attach to senses hierarchical memory system**, that works on the same principles as cortex
    * **train memory system** as we teach children - intelligent machine will build model of its world as seen through its senses - no need to program rules, fact or high-level concepts as in AI - it should learn from observation of world or input from instructor
    * physically, our intelligent machine **can be resided remotely from senses** and can have no specific form
    * what makes it intelligent is that it can understand and interact with its world via hierarchical memory model and can think about its world in a way analogous to how you and I think about this world
  * to build intelligent machine we need to construct large memory systems, that hierarchically organised and that work like cortex
  * **challenges are capacity and connectivity**
  * human **capacity** is about 80 hard drives, if one disk is 100Gb
    * it is not what you can put in your pocket
    * but we don't need to re-create entire human cortex
    * intelligent memory has advantage over standard silicon memory - it should be **tolerant to errors**
    * economics of silicon memory is based on **percentage of chips with errors**
    * larger chip has more chance to have errors, to keep economics, chips are small
    * brain loses thousands of neurons each day, yet mental capacity decays at slow pace
    * **inherent tolerance to errors of brain-like memory will allow designers to build chips that are significantly larger and denser** than today's computer memory chips
  * second problem is connectivity
    * individual cell may connect to 5-10K other cells
    * in chip wires cannot cross on the same level - so **number of connections is limited**
    * solution is to **make single connection shared among many different connections** as transmission speed is much greater than in human mind

## Should we build intelligent machines? ##

  * we can imagine terrible ways a new technology may take over our bodies, outmode our usefulness, or cancel out the very value of human life
  * intelligent machines are going to be one of the **least dangerous, most beneficial technologies** we have ever developed
  * two publicly available dangerous predictions are **machines-run-amok** (go crazy) and **upload-your-brain-into-a-computer**
  * **building intelligent machines is not the same as building self-replicating machines**
    * self-replication does not require intelligence, and intelligence does not require self-replication
    * to make copy of human, it will require to copy nervous system and body as well - looks impossible
  * another concern - might intelligent machines somehow **threaten large portions of the population, as nuclear bombs** do?
    * no, being intelligent does not mean having special ability to destroy property or manipulate people
    * be careful not to rely too much on intelligent machines
  * some people assume that being intelligent is basically the same as having human mentality
    * humans have bad practice - intelligent people in history have tried take over the world
    * it is true, but supported with emotional drives of the old brain - fear, paranoia, desire
    * but intelligent machines do not have these faculties (not for aHuman project though!), **they will not have personal ambition**
    * maybe someday we will have to **place certain restrictions** on what people can do with intelligent machines (I'm afraid it will be impractical), but this day is s long way off (keep in mind, building intelligence is top scientific target today!), and when it comes, the ethical issues are likely to be relatively easy (what it means?!) compared with such present-day moral questions as those surrounding genetics and nuclear technology

## Why build intelligent machines? ##

  * the best we can do is to **understand broad trends**
  * another thing we can do - is to envision **very near-term uses** for brain-like memory
  * consider **speech recognition** software - computer has no understanding of what is being said
    * **recognition errors too high** - child would know this is wrong, but not the computer
    * many applications, like organizer, require machine to listen to spoken language
    * words **overlap and interfere, pieces of sound drop out because of noise**
    * humans perform language-related tasks easily, because our cortex understands not only words, but sentences and context within which they are spoken
    * **we anticipate ideas, phrases and individual words** - our cortical model does this automatically
    * **cortex-like memory systems enables robust speech understanding** - hierarchical memory will track accents, words, phrases and ideas and use them to interpret what is being said
    * to fully understand human language, machine will have experience and learn what humans do
  * **vision** if another set of applications
    * today there is no machine that can look at a natural scene - the world in front of your eyes, or picture using a camera - and describe what is sees
    * it's currently impossible for a computer to identify varieties of objects or analyse scene more generally
    * we hire people to keep an eye on the screens of security cameras round-the-clock, looking for something suspicious, but it is difficult for human to stay alert for a long time
  * look at **transportation**
    * cars are sophisticated - they have GPS, light sensors, accelerometers for airbugs, proximity sensors
    * there are non-commercial cars that drive autonomously on special highways
    * to be a good driver, you should understand traffic, other drivers, the way car work, signal lights, and so on
    * let's say we  want to build truly smart car; the first thing is to select sensors
    * we don't have to rely on sensors human use (or can use!)
    * sensors would be attached to sufficiently large hierarchical memory system
    * then system have to be learned
    * car's engineers could design memory system so that is **actually drives the car or just monitors** what happens when you drive - give advice or take over in critical situation (this is the major question - who is the best in critical situation?)
    * when fully trained, this memory **system can be replicated**; after that it could be upgraded to more advanced version
  * let's think of aspects of technology that will **scale well**
    * which attributes will grow cheaper and cheaper, faster and faster, or smaller and smaller
    * exponential growth examples - silicon memory, hard disk, DNA sequencing techniques, fiber optics
    * in contrast, batteries, motors, traditional robotics - scale poorly
    * JH sees 4 attributes that will scale dramatically and exceed our own abilities - **speed, capacity, replicability and sensory systems**

**Speed**:

  * neurons work on the order of milliseconds, silicon - nanoseconds (1M order difference)
  * intelligent machines can think 1M times faster than human
  * biological brains evolved with two **constraints - speed of cells and speed of which world changes**; biological brain has no reason to work much faster
  * if intelligent machine will interact with human, it would slow down to human speed
  * **two intelligent machines can hold a conversation million times faster**

**Capacity**:

  * size of human brain is limited by maternal pelvis diameter, high metabolic cost of running a brain (2% of body, but uses 20% of oxygen), and slow speed of neurons
  * we can make intelligent memory system of increased size, in several ways
    * **adding depth to hierarchy** will lead to deeper understanding - ability to see higher-order patterns
    * **enlarging capacity within regions** will allow to remember more details, or perceive with more acuity
    * **adding new senses and sensory hierarchies** permits to construct better models of the world
    * human brains became large very recently in evolutionary time, and there is nothing to suggest that we are at some stable maximum size
    * Einstein was undoubtedly extremely smart, and his intelligence was largely a product of physical differences between his brain and typical human brain, caused by genes
    * savants exhibit remarkable abilities such as near-photographic memories or capacity to perform difficult mathematical calculations at lightning speed
  * if atypical brain can have amazing memory abilities, then, in theory, we could do it in artificial brain

**Replicability**

  * each new organic brain must be grown and trained de novo, process that takes decades
  * for intelligent machines due to ability to copy memory **no need to undergo long learning curves**
  * we could **choose to allow the copies to continue learning or not**
  * it should be possible to **share components of learning** the way we share components of software
  * intelligent machine of particular design could be **reprogrammed with a new set of connections to lead to different behaviour**
  * people could **swap and build on work of others**
  * business of building intelligent machines can evolve to have **communities of people training intelligent machines to have specialised knowledge and abilities**, and selling and swapping the resultant memory configurations

**Sensory Systems**

  * human senses are deeply integrated in our genes, bodies, and in subcortical wiring of our brains; we cannot change them
  * if we use night-vision or radar devices, these instruments are only tricky translators, not new modes of perception
  * intelligent machines can directly perceive world through all known and new types of senses
  * we have make exotic sensory system, e.g. sensory net that spans the globe
    * this system can perceive the weather and predict it naturally
    * putting large amounts of weather data into form that human can read and understand is difficult
    * **weather brain would sense and think about weather directly**
  * other possible examples are predicting animal migrations, changes in demographics, spread of decease, electricity consumption in city, traffic on road, movement of people in airport
  * intelligence machines can anticipate political unrest, famines, decease outbreaks, play role in reducing conflicts and human suffering
    * JH thinks intelligence machines do not need emotions to foresee patterns involving human behaviour
    * we are not born with culture and values, we learn it
    * intelligent machines can comprehend human motivations and emotions, even if machine doesn't have emotions itself
  * intelligent machines could perceive patterns in cells or large molecules
    * it can accelerate development of medicines and cures for many deceases
    * our inability to tackle the issue maybe related, primarily, to a mismatch between human senses and physical phenomena we want to understand
  * intelligent machines might live in think in virtual worlds used in mathematics and physics
    * e.g. string theorists think about universe as having ten or more dimensions
    * human cannot easily understand more than three-dimensional world
  * **intelligent machines might think and learn million times faster than we can, remember vast quantities of detailed information, or see incredibly abstract patterns**
  * now we see how Turing Test limited our vision of what is possible - intelligent machines are far more valuable than merely replicating human behaviour

**Finally**

  * change takes longer than expected in short term, but occurs faster than you expect in long term
  * neuroscience community **expectations for working theory of cortex**:
    * 5% - never or already have
    * 5% - 5-10 years
    * 40% - 10-50 years
    * 40% - more than 50 years
  * judging by progress within last 30 years, one can assume we are nowhere near an answer, but near the turning point
    * with correct theoretical framework, we can make rapid progress in understanding cortex
    * useful prototypes and cortex simulations can be created within few years
    * within 10 years intelligent machines will be one of the hottest areas of technology and science

# Epilogue #

  * understanding something does not diminish its wonder and mystery
  * with understanding, we become more comfortable with our role in universe and universe becomes more colourful and mysterious
  * the quest to understand brain and build intelligent machines is a worthy endeavour and a logical next step for humanity
  * scientific frameworks underlying AI and neural networks are not right ones to use in building intelligent machines
  * results are so promising, that JH started new business, Numenta, with mission of developing far-reaching technologies (in computer vision area)

# Appendix: Testable Predictions #

  * memory-prediction framework is grounded in biology and leads to specific and novel predictions that can be tested

**Prediction 1**

  * we should find cells in all areas of cortex, including primary sensory cortex, that show **enhanced activity in anticipation of sensory event**, as opposed to in reaction to a sensory event

**Prediction 2**

  * the more spatially specific a prediction can be, the closer to primary sensory cortex we should find cells that become active in anticipation of an event
  * if monkey learned to expect to see face, but not exactly what and how face would appear, we should find anticipatory cells in face recognition areas, but not in lower visual areas
  * however, if monkey fixates on a target and has learned to expect particular pattern in precise location in its visual field, then we should find anticipatory cells in V1 or close to V1

**Prediction 3**

  * cells that exhibit enhanced activity in anticipation of sensory input should be preferentially located in cortical layers 2, 3, 6 and prediction should stop moving down the hierarchy in layers 2, 3
  * prediction travels via layers 2, 3 which project to layer 6, which projects broadly across layer 1 of lower region, which activates layers 2,3 cells and so on
  * active layers 2, 3 cells represent set of possible active columns
  * active layer 6 cells represent smaller number of columns - specific prediction from region

**Prediction 4**

  * one class of cells in layers 2, 3 should preferentially receive input from layer 6 in higher region
  * learned sequences of patterns occurring together develop temporally constant invariant representation, called "name" in this book
  * this name is a set of layers 2,3 cells across region of cortex if different columns
  * these cells are made active via feedback from layer 6 cells in higher regions
  * apical dendrites of these name cells must form synapses preferentially with axons in layer 1 that originated in layer 6 of higher regions - they should avoid forming synapses with axons in layer 1 that originated in thalamus
  * we should find another class of layers 2,3 cells whose apical dendrites form synapses preferentially with axons originating in non-specific regions of thalamus - these cells predict next items in a sequence

**Prediction 5**

  * a set of "name" cells should remain active during learned sequence
  * no idea what means constant activity - e.g. it may be single spike in unison

**Prediction 6**

  * another class of layers 2,3 cells, different from name cells, should be active in response to an unanticipated input, but should be inactive in response to an anticipated input
  * unanticipated events must be passed up the hierarchy, but when event is anticipated, we don't want to pass it up the hierarchy because it was predicted locally
  * axons of these cells should project to higher regions
  * such cells could be inhibited via interneuron activated by name cell

**Prediction 7**

  * unanticipated events should propagate up the hierarchy
  * the more novel event the higher unanticipated input should flow
  * completely novel event should reach hippocampus

**Prediction 8**

  * sudden understanding should result in a precise  cascading of predictive activity down the hierarchy
  * if look at Necker cube (2 equally possible images), every time perception of image changes we should see propagation of prediction down the hierarchy
  * at lowest levels, say V1, column representing line segment should stay active in either perception (if eyes not moved)
  * similar propagation of prediction should occur with each saccade over learned visual object

**Prediction 9**

  * pyramidal neurons should be able to detect precise coincidences of synaptic input on thin dendrites
  * for many years it was thought that neurons are simple integrators, summing inputs from all their synapses
  * there are also many models assume  that neuron behaves as if each dendritic section operates independently
  * HTM model requires neuron be able to detect coincidence of only few active synapses in narrow window of time on thin dendrite
  * thus neuron with thousands of synapses can learn to fire on many different precise and separate input patterns
  * synapses on thick dendrites

**Prediction 10**

  * representations move down the hierarchy with training
  * through repeated training, cortex relearns sequences in lower regions
  * we should find cells that respond to complex stimulus lower in cortex after extensive training and higher in cortex after minimal training
  * places where recall occurs and where errors are detected should move
  * thus sensations of highly learned patterns should propagate less distance up the hierarchy

**Prediction 11**

  * invariant representations should be found in all cortical areas
  * it is expected that there are cells in association areas that receive both visual and auditory input of the same object that respond to either sight or saying this object
  * we should find invariant representations in all sensory modalities and even motor cortex
  * in motor cortex cells should represent complex motor sequences
  * the higher up the motor hierarchy the more complex and invariant the representation should be

**Finally**

  * if all predictions are true, it wouldn't be a proof that memory-prediction hypothesis is correct, but it would be strong evidence in support of the theory
  * and vice versa...