@@[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [BrainAreaTSA](BrainAreaTSA.md) -> [BrainRegionTARGET\_TSA\_EYE](BrainRegionTARGET_TSA_EYE.md)

---


This page covers biological details of component Eye.
Region is part of aHuman target integrated biological model.

  * **Top-down path to region**: Target -> Human Sensors (aHumanSensors) -> Eye (TARGET.TSA.EYE) (see [Mind Maps](OverallMindMaps.md))
  * **Type**: sensor
  * **Brain area**: [Sensor Area](BrainAreaTSA.md)
  * **Role**: unknown
  * **Function**: Light and Color Perception Sensor
(generated)
# Components #
(generated)


**Component items**:
  * **Eye sensory data** (**eye-sensory**)
    * Eye - rods and cones (eye-edge-output -> [LPC.FD.RT](BrainRegionLPC_FD_RT.md)): after on-center/off-center edge extraction and zipping 100:1
    * Eye - somatic receptors (eye-somatic -> [LPC.PN.SG.TRG](BrainRegionLPC_PN_SG_TRG.md)): eye -> semilunar ganglion/ophthalmic -> PTR
    * Eye - visceral receptors (eye-visceral -> [LPC.MM.MSTR](BrainRegionLPC_MM_MSTR.md)): eye -> semilunar ganglion/ophthalmic -> STR, proprioception
  * **Eye rotation motor muscles** (**eye-rotation-motor**)
    * [Eye - inferior oblique muscle](http://en.wikipedia.org/wiki/Inferior_oblique_muscle) ([LPC.MM.OCN](BrainRegionLPC_MM_OCN.md) -> [eye-muscle-rotate-major-inferior-oblique](HumanMusclesHead.md)): extorsion, elevation, abduction
    * [Eye - inferior rectus muscle](http://en.wikipedia.org/wiki/Inferior_rectus_muscle) ([LPC.MM.OCN](BrainRegionLPC_MM_OCN.md) -> [eye-muscle-rotate-major-inferior-rectus](HumanMusclesHead.md)): depression and adduction
    * [Eye - medial rectus muscle](http://en.wikipedia.org/wiki/Medial_rectus_muscle) ([LPC.MM.OCN](BrainRegionLPC_MM_OCN.md) -> [eye-muscle-rotate-major-medial-rectus](HumanMusclesHead.md)): adducts the eyeball
    * [Eye - superior rectus muscle](http://en.wikipedia.org/wiki/Superior_rectus_muscle) ([LPC.MM.OCN](BrainRegionLPC_MM_OCN.md) -> [eye-muscle-rotate-major-superior-rectus](HumanMusclesHead.md)): elevates, adducts, and rotates medially the eye
    * [Eye - levator palpebrae superioris muscle](http://en.wikipedia.org/wiki/Levator_palpebrae_superioris_muscle) ([LPC.MM.OCN](BrainRegionLPC_MM_OCN.md) -> [eye-muscle-rotate-major-levator-palpebrae](HumanMusclesHead.md)): retracts/elevates eyelid
    * [Eye - superior oblique muscle](http://en.wikipedia.org/wiki/Superior_oblique_muscle) ([LPC.MM.TRH](BrainRegionLPC_MM_TRH.md) -> [eye-muscle-rotate-minor](HumanMusclesHead.md)): superior oblique, rotation in a vertical plane - looking down and up, rotation in the plane of the face
    * [Eye - lateral rectus muscle](http://en.wikipedia.org/wiki/Lateral_rectus_muscle) ([LPC.HP.ABD](BrainRegionLPC_HP_ABD.md) -> [eye-muscle-rotate-vestibular](HumanMusclesHead.md)): lateral rectus, quick turn to the right -> compensatory reflex turning of two eyes to the left
  * **Eye pupil and accomodation motor muscles** (**eye-pupil-motor**)
    * [Eye - ciliary muscle - sympathetic](http://en.wikipedia.org/wiki/Ciliary_muscle) ([LAC.PN.SYM.SCG](BrainRegionLAC_PN_SYM_SCG.md) -> [eye-muscle-curvature-sympathetic](HumanMusclesHead.md)): to ciliary muscle to increase eye accomodation
    * [Eye - ciliary muscle - parasympathetic](http://en.wikipedia.org/wiki/Ciliary_muscle) ([LAC.PN.PSYM.CLG](BrainRegionLAC_PN_PSYM_CLG.md) -> [eye-muscle-curvature-parasympathetic](HumanMusclesHead.md)): to ciliary muscle to inhibit eye accomodation
    * [Eye - iris sphincter muscle](http://en.wikipedia.org/wiki/Iris_sphincter_muscle) ([LAC.PN.PSYM.EPG](BrainRegionLAC_PN_PSYM_EPG.md) -> [eye-muscle-pupil-close](HumanMusclesHead.md)): to sphincter pupillae to close pupil
    * [Eye - iris dilator muscle](http://en.wikipedia.org/wiki/Iris_dilator_muscle) ([LAC.PN.SYM.SCG](BrainRegionLAC_PN_SYM_SCG.md) -> [eye-muscle-pupil-open](HumanMusclesHead.md)): to dilator pupillae to open pupil
  * **Eyelid motor muscles** (**eyelid-motor**)
    * [Eye - orbicularis oculi muscle:temporal](http://en.wikipedia.org/wiki/Orbicularis_oculi_muscle) ([LPC.HP.FCM](BrainRegionLPC_HP_FCM.md) -> [eye-muscle-close-conscious-orbital](HumanMusclesHead.md)): orbital portion, contraction of the orbital to reduce glare
    * [Eye - orbicularis oculi muscle:zygomatic](http://en.wikipedia.org/wiki/Orbicularis_oculi_muscle) ([LPC.HP.FCM](BrainRegionLPC_HP_FCM.md) -> [eye-muscle-close-conscious-lacrimal](HumanMusclesHead.md)): lacrimal part (tensor tarsi), conscious muscle to close eye; draws the eyelids and the ends of the lacrimal canals medialward and compresses them against the surface of the globe of the eye; compresses the lacrimal sac
    * [Eye - orbicularis oculi muscle:palpebrale](http://en.wikipedia.org/wiki/Orbicularis_oculi_muscle) ([LPC.HP.FCM](BrainRegionLPC_HP_FCM.md) -> [eye-muscle-close-involuntary-palpebrale](HumanMusclesHead.md)): palpebral portion, acts involuntarily, closing the lids gently; involuntary muscle to close eye
    * [Eye - superior tarsal muscle](http://en.wikipedia.org/wiki/Superior_tarsal_muscle) ([LAC.PN.SYM.SCG](BrainRegionLAC_PN_SYM_SCG.md) -> [eye-muscle-superior-tarsal](HumanMusclesHead.md)): raise the upper eyelid
    * [Eye - inferior tarsal muscle](http://en.wikipedia.org/wiki/Tarsus_%28eyelids%29) ([LAC.PN.SYM.SCG](BrainRegionLAC_PN_SYM_SCG.md) -> [eye-muscle-inferior-tarsal](HumanMusclesHead.md)): lower lid retraction
    * [Eye - orbitalis muscle](http://en.wikipedia.org/wiki/Orbitalis_muscle) ([LAC.PN.SYM.SCG](BrainRegionLAC_PN_SYM_SCG.md) -> [eye-orbitalis-muscle](HumanMusclesHead.md)): protrusion of eyeball
  * **Eye glands** (**eye-glands**)
    * [Eye - lacrimal gland](http://en.wikipedia.org/wiki/Lacrimal_gland) ([LAC.PN.PSYM.SPG](BrainRegionLAC_PN_PSYM_SPG.md) -> [eye-tears-gland](HumanMusclesHead.md)): tears
    * Eye - lacrimal gland and conjunctiva receptors (eye-lacrimal-gland-conjunctiva-receptors -> [LPC.PN.SG.TRG](BrainRegionLPC_PN_SG_TRG.md)): tears

# Connectivity #
(generated)


![http://ahuman.googlecode.com/svn/images/dot/aHuman/TARGET.TSA.EYE.dot.png](http://ahuman.googlecode.com/svn/images/dot/aHuman/TARGET.TSA.EYE.dot.png)

**Inbound Region Connections:**

| **Source Area** | **Source Region** | **Source Name** | **Type** | **Reference** |
|:----------------|:------------------|:----------------|:---------|:--------------|
| [LAC](BrainAreaLAC.md) | [LAC.PN.PSYM.CLG](BrainRegionLAC_PN_PSYM_CLG.md) | Ciliary Ganglion | eye-muscle-curvature-parasympathetic | [Autonomic nervous system (CLG -> EYE)](http://www.neurophysiology.ws/autonomicns.htm) |
|                 | [LAC.PN.PSYM.EPG](BrainRegionLAC_PN_PSYM_EPG.md) | Episcleral Ganglion | eye-muscle-pupil-close | [Autonomic nervous system (EPG -> EYE)](http://www.neurophysiology.ws/autonomicns.htm) |
|                 | [LAC.PN.PSYM.SPG](BrainRegionLAC_PN_PSYM_SPG.md) | Sphenopalatine Ganglion | eye-tears-gland | (unknown reference) |
|                 | [LAC.PN.SYM.SCG](BrainRegionLAC_PN_SYM_SCG.md) | Superior Cervical Ganglion | eye-muscle-curvature-sympathetic | [Sympathetic and parasympathetic eye pathways (SCG -> EYE)](http://www.nature.com/pr/journal/v71/n3/fig_tab/pr201138f1.html) |
| [LPC](BrainAreaLPC.md) | [LPC.HP.ABD](BrainRegionLPC_HP_ABD.md) | Abducens Nucleus | eye-muscle-rotate-vestibular | [Eye blink reflex and pupillary light reflex (Abducens -> EYE)](http://neuroscience.uth.tmc.edu/s3/chapter07.html) |
|                 | [LPC.HP.FCM](BrainRegionLPC_HP_FCM.md) | Facial Motor Nucleus | eye-muscle-close-conscious-lacrimal | (unknown reference) |
|                 | [LPC.MM.OCN](BrainRegionLPC_MM_OCN.md) | Oculomotor Nucleus | eye-muscle-rotate-major-inferior-oblique | [Eye blink reflex and pupillary light reflex (Oculomotor -> EYE)](http://neuroscience.uth.tmc.edu/s3/chapter07.html) |
|                 | [LPC.MM.TRH](BrainRegionLPC_MM_TRH.md) | Trochlear Nucleus | eye-muscle-rotate-minor | [Extraocular eye muscles (TRC -> EYE)](http://what-when-how.com/neuroscience/the-cranial-nerves-organization-of-the-central-nervous-system-part-4) |

**Outbound Region Connections:**

| **Target Area** | **Target Region** | **Target Name** | **Type** | **Reference** |
|:----------------|:------------------|:----------------|:---------|:--------------|
| [LPC](BrainAreaLPC.md) | [LPC.FD.RT](BrainRegionLPC_FD_RT.md) | Retina          | eye-edge-output | [Vision Components (EYE -> RT)](http://neuroscience.uth.tmc.edu/s3/chapter07.html) |
|                 | [LPC.MM.MSTR](BrainRegionLPC_MM_MSTR.md) | Mesencephalic Trigeminal Nucleus | eye-visceral | (unknown reference) |
|                 | [LPC.PN.SG.TRG](BrainRegionLPC_PN_SG_TRG.md) | Trigeminal Ganglion | eye-lacrimal-gland-conjunctiva-receptors | (unknown reference) |

# Thirdparty Circuits #
(generated)

  * [Extraocular eye muscles](http://what-when-how.com/wp-content/uploads/2012/04/tmp15F38_thumb.jpg) - see [Reference](http://what-when-how.com/neuroscience/the-cranial-nerves-organization-of-the-central-nervous-system-part-4)

<img src='http://what-when-how.com/wp-content/uploads/2012/04/tmp15F38_thumb.jpg' alt='unavailable' height='400width=400'>

<ul><li><a href='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/vision-subcortical.jpg'>Vision Components</a> - see <a href='http://neuroscience.uth.tmc.edu/s3/chapter07.html'>Reference</a></li></ul>

<img src='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/vision-subcortical.jpg' alt='unavailable'>

<ul><li><a href='http://www.dartmouth.edu/~rswenson/NeuroSci/figures/Figure_16_files/image002.jpg'>Trigeminal Nuclei</a> - see <a href='http://www.lookfordiagnosis.com/mesh_info.php?term=Trigeminal+Nucleilang=1'>Reference</a></li></ul>

<img src='http://www.dartmouth.edu/~rswenson/NeuroSci/figures/Figure_16_files/image002.jpg' alt='unavailable'>

<ul><li><a href='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/oculomotor.jpg'>Eye blink reflex and pupillary light reflex</a> - see <a href='http://neuroscience.uth.tmc.edu/s3/chapter07.html'>Reference</a></li></ul>

<img src='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/oculomotor.jpg' alt='unavailable'>

<ul><li><a href='http://www.nature.com/pr/journal/v71/n3/images/pr201138f1.gif'>Sympathetic and parasympathetic eye pathways</a> - see <a href='http://www.nature.com/pr/journal/v71/n3/fig_tab/pr201138f1.html'>Reference</a></li></ul>

<img src='http://www.nature.com/pr/journal/v71/n3/images/pr201138f1.gif' alt='unavailable' height='400width=400'>

<ul><li><a href='http://www.neurophysiology.ws/images/fig-4.gif'>Autonomic nervous system</a> - see <a href='http://www.neurophysiology.ws/autonomicns.htm'>Reference</a></li></ul>

<img src='http://www.neurophysiology.ws/images/fig-4.gif' alt='unavailable'>


<h1>References</h1>
(generated)<br>
<br>
<ul><li><a href='http://what-when-how.com/neuroscience/the-cranial-nerves-organization-of-the-central-nervous-system-part-4'>http://what-when-how.com/neuroscience/the-cranial-nerves-organization-of-the-central-nervous-system-part-4</a>
</li><li><a href='http://neuroscience.uth.tmc.edu/s3/chapter07.html'>http://neuroscience.uth.tmc.edu/s3/chapter07.html</a>
</li><li><a href='http://www.lookfordiagnosis.com/mesh_info.php?term=Trigeminal+Nucleilang=1'>http://www.lookfordiagnosis.com/mesh_info.php?term=Trigeminal+Nucleilang=1</a>
</li><li><a href='http://www.nature.com/pr/journal/v71/n3/fig_tab/pr201138f1.html'>http://www.nature.com/pr/journal/v71/n3/fig_tab/pr201138f1.html</a>
</li><li><a href='http://www.neurophysiology.ws/autonomicns.htm'>http://www.neurophysiology.ws/autonomicns.htm</a></li></ul>
