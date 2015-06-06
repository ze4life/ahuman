[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [BiologicalHierarchyReduced](BiologicalHierarchyReduced.md)

---


This page is reduction of [Full Biological Hierarchy](BiologicalHierarchyFull.md) for the purpose of modeling in aHuman.

## Biological Reduction Rationale ##

  * reduction hierarchy contains only functions copied to aHuman
  * visual brain functions are regarded as generic sensory approach
  * motor is replaced by effector, movement is action
  * body remained as term, but its nature is completely different for aHuman
    * task performed for the mind is the same - default reward system and mandatory part for any action
    * hence somatosensory brain elements remained predefined mandatory sensor, body feeling.
  * single hemisphere is assumed to be enough
  * blood and heart are regarded as regulatory functions, controlling resources spent by brain
  * thalamic area is primarily considered as relay, and to simplify picture, some direct ways, e.g. ACA to HCA are treated as passing via THA
  * limbic lobe was split into parts allocated to other modules, because parts of limbic system seem to me quite different while having strong connections to specific parts
    * anterior cingulate cortex has strong bidirectional connections with anterior cortex and allocated to ACA, posterior cingulate - to PCA as well
    * secondary role of thalamic area is spreading of modulatory activity (sleep-awake cycle, hormones, neurotransmitters and others), and because of that septal nuclei allocated to THA
    * hippocampus is strong aligned with memory formation functions of temporal lobe - enthorinal and perirhinal cortices and eventually allocated to HCA
    * fornix is hippocampus communication facility and that's why allocated also to HCA
    * basal ganglia is rational primitive motor system and needs to be separate module because it is one of major non-cortical functions
    * amygdala is allocated to BGA because generating movements by emotional, but not rational signals

## Biological Brain Hierarchy Reduction ##

  * neocortex
    * frontal lobe
      * **prefrontal cortex** (personality, judgement, complex planning, inhibition, morality)
        * **orbitofrontal cortex** (involved in sensory integration, in representing the affective value of reinforcers, and in decision-making and expectation)
      * **premotor cortex** (patterned effector actions and planning)
      * **primary motor cortex** (individual actions)
        * **frontal eye fields** (control specific sensor)
    * parietal lobe
      * **primary somatosensory cortex** (anterior, basic sensations of the body)
      * **superior parietal lobule** (posterior, body sensations relationships, locating objects in space)
      * **inferior parietal lobule** (posterior, semantics, involved in reading both in regards to meaning and phonology)
      * **intraparietal sulcus** (posterior, essential in guidance of limb and eye movement)
      * **general interpretation area** (opinions)
    * occipital lobe
      * **primary visual cortex** (simple specific sensor spatial primitives)
      * **visual associations** (intermediate specific sensor spatial and temporal patterns)
      * **fusiform gyris** (object representation from specific sensor)
    * temporal lobe
      * **insula** (habits, visceral sensations)
      * **parahippocampal gyrus** (formation of spatial memory, encoding and recognition of scenes)
        * anterior parahippocampal gyrus
          * **perirhinal cortex** (specific sensor perception and memory, facilitates recognition and identification of environmental stimuli)
          * **entorhinal cortex** (hub in a widespread network for memory and navigation, autobiographical/declarative/episodic memories, memory formation, memory consolidation, and memory optimization in sleep)
        * **posterior parahippocampal gyrus** (spatial declarative memory)
  * limbic system
    * **cingulate cortex** (life resources consumption control, cognitive and attentional processing)
      * **anterior cingulate cortex** (error and conflict detection processes)
      * **posterior cingulate cortex** (episodic memory, emotion, navigation, resting)
    * [amygdala](bioAmygdala.md) (signalling cortex of motivationally significant stimuli)
    * **septal nuclei** (controller of theta rhythm, major source of projections to hippocampus)
    * **hippocampus** (detection of novel events, places and stimuli, spatial coding)
      * **dentate gyrus** (formation of memories, distinguishing multiple instances of similar events or multiple visits to the same location, stress and depression)
      * **subiculum** (spatial relations, working memory)
      * **fornix** (carries signals from the hippocampus)
    * [basal ganglia](bioBasalGanglia.md) (primitive effectors system)
      * **striatum** (planning and modulation of actions)
        * **caudate nucleus** (part of the learning and memory system)
        * **putamen** (regulate actions and influence various types of learning)
        * **nucleus accumbens** (reward, pleasure, addiction, fear)
          * **nucleus accumbens core** (acquisition and maintenance of a new strategy)
          * **nucleus accumbens shell** (mediate learning about irrelevant stimuli)
      * **pallidum** (reward and incentive motivation)
        * **globus pallidus externa** (main regulator of the basal ganglia system)
        * **substantia nigra** (reward, addiction, and actions)
      * **subthalamic nucleus** (action selection)
  * diencephalon (relay system between sensory input neurons and other parts of the brain)
    * [thalamus](bioThalamus.md) (relaying sensation, spatial sense and motor signals to the cerebral cortex, regulation of consciousness, sleep and alertness)
      * **specific relay nuclei** (project to/from specific functional area of neocortex)
        * **lateral geniculate body** (specific sensor -> specific sensor cortex area)
        * ventral posterior nucleus
          * **ventral posterior lateral nucleus** (body sensations -> primary somesthetic area)
        * **ventral lateral/anterior nucleus** (effector control feedback from cerebellum and striatum -> primary effector cortex)
      * **association nuclei** (project to association areas)
        * **anterior nucleus** (mammillary bodies, hypothalamus, cingulate gyrus -> cingulate gyrus, hypothalamus, and hippocampus)
        * **medial nucleus** (somatic sensory input from hypothalamus, amygdala -> prefrontal cortex, hypothalamus, hippocampus, striatum)
        * **lateral nucleus** (hypothalamus, cingulate gyrus -> cingulate gyrus)
        * **posterior group nuclei** (pain from spinothalamic tract and 5th cranial nerve -> insula)
        * **pulvinar nuclei** (reciprocal connections with association areas)
      * non-specific nuclei
        * **intralaminar nuclei** (basal ganglia, reticular formation -> all parts of neocortex, effector control system, perceptions of various modalities)
        * **reticular nuclei** (from all fibers leaving and entering the thalamus -> all thalamic nuclei, cortical regulation of the thalamic activity)
    * **hypothalamus** (modulatory, life support and the sleep/wake cycle)
      * **mammillary body** (relay from the amygdala and hippocampus to thalamus)
      * **median eminence** (stimulate or inhibit the release of hormones from the anterior pituitary)
  * **brain stem** (main sensory innervation)
    * **medulla oblongata** (autonomic, involuntary functions, relays nerve signals between the brain and spinal cord)
    * midbrain
      * tectum
        * **superior colliculus** (preliminary specific sensor processing and control of specific sensor)
      * cerebral peduncle
        * **midbrain tegmentum** (involved in many unconscious homeostatic and reflexive pathways)
        * **crus cerebri** (contains effector tracts)
        * **substantia nigra** (sensor control, effector planning, reward seeking, learning, and addiction)
    * **pons** (relay signals from the forebrain to the cerebellum, along with nuclei that deal primarily with sleep, equilibrium, sensor control, expressing emotions)
      * cranial nerves
        * 2 - **optic nerve** (transmits specific sensor information to the brain)
        * 3 - **oculomotor nerve** (perform most sensor control)
        * 4 - **trochlear nerve** (perform certain sensor control)
        * 6 - **abducens nerve** (perform certain sensor control)
  * **cerebellum** (complex actions, sequential thinking, attention, coordination, precision, and accurate timing)
    * peduncles
      * **inferior cerebellar peduncle** (to/from medulla/spinal cord)
      * **middle cerebellar peduncle** (from pons)
      * **superior cerebellar peduncle** (to midbrain)
      * **arbor vitae** (brings sensory/motor information to/from cerebellum)
    * **spinocerebellum** (control actions power and coordination of multiple actions, cerebellum/basal ganglia/neocortex effector actions)
    * **cerebrocerebellum** (participates in planning actions, sensory/prefrontal -> cerebellum -> thalamus -> motor cortex -> effectors
    * **choroid plexus** (inhibits neuronal maturation)
  * spinal cord
    * **anterolateral system** (body feeling pathway)
    * **corticospinal tract** (effector pathway for upper effector neuronal signals coming from the cerebral cortex/basal ganglia)
      * **lateral corticospinal tract** (distal effector actions)
      * **anterior cortical spinal tract** (affect general body state)
    * **ventral spinocerebellar tract** (proprioceptive information travels up the spinal cord)
    * **dorsal spinocerebellar tract** (conveys inconscient proprioceptive information)