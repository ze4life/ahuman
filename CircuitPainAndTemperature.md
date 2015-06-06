@@[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [CircuitPainAndTemperature](CircuitPainAndTemperature.md)

---


This page covers components and connections of circuit Pain and Temperature Perception.
Circuit is part of aHuman target integrated biological model.

(generated)
# Components #
(generated)

| **Mind Area** | **Component ID** | **Component Name** | **Type** | **Function** |
|:--------------|:-----------------|:-------------------|:---------|:-------------|
| [PCA](BrainAreaPCA.md) | [AVA.PN.SG.DRG](BrainRegionAVA_PN_SG_DRG.md) | Dorsal Root Ganglion | sensory ganglion | Integration of afferent signaling from viscera |
| [AMA](BrainAreaAMA.md) | [BFA.FT.AM](BrainRegionBFA_FT_AM.md) | Amygdala           | nucleus  | Experiencing and recognizing emotions |
| [ECA](BrainAreaECA.md) | [BGA.FT.ACC](BrainRegionBGA_FT_ACC.md) | Accumbens Nucleus  | nucleus  | Activate motor functions under attention |
|               | [BGA.FT.CN](BrainRegionBGA_FT_CN.md) | Caudate Nucleus    | nucleus  | Excitation of correct action schemas and selection of appropriate sub-goals based on evaluation of action-outcomes |
|               | [BGA.FT.PU](BrainRegionBGA_FT_PU.md) | Putamen            | nucleus  | Stimulus-response, or habit, learning |
|               | [BGA.FT.VP](BrainRegionBGA_FT_VP.md) | Ventral Pallidum   | nucleus  | Distinguish _wanting_ versus _liking_ enhancements |
| [PCA](BrainAreaPCA.md) | [BMA.SC.PH.MG](BrainRegionBMA_SC_PH_MG.md) | Marginal Nucleus   | nucleus  | Relay information related to pain and temperature sensation |
|               | [BMA.SC.VH.VL](BrainRegionBMA_SC_VH_VL.md) | Ventrolateral Nucleus | nucleus  | Innervation of limb muscles |
| [EPA](BrainAreaEPA.md) | [CGA.FD.TH.SM](BrainRegionCGA_FD_TH_SM.md) | Submedial Nucleus of Thalamus | nucleus  | Pain center  |
|               | [CGA.NC.DACG](BrainRegionCGA_NC_DACG.md) | Dorsal Anterior Cingulate Area | cortex, BA 32 | Rational Thought Processes |
|               | [CGA.NC.SGC](BrainRegionCGA_NC_SGC.md) | Subgenual Cortex   | cortex, BA 25 | Influences changes in appetite and sleep |
|               | [CGA.NC.VACG](BrainRegionCGA_NC_VACG.md) | Ventral Anterior Cingulate Area | cortex, BA 24 | Seat of Free Will |
| [MCA](BrainAreaMCA.md) | [FBA.MM.VTA](BrainRegionFBA_MM_VTA.md) | Ventral Tegmental Area | nucleus  | Respond to novel stimuli, unexpected rewards, and reward predictive sensory cues |
| [EPA](BrainAreaEPA.md) | [FCA.NC.IPG](BrainRegionFCA_NC_IPG.md) | Inferior Prefrontal Gyrus | cortex, BA 47 | Processing of syntax in oral and sign languages |
|               | [FCA.NC.LPFC](BrainRegionFCA_NC_LPFC.md) | Dorsolateral Prefrontal Cortex | cortex, BA 09,46 | Temporal Integration |
|               | [FCA.NC.OMPFC](BrainRegionFCA_NC_OMPFC.md) | Orbitomedial Prefrontal Cortex | cortex, BA 10,11,12 | Personality  |
| [ACA](BrainAreaACA.md) | [HMA.HM.TGM.PE5](BrainRegionHMA_HM_TGM_PE5.md) | Peritrigeminal Nucleus | nucleus  | Thermoregulation |
|               | [HTA.FD.HT.PO](BrainRegionHTA_FD_HT_PO.md) | Preoptic Area      | nucleus  | Thermoregulation |
| [MCA](BrainAreaMCA.md) | [PHA.FD.TH.LI](BrainRegionPHA_FD_TH_LI.md) | Limitans Nucleus of Thalamus | nucleus  | Multisensory projection to striatum |
| [MMA](BrainAreaMMA.md) | [PHA.NC.INS.PIC](BrainRegionPHA_NC_INS_PIC.md) | Posterior Insular Cortex | cortex, BA 13 | Awareness and sensation of pain |
|               | [PHA.NC.INS.PPC](BrainRegionPHA_NC_INS_PPC.md) | Peripaleocortical Claustral | cortex, BA 16 | Relays proprioception |
|               | [PHA.NC.PH.PIR](BrainRegionPHA_NC_PH_PIR.md) | Piriform Cortex    | cortex, BA 34 | Perception of smells |

# Connections #
(generated)

![http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitPainAndTemperature.dot.jpg](http://ahuman.googlecode.com/svn/images/dot/aHuman/CircuitPainAndTemperature.dot.jpg)

| **Source Region** | **Target Region** | **Type** | **Reference** |
|:------------------|:------------------|:---------|:--------------|
| [AVA.PN.SG.DRG](BrainRegionAVA_PN_SG_DRG.md) | [BMA.SC.PH.MG](BrainRegionBMA_SC_PH_MG.md) | ganglion-nucleus | (unknown reference) |
| [BGA.FT.ACC](BrainRegionBGA_FT_ACC.md) | [BGA.FT.VP](BrainRegionBGA_FT_VP.md) | nucleus-nucleus | [Craving (NACC -> VPAL)](http://www.impulsecontroldisorders.org/html/cravings.html) |
| [BGA.FT.CN](BrainRegionBGA_FT_CN.md) | [BGA.FT.PU](BrainRegionBGA_FT_PU.md) | nucleus-nucleus | [Regulation of Social Brain (Caud -> Put)](http://brmlab.cz/project/brain_hacking/tdcs/pfc) |
| [BMA.SC.PH.MG](BrainRegionBMA_SC_PH_MG.md) | [CGA.FD.TH.SM](BrainRegionCGA_FD_TH_SM.md) | nucleus-nucleus | (unknown reference) |
|                   | [PHA.FD.TH.LI](BrainRegionPHA_FD_TH_LI.md) | nucleus-nucleus | (unknown reference) |
| [BMA.SC.VH.VL](BrainRegionBMA_SC_VH_VL.md) | [HMA.HM.TGM.PE5](BrainRegionHMA_HM_TGM_PE5.md) | nucleus-nucleus | (unknown reference) |
| [CGA.FD.TH.SM](BrainRegionCGA_FD_TH_SM.md) | [CGA.NC.SGC](BrainRegionCGA_NC_SGC.md) | nucleus-neocortex | [Saccadic Vision (Thalamus -> FrontalCortex, abstract)](http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html) |
| [CGA.NC.SGC](BrainRegionCGA_NC_SGC.md) | [CGA.NC.DACG](BrainRegionCGA_NC_DACG.md) | neocortex-neocortex | [Regulation of Social Brain (SGC -> DACC)](http://brmlab.cz/project/brain_hacking/tdcs/pfc) |
|                   | [CGA.NC.VACG](BrainRegionCGA_NC_VACG.md) | neocortex-neocortex | [Regulation of Social Brain (SGC -> VACC)](http://brmlab.cz/project/brain_hacking/tdcs/pfc) |
| [FBA.MM.VTA](BrainRegionFBA_MM_VTA.md) | [BGA.FT.VP](BrainRegionBGA_FT_VP.md) | nucleus-nucleus | [Regulation of Social Brain (VTA -> VentPal)](http://brmlab.cz/project/brain_hacking/tdcs/pfc) |
| [FCA.NC.IPG](BrainRegionFCA_NC_IPG.md) | [CGA.NC.SGC](BrainRegionCGA_NC_SGC.md) | neocortex-neocortex | [Regulation of Social Brain (IFG -> SGC)](http://brmlab.cz/project/brain_hacking/tdcs/pfc) |
| [FCA.NC.LPFC](BrainRegionFCA_NC_LPFC.md) | [BGA.FT.CN](BrainRegionBGA_FT_CN.md) | neocortex-nucleus | [Regulation of Social Brain (DLPFC -> Caud)](http://brmlab.cz/project/brain_hacking/tdcs/pfc) |
| [FCA.NC.OMPFC](BrainRegionFCA_NC_OMPFC.md) | [FCA.NC.IPG](BrainRegionFCA_NC_IPG.md) | neocortex-neocortex | [Regulation of Social Brain (OFC -> IFG)](http://brmlab.cz/project/brain_hacking/tdcs/pfc) |
| [HMA.HM.TGM.PE5](BrainRegionHMA_HM_TGM_PE5.md) | [HTA.FD.HT.PO](BrainRegionHTA_FD_HT_PO.md) | nucleus-nucleus | (unknown reference) |
| [PHA.FD.TH.LI](BrainRegionPHA_FD_TH_LI.md) | [CGA.NC.DACG](BrainRegionCGA_NC_DACG.md) | nucleus-neocortex | [Saccadic Vision (Thalamus -> FrontalCortex, abstract)](http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html) |
|                   | [PHA.NC.INS.PPC](BrainRegionPHA_NC_INS_PPC.md) | nucleus-neocortex | [Amygdalar disruption of prefrontal cortex (TH -> INS, abstract)](http://neuropolitics.org/defaultmay10.asp) |
| [PHA.NC.INS.PIC](BrainRegionPHA_NC_INS_PIC.md) | [PHA.NC.INS.PPC](BrainRegionPHA_NC_INS_PPC.md) | neocortex-neocortex | [Gustatory sensory system of rat and macaque (Iav -> IadIap, abstract)](http://www.sciencedirect.com/science/article/pii/S0149763401000215) |
| [PHA.NC.INS.PPC](BrainRegionPHA_NC_INS_PPC.md) | [BFA.FT.AM](BrainRegionBFA_FT_AM.md) | neocortex-nucleus | (unknown reference) |
|                   | [CGA.NC.DACG](BrainRegionCGA_NC_DACG.md) | neocortex-neocortex | [Amygdalar disruption of prefrontal cortex (INS -> ACG, abstract)](http://neuropolitics.org/defaultmay10.asp) |
|                   | [FCA.NC.OMPFC](BrainRegionFCA_NC_OMPFC.md) | neocortex-neocortex | [Amygdalar disruption of prefrontal cortex (INS -> MPFC, abstract)](http://neuropolitics.org/defaultmay10.asp) |
|                   | [PHA.NC.PH.PIR](BrainRegionPHA_NC_PH_PIR.md) | neocortex-neocortex | (unknown reference) |
