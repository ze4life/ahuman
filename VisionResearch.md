@@[Home](Home.md) -> [SensorsResearch](SensorsResearch.md) -> [VisionResearch](VisionResearch.md)

---


# Introduction #

This page is intended to collect the research information published in the field of human vision which can help to build informational model. Human vision is under great and long-term scientific attention and it gives us a lot of facts.

We can say that it is one of most important and functionally rich sensors for human intelligence. Information model of vision can help to understand the nature of effective information processing and generalize it for other sensors.

Implementing the vision in aHuman looks to me less obvious goal, because of its complexity and computer resource demands.

# Terms #

  * transfer ratio (LGN firing/retinal firing)

# See also #

  * [Biphasic Responses in the Lateral Geniculate Nucleus](LGNBiphasicResponses.md) - article review
  * [Thalamus Details](bioThalamus.md) - biological details, include visual pathway

# Interesting links #

  * [Brain Vision](http://brainmind.com/images/VisualPathway2.jpg)

![http://brainmind.com/images/VisualPathway2.jpg](http://brainmind.com/images/VisualPathway2.jpg)

  * [Wikipedia Thalamo-Cortical cooperation article](http://en.wikipedia.org/wiki/Recurrent_thalamo-cortical_resonance)

![http://upload.wikimedia.org/wikipedia/en/thumb/a/a0/Tc_circuit.png/300px-Tc_circuit.png](http://upload.wikimedia.org/wikipedia/en/thumb/a/a0/Tc_circuit.png/300px-Tc_circuit.png)

  * [IT Cortex Pathways](http://www.scholarpedia.org/wiki/images/f/f2/ITCortex_pathway.jpg)

![http://www.scholarpedia.org/wiki/images/f/f2/ITCortex_pathway.jpg](http://www.scholarpedia.org/wiki/images/f/f2/ITCortex_pathway.jpg)

  * [Eye to V1 Cortex Columns](http://mitpdev.mit.edu/library/erefs/arbib/images/figures/A181_fig001.gif)

![http://mitpdev.mit.edu/library/erefs/arbib/images/figures/A181_fig001.gif](http://mitpdev.mit.edu/library/erefs/arbib/images/figures/A181_fig001.gif)

  * [Vision - Lecture Notes](http://www.cns.nyu.edu/~david/courses/perception/lecturenotes/V1/lgn-V1.html)

![http://www.cns.nyu.edu/~david/courses/perception/lecturenotes/V1/LGN-V1-slides/Slide8.jpg](http://www.cns.nyu.edu/~david/courses/perception/lecturenotes/V1/LGN-V1-slides/Slide8.jpg)

# Details #

Currently we are looking for a model that can create a eye like structure and can be integrated with the aHuman brain.

## Biological Vision Flow ##

**High-level Flow**
  * retina -> LGN/thalamus -> PCA/V1 (primary sensory stream)
  * retina -> brainstem (machanics)
    * retina -> pretectum/brainstem (pupillary reflex)
    * retina -> superior colliculus/brainstem (moving the eyes in saccades)

![http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/LGN-V1-layers.png](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/LGN-V1-layers.png)

**diagram comments:**
  * retinal afferents make synaptic contacts on both relay cells (grey circle) and GABAergic intrinsic inhibitory interneurons (blue) in the LGN
  * LGN relay cells in turn provide input to both excitatory (green) and inhibitory (blue) neurons in layer 4 of the visual cortex
    * they also provide collateral input to layer 6 of the visual cortex and to inhibitory neurons in the perigeniculate nucleus (PGN, the visual part of the thalamic reticular nucleus)
  * PGN cells and intrinsic inhibitory interneurons of the LGN both provide inhibitory input to LGN relay cells
  * V1 layer 6 cells (red) provide a massive feedback projection to the LGN that contacts relay cells, intrinsic inhibitory interneurons and PGN cells
    * the same layer 6 cells also send an extensive collateral projection to layer 4 of the visual cortex, where they contact the spiny stellate cells receiving the input from the LGN and local inhibitory interneurons
    * layer 6 cells thus appear to exert a unique control over the access of the retinal input to the central visual system
  * there is also direct feedback from the motion area MT/V5 to layer 6
  * cells in layer 4B and 6 of V1 provide a direct feedforward projection to MT completing a circuit of interaction
    * this diagram only summarizes the direction of the connections
    * feedback from MT also targets layer 4B

**Retina**
  * **flow**: photoreceptors -> bipolar cells -> ganglion cells -> brain
    * photoreceptors - total ~130M
    * ganglion fibers to brain - total ~1.3M
  * **photoreceptors**:
    * rods - peripheral colorless intensity receptors
    * cones - R or G or B receptors - in the center (fovea)
  * **bipolar cells**:
    * uniform lighting of receptive field of bipolar cell will produce no response
  * **ganglion cells**:
    * ganglion cells are not selective for orientation or direction
    * M cells: sensitive to depth, motion, indifferent to color, fast, large receptive field - go to LGN
    * P cells: sensitive to shape, color, insensitive to motion, slow, small receptive field - go to LGN
    * K cells, sensitive to color and indifferent to shape or depth, large receptive field - go to LGN
    * light signal for wake/sleep cycle - go to pretectal olivary nucleus (PON)
    * final population that is used for eye movements

**Thalamus / LGN**
  * LGN separates retinal inputs into parallel streams, one containing color and fine structure, and the other containing contrast and motion
    * color and fine structure - top 4 layers (PV)
    * contrast and motion - lower 2 layers (MG)
    * LGN cells are not selective for orientation or direction
  * **flow**
    * feedforward: retina (eye ganglion cells) -> THA/LGN -> PCA/V1
      * retina -> LGN (10% of synaptic input to relay cells)
      * only retina spike produces LGN relay spike
      * not every retina spike produces LGN relay spike (only 25-50%)
      * transmission is not constant, but rather fluctuates slowly
      * transfer ratio fluctuations are not related to the retinal input
      * fluctuations are global, and involve much of the LGN
      * ipspilateral eye -> LGN 1 (2, 3, 5 layers) -> temporal optic radiations -> V1 (overlapping area)
      * contralateral eye -> LGN 2 (1, 4, 6 layers) -> parietal optic radiations -> V1
    * PCA/V1 -> THA/LGN
  * feedforward: LGN -> V1/L4 (6-9% of layer 4 excitatory inputs)
  * feedforward: LGN -> V1/L6
    * feedforward: V1/L6 -> V1/L4/spiny stellate cells (45% of layer 4 excitatory inputs)
    * feedback: V1/L6 (sensitive to stimulus orientation and direction of motion) -> LGN (30% of synatic input to relay cells, affects distal dendrites, also contact inhibitory interneurons in LGN)
    * feedback: pathway from V1/L6 is a property of all TH relay nuclei
      * directly excites relay cells
      * indirectly inhibits relay cells via the thalamic reticular nucleus (TRN)

**Thalamus / PGN**
  * feedback: V1/L6 -> PGN
  * PGN (perigeniculate nucleus)/TRN (thalamic reticular nucleus)/THA -> THA/LGN
    * PGN activity is negatively correlated with LGN firing

**Brain Stemp/Parabrachial Nucleus (PBN)**:
  * PBN (part of the Ascending Arousal System) receives retinal input
  * activity in PBN is highly correlated with fluctuations in LGN transmission
  * fluctuations in the LGN activity and transfer ratio are uncorrelated with the firing rate of retinal ganglion cells (that innervate the LGN)
  * fluctuations in transfer ratio (retina/RGN) are synchronized across LGN, do not depend on visual stimulation, and are highly correlated with neural activity in the PBN

**Brain Stem/Superior Colliculus**
  * SC is a visual salience map for orienting eye movements

**Visual Cortex:**
  * feedforward: V1/L4 -> MT
  * feedforward: V1/L6 -> MT
  * feedback: MT/V5 -> V1/L6
  * feedback: MT -> V1/L4

**feedback: V1/L6 -> LGN**
  * if dropped, do not affect stationary objects
  * if dropped, short moving objects are signaled by LGN, while large moving objects are not
  * feedback fine-tunes local circuitry in the LGN to optimize the extraction of salient features, and in relation to the shift between burst and tonic firing might alert and focus the circuitry on stimuli requiring attention

## Primary Visual Cortex Model ##

![http://topographica.org/images/Topo-arch-white.jpg](http://topographica.org/images/Topo-arch-white.jpg)

This model is used by topographica to simulate the human eye interaction with the cortex.
There are various models proposed to implement these parts of the model and currently we are researching on the implementation of working LGN module.

Primary Visual cortex will do the processing on the data it gets from the sensor (eye) and will be integrated with the aHuman brain to excite certain neurons to understand the information that it gets from the sensors. This is in accordance with the biological functionality of cortex and eye.

## LGN ##

LGN functionality can be implemented using _'Difference of Gaussian'_ algorithm for edge detection. Currently research is being done in this area to create a working model of LGN.

LGN will get input from the sensors which in this case will simulate the aHuman eye.

## How Eye is controlled ##

See [Eye in Detail](http://www.dartmouth.edu/~dons/part_1/chapter_4.html)

**Control reasons**:

  * Saccades
  * Tracking moving objects
  * Adoption to moving head
  * Intentional focus change
  * Pupil change due to light intensity change
  * Reflexes
  * Eyes sunchronization

**Paths**

  * capture: eye -> LGN (thalamus) -> visual cortex
  * what/ventral: visual cortex -> temporal lobe
  * where/dorsal: visual cortex -> parietal (association) cortex -> frontal lobe
  * early control: parietal cortex -> superior colliculus (midbrain, primary integrating center for eye movements) -> pons (connects left and right cerebellum) -> eye muscles
  * late control: frontal lobe -> superior colliculus -> pons -> eye muscles

## Visual perception ##

  * light level is not transmitted by eyes - only light differences
  * eyes constantly move (saccadic movement), slight tremor and jumps over visual field
  * this produces constant changes in light level over retina
  * when eye is stabilised, e.g. by paralyzing eye muscles and stabilising head, picture disappears
  * then, moving objects can be seen, they pop out suddenly