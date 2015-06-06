[Home](Home.md) -> [BrainPictures](BrainPictures.md)

---




# Biological Overview #

## Biological Hierarchy ##

  * [Full Biological Hierarchy](BiologicalHierarchyFull.md)
  * [Reduced Biological Hierarchy](BiologicalHierarchyReduced.md)

## Links to Common Terms ##

![http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/top.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/top.jpg)

  * head
    * sensors
    * sensor data tract
    * sensor control tract
    * brain
  * body (spinal cord)
    * effectors
    * body feeling components
    * body feeling data tract
    * body feeling modulation tract
    * effectors control tract
    * effectors feedback tract
    * effectors feeling tract

# Biological Model #

## Biological Module View ##

![http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/modules.jpg](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/modules.jpg)

Modules are defined as follows:

<table border='1' cellspacing='5'>
<tr>
<th>Module and allocated areas</th>
<th>Functions</th>
<th>Flows</th>
</tr>

<tr>
<td>
<b>Head Sensors Area (HSA)</b>
</td>
<td>
<ul><li><b>Owned Functions</b>
<ul><li>capture events from external world<br>
</li><li>capture static data from external world<br>
</li><li>expressing sensing behaviour<br>
</li></ul></li><li><b>Involved in Functions</b>
<ul><li>perceptions of various modalities<br>
</li><li>pay attention to selected area / overt attention<br>
</li><li>tracking objects / covert attention<br>
</li><li>saccadic perception / covert attention<br>
</td>
<td>
</li></ul></li><li><b>Inbound</b>
<ul><li>(External World) -> sensor data<br>
</li><li>PCA -> BSA -> low-level sensory control in perception<br>
</li><li>ACA -> BSA -> attention area selection<br>
</li></ul></li><li><b>Outbound</b>
<ul><li>sensory data -> BSA<br>
</li><li>perception control feedback -> THA -> PCA<br>
</li><li>attention sensor control feedback -> THA -> ACA<br>
</li><li>sensory state expression -> (External World)<br>
</td>
</tr></li></ul></li></ul>

<tr>
<td>
<b>Thalamus Area (THA)</b>
<ul><li>diencephalon<br>
<ul><li>thalamus<br>
</li><li>hypothalamus<br>
</li></ul></li><li>limbic system<br>
<ul><li>septal nuclei<br>
</td>
<td>
</li></ul></li><li><b>Owned Functions</b>
<ul><li>visceral control center of the body<br>
</li><li>relaying sensation, spatial sense and motor signals to the cerebral cortex<br>
</li><li>regulation of consciousness, sleep and alertness<br>
</li><li>control memory, attention and alertness<br>
</li><li>controller of theta rhythm<br>
</li></ul></li><li><b>Involved in Functions</b>
<ul><li>effector control system<br>
</li><li>perceptions of various modalities<br>
</li><li>cortical regulation of the thalamic activity<br>
</li><li>modulatory, life support and the sleep/wake cycle<br>
</li><li>attention, planning, organization<br>
</li><li>abstract thinking, multi-tasking and active memory<br>
</td>
<td>
</li></ul></li><li><b>Relay</b>
<ul><li>BSA -> sensor data -> PCA<br>
</li><li>BSA -> sensor data (lateral posterior nucleus, pulvinar) -> HCA<br>
</li><li>BSA -> perception (intralaminar) -> BGA<br>
</li><li>BSA -> cerebellum effector control feedback -> ACA<br>
</li><li>BSA -> body sensations -> ACA<br>
</li><li>BSA -> pain -> PCA<br>
</li><li>HCA -> alerts, (anterior/medial nuclei) -> ACA<br>
</li><li>BGA -> sensory data (ventral posterolateral/posteromedial nucleus) -> ACA<br>
</li><li>BGA -> striatum effector control feedback -> ACA<br>
</li></ul></li><li><b>Reciprocal</b>
<ul><li>PCA -> (medial nuclei) -> PCA<br>
</li><li>HCA -> (anterior nuclei) -> HCA<br>
</li><li>ACA -> (medial nuclei) -> ACA<br>
</td>
</tr></li></ul></li></ul>

