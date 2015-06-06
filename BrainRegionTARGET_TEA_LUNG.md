@@[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [BrainAreaTEA](BrainAreaTEA.md) -> [BrainRegionTARGET\_TEA\_LUNG](BrainRegionTARGET_TEA_LUNG.md)

---


This page covers biological details of component Lung.
Region is part of aHuman target integrated biological model.

  * **Top-down path to region**: Target -> Human Effectors (aHumanEffectors) -> Lung (TARGET.TEA.LUNG) (see [Mind Maps](OverallMindMaps.md))
  * **Type**: effector
  * **Brain area**: [Effector Area](BrainAreaTEA.md)
  * **Role**: unknown
  * **Function**: Oxigen Supply
(generated)
# Components #
(generated)


**Component items**:
  * **Lung sensory data** (**lung-sensory-data**)
    * Lung - pulmonary neuroepithelial bodies (pulmonary-neuroepithelial-bodies -> [LPC.PN.SG.NOD](BrainRegionLPC_PN_SG_NOD.md)): trachea, bronchial tree and lungs - intraepithelial receptors
    * Lung - pericardium and pleura receptors (pericardium-pleura-receptors -> [LPC.PN.SG.UDRG](BrainRegionLPC_PN_SG_UDRG.md)): somatic sensations
    * Lung - pulmonary stretch receptors (pulmonary-stretch-receptors -> [LPC.PN.SG.JUG](BrainRegionLPC_PN_SG_JUG.md)): imitate the Hering-Breuer reflex, which reduces the respiratory rate; increased firing from the stretch receptors also increases production of pulmonary surfactant
  * **Lung visceral activity** (**lung-visceral-activity**)
    * [Lung - glands of trachea, lungs, and bronchi](http://education.yahoo.com/reference/gray/subjects/subject/237) ([LAC.PN.PSYM.PUG](BrainRegionLAC_PN_PSYM_PUG.md) -> [visceral-glands](HumanMusclesTorso.md)): increase in airway secretions
    * [Lung - smooth muscles of trachea and bronchial tree](http://en.wikipedia.org/wiki/Bronchus) ([LAC.PN.PSYM.PUG](BrainRegionLAC_PN_PSYM_PUG.md) -> [smooth-muscles](HumanMusclesTorso.md)): constriction of trachea and bronchioles
  * **Lung breath muscles** (**lung-breath-muscles**)
    * [Lung - thoracic diaphragm](http://en.wikipedia.org/wiki/Semispinalis_dorsi) ([LPC.SC.VH.PHR](BrainRegionLPC_SC_VH_PHR.md) -> [thoracic-diaphragm](HumanMusclesTorso.md)): increases thoracic cavity volume; inhalation
    * [Lung - stylopharyngeus muscle](http://en.wikipedia.org/wiki/Stylopharyngeus_muscle) ([LPC.HM.AMB](BrainRegionLPC_HM_AMB.md) -> [stylopharyngeus-muscle](HumanMusclesNeck.md)): elevate the larynx, elevate the pharynx, swallowing

# Connectivity #
(generated)


![http://ahuman.googlecode.com/svn/images/dot/aHuman/TARGET.TEA.LUNG.dot.png](http://ahuman.googlecode.com/svn/images/dot/aHuman/TARGET.TEA.LUNG.dot.png)

**Inbound Region Connections:**

| **Source Area** | **Source Region** | **Source Name** | **Type** | **Reference** |
|:----------------|:------------------|:----------------|:---------|:--------------|
| [LAC](BrainAreaLAC.md) | [LAC.PN.PSYM.PUG](BrainRegionLAC_PN_PSYM_PUG.md) | Pulmonary Peripheral Ganglion | smooth-muscles | (unknown reference) |
| [LPC](BrainAreaLPC.md) | [LPC.HM.AMB](BrainRegionLPC_HM_AMB.md) | Ambiguus Nucleus | stylopharyngeus-muscle | (unknown reference) |
|                 | [LPC.SC.VH.PHR](BrainRegionLPC_SC_VH_PHR.md) | Phrenic Nucleus | thoracic-diaphragm | (unknown reference) |

**Outbound Region Connections:**

| **Target Area** | **Target Region** | **Target Name** | **Type** | **Reference** |
|:----------------|:------------------|:----------------|:---------|:--------------|
| [LPC](BrainAreaLPC.md) | [LPC.PN.SG.JUG](BrainRegionLPC_PN_SG_JUG.md) | Jugular Ganglion | pulmonary-stretch-receptors | (unknown reference) |
|                 | [LPC.PN.SG.NOD](BrainRegionLPC_PN_SG_NOD.md) | Nodose Ganglion | pulmonary-neuroepithelial-bodies | (unknown reference) |
|                 | [LPC.PN.SG.UDRG](BrainRegionLPC_PN_SG_UDRG.md) | Upper Dorsal Root Ganglion | pericardium-pleura-receptors | (unknown reference) |

# Thirdparty Circuits #
(generated)

  * no circuits defined

# References #
(generated)

  * no references defined
