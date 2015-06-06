[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [BrainAreaNDM](BrainAreaNDM.md)

---




# Local Circuits #
(generated)

| **ID** | **Name** | **Regions** |
|:-------|:---------|:------------|
| HLC    | High-Level Control | [NDM.FD.TH.MDM](BrainRegionNDM_FD_TH_MDM.md), [NDM.NC.AL.FPC](BrainRegionNDM_NC_AL_FPC.md) |
| HLNM   | High-Level Novelty Attention | [NDM.NC.AL.ROFCL](BrainRegionNDM_NC_AL_ROFCL.md), [NDM.NC.AL.ROFCM](BrainRegionNDM_NC_AL_ROFCM.md), [NDM.NC.AL.ROFCR](BrainRegionNDM_NC_AL_ROFCR.md), [NDM.NC.AL.ROFCS](BrainRegionNDM_NC_AL_ROFCS.md) |
| HWM    | Working Memory | [NDM.NC.AL.DLPFCL](BrainRegionNDM_NC_AL_DLPFCL.md), [NDM.NC.AL.DLPFCR](BrainRegionNDM_NC_AL_DLPFCR.md) |
| MAS    | Motivatory Associations | [NDM.FD.TH.SM](BrainRegionNDM_FD_TH_SM.md), [NDM.NC.AL.DMPFC](BrainRegionNDM_NC_AL_DMPFC.md), [NDM.NC.AL.IPG](BrainRegionNDM_NC_AL_IPG.md), [NDM.NC.AL.VMPFC](BrainRegionNDM_NC_AL_VMPFC.md) |
| MRS    | Motivational Responses | [NDM.NC.AL.DMCG](BrainRegionNDM_NC_AL_DMCG.md), [NDM.NC.AL.PGCG](BrainRegionNDM_NC_AL_PGCG.md), [NDM.NC.AL.VMCG](BrainRegionNDM_NC_AL_VMCG.md) |
| UMC    | Unimodal Control | [NDM.NC.AL.DACG](BrainRegionNDM_NC_AL_DACG.md), [NDM.NC.AL.VACG](BrainRegionNDM_NC_AL_VACG.md) |

## High-Level Control ##


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/NDM_HLC.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNDM_FD_TH_MDM.md'>NDM.FD.TH.MDM</a> </td><td> Medial Mediodorsal Nucleus of Thalamus </td><td> nucleus     </td><td> NPU            </td><td> relay emotional attention to orbitofrontal cortex </td><td> orbitofrontal cortex (BA12,13) defined by MDm<br>
<br>
<BR><br>
<br>
projection; relay AM-Bp to OFC; OFCm - subjective<br>
<br>
<BR><br>
<br>
pleasantness, OFCl - subjective unpleasantness </td></tr>
<tr><td> <a href='BrainRegionNDM_NC_AL_FPC.md'>NDM.NC.AL.FPC</a> </td><td> Lateral Frontopolar Cortex </td><td> cortex, BA 10 </td><td> NPU            </td><td> Emotion Regulation </td><td> Frontopolar area, contains ILC - infralimbic cortex </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNDM_FD_TH_MDM.md'>NDM.FD.TH.MDM</a> </td><td> <a href='BrainRegionNDM_NC_AL_FPC.md'>NDM.NC.AL.FPC</a> </td><td> nucleus-neocortex </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (MD -&gt; pMD, abstract)</a> </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionNDM_NC_AL_FPC.md'>NDM.NC.AL.FPC</a> </td><td> <a href='BrainRegionNCP_NC_INS_PPC.md'>NCP.NC.INS.PPC</a> </td><td> Peripaleocortical Claustral </td><td> neocortex-neocortex </td><td> <a href='http://neuropolitics.org/defaultmay10.asp'>Amygdalar disruption of prefrontal cortex (INS -&gt; MPFC, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionNDM_FD_TH_MDM.md'>NDM.FD.TH.MDM</a> </td><td> <a href='BrainRegionFAM_FT_AM_AB.md'>FAM.FT.AM.AB</a> </td><td> Accessory Basal Amygdaloid Nucleus </td><td> nucleus-nucleus </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in emotional behavior (AM -&gt; TH, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFAM_FT_SEP_MED.md'>FAM.FT.SEP.MED</a> </td><td> Medial Septal Nucleus </td><td> nucleus-nucleus-ACh </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (s1MD -&gt; MD, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionNDM_FD_TH_MDM.md'>NDM.FD.TH.MDM</a> </td><td> <a href='BrainRegionFEC_FT_GPI_RM.md'>FEC.FT.GPI.RM</a> </td><td> Globus Pallidus Internal Rostromedial </td><td> nucleus-nucleus-gaba </td><td> <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Saccadic Vision (BG -&gt; Thalamus, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionNDM_FD_TH_MDM.md'>NDM.FD.TH.MDM</a> </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> Lateral Entorhinal Cortex </td><td> neocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (EC -&gt; MDmc, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_PER.md'>FMM.NC.PH.PER</a> </td><td> Perirhinal Cortex  </td><td> neocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (Perirhinal -&gt; MDmc, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLMC.md'>LMC</a> </td><td> <a href='BrainRegionNDM_NC_AL_FPC.md'>NDM.NC.AL.FPC</a> </td><td> <a href='BrainRegionLMC_FT_NBM.md'>LMC.FT.NBM</a> </td><td> Basal Nucleus of Meynert </td><td> nucleus-neocortex-ACh </td><td> <a href='http://www.intechopen.com/books/computational-intelligence-in-electromyography-analysis-a-perspective-on-current-applications-and-future-challenges/sphincter-emg-for-diagnosing-multiple-system-atrophy-and-related-disorders'>Physiology and pathophysiology of lower urinary tract (NBM -&gt; MPFC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLMC_MM_VTA.md'>LMC.MM.VTA</a> </td><td> Ventral Tegmental Area </td><td> nucleus-neocortex-DA </td><td> <a href='http://neurowiki2012.wikispaces.com/Presynaptic+Mechanisms+of+Synaptic+Plasticity'>Reward circuit of human brain (VTA -&gt; PFC, abstract)</a> </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionNDM_FD_TH_MDM.md'>NDM.FD.TH.MDM</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCR.md'>NDM.NC.AL.DLPFCR</a> </td><td> Rostral Mid-Dorsolateral Prefrontal Cortex </td><td> nucleus-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in emotional behavior (TH -&gt; LPFC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNDM_NC_AL_FPC.md'>NDM.NC.AL.FPC</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCR.md'>NDM.NC.AL.DLPFCR</a> </td><td> Rostral Mid-Dorsolateral Prefrontal Cortex </td><td> neocortex-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in emotional behavior (OPFC -&gt; LPFC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNDM_NC_AL_VACG.md'>NDM.NC.AL.VACG</a> </td><td> Ventral Anterior Cingulate Area </td><td> neocortex-neocortex </td><td> <a href='http://www.pnas.org/content/107/40/17071/F1.expansion.html'>Role for serotonin in moral behavior (OMPFC -&gt; ACG, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionNDM_NC_AL_FPC.md'>NDM.NC.AL.FPC</a> </td><td> <a href='BrainRegionFAM_FT_AM_BM.md'>FAM.FT.AM.BM</a> </td><td> Magnocellular Basal Amygdaloid Nucleus </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFAM_FT_AM_BP.md'>FAM.FT.AM.BP</a> </td><td> Parvicellular Basal Amygdaloid Nucleus </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFAM_FT_SEP_SH.md'>FAM.FT.SEP.SH</a> </td><td> Septohippocampal Nucleus </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionNDM_NC_AL_FPC.md'>NDM.NC.AL.FPC</a> </td><td> <a href='BrainRegionFEC_FT_ACC_CORE.md'>FEC.FT.ACC.CORE</a> </td><td> Nucleus Accumbens Core </td><td> neocortex-nucleus </td><td> <a href='http://www.expertsmind.com/topic/emotion/affective-basal-ganglia-circuit-93570.aspx'>Affective basal ganglia circuit (OMPFC -&gt; NACC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFEC_FT_SNR_MED.md'>FEC.FT.SNR.MED</a> </td><td> Substantia Nigra Pars Reticulata Medial </td><td> neocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (FrontalCortex -&gt; BGA, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLAC.md'>LAC</a> </td><td> <a href='BrainRegionNDM_NC_AL_FPC.md'>NDM.NC.AL.FPC</a> </td><td> <a href='BrainRegionLAC_FD_HT_RCH.md'>LAC.FD.HT.RCH</a> </td><td> Retrochiasmatic Nucleus </td><td> neocortex-nucleus </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in emotional behavior (OPFC -&gt; HT, abstract)</a> </td></tr></tbody></table>

<h2>High-Level Novelty Attention</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/NDM_HLNM.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNDM_NC_AL_ROFCL.md'>NDM.NC.AL.ROFCL</a> </td><td> Lateral Rostral Orbitofrontal Cortex </td><td> cortex, BA 12 </td><td> NPU            </td><td> Visual selection of novelty </td><td> 12L             </td></tr>
<tr><td> <a href='BrainRegionNDM_NC_AL_ROFCM.md'>NDM.NC.AL.ROFCM</a> </td><td> Medial Rostral Orbitofrontal Cortex </td><td> cortex, BA 12 </td><td> NPU            </td><td> Somatosensory selection of novelty </td><td> 12M             </td></tr>
<tr><td> <a href='BrainRegionNDM_NC_AL_ROFCR.md'>NDM.NC.AL.ROFCR</a> </td><td> Most Rostral Orbitofrontal Cortex </td><td> cortex, BA 12 </td><td> NPU            </td><td> Integral conscious selection of novelty </td><td> 12R             </td></tr>
<tr><td> <a href='BrainRegionNDM_NC_AL_ROFCS.md'>NDM.NC.AL.ROFCS</a> </td><td> Sulcal Rostral Orbitofrontal Cortex </td><td> cortex, BA 12 </td><td> NPU            </td><td> Gustatory and auditory selection of novelty </td><td> 12S             </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNDM_NC_AL_ROFCL.md'>NDM.NC.AL.ROFCL</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCR.md'>NDM.NC.AL.ROFCR</a> </td><td> neocortex-neocortex </td><td> <a href='http://brmlab.cz/project/brain_hacking/tdcs/pfc'>Regulation of Social Brain (MPFC -&gt; OFC, abstract)</a> </td></tr>
<tr><td> <a href='BrainRegionNDM_NC_AL_ROFCM.md'>NDM.NC.AL.ROFCM</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCL.md'>NDM.NC.AL.ROFCL</a> </td><td> neocortex-neocortex </td><td> <a href='http://brmlab.cz/project/brain_hacking/tdcs/pfc'>Regulation of Social Brain (MPFC -&gt; OFC, abstract)</a> </td></tr>
<tr><td>                      </td><td> <a href='BrainRegionNDM_NC_AL_ROFCR.md'>NDM.NC.AL.ROFCR</a> </td><td> neocortex-neocortex </td><td> <a href='http://brmlab.cz/project/brain_hacking/tdcs/pfc'>Regulation of Social Brain (MPFC -&gt; OFC, abstract)</a> </td></tr>
<tr><td> <a href='BrainRegionNDM_NC_AL_ROFCS.md'>NDM.NC.AL.ROFCS</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCL.md'>NDM.NC.AL.ROFCL</a> </td><td> neocortex-neocortex </td><td> <a href='http://brmlab.cz/project/brain_hacking/tdcs/pfc'>Regulation of Social Brain (MPFC -&gt; OFC, abstract)</a> </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCR.md'>NDM.NC.AL.ROFCR</a> </td><td> <a href='BrainRegionNCP_NC_MPL_RSC.md'>NCP.NC.MPL.RSC</a> </td><td> Retrosplenial Cortex </td><td> neocortex-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in emotional behavior (PCA -&gt; OPFC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCL.md'>NDM.NC.AL.ROFCL</a> </td><td> <a href='BrainRegionNPE_FD_TH_MPV.md'>NPE.FD.TH.MPV</a> </td><td> Medial Pulvinar    </td><td> nucleus-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Saccadic Vision (Thalamus -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNDM_NC_AL_ROFCM.md'>NDM.NC.AL.ROFCM</a> </td><td> <a href='BrainRegionNPE_NC_SPL_SA.md'>NPE.NC.SPL.SA</a> </td><td> Somatosensory Association Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1053810011000080'>Cortico-Cortical Connectivity (SA -&gt; PFC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNSA.md'>NSA</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCS.md'>NDM.NC.AL.ROFCS</a> </td><td> <a href='BrainRegionNSA_NC_PO_PCC.md'>NSA.NC.PO.PCC</a> </td><td> Precentral Cortex  </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (ParietalCortex -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCR.md'>NDM.NC.AL.ROFCR</a> </td><td> <a href='BrainRegionFAM_FD_TH_PT.md'>FAM.FD.TH.PT</a> </td><td> Paratenial Nucleus of Thalamus </td><td> nucleus-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Saccadic Vision (Thalamus -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCR.md'>NDM.NC.AL.ROFCR</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1D.md'>FMM.FT.HC.CA1D</a> </td><td> Distal CA1 of Hippocampus </td><td> allocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S030100820900183X'>Simplified model of hippocampal formation anatomy (CA1 -&gt; mPFC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> Distal Subiculum   </td><td> allocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S030100820900183X'>Simplified model of hippocampal formation anatomy (SUB -&gt; mPFC, abstract)</a> </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCR.md'>NDM.NC.AL.ROFCR</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> Dorsal Anterior Cingulate Area </td><td> neocortex-neocortex </td><td> <a href='http://www.pnas.org/content/107/40/17071/F1.expansion.html'>Role for serotonin in moral behavior (OMPFC -&gt; ACG, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNDM_NC_AL_IPG.md'>NDM.NC.AL.IPG</a> </td><td> Inferior Prefrontal Gyrus </td><td> neocortex-neocortex </td><td> <a href='http://brmlab.cz/project/brain_hacking/tdcs/pfc'>Regulation of Social Brain (OFC -&gt; IFG, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCR.md'>NDM.NC.AL.ROFCR</a> </td><td> <a href='BrainRegionFEC_FD_STN_DL.md'>FEC.FD.STN.DL</a> </td><td> Subthalamic Nucleus Dorsolateral </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFEC_FD_TH_RH.md'>FEC.FD.TH.RH</a> </td><td> Rhomboidal Nucleus of Thalamus </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFEC_FT_CN_TL.md'>FEC.FT.CN.TL</a> </td><td> Caudate Nucleus Tail </td><td> neocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (FrontalCortex -&gt; BGA, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCR.md'>NDM.NC.AL.ROFCR</a> </td><td> <a href='BrainRegionFMM_FD_TH_RE.md'>FMM.FD.TH.RE</a> </td><td> Reuniens Nucleus of Thalamus </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr></tbody></table>

<h2>Working Memory</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/NDM_HWM.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNDM_NC_AL_DLPFCL.md'>NDM.NC.AL.DLPFCL</a> </td><td> Lateral Mid-Dorsolateral Prefrontal Cortex </td><td> cortex, BA 46 </td><td> NPU            </td><td> Cognitive control related to stimulus processing and selection of relevant<br>
<br>
<BR><br>
<br>
information for behavior </td><td>                 </td></tr>
<tr><td> <a href='BrainRegionNDM_NC_AL_DLPFCR.md'>NDM.NC.AL.DLPFCR</a> </td><td> Rostral Mid-Dorsolateral Prefrontal Cortex </td><td> cortex, BA 46 </td><td> NPU            </td><td> Cognitive control and monitoring to resolve conflict in information processing<br>
<br>
<BR><br>
<br>
and competing response plans </td><td>                 </td></tr></tbody></table>

<b>Internal Region Connections:</b>
<ul><li>no connections</li></ul>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCR.md'>NDM.NC.AL.DLPFCR</a> </td><td> <a href='BrainRegionNCP_NC_MPL_RSC.md'>NCP.NC.MPL.RSC</a> </td><td> Retrosplenial Cortex </td><td> neocortex-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in emotional behavior (PCA -&gt; LPFC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCL.md'>NDM.NC.AL.DLPFCL</a> </td><td> <a href='BrainRegionNDM_NC_AL_IPG.md'>NDM.NC.AL.IPG</a> </td><td> Inferior Prefrontal Gyrus </td><td> neocortex-neocortex </td><td> <a href='http://www.frontiersin.org/Human_Neuroscience/10.3389/fnhum.2012.00184/full'>Directed Effort Network (fPole -&gt; DLPFC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCR.md'>NDM.NC.AL.DLPFCR</a> </td><td> <a href='BrainRegionNDM_FD_TH_MDM.md'>NDM.FD.TH.MDM</a> </td><td> Medial Mediodorsal Nucleus of Thalamus </td><td> nucleus-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in emotional behavior (TH -&gt; LPFC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNDM_NC_AL_FPC.md'>NDM.NC.AL.FPC</a> </td><td> Lateral Frontopolar Cortex </td><td> neocortex-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in emotional behavior (OPFC -&gt; LPFC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCL.md'>NDM.NC.AL.DLPFCL</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F4.md'>NMA.NC.PMC.F4</a> </td><td> Ventral Caudal Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1053810011000080'>Cortico-Cortical Connectivity (MA -&gt; PFC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCL.md'>NDM.NC.AL.DLPFCL</a> </td><td> <a href='BrainRegionNPE_FD_TH_MPV.md'>NPE.FD.TH.MPV</a> </td><td> Medial Pulvinar    </td><td> nucleus-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Saccadic Vision (Thalamus -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCR.md'>NDM.NC.AL.DLPFCR</a> </td><td> <a href='BrainRegionNPE_NC_IPL_MST.md'>NPE.NC.IPL.MST</a> </td><td> Medial Superior Temporal Area </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1053810011000080'>Cortico-Cortical Connectivity (PTHA -&gt; PFC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNSA.md'>NSA</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCL.md'>NDM.NC.AL.DLPFCL</a> </td><td> <a href='BrainRegionNSA_NC_IT_TE.md'>NSA.NC.IT.TE</a> </td><td> Inferotemporal Cortex </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (IT -&gt; LPC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_OCC_V2TN.md'>NSA.NC.OCC.V2TN</a> </td><td> Secondary Visual Cortex, Thin Stripe </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1053810011000080'>Cortico-Cortical Connectivity (VA -&gt; PFC, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaLLC.md'>LLC</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCL.md'>NDM.NC.AL.DLPFCL</a> </td><td> <a href='BrainRegionLLC_HP_CR_DN.md'>LLC.HP.CR.DN</a> </td><td> Dentate Nucleus    </td><td> nucleus-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in motor behavior (CR -&gt; LPFC, abstract)</a> </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCR.md'>NDM.NC.AL.DLPFCR</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> Dorsal Anterior Cingulate Area </td><td> neocortex-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in emotional behavior (LPFC -&gt; ACG, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCL.md'>NDM.NC.AL.DLPFCL</a> </td><td> <a href='BrainRegionNMA_FD_TH_VA.md'>NMA.FD.TH.VA</a> </td><td> Ventral Anterior Nucleus </td><td> neocortex-nucleus </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in motor behavior (LPFC -&gt; TH, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNMA_NC_PMC_AFEF.md'>NMA.NC.PMC.AFEF</a> </td><td> Anterior Frontal Eye Field </td><td> neocortex-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in motor behavior (LPFC -&gt; PMC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNMA_NC_PMC_F5.md'>NMA.NC.PMC.F5</a> </td><td> Ventral Rostral Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in motor behavior (LPFC -&gt; PMC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCR.md'>NDM.NC.AL.DLPFCR</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F7.md'>NMA.NC.PMC.F7</a> </td><td> Dorsal Rostral Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in motor behavior (LPFC -&gt; PMC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNMA_NC_SMC_SEF.md'>NMA.NC.SMC.SEF</a> </td><td> Supplementary Eye Field </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (LPC -&gt; pre-SMA, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCL.md'>NDM.NC.AL.DLPFCL</a> </td><td> <a href='BrainRegionFEC_FT_CN_HD.md'>FEC.FT.CN.HD</a> </td><td> Caudate Nucleus Head </td><td> neocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (FrontalCortex -&gt; BGA, abstract)</a> </td></tr></tbody></table>

<h2>Motivatory Associations</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/NDM_MAS.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNDM_FD_TH_SM.md'>NDM.FD.TH.SM</a> </td><td> Submedial Nucleus of Thalamus </td><td> nucleus     </td><td> NPU            </td><td> Pain center     </td><td> Projections from SC Lamina I, trigeminal nucleus to<br>
<br>
<BR><br>
<br>
ACC </td></tr>
<tr><td> <a href='BrainRegionNDM_NC_AL_DMPFC.md'>NDM.NC.AL.DMPFC</a> </td><td> Dorsomedial Prefrontal Cortex </td><td> cortex, BA 09 </td><td> NPU            </td><td> Ongoing Extroverted Attention to Select Appropriate Response </td><td> upper MPFC, primary connections to the cingulate<br>
<br>
<BR><br>
<br>
and the motor and premotor cortices </td></tr>
<tr><td> <a href='BrainRegionNDM_NC_AL_IPG.md'>NDM.NC.AL.IPG</a> </td><td> Inferior Prefrontal Gyrus </td><td> cortex, BA 47 </td><td> NPU            </td><td> Processing of syntax in oral and sign languages </td><td> Personality, endurance </td></tr>
<tr><td> <a href='BrainRegionNDM_NC_AL_VMPFC.md'>NDM.NC.AL.VMPFC</a> </td><td> Ventromedial Prefrontal Cortex </td><td> cortex, BA 11 </td><td> NPU            </td><td> Ongoing Introverted Attention with Regard to Emotions and Feelings, Reward or<br>
<br>
<BR><br>
<br>
Punishment </td><td> lower MPFC, primary connections to limbic and<br>
<br>
<BR><br>
<br>
sensory cortices; Reward mediated behaviours </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNDM_FD_TH_SM.md'>NDM.FD.TH.SM</a> </td><td> <a href='BrainRegionNDM_NC_AL_DMPFC.md'>NDM.NC.AL.DMPFC</a> </td><td> nucleus-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Saccadic Vision (Thalamus -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td> <a href='BrainRegionNDM_NC_AL_IPG.md'>NDM.NC.AL.IPG</a> </td><td> <a href='BrainRegionNDM_NC_AL_DMPFC.md'>NDM.NC.AL.DMPFC</a> </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionNDM_NC_AL_IPG.md'>NDM.NC.AL.IPG</a> </td><td> <a href='BrainRegionNCP_NC_INS_AIC.md'>NCP.NC.INS.AIC</a> </td><td> Anterior Insular Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.frontiersin.org/Human_Neuroscience/10.3389/fnhum.2012.00184/full'>Directed Effort Network (Insula -&gt; fPole, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNCP_NC_TPC.md'>NCP.NC.TPC</a> </td><td> Temporopolar Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1364661312002823'>Language-Related Regions (TC -&gt; vIFC)</a> </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionNDM_NC_AL_IPG.md'>NDM.NC.AL.IPG</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCR.md'>NDM.NC.AL.ROFCR</a> </td><td> Most Rostral Orbitofrontal Cortex </td><td> neocortex-neocortex </td><td> <a href='http://brmlab.cz/project/brain_hacking/tdcs/pfc'>Regulation of Social Brain (OFC -&gt; IFG, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionNDM_NC_AL_VMPFC.md'>NDM.NC.AL.VMPFC</a> </td><td> <a href='BrainRegionFAM_FT_SEP_DBB.md'>FAM.FT.SEP.DBB</a> </td><td> Diagonal Band of Broca </td><td> nucleus-neocortex-gaba </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainAreaLPC.md'>LPC</a> </td><td> <a href='BrainRegionNDM_FD_TH_SM.md'>NDM.FD.TH.SM</a> </td><td> <a href='BrainRegionLPC_SC_PH_LMG.md'>LPC.SC.PH.LMG</a> </td><td> Lower Marginal Nucleus </td><td> nucleus-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLPC_SC_PH_UMG.md'>LPC.SC.PH.UMG</a> </td><td> Upper Marginal Nucleus </td><td> nucleus-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNDM_NC_AL_VMPFC.md'>NDM.NC.AL.VMPFC</a> </td><td> <a href='BrainRegionLPC_FD_TH_PV.md'>LPC.FD.TH.PV</a> </td><td> Paraventricular Nucleus of Thalamus </td><td> nucleus-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Saccadic Vision (Thalamus -&gt; FrontalCortex, abstract)</a> </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionNDM_NC_AL_DMPFC.md'>NDM.NC.AL.DMPFC</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> Dorsal Anterior Cingulate Area </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNDM_NC_AL_IPG.md'>NDM.NC.AL.IPG</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCL.md'>NDM.NC.AL.DLPFCL</a> </td><td> Lateral Mid-Dorsolateral Prefrontal Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.frontiersin.org/Human_Neuroscience/10.3389/fnhum.2012.00184/full'>Directed Effort Network (fPole -&gt; DLPFC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNDM_NC_AL_VACG.md'>NDM.NC.AL.VACG</a> </td><td> Ventral Anterior Cingulate Area </td><td> neocortex-neocortex </td><td> <a href='http://www.frontiersin.org/Human_Neuroscience/10.3389/fnhum.2012.00184/full'>Directed Effort Network (fPole -&gt; vACC)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionNDM_NC_AL_DMPFC.md'>NDM.NC.AL.DMPFC</a> </td><td> <a href='BrainRegionFAM_FT_AM_ITC.md'>FAM.FT.AM.ITC</a> </td><td> Intercalated Amygdaloid Nuclei </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr></tbody></table>

<h2>Motivational Responses</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/NDM_MRS.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNDM_NC_AL_DMCG.md'>NDM.NC.AL.DMCG</a> </td><td> Dorsal Anterior Cingulate Area </td><td> cortex, BA 32 </td><td> NPU            </td><td> Rational Thought Processes </td><td> Anticipate and detect targets, indicate novelty,<br>
<br>
<BR><br>
<br>
influence motor responses, encode reward values,<br>
<br>
<BR><br>
<br>
and signal errors, motor, attentional and cognitive<br>
<br>
<BR><br>
<br>
functions; BA32-caudal </td></tr>
<tr><td> <a href='BrainRegionNDM_NC_AL_PGCG.md'>NDM.NC.AL.PGCG</a> </td><td> Pregenual Cingulate Cortex </td><td> cortex, BA 33 </td><td> NPU            </td><td> Sensation of Emotion </td><td> Storage of emotional memory, emotions, mood and<br>
<br>
<BR><br>
<br>
autonomic functions </td></tr>
<tr><td> <a href='BrainRegionNDM_NC_AL_VMCG.md'>NDM.NC.AL.VMCG</a> </td><td> Ventral Anterior Cingulate Area </td><td> cortex, BA 24 </td><td> NPU            </td><td> Response Selection </td><td> BA24-caudal     </td></tr></tbody></table>

<b>Internal Region Connections:</b>
<ul><li>no connections</li></ul>

<b>External Inbound Region Connections:</b>
<ul><li>no connections</li></ul>

<b>External Outbound Region Connections:</b>
<ul><li>no connections</li></ul>

<h2>Unimodal Control</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/NDM_UMC.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> Dorsal Anterior Cingulate Area </td><td> cortex, BA 32 </td><td> NPU            </td><td> Rational Thought Processes </td><td> Anticipate and detect targets, indicate novelty,<br>
<br>
<BR><br>
<br>
influence motor responses, encode reward values,<br>
<br>
<BR><br>
<br>
and signal errors, motor, attentional and cognitive<br>
<br>
<BR><br>
<br>
functions; BA32-rostral </td></tr>
<tr><td> <a href='BrainRegionNDM_NC_AL_VACG.md'>NDM.NC.AL.VACG</a> </td><td> Ventral Anterior Cingulate Area </td><td> cortex, BA 24 </td><td> NPU            </td><td> Seat of Free Will </td><td> motor, attentional and cognitive functions;<br>
<br>
<BR><br>
<br>
BA24-rostral </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> <a href='BrainRegionNDM_NC_AL_VACG.md'>NDM.NC.AL.VACG</a> </td><td> neocortex-neocortex </td><td> <a href='http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.html'>Principal Connections of Hippocampus (DorsalCingulate -&gt; VentralCingulate)</a> </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> <a href='BrainRegionNCP_NC_INS_PPC.md'>NCP.NC.INS.PPC</a> </td><td> Peripaleocortical Claustral </td><td> neocortex-neocortex </td><td> <a href='http://neuropolitics.org/defaultmay10.asp'>Amygdalar disruption of prefrontal cortex (INS -&gt; ACG, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNDM_NC_AL_VACG.md'>NDM.NC.AL.VACG</a> </td><td> <a href='BrainRegionNCP_FD_TH_AM.md'>NCP.FD.TH.AM</a> </td><td> Anteromedial Nucleus </td><td> nucleus-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Saccadic Vision (Thalamus -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNCP_NC_INS_AIC.md'>NCP.NC.INS.AIC</a> </td><td> Anterior Insular Cortex </td><td> neocortex-neocortex </td><td> <a href='http://neuropolitics.org/defaultmay10.asp'>Amygdalar disruption of prefrontal cortex (INS -&gt; ACG, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCR.md'>NDM.NC.AL.DLPFCR</a> </td><td> Rostral Mid-Dorsolateral Prefrontal Cortex </td><td> neocortex-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in emotional behavior (LPFC -&gt; ACG, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNDM_NC_AL_DMPFC.md'>NDM.NC.AL.DMPFC</a> </td><td> Dorsomedial Prefrontal Cortex </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNDM_NC_AL_ROFCR.md'>NDM.NC.AL.ROFCR</a> </td><td> Most Rostral Orbitofrontal Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.pnas.org/content/107/40/17071/F1.expansion.html'>Role for serotonin in moral behavior (OMPFC -&gt; ACG, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNDM_NC_AL_VACG.md'>NDM.NC.AL.VACG</a> </td><td> <a href='BrainRegionNDM_NC_AL_FPC.md'>NDM.NC.AL.FPC</a> </td><td> Lateral Frontopolar Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.pnas.org/content/107/40/17071/F1.expansion.html'>Role for serotonin in moral behavior (OMPFC -&gt; ACG, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNDM_NC_AL_IPG.md'>NDM.NC.AL.IPG</a> </td><td> Inferior Prefrontal Gyrus </td><td> neocortex-neocortex </td><td> <a href='http://www.frontiersin.org/Human_Neuroscience/10.3389/fnhum.2012.00184/full'>Directed Effort Network (fPole -&gt; vACC)</a> </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> <a href='BrainRegionNMA_FD_TH_MDL.md'>NMA.FD.TH.MDL</a> </td><td> Lateral Mediodorsal Nucleus of Thalamus </td><td> nucleus-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Saccadic Vision (Thalamus -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> <a href='BrainRegionNPE_NC_IPL_MST.md'>NPE.NC.IPL.MST</a> </td><td> Medial Superior Temporal Area </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (ParietalCortex -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNPE_NC_SPL_PF.md'>NPE.NC.SPL.PF</a> </td><td> Rostral Precuneus  </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (ParietalCortex -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNSA.md'>NSA</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> <a href='BrainRegionNSA_NC_TTG_A2.md'>NSA.NC.TTG.A2</a> </td><td> Auditory Association Area </td><td> neocortex-neocortex </td><td> <a href='http://www.frontiersin.org/Human_Neuroscience/10.3389/fnhum.2012.00184/full'>Directed Effort Network (ACA -&gt; dACC)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> <a href='BrainRegionFAM_FT_AM_AB.md'>FAM.FT.AM.AB</a> </td><td> Accessory Basal Amygdaloid Nucleus </td><td> nucleus-neocortex </td><td> <a href='http://neuropolitics.org/defaultmay10.asp'>Amygdalar disruption of prefrontal cortex (AM -&gt; ACG, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNDM_NC_AL_VACG.md'>NDM.NC.AL.VACG</a> </td><td> <a href='BrainRegionFAM_FT_AM_AB.md'>FAM.FT.AM.AB</a> </td><td> Accessory Basal Amygdaloid Nucleus </td><td> nucleus-neocortex </td><td> <a href='http://neuropolitics.org/defaultmay10.asp'>Amygdalar disruption of prefrontal cortex (AM -&gt; ACG, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> <a href='BrainRegionFEC_FD_TH_LI.md'>FEC.FD.TH.LI</a> </td><td> Limitans Nucleus of Thalamus </td><td> nucleus-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Saccadic Vision (Thalamus -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLMC.md'>LMC</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> <a href='BrainRegionLMC_MM_VTA.md'>LMC.MM.VTA</a> </td><td> Ventral Tegmental Area </td><td> nucleus-neocortex-DA </td><td> (unknown reference) </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> <a href='BrainRegionNCP_NC_MPL_PSCG.md'>NCP.NC.MPL.PSCG</a> </td><td> Posterior Cingulate Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (FrontalCortex -&gt; ParietalCortex, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNDM_NC_AL_VACG.md'>NDM.NC.AL.VACG</a> </td><td> <a href='BrainRegionNCP_NC_MPL_PSCG.md'>NCP.NC.MPL.PSCG</a> </td><td> Posterior Cingulate Cortex </td><td> neocortex-neocortex </td><td> <a href='http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.html'>Principal Connections of Hippocampus (VentralCingulate -&gt; PosteriorCingulate)</a> </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F7.md'>NMA.NC.PMC.F7</a> </td><td> Dorsal Rostral Premotor Cortex </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNDM_NC_AL_VACG.md'>NDM.NC.AL.VACG</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> Dorsal Caudal Premotor Cortex </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> <a href='BrainRegionFAM_FT_AM_BP.md'>FAM.FT.AM.BP</a> </td><td> Parvicellular Basal Amygdaloid Nucleus </td><td> neocortex-nucleus </td><td> <a href='http://www.pnas.org/content/107/40/17071/F1.expansion.html'>Role for serotonin in moral behavior (ACG -&gt; AMY, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNDM_NC_AL_VACG.md'>NDM.NC.AL.VACG</a> </td><td> <a href='BrainRegionFAM_FT_AM_BP.md'>FAM.FT.AM.BP</a> </td><td> Parvicellular Basal Amygdaloid Nucleus </td><td> neocortex-nucleus </td><td> <a href='http://www.pnas.org/content/107/40/17071/F1.expansion.html'>Role for serotonin in moral behavior (ACG -&gt; AMY, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> <a href='BrainRegionFEC_FD_STN_CD.md'>FEC.FD.STN.CD</a> </td><td> Subthalamic Nucleus Caudal </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFEC_FT_CN_HD.md'>FEC.FT.CN.HD</a> </td><td> Caudate Nucleus Head </td><td> neocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (FrontalCortex -&gt; BGA, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNDM_NC_AL_VACG.md'>NDM.NC.AL.VACG</a> </td><td> <a href='BrainRegionFEC_FT_ACC_SH.md'>FEC.FT.ACC.SH</a> </td><td> Nucleus Accumbens Shell </td><td> neocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (FrontalCortex -&gt; BGA, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFEC_FT_CN_BD.md'>FEC.FT.CN.BD</a> </td><td> Caudate Nucleus Body </td><td> neocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (FrontalCortex -&gt; BGA, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFEC_FT_PU_VT.md'>FEC.FT.PU.VT</a> </td><td> Ventral Putamen    </td><td> neocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (FrontalCortex -&gt; BGA, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLLC.md'>LLC</a> </td><td> <a href='BrainRegionNDM_NC_AL_VACG.md'>NDM.NC.AL.VACG</a> </td><td> <a href='BrainRegionLLC_HP_PRF_PDT.md'>LLC.HP.PRF.PDT</a> </td><td> Pontine Reticulotegmental Nucleus </td><td> neocortex-nucleus </td><td> <a href='http://www.frontiersin.org/neuroanatomy/10.3389/fnana.2011.00034/full'>Vocal Control (Premotor24 -&gt; RF, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLLC_MM_RD.md'>LLC.MM.RD</a> </td><td> Red Nucleus        </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainAreaLMC.md'>LMC</a> </td><td> <a href='BrainRegionNDM_NC_AL_VACG.md'>NDM.NC.AL.VACG</a> </td><td> <a href='BrainRegionLMC_HP_LC.md'>LMC.HP.LC</a> </td><td> Locus Coeruleus    </td><td> neocortex-nucleus </td><td> <a href='http://www.frontiersin.org/neuroanatomy/10.3389/fnana.2011.00034/full'>Vocal Control (Premotor24 -&gt; RF, abstract)</a> </td></tr></tbody></table>

<h1>Thirdparty Circuits</h1>
(generated)<br>
<br>
<ul><li><a href='http://brmlab.cz/lib/exe/fetch.php?hash=fca48f&media=http%3A%2F%2Fars.els-cdn.com%2Fcontent%2Fimage%2F1-s2.0-S1364661308002490-gr2.jpg'>Regulation of Social Brain</a> - see <a href='http://brmlab.cz/project/brain_hacking/tdcs/pfc'>Reference</a></li></ul>

<img src='http://brmlab.cz/lib/exe/fetch.php?hash=fca48f&media=http%3A%2F%2Fars.els-cdn.com%2Fcontent%2Fimage%2F1-s2.0-S1364661308002490-gr2.jpg' alt='unavailable'>

<ul><li><a href='http://c431376.r76.cf2.rackcdn.com/18691/fnhum-06-00184-HTML/image_m/fnhum-06-00184-g001.jpg'>Directed Effort Network</a> - see <a href='http://www.frontiersin.org/Human_Neuroscience/10.3389/fnhum.2012.00184/full'>Reference</a></li></ul>

<img src='http://c431376.r76.cf2.rackcdn.com/18691/fnhum-06-00184-HTML/image_m/fnhum-06-00184-g001.jpg' alt='unavailable'>

<ul><li><a href='http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.gif'>Principal Connections of Hippocampus</a> - see <a href='http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.html'>Reference</a></li></ul>

<img src='http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.gif' alt='unavailable'>

<ul><li><a href='http://c431376.r76.cf2.rackcdn.com/10053/fnana-05-00034-r1/image_m/fnana-05-00034-g002.jpg'>Vocal Control</a> - see <a href='http://www.frontiersin.org/neuroanatomy/10.3389/fnana.2011.00034/full'>Reference</a></li></ul>

<img src='http://c431376.r76.cf2.rackcdn.com/10053/fnana-05-00034-r1/image_m/fnana-05-00034-g002.jpg' alt='unavailable'>

<ul><li><a href='http://ars.els-cdn.com/content/image/1-s2.0-S1364661312002823-gr2.jpg'>Language-Related Regions</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S1364661312002823'>Reference</a></li></ul>

<img src='http://ars.els-cdn.com/content/image/1-s2.0-S1364661312002823-gr2.jpg' alt='unavailable'>

<ul><li><a href='http://www.nature.com/npp/journal/v35/n1/images/npp2009121f1.jpg'>Fear regulation</a> - see <a href='https://brmlab.cz/project/brain_hacking/tdcs/pfc'>Reference</a></li></ul>

<img src='http://www.nature.com/npp/journal/v35/n1/images/npp2009121f1.jpg' alt='unavailable'>

<ul><li><a href='http://www.nature.com/npp/journal/v35/n1/images/npp2009129f1.jpg'>Pathways of Reward Circuit</a> - see <a href='http://www.nature.com/npp/journal/v35/n1/fig_tab/npp2009129f1.html'>Reference</a></li></ul>

<img src='http://www.nature.com/npp/journal/v35/n1/images/npp2009129f1.jpg' alt='unavailable'>

<ul><li><a href='http://contemplativemind.files.wordpress.com/2011/03/mental_illness_matrix_2010_final1.jpg'>Depression</a> - see <a href='http://contemplativemind.wordpress.com/category/peer-reviewed-journal-articles/'>Reference</a></li></ul>

<img src='http://contemplativemind.files.wordpress.com/2011/03/mental_illness_matrix_2010_final1.jpg' alt='unavailable'>


<h1>References</h1>
(generated)<br>
<br>
<ul><li><a href='http://brmlab.cz/project/brain_hacking/tdcs/pfc'>http://brmlab.cz/project/brain_hacking/tdcs/pfc</a>
</li><li><a href='http://www.frontiersin.org/Human_Neuroscience/10.3389/fnhum.2012.00184/full'>http://www.frontiersin.org/Human_Neuroscience/10.3389/fnhum.2012.00184/full</a>
</li><li><a href='http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.html'>http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.html</a>
</li><li><a href='http://www.frontiersin.org/neuroanatomy/10.3389/fnana.2011.00034/full'>http://www.frontiersin.org/neuroanatomy/10.3389/fnana.2011.00034/full</a>
</li><li><a href='http://www.sciencedirect.com/science/article/pii/S1364661312002823'>http://www.sciencedirect.com/science/article/pii/S1364661312002823</a>
</li><li><a href='https://brmlab.cz/project/brain_hacking/tdcs/pfc'>https://brmlab.cz/project/brain_hacking/tdcs/pfc</a>
</li><li><a href='http://www.nature.com/npp/journal/v35/n1/fig_tab/npp2009129f1.html'>http://www.nature.com/npp/journal/v35/n1/fig_tab/npp2009129f1.html</a>
</li><li><a href='http://contemplativemind.wordpress.com/category/peer-reviewed-journal-articles/'>http://contemplativemind.wordpress.com/category/peer-reviewed-journal-articles/</a></li></ul>
