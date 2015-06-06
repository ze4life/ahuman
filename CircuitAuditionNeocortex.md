@@[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [CircuitAuditionNeocortex](CircuitAuditionNeocortex.md)

---


This page covers components and connections of circuit Audition Perception in Neocortex.
Circuit is part of aHuman target integrated biological model.

(generated)
# Components #
(generated)

| **Mind Area** | **Component ID** | **Component Name** | **Type** | **Function** |
|:--------------|:-----------------|:-------------------|:---------|:-------------|
| [SAA](BrainAreaSAA.md) | [ACA.NC.A1](BrainRegionACA_NC_A1.md) | Primary Auditory Cortex | cortex, BA 41 | Main topotonic map, extract phonemes |
|               | [ACA.NC.A2](BrainRegionACA_NC_A2.md) | Auditory Association Area | cortex, BA 42 | Classify with respect to function |
|               | [ACA.NC.A3](BrainRegionACA_NC_A3.md) | Wernicke's area A3 | cortex, BA 22 | Classify with respect to content |
|               | [ACA.NC.A4](BrainRegionACA_NC_A4.md) | Wernicke's area A4 | cortex, BA 22 | Coordinate the activation or deactivation of grammar areas |
|               | [ACA.NC.BRA](BrainRegionACA_NC_BRA.md) | Broca's Area       | cortex, BA 44,45 | Speech Engine |
|               | [ACA.NC.IPL.SMW](BrainRegionACA_NC_IPL_SMW.md) | Supramarginal Wernike Cortex | cortex, BA 40 | Phonological and articulatory processing of words |
|               | [ACA.NC.PRI](BrainRegionACA_NC_PRI.md) | Parainsular Area   | cortex, BA 52 | Medial auditory stream |
| [EPA](BrainAreaEPA.md) | [CGA.NC.DACG](BrainRegionCGA_NC_DACG.md) | Dorsal Anterior Cingulate Area | cortex, BA 32 | Rational Thought Processes |
|               | [FCA.NC.IPG](BrainRegionFCA_NC_IPG.md) | Inferior Prefrontal Gyrus | cortex, BA 47 | Processing of syntax in oral and sign languages |
| [MAA](BrainAreaMAA.md) | [MCA.NC.PMC.F2](BrainRegionMCA_NC_PMC_F2.md) | Dorsal Caudal Premotor Cortex | cortex, BA 06 | Guiding reaching |
|               | [MCA.NC.PMC.F4](BrainRegionMCA_NC_PMC_F4.md) | Ventral Caudal Premotor Cortex | cortex, BA 06 | Sensory guidance of movement |
|               | [MCA.NC.PMC.F5](BrainRegionMCA_NC_PMC_F5.md) | Ventral Rostral Premotor Cortex | cortex, BA 06 | Shaping hand during grasping |
|               | [MCA.NC.PMC.F7](BrainRegionMCA_NC_PMC_F7.md) | Dorsal Rostral Premotor Cortex | cortex, BA 06 | Associate arbitrary sensory stimuli with specific eye movements |
|               | [MCA.NC.PMC.FEF](BrainRegionMCA_NC_PMC_FEF.md) | Frontal Eye Field  | cortex, BA 08 | Initiation of eye movements |
| [MMA](BrainAreaMMA.md) | [PHA.NC.TPC](BrainRegionPHA_NC_TPC.md) | Temporopolar Cortex | cortex, BA 38 | Self representation, semantic (left) and autobiographic (right) |
| [SAA](BrainAreaSAA.md) | [VCA.NC.IT.TEO](BrainRegionVCA_NC_IT_TEO.md) | Preoccipital Inferotemporal Area | cortex, BA 21 | Represent different features of objects |
|               | [VCA.NC.MT](BrainRegionVCA_NC_MT.md) | Middle Temporal Area | cortex, BA 19 | Integration of local motion signals into global percepts |

# Connections #
(generated)

![http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitAuditionNeocortex.dot.jpg](http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitAuditionNeocortex.dot.jpg)

| **Source Region** | **Target Region** | **Type** | **Reference** |
|:------------------|:------------------|:---------|:--------------|
| [ACA.NC.A1](BrainRegionACA_NC_A1.md) | [ACA.NC.A2](BrainRegionACA_NC_A2.md) | neocortex-neocortex | [Cortical Auditory System (Core41 -> Belt42)](http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html) |
|                   | [ACA.NC.A3](BrainRegionACA_NC_A3.md) | neocortex-neocortex | [Cortico-Cortical Connectivity (A1 -> AA)](http://www.sciencedirect.com/science/article/pii/S1053810011000080) |
|                   | [ACA.NC.A4](BrainRegionACA_NC_A4.md) | neocortex-neocortex | [Vocal Control (A1 -> Wernike)](http://www.frontiersin.org/neuroanatomy/10.3389/fnana.2011.00034/full) |
|                   | [ACA.NC.IPL.SMW](BrainRegionACA_NC_IPL_SMW.md) | neocortex-neocortex | [Dual Auditory Processing (A1 -> PPC, abstract)](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC2846110/) |
|                   | [MCA.NC.PMC.F7](BrainRegionMCA_NC_PMC_F7.md) | neocortex-neocortex | [Dual Auditory Processing (A1 -> DLPFC, abstract)](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC2846110/) |
| [ACA.NC.A2](BrainRegionACA_NC_A2.md) | [ACA.NC.A4](BrainRegionACA_NC_A4.md) | neocortex-neocortex | [Cortical Auditory System (Belt42 -> AC22)](http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html) |
|                   | [CGA.NC.DACG](BrainRegionCGA_NC_DACG.md) | neocortex-neocortex | [Directed Effort Network (ACA -> dACC)](http://www.frontiersin.org/Human_Neuroscience/10.3389/fnhum.2012.00184/full) |
| [ACA.NC.A3](BrainRegionACA_NC_A3.md) | [ACA.NC.BRA](BrainRegionACA_NC_BRA.md) | neocortex-neocortex | [Cortical Auditory System (STS22 -> IFC45)](http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html) |
|                   | [ACA.NC.IPL.SMW](BrainRegionACA_NC_IPL_SMW.md) | neocortex-neocortex | [Cortico-Cortical Connectivity (AA -> PTHA, abstract)](http://www.sciencedirect.com/science/article/pii/S1053810011000080) |
|                   | [MCA.NC.PMC.F4](BrainRegionMCA_NC_PMC_F4.md) | neocortex-neocortex | [Dual Auditory Processing (ST -> VLPFC, abstract)](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC2846110/) |
|                   | [PHA.NC.TPC](BrainRegionPHA_NC_TPC.md) | neocortex-neocortex | [Language-Related Regions (STG22a -> TC)](http://www.sciencedirect.com/science/article/pii/S1364661312002823) |
| [ACA.NC.A4](BrainRegionACA_NC_A4.md) | [ACA.NC.A3](BrainRegionACA_NC_A3.md) | neocortex-neocortex | [Cortical Auditory System (AC22 -> STS22)](http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html) |
|                   | [ACA.NC.BRA](BrainRegionACA_NC_BRA.md) | neocortex-neocortex | [Language-Related Regions (pSTC -> BA44)](http://www.sciencedirect.com/science/article/pii/S1364661312002823) |
|                   | [ACA.NC.IPL.SMW](BrainRegionACA_NC_IPL_SMW.md) | neocortex-neocortex | [Cortical Auditory System (AC22 -> IPL40, abstract)](http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html) |
|                   | [MCA.NC.PMC.F4](BrainRegionMCA_NC_PMC_F4.md) | neocortex-neocortex | [Language-Related Regions (pSTC -> PMC, abstract)](http://www.sciencedirect.com/science/article/pii/S1364661312002823) |
| [ACA.NC.BRA](BrainRegionACA_NC_BRA.md) | [ACA.NC.IPL.SMW](BrainRegionACA_NC_IPL_SMW.md) | neocortex-neocortex | [Cortical Auditory System (IFC44 -> IPL40, abstract)](http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html) |
|                   | [MCA.NC.PMC.FEF](BrainRegionMCA_NC_PMC_FEF.md) | neocortex-neocortex | [Cortical Auditory System (IFC44 -> PMC8)](http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html) |
| [ACA.NC.IPL.SMW](BrainRegionACA_NC_IPL_SMW.md) | [MCA.NC.PMC.F2](BrainRegionMCA_NC_PMC_F2.md) | neocortex-neocortex | [Dual Auditory Processing (PPC -> DLPFC, abstract)](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC2846110/) |
|                   | [MCA.NC.PMC.F4](BrainRegionMCA_NC_PMC_F4.md) | neocortex-neocortex | [3 Visual Cortex Paths (IPL -> vPM, abstract)](http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf) |
| [ACA.NC.PRI](BrainRegionACA_NC_PRI.md) | [ACA.NC.IPL.SMW](BrainRegionACA_NC_IPL_SMW.md) | neocortex-neocortex | (unknown reference) |
| [MCA.NC.PMC.FEF](BrainRegionMCA_NC_PMC_FEF.md) | [MCA.NC.PMC.F5](BrainRegionMCA_NC_PMC_F5.md) | neocortex-neocortex | [Cortical Auditory System (PMC8 -> PMC6, abstract)](http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html) |
| [PHA.NC.TPC](BrainRegionPHA_NC_TPC.md) | [ACA.NC.BRA](BrainRegionACA_NC_BRA.md) | neocortex-neocortex | [Language-Related Regions (TC -> BA45)](http://www.sciencedirect.com/science/article/pii/S1364661312002823) |
|                   | [FCA.NC.IPG](BrainRegionFCA_NC_IPG.md) | neocortex-neocortex | [Language-Related Regions (TC -> vIFC)](http://www.sciencedirect.com/science/article/pii/S1364661312002823) |
| [VCA.NC.IT.TEO](BrainRegionVCA_NC_IT_TEO.md) | [PHA.NC.TPC](BrainRegionPHA_NC_TPC.md) | neocortex-neocortex | [Language-Related Regions (MTG21 -> TC)](http://www.sciencedirect.com/science/article/pii/S1364661312002823) |
| [VCA.NC.MT](BrainRegionVCA_NC_MT.md) | [ACA.NC.A4](BrainRegionACA_NC_A4.md) | neocortex-neocortex | [Category-Selectivity Paradigm (IOG -> STS, abstract)](http://www.sciencedirect.com/science/article/pii/S1053811905008013) |
