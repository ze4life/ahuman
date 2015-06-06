@@[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [CircuitMemoryMB](CircuitMemoryMB.md)

---


This page covers components and connections of circuit Memory Process in Mammillary Bodies.
Circuit is part of aHuman target integrated biological model.

(generated)
# Components #
(generated)

| **Mind Area** | **Component ID** | **Component Name** | **Type** | **Function** |
|:--------------|:-----------------|:-------------------|:---------|:-------------|
| [AMA](BrainAreaAMA.md) | [BFA.FT.SEP](BrainRegionBFA_FT_SEP.md) | Septal Nucleus     | nucleus  | Inhibition of fear and expression of pleasurable responses |
| [EPA](BrainAreaEPA.md) | [CGA.FD.TH.AN](BrainRegionCGA_FD_TH_AN.md) | Anterior Nucleus of Thalamus | nucleus  | Extended hippocampal system |
|               | [CGA.NC.MPL.RSC](BrainRegionCGA_NC_MPL_RSC.md) | Retrosplenial Cortex | cortex, BA 26,29,30 | Processing of emotionally salient stimuli |
| [MCA](BrainAreaMCA.md) | [FBA.MM.VTA](BrainRegionFBA_MM_VTA.md) | Ventral Tegmental Area | nucleus  | Respond to novel stimuli, unexpected rewards, and reward predictive sensory cues |
| [MMA](BrainAreaMMA.md) | [HBA.FD.MB.MMB](BrainRegionHBA_FD_MB_MMB.md) | Medial Mammillary Nucleus | nucleus  | Relay for impulses coming from AM and HC |
|               | [HBA.FT.DG](BrainRegionHBA_FT_DG.md) | Dentate Gyrus      | cortex   | Distinguishing multiple instances of similar events |
|               | [HBA.FT.HC.CA1](BrainRegionHBA_FT_HC_CA1.md) | Ventrolateral Cornu Ammonis of Hippocampus | cortex   | Representing sequences of episodic memory - long-term |
|               | [HBA.FT.HC.CA2](BrainRegionHBA_FT_HC_CA2.md) | Dorsolateral Cornu Ammonis of Hippocampus | cortex   | Gate controlled by the activity of the supramammillary nucleus to control signal propagation between HC lamines |
|               | [HBA.FT.HC.CA3](BrainRegionHBA_FT_HC_CA3.md) | Dorsomedial Cornu Ammonis of Hippocampus | cortex   | Representing sequences of episodic memory - short-term |
|               | [HBA.FT.SC.SUB](BrainRegionHBA_FT_SC_SUB.md) | Subiculum          | cortex   | Spatial navigation and mnemonic processing |
| [MRA](BrainAreaMRA.md) | [HMA.HP.PRF.PDT](BrainRegionHMA_HP_PRF_PDT.md) | Pontine Reticulotegmental Nucleus | nucleus  | Mediate saccadic eye movements |
| [ACA](BrainAreaACA.md) | [HTA.FD.HT.LT](BrainRegionHTA_FD_HT_LT.md) | Lateral Nucleus    | nucleus  | Thirst and hunger |
|               | [HTA.FD.HT.PN](BrainRegionHTA_FD_HT_PN.md) | Posterior Nucleus  | nucleus  | Blood pressure, pupillary dilation |
| [LCA](BrainAreaLCA.md) | [MBA.HP.PN.RP](BrainRegionMBA_HP_PN_RP.md) | Rostral Pontine Nucleus | nucleus  | Part of learning, motivation, spatial memory pathway |
| [MCA](BrainAreaMCA.md) | [MBA.MM.TG.LDT](BrainRegionMBA_MM_TG_LDT.md) | Laterodorsal Tegmental Nucleus | nucleus  | Modulating sustained attention or in mediating alerting responses |
| [MMA](BrainAreaMMA.md) | [PHA.FD.MB.LMB](BrainRegionPHA_FD_MB_LMB.md) | Lateral Mammillary Nucleus | nucleus  | Generate theta rythm and relay to HC |
|               | [PHA.NC.PAS](BrainRegionPHA_NC_PAS.md) | Parasubiculum      | cortex, BA 49 | Spatial navigation and the integration of head-directional information |
|               | [PHA.NC.PH.ET](BrainRegionPHA_NC_PH_ET.md) | Enthorhinal Cortex | cortex, BA 28 | Memory consolidation |
|               | [PHA.NC.PRS](BrainRegionPHA_NC_PRS.md) | Presubiculum       | cortex, BA 27 | Path integration, head direction |
|               | [PHA.NC.PSS](BrainRegionPHA_NC_PSS.md) | Postsubiculum      | cortex, BA 48 | Visual association |

# Connections #
(generated)

![http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitMemoryMB.dot.jpg](http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitMemoryMB.dot.jpg)

| **Source Region** | **Target Region** | **Type** | **Reference** |
|:------------------|:------------------|:---------|:--------------|
| [BFA.FT.SEP](BrainRegionBFA_FT_SEP.md) | [CGA.NC.MPL.RSC](BrainRegionCGA_NC_MPL_RSC.md) | nucleus-neocortex | [Medial mammillary nucleus and theta rhythm (SEP -> RSP)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html) |
|                   | [HBA.FD.MB.MMB](BrainRegionHBA_FD_MB_MMB.md) | nucleus-nucleus | [Mammillary bodies: two memory systems in one (SEP -> MMB)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html) |
|                   | [HBA.FT.HC.CA2](BrainRegionHBA_FT_HC_CA2.md) | nucleus-allocortex | [Medial mammillary nucleus and theta rhythm (SEP -> HF, abstract)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html) |
|                   | [PHA.FD.MB.LMB](BrainRegionPHA_FD_MB_LMB.md) | nucleus-nucleus | [Mammillary bodies: two memory systems in one (SEP -> LMB)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html) |
| [FBA.MM.VTA](BrainRegionFBA_MM_VTA.md) | [HBA.FD.MB.MMB](BrainRegionHBA_FD_MB_MMB.md) | nucleus-nucleus | [Mammillary bodies: two memory systems in one (VTN -> MMB)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html) |
| [HBA.FD.MB.MMB](BrainRegionHBA_FD_MB_MMB.md) | [CGA.FD.TH.AN](BrainRegionCGA_FD_TH_AN.md) | nucleus-nucleus | [Mammillary bodies: two memory systems in one (MMB -> AMTH)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html) |
|                   | [FBA.MM.VTA](BrainRegionFBA_MM_VTA.md) | nucleus-nucleus | [Medial mammillary nucleus and theta rhythm (MMB -> VTN)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html) |
|                   | [HMA.HP.PRF.PDT](BrainRegionHMA_HP_PRF_PDT.md) | nucleus-nucleus | [Mammillary Body (MMB -> RTG)](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/mb.jpg) |
|                   | [MBA.HP.PN.RP](BrainRegionMBA_HP_PN_RP.md) | nucleus-nucleus | (unknown reference) |
| [HBA.FT.HC.CA1](BrainRegionHBA_FT_HC_CA1.md) | [HBA.FD.MB.MMB](BrainRegionHBA_FD_MB_MMB.md) | allocortex-nucleus | [Hippocampus and Septal Area (CA1 -> MB)](http://neurondevelopment.org/hippocampal-development) |
| [HBA.FT.HC.CA3](BrainRegionHBA_FT_HC_CA3.md) | [HBA.FD.MB.MMB](BrainRegionHBA_FD_MB_MMB.md) | allocortex-nucleus | [Principal Connections of Hippocampus (HC -> MB)](http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.html) |
| [HBA.FT.SC.SUB](BrainRegionHBA_FT_SC_SUB.md) | [HBA.FD.MB.MMB](BrainRegionHBA_FD_MB_MMB.md) | allocortex-nucleus | [Mammillary bodies: two memory systems in one (SUB -> MMB)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html) |
| [HTA.FD.HT.LT](BrainRegionHTA_FD_HT_LT.md) | [HBA.FD.MB.MMB](BrainRegionHBA_FD_MB_MMB.md) | nucleus-nucleus | [Mammillary bodies: two memory systems in one (TuberoMM -> MMB)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html) |
|                   | [PHA.FD.MB.LMB](BrainRegionPHA_FD_MB_LMB.md) | nucleus-nucleus | [Mammillary bodies: two memory systems in one (TuberoMM -> LMB)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html) |
| [HTA.FD.HT.PN](BrainRegionHTA_FD_HT_PN.md) | [BFA.FT.SEP](BrainRegionBFA_FT_SEP.md) | nucleus-nucleus | [Medial mammillary nucleus and theta rhythm (SupraMM -> SEP)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html) |
|                   | [HBA.FD.MB.MMB](BrainRegionHBA_FD_MB_MMB.md) | nucleus-nucleus | [Mammillary bodies: two memory systems in one (SupraMM -> MMB)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html) |
|                   | [HBA.FT.DG](BrainRegionHBA_FT_DG.md) | nucleus-allocortex | [Medial mammillary nucleus and theta rhythm (SupraMM -> HF, abstract)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html) |
|                   | [HBA.FT.HC.CA3](BrainRegionHBA_FT_HC_CA3.md) | nucleus-allocortex | [Medial mammillary nucleus and theta rhythm (SupraMM -> HF, abstract)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html) |
|                   | [PHA.FD.MB.LMB](BrainRegionPHA_FD_MB_LMB.md) | nucleus-nucleus | [Mammillary bodies: two memory systems in one (SupraMM -> LMB)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html) |
| [MBA.MM.TG.LDT](BrainRegionMBA_MM_TG_LDT.md) | [PHA.FD.MB.LMB](BrainRegionPHA_FD_MB_LMB.md) | nucleus-nucleus | [Hippocampal Formation (DTN -> LMam)](http://ahuman.googlecode.com/svn/research/articles/2009-Hippocampus-Thesis.pdf) |
| [PHA.FD.MB.LMB](BrainRegionPHA_FD_MB_LMB.md) | [CGA.FD.TH.AN](BrainRegionCGA_FD_TH_AN.md) | nucleus-nucleus | [Head Direction Cell Circuit (LMB -> AD)](http://www.scholarpedia.org/article/Head_direction_cells) |
|                   | [HMA.HP.PRF.PDT](BrainRegionHMA_HP_PRF_PDT.md) | nucleus-nucleus | [Mammillary Body (LMB -> RTG)](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/mb.jpg) |
|                   | [MBA.MM.TG.LDT](BrainRegionMBA_MM_TG_LDT.md) | nucleus-nucleus | [Head Direction Cell Circuit (LMB -> DTN)](http://www.scholarpedia.org/article/Head_direction_cells) |
|                   | [PHA.NC.PRS](BrainRegionPHA_NC_PRS.md) | nucleus-neocortex | [Attractor Network in Hippocampus (MBOUT -> PRESUB)](http://learnmem.cshlp.org/content/14/11/714/F1.expansion) |
| [PHA.NC.PAS](BrainRegionPHA_NC_PAS.md) | [PHA.FD.MB.LMB](BrainRegionPHA_FD_MB_LMB.md) | neocortex-nucleus | [Mammillary bodies: two memory systems in one (PAS -> LMB)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html) |
| [PHA.NC.PH.ET](BrainRegionPHA_NC_PH_ET.md) | [HBA.FD.MB.MMB](BrainRegionHBA_FD_MB_MMB.md) | neocortex-nucleus | [Mammillary bodies: two memory systems in one (MedialEC -> MMB)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html) |
| [PHA.NC.PRS](BrainRegionPHA_NC_PRS.md) | [HBA.FD.MB.MMB](BrainRegionHBA_FD_MB_MMB.md) | neocortex-nucleus | [Attractor Network in Hippocampus (PRESUB -> MBIN)](http://learnmem.cshlp.org/content/14/11/714/F1.expansion) |
|                   | [PHA.FD.MB.LMB](BrainRegionPHA_FD_MB_LMB.md) | neocortex-nucleus | [Mammillary bodies: two memory systems in one (PRS -> LMB)](http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html) |
| [PHA.NC.PSS](BrainRegionPHA_NC_PSS.md) | [PHA.FD.MB.LMB](BrainRegionPHA_FD_MB_LMB.md) | neocortex-nucleus | [Head Direction Cell Circuit (PSUB -> LMB)](http://www.scholarpedia.org/article/Head_direction_cells) |
