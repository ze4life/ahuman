[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [BrainAreaNMA](BrainAreaNMA.md)

---




# Local Circuits #
(generated)

| **ID** | **Name** | **Regions** |
|:-------|:---------|:------------|
| FLM    | Flexor Motor | [NMA.FD.TH.VL](BrainRegionNMA_FD_TH_VL.md), [NMA.NC.MC](BrainRegionNMA_NC_MC.md) |
| SEQ    | Complex Motor | [NMA.FD.TH.MDL](BrainRegionNMA_FD_TH_MDL.md), [NMA.NC.PMC.AFEF](BrainRegionNMA_NC_PMC_AFEF.md), [NMA.NC.PMC.CFEF](BrainRegionNMA_NC_PMC_CFEF.md), [NMA.NC.SMC.F3](BrainRegionNMA_NC_SMC_F3.md), [NMA.NC.SMC.F6](BrainRegionNMA_NC_SMC_F6.md), [NMA.NC.SMC.SEF](BrainRegionNMA_NC_SMC_SEF.md) |
| XTM    | Extensor Motor | [NMA.FD.TH.VA](BrainRegionNMA_FD_TH_VA.md), [NMA.NC.PMC.F2](BrainRegionNMA_NC_PMC_F2.md), [NMA.NC.PMC.F4](BrainRegionNMA_NC_PMC_F4.md), [NMA.NC.PMC.F5](BrainRegionNMA_NC_PMC_F5.md), [NMA.NC.PMC.F7](BrainRegionNMA_NC_PMC_F7.md) |

## Flexor Motor ##


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/NMA_FLM.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNMA_FD_TH_VL.md'>NMA.FD.TH.VL</a> </td><td> Ventral Lateral Nucleus </td><td> nucleus     </td><td> NMU            </td><td> Relay BSA.CR to MCA.MC </td><td> Executive motor </td></tr>
<tr><td> <a href='BrainRegionNMA_NC_MC.md'>NMA.NC.MC</a> </td><td> Motor Cortex          </td><td> cortex, BA 04 </td><td> NMU            </td><td> Execution of required voluntary movements </td><td> F1; Encode individual movements </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNMA_FD_TH_VL.md'>NMA.FD.TH.VL</a> </td><td> <a href='BrainRegionNMA_NC_MC.md'>NMA.NC.MC</a> </td><td> nucleus-neocortex </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (VL -&gt; pVL)</a> </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNMA_NC_MC.md'>NMA.NC.MC</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> Dorsal Caudal Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in motor behavior (PMC -&gt; MC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNMA_NC_PMC_F5.md'>NMA.NC.PMC.F5</a> </td><td> Ventral Rostral Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0893608098000471'>Primate Control of Grasping (F5 -&gt; F1)</a> </td></tr>
<tr><td> <a href='BrainAreaNSA.md'>NSA</a> </td><td> <a href='BrainRegionNMA_NC_MC.md'>NMA.NC.MC</a> </td><td> <a href='BrainRegionNSA_NC_PG_PV.md'>NSA.NC.PG.PV</a> </td><td> Parietal Ventral Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (ParietalCortex -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_PG_S2.md'>NSA.NC.PG.S2</a> </td><td> Secondary Somatosensory Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (ParietalCortex -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionNMA_FD_TH_VL.md'>NMA.FD.TH.VL</a> </td><td> <a href='BrainRegionFEC_FT_GPI_LT.md'>FEC.FT.GPI.LT</a> </td><td> Globus Pallidus Internal Lateral </td><td> nucleus-nucleus-gaba </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (s2VL -&gt; VL, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLLC.md'>LLC</a> </td><td> <a href='BrainRegionNMA_FD_TH_VL.md'>NMA.FD.TH.VL</a> </td><td> <a href='BrainRegionLLC_HP_CR_DN.md'>LLC.HP.CR.DN</a> </td><td> Dentate Nucleus    </td><td> nucleus-nucleus </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (s1VL -&gt; VL, abstract)</a> </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNMA_FD_TH_VL.md'>NMA.FD.TH.VL</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F5.md'>NMA.NC.PMC.F5</a> </td><td> Ventral Rostral Premotor Cortex </td><td> nucleus-neocortex </td><td> <a href='http://thebrain.mcgill.ca/flash/a/a_06/a_06_cr/a_06_cr_mou/a_06_cr_mou.html'>Basal Ganglia Activity (VLo -&gt; PMC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNMA_NC_SMC_F6.md'>NMA.NC.SMC.F6</a> </td><td> Pre-Supplementary Motor Area </td><td> nucleus-neocortex </td><td> <a href='http://thebrain.mcgill.ca/flash/a/a_06/a_06_cr/a_06_cr_mou/a_06_cr_mou.html'>Basal Ganglia Activity (VLo -&gt; SMC, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionNMA_NC_MC.md'>NMA.NC.MC</a> </td><td> <a href='BrainRegionFEC_FD_STN_LT.md'>FEC.FD.STN.LT</a> </td><td> Subthalamic Nucleus Lateral </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFEC_FT_PU_LT.md'>FEC.FT.PU.LT</a> </td><td> Dorsal Putamen Lateral </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainAreaLLC.md'>LLC</a> </td><td> <a href='BrainRegionNMA_NC_MC.md'>NMA.NC.MC</a> </td><td> <a href='BrainRegionLLC_HP_PN_PBB.md'>LLC.HP.PN.PBB</a> </td><td> Pontobulbar Body   </td><td> neocortex-nucleus </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in motor behavior (MC -&gt; PN, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLLC_HP_PRF_PDT.md'>LLC.HP.PRF.PDT</a> </td><td> Pontine Reticulotegmental Nucleus </td><td> neocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (FrontalCortex -&gt; RF, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLPC.md'>LPC</a> </td><td> <a href='BrainRegionNMA_NC_MC.md'>NMA.NC.MC</a> </td><td> <a href='BrainRegionLPC_HM_AMB.md'>LPC.HM.AMB</a> </td><td> Ambiguus Nucleus   </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLPC_SC_VH_ONF.md'>LPC.SC.VH.ONF</a> </td><td> Onuf's Nucleus     </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLPC_SC_VH_PL.md'>LPC.SC.VH.PL</a> </td><td> Posterolateral Nucleus </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLPC_SC_VH_PM.md'>LPC.SC.VH.PM</a> </td><td> Posteromedial Nucleus </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLPC_SC_VH_RPL.md'>LPC.SC.VH.RPL</a> </td><td> Retroposterolateral Nucleus </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainAreaLRC.md'>LRC</a> </td><td> <a href='BrainRegionNMA_NC_MC.md'>NMA.NC.MC</a> </td><td> <a href='BrainRegionLRC_HP_PRF_CRF.md'>LRC.HP.PRF.CRF</a> </td><td> Caudal Pontine Reticular Nucleus </td><td> neocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (FrontalCortex -&gt; RF, abstract)</a> </td></tr></tbody></table>

<h2>Complex Motor</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/NMA_SEQ.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNMA_FD_TH_MDL.md'>NMA.FD.TH.MDL</a> </td><td> Lateral Mediodorsal Nucleus of Thalamus </td><td> nucleus     </td><td> NPU            </td><td> relay tegmentum to dorsal cingulate cortex </td><td> Relay Superior Colliculus, TH-LD, LDTG, IPD to<br>
<br>
<BR><br>
<br>
ACCdl </td></tr>
<tr><td> <a href='BrainRegionNMA_NC_PMC_AFEF.md'>NMA.NC.PMC.AFEF</a> </td><td> Anterior Frontal Eye Field </td><td> cortex, BA 08 </td><td> NMU            </td><td> Head and eye movements toward auditory stimuli </td><td> longer saccades, dorsomedial - 8A (8Ac, 8Am), but<br>
<br>
<BR><br>
<br>
not 8Ar; 8Ac - saccades </td></tr>
<tr><td> <a href='BrainRegionNMA_NC_PMC_CFEF.md'>NMA.NC.PMC.CFEF</a> </td><td> Caudal Frontal Eye Field </td><td> cortex, BA 08 </td><td> NMU            </td><td> Head and eye movements toward visual stimuli </td><td> shorter saccades </td></tr>
<tr><td> <a href='BrainRegionNMA_NC_SMC_F3.md'>NMA.NC.SMC.F3</a> </td><td> Supplementary Motor Area </td><td> cortex, BA 06 </td><td> NMU            </td><td> Movement execution; Numerical and verbal mental-operation tasks </td><td> from TH/VLo from from putamen; F1/F2/F4/24d -<br>
<br>
<BR><br>
<br>
strong; F6/F7/F5/24c - modest; no input from the<br>
<br>
<BR><br>
<br>
prefrontal lobe </td></tr>
<tr><td> <a href='BrainRegionNMA_NC_SMC_F6.md'>NMA.NC.SMC.F6</a> </td><td> Pre-Supplementary Motor Area </td><td> cortex, BA 06 </td><td> NMU            </td><td> High level motor functions; Numerical and verbal mental-operation tasks </td><td> from TH/VLpc, MD from caudate, CR; F5/24c/46; no<br>
<br>
<BR><br>
<br>
connections with F1 </td></tr>
<tr><td> <a href='BrainRegionNMA_NC_SMC_SEF.md'>NMA.NC.SMC.SEF</a> </td><td> Supplementary Eye Field </td><td> cortex, BA 06 </td><td> NMU            </td><td> high level aspects of saccade control </td><td> Complex spatial transformations, learned<br>
<br>
<BR><br>
<br>
transformations, and executive cognitive functions;<br>
<br>
<BR><br>
<br>
dorsorostral of F7 </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNMA_FD_TH_MDL.md'>NMA.FD.TH.MDL</a> </td><td> <a href='BrainRegionNMA_NC_PMC_AFEF.md'>NMA.NC.PMC.AFEF</a> </td><td> nucleus-neocortex </td><td> <a href='http://www.springerimages.com/Images/LifeSciences/1-10.1007_s00359-004-0565-9-0'>Oculomotor decision-making (Thalamus -&gt; FEF, abstract)</a> </td></tr>
<tr><td> <a href='BrainRegionNMA_NC_PMC_CFEF.md'>NMA.NC.PMC.CFEF</a> </td><td> <a href='BrainRegionNMA_NC_PMC_AFEF.md'>NMA.NC.PMC.AFEF</a> </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainRegionNMA_NC_SMC_SEF.md'>NMA.NC.SMC.SEF</a> </td><td> <a href='BrainRegionNMA_NC_PMC_AFEF.md'>NMA.NC.PMC.AFEF</a> </td><td> neocortex-neocortex </td><td> <a href='http://www.cixip.com/index.php/page/content/id/1190'>Summary of eye movement control (SEF -&gt; FEF, abstract)</a> </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionNMA_NC_PMC_AFEF.md'>NMA.NC.PMC.AFEF</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCL.md'>NDM.NC.AL.DLPFCL</a> </td><td> Lateral Mid-Dorsolateral Prefrontal Cortex </td><td> neocortex-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in motor behavior (LPFC -&gt; PMC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_SMC_SEF.md'>NMA.NC.SMC.SEF</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCR.md'>NDM.NC.AL.DLPFCR</a> </td><td> Rostral Mid-Dorsolateral Prefrontal Cortex </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (LPC -&gt; pre-SMA, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNMA_NC_SMC_F3.md'>NMA.NC.SMC.F3</a> </td><td> <a href='BrainRegionNMA_FD_TH_VA.md'>NMA.FD.TH.VA</a> </td><td> Ventral Anterior Nucleus </td><td> nucleus-neocortex </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (VA -&gt; pVA, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNMA_NC_PMC_F4.md'>NMA.NC.PMC.F4</a> </td><td> Ventral Caudal Premotor Cortex </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_SMC_F6.md'>NMA.NC.SMC.F6</a> </td><td> <a href='BrainRegionNMA_FD_TH_VL.md'>NMA.FD.TH.VL</a> </td><td> Ventral Lateral Nucleus </td><td> nucleus-neocortex </td><td> <a href='http://thebrain.mcgill.ca/flash/a/a_06/a_06_cr/a_06_cr_mou/a_06_cr_mou.html'>Basal Ganglia Activity (VLo -&gt; SMC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionNMA_NC_PMC_AFEF.md'>NMA.NC.PMC.AFEF</a> </td><td> <a href='BrainRegionNPE_NC_BRA_PO.md'>NPE.NC.BRA.PO</a> </td><td> Broca's Area Pars Opercularis </td><td> neocortex-neocortex </td><td> <a href='http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html'>Cortical Auditory System (IFC44 -&gt; PMC8, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_CFEF.md'>NMA.NC.PMC.CFEF</a> </td><td> <a href='BrainRegionNPE_NC_IPS_LIP.md'>NPE.NC.IPS.LIP</a> </td><td> Lateral Intraparietal Sulcus </td><td> neocortex-neocortex </td><td> <a href='http://www.cixip.com/index.php/page/content/id/1190'>Summary of eye movement control (PEF -&gt; FEF, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_SMC_SEF.md'>NMA.NC.SMC.SEF</a> </td><td> <a href='BrainRegionNPE_NC_SPL_PG.md'>NPE.NC.SPL.PG</a> </td><td> Caudal Precuneus   </td><td> neocortex-neocortex </td><td> <a href='http://thebrainlabs.com/brain.shtml'>Movement Planning (PPC -&gt; SMC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNSA.md'>NSA</a> </td><td> <a href='BrainRegionNMA_NC_PMC_CFEF.md'>NMA.NC.PMC.CFEF</a> </td><td> <a href='BrainRegionNSA_NC_IT_TE.md'>NSA.NC.IT.TE</a> </td><td> Inferotemporal Cortex </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/saccades.jpg'>Saccades and smooth movements (TEF -&gt; FEF, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionNMA_FD_TH_MDL.md'>NMA.FD.TH.MDL</a> </td><td> <a href='BrainRegionFEC_FT_SNR_MED.md'>FEC.FT.SNR.MED</a> </td><td> Substantia Nigra Pars Reticulata Medial </td><td> nucleus-nucleus-gaba </td><td> <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Saccadic Vision (BG -&gt; Thalamus, abstract)</a> </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionNMA_FD_TH_MDL.md'>NMA.FD.TH.MDL</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> Dorsal Anterior Cingulate Area </td><td> nucleus-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Saccadic Vision (Thalamus -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNMA_NC_PMC_AFEF.md'>NMA.NC.PMC.AFEF</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F7.md'>NMA.NC.PMC.F7</a> </td><td> Dorsal Rostral Premotor Cortex </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_CFEF.md'>NMA.NC.PMC.CFEF</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F5.md'>NMA.NC.PMC.F5</a> </td><td> Ventral Rostral Premotor Cortex </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_SMC_F3.md'>NMA.NC.SMC.F3</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> Dorsal Caudal Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (pre-SMA -&gt; dPM, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNMA_NC_PMC_F5.md'>NMA.NC.PMC.F5</a> </td><td> Ventral Rostral Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (pre-SMA -&gt; vPM, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_SMC_F6.md'>NMA.NC.SMC.F6</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F5.md'>NMA.NC.PMC.F5</a> </td><td> Ventral Rostral Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0893608098000471'>Primate Control of Grasping (F6 -&gt; F5)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionNMA_NC_PMC_AFEF.md'>NMA.NC.PMC.AFEF</a> </td><td> <a href='BrainRegionFEC_FT_CN_BD.md'>FEC.FT.CN.BD</a> </td><td> Caudate Nucleus Body </td><td> neocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (FrontalCortex -&gt; BGA, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_SMC_F3.md'>NMA.NC.SMC.F3</a> </td><td> <a href='BrainRegionFEC_FT_PU_MED.md'>FEC.FT.PU.MED</a> </td><td> Dorsal Putamen Medial </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_SMC_F6.md'>NMA.NC.SMC.F6</a> </td><td> <a href='BrainRegionFEC_FD_STN_MED.md'>FEC.FD.STN.MED</a> </td><td> Subthalamic Nucleus Medial </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainAreaLLC.md'>LLC</a> </td><td> <a href='BrainRegionNMA_NC_SMC_F3.md'>NMA.NC.SMC.F3</a> </td><td> <a href='BrainRegionLLC_HP_PRF_PDT.md'>LLC.HP.PRF.PDT</a> </td><td> Pontine Reticulotegmental Nucleus </td><td> neocortex-nucleus </td><td> <a href='http://www.frontiersin.org/neuroanatomy/10.3389/fnana.2011.00034/full'>Vocal Control (M2 -&gt; RF, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLRC.md'>LRC</a> </td><td> <a href='BrainRegionNMA_NC_PMC_AFEF.md'>NMA.NC.PMC.AFEF</a> </td><td> <a href='BrainRegionLRC_HP_PRF_GCR.md'>LRC.HP.PRF.GCR</a> </td><td> Gigantocellular Reticular Nucleus </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLRC_HP_PRF_RPO.md'>LRC.HP.PRF.RPO</a> </td><td> Oral Pontine Reticular Nucleus </td><td> neocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (FrontalCortex -&gt; RF, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLRC_MM_CJ.md'>LRC.MM.CJ</a> </td><td> Cajal Nucleus      </td><td> neocortex-nucleus </td><td> <a href='http://www.cixip.com/index.php/page/content/id/1190'>Summary of eye movement control (FEF -&gt; riMLF, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLRC_MM_DSCH.md'>LRC.MM.DSCH</a> </td><td> Darkschewitsch Nucleus </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLRC_MM_SC_INT.md'>LRC.MM.SC.INT</a> </td><td> Intermediate Superior Colliculus </td><td> neocortex-nucleus </td><td> <a href='http://www.cixip.com/index.php/page/content/id/1190'>Summary of eye movement control (FEF -&gt; SC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_SMC_F3.md'>NMA.NC.SMC.F3</a> </td><td> <a href='BrainRegionLRC_HP_PRF_CRF.md'>LRC.HP.PRF.CRF</a> </td><td> Caudal Pontine Reticular Nucleus </td><td> neocortex-nucleus </td><td> <a href='http://www.frontiersin.org/neuroanatomy/10.3389/fnana.2011.00034/full'>Vocal Control (M2 -&gt; RF, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLRC_HP_PRF_GCR.md'>LRC.HP.PRF.GCR</a> </td><td> Gigantocellular Reticular Nucleus </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_SMC_SEF.md'>NMA.NC.SMC.SEF</a> </td><td> <a href='BrainRegionLRC_MM_RP_RIP.md'>LRC.MM.RP.RIP</a> </td><td> Raphe Interpositus Nucleus </td><td> neocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0006899301025987'>Horizontal saccades and smooth pursuit movements (FEFSEF -&gt; RIP, abstract)</a> </td></tr></tbody></table>

<h2>Extensor Motor</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/NMA_XTM.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNMA_FD_TH_VA.md'>NMA.FD.TH.VA</a> </td><td> Ventral Anterior Nucleus </td><td> nucleus     </td><td> NMU            </td><td> Relay BGA.SN, BGA.GPI, FCA.OMPFC, FCA.CG to MCA.PMC, MCA.SMC </td><td> Cognitive motor </td></tr>
<tr><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> Dorsal Caudal Premotor Cortex </td><td> cortex, BA 06 </td><td> NMU            </td><td> Guiding reaching </td><td> 6DC; Active during preparation for reach and also<br>
<br>
<BR><br>
<br>
during reach itself; leg and arm; transform sensory<br>
<br>
<BR><br>
<br>
information into motor representation; preparation<br>
<br>
<BR><br>
<br>
and execution of motor acts </td></tr>
<tr><td> <a href='BrainRegionNMA_NC_PMC_F4.md'>NMA.NC.PMC.F4</a> </td><td> Ventral Caudal Premotor Cortex </td><td> cortex, BA 06 </td><td> NMU            </td><td> Sensory guidance of movement </td><td> 6VC; Neurons are especially sensitive to objects in<br>
<br>
<BR><br>
<br>
space immediately surrounding body; move head, face<br>
<br>
<BR><br>
<br>
and arm </td></tr>
<tr><td> <a href='BrainRegionNMA_NC_PMC_F5.md'>NMA.NC.PMC.F5</a> </td><td> Ventral Rostral Premotor Cortex </td><td> cortex, BA 06 </td><td> NMU            </td><td> Shaping hand during grasping </td><td> 6VR; Mirror neurons - both sensory and motor; arm;<br>
<br>
<BR><br>
<br>
F5c=convexity - F1/F4/F2VR/F6/F3/24d/24c,<br>
<br>
<BR><br>
<br>
F5p=posterior - F3/F4/F1/24c/24a, F5a=anterior -<br>
<br>
<BR><br>
<br>
F4/F6/24c/24d/24a/46v/12r/12l </td></tr>
<tr><td> <a href='BrainRegionNMA_NC_PMC_F7.md'>NMA.NC.PMC.F7</a> </td><td> Dorsal Rostral Premotor Cortex </td><td> cortex, BA 06 </td><td> NMU            </td><td> Associate arbitrary sensory stimuli with specific eye movements </td><td> 6DR; Can evoke eye movements; strong afferents from<br>
<br>
<BR><br>
<br>
DLPFC; convey inputs to caudal concerning<br>
<br>
<BR><br>
<br>
motivation, long term plans, memory of past<br>
<br>
<BR><br>
<br>
actions; integrates sensory and internally driven<br>
<br>
<BR><br>
<br>
inputs for planning of goal-directed actions </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNMA_FD_TH_VA.md'>NMA.FD.TH.VA</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> nucleus-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in motor behavior (TH -&gt; PMC, abstract)</a> </td></tr>
<tr><td> <a href='BrainRegionNMA_NC_PMC_F4.md'>NMA.NC.PMC.F4</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainRegionNMA_NC_PMC_F5.md'>NMA.NC.PMC.F5</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainRegionNMA_NC_PMC_F7.md'>NMA.NC.PMC.F7</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionNMA_FD_TH_VA.md'>NMA.FD.TH.VA</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCL.md'>NDM.NC.AL.DLPFCL</a> </td><td> Lateral Mid-Dorsolateral Prefrontal Cortex </td><td> neocortex-nucleus </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in motor behavior (LPFC -&gt; TH, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> <a href='BrainRegionNDM_NC_AL_VACG.md'>NDM.NC.AL.VACG</a> </td><td> Ventral Anterior Cingulate Area </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_F5.md'>NMA.NC.PMC.F5</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCL.md'>NDM.NC.AL.DLPFCL</a> </td><td> Lateral Mid-Dorsolateral Prefrontal Cortex </td><td> neocortex-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in motor behavior (LPFC -&gt; PMC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_F7.md'>NMA.NC.PMC.F7</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> Dorsal Anterior Cingulate Area </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCR.md'>NDM.NC.AL.DLPFCR</a> </td><td> Rostral Mid-Dorsolateral Prefrontal Cortex </td><td> neocortex-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in motor behavior (LPFC -&gt; PMC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> <a href='BrainRegionNMA_NC_SMC_F3.md'>NMA.NC.SMC.F3</a> </td><td> Supplementary Motor Area </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (pre-SMA -&gt; dPM, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_F5.md'>NMA.NC.PMC.F5</a> </td><td> <a href='BrainRegionNMA_FD_TH_VL.md'>NMA.FD.TH.VL</a> </td><td> Ventral Lateral Nucleus </td><td> nucleus-neocortex </td><td> <a href='http://thebrain.mcgill.ca/flash/a/a_06/a_06_cr/a_06_cr_mou/a_06_cr_mou.html'>Basal Ganglia Activity (VLo -&gt; PMC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNMA_NC_PMC_CFEF.md'>NMA.NC.PMC.CFEF</a> </td><td> Caudal Frontal Eye Field </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNMA_NC_SMC_F3.md'>NMA.NC.SMC.F3</a> </td><td> Supplementary Motor Area </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (pre-SMA -&gt; vPM, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNMA_NC_SMC_F6.md'>NMA.NC.SMC.F6</a> </td><td> Pre-Supplementary Motor Area </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0893608098000471'>Primate Control of Grasping (F6 -&gt; F5)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_F7.md'>NMA.NC.PMC.F7</a> </td><td> <a href='BrainRegionNMA_NC_PMC_AFEF.md'>NMA.NC.PMC.AFEF</a> </td><td> Anterior Frontal Eye Field </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> <a href='BrainRegionNPE_NC_IPL_SMW.md'>NPE.NC.IPL.SMW</a> </td><td> Supramarginal Wernike Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.ncbi.nlm.nih.gov/pmc/articles/PMC2846110/'>Dual Auditory Processing (PPC -&gt; DLPFC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNPE_NC_SPL_PF.md'>NPE.NC.SPL.PF</a> </td><td> Rostral Precuneus  </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (SPL -&gt; dPM, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNPE_NC_SPL_PG.md'>NPE.NC.SPL.PG</a> </td><td> Caudal Precuneus   </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (SPL -&gt; dPM, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNPE_NC_SPL_SA.md'>NPE.NC.SPL.SA</a> </td><td> Somatosensory Association Cortex </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (SPL -&gt; dPM, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_F4.md'>NMA.NC.PMC.F4</a> </td><td> <a href='BrainRegionNPE_NC_IPL_MST.md'>NPE.NC.IPL.MST</a> </td><td> Medial Superior Temporal Area </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (IPL -&gt; vPM, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNPE_NC_IPL_SMW.md'>NPE.NC.IPL.SMW</a> </td><td> Supramarginal Wernike Cortex </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (IPL -&gt; vPM, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_F7.md'>NMA.NC.PMC.F7</a> </td><td> <a href='BrainRegionNPE_NC_IPS_LIP.md'>NPE.NC.IPS.LIP</a> </td><td> Lateral Intraparietal Sulcus </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (ParietalCortex -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNSA.md'>NSA</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> <a href='BrainRegionNSA_NC_PG_S1.md'>NSA.NC.PG.S1</a> </td><td> Primary Somatosensory Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (ParietalCortex -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_F4.md'>NMA.NC.PMC.F4</a> </td><td> <a href='BrainRegionNSA_NC_IPS_AIP.md'>NSA.NC.IPS.AIP</a> </td><td> Anterior Intraparietal Sulcus </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0893608098000471'>Primate Control of Grasping (AIP -&gt; F4)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_IPS_VIP.md'>NSA.NC.IPS.VIP</a> </td><td> Ventral Intraparietal Sulcus </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0893608098000471'>Primate Control of Grasping (VIP -&gt; F4)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_STG_A3.md'>NSA.NC.STG.A3</a> </td><td> Wernicke's area A3 </td><td> neocortex-neocortex </td><td> <a href='http://www.ncbi.nlm.nih.gov/pmc/articles/PMC2846110/'>Dual Auditory Processing (ST -&gt; VLPFC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_STG_A4.md'>NSA.NC.STG.A4</a> </td><td> Wernicke's area A4 </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1364661312002823'>Language-Related Regions (pSTC -&gt; PMC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_F5.md'>NMA.NC.PMC.F5</a> </td><td> <a href='BrainRegionNSA_NC_IPS_AIP.md'>NSA.NC.IPS.AIP</a> </td><td> Anterior Intraparietal Sulcus </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0893608098000471'>Primate Control of Grasping (AIP -&gt; F5)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_PG_S1.md'>NSA.NC.PG.S1</a> </td><td> Primary Somatosensory Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0893608098000471'>Primate Control of Grasping (S2 -&gt; F5)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_F7.md'>NMA.NC.PMC.F7</a> </td><td> <a href='BrainRegionNSA_NC_TTG_A1.md'>NSA.NC.TTG.A1</a> </td><td> Primary Auditory Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.ncbi.nlm.nih.gov/pmc/articles/PMC2846110/'>Dual Auditory Processing (A1 -&gt; DLPFC, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionNMA_FD_TH_VA.md'>NMA.FD.TH.VA</a> </td><td> <a href='BrainRegionFEC_FT_GPI_DS.md'>FEC.FT.GPI.DS</a> </td><td> Globus Pallidus Internal Dorsal </td><td> nucleus-nucleus-gaba </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (sVA -&gt; VA, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFEC_FT_GPI_MED.md'>FEC.FT.GPI.MED</a> </td><td> Globus Pallidus Internal Medial </td><td> nucleus-nucleus-gaba </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (sVA -&gt; VA, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFEC_FT_SNR_DL.md'>FEC.FT.SNR.DL</a> </td><td> Substantia Nigra Pars Reticulata Dorsolateral </td><td> nucleus-nucleus-gaba </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (sVA -&gt; VA, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLRC.md'>LRC</a> </td><td> <a href='BrainRegionNMA_FD_TH_VA.md'>NMA.FD.TH.VA</a> </td><td> <a href='BrainRegionLRC_MM_SC_INT.md'>LRC.MM.SC.INT</a> </td><td> Intermediate Superior Colliculus </td><td> nucleus-nucleus </td><td> <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Saccadic Vision (SCi -&gt; Thalamus, abstract)</a> </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F4.md'>NMA.NC.PMC.F4</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCL.md'>NDM.NC.AL.DLPFCL</a> </td><td> Lateral Mid-Dorsolateral Prefrontal Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1053810011000080'>Cortico-Cortical Connectivity (MA -&gt; PFC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNMA_FD_TH_VA.md'>NMA.FD.TH.VA</a> </td><td> <a href='BrainRegionNMA_NC_SMC_F3.md'>NMA.NC.SMC.F3</a> </td><td> Supplementary Motor Area </td><td> nucleus-neocortex </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (VA -&gt; pVA, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> <a href='BrainRegionNMA_NC_MC.md'>NMA.NC.MC</a> </td><td> Motor Cortex       </td><td> neocortex-neocortex </td><td> <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Prefrontal Cortex (PFC) in motor behavior (PMC -&gt; MC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_F4.md'>NMA.NC.PMC.F4</a> </td><td> <a href='BrainRegionNMA_NC_SMC_F3.md'>NMA.NC.SMC.F3</a> </td><td> Supplementary Motor Area </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_F5.md'>NMA.NC.PMC.F5</a> </td><td> <a href='BrainRegionNMA_NC_MC.md'>NMA.NC.MC</a> </td><td> Motor Cortex       </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0893608098000471'>Primate Control of Grasping (F5 -&gt; F1)</a> </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F7.md'>NMA.NC.PMC.F7</a> </td><td> <a href='BrainRegionNPE_NC_SPL_SA.md'>NPE.NC.SPL.SA</a> </td><td> Somatosensory Association Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1053810011000080'>Cortico-Cortical Connectivity (MA -&gt; SA, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> <a href='BrainRegionFEC_FT_PU_MED.md'>FEC.FT.PU.MED</a> </td><td> Dorsal Putamen Medial </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNMA_NC_PMC_F5.md'>NMA.NC.PMC.F5</a> </td><td> <a href='BrainRegionFEC_FT_PU_MED.md'>FEC.FT.PU.MED</a> </td><td> Dorsal Putamen Medial </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr></tbody></table>

<h1>Thirdparty Circuits</h1>
(generated)<br>
<br>
<ul><li><a href='http://ars.els-cdn.com/content/image/1-s2.0-S0893608098000471-gr6.gif'>Primate Control of Grasping</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S0893608098000471'>Reference</a></li></ul>

<img src='http://ars.els-cdn.com/content/image/1-s2.0-S0893608098000471-gr6.gif' alt='unavailable'>

<ul><li><a href='http://what-when-how.com/wp-content/uploads/2012/04/tmp3649_thumb1_thumb.jpg'>Thalamocortical relationships</a> - see <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Reference</a></li></ul>

<img src='http://what-when-how.com/wp-content/uploads/2012/04/tmp3649_thumb1_thumb.jpg' alt='unavailable' height='400width=400'>

<ul><li><a href='http://thebrain.mcgill.ca/flash/a/a_06/a_06_cr/a_06_cr_mou/a_06_cr_mou_2b.jpg'>Basal Ganglia Activity</a> - see <a href='http://thebrain.mcgill.ca/flash/a/a_06/a_06_cr/a_06_cr_mou/a_06_cr_mou.html'>Reference</a></li></ul>

<img src='http://thebrain.mcgill.ca/flash/a/a_06/a_06_cr/a_06_cr_mou/a_06_cr_mou_2b.jpg' alt='unavailable'>

<ul><li><a href='http://www.mdvu.org/images/par_path2.jpg'>Normal Functional Anatomy of Basal Ganglia</a> - see <a href='http://www.mdvu.org/library/disease/pd/par_path.asp'>Reference</a></li></ul>

<img src='http://www.mdvu.org/images/par_path2.jpg' alt='unavailable'>

<ul><li><a href='http://img.springerimages.com/Images/Springer/PUB=Springer-Verlag-Berlin-Heidelberg/JOU=00359/VOL=2005.191/ISU=3/ART=2004_565/MediaObjects/WATER_s00359-004-0565-9fhc1.jpg'>Oculomotor decision-making</a> - see <a href='http://www.springerimages.com/Images/LifeSciences/1-10.1007_s00359-004-0565-9-0'>Reference</a></li></ul>

<img src='http://img.springerimages.com/Images/Springer/PUB=Springer-Verlag-Berlin-Heidelberg/JOU=00359/VOL=2005.191/ISU=3/ART=2004_565/MediaObjects/WATER_s00359-004-0565-9fhc1.jpg' alt='unavailable'>

<ul><li><a href='http://www.cixip.com/Public/kindeditor/attached/image/20121030/20121030134649_52795.jpg'>Summary of eye movement control</a> - see <a href='http://www.cixip.com/index.php/page/content/id/1190'>Reference</a></li></ul>

<img src='http://www.cixip.com/Public/kindeditor/attached/image/20121030/20121030134649_52795.jpg' alt='unavailable'>

<ul><li><a href='http://www.nature.com/neuro/journal/v12/n6/images/nn.2331-F5.jpg'>Cortical Auditory System</a> - see <a href='http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html'>Reference</a></li></ul>

<img src='http://www.nature.com/neuro/journal/v12/n6/images/nn.2331-F5.jpg' alt='unavailable'>

<ul><li><a href='http://ars.els-cdn.com/content/image/1-s2.0-S0959438807000323-gr1.jpg'>Two extended parallel pathways for decision making</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S0959438807000323'>Reference</a></li></ul>

<img src='http://ars.els-cdn.com/content/image/1-s2.0-S0959438807000323-gr1.jpg' alt='unavailable'>

<ul><li><a href='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/visual-streams.jpg'>3 Visual Cortex Paths</a> - see [article:Biological/2008-dorsal-stream.pdf Reference]</li></ul>

<img src='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/visual-streams.jpg' alt='unavailable'>

<ul><li><a href='http://aids.hallym.ac.kr/d/kns/tutor/ch2-nb3.jpg'>Sensimotor Nerves</a> - see <a href='http://aids.hallym.ac.kr/d/kns/tutor/chap2-bn.html'>Reference</a></li></ul>

<img src='http://aids.hallym.ac.kr/d/kns/tutor/ch2-nb3.jpg' alt='unavailable'>

<ul><li><a href='http://aids.hallym.ac.kr/d/kns/tutor/pns49.jpg'>Sensimotor Interactions</a> - see <a href='http://aids.hallym.ac.kr/d/kns/tutor/chap2-bn.html'>Reference</a></li></ul>

<img src='http://aids.hallym.ac.kr/d/kns/tutor/pns49.jpg' alt='unavailable'>

<ul><li><a href='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/motor_top.jpg'>Prefrontal Cortex (PFC) in motor behavior</a> - see <a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>Reference</a></li></ul>

<img src='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/motor_top.jpg' alt='unavailable'>

<ul><li><a href='http://ars.els-cdn.com/content/image/1-s2.0-S0896627307007118-gr4.jpg'>Divisions of Cortical Motor System</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S0896627307007118'>Reference</a></li></ul>

<img src='http://ars.els-cdn.com/content/image/1-s2.0-S0896627307007118-gr4.jpg' alt='unavailable'>

<ul><li><a href='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/motor-cortex.jpg'>Motor Cortices</a> (unknown reference)</li></ul>

<img src='http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/motor-cortex.jpg' alt='unavailable'>

<ul><li><a href='http://brainmind.com/images/Pyramidaltract.jpg'>Corticospinal pathway</a> - see <a href='http://brainmind.com'>Reference</a></li></ul>

<img src='http://brainmind.com/images/Pyramidaltract.jpg' alt='unavailable'>

<ul><li><a href='http://ars.els-cdn.com/content/image/1-s2.0-S1053810011000080-gr3.jpg'>Cortico-Cortical Connectivity</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S1053810011000080'>Reference</a></li></ul>

<img src='http://ars.els-cdn.com/content/image/1-s2.0-S1053810011000080-gr3.jpg' alt='unavailable'>


<h1>References</h1>
(generated)<br>
<br>
<ul><li><a href='http://www.sciencedirect.com/science/article/pii/S0893608098000471'>http://www.sciencedirect.com/science/article/pii/S0893608098000471</a>
</li><li><a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/</a>
</li><li><a href='http://thebrain.mcgill.ca/flash/a/a_06/a_06_cr/a_06_cr_mou/a_06_cr_mou.html'>http://thebrain.mcgill.ca/flash/a/a_06/a_06_cr/a_06_cr_mou/a_06_cr_mou.html</a>
</li><li><a href='http://www.mdvu.org/library/disease/pd/par_path.asp'>http://www.mdvu.org/library/disease/pd/par_path.asp</a>
</li><li><a href='http://www.springerimages.com/Images/LifeSciences/1-10.1007_s00359-004-0565-9-0'>http://www.springerimages.com/Images/LifeSciences/1-10.1007_s00359-004-0565-9-0</a>
</li><li><a href='http://www.cixip.com/index.php/page/content/id/1190'>http://www.cixip.com/index.php/page/content/id/1190</a>
</li><li><a href='http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html'>http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html</a>
</li><li><a href='http://www.sciencedirect.com/science/article/pii/S0959438807000323'>http://www.sciencedirect.com/science/article/pii/S0959438807000323</a>
</li><li>article:Biological/2008-dorsal-stream.pdf<br>
</li><li><a href='http://aids.hallym.ac.kr/d/kns/tutor/chap2-bn.html'>http://aids.hallym.ac.kr/d/kns/tutor/chap2-bn.html</a>
</li><li><a href='https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988'>https://www.google.ru/search?hl=rutbo=ptbm=bksq=isbn:0080887988</a>
</li><li><a href='http://www.sciencedirect.com/science/article/pii/S0896627307007118'>http://www.sciencedirect.com/science/article/pii/S0896627307007118</a>
</li><li><a href='http://brainmind.com'>http://brainmind.com</a>
</li><li><a href='http://www.sciencedirect.com/science/article/pii/S1053810011000080'>http://www.sciencedirect.com/science/article/pii/S1053810011000080</a></li></ul>
