@@[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [BrainAreaTSA](BrainAreaTSA.md) -> [BrainRegionTARGET\_TSA\_NOSE](BrainRegionTARGET_TSA_NOSE.md)

---


This page covers biological details of component Nose.
Region is part of aHuman target integrated biological model.

  * **Top-down path to region**: Target -> Human Sensors (aHumanSensors) -> Nose (TARGET.TSA.NOSE) (see [Mind Maps](OverallMindMaps.md))
  * **Type**: sensor
  * **Brain area**: [Sensor Area](BrainAreaTSA.md)
  * **Role**: unknown
  * **Function**: Olfaction Sensor
(generated)
# Components #
(generated)


**Component items**:
  * **Nose sensory data** (**nose-sensory-data**)
    * Nose - volatile (nose-volatile -> [LPC.PN.SG.MOE](BrainRegionLPC_PN_SG_MOE.md)): Sensing smells - volatile odorants
    * Nose - nonvolatile (nose-nonvolatile -> [LPC.PN.SG.VNO](BrainRegionLPC_PN_SG_VNO.md)): Sensing smells - non-volatile pheromones
    * Nose - proprioceptors (nose-proprioceptors -> [LPC.MM.MSTR](BrainRegionLPC_MM_MSTR.md)): proprioception
    * Nose - touch receptors (nose-somatic -> [LPC.PN.SG.TRG](BrainRegionLPC_PN_SG_TRG.md)): touch
    * Nose - visceral nodose receptors (nose-visceral-vagus -> [LPC.PN.SG.NOD](BrainRegionLPC_PN_SG_NOD.md)): visceral sensations
    * Nose - visceral pharynx receptors (nose-visceral-pharynx -> [LPC.PN.SG.PET](BrainRegionLPC_PN_SG_PET.md)): visceral sensations
  * **Ear sensory control** (**nose-sensory-control**)
    * [Nose - nasal glands](http://en.wikipedia.org/wiki/Nasal_glands) ([LAC.PN.PSYM.SPG](BrainRegionLAC_PN_PSYM_SPG.md) -> [nose-nasal-glands](HumanMusclesHead.md)): smelling control and moisturing
  * **Nose move muscles** (**nose-muscles**): constricts nostrils, lower alar pars and helps to wrinkle nose
    * [Nose - depressor septi nasi muscle](http://en.wikipedia.org/wiki/Depressor_septi_nasi_muscle) ([LPC.HP.FCM](BrainRegionLPC_HP_FCM.md) -> [nose-depressor-septi-nasi](HumanMusclesHead.md)): depression of nasal septum
    * [Nose - levator labii superioris alaeque nasi muscle](http://en.wikipedia.org/wiki/Levator_labii_superioris_alaeque_nasi_muscle) ([LPC.HP.FCM](BrainRegionLPC_HP_FCM.md) -> [nose-levator-labii-superioris-alaeque-nasi](HumanMusclesHead.md)): dilates the nostril; elevates the upper lip and wing of the nose
    * [Nose - nasalis muscle](http://en.wikipedia.org/wiki/Nasalis_muscle) ([LPC.HP.FCM](BrainRegionLPC_HP_FCM.md) -> [nose-nasalis](HumanMusclesHead.md)): compresses bridge, depresses tip of nose, elevates corners of nostrils
    * [Nose - salpingopharyngeus muscle](http://en.wikipedia.org/wiki/Salpingopharyngeus_muscle) ([LPC.HM.AMB](BrainRegionLPC_HM_AMB.md) -> [nose-salpingopharyngeus](HumanMusclesNeck.md)): raise the nasopharynx

# Connectivity #
(generated)


![http://ahuman.googlecode.com/svn/images/dot/aHuman/TARGET.TSA.NOSE.dot.png](http://ahuman.googlecode.com/svn/images/dot/aHuman/TARGET.TSA.NOSE.dot.png)

**Inbound Region Connections:**

| **Source Area** | **Source Region** | **Source Name** | **Type** | **Reference** |
|:----------------|:------------------|:----------------|:---------|:--------------|
| [LAC](BrainAreaLAC.md) | [LAC.PN.PSYM.SPG](BrainRegionLAC_PN_PSYM_SPG.md) | Sphenopalatine Ganglion | nose-nasal-glands | (unknown reference) |
| [LPC](BrainAreaLPC.md) | [LPC.HM.AMB](BrainRegionLPC_HM_AMB.md) | Ambiguus Nucleus | nose-salpingopharyngeus | (unknown reference) |
|                 | [LPC.HP.FCM](BrainRegionLPC_HP_FCM.md) | Facial Motor Nucleus | nose-depressor-septi-nasi | (unknown reference) |

**Outbound Region Connections:**

| **Target Area** | **Target Region** | **Target Name** | **Type** | **Reference** |
|:----------------|:------------------|:----------------|:---------|:--------------|
| [LPC](BrainAreaLPC.md) | [LPC.MM.MSTR](BrainRegionLPC_MM_MSTR.md) | Mesencephalic Trigeminal Nucleus | nose-proprioceptors | (unknown reference) |
|                 | [LPC.PN.SG.MOE](BrainRegionLPC_PN_SG_MOE.md) | Main Olfactory Epithelium | nose-volatile | (unknown reference) |
|                 | [LPC.PN.SG.NOD](BrainRegionLPC_PN_SG_NOD.md) | Nodose Ganglion | nose-visceral-vagus | (unknown reference) |
|                 | [LPC.PN.SG.PET](BrainRegionLPC_PN_SG_PET.md) | Petrosal Ganglion | nose-visceral-pharynx | (unknown reference) |
|                 | [LPC.PN.SG.TRG](BrainRegionLPC_PN_SG_TRG.md) | Trigeminal Ganglion | nose-somatic | (unknown reference) |
|                 | [LPC.PN.SG.VNO](BrainRegionLPC_PN_SG_VNO.md) | Vomeronasal Organ | nose-nonvolatile | (unknown reference) |

# Thirdparty Circuits #
(generated)

  * no circuits defined

# References #
(generated)

  * no references defined
