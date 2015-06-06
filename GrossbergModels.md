@@[Home](Home.md) -> [NeoCortexResearch](NeoCortexResearch.md) -> [PrefrontalCortexReview](PrefrontalCortexReview.md)

---

Below are most interesting thoughts, from my point of view,
of article by Stephen Grossberg, founder of computational neurobiology,
named "Cortical and subcortical predictive dynamics and learning during
perception, cognition, emotion and action", 2008.



# 1. INTRODUCTION #

  * realtime learning - from 2 **complementary streams** - ventral "what" (LGN/PV -> V1 -> V2 -> V4 -> IT -> LPFC) and dorsal "where" (V1 -> V2 -> MT -> PPC -> LPFC)
    * **what**: excitatory matching and match-based learning to create predictive representations of objects and events in the world
    * **where**: inhibitory matching and mismatch-based learning to continually update spatial maps and sensory-motor gains as our bodily parameters change through time

![http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/visual-streams.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/visual-streams.jpg)

(picture from The “Conscious” Dorsal Stream: Embodied Simulation and its Role in Space and Action Conscious Awareness by Vittorio Gallese, 2007)

  * "what" stream learns **spatially invariant object categories**
  * "where" stream learns **spatial maps** and **movement gains**
  * "what"–"where" interstream interactions enable spatially invariant object representations to **control actions towards desired goals** in space
  * **perceptual** and **cognitive** learning control **spatial/motor** learning

# 2. LEARNING OF INVARIANT RECOGNITION CATEGORIES #

  * categories that tend to be increasingly independent of object size and position at higher cortical levels (ITa is invariant)
  * fast learning without catastrophic forgetting - **ART model**
    * integrate properties of consciousness, learning, expectation, attention, resonance and synchrony (CLEARS)
    * **excitatory resonanse** when match between learned top-down pattern and bottom-up input
    * focused attention on critical feature pattern
    * resonanse forces fast incorporation of such patterns into category

![http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-art.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-art.jpg)

  * solves **stability-plasticity dilemma** - learn quickly without experiencing catastrophic forgetting
    * all **conscious states are resonant states**
    * animals pay **attention to salient objects**
    * learning one-to-many (many views of one category) and many-to-one (know many things about object) maps

# 3. EXPECTATIONS AND BIASED COMPETITION #

  * it was mathematically proved that the simplest network which solves the stability–plasticity dilemma is a **top-down, modulatory on-centre, off-surround network**
    * excitatory priming of features in the on-centre
    * inhibition in the off-surround
  * it was termed as **biased competition**

# 4. IMAGINING AND PLANNING AHEAD #

  * excitatory/inhibitory balance in the modulatory on-centre of a top-down expectation can be modified by **volitional control from the basal ganglia**
  * if these volitional signals become tonically hyperactive, then top-down expectations can fire without overt intention, leading to properties such as schizophrenic hallucinations

# 5. EXPECTED VERSUS UNEXPECTED EVENTS #

  * match-based learning stabilizes learned memories in both the bottom-up and top-down adaptive filters
  * top-down expectations can also predictively prime events whose future occurrence is sought

# 6. SPIKES, SYNCHRONY AND ATTENTIVE LEARNING #

  * synchronous matching ART (**SMART**) model predicts CLEARS from muti-level brain organization and provides:
    * unified functional explanation of single-cell properties, such as spiking dynamics, spike-timing-dependent plasticity and acetylcholine modulation
    * detailed laminar thalamic and cortical circuit designs and their interactions
    * aggregate cell recordings, such as current source densities and local field potentials
    * single cell and large-scale inter-areal oscillations in the gamma and beta frequency domains

![http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-smart.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-smart.jpg)

  * SMART predicts that **matches cause gamma oscillations** that support attention, resonance, learning and consciousness, whereas **mismatches inhibit learning by causing slower beta oscillations** during reset and hypothesis testing operations that are initiated in the deeper cortical layers
    * beta oscillations in deeper cortical layers
    * beta oscillations during partial attention shifts
    * beta oscillations during hippocampal place cell learning in novel environments
    * **hippocampal place cells can develop within seconds to minutes, and can remain stable for months**
    * beta power was very low as a mouse traversed a lap for the first time, grew to full strength on the second and third laps, became low again after 2 min of exploration, and remained low on subsequent days
  * beta oscillation power also correlated with the rate at which place cells became **spatially selective**
    * top-down adaptive weights are large before learning occurs, so that they can match whatever input pattern first initiates the learning of a new category
    * weights are pruned on subsequent learning trials to match the emerging critical feature pattern during mismatchbased reset events
    * low beta power on the first lap of exploration can be explained by the initial top-down match
    * beta power on subsequent laps can be explained by mismatch events that correlate with the rate at which place cells become spatially selective

