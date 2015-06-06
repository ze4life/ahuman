[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [BrainAreaFMM](BrainAreaFMM.md)

---




# Local Circuits #
(generated)

| **ID** | **Name** | **Regions** |
|:-------|:---------|:------------|
| MMAHCE | Emotional Hippocampus | [FMM.FT.HC.CA1D](BrainRegionFMM_FT_HC_CA1D.md), [FMM.FT.HC.CA3P](BrainRegionFMM_FT_HC_CA3P.md), [FMM.FT.HF.SUBP](BrainRegionFMM_FT_HF_SUBP.md) |
| MMAHCF | Creating Fields | [FMM.FT.HC.CA2](BrainRegionFMM_FT_HC_CA2.md), [FMM.FT.HC.DG](BrainRegionFMM_FT_HC_DG.md) |
| MMAHCS | Spatial Hippocampus | [FMM.FT.HC.CA1P](BrainRegionFMM_FT_HC_CA1P.md), [FMM.FT.HC.CA3D](BrainRegionFMM_FT_HC_CA3D.md), [FMM.FT.HF.SUBD](BrainRegionFMM_FT_HF_SUBD.md) |
| MMAHCT | Thalamic Hippocampus | [FMM.FD.TH.RE](BrainRegionFMM_FD_TH_RE.md), [FMM.FT.HC.CA1M](BrainRegionFMM_FT_HC_CA1M.md), [FMM.FT.HC.CA3M](BrainRegionFMM_FT_HC_CA3M.md), [FMM.FT.HF.SUBM](BrainRegionFMM_FT_HF_SUBM.md) |
| MMAORIENT | Orienting Control | [FMM.FD.MB.LMB](BrainRegionFMM_FD_MB_LMB.md), [FMM.FD.TH.AD](BrainRegionFMM_FD_TH_AD.md), [FMM.NC.PH.POS](BrainRegionFMM_NC_PH_POS.md) |
| MMASENSE | Emotional Sensory Input to Hippocampus | [FMM.NC.PH.LEC](BrainRegionFMM_NC_PH_LEC.md), [FMM.NC.PH.PER](BrainRegionFMM_NC_PH_PER.md) |
| MMASENSS | Spatial Sensory Input to Hippocampus | [FMM.NC.PH.MEC](BrainRegionFMM_NC_PH_MEC.md), [FMM.NC.PH.POR](BrainRegionFMM_NC_PH_POR.md) |
| MMATHETA | Theta Waves Control | [FMM.FD.MB.MMB](BrainRegionFMM_FD_MB_MMB.md), [FMM.FD.TH.AV](BrainRegionFMM_FD_TH_AV.md), [FMM.FD.TH.LD](BrainRegionFMM_FD_TH_LD.md), [FMM.NC.PH.PAS](BrainRegionFMM_NC_PH_PAS.md), [FMM.NC.PH.PRS](BrainRegionFMM_NC_PH_PRS.md) |

## Emotional Hippocampus ##


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/FMM_MMAHCE.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionFMM_FT_HC_CA1D.md'>FMM.FT.HC.CA1D</a> </td><td> Distal CA1 of Hippocampus </td><td> cortex      </td><td> FMU            </td><td> Long-term memory, motivational </td><td>                 </td></tr>
<tr><td> <a href='BrainRegionFMM_FT_HC_CA3P.md'>FMM.FT.HC.CA3P</a> </td><td> Proximal CA1 of Hippocampus </td><td> cortex      </td><td> FMU            </td><td> Representing sequences of episodic memory, spatial </td><td>                 </td></tr>
<tr><td> <a href='BrainRegionFMM_FT_HF_SUBP.md'>FMM.FT.HF.SUBP</a> </td><td> Proximal Subiculum    </td><td> cortex      </td><td> FMU            </td><td> Controlling hypothalamic-pituitary-adrenal (HPA) axis </td><td>                 </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionFMM_FT_HC_CA1D.md'>FMM.FT.HC.CA1D</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBP.md'>FMM.FT.HF.SUBP</a> </td><td> allocortex-allocortex </td><td> <a href='http://learnmem.cshlp.org/content/14/11/714/F1.expansion'>Attractor Network in Hippocampus (CA1 -&gt; SUB, abstract)</a> </td></tr>
<tr><td> <a href='BrainRegionFMM_FT_HC_CA3P.md'>FMM.FT.HC.CA3P</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1D.md'>FMM.FT.HC.CA1D</a> </td><td> allocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (CA3 -&gt; CA1, abstract)</a> </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBP.md'>FMM.FT.HF.SUBP</a> </td><td> <a href='BrainRegionFAM_FT_SEP_BAC.md'>FAM.FT.SEP.BAC</a> </td><td> Bed Nucleus of Anterior Commissure </td><td> nucleus-allocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html'>Medial mammillary nucleus and theta rhythm (SEP -&gt; HF, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBP.md'>FMM.FT.HF.SUBP</a> </td><td> <a href='BrainRegionFEC_FD_TH_RH.md'>FEC.FD.TH.RH</a> </td><td> Rhomboidal Nucleus of Thalamus </td><td> nucleus-allocortex </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (MID -&gt; SubPrePara, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1D.md'>FMM.FT.HC.CA1D</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA2.md'>FMM.FT.HC.CA2</a> </td><td> Dorsolateral Cornu Ammonis of Hippocampus </td><td> allocortex-allocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S030645220600755X'>Flow of impulses in hippocampal region (CA2 -&gt; CA1, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> Lateral Entorhinal Cortex </td><td> neocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (ET -&gt; CA1, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FT_HC_CA3P.md'>FMM.FT.HC.CA3P</a> </td><td> <a href='BrainRegionFMM_FT_HC_DG.md'>FMM.FT.HC.DG</a> </td><td> Dentate Gyrus      </td><td> allocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (DG -&gt; CA3, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FT_HF_SUBP.md'>FMM.FT.HF.SUBP</a> </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> Lateral Entorhinal Cortex </td><td> neocortex-allocortex </td><td> <a href='http://www.scholarpedia.org/article/Inferior_temporal_cortex'>Visual Path to Hippocampus (ER -&gt; H, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_PER.md'>FMM.NC.PH.PER</a> </td><td> Perirhinal Cortex  </td><td> neocortex-allocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0149763401000215'>Gustatory sensory system of rat and macaque (PrC -&gt; HF, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLAC.md'>LAC</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA3P.md'>FMM.FT.HC.CA3P</a> </td><td> <a href='BrainRegionLAC_FD_HT_PN.md'>LAC.FD.HT.PN</a> </td><td> Posterior Hypothalamic Nucleus </td><td> nucleus-allocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLAC_FD_HT_SUM.md'>LAC.FD.HT.SUM</a> </td><td> Supramammillary Nucleus </td><td> nucleus-allocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html'>Medial mammillary nucleus and theta rhythm (SupraMM -&gt; HF, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLMC.md'>LMC</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1D.md'>FMM.FT.HC.CA1D</a> </td><td> <a href='BrainRegionLMC_MM_VTA.md'>LMC.MM.VTA</a> </td><td> Ventral Tegmental Area </td><td> nucleus-allocortex-DA </td><td> <a href='http://neurowiki2012.wikispaces.com/Presynaptic+Mechanisms+of+Synaptic+Plasticity'>Reward circuit of human brain (VTA -&gt; HC, abstract)</a> </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1D.md'>FMM.FT.HC.CA1D</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCR.md'>NDM.NC.AL.ROFCR</a> </td><td> Most Rostral Orbitofrontal Cortex </td><td> allocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S030100820900183X'>Simplified model of hippocampal formation anatomy (CA1 -&gt; mPFC, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1D.md'>FMM.FT.HC.CA1D</a> </td><td> <a href='BrainRegionFAM_FT_SEP_MED.md'>FAM.FT.SEP.MED</a> </td><td> Medial Septal Nucleus </td><td> allocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/14/11/714/F1.expansion'>Attractor Network in Hippocampus (CA1 -&gt; SEP, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FT_HF_SUBP.md'>FMM.FT.HF.SUBP</a> </td><td> <a href='BrainRegionFAM_FT_AM_AB.md'>FAM.FT.AM.AB</a> </td><td> Accessory Basal Amygdaloid Nucleus </td><td> allocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S030100820900183X'>Simplified model of hippocampal formation anatomy (SUB -&gt; Amyg, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBP.md'>FMM.FT.HF.SUBP</a> </td><td> <a href='BrainRegionFEC_FT_ACC_CORE.md'>FEC.FT.ACC.CORE</a> </td><td> Nucleus Accumbens Core </td><td> allocortex-nucleus </td><td> <a href='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/nucleus-accumbens.jpg'>Nucleus Accumbens (SUB -&gt; NACC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA3P.md'>FMM.FT.HC.CA3P</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA2.md'>FMM.FT.HC.CA2</a> </td><td> Dorsolateral Cornu Ammonis of Hippocampus </td><td> allocortex-allocortex-gaba </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1571064507000243'>KIV model of cortico-hippocampal formation with subcortical projections for motor actions (CA3 -&gt; CA2, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FT_HF_SUBP.md'>FMM.FT.HF.SUBP</a> </td><td> <a href='BrainRegionFMM_FD_MB_MMB.md'>FMM.FD.MB.MMB</a> </td><td> Medial Mammillary Nucleus </td><td> allocortex-nucleus </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html'>Mammillary bodies: two memory systems in one (SUB -&gt; MMB, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLAC.md'>LAC</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1D.md'>FMM.FT.HC.CA1D</a> </td><td> <a href='BrainRegionLAC_FD_HT_PO.md'>LAC.FD.HT.PO</a> </td><td> Preoptic Nucleus   </td><td> allocortex-nucleus </td><td> <a href='http://www.nature.com/nrn/journal/v5/n7'>Feeling (HC -&gt; HT, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FT_HF_SUBP.md'>FMM.FT.HF.SUBP</a> </td><td> <a href='BrainRegionLAC_FD_HT_AH.md'>LAC.FD.HT.AH</a> </td><td> Anterior Hypothalamic Nucleus </td><td> allocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLAC_FD_HT_VM.md'>LAC.FD.HT.VM</a> </td><td> Ventromedial Hypothalamic Nucleus </td><td> allocortex-nucleus </td><td> (unknown reference) </td></tr></tbody></table>

<h2>Creating Fields</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/FMM_MMAHCF.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionFMM_FT_HC_CA2.md'>FMM.FT.HC.CA2</a> </td><td> Dorsolateral Cornu Ammonis of Hippocampus </td><td> cortex      </td><td> FMU            </td><td> Gate controlled by the activity of the supramammillary nucleus to control signal<br>
<br>
<BR><br>
<br>
propagation between HC lamines </td><td> Hippocampus. Receives theta rithm input from Septum<br>
<br>
<BR><br>
<br>
Nucleus; the only SUM projection in rat, the only<br>
<br>
<BR><br>
<br>
converge from ET L2 and L3; social memory </td></tr>
<tr><td> <a href='BrainRegionFMM_FT_HC_DG.md'>FMM.FT.HC.DG</a> </td><td> Dentate Gyrus         </td><td> cortex      </td><td> FMU            </td><td> Distinguishing multiple instances of similar events </td><td>                 </td></tr></tbody></table>

<b>Internal Region Connections:</b>
<ul><li>no connections</li></ul>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA2.md'>FMM.FT.HC.CA2</a> </td><td> <a href='BrainRegionFAM_FT_SEP_DBB.md'>FAM.FT.SEP.DBB</a> </td><td> Diagonal Band of Broca </td><td> nucleus-allocortex-gaba </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html'>Medial mammillary nucleus and theta rhythm (SEP -&gt; HF, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA2.md'>FMM.FT.HC.CA2</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA3D.md'>FMM.FT.HC.CA3D</a> </td><td> Distal CA1 of Hippocampus </td><td> allocortex-allocortex-gaba </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1571064507000243'>KIV model of cortico-hippocampal formation with subcortical projections for motor actions (CA3 -&gt; CA2, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HC_CA3M.md'>FMM.FT.HC.CA3M</a> </td><td> Middle CA1 of Hippocampus </td><td> allocortex-allocortex-gaba </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1571064507000243'>KIV model of cortico-hippocampal formation with subcortical projections for motor actions (CA3 -&gt; CA2, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HC_CA3P.md'>FMM.FT.HC.CA3P</a> </td><td> Proximal CA1 of Hippocampus </td><td> allocortex-allocortex-gaba </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1571064507000243'>KIV model of cortico-hippocampal formation with subcortical projections for motor actions (CA3 -&gt; CA2, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> Lateral Entorhinal Cortex </td><td> neocortex-allocortex </td><td> <a href='http://www.surgicalneurologyint.com/article.asp?issn=2152-7806;year=2012;volume=3;issue=2;spage=40;epage=46;aulast=Langevin'>Amygdala and its network (EC -&gt; HC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_MEC.md'>FMM.NC.PH.MEC</a> </td><td> Medial Entorhinal Cortex </td><td> neocortex-allocortex </td><td> <a href='http://www.surgicalneurologyint.com/article.asp?issn=2152-7806;year=2012;volume=3;issue=2;spage=40;epage=46;aulast=Langevin'>Amygdala and its network (EC -&gt; HC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FT_HC_DG.md'>FMM.FT.HC.DG</a> </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> Lateral Entorhinal Cortex </td><td> neocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (ET -&gt; DG, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_MEC.md'>FMM.NC.PH.MEC</a> </td><td> Medial Entorhinal Cortex </td><td> neocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (ET -&gt; DG, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_PER.md'>FMM.NC.PH.PER</a> </td><td> Perirhinal Cortex  </td><td> neocortex-allocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0149763401000215'>Gustatory sensory system of rat and macaque (PrC -&gt; HF, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLAC.md'>LAC</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA2.md'>FMM.FT.HC.CA2</a> </td><td> <a href='BrainRegionLAC_FD_HT_SUM.md'>LAC.FD.HT.SUM</a> </td><td> Supramammillary Nucleus </td><td> nucleus-allocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html'>Medial mammillary nucleus and theta rhythm (SupraMM -&gt; HF, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FT_HC_DG.md'>FMM.FT.HC.DG</a> </td><td> <a href='BrainRegionLAC_FD_HT_PN.md'>LAC.FD.HT.PN</a> </td><td> Posterior Hypothalamic Nucleus </td><td> nucleus-allocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLAC_FD_HT_SUM.md'>LAC.FD.HT.SUM</a> </td><td> Supramammillary Nucleus </td><td> nucleus-allocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html'>Medial mammillary nucleus and theta rhythm (SupraMM -&gt; HF, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLRC.md'>LRC</a> </td><td> <a href='BrainRegionFMM_FT_HC_DG.md'>FMM.FT.HC.DG</a> </td><td> <a href='BrainRegionLRC_HP_PN_SC.md'>LRC.HP.PN.SC</a> </td><td> Nucleus Subceruleus </td><td> nucleus-allocortex </td><td> (unknown reference) </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA2.md'>FMM.FT.HC.CA2</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1D.md'>FMM.FT.HC.CA1D</a> </td><td> Distal CA1 of Hippocampus </td><td> allocortex-allocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S030645220600755X'>Flow of impulses in hippocampal region (CA2 -&gt; CA1, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HC_CA1M.md'>FMM.FT.HC.CA1M</a> </td><td> Middle CA1 of Hippocampus </td><td> allocortex-allocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S030645220600755X'>Flow of impulses in hippocampal region (CA2 -&gt; CA1, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HC_CA1P.md'>FMM.FT.HC.CA1P</a> </td><td> Proximal CA1 of Hippocampus </td><td> allocortex-allocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S030645220600755X'>Flow of impulses in hippocampal region (CA2 -&gt; CA1, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FT_HC_DG.md'>FMM.FT.HC.DG</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA3D.md'>FMM.FT.HC.CA3D</a> </td><td> Distal CA1 of Hippocampus </td><td> allocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (DG -&gt; CA3, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HC_CA3M.md'>FMM.FT.HC.CA3M</a> </td><td> Middle CA1 of Hippocampus </td><td> allocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (DG -&gt; CA3, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HC_CA3P.md'>FMM.FT.HC.CA3P</a> </td><td> Proximal CA1 of Hippocampus </td><td> allocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (DG -&gt; CA3, abstract)</a> </td></tr></tbody></table>

<h2>Spatial Hippocampus</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/FMM_MMAHCS.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionFMM_FT_HC_CA1P.md'>FMM.FT.HC.CA1P</a> </td><td> Proximal CA1 of Hippocampus </td><td> cortex      </td><td> FMU            </td><td> Long-term memory, spatial </td><td>                 </td></tr>
<tr><td> <a href='BrainRegionFMM_FT_HC_CA3D.md'>FMM.FT.HC.CA3D</a> </td><td> Distal CA1 of Hippocampus </td><td> cortex      </td><td> FMU            </td><td> Representing sequences of episodic memory, motivational </td><td>                 </td></tr>
<tr><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> Distal Subiculum      </td><td> cortex      </td><td> FMU            </td><td> Providing coarse representation of space </td><td>                 </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionFMM_FT_HC_CA1P.md'>FMM.FT.HC.CA1P</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> allocortex-allocortex </td><td> <a href='http://learnmem.cshlp.org/content/14/11/714/F1.expansion'>Attractor Network in Hippocampus (CA1 -&gt; SUB, abstract)</a> </td></tr>
<tr><td> <a href='BrainRegionFMM_FT_HC_CA3D.md'>FMM.FT.HC.CA3D</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1P.md'>FMM.FT.HC.CA1P</a> </td><td> allocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (CA3 -&gt; CA1, abstract)</a> </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1P.md'>FMM.FT.HC.CA1P</a> </td><td> <a href='BrainRegionNCP_NC_MPL_PSCG.md'>NCP.NC.MPL.PSCG</a> </td><td> Posterior Cingulate Cortex </td><td> neocortex-allocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n7'>Feeling (CG -&gt; HC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FT_HC_CA3D.md'>FMM.FT.HC.CA3D</a> </td><td> <a href='BrainRegionNCP_NC_MPL_RSC.md'>NCP.NC.MPL.RSC</a> </td><td> Retrosplenial Cortex </td><td> neocortex-allocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in emotional behavior (PCA -&gt; HCA, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA3D.md'>FMM.FT.HC.CA3D</a> </td><td> <a href='BrainRegionNPE_NC_IPL_MST.md'>NPE.NC.IPL.MST</a> </td><td> Medial Superior Temporal Area </td><td> neocortex-allocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0149763409002061'>Contribution of hippocampal region CA3 to consciousness (IPL -&gt; CA1, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1P.md'>FMM.FT.HC.CA1P</a> </td><td> <a href='BrainRegionFMM_FD_TH_AV.md'>FMM.FD.TH.AV</a> </td><td> Anteroventral Nucleus </td><td> nucleus-allocortex </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (AN -&gt; HC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FD_TH_LD.md'>FMM.FD.TH.LD</a> </td><td> Lateral Dorsal Nucleus of Thalamus </td><td> nucleus-allocortex </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (LD -&gt; HC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HC_CA2.md'>FMM.FT.HC.CA2</a> </td><td> Dorsolateral Cornu Ammonis of Hippocampus </td><td> allocortex-allocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S030645220600755X'>Flow of impulses in hippocampal region (CA2 -&gt; CA1, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_MEC.md'>FMM.NC.PH.MEC</a> </td><td> Medial Entorhinal Cortex </td><td> neocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (ET -&gt; CA1, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FT_HC_CA3D.md'>FMM.FT.HC.CA3D</a> </td><td> <a href='BrainRegionFMM_FT_HC_DG.md'>FMM.FT.HC.DG</a> </td><td> Dentate Gyrus      </td><td> allocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (DG -&gt; CA3, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> <a href='BrainRegionFMM_NC_PH_POR.md'>FMM.NC.PH.POR</a> </td><td> Postrhinal Cortex  </td><td> neocortex-allocortex </td><td> (unknown reference) </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> <a href='BrainRegionNCP_NC_MPL_RSC.md'>NCP.NC.MPL.RSC</a> </td><td> Retrosplenial Cortex </td><td> allocortex-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v3/n2/fig_tab/nrn726_F3.html'>McNaughton Spatial Processing Network (SUB -&gt; PCGRSP, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCR.md'>NDM.NC.AL.ROFCR</a> </td><td> Most Rostral Orbitofrontal Cortex </td><td> allocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S030100820900183X'>Simplified model of hippocampal formation anatomy (SUB -&gt; mPFC, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA3D.md'>FMM.FT.HC.CA3D</a> </td><td> <a href='BrainRegionFAM_FT_SEP_SF.md'>FAM.FT.SEP.SF</a> </td><td> Septofimbrial Nucleus </td><td> allocortex-nucleus </td><td> <a href='http://www.thebrainlabs.com'>Cingulate Gyrus (HC -&gt; SEP, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> <a href='BrainRegionFAM_FT_AM_AB.md'>FAM.FT.AM.AB</a> </td><td> Accessory Basal Amygdaloid Nucleus </td><td> allocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S030100820900183X'>Simplified model of hippocampal formation anatomy (SUB -&gt; Amyg, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFAM_FT_SEP_TR.md'>FAM.FT.SEP.TR</a> </td><td> Triangular Septal Nucleus </td><td> allocortex-nucleus </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html'>Medial mammillary nucleus and theta rhythm (HF -&gt; SEP, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> <a href='BrainRegionFEC_FT_ACC_CORE.md'>FEC.FT.ACC.CORE</a> </td><td> Nucleus Accumbens Core </td><td> allocortex-nucleus </td><td> <a href='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/nucleus-accumbens.jpg'>Nucleus Accumbens (SUB -&gt; NACC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1P.md'>FMM.FT.HC.CA1P</a> </td><td> <a href='BrainRegionFMM_NC_PH_PAS.md'>FMM.NC.PH.PAS</a> </td><td> Parasubiculum      </td><td> allocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_POR.md'>FMM.NC.PH.POR</a> </td><td> Postrhinal Cortex  </td><td> allocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0149763411001722'>Entorhinal Cortex Inputs and Outputs (CA1 -&gt; TFTH, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FT_HC_CA3D.md'>FMM.FT.HC.CA3D</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA2.md'>FMM.FT.HC.CA2</a> </td><td> Dorsolateral Cornu Ammonis of Hippocampus </td><td> allocortex-allocortex-gaba </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1571064507000243'>KIV model of cortico-hippocampal formation with subcortical projections for motor actions (CA3 -&gt; CA2, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> <a href='BrainRegionFMM_FD_MB_MMB.md'>FMM.FD.MB.MMB</a> </td><td> Medial Mammillary Nucleus </td><td> allocortex-nucleus </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html'>Mammillary bodies: two memory systems in one (SUB -&gt; MMB, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FD_TH_AV.md'>FMM.FD.TH.AV</a> </td><td> Anteroventral Nucleus </td><td> allocortex-nucleus </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (s1A -&gt; A, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FD_TH_LD.md'>FMM.FD.TH.LD</a> </td><td> Lateral Dorsal Nucleus of Thalamus </td><td> allocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (Sub -&gt; LD, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> Lateral Entorhinal Cortex </td><td> allocortex-neocortex </td><td> <a href='http://learnmem.cshlp.org/content/14/11/714/F1.expansion'>Attractor Network in Hippocampus (SUB -&gt; EC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_MEC.md'>FMM.NC.PH.MEC</a> </td><td> Medial Entorhinal Cortex </td><td> allocortex-neocortex </td><td> <a href='http://learnmem.cshlp.org/content/14/11/714/F1.expansion'>Attractor Network in Hippocampus (SUB -&gt; EC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_POS.md'>FMM.NC.PH.POS</a> </td><td> Postsubiculum      </td><td> allocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/2009-Hippocampus-Thesis.pdf'>Hippocampal Formation (Sub -&gt; PoS, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_PRS.md'>FMM.NC.PH.PRS</a> </td><td> Presubiculum       </td><td> allocortex-neocortex </td><td> <a href='http://learnmem.cshlp.org/content/14/11/714/F1.expansion'>Attractor Network in Hippocampus (SUB -&gt; PRESUB, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLAC.md'>LAC</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> <a href='BrainRegionLAC_FD_HT_PV.md'>LAC.FD.HT.PV</a> </td><td> Paraventricular Nucleus </td><td> allocortex-nucleus </td><td> (unknown reference) </td></tr></tbody></table>

<h2>Thalamic Hippocampus</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/FMM_MMAHCT.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionFMM_FD_TH_RE.md'>FMM.FD.TH.RE</a> </td><td> Reuniens Nucleus of Thalamus </td><td> nucleus     </td><td> FMU            </td><td> Gate information between OMPFC and HC dependent upon attentive/arousal states </td><td> Regulate amount of neural traffic with changes in<br>
<br>
<BR><br>
<br>
attentiveness </td></tr>
<tr><td> <a href='BrainRegionFMM_FT_HC_CA1M.md'>FMM.FT.HC.CA1M</a> </td><td> Middle CA1 of Hippocampus </td><td> cortex      </td><td> FMU            </td><td> Long-term memory, synchronize </td><td>                 </td></tr>
<tr><td> <a href='BrainRegionFMM_FT_HC_CA3M.md'>FMM.FT.HC.CA3M</a> </td><td> Middle CA1 of Hippocampus </td><td> cortex      </td><td> FMU            </td><td> Representing sequences of episodic memory, synchronize </td><td>                 </td></tr>
<tr><td> <a href='BrainRegionFMM_FT_HF_SUBM.md'>FMM.FT.HF.SUBM</a> </td><td> Middle Subiculum      </td><td> cortex      </td><td> FMU            </td><td> Dynamic bridging of temporal intervals </td><td>                 </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionFMM_FD_TH_RE.md'>FMM.FD.TH.RE</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1M.md'>FMM.FT.HC.CA1M</a> </td><td> nucleus-allocortex </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (MID -&gt; HC, abstract)</a> </td></tr>
<tr><td> <a href='BrainRegionFMM_FT_HC_CA1M.md'>FMM.FT.HC.CA1M</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBM.md'>FMM.FT.HF.SUBM</a> </td><td> allocortex-allocortex </td><td> <a href='http://learnmem.cshlp.org/content/14/11/714/F1.expansion'>Attractor Network in Hippocampus (CA1 -&gt; SUB, abstract)</a> </td></tr>
<tr><td> <a href='BrainRegionFMM_FT_HC_CA3M.md'>FMM.FT.HC.CA3M</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1M.md'>FMM.FT.HC.CA1M</a> </td><td> allocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (CA3 -&gt; CA1, abstract)</a> </td></tr>
<tr><td> <a href='BrainRegionFMM_FT_HF_SUBM.md'>FMM.FT.HF.SUBM</a> </td><td> <a href='BrainRegionFMM_FD_TH_RE.md'>FMM.FD.TH.RE</a> </td><td> allocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (Sub -&gt; MID, abstract)</a> </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionFMM_FD_TH_RE.md'>FMM.FD.TH.RE</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCR.md'>NDM.NC.AL.ROFCR</a> </td><td> Most Rostral Orbitofrontal Cortex </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionFMM_FD_TH_RE.md'>FMM.FD.TH.RE</a> </td><td> <a href='BrainRegionFAM_FT_AM_MPV.md'>FAM.FT.AM.MPV</a> </td><td> Medial Posteror Ventral Amygdaloid Nucleus </td><td> nucleus-nucleus-gaba </td><td> <a href='http://www.springerimages.com/Images/LifeSciences/1-10.1007_s00359-004-0565-9-0'>Oculomotor decision-making (AMYG -&gt; Thalamus, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1M.md'>FMM.FT.HC.CA1M</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA2.md'>FMM.FT.HC.CA2</a> </td><td> Dorsolateral Cornu Ammonis of Hippocampus </td><td> allocortex-allocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S030645220600755X'>Flow of impulses in hippocampal region (CA2 -&gt; CA1, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FT_HC_CA3M.md'>FMM.FT.HC.CA3M</a> </td><td> <a href='BrainRegionFMM_FT_HC_DG.md'>FMM.FT.HC.DG</a> </td><td> Dentate Gyrus      </td><td> allocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (DG -&gt; CA3, abstract)</a> </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBM.md'>FMM.FT.HF.SUBM</a> </td><td> <a href='BrainRegionNCP_FD_TH_AM.md'>NCP.FD.TH.AM</a> </td><td> Anteromedial Nucleus </td><td> allocortex-nucleus </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (s1A -&gt; A, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA3M.md'>FMM.FT.HC.CA3M</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA2.md'>FMM.FT.HC.CA2</a> </td><td> Dorsolateral Cornu Ammonis of Hippocampus </td><td> allocortex-allocortex-gaba </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1571064507000243'>KIV model of cortico-hippocampal formation with subcortical projections for motor actions (CA3 -&gt; CA2, abstract)</a> </td></tr></tbody></table>

<h2>Orienting Control</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/FMM_MMAORIENT.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionFMM_FD_MB_LMB.md'>FMM.FD.MB.LMB</a> </td><td> Lateral Mammillary Nucleus </td><td> nucleus     </td><td> FMU            </td><td> Generate theta rythm and relay to HC </td><td> Memory, recognition, spatial awareness, and<br>
<br>
<BR><br>
<br>
interpreting the context of events </td></tr>
<tr><td> <a href='BrainRegionFMM_FD_TH_AD.md'>FMM.FD.TH.AD</a> </td><td> Anterodorsal Nucleus  </td><td> nucleus     </td><td> NPU            </td><td> head direction, spatial learning and memory </td><td>                 </td></tr>
<tr><td> <a href='BrainRegionFMM_NC_PH_POS.md'>FMM.NC.PH.POS</a> </td><td> Postsubiculum         </td><td> cortex, BA 48 </td><td> FMU            </td><td> Visual association </td><td> Detached dorsal part of presubiculum; Integrate<br>
<br>
<BR><br>
<br>
visual landmarks with internal representations of<br>
<br>
<BR><br>
<br>
environments </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionFMM_FD_MB_LMB.md'>FMM.FD.MB.LMB</a> </td><td> <a href='BrainRegionFMM_FD_TH_AD.md'>FMM.FD.TH.AD</a> </td><td> nucleus-nucleus </td><td> <a href='http://www.scholarpedia.org/article/Head_direction_cells'>Head Direction Cell Circuit (LMB -&gt; AD)</a> </td></tr>
<tr><td> <a href='BrainRegionFMM_FD_TH_AD.md'>FMM.FD.TH.AD</a> </td><td> <a href='BrainRegionFMM_NC_PH_POS.md'>FMM.NC.PH.POS</a> </td><td> nucleus-neocortex </td><td> <a href='http://www.scholarpedia.org/article/Head_direction_cells'>Head Direction Cell Circuit (AD -&gt; PSUB)</a> </td></tr>
<tr><td> <a href='BrainRegionFMM_NC_PH_POS.md'>FMM.NC.PH.POS</a> </td><td> <a href='BrainRegionFMM_FD_MB_LMB.md'>FMM.FD.MB.LMB</a> </td><td> neocortex-nucleus </td><td> <a href='http://www.scholarpedia.org/article/Head_direction_cells'>Head Direction Cell Circuit (PSUB -&gt; LMB)</a> </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionFMM_FD_TH_AD.md'>FMM.FD.TH.AD</a> </td><td> <a href='BrainRegionNCP_NC_MPL_RSC.md'>NCP.NC.MPL.RSC</a> </td><td> Retrosplenial Cortex </td><td> neocortex-nucleus </td><td> <a href='http://www.scholarpedia.org/article/Head_direction_cells'>Head Direction Cell Circuit (RSP -&gt; AD)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_POS.md'>FMM.NC.PH.POS</a> </td><td> <a href='BrainRegionNCP_NC_MPL_RSC.md'>NCP.NC.MPL.RSC</a> </td><td> Retrosplenial Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.scholarpedia.org/article/Head_direction_cells'>Head Direction Cell Circuit (RSP -&gt; PSUB)</a> </td></tr>
<tr><td> <a href='BrainAreaNSA.md'>NSA</a> </td><td> <a href='BrainRegionFMM_NC_PH_POS.md'>FMM.NC.PH.POS</a> </td><td> <a href='BrainRegionNSA_NC_OCC_V2TK.md'>NSA.NC.OCC.V2TK</a> </td><td> Secondary Visual Cortex, Thick Stripe </td><td> neocortex-neocortex </td><td> <a href='http://www.scholarpedia.org/article/Head_direction_cells'>Head Direction Cell Circuit (VC -&gt; PSUB, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionFMM_FD_MB_LMB.md'>FMM.FD.MB.LMB</a> </td><td> <a href='BrainRegionFAM_FT_SEP_MED.md'>FAM.FT.SEP.MED</a> </td><td> Medial Septal Nucleus </td><td> nucleus-nucleus-ACh </td><td> <a href='http://www.thebrainlabs.com'>Cingulate Gyrus (SEP -&gt; HT, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_FD_MB_LMB.md'>FMM.FD.MB.LMB</a> </td><td> <a href='BrainRegionFMM_NC_PH_PAS.md'>FMM.NC.PH.PAS</a> </td><td> Parasubiculum      </td><td> neocortex-nucleus </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html'>Mammillary bodies: two memory systems in one (PAS -&gt; LMB)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_PRS.md'>FMM.NC.PH.PRS</a> </td><td> Presubiculum       </td><td> neocortex-nucleus </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html'>Mammillary bodies: two memory systems in one (PRS -&gt; LMB)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_POS.md'>FMM.NC.PH.POS</a> </td><td> <a href='BrainRegionFMM_FD_TH_LD.md'>FMM.FD.TH.LD</a> </td><td> Lateral Dorsal Nucleus of Thalamus </td><td> nucleus-neocortex </td><td> <a href='http://www.scholarpedia.org/article/Head_direction_cells'>Head Direction Cell Circuit (LD -&gt; PSUB)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> Distal Subiculum   </td><td> allocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/2009-Hippocampus-Thesis.pdf'>Hippocampal Formation (Sub -&gt; PoS, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLAC.md'>LAC</a> </td><td> <a href='BrainRegionFMM_FD_MB_LMB.md'>FMM.FD.MB.LMB</a> </td><td> <a href='BrainRegionLAC_FD_HT_LTN.md'>LAC.FD.HT.LTN</a> </td><td> Lateral Hypothalamic Nucleus </td><td> nucleus-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLAC_FD_HT_PN.md'>LAC.FD.HT.PN</a> </td><td> Posterior Hypothalamic Nucleus </td><td> nucleus-nucleus </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainAreaLMC.md'>LMC</a> </td><td> <a href='BrainRegionFMM_FD_MB_LMB.md'>FMM.FD.MB.LMB</a> </td><td> <a href='BrainRegionLMC_HP_TG_DTG.md'>LMC.HP.TG.DTG</a> </td><td> Dorsal Tegmental Nucleus </td><td> nucleus-nucleus-ACh </td><td> (unknown reference) </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_NC_PH_POS.md'>FMM.NC.PH.POS</a> </td><td> <a href='BrainRegionFMM_NC_PH_MEC.md'>FMM.NC.PH.MEC</a> </td><td> Medial Entorhinal Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.scholarpedia.org/article/Head_direction_cells'>Head Direction Cell Circuit (PSUB -&gt; EC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLLC.md'>LLC</a> </td><td> <a href='BrainRegionFMM_FD_MB_LMB.md'>FMM.FD.MB.LMB</a> </td><td> <a href='BrainRegionLLC_HP_PRF_PDT.md'>LLC.HP.PRF.PDT</a> </td><td> Pontine Reticulotegmental Nucleus </td><td> nucleus-nucleus </td><td> <a href='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/mb.jpg'>Mammillary Body (LMB -&gt; RTG)</a> </td></tr>
<tr><td> <a href='BrainAreaLMC.md'>LMC</a> </td><td> <a href='BrainRegionFMM_FD_MB_LMB.md'>FMM.FD.MB.LMB</a> </td><td> <a href='BrainRegionLMC_HP_TG_LDT.md'>LMC.HP.TG.LDT</a> </td><td> Laterodorsal Tegmental Nucleus </td><td> nucleus-nucleus </td><td> <a href='http://www.scholarpedia.org/article/Head_direction_cells'>Head Direction Cell Circuit (LMB -&gt; DTN)</a> </td></tr></tbody></table>

<h2>Emotional Sensory Input to Hippocampus</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/FMM_MMASENSE.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> Lateral Entorhinal Cortex </td><td> cortex, BA 28 </td><td> FMU            </td><td> Memory consolidation, emotioncal aspects </td><td> non-spatial input to HC; process information about<br>
<br>
<BR><br>
<br>
individual items and locations based on a local<br>
<br>
<BR><br>
<br>
frame of reference, primarily using external<br>
<br>
<BR><br>
<br>
sensory input; it provides the hippocampus with<br>
<br>
<BR><br>
<br>
information about content of experience </td></tr>
<tr><td> <a href='BrainRegionFMM_NC_PH_PER.md'>FMM.NC.PH.PER</a> </td><td> Perirhinal Cortex     </td><td> cortex, BA 35,36 </td><td> FMU            </td><td> Associate different visual views of objects and their various nonvisual<br>
<br>
<BR><br>
<br>
attributes </td><td>                 </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionFMM_NC_PH_PER.md'>FMM.NC.PH.PER</a> </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> neocortex-neocortex </td><td> <a href='http://www.scholarpedia.org/article/Inferior_temporal_cortex'>Visual Path to Hippocampus (PRPH -&gt; ER, abstract)</a> </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionFMM_NC_PH_PER.md'>FMM.NC.PH.PER</a> </td><td> <a href='BrainRegionNCP_NC_INS_AIC.md'>NCP.NC.INS.AIC</a> </td><td> Anterior Insular Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0149763401000215'>Gustatory sensory system of rat and macaque (Iav -&gt; PrC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNCP_NC_INS_HR.md'>NCP.NC.INS.HR</a> </td><td> Anterior Temporal Lobe </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0149763409002061'>Contribution of hippocampal region CA3 to consciousness (AnteriorTemporal -&gt; PRCortex)</a> </td></tr>
<tr><td> <a href='BrainAreaNSA.md'>NSA</a> </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> <a href='BrainRegionNSA_NC_IT_TE.md'>NSA.NC.IT.TE</a> </td><td> Inferotemporal Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v3/n2/fig_tab/nrn726_F3.html'>McNaughton Spatial Processing Network (ITCortex -&gt; EnthCortex, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_PH_PIR.md'>NSA.NC.PH.PIR</a> </td><td> Piriform Cortex    </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1571064507000243'>KIV model of cortico-hippocampal formation with subcortical projections for motor actions (PC -&gt; EC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_STG_A3.md'>NSA.NC.STG.A3</a> </td><td> Wernicke's area A3 </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_STG_A4.md'>NSA.NC.STG.A4</a> </td><td> Wernicke's area A4 </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_PER.md'>FMM.NC.PH.PER</a> </td><td> <a href='BrainRegionNSA_NC_IT_TE.md'>NSA.NC.IT.TE</a> </td><td> Inferotemporal Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.scholarpedia.org/article/Inferior_temporal_cortex'>Visual Path to Hippocampus (IT -&gt; PRPH)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_PG_PV.md'>NSA.NC.PG.PV</a> </td><td> Parietal Ventral Cortex </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> <a href='BrainRegionFAM_FD_TH_PT.md'>FAM.FD.TH.PT</a> </td><td> Paratenial Nucleus of Thalamus </td><td> nucleus-neocortex </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (MID -&gt; EC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFAM_FT_AM_BP.md'>FAM.FT.AM.BP</a> </td><td> Parvicellular Basal Amygdaloid Nucleus </td><td> nucleus-neocortex </td><td> <a href='http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.html'>Principal Connections of Hippocampus (AM -&gt; EC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_PER.md'>FMM.NC.PH.PER</a> </td><td> <a href='BrainRegionFAM_HP_NI.md'>FAM.HP.NI</a> </td><td> Incertus Nucleus   </td><td> nucleus-neocortex-gaba </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> Distal Subiculum   </td><td> allocortex-neocortex </td><td> <a href='http://learnmem.cshlp.org/content/14/11/714/F1.expansion'>Attractor Network in Hippocampus (SUB -&gt; EC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLMC.md'>LMC</a> </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> <a href='BrainRegionLMC_MM_VTA.md'>LMC.MM.VTA</a> </td><td> Ventral Tegmental Area </td><td> nucleus-neocortex-DA </td><td> <a href='http://www.impulsecontroldisorders.org/html/cravings.html'>Combining Novelty, Motivational Salience, and Reward to Control Attention and Learning (VTA -&gt; EC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLPC.md'>LPC</a> </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> <a href='BrainRegionLPC_FD_TH_PV.md'>LPC.FD.TH.PV</a> </td><td> Paraventricular Nucleus of Thalamus </td><td> nucleus-neocortex </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (MID -&gt; EC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_PER.md'>FMM.NC.PH.PER</a> </td><td> <a href='BrainRegionLPC_FD_TH_PV.md'>LPC.FD.TH.PV</a> </td><td> Paraventricular Nucleus of Thalamus </td><td> nucleus-neocortex </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (MID -&gt; Perirhinal, abstract)</a> </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> <a href='BrainRegionNDM_FD_TH_MDM.md'>NDM.FD.TH.MDM</a> </td><td> Medial Mediodorsal Nucleus of Thalamus </td><td> neocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (EC -&gt; MDmc, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_PER.md'>FMM.NC.PH.PER</a> </td><td> <a href='BrainRegionNDM_FD_TH_MDM.md'>NDM.FD.TH.MDM</a> </td><td> Medial Mediodorsal Nucleus of Thalamus </td><td> neocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (Perirhinal -&gt; MDmc, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionFMM_NC_PH_PER.md'>FMM.NC.PH.PER</a> </td><td> <a href='BrainRegionNPE_FD_TH_MPV.md'>NPE.FD.TH.MPV</a> </td><td> Medial Pulvinar    </td><td> neocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (Perirhinal -&gt; mPULV)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> <a href='BrainRegionFAM_FT_AM_AB.md'>FAM.FT.AM.AB</a> </td><td> Accessory Basal Amygdaloid Nucleus </td><td> neocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S030100820900183X'>Simplified model of hippocampal formation anatomy (EC -&gt; Amyg, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> <a href='BrainRegionFEC_FT_ACC_CORE.md'>FEC.FT.ACC.CORE</a> </td><td> Nucleus Accumbens Core </td><td> neocortex-nucleus </td><td> <a href='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/nucleus-accumbens.jpg'>Nucleus Accumbens (EC -&gt; NACC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_PER.md'>FMM.NC.PH.PER</a> </td><td> <a href='BrainRegionFEC_FT_ACC_CORE.md'>FEC.FT.ACC.CORE</a> </td><td> Nucleus Accumbens Core </td><td> neocortex-nucleus </td><td> <a href='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/nucleus-accumbens.jpg'>Nucleus Accumbens (PRR -&gt; NACC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_NC_PH_LEC.md'>FMM.NC.PH.LEC</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1D.md'>FMM.FT.HC.CA1D</a> </td><td> Distal CA1 of Hippocampus </td><td> neocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (ET -&gt; CA1, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HC_CA2.md'>FMM.FT.HC.CA2</a> </td><td> Dorsolateral Cornu Ammonis of Hippocampus </td><td> neocortex-allocortex </td><td> <a href='http://www.surgicalneurologyint.com/article.asp?issn=2152-7806;year=2012;volume=3;issue=2;spage=40;epage=46;aulast=Langevin'>Amygdala and its network (EC -&gt; HC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HC_DG.md'>FMM.FT.HC.DG</a> </td><td> Dentate Gyrus      </td><td> neocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (ET -&gt; DG, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HF_SUBP.md'>FMM.FT.HF.SUBP</a> </td><td> Proximal Subiculum </td><td> neocortex-allocortex </td><td> <a href='http://www.scholarpedia.org/article/Inferior_temporal_cortex'>Visual Path to Hippocampus (ER -&gt; H, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_PER.md'>FMM.NC.PH.PER</a> </td><td> <a href='BrainRegionFMM_FT_HC_DG.md'>FMM.FT.HC.DG</a> </td><td> Dentate Gyrus      </td><td> neocortex-allocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0149763401000215'>Gustatory sensory system of rat and macaque (PrC -&gt; HF, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HF_SUBP.md'>FMM.FT.HF.SUBP</a> </td><td> Proximal Subiculum </td><td> neocortex-allocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0149763401000215'>Gustatory sensory system of rat and macaque (PrC -&gt; HF, abstract)</a> </td></tr></tbody></table>

<h2>Spatial Sensory Input to Hippocampus</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/FMM_MMASENSS.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionFMM_NC_PH_MEC.md'>FMM.NC.PH.MEC</a> </td><td> Medial Entorhinal Cortex </td><td> cortex, BA 28 </td><td> FMU            </td><td> Memory consolidation, basic, view inpedepdent position </td><td> spatial input to HC; grid cells; path integration<br>
<br>
<BR><br>
<br>
computations based on a global frame of reference,<br>
<br>
<BR><br>
<br>
primarily using internally generated, self-motion<br>
<br>
<BR><br>
<br>
cues and external input about environmental<br>
<br>
<BR><br>
<br>
boundaries and scenes; provides hippocampus with<br>
<br>
<BR><br>
<br>
coordinate system that underlies spatial context of<br>
<br>
<BR><br>
<br>
experience </td></tr>
<tr><td> <a href='BrainRegionFMM_NC_PH_POR.md'>FMM.NC.PH.POR</a> </td><td> Postrhinal Cortex     </td><td> cortex, BA 29,30 </td><td> FMU            </td><td> Spatial declarative memory </td><td>                 </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionFMM_NC_PH_POR.md'>FMM.NC.PH.POR</a> </td><td> <a href='BrainRegionFMM_NC_PH_MEC.md'>FMM.NC.PH.MEC</a> </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0149763411001722'>Entorhinal Cortex Inputs and Outputs (TFTH -&gt; EC, abstract)</a> </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionFMM_NC_PH_MEC.md'>FMM.NC.PH.MEC</a> </td><td> <a href='BrainRegionNCP_NC_MPL_PSCG.md'>NCP.NC.MPL.PSCG</a> </td><td> Posterior Cingulate Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v3/n2/fig_tab/nrn726_F3.html'>McNaughton Spatial Processing Network (PCGRSP -&gt; EnthCortex, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNCP_NC_MPL_RSC.md'>NCP.NC.MPL.RSC</a> </td><td> Retrosplenial Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v3/n2/fig_tab/nrn726_F3.html'>McNaughton Spatial Processing Network (PCGRSP -&gt; EnthCortex, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionFMM_NC_PH_POR.md'>FMM.NC.PH.POR</a> </td><td> <a href='BrainRegionNPE_NC_IPL_MST.md'>NPE.NC.IPL.MST</a> </td><td> Medial Superior Temporal Area </td><td> neocortex-neocortex </td><td> <a href='http://www.scholarpedia.org/article/Head_direction_cells'>Head Direction Cell Circuit (PC -&gt; PRHC, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_NC_PH_MEC.md'>FMM.NC.PH.MEC</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> Distal Subiculum   </td><td> allocortex-neocortex </td><td> <a href='http://learnmem.cshlp.org/content/14/11/714/F1.expansion'>Attractor Network in Hippocampus (SUB -&gt; EC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_PAS.md'>FMM.NC.PH.PAS</a> </td><td> Parasubiculum      </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_POS.md'>FMM.NC.PH.POS</a> </td><td> Postsubiculum      </td><td> neocortex-neocortex </td><td> <a href='http://www.scholarpedia.org/article/Head_direction_cells'>Head Direction Cell Circuit (PSUB -&gt; EC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_PRS.md'>FMM.NC.PH.PRS</a> </td><td> Presubiculum       </td><td> neocortex-neocortex </td><td> <a href='http://learnmem.cshlp.org/content/14/11/714/F1.expansion'>Attractor Network in Hippocampus (PRESUB -&gt; EC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_POR.md'>FMM.NC.PH.POR</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1P.md'>FMM.FT.HC.CA1P</a> </td><td> Proximal CA1 of Hippocampus </td><td> allocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0149763411001722'>Entorhinal Cortex Inputs and Outputs (CA1 -&gt; TFTH, abstract)</a> </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_NC_PH_MEC.md'>FMM.NC.PH.MEC</a> </td><td> <a href='BrainRegionFMM_FD_MB_MMB.md'>FMM.FD.MB.MMB</a> </td><td> Medial Mammillary Nucleus </td><td> neocortex-nucleus </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html'>Mammillary bodies: two memory systems in one (MedialEC -&gt; MMB, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FD_TH_LD.md'>FMM.FD.TH.LD</a> </td><td> Lateral Dorsal Nucleus of Thalamus </td><td> neocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (EC -&gt; LD, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HC_CA1P.md'>FMM.FT.HC.CA1P</a> </td><td> Proximal CA1 of Hippocampus </td><td> neocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (ET -&gt; CA1, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HC_CA2.md'>FMM.FT.HC.CA2</a> </td><td> Dorsolateral Cornu Ammonis of Hippocampus </td><td> neocortex-allocortex </td><td> <a href='http://www.surgicalneurologyint.com/article.asp?issn=2152-7806;year=2012;volume=3;issue=2;spage=40;epage=46;aulast=Langevin'>Amygdala and its network (EC -&gt; HC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HC_DG.md'>FMM.FT.HC.DG</a> </td><td> Dentate Gyrus      </td><td> neocortex-allocortex </td><td> <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Neuronal projections in the hippocampus (ET -&gt; DG, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_POR.md'>FMM.NC.PH.POR</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> Distal Subiculum   </td><td> neocortex-allocortex </td><td> (unknown reference) </td></tr></tbody></table>

<h2>Theta Waves Control</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/FMM_MMATHETA.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionFMM_FD_MB_MMB.md'>FMM.FD.MB.MMB</a> </td><td> Medial Mammillary Nucleus </td><td> nucleus     </td><td> FMU            </td><td> Relay for impulses coming from AM and HC </td><td> Memory, recognition, spatial awareness, and<br>
<br>
<BR><br>
<br>
interpreting the context of events </td></tr>
<tr><td> <a href='BrainRegionFMM_FD_TH_AV.md'>FMM.FD.TH.AV</a> </td><td> Anteroventral Nucleus </td><td> nucleus     </td><td> NPU            </td><td> return loop to convey theta to to HF, attentional processes </td><td>                 </td></tr>
<tr><td> <a href='BrainRegionFMM_FD_TH_LD.md'>FMM.FD.TH.LD</a> </td><td> Lateral Dorsal Nucleus of Thalamus </td><td> nucleus     </td><td> NPU            </td><td> Head direction, spatial learning </td><td> From RSP L5,6 BA17,18, RT, LGN </td></tr>
<tr><td> <a href='BrainRegionFMM_NC_PH_PAS.md'>FMM.NC.PH.PAS</a> </td><td> Parasubiculum         </td><td> cortex, BA 49 </td><td> FMU            </td><td> Spatial navigation and the integration of head-directional information </td><td> Major projects to ET, from CA1,AM </td></tr>
<tr><td> <a href='BrainRegionFMM_NC_PH_PRS.md'>FMM.NC.PH.PRS</a> </td><td> Presubiculum          </td><td> cortex, BA 27 </td><td> FMU            </td><td> Path integration, head direction </td><td> Major projects to ET, from TH.LD </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionFMM_FD_MB_MMB.md'>FMM.FD.MB.MMB</a> </td><td> <a href='BrainRegionFMM_FD_TH_AV.md'>FMM.FD.TH.AV</a> </td><td> nucleus-nucleus </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html'>Mammillary bodies: two memory systems in one (MMB -&gt; AVTH)</a> </td></tr>
<tr><td> <a href='BrainRegionFMM_FD_TH_AV.md'>FMM.FD.TH.AV</a> </td><td> <a href='BrainRegionFMM_NC_PH_PAS.md'>FMM.NC.PH.PAS</a> </td><td> nucleus-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                      </td><td> <a href='BrainRegionFMM_NC_PH_PRS.md'>FMM.NC.PH.PRS</a> </td><td> nucleus-neocortex </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainRegionFMM_NC_PH_PAS.md'>FMM.NC.PH.PAS</a> </td><td> <a href='BrainRegionFMM_FD_TH_LD.md'>FMM.FD.TH.LD</a> </td><td> neocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (Parasub -&gt; LD)</a> </td></tr>
<tr><td> <a href='BrainRegionFMM_NC_PH_PRS.md'>FMM.NC.PH.PRS</a> </td><td> <a href='BrainRegionFMM_FD_MB_MMB.md'>FMM.FD.MB.MMB</a> </td><td> neocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/14/11/714/F1.expansion'>Attractor Network in Hippocampus (PRESUB -&gt; MBIN)</a> </td></tr>
<tr><td>                      </td><td> <a href='BrainRegionFMM_FD_TH_LD.md'>FMM.FD.TH.LD</a> </td><td> neocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (Presub -&gt; LD)</a> </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionFMM_FD_TH_AV.md'>FMM.FD.TH.AV</a> </td><td> <a href='BrainRegionNCP_NC_MPL_RSC.md'>NCP.NC.MPL.RSC</a> </td><td> Retrosplenial Cortex </td><td> neocortex-nucleus </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html'>Medial mammillary nucleus and theta rhythm (RSP -&gt; AVTH)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FD_TH_LD.md'>FMM.FD.TH.LD</a> </td><td> <a href='BrainRegionNCP_NC_MPL_RSC.md'>NCP.NC.MPL.RSC</a> </td><td> Retrosplenial Cortex </td><td> neocortex-nucleus </td><td> <a href='http://www.scholarpedia.org/article/Head_direction_cells'>Head Direction Cell Circuit (RSP -&gt; LD)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_PRS.md'>FMM.NC.PH.PRS</a> </td><td> <a href='BrainRegionNCP_NC_INS_PPC.md'>NCP.NC.INS.PPC</a> </td><td> Peripaleocortical Claustral </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionFMM_FD_TH_LD.md'>FMM.FD.TH.LD</a> </td><td> <a href='BrainRegionNPE_NC_SPL_PF.md'>NPE.NC.SPL.PF</a> </td><td> Rostral Precuneus  </td><td> neocortex-nucleus </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (sLD -&gt; LD, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionFMM_FD_MB_MMB.md'>FMM.FD.MB.MMB</a> </td><td> <a href='BrainRegionFAM_FT_SEP_DBB.md'>FAM.FT.SEP.DBB</a> </td><td> Diagonal Band of Broca </td><td> nucleus-nucleus-gaba </td><td> <a href='http://www.thebrainlabs.com'>Cingulate Gyrus (SEP -&gt; HT, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFAM_FT_SEP_MED.md'>FAM.FT.SEP.MED</a> </td><td> Medial Septal Nucleus </td><td> nucleus-nucleus-gaba </td><td> <a href='http://www.thebrainlabs.com'>Cingulate Gyrus (SEP -&gt; HT, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_PAS.md'>FMM.NC.PH.PAS</a> </td><td> <a href='BrainRegionFAM_FT_AM_AB.md'>FAM.FT.AM.AB</a> </td><td> Accessory Basal Amygdaloid Nucleus </td><td> nucleus-neocortex </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_FD_MB_MMB.md'>FMM.FD.MB.MMB</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> Distal Subiculum   </td><td> allocortex-nucleus </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html'>Mammillary bodies: two memory systems in one (SUB -&gt; MMB, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_FT_HF_SUBP.md'>FMM.FT.HF.SUBP</a> </td><td> Proximal Subiculum </td><td> allocortex-nucleus </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html'>Mammillary bodies: two memory systems in one (SUB -&gt; MMB, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_MEC.md'>FMM.NC.PH.MEC</a> </td><td> Medial Entorhinal Cortex </td><td> neocortex-nucleus </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html'>Mammillary bodies: two memory systems in one (MedialEC -&gt; MMB, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FD_TH_AV.md'>FMM.FD.TH.AV</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> Distal Subiculum   </td><td> allocortex-nucleus </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (s1A -&gt; A, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FD_TH_LD.md'>FMM.FD.TH.LD</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> Distal Subiculum   </td><td> allocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (Sub -&gt; LD, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_MEC.md'>FMM.NC.PH.MEC</a> </td><td> Medial Entorhinal Cortex </td><td> neocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (EC -&gt; LD, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_PAS.md'>FMM.NC.PH.PAS</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1P.md'>FMM.FT.HC.CA1P</a> </td><td> Proximal CA1 of Hippocampus </td><td> allocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_PRS.md'>FMM.NC.PH.PRS</a> </td><td> <a href='BrainRegionFMM_FT_HF_SUBD.md'>FMM.FT.HF.SUBD</a> </td><td> Distal Subiculum   </td><td> allocortex-neocortex </td><td> <a href='http://learnmem.cshlp.org/content/14/11/714/F1.expansion'>Attractor Network in Hippocampus (SUB -&gt; PRESUB, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLAC.md'>LAC</a> </td><td> <a href='BrainRegionFMM_FD_MB_MMB.md'>FMM.FD.MB.MMB</a> </td><td> <a href='BrainRegionLAC_FD_HT_LTN.md'>LAC.FD.HT.LTN</a> </td><td> Lateral Hypothalamic Nucleus </td><td> nucleus-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLAC_FD_HT_PN.md'>LAC.FD.HT.PN</a> </td><td> Posterior Hypothalamic Nucleus </td><td> nucleus-nucleus </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainAreaLMC.md'>LMC</a> </td><td> <a href='BrainRegionFMM_FD_MB_MMB.md'>FMM.FD.MB.MMB</a> </td><td> <a href='BrainRegionLMC_HP_TG_VTG.md'>LMC.HP.TG.VTG</a> </td><td> Ventral Tegmental Nucleus </td><td> nucleus-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLMC_MM_RF_SUC.md'>LMC.MM.RF.SUC</a> </td><td> Superior Central Raphe Nucleus </td><td> nucleus-nucleus-5HT </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLMC_MM_VTA.md'>LMC.MM.VTA</a> </td><td> Ventral Tegmental Area </td><td> nucleus-nucleus-DA </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html'>Mammillary bodies: two memory systems in one (VTN -&gt; MMB)</a> </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionFMM_NC_PH_PRS.md'>FMM.NC.PH.PRS</a> </td><td> <a href='BrainRegionNPE_FD_TH_MPV.md'>NPE.FD.TH.MPV</a> </td><td> Medial Pulvinar    </td><td> neocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (Presub -&gt; mPULV)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionFMM_NC_PH_PAS.md'>FMM.NC.PH.PAS</a> </td><td> <a href='BrainRegionFEC_FT_ACC_CORE.md'>FEC.FT.ACC.CORE</a> </td><td> Nucleus Accumbens Core </td><td> neocortex-nucleus </td><td> <a href='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/nucleus-accumbens.jpg'>Nucleus Accumbens (PAS -&gt; NACC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionFMM_FD_TH_AV.md'>FMM.FD.TH.AV</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1P.md'>FMM.FT.HC.CA1P</a> </td><td> Proximal CA1 of Hippocampus </td><td> nucleus-allocortex </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (AN -&gt; HC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_FD_TH_LD.md'>FMM.FD.TH.LD</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA1P.md'>FMM.FT.HC.CA1P</a> </td><td> Proximal CA1 of Hippocampus </td><td> nucleus-allocortex </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (LD -&gt; HC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_POS.md'>FMM.NC.PH.POS</a> </td><td> Postsubiculum      </td><td> nucleus-neocortex </td><td> <a href='http://www.scholarpedia.org/article/Head_direction_cells'>Head Direction Cell Circuit (LD -&gt; PSUB)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_PAS.md'>FMM.NC.PH.PAS</a> </td><td> <a href='BrainRegionFMM_FD_MB_LMB.md'>FMM.FD.MB.LMB</a> </td><td> Lateral Mammillary Nucleus </td><td> neocortex-nucleus </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html'>Mammillary bodies: two memory systems in one (PAS -&gt; LMB)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_MEC.md'>FMM.NC.PH.MEC</a> </td><td> Medial Entorhinal Cortex </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionFMM_NC_PH_PRS.md'>FMM.NC.PH.PRS</a> </td><td> <a href='BrainRegionFMM_FD_MB_LMB.md'>FMM.FD.MB.LMB</a> </td><td> Lateral Mammillary Nucleus </td><td> neocortex-nucleus </td><td> <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html'>Mammillary bodies: two memory systems in one (PRS -&gt; LMB)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_MEC.md'>FMM.NC.PH.MEC</a> </td><td> Medial Entorhinal Cortex </td><td> neocortex-neocortex </td><td> <a href='http://learnmem.cshlp.org/content/14/11/714/F1.expansion'>Attractor Network in Hippocampus (PRESUB -&gt; EC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLLC.md'>LLC</a> </td><td> <a href='BrainRegionFMM_FD_MB_MMB.md'>FMM.FD.MB.MMB</a> </td><td> <a href='BrainRegionLLC_HP_PN_RP.md'>LLC.HP.PN.RP</a> </td><td> Rostral Pontine Nucleus </td><td> nucleus-nucleus </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in emotional behavior (HT -&gt; PN, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLLC_HP_PRF_PDT.md'>LLC.HP.PRF.PDT</a> </td><td> Pontine Reticulotegmental Nucleus </td><td> nucleus-nucleus </td><td> <a href='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/mb.jpg'>Mammillary Body (MMB -&gt; RTG)</a> </td></tr></tbody></table>

<h1>Thirdparty Circuits</h1>
(generated)<br>
<br>
<ul><li><a href='http://learnmem.cshlp.org/content/18/6/384/F1.large.jpg'>Contributions of Diencephalon to Recognition Memory</a> - see <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Reference</a></li></ul>

<img src='http://learnmem.cshlp.org/content/18/6/384/F1.large.jpg' alt='unavailable'>

<ul><li><a href='http://www.nature.com/nrn/journal/v5/n1/images/nrn1299-f2.jpg'>Mammillary bodies: two memory systems in one</a> - see <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html'>Reference</a></li></ul>

<img src='http://www.nature.com/nrn/journal/v5/n1/images/nrn1299-f2.jpg' alt='unavailable'>

<ul><li><a href='http://www.scholarpedia.org/w/images/6/63/Taube_Figure_5a.png'>Head Direction Cell Circuit</a> - see <a href='http://www.scholarpedia.org/article/Head_direction_cells'>Reference</a></li></ul>

<img src='http://www.scholarpedia.org/w/images/6/63/Taube_Figure_5a.png' alt='unavailable'>

<ul><li><a href='http://learnmem.cshlp.org/content/14/11/714/F1.large.jpg'>Attractor Network in Hippocampus</a> - see <a href='http://learnmem.cshlp.org/content/14/11/714/F1.expansion'>Reference</a></li></ul>

<img src='http://learnmem.cshlp.org/content/14/11/714/F1.large.jpg' alt='unavailable'>

<ul><li><a href='http://ahuman.googlecode.com/svn/images/wiki/research/brain/HF.jpg'>Hippocampal Formation</a> - see [article:2009-Hippocampus-Thesis.pdf Reference]</li></ul>

<img src='http://ahuman.googlecode.com/svn/images/wiki/research/brain/HF.jpg' alt='unavailable'>

<ul><li><a href='http://ars.els-cdn.com/content/image/1-s2.0-S030645220600755X-gr1.jpg'>Flow of impulses in hippocampal region</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S030645220600755X'>Reference</a></li></ul>

<img src='http://ars.els-cdn.com/content/image/1-s2.0-S030645220600755X-gr1.jpg' alt='unavailable'>

<ul><li><a href='http://ars.els-cdn.com/content/image/1-s2.0-S0149763409002061-gr1.jpg'>Contribution of hippocampal region CA3 to consciousness</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S0149763409002061'>Reference</a></li></ul>

<img src='http://ars.els-cdn.com/content/image/1-s2.0-S0149763409002061-gr1.jpg' alt='unavailable'>

<ul><li><a href='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/nucleus-accumbens.jpg'>Nucleus Accumbens</a> (unknown reference)</li></ul>

<img src='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/nucleus-accumbens.jpg' alt='unavailable'>

<ul><li><a href='http://ars.els-cdn.com/content/image/1-s2.0-S1571064507000243-gr008.jpg'>KIV model of cortico-hippocampal formation with subcortical projections for motor actions</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S1571064507000243'>Reference</a></li></ul>

<img src='http://ars.els-cdn.com/content/image/1-s2.0-S1571064507000243-gr008.jpg' alt='unavailable'>

<ul><li><a href='http://what-when-how.com/wp-content/uploads/2012/04/tmp3637_thumb.jpg'>Hippocampus in Detail</a> - see <a href='http://what-when-how.com/neuroscience/the-limbic-system-integrative-systems-part-1/'>Reference</a></li></ul>

<img src='http://what-when-how.com/wp-content/uploads/2012/04/tmp3637_thumb.jpg' alt='unavailable'>

<ul><li><a href='http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.gif'>Principal Connections of Hippocampus</a> - see <a href='http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.html'>Reference</a></li></ul>

<img src='http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.gif' alt='unavailable'>

<ul><li><a href='http://www.nature.com/nrn/journal/v5/n1/images/nrn1299-f4.jpg'>Medial mammillary nucleus and theta rhythm</a> - see <a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html'>Reference</a></li></ul>

<img src='http://www.nature.com/nrn/journal/v5/n1/images/nrn1299-f4.jpg' alt='unavailable'>

<ul><li><a href='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/mb.jpg'>Mammillary Body</a> (unknown reference)</li></ul>

<img src='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/mb.jpg' alt='unavailable'>

<ul><li><a href='http://media.wiley.com/mrw_images/compphys/articles/cp010508/image_n/ncp01050839.jpg'>Entorhinal Cortex Inputs and Outputs</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S0149763411001722'>Reference</a></li></ul>

<img src='http://media.wiley.com/mrw_images/compphys/articles/cp010508/image_n/ncp01050839.jpg' alt='unavailable'>

<ul><li><a href='http://www.scholarpedia.org/w/images/thumb/f/f2/ITCortex_pathway.jpg/400px-ITCortex_pathway.jpg'>Visual Path to Hippocampus</a> - see <a href='http://www.scholarpedia.org/article/Inferior_temporal_cortex'>Reference</a></li></ul>

<img src='http://www.scholarpedia.org/w/images/thumb/f/f2/ITCortex_pathway.jpg/400px-ITCortex_pathway.jpg' alt='unavailable'>

<ul><li><a href='http://ars.els-cdn.com/content/image/1-s2.0-S0149763401000215-gr4a.gif'>Gustatory sensory system of rat and macaque</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S0149763401000215'>Reference</a></li></ul>

<img src='http://ars.els-cdn.com/content/image/1-s2.0-S0149763401000215-gr4a.gif' alt='unavailable'>

<ul><li><a href='http://ahuman.googlecode.com/svn/images/wiki/research/human/22-reticular-formation-and-limbic-system/F22-2.png'>Basal Nucleus of Meynert</a> - see [article:Biological/2005-The-Human-Nervous-System.pdf Reference]</li></ul>

<img src='http://ahuman.googlecode.com/svn/images/wiki/research/human/22-reticular-formation-and-limbic-system/F22-2.png' alt='unavailable'>

<ul><li><a href='http://ars.els-cdn.com/content/image/1-s2.0-S030100820900183X-gr4.jpg'>Simplified model of hippocampal formation anatomy</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S030100820900183X'>Reference</a></li></ul>

<img src='http://ars.els-cdn.com/content/image/1-s2.0-S030100820900183X-gr4.jpg' alt='unavailable'>

<ul><li><a href='http://www.impulsecontroldisorders.org/images/6-HippocampalVTA.jpg'>Combining Novelty, Motivational Salience, and Reward to Control Attention and Learning</a> - see <a href='http://www.impulsecontroldisorders.org/html/cravings.html'>Reference</a></li></ul>

<img src='http://www.impulsecontroldisorders.org/images/6-HippocampalVTA.jpg' alt='unavailable'>

<ul><li><a href='http://www.frontiersin.org/files/Articles/46459/fpsyt-04-00061-HTML/image_m/fpsyt-04-00061-g002.jpg'>Neuronal projections in the hippocampus</a> - see <a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>Reference</a></li></ul>

<img src='http://www.frontiersin.org/files/Articles/46459/fpsyt-04-00061-HTML/image_m/fpsyt-04-00061-g002.jpg' alt='unavailable'>

<ul><li><a href='http://what-when-how.com/wp-content/uploads/2012/04/tmp3649_thumb1_thumb.jpg'>Thalamocortical relationships</a> - see <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Reference</a></li></ul>

<img src='http://what-when-how.com/wp-content/uploads/2012/04/tmp3649_thumb1_thumb.jpg' alt='unavailable' height='400width=400'>

<ul><li><a href='http://neurondevelopment.org/userfiles/image/hippocampal-dev-page.gif'>Hippocampus and Septal Area</a> - see <a href='http://neurondevelopment.org/hippocampal-development'>Reference</a></li></ul>

<img src='http://neurondevelopment.org/userfiles/image/hippocampal-dev-page.gif' alt='unavailable'>


<h1>References</h1>
(generated)<br>
<br>
<ul><li><a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html</a>
</li><li><a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html'>http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F2.html</a>
</li><li><a href='http://www.scholarpedia.org/article/Head_direction_cells'>http://www.scholarpedia.org/article/Head_direction_cells</a>
</li><li><a href='http://learnmem.cshlp.org/content/14/11/714/F1.expansion'>http://learnmem.cshlp.org/content/14/11/714/F1.expansion</a>
</li><li>article:2009-Hippocampus-Thesis.pdf<br>
</li><li><a href='http://www.sciencedirect.com/science/article/pii/S030645220600755X'>http://www.sciencedirect.com/science/article/pii/S030645220600755X</a>
</li><li><a href='http://www.sciencedirect.com/science/article/pii/S0149763409002061'>http://www.sciencedirect.com/science/article/pii/S0149763409002061</a>
</li><li><a href='http://www.sciencedirect.com/science/article/pii/S1571064507000243'>http://www.sciencedirect.com/science/article/pii/S1571064507000243</a>
</li><li><a href='http://what-when-how.com/neuroscience/the-limbic-system-integrative-systems-part-1/'>http://what-when-how.com/neuroscience/the-limbic-system-integrative-systems-part-1/</a>
</li><li><a href='http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.html'>http://highered.mcgraw-hill.com/sites/dl/free/0071402357/156721/figure350_1.html</a>
</li><li><a href='http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html'>http://www.nature.com/nrn/journal/v5/n1/fig_tab/nrn1299_F4.html</a>
</li><li><a href='http://www.sciencedirect.com/science/article/pii/S0149763411001722'>http://www.sciencedirect.com/science/article/pii/S0149763411001722</a>
</li><li><a href='http://www.scholarpedia.org/article/Inferior_temporal_cortex'>http://www.scholarpedia.org/article/Inferior_temporal_cortex</a>
</li><li><a href='http://www.sciencedirect.com/science/article/pii/S0149763401000215'>http://www.sciencedirect.com/science/article/pii/S0149763401000215</a>
</li><li>article:Biological/2005-The-Human-Nervous-System.pdf<br>
</li><li><a href='http://www.sciencedirect.com/science/article/pii/S030100820900183X'>http://www.sciencedirect.com/science/article/pii/S030100820900183X</a>
</li><li><a href='http://www.impulsecontroldisorders.org/html/cravings.html'>http://www.impulsecontroldisorders.org/html/cravings.html</a>
</li><li><a href='http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full'>http://journal.frontiersin.org/Journal/10.3389/fpsyt.2013.00061/full</a>
</li><li><a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/</a>
</li><li><a href='http://neurondevelopment.org/hippocampal-development'>http://neurondevelopment.org/hippocampal-development</a></li></ul>
