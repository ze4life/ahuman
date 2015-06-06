@@[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [BrainAreaTSA](BrainAreaTSA.md) -> [BrainRegionTARGET\_TSA\_EAR](BrainRegionTARGET_TSA_EAR.md)

---


This page covers biological details of component Ear.
Region is part of aHuman target integrated biological model.

  * **Top-down path to region**: Target -> Human Sensors (aHumanSensors) -> Ear (TARGET.TSA.EAR) (see [Mind Maps](OverallMindMaps.md))
  * **Type**: sensor
  * **Brain area**: [Sensor Area](BrainAreaTSA.md)
  * **Role**: unknown
  * **Function**: Auditory and Vestibular Sensor
(generated)
# Components #
(generated)


**Component items**:
  * **Ear sound sensory data** (**ear-sensory-sound-data**)
    * Ear - inner hair cells (ear-inner-hair-cells -> [LPC.PN.SG.SP](BrainRegionLPC_PN_SG_SP.md)): frequency-aligned tonotopic mapping
    * Ear - outer hair cells feedback (ear-outer-hair-cells-feedback -> [LPC.PN.SG.SP](BrainRegionLPC_PN_SG_SP.md)): verifies amplify actions done
    * Ear - somatic receptors (ear-somatic -> [LPC.PN.SG.GNG](BrainRegionLPC_PN_SG_GNG.md)): from skin to geniculate ganglion to spinal trigeminal nucleus
    * Ear - outer ear skin (ear-external-skin -> [LPC.PN.SG.UDRG](BrainRegionLPC_PN_SG_UDRG.md)): skin over the mastoid process, back of the auricle, lobule and a portion of the scalp
    * Ear - acoustic meatus skin (ear-acoustic-meatus-skin -> [LPC.PN.SG.TRG](BrainRegionLPC_PN_SG_TRG.md)): from skin lining external acoustic meatus, and tympanic membrane to trigeminal gangion
    * Ear - visceral receptors (ear-visceral -> [LPC.PN.SG.JUG](BrainRegionLPC_PN_SG_JUG.md)): pain, temperature, and touch
    * Ear - timpanic cavity (ear-timpanic-cavity -> [LPC.PN.SG.PET](BrainRegionLPC_PN_SG_PET.md)): pain, temperature, and touch
  * **Ear vestibular sensory data** (**ear-sensory-vestibular-data**)
    * Ear - semicircular canals, cristae (ear-semicircular-canals -> [LPC.PN.SG.CVB](BrainRegionLPC_PN_SG_CVB.md)): activate afferent receptors in response to rotational acceleration
    * Ear - utricle, maculae (ear-utricle -> [LPC.PN.SG.UVB](BrainRegionLPC_PN_SG_UVB.md)): activate afferent receptors in response to horizontal linear acceleration
    * Ear - saccule, maculae (ear-saccule -> [LPC.PN.SG.SVB](BrainRegionLPC_PN_SG_SVB.md)): activate afferent receptors in response to vertical linear acceleration
  * **Ear sound sensory control** (**ear-sensory-control**)
    * [Ear - outer hair cells](http://www.d.umn.edu/~jfitzake/Lectures/UndergradPharmacy/SensoryPhysiology/Audition/OHCFunction.html) ([LPC.MM.SOC](BrainRegionLPC_MM_SOC.md) -> [ear-outer-hair-cells](HumanMusclesHead.md)): contracts basilar membrane; mechanically amplify low-level sound that enters cochlea
    * [Ear - stapedius muscle](http://en.wikipedia.org/wiki/Stapedius) ([LPC.HP.FCM](BrainRegionLPC_HP_FCM.md) -> [ear-stapedius](HumanMusclesHead.md)): dampens vibrations of stapes
    * [Ear - tympanic membrane muscle](http://en.wikipedia.org/wiki/Tensor_tympani) ([LPC.HP.PTP.TRM](BrainRegionLPC_HP_PTP_TRM.md) -> [ear-tensor-tympani-muscle](HumanMusclesHead.md)): dampen sounds, such as those produced from chewing
  * **Ear move muscles** (**ear-move**)
    * [Ear - anterior auricular muscle](http://en.wikipedia.org/wiki/Anterior_auricular_muscle) ([LPC.HP.FCM](BrainRegionLPC_HP_FCM.md) -> [ear-anterior-auricular-muscle](HumanMusclesHead.md)): pulls ear forward
    * [Ear - posterior auricular muscle](http://en.wikipedia.org/wiki/Posterior_auricular_muscle) ([LPC.HP.FCM](BrainRegionLPC_HP_FCM.md) -> [ear-posterior-auricular-muscle](HumanMusclesHead.md)): pulls ear backward
    * [Ear - superior auricular muscle](http://en.wikipedia.org/wiki/Superior_auricular_muscle) ([LPC.HP.FCM](BrainRegionLPC_HP_FCM.md) -> [ear-superior-auricular-muscle](HumanMusclesHead.md)): pulls ear upward
    * [Ear - oblique muscle of auricle](http://en.wikipedia.org/wiki/Oblique_muscle_of_auricle) ([LPC.HP.FCM](BrainRegionLPC_HP_FCM.md) -> [ear-oblique-auricular-muscle](HumanMusclesHead.md)): movement of the ears
    * [Ear - temporoparietalis muscle](http://en.wikipedia.org/wiki/Temporoparietalis_muscle) ([LPC.HP.FCM](BrainRegionLPC_HP_FCM.md) -> [ear-temporoparietalis-muscle](HumanMusclesHead.md)): assist the frontal belly in drawing the epicranial aponeurosis towards the front of the cranium

# Connectivity #
(generated)


![http://ahuman.googlecode.com/svn/images/dot/aHuman/TARGET.TSA.EAR.dot.png](http://ahuman.googlecode.com/svn/images/dot/aHuman/TARGET.TSA.EAR.dot.png)

**Inbound Region Connections:**

| **Source Area** | **Source Region** | **Source Name** | **Type** | **Reference** |
|:----------------|:------------------|:----------------|:---------|:--------------|
| [LPC](BrainAreaLPC.md) | [LPC.HP.FCM](BrainRegionLPC_HP_FCM.md) | Facial Motor Nucleus | ear-anterior-auricular-muscle | (unknown reference) |
|                 | [LPC.HP.PTP.TRM](BrainRegionLPC_HP_PTP_TRM.md) | Trigeminal Motor Nucleus | ear-tensor-tympani-muscle | (unknown reference) |
|                 | [LPC.MM.SOC](BrainRegionLPC_MM_SOC.md) | Superior Olivary Complex | ear-outer-hair-cells | [Five Parallel Auditory Pathways (VNTB -> Cochlea)](http://lifeboat.com/ex/law.of.accelerating.returns) |

**Outbound Region Connections:**

| **Target Area** | **Target Region** | **Target Name** | **Type** | **Reference** |
|:----------------|:------------------|:----------------|:---------|:--------------|
| [LPC](BrainAreaLPC.md) | [LPC.PN.SG.CVB](BrainRegionLPC_PN_SG_CVB.md) | Vestibular Ganglion - Semicircular Canal Neurons | ear-semicircular-canals | (unknown reference) |
|                 | [LPC.PN.SG.GNG](BrainRegionLPC_PN_SG_GNG.md) | Geniculate Ganglion | ear-somatic | (unknown reference) |
|                 | [LPC.PN.SG.JUG](BrainRegionLPC_PN_SG_JUG.md) | Jugular Ganglion | ear-visceral | (unknown reference) |
|                 | [LPC.PN.SG.PET](BrainRegionLPC_PN_SG_PET.md) | Petrosal Ganglion | ear-timpanic-cavity | (unknown reference) |
|                 | [LPC.PN.SG.SP](BrainRegionLPC_PN_SG_SP.md) | Spiral Ganglion | ear-inner-hair-cells | [Auditory System Model (Ear -> CochleaGanglion)](http://www.sciencedirect.com/science/article/pii/S1359644605035427) |
|                 | [LPC.PN.SG.SVB](BrainRegionLPC_PN_SG_SVB.md) | Vestibular Ganglion - Saccule Neurons | ear-saccule | (unknown reference) |
|                 | [LPC.PN.SG.TRG](BrainRegionLPC_PN_SG_TRG.md) | Trigeminal Ganglion | ear-acoustic-meatus-skin | (unknown reference) |
|                 | [LPC.PN.SG.UDRG](BrainRegionLPC_PN_SG_UDRG.md) | Upper Dorsal Root Ganglion | ear-external-skin | (unknown reference) |
|                 | [LPC.PN.SG.UVB](BrainRegionLPC_PN_SG_UVB.md) | Vestibular Ganglion - Utricle Neurons | ear-utricle | (unknown reference) |

# Thirdparty Circuits #
(generated)

  * [Five Parallel Auditory Pathways](http://lifeboat.com/kurzweil/cochlea.gif) - see [Reference](http://lifeboat.com/ex/law.of.accelerating.returns)

<img src='http://lifeboat.com/kurzweil/cochlea.gif' alt='unavailable'>

<ul><li><a href='http://ars.sciencedirect.com/content/image/1-s2.0-S1359644605035427-gr1.jpg'>Auditory System Model</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S1359644605035427'>Reference</a></li></ul>

<img src='http://ars.sciencedirect.com/content/image/1-s2.0-S1359644605035427-gr1.jpg' alt='unavailable'>

<ul><li><a href='http://www.benbest.com/science/anatmind/FigVI1.gif'>Auditory System in Brain</a> - see <a href='http://www.benbest.com/science/anatmind/anatmd6.html'>Reference</a></li></ul>

<img src='http://www.benbest.com/science/anatmind/FigVI1.gif' alt='unavailable'>


<h1>References</h1>
(generated)<br>
<br>
<ul><li><a href='http://lifeboat.com/ex/law.of.accelerating.returns'>http://lifeboat.com/ex/law.of.accelerating.returns</a>
</li><li><a href='http://www.sciencedirect.com/science/article/pii/S1359644605035427'>http://www.sciencedirect.com/science/article/pii/S1359644605035427</a>
</li><li><a href='http://www.benbest.com/science/anatmind/anatmd6.html'>http://www.benbest.com/science/anatmind/anatmd6.html</a></li></ul>
