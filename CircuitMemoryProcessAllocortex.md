@@[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [CircuitMemoryProcessAllocortex](CircuitMemoryProcessAllocortex.md)

---


This page covers components and connections of circuit Memory Process in Allocortex.
Circuit is part of aHuman target integrated biological model.

(generated)
# Components #
(generated)

| **Mind Area** | **Component ID** | **Component Name** | **Type** | **Function** |
|:--------------|:-----------------|:-------------------|:---------|:-------------|
| [AMA](BrainAreaAMA.md) | [BFA.FT.SEP](BrainRegionBFA_FT_SEP.md) | Septal Nucleus     | nucleus  | Inhibition of fear and expression of pleasurable responses |
| [ECA](BrainAreaECA.md) | [BGA.FD.TH.CM](BrainRegionBGA_FD_TH_CM.md) | Centromedian Nucleus of Thalamus | nucleus  | Control of level of cortical activity |
|               | [BGA.FT.ACC](BrainRegionBGA_FT_ACC.md) | Accumbens Nucleus  | nucleus  | Activate motor functions under attention |
| [EPA](BrainAreaEPA.md) | [CGA.FD.TH.AN](BrainRegionCGA_FD_TH_AN.md) | Anterior Nucleus of Thalamus | nucleus  | Extended hippocampal system |
|               | [CGA.FD.TH.LD](BrainRegionCGA_FD_TH_LD.md) | Lateral Dorsal Nucleus of Thalamus | nucleus  | Head direction, spatial learning |
|               | [CGA.NC.MPL.PCG](BrainRegionCGA_NC_MPL_PCG.md) | Posterior Cingulate Cortex | cortex, BA 23,31 | Self-awareness, pain and episodic memory retrieval |
|               | [CGA.NC.MPL.RSC](BrainRegionCGA_NC_MPL_RSC.md) | Retrosplenial Cortex | cortex, BA 26,29,30 | Processing of emotionally salient stimuli |
| [MCA](BrainAreaMCA.md) | [FBA.MM.VTA](BrainRegionFBA_MM_VTA.md) | Ventral Tegmental Area | nucleus  | Respond to novel stimuli, unexpected rewards, and reward predictive sensory cues |
| [MMA](BrainAreaMMA.md) | [HBA.FD.TH.RE](BrainRegionHBA_FD_TH_RE.md) | Reuniens Nucleus of Thalamus | nucleus  | Gate information between OMPFC and HC dependent upon attentive/arousal states |
|               | [HBA.FD.TH.RH](BrainRegionHBA_FD_TH_RH.md) | Rhomboidal Nucleus of Thalamus | nucleus  | Communication of information across memory delays to guide memory responses |
|               | [HBA.FT.DG](BrainRegionHBA_FT_DG.md) | Dentate Gyrus      | cortex   | Distinguishing multiple instances of similar events |
|               | [HBA.FT.HC.CA1](BrainRegionHBA_FT_HC_CA1.md) | Ventrolateral Cornu Ammonis of Hippocampus | cortex   | Representing sequences of episodic memory - long-term |
|               | [HBA.FT.HC.CA2](BrainRegionHBA_FT_HC_CA2.md) | Dorsolateral Cornu Ammonis of Hippocampus | cortex   | Gate controlled by the activity of the supramammillary nucleus to control signal propagation between HC lamines |
|               | [HBA.FT.HC.CA3](BrainRegionHBA_FT_HC_CA3.md) | Dorsomedial Cornu Ammonis of Hippocampus | cortex   | Representing sequences of episodic memory - short-term |
|               | [HBA.FT.HC.CA4](BrainRegionHBA_FT_HC_CA4.md) | Ventromedial Cornu Ammonis of Hippocampus | cortex   | Mediate dynamic regulation of pattern separation in the dentate gyrus |
|               | [HBA.FT.SC.SUB](BrainRegionHBA_FT_SC_SUB.md) | Subiculum          | cortex   | Spatial navigation and mnemonic processing |
|               | [PHA.NC.PAS](BrainRegionPHA_NC_PAS.md) | Parasubiculum      | cortex, BA 49 | Spatial navigation and the integration of head-directional information |
|               | [PHA.NC.PH.ET](BrainRegionPHA_NC_PH_ET.md) | Enthorhinal Cortex | cortex, BA 28 | Memory consolidation |
|               | [PHA.NC.PH.TFTH](BrainRegionPHA_NC_PH_TFTH.md) | Posterior Parahippocampal Gyrus | cortex, BA 99 | Spatial declarative memory |
|               | [PHA.NC.PRS](BrainRegionPHA_NC_PRS.md) | Presubiculum       | cortex, BA 27 | Path integration, head direction |
|               | [PHA.NC.PSS](BrainRegionPHA_NC_PSS.md) | Postsubiculum      | cortex, BA 48 | Visual association |
| [SAA](BrainAreaSAA.md) | [VCA.NC.IPL.MST](BrainRegionVCA_NC_IPL_MST.md) | Medial Superior Temporal Area | cortex, BA 39 | Image stabilization, predictive target tracking |

# Connections #
(generated)

![http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitMemoryProcessAllocortex.dot.jpg](http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitMemoryProcessAllocortex.dot.jpg)

| **Source Region** | **Target Region** | **Type** | **Reference** |
|:------------------|:------------------|:---------|:--------------|
| [BGA.FD.TH.CM](BrainRegionBGA_FD_TH_CM.md) | [HBA.FT.HC.CA1](BrainRegionHBA_FT_HC_CA1.md) | nucleus-allocortex | [Contributions of Diencephalon to Recognition Memory (CM -> HC, abstract)](http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html) |
|                   | [HBA.FT.SC.SUB](BrainRegionHBA_FT_SC_SUB.md) | nucleus-allocortex | [Contributions of Diencephalon to Recognition Memory (CM -> SubPrePara)](http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html) |
| [CGA.FD.TH.AN](BrainRegionCGA_FD_TH_AN.md) | [HBA.FT.HC.CA1](BrainRegionHBA_FT_HC_CA1.md) | nucleus-allocortex | [Contributions of Diencephalon to Recognition Memory (AN -> HC, abstract)](http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html) |
|                   | [HBA.FT.SC.SUB](BrainRegionHBA_FT_SC_SUB.md) | nucleus-allocortex | [Contributions of Diencephalon to Recognition Memory (AN -> SubPrePara)](http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html) |
| [CGA.FD.TH.LD](BrainRegionCGA_FD_TH_LD.md) | [HBA.FT.HC.CA1](BrainRegionHBA_FT_HC_CA1.md) | nucleus-allocortex | [Contributions of Diencephalon to Recognition Memory (LD -> HC, abstract)](http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html) |
|                   | [HBA.FT.SC.SUB](BrainRegionHBA_FT_SC_SUB.md) | nucleus-allocortex | [Contributions of Diencephalon to Recognition Memory (LD -> SubPrePara)](http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html) |
| [CGA.NC.MPL.PCG](BrainRegionCGA_NC_MPL_PCG.md) | [HBA.FT.HC.CA1](BrainRegionHBA_FT_HC_CA1.md) | neocortex-allocortex | [Feeling (CG -> HC, abstract)](http://www.nature.com/nrn/journal/v5/n7) |
| [CGA.NC.MPL.RSC](BrainRegionCGA_NC_MPL_RSC.md) | [HBA.FT.HC.CA3](BrainRegionHBA_FT_HC_CA3.md) | neocortex-allocortex | [Contribution of hippocampal region CA3 to consciousness (Retrosplenial -> CA1)](http://www.sciencedirect.com/science/article/pii/S0149763409002061) |
| [FBA.MM.VTA](BrainRegionFBA_MM_VTA.md) | [HBA.FT.HC.CA1](BrainRegionHBA_FT_HC_CA1.md) | nucleus-allocortex | [Combining Novelty, Motivational Salience, and Reward to Control Attention and Learning (VTA -> CA1)](http://www.impulsecontroldisorders.org/html/cravings.html) |
| [HBA.FD.TH.RE](BrainRegionHBA_FD_TH_RE.md) | [HBA.FT.HC.CA1](BrainRegionHBA_FT_HC_CA1.md) | nucleus-allocortex | [Contributions of Diencephalon to Recognition Memory (MID -> HC, abstract)](http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html) |
|                   | [HBA.FT.SC.SUB](BrainRegionHBA_FT_SC_SUB.md) | nucleus-allocortex | [Contributions of Diencephalon to Recognition Memory (MID -> SubPrePara, abstract)](http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html) |
| [HBA.FD.TH.RH](BrainRegionHBA_FD_TH_RH.md) | [HBA.FT.HC.CA1](BrainRegionHBA_FT_HC_CA1.md) | nucleus-allocortex | [Contributions of Diencephalon to Recognition Memory (MID -> HC, abstract)](http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html) |
|                   | [HBA.FT.SC.SUB](BrainRegionHBA_FT_SC_SUB.md) | nucleus-allocortex | [Contributions of Diencephalon to Recognition Memory (MID -> SubPrePara, abstract)](http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html) |
| [HBA.FT.DG](BrainRegionHBA_FT_DG.md) | [HBA.FT.HC.CA3](BrainRegionHBA_FT_HC_CA3.md) | allocortex-allocortex | [Attractor Network in Hippocampus (DG -> CA3)](http://learnmem.cshlp.org/content/14/11/714/F1.expansion) |
|                   | [HBA.FT.HC.CA4](BrainRegionHBA_FT_HC_CA4.md) | allocortex-allocortex | (unknown reference) |
| [HBA.FT.HC.CA1](BrainRegionHBA_FT_HC_CA1.md) | [BFA.FT.SEP](BrainRegionBFA_FT_SEP.md) | allocortex-nucleus | [Attractor Network in Hippocampus (CA1 -> SEP)](http://learnmem.cshlp.org/content/14/11/714/F1.expansion) |
|                   | [BGA.FT.ACC](BrainRegionBGA_FT_ACC.md) | allocortex-nucleus | [Nucleus Accumbens (CA1 -> NACC)](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/nucleus-accumbens.jpg) |
|                   | [HBA.FT.SC.SUB](BrainRegionHBA_FT_SC_SUB.md) | allocortex-allocortex | [Attractor Network in Hippocampus (CA1 -> SUB)](http://learnmem.cshlp.org/content/14/11/714/F1.expansion) |
|                   | [PHA.NC.PAS](BrainRegionPHA_NC_PAS.md) | allocortex-neocortex | (unknown reference) |
|                   | [PHA.NC.PH.ET](BrainRegionPHA_NC_PH_ET.md) | allocortex-neocortex | [Hippocampal Formation (CA1 -> EC)](http://ahuman.googlecode.com/svn/research/articles/2009-Hippocampus-Thesis.pdf) |
|                   | [PHA.NC.PH.TFTH](BrainRegionPHA_NC_PH_TFTH.md) | allocortex-neocortex | [Entorhinal Cortex Inputs and Outputs (CA1 -> TFTH)](http://www.sciencedirect.com/science/article/pii/S0149763411001722) |
| [HBA.FT.HC.CA2](BrainRegionHBA_FT_HC_CA2.md) | [HBA.FT.HC.CA1](BrainRegionHBA_FT_HC_CA1.md) | allocortex-allocortex | [Flow of impulses in hippocampal region (CA2 -> CA1)](http://www.sciencedirect.com/science/article/pii/S030645220600755X) |
| [HBA.FT.HC.CA3](BrainRegionHBA_FT_HC_CA3.md) | [BFA.FT.SEP](BrainRegionBFA_FT_SEP.md) | allocortex-nucleus | [Principal Connections of Hippocampus (HC -> SEP)](http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.html) |
|                   | [BGA.FT.ACC](BrainRegionBGA_FT_ACC.md) | allocortex-nucleus | [Nucleus Accumbens (CA3 -> NACC)](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/nucleus-accumbens.jpg) |
|                   | [CGA.FD.TH.AN](BrainRegionCGA_FD_TH_AN.md) | allocortex-nucleus | [Principal Connections of Hippocampus (HC -> AN)](http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.html) |
|                   | [HBA.FT.HC.CA1](BrainRegionHBA_FT_HC_CA1.md) | allocortex-allocortex | [Attractor Network in Hippocampus (CA3 -> CA1)](http://learnmem.cshlp.org/content/14/11/714/F1.expansion) |
|                   | [HBA.FT.HC.CA2](BrainRegionHBA_FT_HC_CA2.md) | allocortex-allocortex | [KIV model of cortico-hippocampal formation with subcortical projections for motor actions (CA3 -> CA2)](http://www.sciencedirect.com/science/article/pii/S1571064507000243) |
|                   | [HBA.FT.HC.CA4](BrainRegionHBA_FT_HC_CA4.md) | allocortex-allocortex | (unknown reference) |
| [HBA.FT.HC.CA4](BrainRegionHBA_FT_HC_CA4.md) | [HBA.FT.DG](BrainRegionHBA_FT_DG.md) | allocortex-allocortex | (unknown reference) |
| [HBA.FT.SC.SUB](BrainRegionHBA_FT_SC_SUB.md) | [BGA.FT.ACC](BrainRegionBGA_FT_ACC.md) | allocortex-nucleus | [Nucleus Accumbens (SUB -> NACC)](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/nucleus-accumbens.jpg) |
|                   | [CGA.FD.TH.AN](BrainRegionCGA_FD_TH_AN.md) | allocortex-nucleus | [Thalamocortical relationships (s1A -> A)](http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/) |
|                   | [CGA.FD.TH.LD](BrainRegionCGA_FD_TH_LD.md) | allocortex-nucleus | [Contributions of Diencephalon to Recognition Memory (Sub -> LD)](http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html) |
|                   | [CGA.NC.MPL.RSC](BrainRegionCGA_NC_MPL_RSC.md) | allocortex-neocortex | [McNaughton Spatial Processing Network (SUB -> PCGRSP, abstract)](http://www.nature.com/nrn/journal/v3/n2/fig_tab/nrn726_F3.html) |
|                   | [HBA.FD.TH.RE](BrainRegionHBA_FD_TH_RE.md) | allocortex-nucleus | [Contributions of Diencephalon to Recognition Memory (Sub -> MID, abstract)](http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html) |
|                   | [PHA.NC.PH.ET](BrainRegionPHA_NC_PH_ET.md) | allocortex-neocortex | [Attractor Network in Hippocampus (SUB -> EC)](http://learnmem.cshlp.org/content/14/11/714/F1.expansion) |
|                   | [PHA.NC.PRS](BrainRegionPHA_NC_PRS.md) | allocortex-neocortex | [Attractor Network in Hippocampus (SUB -> PRESUB)](http://learnmem.cshlp.org/content/14/11/714/F1.expansion) |
|                   | [PHA.NC.PSS](BrainRegionPHA_NC_PSS.md) | allocortex-neocortex | [Hippocampal Formation (Sub -> PoS)](http://ahuman.googlecode.com/svn/research/articles/2009-Hippocampus-Thesis.pdf) |
| [PHA.NC.PH.ET](BrainRegionPHA_NC_PH_ET.md) | [HBA.FT.DG](BrainRegionHBA_FT_DG.md) | neocortex-allocortex | [Attractor Network in Hippocampus (EC -> DG)](http://learnmem.cshlp.org/content/14/11/714/F1.expansion) |
|                   | [HBA.FT.HC.CA1](BrainRegionHBA_FT_HC_CA1.md) | neocortex-allocortex | [Combining Novelty, Motivational Salience, and Reward to Control Attention and Learning (EC -> CA1)](http://www.impulsecontroldisorders.org/html/cravings.html) |
|                   | [HBA.FT.HC.CA2](BrainRegionHBA_FT_HC_CA2.md) | neocortex-allocortex | [Flow of impulses in hippocampal region (ENT -> CA2)](http://www.sciencedirect.com/science/article/pii/S030645220600755X) |
|                   | [HBA.FT.HC.CA3](BrainRegionHBA_FT_HC_CA3.md) | neocortex-allocortex | [Hippocampal Formation (EC -> CA3)](http://ahuman.googlecode.com/svn/research/articles/2009-Hippocampus-Thesis.pdf) |
|                   | [HBA.FT.SC.SUB](BrainRegionHBA_FT_SC_SUB.md) | neocortex-allocortex | [Simplified model of hippocampal formation anatomy (EC -> SUB)](http://www.sciencedirect.com/science/article/pii/S030100820900183X) |
| [VCA.NC.IPL.MST](BrainRegionVCA_NC_IPL_MST.md) | [HBA.FT.HC.CA3](BrainRegionHBA_FT_HC_CA3.md) | neocortex-allocortex | [Contribution of hippocampal region CA3 to consciousness (IPL -> CA1, abstract)](http://www.sciencedirect.com/science/article/pii/S0149763409002061) |