<tr>
<td>
<b>Anterior Cortex Area (ACA)</b>
<ul><li>frontal lobe<br>
</li><li>parietal lobe<br>
<ul><li>primary somatosensory cortex<br>
</li></ul></li><li>limbic system<br>
<ul><li>cingulate cortex<br>
<ul><li>anterior cingulate cortex<br>
</td>
<td>
</li></ul></li></ul></li><li><b>Owned Functions</b>
<ul><li>self-consciousness / personality / identity<br>
</li><li>top-level complex planning / imagination<br>
</li><li>inhibition control<br>
</li><li>model of good ideal behaviour / morality<br>
</li><li>top-level patterned effector actions<br>
</li><li>cortex individual effector actions and sensor control<br>
</li><li>top-level error and conflict detection<br>
</li><li>guide task selection<br>
</li><li>monitor progress<br>
</li><li>basic sensations of the body<br>
</li><li>working memory<br>
</li></ul></li><li><b>Involved in Functions</b>
<ul><li>sensory integration<br>
</li><li>representing the affective value of reinforcers<br>
</li><li>decision-making<br>
</td>
<td>
</li></ul></li><li><b>Inbound</b>
<ul><li>BGA -> THA -> sensory data<br>
</li><li>PCA -> perception data<br>
</li><li>HCA -> past experience<br>
</li><li>HCA -> reward signals (orbitomedial PFC)<br>
</li><li>BSA -> THA -> body senses<br>
</li><li>THA -> bioregulatory responses<br>
</li></ul></li><li><b>Outbound</b>
<ul><li>current converged sensory input (pcf) -> HCA<br>
</li><li>motor/behavioral commands -> PCA<br>
</li><li>reward, feedback to bias flow along expectation -> PCA<br>
</li><li>motor control -> BSA<br>
</li><li>anti-inhibitory emotional context -> BGA<br>
</li><li>inhibitory emotional context -> BGA<br>
</li><li>guidance of movement -> BGA<br>
</li><li>(premotor) -> THA<br>
</td>
</tr></li></ul></li></ul>

<tr>
<td>
<b>Posterior Cortex Area (PCA)</b>
<ul><li>occipital lobe<br>
</li><li>parietal lobe<br>
<ul><li>superior parietal lobule<br>
</li><li>inferior parietal lobule<br>
</li><li>intraparietal sulcus<br>
</li><li>general interpretation area<br>
</li></ul></li><li>limbic system<br>
<ul><li>cingulate cortex<br>
<ul><li>posterior cingulate cortex<br>
</td>
<td>
</li></ul></li></ul></li><li><b>Owned Functions</b>
<ul><li>body sensations relationships / body image<br>
</li><li>opinions<br>
</li><li>simple specific sensor spatial primitives<br>
</li><li>intermediate specific sensor spatial and temporal patterns<br>
</li><li>object representation from specific sensor<br>
</li><li>episodic memory, emotion, navigation, resting<br>
</li></ul></li><li><b>Involved in Functions</b>
<ul><li>semantics<br>
</li><li>reading both in regards to meaning and phonology<br>
</li><li>guidance of limb and eye movement<br>
</td>
<td>
</li></ul></li><li><b>Inbound</b>
<ul><li>HSA -> BSA -> THA -> sensory data<br>
</li><li>HSA -> BSA -> THA -> sensory perception control feedback<br>
</li><li>HCA -> THA -> long-term memory sequences<br>
</li><li>BSA -> THA -> pain<br>
</li><li>ACA -> reward, feedback to bias flow along expectation<br>
</li></ul></li><li><b>Outbound</b>
<ul><li>sensory data -> HCA<br>
</li><li>associations -> THA -> ACA<br>
</li><li>guide saccadic perception -> BSA -> HSA<br>
</li><li>feelings -> ACA<br>
</td>
</tr></li></ul></li></ul>

