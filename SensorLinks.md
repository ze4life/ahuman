@@[Home](Home.md) -> [SensorsResearch](SensorsResearch.md) -> [SensorLinks](SensorLinks.md)

---


## Sensor Area Inputs ##

  * **primary input** - external world properties captured by sensor
  * **sensor control** - origination of control data and nature of inter-area link - to be understood, see sections below
  * **perception feedback** - time-based expectation for sensory data from perception area

## Sensor Area Outputs ##

  * **primary output** - sensory data, sent to perception area
  * **control feedback** - providing status of control command execution - executed completely or partially, or somehow in different way
  * **exposed control state properties** - emitted to external world to facilitate establishing direct communication channel with other subjects

## Biological Eye Sensor Paths ##

  * **primary input**
    * light -> rods (fast colorless contrast low-resolution receptors)
    * light -> cones (slow R/G/B high-resolution receptors)
  * **sensor control**
    * prefrontal cortex/eye field -> BSA/superior colliculus -> BSA/horizontal gaze center
    * prefrontal cortex/eye field -> BSA/pretectum/horizontal gaze center
    * visual cortex/association cortex -> superior colliculus -> pretectum/horizontal gaze center
    * brain stem/midbrain/pretectum -> oculomotor, trochlear, abducent nerve (III, IV, VI cranial) -> pretectum/Edinger-Westphal nucleus -> ciliary ganglion -> eye

{code}
constriction of pupil, accommodation of lens
ciliary ganglion - parasympathetic ganglion
Edinger-Westphal nucleus - parasympathetic cranial nerve nucleus
{code}

  * **primary output**
    * rods/cones -> thalamus/LGN/1-6 (main relay) -> primary visual cortex
    * rods/cones -> superior colliculus (10%, 150K axons - initiates move to orient eye toward stimulus - place it from peripheral field to fovea/macula)
    * rods/cones -> pretectum (pupil resize and accommodation reflex)
    * rods/cones -> hypothalamus (synchronize biological rhythms)

**http://www.acbrown.com/neuro/Lectures/EyeM/NrEyeM.htm**

![http://www.acbrown.com/neuro/Lectures/EyeM/NrEyeM_files/image012.png](http://www.acbrown.com/neuro/Lectures/EyeM/NrEyeM_files/image012.png)

## Linking Sensors to Perception - HLAv3 ##

  * **sensor/data** -> thalamus/input
  * thalamus/output -> perception/feed-forward-input
  * perception/feed-forward-output -> parietal/feed-forward-input
  * perception/feed-back-output -> thalamus/input
  * parietal/feed-forward-output -> **sensor/control**
  * parietal/feed-back-output -> perception/feed-back-input
  * **sensor/feedback** -> somatic/feed-forward-input
  * somatic/feed-forward-output -> parietal/feed-forward-input
  * somatic/feed-back-output -> parietal/feed-back-input

## Linking Sensors to Perception ##

  * for each sensor there is perception belief network for processing sensor data
    * several sensors are mapped to perception area
    * each sensor needs its own processing because of specific data format and patterns

## Interesting facts ##

  * when an animal attends to some features in its sensations, the neural representations even in the lowest cortical levels adapt mostly to those features and not to others

## Links ##

  * [Eye Movement](http://www.acbrown.com/neuro/Lectures/EyeM/NrEyeM.htm)