# 7. COGNITIVE–EMOTIONAL INTERACTIONS #

  * **invariant recognition categories** can be activated when objects are experienced, but without emotional value of these objects
    * can be **associated** through reinforcement learning with one or more **drive representations** (internal drive states and emotions)
    * activation of drive representation by invariant object category can **trigger emotional reactions and motivational decisions** that can motivationally modulate object representations
    * recognized objects can hereby **trigger choice and release of actions** that realize goals in context-sensitive way
  * **CogEM** model represents three types of interacting representations (sensory, drive and motor), as they control three types of learning (conditioned reinforcer, incentive motivational and motor) during reinforcement learning
    * sensory representations S temporarily store internal representations of sensory events in working memory; drive representations D are the sites where reinforcing and homeostatic, or drive, cues converge to activate emotional responses; motor representations M control read-out of actions
    * **conditioned reinforcer learning** enables sensory events to activate emotional reactions at drive representations
    * **incentive motivational learning** enables emotions to generate a motivational set that biases the system to process information consistent with that emotion
    * **motor learning** allows sensory and cognitive representations to generate actions

![http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-cogem.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-cogem.jpg)

  * visually perceived objects are called **conditioned stimuli** (CSi), invariant object categories that they activate are called **sensory representations** (SCSi), which, in turn, activate **drive representations** (D)
  * **amygdala** is drive representation, sends projections to PFC
    * reinforcement learning can covert CS1, that activates SCS1-1 into **conditioned reinforcer** by strengthening the associative links from SCS1-1 to D (e.g. learning in IT -> AM pathways)
    * SCS1-1 can also send excitatory projections to SCS1-2 (regions of prefrontal cortex, PFC)
    * reinforcement learning strengthen AM-to-PFC pathways, which provide **incentive motivation** to PFC representations
  * SCS1-2 (PFC) send top-down feedback to SCS1-1 (sensory cortex)
    * enhances sensory representations that are **motivationally salient**
    * IT chooses those with best combination of sensory and motivational support
    * IT–AM–OMPFC feedback loop triggers **cognitive–emotional resonance** that supports **basic consciousness of goals and feelings** and releases learned action commands from PFC (SCS2-1 -> M) to achieve valued goals

  * **TELOS** proposes how basal ganglia trigger reinforcement learning in response to unexpected rewards, and gates selection and release of actions that are learned through reinforcement learning
  * in vivo, the basal ganglia and amygdala work together to provide:
    * motivational support
    * focus attention
    * and release contextually appropriate actions to achieve valued goals

![http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-telos.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-telos.jpg)

  * **MOTIVATOR** unifies CogEM and TELOS models and clarifies how interaction of basal ganglia and amygdala happens
  * simulates properties such as:
    * food-specific satiety
    * Pavlovian conditioning
    * reinforcer devaluation
    * simultaneous visual discrimination
    * saccadic reaction times
    * CS-dependent changes in systolic blood pressure
    * discharge dynamics of known cell types

![http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-motivator.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-motivator.jpg)

  * brain areas can be divided into four regions that process information about conditioned stimuli (CSs) and unconditioned stimuli (USs):
    * **object categories** represent visual or gustatory inputs in anterior inferotemporal (ITA) and rhinal (RHIN) cortices
    * **value categories** represent value of anticipated outcomes on basis of hunger and satiety inputs in amygdala (AMYG) and lateral hypothalamus (LH)
    * **object–va
lue** categories resolve value of competing perceptual stimuli in medial (MORB) and lateral (ORB) orbitofrontal cortex
    * **reward expectation filter** involves basal ganglia circuitry that responds to unexpected rewards

# 8. ADAPTIVELY TIMED PREDICTIONS #

  * **reinforcement learning must be adaptively timed**, since rewards are often delayed in time relative to actions aimed at acquiring them
    * if animal could not inhibit its exploratory behaviour, then it could starve to death by restlessly moving from place to place
    * if animal inhibited its exploratory behaviour for too long while waiting for expected reward, then it could starve to death if food was not forthcoming
  * being able to predict **when** desired consequences occur is often as important as predicting **that** they will occur
  * to **control predictive actions**:
    * what - recognition learning
    * why - reinforcement learning
    * when - adaptively timed learning
    * where - spatial learning
    * how - sensory-motor learning
  * **START** (Spectrally Timed ART) predicts how brain distinguishes **expected nonoccurrences** of rewards, which should not interfere with acquiring the delayed goal, from **unexpected non-occurrences** of rewards, which can trigger:
    * reset of working memory
    * attention shifts
    * emotional rebounds
    * exploratory behaviours

