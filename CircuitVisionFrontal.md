@@[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [CircuitVisionFrontal](CircuitVisionFrontal.md)

---


This page covers components and connections of circuit Vision Frontal Networks.
Circuit is part of aHuman target integrated biological model.

(generated)
# Components #
(generated)

| **Mind Area** | **Component ID** | **Component Name** | **Type** | **Function** |
|:--------------|:-----------------|:-------------------|:---------|:-------------|
| [ECA](BrainAreaECA.md) | [BGA.FT.CN](BrainRegionBGA_FT_CN.md) | Caudate Nucleus    | nucleus  | Excitation of correct action schemas and selection of appropriate sub-goals based on evaluation of action-outcomes |
| [EPA](BrainAreaEPA.md) | [CGA.NC.MPL.PCG](BrainRegionCGA_NC_MPL_PCG.md) | Posterior Cingulate Cortex | cortex, BA 23,31 | Self-awareness, pain and episodic memory retrieval |
|               | [FCA.FD.TH.MD](BrainRegionFCA_FD_TH_MD.md) | Mediodorsal Nucleus of Thalamus | nucleus  | Attention, planning, organization, abstract thinking, multi-tasking, and active memory |
|               | [FCA.NC.LPFC](BrainRegionFCA_NC_LPFC.md) | Dorsolateral Prefrontal Cortex | cortex, BA 09,46 | Temporal Integration |
| [MRA](BrainAreaMRA.md) | [HMA.HP.PRF.GCR](BrainRegionHMA_HP_PRF_GCR.md) | Gigantocellular Reticular Nucleus | nucleus  | Mediate head movements |
|               | [HMA.HP.PRF.RPO](BrainRegionHMA_HP_PRF_RPO.md) | Oral Pontine Reticular Nucleus | nucleus  | Mediation of changing to and from REM sleep |
|               | [HMA.MM.CJ](BrainRegionHMA_MM_CJ.md) | Cajal Nucleus      | nucleus  | Integration of head and eye movements, controls downward vertical gaze |
|               | [MBA.MM.SC.DEEP](BrainRegionMBA_MM_SC_DEEP.md) | Deep Superior Colliculus | nucleus  | Head and eye attention to non-visual stimuli |
| [MAA](BrainAreaMAA.md) | [MCA.NC.MC](BrainRegionMCA_NC_MC.md) | Motor Cortex       | cortex, BA 04 | Execution of required voluntary movements |
|               | [MCA.NC.PMC.F2](BrainRegionMCA_NC_PMC_F2.md) | Dorsal Caudal Premotor Cortex | cortex, BA 06 | Guiding reaching |
|               | [MCA.NC.PMC.F4](BrainRegionMCA_NC_PMC_F4.md) | Ventral Caudal Premotor Cortex | cortex, BA 06 | Sensory guidance of movement |
|               | [MCA.NC.PMC.F5](BrainRegionMCA_NC_PMC_F5.md) | Ventral Rostral Premotor Cortex | cortex, BA 06 | Shaping hand during grasping |
|               | [MCA.NC.PMC.FEF](BrainRegionMCA_NC_PMC_FEF.md) | Frontal Eye Field  | cortex, BA 08 | Initiation of eye movements |
|               | [MCA.NC.SMC](BrainRegionMCA_NC_SMC.md) | Supplementary Motor Cortex | cortex, BA 06 | Process sequences of movements and coordinate bilateral movements |
| [BAA](BrainAreaBAA.md) | [SMA.NC.SPL.PG](BrainRegionSMA_NC_SPL_PG.md) | Caudal Precuneus   | cortex, BA 07 | Controlling spatially guided behavior with respect to visual and tactile information |
| [SAA](BrainAreaSAA.md) | [VCA.NC.IPL.MST](BrainRegionVCA_NC_IPL_MST.md) | Medial Superior Temporal Area | cortex, BA 39 | Image stabilization, predictive target tracking |
|               | [VCA.NC.IPS.PEF](BrainRegionVCA_NC_IPS_PEF.md) | Posterior Eye Field | cortex, BA 39 | Reflexive saccade triggering |
|               | [VCA.NC.IT.TE](BrainRegionVCA_NC_IT_TE.md) | Inferotemporal Cortex | cortex, BA 20 | Represent different views of objects |

# Connections #
(generated)

![http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitVisionFrontal.dot.jpg](http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitVisionFrontal.dot.jpg)

| **Source Region** | **Target Region** | **Type** | **Reference** |
|:------------------|:------------------|:---------|:--------------|
| [FCA.FD.TH.MD](BrainRegionFCA_FD_TH_MD.md) | [MCA.NC.PMC.FEF](BrainRegionMCA_NC_PMC_FEF.md) | nucleus-neocortex | [Oculomotor decision-making (Thalamus -> FEF, abstract)](http://www.springerimages.com/Images/LifeSciences/1-10.1007_s00359-004-0565-9-0) |
| [FCA.NC.LPFC](BrainRegionFCA_NC_LPFC.md) | [MCA.NC.PMC.F5](BrainRegionMCA_NC_PMC_F5.md) | neocortex-neocortex | [Prefrontal Cortex (PFC) in motor behavior (LPFC -> PMC, abstract)](https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988) |
|                   | [MCA.NC.PMC.FEF](BrainRegionMCA_NC_PMC_FEF.md) | neocortex-neocortex | [Summary of eye movement control (DLPFC -> FEF)](http://www.cixip.com/index.php/page/content/id/1190) |
|                   | [MCA.NC.SMC](BrainRegionMCA_NC_SMC.md) | neocortex-neocortex | [Primate Control of Grasping (46 -> F6)](http://www.sciencedirect.com/science/article/pii/S0893608098000471) |
| [MCA.NC.PMC.F2](BrainRegionMCA_NC_PMC_F2.md) | [MCA.NC.MC](BrainRegionMCA_NC_MC.md) | neocortex-neocortex | [Prefrontal Cortex (PFC) in motor behavior (PMC -> MC, abstract)](https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988) |
| [MCA.NC.PMC.F5](BrainRegionMCA_NC_PMC_F5.md) | [MCA.NC.MC](BrainRegionMCA_NC_MC.md) | neocortex-neocortex | [Primate Control of Grasping (F5 -> F1)](http://www.sciencedirect.com/science/article/pii/S0893608098000471) |
| [MCA.NC.PMC.FEF](BrainRegionMCA_NC_PMC_FEF.md) | [BGA.FT.CN](BrainRegionBGA_FT_CN.md) | neocortex-nucleus | [Oculomotor decision-making (FEF -> Caudate)](http://www.springerimages.com/Images/LifeSciences/1-10.1007_s00359-004-0565-9-0) |
|                   | [HMA.HP.PRF.GCR](BrainRegionHMA_HP_PRF_GCR.md) | neocortex-nucleus | (unknown reference) |
|                   | [HMA.HP.PRF.RPO](BrainRegionHMA_HP_PRF_RPO.md) | neocortex-nucleus | [Saccades and smooth movements (FEF -> DLPN)](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/saccades.jpg) |
|                   | [HMA.MM.CJ](BrainRegionHMA_MM_CJ.md) | neocortex-nucleus | [Summary of eye movement control (FEF -> riMLF)](http://www.cixip.com/index.php/page/content/id/1190) |
|                   | [MBA.MM.SC.DEEP](BrainRegionMBA_MM_SC_DEEP.md) | neocortex-nucleus | [Summary of eye movement control (FEF -> SC, abstract)](http://www.cixip.com/index.php/page/content/id/1190) |
| [MCA.NC.SMC](BrainRegionMCA_NC_SMC.md) | [MCA.NC.PMC.F2](BrainRegionMCA_NC_PMC_F2.md) | neocortex-neocortex | [3 Visual Cortex Paths (pre-SMA -> dPM, abstract)](http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf) |
|                   | [MCA.NC.PMC.F5](BrainRegionMCA_NC_PMC_F5.md) | neocortex-neocortex | [Primate Control of Grasping (F6 -> F5)](http://www.sciencedirect.com/science/article/pii/S0893608098000471) |
|                   | [MCA.NC.PMC.FEF](BrainRegionMCA_NC_PMC_FEF.md) | neocortex-neocortex | [Summary of eye movement control (SEF -> FEF)](http://www.cixip.com/index.php/page/content/id/1190) |
| [SMA.NC.SPL.PG](BrainRegionSMA_NC_SPL_PG.md) | [MCA.NC.PMC.F2](BrainRegionMCA_NC_PMC_F2.md) | neocortex-neocortex | [3 Visual Cortex Paths (SPL -> dPM, abstract)](http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf) |
| [VCA.NC.IPL.MST](BrainRegionVCA_NC_IPL_MST.md) | [FCA.NC.LPFC](BrainRegionFCA_NC_LPFC.md) | neocortex-neocortex | [Cortico-Cortical Connectivity (PTHA -> PFC, abstract)](http://www.sciencedirect.com/science/article/pii/S1053810011000080) |
|                   | [MCA.NC.PMC.F4](BrainRegionMCA_NC_PMC_F4.md) | neocortex-neocortex | [3 Visual Cortex Paths (IPL -> vPM, abstract)](http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf) |
| [VCA.NC.IPS.PEF](BrainRegionVCA_NC_IPS_PEF.md) | [CGA.NC.MPL.PCG](BrainRegionCGA_NC_MPL_PCG.md) | neocortex-neocortex | [Oculomotor decision-making (LIP -> CGp)](http://www.springerimages.com/Images/LifeSciences/1-10.1007_s00359-004-0565-9-0) |
|                   | [FCA.NC.LPFC](BrainRegionFCA_NC_LPFC.md) | neocortex-neocortex | [Summary of eye movement control (PEF -> DLPFC)](http://www.cixip.com/index.php/page/content/id/1190) |
|                   | [MCA.NC.PMC.FEF](BrainRegionMCA_NC_PMC_FEF.md) | neocortex-neocortex | [Summary of eye movement control (PEF -> FEF)](http://www.cixip.com/index.php/page/content/id/1190) |
| [VCA.NC.IT.TE](BrainRegionVCA_NC_IT_TE.md) | [MCA.NC.PMC.FEF](BrainRegionMCA_NC_PMC_FEF.md) | neocortex-neocortex | [Saccades and smooth movements (TEF -> FEF, abstract)](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/saccades.jpg) |
