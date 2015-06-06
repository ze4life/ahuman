@@[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [CircuitSleepWakeCycle](CircuitSleepWakeCycle.md)

---


This page covers components and connections of circuit Sleep-Wake Cycle.
Circuit is part of aHuman target integrated biological model.

(generated)
# Components #
(generated)

| **Mind Area** | **Component ID** | **Component Name** | **Type** | **Function** |
|:--------------|:-----------------|:-------------------|:---------|:-------------|
| [PCA](BrainAreaPCA.md) | [HMA.HM.SOL](BrainRegionHMA_HM_SOL.md) | Solitary Nucleus   | nucleus  | Carry taste buds, thoracic and abdominal viscera |
| [ACA](BrainAreaACA.md) | [HTA.FD.HT.AR](BrainRegionHTA_FD_HT_AR.md) | Arcuate Nucleus of Hypothalamus | nucleus  | Regulation of growth, appetite and body weight |
|               | [HTA.FD.HT.PV](BrainRegionHTA_FD_HT_PV.md) | Paraventricular Nucleus | nucleus  | Regulate appetite and autonomic functions |
|               | [HTA.FD.HT.SCN](BrainRegionHTA_FD_HT_SCN.md) | Suprachiasmatic Nucleus | nucleus  | 24-hour rhythms |
| [PCA](BrainAreaPCA.md) | [VBA.FD.RT](BrainRegionVBA_FD_RT.md) | Retina             | nucleus  | Spatial decorrelation through center surround inhibition |

# Connections #
(generated)

![http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitSleepWakeCycle.dot.jpg](http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitSleepWakeCycle.dot.jpg)

| **Source Region** | **Target Region** | **Type** | **Reference** |
|:------------------|:------------------|:---------|:--------------|
| [HMA.HM.SOL](BrainRegionHMA_HM_SOL.md) | [HTA.FD.HT.PV](BrainRegionHTA_FD_HT_PV.md) | nucleus-nucleus | (unknown reference) |
| [HTA.FD.HT.AR](BrainRegionHTA_FD_HT_AR.md) | [HTA.FD.HT.PV](BrainRegionHTA_FD_HT_PV.md) | nucleus-nucleus | (unknown reference) |
| [HTA.FD.HT.SCN](BrainRegionHTA_FD_HT_SCN.md) | [HTA.FD.HT.PV](BrainRegionHTA_FD_HT_PV.md) | nucleus-nucleus | (unknown reference) |
| [VBA.FD.RT](BrainRegionVBA_FD_RT.md) | [HTA.FD.HT.SCN](BrainRegionHTA_FD_HT_SCN.md) | nucleus-nucleus | [Targets of retina neurons (Retina -> HT, abstract)](http://www.rci.rutgers.edu/~uzwiak/AnatPhys/Vision.htm) |