![http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-start.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-start.jpg)

# 9. SPECTRAL TIMING IN CEREBELLUM AND HIPPOCAMPUS #

  * adaptive timing occurs during several types of reinforcement learning
    * in classical conditioning, at range of positive interstimulus intervals (between CS and US) learned responses are timed to match statistics of learning environment
  * although amygdala is primary site for emotion and stimulus–reward association, **hippocampus** and **cerebellum** have also been implicated in **adaptively timed processing of cognitive–emotional interaction**
    * CogEM predicts how salient conditioned cues can rapidly focus attention on S via cognitive–emotional resonance with associated D
    * CR predicted to adaptively time actions in task-appropriate way by using spectrum of learning sites, each **sensitive to different range of delays between CS and US**
    * adaptively timed long-term depression (LTD) learning at parallel fibre/Purkinje cell synapses depresses tonically active output from cerebellar Purkinje cells to cerebellar nuclei
    * there is **premature responding** when cerebellar cortex is lesioned
    * see also: role of **calcium signalling** and mGluR in cerebellar adaptive timing
  * two potentially **conflicting behavioural properties**, reconciled by CR^
    * fast allocation of attention to motivationally salient events via cortico-amydala feedback
    * adaptively timed responses to these events via cortico-cerebellar adaptively timed responding
  * **motivated attention** needs to persist long enough to support read-out of adaptively timed motor commands, and to prevent irrelevant events from prematurely resetting these commands
    * as per START, hippocampal dentate-CA3 circuits can do this
    * without it, novel event could easily reset motor commands prematurely
    * HC system and non-specific TH are proposed to be part of mismatch-activated orienting system A (see ART)
  * thalamocortical and corticocortical mismatches that activate HC or non-specific TH are not sensitive to whether novel event that caused mismatch is task **relevant**
    * mismatches may be modulated by task relevance in an adaptively timed way
    * adaptively timed activity (T - see START) can inhibit A during interval wherein valued and predictable goal is being acted upon
  * START model enables three key properties to simultaneously coexist:
    * **fast motivated attention**: rapid focusing of attention on motivationally salient cues occurs from regions such as AM to PFC (D -> S2); could prematurely release motor behaviours (S2 -> M)
    * **adaptively timed responding**: readout of responses via CR circuits enables learned responses to be released at task-appropriate times, despite fact that CS cortical representations can be quickly activated by fast motivated attention
    * **adaptively timed duration of motivated attention and inhibition of orienting responses**: premature reset of active CS representations by irrelevant cues during task-specific delays is prevented by adaptively timed inhibition of mismatch-sensitive cells in orienting system of HC (T -> D -> A) as part of competition between consummatory and orienting behaviours; incentive motivational feedback (D -> S2 -> S1) simultaneously maintains CS activation in short-term memory, so that CS can continue to read out adaptively timed responses until they are complete; **contingent negative variation** event-related potential is predicted to be neural marker of adaptively timed motivational feedback

# 10. LAMINAR CORTICAL DYNAMICS OF WORKING MEMORY #

  * above mechanisms do not explain how brain responds selectively to sequences of events
  * predictive behaviour depends upon **capacity to think about, plan, execute and evaluate event sequences**
  * multiple events in specific temporal order can be **stored temporarily in working memory**
    * event sequences are temporarily stored, grouped, or chunked, through learning into unitized plans, or list chunks, and can later be **performed at variable rates under volitional control**
    * working memory means storing temporal order of events, not just events
  * **LIST PARSE** model proposes how working memories are designed to enable list chunks to be stably learned and remembered
    * inputs to working memory are **unitized item categories** of individual events or objects that have enough adaptively timed, incentive motivational support to be persistently stored and transferred into working memory
    * item representations are stored in working memory as **temporally evolving spatial pattern of activity** across working memory cells
    * relative activity of different cell populations codes temporal order in which items will be rehearsed, with largest activities rehearsed earliest (competitive queuing)

![http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-listparse.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-listparse.jpg)

  * neurobiological view for visual and auditory processing:
    * learned in IT and OMPFC, latter with motivations
    * load sequences into working memory - in OMPFC/LPFC
    * working memory patterns categorized by list chunks - sequential plans
    * sequential plans are used to predict subsequent expected events
  * LIST PARSE quantitatively simulates human cognitive data about:
    * immediate serial recall
    * immediate, delayed and continuous-distracter freerecall
    * monkey neurophysiological data from PFC obtained during sequential sensory-motor imitation and planned performance

