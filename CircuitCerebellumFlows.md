@@[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [CircuitCerebellumFlows](CircuitCerebellumFlows.md)

---


This page covers components and connections of circuit Cerebellum Flows.
Circuit is part of aHuman target integrated biological model.

(generated)
# Components #
(generated)

| **Mind Area** | **Component ID** | **Component Name** | **Type** | **Function** |
|:--------------|:-----------------|:-------------------|:---------|:-------------|
| [PCA](BrainAreaPCA.md) | [BMA.HM.CU](BrainRegionBMA_HM_CU.md) | Cuneate Nucleus    | nucleus  | Carry fine touch and proprioceptive information from upper body |
| [LCA](BrainAreaLCA.md) | [BMA.HM.IO](BrainRegionBMA_HM_IO.md) | Inferior Olivary Nucleus | nucleus  | Proprioception Relay from Spinal Cord to Cerebellum |
| [MRA](BrainAreaMRA.md) | [BMA.HP.VB](BrainRegionBMA_HP_VB.md) | Vestibular Nucleus | nucleus  | Equilibrium, Postural Reflexes |
| [LCA](BrainAreaLCA.md) | [BMA.SC.IZ.CBS](BrainRegionBMA_SC_IZ_CBS.md) | Centrobasalis Nucleus | nucleus  | Unconscious proprioception to CR |
|               | [BMA.SC.LH.LCV](BrainRegionBMA_SC_LH_LCV.md) | Lateral Cervical Nucleus | nucleus  | Relay Low-threshold Mechanoreceptors to CR |
|               | [BMA.SC.PH.CL](BrainRegionBMA_SC_PH_CL.md) | Clarke Nucleus     | nucleus  | Unconscious Proprioception |
| [EPA](BrainAreaEPA.md) | [CGA.NC.VACG](BrainRegionCGA_NC_VACG.md) | Ventral Anterior Cingulate Area | cortex, BA 24 | Seat of Free Will |
| [MRA](BrainAreaMRA.md) | [HMA.HP.PRF.CRF](BrainRegionHMA_HP_PRF_CRF.md) | Caudal Pontine Reticular Nucleus | nucleus  | Mediate head movements |
|               | [HMA.HP.PRF.RPO](BrainRegionHMA_HP_PRF_RPO.md) | Oral Pontine Reticular Nucleus | nucleus  | Mediation of changing to and from REM sleep |
| [LCA](BrainAreaLCA.md) | [MBA.HP.CR](BrainRegionMBA_HP_CR.md) | Cerebellum         | nucleus  | Motor coordination |
|               | [MBA.HP.PN.RP](BrainRegionMBA_HP_PN_RP.md) | Rostral Pontine Nucleus | nucleus  | Part of learning, motivation, spatial memory pathway |
|               | [MBA.MM.RD](BrainRegionMBA_MM_RD.md) | Red Nucleus        | nucleus  | Motor coordination |
| [MRA](BrainAreaMRA.md) | [MBA.MM.SC.DEEP](BrainRegionMBA_MM_SC_DEEP.md) | Deep Superior Colliculus | nucleus  | Head and eye attention to non-visual stimuli |
| [MAA](BrainAreaMAA.md) | [MCA.FD.TH.VL](BrainRegionMCA_FD_TH_VL.md) | Ventral Lateral Nucleus | nucleus  | Relay BSA.CR to MCA.MC |
|               | [MCA.NC.MC](BrainRegionMCA_NC_MC.md) | Motor Cortex       | cortex, BA 04 | Execution of required voluntary movements |
|               | [MCA.NC.SMC](BrainRegionMCA_NC_SMC.md) | Supplementary Motor Cortex | cortex, BA 06 | Process sequences of movements and coordinate bilateral movements |

# Connections #
(generated)

![http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitCerebellumFlows.dot.jpg](http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitCerebellumFlows.dot.jpg)

| **Source Region** | **Target Region** | **Type** | **Reference** |
|:------------------|:------------------|:---------|:--------------|
| [BMA.HM.CU](BrainRegionBMA_HM_CU.md) | [MBA.HP.CR](BrainRegionMBA_HP_CR.md) | nucleus-nucleus | (unknown reference) |
| [BMA.HM.IO](BrainRegionBMA_HM_IO.md) | [MBA.HP.CR](BrainRegionMBA_HP_CR.md) | nucleus-nucleus | (unknown reference) |
| [BMA.HP.VB](BrainRegionBMA_HP_VB.md) | [MBA.HP.CR](BrainRegionMBA_HP_CR.md) | nucleus-nucleus | (unknown reference) |
| [BMA.SC.IZ.CBS](BrainRegionBMA_SC_IZ_CBS.md) | [MBA.HP.CR](BrainRegionMBA_HP_CR.md) | nucleus-nucleus | (unknown reference) |
| [BMA.SC.LH.LCV](BrainRegionBMA_SC_LH_LCV.md) | [MBA.HP.CR](BrainRegionMBA_HP_CR.md) | nucleus-nucleus | (unknown reference) |
| [BMA.SC.PH.CL](BrainRegionBMA_SC_PH_CL.md) | [MBA.HP.CR](BrainRegionMBA_HP_CR.md) | nucleus-nucleus | (unknown reference) |
| [CGA.NC.VACG](BrainRegionCGA_NC_VACG.md) | [MBA.MM.RD](BrainRegionMBA_MM_RD.md) | neocortex-nucleus | (unknown reference) |
| [HMA.HP.PRF.RPO](BrainRegionHMA_HP_PRF_RPO.md) | [MBA.HP.CR](BrainRegionMBA_HP_CR.md) | nucleus-nucleus | [Saccades and smooth movements (DLPN -> CR)](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/saccades.jpg) |
| [MBA.HP.CR](BrainRegionMBA_HP_CR.md) | [BMA.HP.VB](BrainRegionBMA_HP_VB.md) | nucleus-nucleus | [Saccades and smooth movements (CR -> Vestibular)](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/saccades.jpg) |
|                   | [HMA.HP.PRF.CRF](BrainRegionHMA_HP_PRF_CRF.md) | nucleus-nucleus | [Saccadic Vision (CR -> RF, abstract)](http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html) |
|                   | [MBA.MM.RD](BrainRegionMBA_MM_RD.md) | nucleus-nucleus | (unknown reference) |
|                   | [MCA.FD.TH.VL](BrainRegionMCA_FD_TH_VL.md) | nucleus-nucleus | [Thalamocortical relationships (s1VL -> VL)](http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/) |
| [MBA.HP.PN.RP](BrainRegionMBA_HP_PN_RP.md) | [MBA.HP.CR](BrainRegionMBA_HP_CR.md) | nucleus-nucleus | [Prefrontal Cortex (PFC) in motor behavior (PN -> CR, abstract)](https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988) |
| [MBA.MM.RD](BrainRegionMBA_MM_RD.md) | [BMA.HM.IO](BrainRegionBMA_HM_IO.md) | nucleus-nucleus | (unknown reference) |
| [MBA.MM.SC.DEEP](BrainRegionMBA_MM_SC_DEEP.md) | [MBA.HP.CR](BrainRegionMBA_HP_CR.md) | nucleus-nucleus | [Saccadic Vision (SCi -> CR, abstract)](http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html) |
| [MCA.FD.TH.VL](BrainRegionMCA_FD_TH_VL.md) | [MCA.NC.MC](BrainRegionMCA_NC_MC.md) | nucleus-neocortex | [Thalamocortical relationships (VL -> pVL)](http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/) |
|                   | [MCA.NC.SMC](BrainRegionMCA_NC_SMC.md) | nucleus-neocortex | [Basal Ganglia Activity (VLo -> SMC)](http://thebrain.mcgill.ca/flash/a/a_06/a_06_cr/a_06_cr_mou/a_06_cr_mou.html) |
