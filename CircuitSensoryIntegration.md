@@[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [CircuitSensoryIntegration](CircuitSensoryIntegration.md)

---


This page covers components and connections of circuit Multisensory Integration for Hippocampus.
Circuit is part of aHuman target integrated biological model.

(generated)
# Components #
(generated)

| **Mind Area** | **Component ID** | **Component Name** | **Type** | **Function** |
|:--------------|:-----------------|:-------------------|:---------|:-------------|
| [EPA](BrainAreaEPA.md) | [CGA.NC.MPL.PCG](BrainRegionCGA_NC_MPL_PCG.md) | Posterior Cingulate Cortex | cortex, BA 23,31 | Self-awareness, pain and episodic memory retrieval |
|               | [CGA.NC.MPL.RSC](BrainRegionCGA_NC_MPL_RSC.md) | Retrosplenial Cortex | cortex, BA 26,29,30 | Processing of emotionally salient stimuli |
| [MMA](BrainAreaMMA.md) | [PHA.NC.PH.ET](BrainRegionPHA_NC_PH_ET.md) | Enthorhinal Cortex | cortex, BA 28 | Memory consolidation |
|               | [PHA.NC.PH.PRR](BrainRegionPHA_NC_PH_PRR.md) | Perirhinal Cortex  | cortex, BA 35 | Associate different visual views of objects and their various nonvisual attributes |
| [SAA](BrainAreaSAA.md) | [VCA.NC.IT.TE](BrainRegionVCA_NC_IT_TE.md) | Inferotemporal Cortex | cortex, BA 20 | Represent different views of objects |

# Connections #
(generated)

![http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitSensoryIntegration.dot.jpg](http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitSensoryIntegration.dot.jpg)

| **Source Region** | **Target Region** | **Type** | **Reference** |
|:------------------|:------------------|:---------|:--------------|
| [CGA.NC.MPL.PCG](BrainRegionCGA_NC_MPL_PCG.md) | [PHA.NC.PH.ET](BrainRegionPHA_NC_PH_ET.md) | neocortex-neocortex | [Cingulate Gyrus (CG -> ET)](http://www.thebrainlabs.com) |
| [CGA.NC.MPL.RSC](BrainRegionCGA_NC_MPL_RSC.md) | [PHA.NC.PH.ET](BrainRegionPHA_NC_PH_ET.md) | neocortex-neocortex | [McNaughton Spatial Processing Network (PCGRSP -> EnthCortex, abstract)](http://www.nature.com/nrn/journal/v3/n2/fig_tab/nrn726_F3.html) |
| [PHA.NC.PH.PRR](BrainRegionPHA_NC_PH_PRR.md) | [PHA.NC.PH.ET](BrainRegionPHA_NC_PH_ET.md) | neocortex-neocortex | [Visual Path to Hippocampus (PRPH -> ER)](http://www.scholarpedia.org/article/Inferior_temporal_cortex) |
| [VCA.NC.IT.TE](BrainRegionVCA_NC_IT_TE.md) | [PHA.NC.PH.PRR](BrainRegionPHA_NC_PH_PRR.md) | neocortex-neocortex | [Visual Path to Hippocampus (IT -> PRPH)](http://www.scholarpedia.org/article/Inferior_temporal_cortex) |