# 11. BALANCING REACTIVE VERSUS PLANNED BEHAVIOURS #

  * learned **new recognition codes are subsumed** by larger complementary brain system that balances reactive versus planned behaviours
    * rapid reactive movements
    * planned movements longer to select and release
    * how prevent premature reactive movements?
  * **movement gates** can inhibit premature reactive movements until planned is ready to compete
    * function of BGA - inhibit reactive in progress of planned execution
    * answer why reactive movements are not inhibited when no plans - see TELOS model
    * frontal–parietal resonance occurs when competition is resolved, and lets appropriate gate open

# 12. CONTROL OF SPATIALLY PRECISE ACTIONS #

![http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-valdo.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-valdo.jpg)

  * conditioned movement cannot be made until goal objects are recognized and selected, and their spatial locations specified
    * **what** stream learns independent object representation
    * **where** stream represents the object positions and how to move
    * what-where stream interactions generate movements towards recognized objects
  * as per ART:
    * ITp combines feature and positional information
    * ITa are positionally invariant
    * both are linked reciprocally
  * ITp projects to PPC - **target locations of object**
  * consider if **multiple objects in scene try to activate ITp, ITa**:
    * suppose particular ITa category represents valued goal object
    * **ITa representation can get amplified** by IT/AM/OMPFC resonance
    * amplified ITa representation can better compete for object attention, and can send **larger top-down priming signals** to its ITp representations
    * ITp representation that corresponds to valued object is thereby selectively amplified, and **sends amplified signal to PPC**, where its target location can win competition for where next movement will go
    * see **Where’s Waldo** problem - "How individuals can rapidly detect an object in a cluttered scene"

# 13. USING ATTENTIONAL SHROUDS #

  * how are positionally invariant and view-invariant categories learned by brain?
    * what is object?
    * how does brain learn what object is under both unsupervised and supervised learning conditions?
    * how does brain learn to bind multiple views of object into view-invariant and positionally invariant object category while scanning its parts with eye movements?
    * as eyes scan a scene, two successive eye movements may focus on different parts of same object or on different objects - how does brain avoid erroneously classifying views of different objects together, even before brain knows what object is?

![http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-artscan.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-artscan.jpg)

  * **ARTSCAN** model clarifies how brain uses scanning saccadic eye movements to learn view-invariant object categories
    * explains how object attention works with spatial attention in **where** cortical stream to direct eye movements that explore object surfaces
    * as eyes move around object surface, multiple view-specific categories are learned of object (e.g. in ITp) and are associated with emerging view-invariant object category (e.g. in ITa)
    * how does brain know which view-specific categories should be associated with given view-invariant category?
  * ARTSCAN predicts that pre-attentively formed surface representation activates attentional **shroud** - **form-fitting distribution of spatial attention**, even before brain can recognize surface as representing particular object
    * shroud persists within **where** stream during active scanning of object
    * shroud protects view-invariant category from getting reset, even while view-specific categories are reset, as eyes explore object
    * shroud does this by **inhibiting ITa reset mechanism**
  * how does shroud persist during active scanning of object?
    * surface-shroud resonance arises owing to feedback interactions between surface representation (e.g. in area V4) and spatial attention (e.g. in PPC), and focuses spatial attention upon object to be learned
    * when shroud collapses as eyes move to another surface, its view-invariant object category is reset as well
    * spatial attention can increase perceived brightness of surface

# 14. LEARNING OF SENSORY MOTOR MAPS AND GAINS #

  * learning of object representations in **what** stream uses excitatory matching and match-based learning to solve stability–plasticity dilemma
  * **where** stream learning uses inhibitory matching and mismatch-based learning
    * inhibitory matching is often between brain representations of target position and present position of motor effector
    * inhibitory matching computes difference vector that represents distance and direction of intended movement
    * difference vector is volitionally gated by GO signal that determines when and how fast movement will occur
  * during motor learning, difference vector can also generate error signals when same target position and present position are encoded but not properly calibrated
    * error signals eliminate source of mismatch through time by recalibrating system maps and gains
    * below model predicts how mismatch learning may tune spatial representations and adaptive motor gains in BG, CR, MC, PPC and PFC

![http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-bginteractions.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/grossberg-bginteractions.jpg)

  * perceptual/cognitive processes often use excitatory matching and match-based learning to create stable predictive representations of objects and events
  * complementary spatial/motor processes often use inhibitory matching and mismatch-based learning to continually update spatial maps and sensory motor gains
  * together, these complementary predictive and learning mechanisms create self-stabilizing perceptual/cognitive front end for activating more labile spatial/motor processes that control our changing bodies as they act upon objects in world