<tr>
<td>
<b>Hippocampus Area (HCA)</b>
<ul><li>temporal lobe<br>
</li><li>limbic system<br>
<ul><li>hippocampus<br>
</li><li>fornix<br>
</td>
<td>
</li></ul></li><li><b>Owned Functions</b>
<ul><li>specific sensor perception and memory<br>
</li><li>working memory<br>
</li><li>autobiographical/declarative/episodic memories<br>
</li><li>formation and storing spatial declarative memory<br>
</li><li>encoding and recognition of scenes, spatial relations<br>
</li><li>detection of novel events, places and stimuli, spatial coding<br>
</li><li>distinguishing multiple instances of similar events, multiple visits to the same location<br>
</li><li>emotional and affective state<br>
</li><li>distinguishing stress and depression<br>
</li><li>assigning stimuli to categorical classes<br>
</li><li>habits, visceral sensations<br>
</li></ul></li><li><b>Involved in Functions</b>
<ul><li>memory consolidation<br>
</li><li>memory optimization in sleep<br>
</li><li>recognition and identification of environmental stimuli<br>
</td>
<td>
</li></ul></li><li><b>Inbound</b>
<ul><li>PCA -> primary and secondary sensory perception<br>
</li><li>PCA -> polymodal/associative sensory perception<br>
</li><li>ACA -> converged sensory input<br>
</li><li>BSA -> sensory input (hierarchical sensory pathway)<br>
</li><li>THA -> emotional stimulus<br>
</li><li>THA -> modulatory inputs<br>
</li><li>THA (septum) -> (fornix) -> initiation of hippocampal thata-rithm<br>
</li></ul></li><li><b>Outbound</b>
<ul><li>sensory association -> BGA<br>
</li><li>reward signals -> ACA<br>
</li><li>past experience -> ACA<br>
</li><li>mismatch signal (to raise ACh in HC to facilitate encoding) -> THA (septum)<br>
</li><li>match signal (to attenuate ACh in HC to facilitate retrieval) -> THA (septum)<br>
</td>
</tr></li></ul></li></ul>

<tr>
<td>
<b>Basal Ganglia Area (BGA)</b>
<ul><li>limbic system<br>
<ul><li>basal ganglia<br>
</li><li>amygdala<br>
</td>
<td>
</li></ul></li><li><b>Owned Functions</b>
<ul><li>starting, stopping and monitoring movement<br>
</li><li>inhibit unnecessary movement<br>
</li><li>planning and modulation of actions, regulate actions<br>
</li><li>reward, pleasure, addiction, fear<br>
</li><li>reward and incentive motivation<br>
</li><li>acquisition and maintenance of a new strategy<br>
</li><li>mediate learning about irrelevant stimuli<br>
</li><li>action selection<br>
</li><li>block slow thinking<br>
</li><li>quick threat assessment<br>
</li><li>signalling cortex of motivationally significant stimuli<br>
</li></ul></li><li><b>Involved in Functions</b>
<ul><li>learning and memory system<br>
</li><li>influence various types of learning<br>
</td>
<td>
</li></ul></li><li><b>Inbound</b>
<ul><li>ACA -> anti-inhibitory emotional context<br>
</li><li>ACA -> inhibitory emotional context<br>
</li><li>HCA -> sensory association<br>
</li></ul></li><li><b>Outbound</b>
<ul><li>regulation -> ACA<br>
</li><li>cognition -> ACA<br>
</li><li>instant actions -> BSA<br>
</li><li>sensory data (auditory, dorsal auditory pathway) -> PCA<br>
</td>
</tr></li></ul></li></ul>

<tr>
<td>
<b>Brain Stem Area (BSA)</b>
<ul><li>brain stem<br>
</li><li>cerebellum<br>
</td>
<td>
</li><li><b>Owned Functions</b>
<ul><li>autonomic behavior, autonomic, involuntary functions<br>
</li><li>integrate sensors and effectors for precise timing of actions<br>
</li><li>maintain wakefulness and attention<br>
</li><li>modulation of outbound effectors information<br>
</li><li>preliminary specific sensor processing<br>
</li><li>complex actions, sequential thinking<br>
</li><li>attention, coordination, precision, and accurate timing<br>
</li><li>inhibits neuronal maturation<br>
</li></ul></li><li><b>Involved in Functions</b>
<ul><li>control of specific sensor<br>
</li><li>many unconscious homeostatic and reflexive pathways<br>
</li><li>sensor control, effector planning<br>
</li><li>reward seeking, learning, and addiction<br>
</li><li>sleep, equilibrium, sensor control, expressing emotions<br>
</li><li>control actions power and coordination of multiple actions<br>
</li><li>control cerebellum/basal ganglia/neocortex effector actions<br>
</li><li>planning actions<br>
</td>
<td>
</li></ul></li><li><b>Inbound</b>
<ul><li>TBD<br>
</li></ul></li><li><b>Outbound</b>
<ul><li>TBD<br>
</td>
</tr></li></ul></li></ul>

<tr>
<td>
<b>Spinal Cord Area (SCA)</b> (Body)<br>
<ul><li>spinal cord<br>
</li><li>(peripheral nervous system)<br>
</td>
<td>
</li><li><b>Owned Functions</b>
<ul><li>body feeling<br>
</li><li>affect general body state<br>
</li><li>generating proprioceptive information<br>
</li><li>conveys inconscient proprioceptive information<br>
</li></ul></li><li><b>Involved in Functions</b>
<ul><li>activate effectors<br>
</li><li>distal effector actions<br>
</td>
<td>
</li></ul></li><li><b>Inbound</b>
<ul><li>TBD<br>
</li></ul></li><li><b>Outbound</b>
<ul><li>TBD<br>
</td>
</tr>
</table></li></ul></li></ul>

## Biological Paths ##

  * [neural pathway connecting the posterior part of the temporoparietal junction with the frontal cortex](http://en.wikipedia.org/wiki/Arcuate_fasciculus)
  * [sensory pathway transmitting fine touch, vibration and conscious proprioceptive information from the body to the cerebral cortex](http://en.wikipedia.org/wiki/Dorsal_column-medial_lemniscus_pathway)
  * [sensory pathway originating in the spinal cord and transmitting pain, temperature, itch and crude touch to the thalamus](http://en.wikipedia.org/wiki/Ventral_spinothalamic_tract)
  * [pathway arising from motor area of the cerebral cortex and controlling movement of ipsilateral limbs](http://en.wikipedia.org/wiki/Lateral_corticospinal_tract)
  * [pathway, conducting voluntary motor impulses from primary motor cortex to the motor centers of the cord](http://en.wikipedia.org/wiki/Anterior_corticospinal_tract)
  * [pathway connecting the cerebral cortex to the medulla in brainstem, controlling muscles of the face, head and neck](http://en.wikipedia.org/wiki/Corticobulbar_tract)
  * [pathway connecting the left and right cerebral hemispheres and facilitating interhemispheric communication](http://en.wikipedia.org/wiki/Corpus_callosum)
  * [pathway connecting ventral tegmentum to frontal cerebral cortex, involved in motivation and emotional response](http://en.wikipedia.org/wiki/Mesocortical_pathway)
  * [pathway begins in midbrain and connects to striatum, amygdala, hippocampus, medial prefrontal cortex](http://en.wikipedia.org/wiki/Mesolimbic_pathway)
  * [pathway connecting substantia nigra with striatum, involved in production of movement](http://en.wikipedia.org/wiki/Nigrostriatal_pathway)
  * [intra-hypothalamus pathway, involved in regulation of lactation, menstrual cycle, vision, blood flow and sexual functions](http://en.wikipedia.org/wiki/Tuberoinfundibular_pathway)
  * [ventral stream travels to the temporal lobe and is involved with object identification](http://en.wikipedia.org/wiki/Ventral_stream)
  * [dorsal stream stretches from the primary visual cortex (V1) in the occipital lobe forward into the parietal lobe](http://en.wikipedia.org/wiki/Ventral_stream)
  * [Papez circuit, one of major pathways of limbic system and is involved in cortical control of emotion](http://en.wikipedia.org/wiki/Papez_circuit)


# Biological Life Pictures #

Operating of the mind as a whole. Mind parts.

  * [From Cortex to Old Brain](http://www.humanneurophysiology.com/imageshypothalami/fig-12.gif)

![http://www.humanneurophysiology.com/imageshypothalami/fig-12.gif](http://www.humanneurophysiology.com/imageshypothalami/fig-12.gif)