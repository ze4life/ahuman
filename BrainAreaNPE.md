[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [BrainAreaNPE](BrainAreaNPE.md)

---




# Local Circuits #
(generated)

| **ID** | **Name** | **Regions** |
|:-------|:---------|:------------|
| AES    | Execution by Auditory Inputs | [NPE.NC.BRA.PO](BrainRegionNPE_NC_BRA_PO.md), [NPE.NC.BRA.PT](BrainRegionNPE_NC_BRA_PT.md), [NPE.NC.IPL.SMW](BrainRegionNPE_NC_IPL_SMW.md), [NPE.NC.STG.PAI](BrainRegionNPE_NC_STG_PAI.md) |
| GRC    | Grasping Control | [NPE.FD.TH.OPV](BrainRegionNPE_FD_TH_OPV.md), [NPE.NC.IPS.MIP](BrainRegionNPE_NC_IPS_MIP.md), [NPE.NC.SPL.PF](BrainRegionNPE_NC_SPL_PF.md), [NPE.NC.SPL.SA](BrainRegionNPE_NC_SPL_SA.md) |
| NPS    | Execution by Motion Inputs | [NPE.FD.TH.MPV](BrainRegionNPE_FD_TH_MPV.md), [NPE.NC.IPL.MST](BrainRegionNPE_NC_IPL_MST.md) |
| ORV    | Orienting by Visual Stimuli | [NPE.NC.IPS.LIP](BrainRegionNPE_NC_IPS_LIP.md), [NPE.NC.OCC.V2PL](BrainRegionNPE_NC_OCC_V2PL.md), [NPE.NC.OCC.V3D](BrainRegionNPE_NC_OCC_V3D.md), [NPE.NC.OCC.V3V](BrainRegionNPE_NC_OCC_V3V.md) |
| SEC    | Subcortical Execution Control | [NPE.FD.TH.LP](BrainRegionNPE_FD_TH_LP.md), [NPE.NC.SPL.PG](BrainRegionNPE_NC_SPL_PG.md) |

## Execution by Auditory Inputs ##


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/NPE_AES.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNPE_NC_BRA_PO.md'>NPE.NC.BRA.PO</a> </td><td> Broca's Area Pars Opercularis </td><td> cortex, BA 44 </td><td> NEU            </td><td> Speech Engine   </td><td> Orbital Inferior Frontal Gyrus </td></tr>
<tr><td> <a href='BrainRegionNPE_NC_BRA_PT.md'>NPE.NC.BRA.PT</a> </td><td> Broca's Area Pars Triangularis </td><td> cortex, BA 45 </td><td> NEU            </td><td> Language production and prefrontal associational integration, propositional<br>
<br>
<BR><br>
<br>
language comprehension </td><td> Triangular Inferior Frontal Gyrus, switching<br>
<br>
<BR><br>
<br>
between semantic sub-categories in word retrieval </td></tr>
<tr><td> <a href='BrainRegionNPE_NC_IPL_SMW.md'>NPE.NC.IPL.SMW</a> </td><td> Supramarginal Wernike Cortex </td><td> cortex, BA 40 </td><td> NEU            </td><td> Phonological and articulatory processing of words </td><td> PF, Computing sound of word, tactile learning and<br>
<br>
<BR><br>
<br>
memory </td></tr>
<tr><td> <a href='BrainRegionNPE_NC_STG_PAI.md'>NPE.NC.STG.PAI</a> </td><td> Parainsular Area      </td><td> cortex, BA 52 </td><td> NEU            </td><td> Medial auditory stream </td><td> Major projects to PFC multi-modal associations,<br>
<br>
<BR><br>
<br>
auditory to insula </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNPE_NC_BRA_PT.md'>NPE.NC.BRA.PT</a> </td><td> <a href='BrainRegionNPE_NC_IPL_SMW.md'>NPE.NC.IPL.SMW</a> </td><td> neocortex-neocortex </td><td> <a href='http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html'>Cortical Auditory System (IFC44 -&gt; IPL40, abstract)</a> </td></tr>
<tr><td> <a href='BrainRegionNPE_NC_STG_PAI.md'>NPE.NC.STG.PAI</a> </td><td> <a href='BrainRegionNPE_NC_IPL_SMW.md'>NPE.NC.IPL.SMW</a> </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionNPE_NC_BRA_PO.md'>NPE.NC.BRA.PO</a> </td><td> <a href='BrainRegionNCP_NC_TPC.md'>NCP.NC.TPC</a> </td><td> Temporopolar Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1364661312002823'>Language-Related Regions (TC -&gt; BA45, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionNPE_NC_IPL_SMW.md'>NPE.NC.IPL.SMW</a> </td><td> <a href='BrainRegionNPE_NC_IPL_MST.md'>NPE.NC.IPL.MST</a> </td><td> Medial Superior Temporal Area </td><td> neocortex-neocortex </td><td> <a href='http://www.hindawi.com/journals/nri/2012/719056'>Visual Dorsal Pathway (MST -&gt; IPL, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNSA.md'>NSA</a> </td><td> <a href='BrainRegionNPE_NC_BRA_PT.md'>NPE.NC.BRA.PT</a> </td><td> <a href='BrainRegionNSA_NC_STG_A3.md'>NSA.NC.STG.A3</a> </td><td> Wernicke's area A3 </td><td> neocortex-neocortex </td><td> <a href='http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html'>Cortical Auditory System (STS22 -&gt; IFC45, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_STG_A4.md'>NSA.NC.STG.A4</a> </td><td> Wernicke's area A4 </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1364661312002823'>Language-Related Regions (pSTC -&gt; BA44, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_IPL_SMW.md'>NPE.NC.IPL.SMW</a> </td><td> <a href='BrainRegionNSA_NC_IPS_VIP.md'>NSA.NC.IPS.VIP</a> </td><td> Ventral Intraparietal Sulcus </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (IPS -&gt; IPL, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_PG_S2.md'>NSA.NC.PG.S2</a> </td><td> Secondary Somatosensory Cortex </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_STG_A3.md'>NSA.NC.STG.A3</a> </td><td> Wernicke's area A3 </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1053810011000080'>Cortico-Cortical Connectivity (AA -&gt; PTHA, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_STG_A4.md'>NSA.NC.STG.A4</a> </td><td> Wernicke's area A4 </td><td> neocortex-neocortex </td><td> <a href='http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html'>Cortical Auditory System (AC22 -&gt; IPL40, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_TTG_A1.md'>NSA.NC.TTG.A1</a> </td><td> Primary Auditory Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.ncbi.nlm.nih.gov/pmc/articles/PMC2846110/'>Dual Auditory Processing (A1 -&gt; PPC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_STG_PAI.md'>NPE.NC.STG.PAI</a> </td><td> <a href='BrainRegionNSA_FD_TH_VPM.md'>NSA.FD.TH.VPM</a> </td><td> Ventral Posteromedial Nucleus </td><td> nucleus-neocortex </td><td> (unknown reference) </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNPE_NC_BRA_PO.md'>NPE.NC.BRA.PO</a> </td><td> <a href='BrainRegionNMA_NC_PMC_AFEF.md'>NMA.NC.PMC.AFEF</a> </td><td> Anterior Frontal Eye Field </td><td> neocortex-neocortex </td><td> <a href='http://www.nature.com/neuro/journal/v12/n6/fig_tab/nn.2331_F5.html'>Cortical Auditory System (IFC44 -&gt; PMC8, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_IPL_SMW.md'>NPE.NC.IPL.SMW</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> Dorsal Caudal Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.ncbi.nlm.nih.gov/pmc/articles/PMC2846110/'>Dual Auditory Processing (PPC -&gt; DLPFC, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNMA_NC_PMC_F4.md'>NMA.NC.PMC.F4</a> </td><td> Ventral Caudal Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (IPL -&gt; vPM, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaLLC.md'>LLC</a> </td><td> <a href='BrainRegionNPE_NC_BRA_PO.md'>NPE.NC.BRA.PO</a> </td><td> <a href='BrainRegionLLC_HP_PRF_PDT.md'>LLC.HP.PRF.PDT</a> </td><td> Pontine Reticulotegmental Nucleus </td><td> neocortex-nucleus </td><td> <a href='http://www.frontiersin.org/neuroanatomy/10.3389/fnana.2011.00034/full'>Vocal Control (Broca -&gt; RF, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLRC.md'>LRC</a> </td><td> <a href='BrainRegionNPE_NC_BRA_PO.md'>NPE.NC.BRA.PO</a> </td><td> <a href='BrainRegionLRC_HP_PRF_RPO.md'>LRC.HP.PRF.RPO</a> </td><td> Oral Pontine Reticular Nucleus </td><td> neocortex-nucleus </td><td> <a href='http://www.frontiersin.org/neuroanatomy/10.3389/fnana.2011.00034/full'>Vocal Control (Broca -&gt; RF, abstract)</a> </td></tr></tbody></table>

<h2>Grasping Control</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/NPE_GRC.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNPE_FD_TH_OPV.md'>NPE.FD.TH.OPV</a> </td><td> Oral Pulvinar         </td><td> nucleus     </td><td> NEU            </td><td> Somatosensory functions </td><td> Thalamus, connected with parietal cortex, anterior<br>
<br>
<BR><br>
<br>
pulvinar </td></tr>
<tr><td> <a href='BrainRegionNPE_NC_IPS_MIP.md'>NPE.NC.IPS.MIP</a> </td><td> Medial Intraparietal Sulcus </td><td> cortex, BA 39 </td><td> NEU            </td><td> Encode location of reach target in nose-centered coordinates </td><td>                 </td></tr>
<tr><td> <a href='BrainRegionNPE_NC_SPL_PF.md'>NPE.NC.SPL.PF</a> </td><td> Rostral Precuneus     </td><td> cortex, BA 07 </td><td> NEU            </td><td> Spatial orientation, representation of the self </td><td> rostral, 7B=PF, heavy somatosensory input </td></tr>
<tr><td> <a href='BrainRegionNPE_NC_SPL_SA.md'>NPE.NC.SPL.SA</a> </td><td> Somatosensory Association Cortex </td><td> cortex, BA 05 </td><td> NPU            </td><td> Locating objects in space </td><td> PE, somatosensory, guiding movement by providing<br>
<br>
<BR><br>
<br>
information about limb position </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNPE_FD_TH_OPV.md'>NPE.FD.TH.OPV</a> </td><td> <a href='BrainRegionNPE_NC_SPL_PF.md'>NPE.NC.SPL.PF</a> </td><td> nucleus-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (Pulvinar -&gt; ParietalCortex, abstract)</a> </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNPE_NC_SPL_SA.md'>NPE.NC.SPL.SA</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F7.md'>NMA.NC.PMC.F7</a> </td><td> Dorsal Rostral Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1053810011000080'>Cortico-Cortical Connectivity (MA -&gt; SA, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionNPE_FD_TH_OPV.md'>NPE.FD.TH.OPV</a> </td><td> <a href='BrainRegionNPE_NC_SPL_PG.md'>NPE.NC.SPL.PG</a> </td><td> Caudal Precuneus   </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainAreaNSA.md'>NSA</a> </td><td> <a href='BrainRegionNPE_FD_TH_OPV.md'>NPE.FD.TH.OPV</a> </td><td> <a href='BrainRegionNSA_NC_PG_S1.md'>NSA.NC.PG.S1</a> </td><td> Primary Somatosensory Cortex </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_IPS_MIP.md'>NPE.NC.IPS.MIP</a> </td><td> <a href='BrainRegionNSA_NC_IT_TEO.md'>NSA.NC.IT.TEO</a> </td><td> Preoccipital Inferotemporal Area </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (IT -&gt; IPS, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_SPL_PF.md'>NPE.NC.SPL.PF</a> </td><td> <a href='BrainRegionNSA_NC_IPS_VIP.md'>NSA.NC.IPS.VIP</a> </td><td> Ventral Intraparietal Sulcus </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0166223697010679'>Parietal Association Cortex (VIP -&gt; 7b)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_PG_S2.md'>NSA.NC.PG.S2</a> </td><td> Secondary Somatosensory Cortex </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_SPL_SA.md'>NPE.NC.SPL.SA</a> </td><td> <a href='BrainRegionNSA_NC_PG_PV.md'>NSA.NC.PG.PV</a> </td><td> Parietal Ventral Cortex </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionNPE_NC_SPL_SA.md'>NPE.NC.SPL.SA</a> </td><td> <a href='BrainRegionFEC_FD_TH_RIL.md'>FEC.FD.TH.RIL</a> </td><td> Rostral Intralaminar Nuclear Group of Thalamus </td><td> nucleus-neocortex </td><td> (unknown reference) </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionNPE_NC_IPS_MIP.md'>NPE.NC.IPS.MIP</a> </td><td> <a href='BrainRegionNCP_NC_MPL_PSCG.md'>NCP.NC.MPL.PSCG</a> </td><td> Posterior Cingulate Cortex </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_SPL_PF.md'>NPE.NC.SPL.PF</a> </td><td> <a href='BrainRegionNCP_NC_MPL_RSC.md'>NCP.NC.MPL.RSC</a> </td><td> Retrosplenial Cortex </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_SPL_SA.md'>NPE.NC.SPL.SA</a> </td><td> <a href='BrainRegionNCP_NC_INS_PIC.md'>NCP.NC.INS.PIC</a> </td><td> Posterior Insular Cortex </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionNPE_NC_SPL_PF.md'>NPE.NC.SPL.PF</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> Dorsal Anterior Cingulate Area </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (ParietalCortex -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_SPL_SA.md'>NPE.NC.SPL.SA</a> </td><td> <a href='BrainRegionNDM_NC_AL_ROFCM.md'>NDM.NC.AL.ROFCM</a> </td><td> Medial Rostral Orbitofrontal Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1053810011000080'>Cortico-Cortical Connectivity (SA -&gt; PFC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNPE_NC_SPL_PF.md'>NPE.NC.SPL.PF</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> Dorsal Caudal Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (SPL -&gt; dPM, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_SPL_SA.md'>NPE.NC.SPL.SA</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> Dorsal Caudal Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (SPL -&gt; dPM, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionNPE_NC_IPS_MIP.md'>NPE.NC.IPS.MIP</a> </td><td> <a href='BrainRegionNPE_NC_SPL_PG.md'>NPE.NC.SPL.PG</a> </td><td> Caudal Precuneus   </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (IPS -&gt; SPL, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNSA.md'>NSA</a> </td><td> <a href='BrainRegionNPE_NC_SPL_PF.md'>NPE.NC.SPL.PF</a> </td><td> <a href='BrainRegionNSA_NC_PO_PCC.md'>NSA.NC.PO.PCC</a> </td><td> Precentral Cortex  </td><td> neocortex-neocortex </td><td> (unknown reference) </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionNPE_NC_SPL_PF.md'>NPE.NC.SPL.PF</a> </td><td> <a href='BrainRegionFMM_FD_TH_LD.md'>FMM.FD.TH.LD</a> </td><td> Lateral Dorsal Nucleus of Thalamus </td><td> neocortex-nucleus </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (sLD -&gt; LD, abstract)</a> </td></tr></tbody></table>

<h2>Execution by Motion Inputs</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/NPE_NPS.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNPE_FD_TH_MPV.md'>NPE.FD.TH.MPV</a> </td><td> Medial Pulvinar       </td><td> nucleus     </td><td> NEU            </td><td> Integration of associative cortical information and projects to<br>
<br>
<BR><br>
<br>
visuomotor-related cortex </td><td> CG, PMC, PFC connections </td></tr>
<tr><td> <a href='BrainRegionNPE_NC_IPL_MST.md'>NPE.NC.IPL.MST</a> </td><td> Medial Superior Temporal Area </td><td> cortex, BA 39 </td><td> NEU            </td><td> Image stabilization, predictive target tracking </td><td> PG, Ventro-dorsal stream </td></tr></tbody></table>

<b>Internal Region Connections:</b>
<ul><li>no connections</li></ul>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNSA.md'>NSA</a> </td><td> <a href='BrainRegionNPE_NC_IPL_MST.md'>NPE.NC.IPL.MST</a> </td><td> <a href='BrainRegionNSA_FD_TH_IPV.md'>NSA.FD.TH.IPV</a> </td><td> Inferior Pulvinar  </td><td> nucleus-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (Pulvinar -&gt; ParietalCortex, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_OCC_MT.md'>NSA.NC.OCC.MT</a> </td><td> Middle Temporal Area </td><td> neocortex-neocortex </td><td> <a href='http://thebrain.mcgill.ca/flash/i/i_02/i_02_cr/i_02_cr_vis/i_02_cr_vis.html'>Paths from Retina to Parietal Cortex and IT (MT -&gt; MST)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_OCC_PO.md'>NSA.NC.OCC.PO</a> </td><td> Parietooccipital Area </td><td> neocortex-neocortex </td><td> <a href='http://thebrain.mcgill.ca/flash/i/i_02/i_02_cr/i_02_cr_vis/i_02_cr_vis.html'>Paths from Retina to Parietal Cortex and IT (PO -&gt; MST)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFAM.md'>FAM</a> </td><td> <a href='BrainRegionNPE_FD_TH_MPV.md'>NPE.FD.TH.MPV</a> </td><td> <a href='BrainRegionFAM_FD_TH_PT.md'>FAM.FD.TH.PT</a> </td><td> Paratenial Nucleus of Thalamus </td><td> nucleus-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (MID -&gt; mPULV, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionNPE_FD_TH_MPV.md'>NPE.FD.TH.MPV</a> </td><td> <a href='BrainRegionFMM_NC_PH_PER.md'>FMM.NC.PH.PER</a> </td><td> Perirhinal Cortex  </td><td> neocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (Perirhinal -&gt; mPULV)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_PRS.md'>FMM.NC.PH.PRS</a> </td><td> Presubiculum       </td><td> neocortex-nucleus </td><td> <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Contributions of Diencephalon to Recognition Memory (Presub -&gt; mPULV)</a> </td></tr>
<tr><td> <a href='BrainAreaLPC.md'>LPC</a> </td><td> <a href='BrainRegionNPE_FD_TH_MPV.md'>NPE.FD.TH.MPV</a> </td><td> <a href='BrainRegionLPC_FD_RT.md'>LPC.FD.RT</a> </td><td> Retina             </td><td> ganglion-nucleus </td><td> <a href='http://unifiedtao-en.blogspot.ru/2011/03/what-we-see-of-tao.html'>Retina and superior colliculus targets (Retina -&gt; Pulvinar, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLRC.md'>LRC</a> </td><td> <a href='BrainRegionNPE_FD_TH_MPV.md'>NPE.FD.TH.MPV</a> </td><td> <a href='BrainRegionLRC_MM_PT_PTA.md'>LRC.MM.PT.PTA</a> </td><td> Anterior Pretectum Nucleus </td><td> nucleus-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLRC_MM_PT_SL.md'>LRC.MM.PT.SL</a> </td><td> Sublentiform Nucleus </td><td> nucleus-nucleus </td><td> (unknown reference) </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionNPE_FD_TH_MPV.md'>NPE.FD.TH.MPV</a> </td><td> <a href='BrainRegionNCP_NC_MPL_PSCG.md'>NCP.NC.MPL.PSCG</a> </td><td> Posterior Cingulate Cortex </td><td> nucleus-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (Pulvinar -&gt; ParietalCortex, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_IPL_MST.md'>NPE.NC.IPL.MST</a> </td><td> <a href='BrainRegionNCP_NC_MPL_PSCG.md'>NCP.NC.MPL.PSCG</a> </td><td> Posterior Cingulate Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0149763409002061'>Contribution of hippocampal region CA3 to consciousness (IPL -&gt; PosteriorCingulate, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNDM.md'>NDM</a> </td><td> <a href='BrainRegionNPE_FD_TH_MPV.md'>NPE.FD.TH.MPV</a> </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCL.md'>NDM.NC.AL.DLPFCL</a> </td><td> Lateral Mid-Dorsolateral Prefrontal Cortex </td><td> nucleus-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Saccadic Vision (Thalamus -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNDM_NC_AL_ROFCL.md'>NDM.NC.AL.ROFCL</a> </td><td> Lateral Rostral Orbitofrontal Cortex </td><td> nucleus-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Saccadic Vision (Thalamus -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_IPL_MST.md'>NPE.NC.IPL.MST</a> </td><td> <a href='BrainRegionNDM_NC_AL_DACG.md'>NDM.NC.AL.DACG</a> </td><td> Dorsal Anterior Cingulate Area </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (ParietalCortex -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNDM_NC_AL_DLPFCR.md'>NDM.NC.AL.DLPFCR</a> </td><td> Rostral Mid-Dorsolateral Prefrontal Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1053810011000080'>Cortico-Cortical Connectivity (PTHA -&gt; PFC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNPE_NC_IPL_MST.md'>NPE.NC.IPL.MST</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F4.md'>NMA.NC.PMC.F4</a> </td><td> Ventral Caudal Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (IPL -&gt; vPM, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionNPE_NC_IPL_MST.md'>NPE.NC.IPL.MST</a> </td><td> <a href='BrainRegionNPE_NC_IPL_SMW.md'>NPE.NC.IPL.SMW</a> </td><td> Supramarginal Wernike Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.hindawi.com/journals/nri/2012/719056'>Visual Dorsal Pathway (MST -&gt; IPL, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNPE_NC_SPL_PG.md'>NPE.NC.SPL.PG</a> </td><td> Caudal Precuneus   </td><td> neocortex-neocortex </td><td> <a href='http://thebrain.mcgill.ca/flash/i/i_02/i_02_cr/i_02_cr_vis/i_02_cr_vis.html'>Paths from Retina to Parietal Cortex and IT (MST -&gt; 7a)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFMM.md'>FMM</a> </td><td> <a href='BrainRegionNPE_NC_IPL_MST.md'>NPE.NC.IPL.MST</a> </td><td> <a href='BrainRegionFMM_FT_HC_CA3D.md'>FMM.FT.HC.CA3D</a> </td><td> Distal CA1 of Hippocampus </td><td> neocortex-allocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0149763409002061'>Contribution of hippocampal region CA3 to consciousness (IPL -&gt; CA1, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionFMM_NC_PH_POR.md'>FMM.NC.PH.POR</a> </td><td> Postrhinal Cortex  </td><td> neocortex-neocortex </td><td> <a href='http://www.scholarpedia.org/article/Head_direction_cells'>Head Direction Cell Circuit (PC -&gt; PRHC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLRC.md'>LRC</a> </td><td> <a href='BrainRegionNPE_NC_IPL_MST.md'>NPE.NC.IPL.MST</a> </td><td> <a href='BrainRegionLRC_MM_SC_SUP.md'>LRC.MM.SC.SUP</a> </td><td> Superficial Superior Colliculus </td><td> neocortex-nucleus </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (ParietalCortex -&gt; SCi, abstract)</a> </td></tr></tbody></table>

<h2>Orienting by Visual Stimuli</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/NPE_ORV.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNPE_NC_IPS_LIP.md'>NPE.NC.IPS.LIP</a> </td><td> Lateral Intraparietal Sulcus </td><td> cortex, BA 39 </td><td> NEU            </td><td> Representing saliency of spatial locations, and attention to locations </td><td> Targeting eye movements </td></tr>
<tr><td> <a href='BrainRegionNPE_NC_OCC_V2PL.md'>NPE.NC.OCC.V2PL</a> </td><td> Secondary Visual Cortex, Pale Stripe </td><td> cortex      </td><td> NEU            </td><td> Extract form features </td><td>                 </td></tr>
<tr><td> <a href='BrainRegionNPE_NC_OCC_V3D.md'>NPE.NC.OCC.V3D</a> </td><td> Dorsal Associative Visual Cortex </td><td> cortex      </td><td> NEU            </td><td> Processing of global motion, orientation </td><td>                 </td></tr>
<tr><td> <a href='BrainRegionNPE_NC_OCC_V3V.md'>NPE.NC.OCC.V3V</a> </td><td> Ventral Associative Visual Cortex </td><td> cortex      </td><td> NEU            </td><td> Processing of dynamic shapes </td><td>                 </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNPE_NC_OCC_V2PL.md'>NPE.NC.OCC.V2PL</a> </td><td> <a href='BrainRegionNPE_NC_OCC_V3V.md'>NPE.NC.OCC.V3V</a> </td><td> neocortex-neocortex </td><td> <a href='http://thebrain.mcgill.ca/flash/i/i_02/i_02_cr/i_02_cr_vis/i_02_cr_vis.html'>Paths from Retina to Parietal Cortex and IT (V2 -&gt; V3, abstract)</a> </td></tr>
<tr><td> <a href='BrainRegionNPE_NC_OCC_V3D.md'>NPE.NC.OCC.V3D</a> </td><td> <a href='BrainRegionNPE_NC_IPS_LIP.md'>NPE.NC.IPS.LIP</a> </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0893608098000471'>Primate Control of Grasping (VC -&gt; PIP, abstract)</a> </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNSA.md'>NSA</a> </td><td> <a href='BrainRegionNPE_NC_IPS_LIP.md'>NPE.NC.IPS.LIP</a> </td><td> <a href='BrainRegionNSA_NC_OCC_MT.md'>NSA.NC.OCC.MT</a> </td><td> Middle Temporal Area </td><td> neocortex-neocortex </td><td> <a href='http://thebrain.mcgill.ca/flash/i/i_02/i_02_cr/i_02_cr_vis/i_02_cr_vis.html'>Paths from Retina to Parietal Cortex and IT (MT -&gt; LIP)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_OCC_PO.md'>NSA.NC.OCC.PO</a> </td><td> Parietooccipital Area </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0166223697010679'>Parietal Association Cortex (V6 -&gt; LIP)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_OCC_V2PL.md'>NPE.NC.OCC.V2PL</a> </td><td> <a href='BrainRegionNSA_NC_OCC_V1.md'>NSA.NC.OCC.V1</a> </td><td> Primary Visual Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S1053810011000080'>Cortico-Cortical Connectivity (V1 -&gt; VA, abstract)</a> </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNPE_NC_IPS_LIP.md'>NPE.NC.IPS.LIP</a> </td><td> <a href='BrainRegionNMA_NC_PMC_CFEF.md'>NMA.NC.PMC.CFEF</a> </td><td> Caudal Frontal Eye Field </td><td> neocortex-neocortex </td><td> <a href='http://www.cixip.com/index.php/page/content/id/1190'>Summary of eye movement control (PEF -&gt; FEF, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNMA_NC_PMC_F7.md'>NMA.NC.PMC.F7</a> </td><td> Dorsal Rostral Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0959438808001566'>Global visual system (ParietalCortex -&gt; FrontalCortex, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNSA.md'>NSA</a> </td><td> <a href='BrainRegionNPE_NC_IPS_LIP.md'>NPE.NC.IPS.LIP</a> </td><td> <a href='BrainRegionNSA_NC_IPS_AIP.md'>NSA.NC.IPS.AIP</a> </td><td> Anterior Intraparietal Sulcus </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0893608098000471'>Primate Control of Grasping (PIP -&gt; AIP, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_OCC_V3D.md'>NPE.NC.OCC.V3D</a> </td><td> <a href='BrainRegionNSA_NC_OCC_MT.md'>NSA.NC.OCC.MT</a> </td><td> Middle Temporal Area </td><td> neocortex-neocortex </td><td> <a href='http://thebrain.mcgill.ca/flash/i/i_02/i_02_cr/i_02_cr_vis/i_02_cr_vis.html'>Paths from Retina to Parietal Cortex and IT (V3 -&gt; MT, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_OCC_PO.md'>NSA.NC.OCC.PO</a> </td><td> Parietooccipital Area </td><td> neocortex-neocortex </td><td> <a href='http://thebrain.mcgill.ca/flash/i/i_02/i_02_cr/i_02_cr_vis/i_02_cr_vis.html'>Paths from Retina to Parietal Cortex and IT (V3 -&gt; PO, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_OCC_V3V.md'>NPE.NC.OCC.V3V</a> </td><td> <a href='BrainRegionNSA_NC_OCC_V4D.md'>NSA.NC.OCC.V4D</a> </td><td> Dorsal Visual Area V4 </td><td> neocortex-neocortex </td><td> <a href='http://thebrain.mcgill.ca/flash/i/i_02/i_02_cr/i_02_cr_vis/i_02_cr_vis.html'>Paths from Retina to Parietal Cortex and IT (V3 -&gt; V4, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_OCC_V4V.md'>NSA.NC.OCC.V4V</a> </td><td> Ventral Visual Area V4 </td><td> neocortex-neocortex </td><td> <a href='http://thebrain.mcgill.ca/flash/i/i_02/i_02_cr/i_02_cr_vis/i_02_cr_vis.html'>Paths from Retina to Parietal Cortex and IT (V3 -&gt; V4, abstract)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaLRC.md'>LRC</a> </td><td> <a href='BrainRegionNPE_NC_IPS_LIP.md'>NPE.NC.IPS.LIP</a> </td><td> <a href='BrainRegionLRC_MM_CJ.md'>LRC.MM.CJ</a> </td><td> Cajal Nucleus      </td><td> neocortex-nucleus </td><td> <a href='http://neuroscience.uth.tmc.edu/s3/chapter07.html'>Vision Components (VAC -&gt; SOA, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLRC_MM_RIMLF.md'>LRC.MM.RIMLF</a> </td><td> Rostral Interstitial Nucleus of MLF </td><td> neocortex-nucleus </td><td> <a href='http://neuroscience.uth.tmc.edu/s3/chapter07.html'>Vision Components (VAC -&gt; SOA, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLRC_MM_SC_SUP.md'>LRC.MM.SC.SUP</a> </td><td> Superficial Superior Colliculus </td><td> neocortex-nucleus </td><td> <a href='http://www.cixip.com/index.php/page/content/id/1190'>Summary of eye movement control (PEF -&gt; SC, abstract)</a> </td></tr>
<tr><td>                    </td><td> <a href='BrainRegionNPE_NC_OCC_V3D.md'>NPE.NC.OCC.V3D</a> </td><td> <a href='BrainRegionLRC_MM_CJ.md'>LRC.MM.CJ</a> </td><td> Cajal Nucleus      </td><td> neocortex-nucleus </td><td> <a href='http://neuroscience.uth.tmc.edu/s3/chapter07.html'>Eye blink reflex and pupillary light reflex (VAC -&gt; SupraOculomotor, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLRC_MM_RIMLF.md'>LRC.MM.RIMLF</a> </td><td> Rostral Interstitial Nucleus of MLF </td><td> neocortex-nucleus </td><td> <a href='http://neuroscience.uth.tmc.edu/s3/chapter07.html'>Eye blink reflex and pupillary light reflex (VAC -&gt; SupraOculomotor, abstract)</a> </td></tr></tbody></table>

<h2>Subcortical Execution Control</h2>


<img src='http://ahuman.googlecode.com/svn/images/dot/aHuman/NPE_SEC.dot.png' alt='unavailable'>

<table><thead><th> <b>Component ID</b> </th><th> <b>Component Name</b> </th><th> <b>Type</b> </th><th> <b>Service</b> </th><th> <b>Function</b> </th><th> <b>Comments</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNPE_FD_TH_LP.md'>NPE.FD.TH.LP</a> </td><td> Lateral Posterior Nucleus of Thalamus </td><td> nucleus     </td><td> NEU            </td><td> Visual association cortex </td><td> From superior colliculus, pretectum </td></tr>
<tr><td> <a href='BrainRegionNPE_NC_SPL_PG.md'>NPE.NC.SPL.PG</a> </td><td> Caudal Precuneus      </td><td> cortex, BA 07 </td><td> NEU            </td><td> Controlling spatially guided behavior with respect to visual and tactile<br>
<br>
<BR><br>
<br>
information </td><td> caudal, 7A=PG+Opt </td></tr></tbody></table>

<b>Internal Region Connections:</b>

<table><thead><th> <b>Source Region</b> </th><th> <b>Target Region</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <a href='BrainRegionNPE_FD_TH_LP.md'>NPE.FD.TH.LP</a> </td><td> <a href='BrainRegionNPE_NC_SPL_PG.md'>NPE.NC.SPL.PG</a> </td><td> nucleus-neocortex </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (LP -&gt; pLP, abstract)</a> </td></tr></tbody></table>

<b>External Inbound Region Connections:</b>

<table><thead><th> <b>Source Area</b> </th><th> <b>Local Region</b> </th><th> <b>Source Region</b> </th><th> <b>Source Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionNPE_NC_SPL_PG.md'>NPE.NC.SPL.PG</a> </td><td> <a href='BrainRegionNPE_NC_IPL_MST.md'>NPE.NC.IPL.MST</a> </td><td> Medial Superior Temporal Area </td><td> neocortex-neocortex </td><td> <a href='http://thebrain.mcgill.ca/flash/i/i_02/i_02_cr/i_02_cr_vis/i_02_cr_vis.html'>Paths from Retina to Parietal Cortex and IT (MST -&gt; 7a)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNPE_NC_IPS_MIP.md'>NPE.NC.IPS.MIP</a> </td><td> Medial Intraparietal Sulcus </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (IPS -&gt; SPL, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNSA.md'>NSA</a> </td><td> <a href='BrainRegionNPE_NC_SPL_PG.md'>NPE.NC.SPL.PG</a> </td><td> <a href='BrainRegionNSA_NC_IPS_VIP.md'>NSA.NC.IPS.VIP</a> </td><td> Ventral Intraparietal Sulcus </td><td> neocortex-neocortex </td><td> <a href='http://thebrain.mcgill.ca/flash/i/i_02/i_02_cr/i_02_cr_vis/i_02_cr_vis.html'>Paths from Retina to Parietal Cortex and IT (VIP -&gt; 7a)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_OCC_MT.md'>NSA.NC.OCC.MT</a> </td><td> Middle Temporal Area </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0166223697010679'>Parietal Association Cortex (V5A -&gt; 7a)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_OCC_PO.md'>NSA.NC.OCC.PO</a> </td><td> Parietooccipital Area </td><td> neocortex-neocortex </td><td> <a href='http://www.sciencedirect.com/science/article/pii/S0166223697010679'>Parietal Association Cortex (V6 -&gt; 7a)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNSA_NC_PG_S1.md'>NSA.NC.PG.S1</a> </td><td> Primary Somatosensory Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v3/n2/fig_tab/nrn726_F3.html'>McNaughton Spatial Processing Network (SomSensCortex -&gt; PosteriorParietalCortex)</a> </td></tr>
<tr><td> <font color='red'>Subcortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaFEC.md'>FEC</a> </td><td> <a href='BrainRegionNPE_FD_TH_LP.md'>NPE.FD.TH.LP</a> </td><td> <a href='BrainRegionFEC_FT_GPI_DL.md'>FEC.FT.GPI.DL</a> </td><td> Globus Pallidus Internal Dorsolateral </td><td> nucleus-nucleus-gaba </td><td> <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Saccadic Vision (BG -&gt; Thalamus, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaLRC.md'>LRC</a> </td><td> <a href='BrainRegionNPE_FD_TH_LP.md'>NPE.FD.TH.LP</a> </td><td> <a href='BrainRegionLRC_MM_PT_PTA.md'>LRC.MM.PT.PTA</a> </td><td> Anterior Pretectum Nucleus </td><td> nucleus-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLRC_MM_PT_SL.md'>LRC.MM.PT.SL</a> </td><td> Sublentiform Nucleus </td><td> nucleus-nucleus </td><td> (unknown reference) </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionLRC_MM_SC_SUP.md'>LRC.MM.SC.SUP</a> </td><td> Superficial Superior Colliculus </td><td> nucleus-nucleus </td><td> <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Thalamocortical relationships (sLP -&gt; LP, abstract)</a> </td></tr></tbody></table>

<b>External Outbound Region Connections:</b>

<table><thead><th> <b>Target Area</b> </th><th> <b>Local Region</b> </th><th> <b>Target Region</b> </th><th> <b>Target Name</b> </th><th> <b>Type</b> </th><th> <b>Reference</b> </th></thead><tbody>
<tr><td> <font color='red'>Cortical</font> </td><td>                     </td><td>                      </td><td>                    </td><td>             </td><td>                  </td></tr>
<tr><td> <a href='BrainAreaNCP.md'>NCP</a> </td><td> <a href='BrainRegionNPE_NC_SPL_PG.md'>NPE.NC.SPL.PG</a> </td><td> <a href='BrainRegionNCP_NC_MPL_RSC.md'>NCP.NC.MPL.RSC</a> </td><td> Retrosplenial Cortex </td><td> neocortex-neocortex </td><td> <a href='http://www.nature.com/nrn/journal/v3/n2/fig_tab/nrn726_F3.html'>McNaughton Spatial Processing Network (PosteriorParietalCortex -&gt; PCGRSP, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNMA.md'>NMA</a> </td><td> <a href='BrainRegionNPE_NC_SPL_PG.md'>NPE.NC.SPL.PG</a> </td><td> <a href='BrainRegionNMA_NC_PMC_F2.md'>NMA.NC.PMC.F2</a> </td><td> Dorsal Caudal Premotor Cortex </td><td> neocortex-neocortex </td><td> <a href='http://ahuman.googlecode.com/svn/research/articles/Biological/2008-dorsal-stream.pdf'>3 Visual Cortex Paths (SPL -&gt; dPM, abstract)</a> </td></tr>
<tr><td>                    </td><td>                     </td><td> <a href='BrainRegionNMA_NC_SMC_SEF.md'>NMA.NC.SMC.SEF</a> </td><td> Supplementary Eye Field </td><td> neocortex-neocortex </td><td> <a href='http://thebrainlabs.com/brain.shtml'>Movement Planning (PPC -&gt; SMC, abstract)</a> </td></tr>
<tr><td> <a href='BrainAreaNPE.md'>NPE</a> </td><td> <a href='BrainRegionNPE_NC_SPL_PG.md'>NPE.NC.SPL.PG</a> </td><td> <a href='BrainRegionNPE_FD_TH_OPV.md'>NPE.FD.TH.OPV</a> </td><td> Oral Pulvinar      </td><td> neocortex-nucleus </td><td> (unknown reference) </td></tr></tbody></table>

<h1>Thirdparty Circuits</h1>
(generated)<br>
<br>
<ul><li><a href='http://ars.els-cdn.com/content/image/1-s2.0-S0166223697010679-gr6.gif'>Parietal Association Cortex</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S0166223697010679'>Reference</a></li></ul>

<img src='http://ars.els-cdn.com/content/image/1-s2.0-S0166223697010679-gr6.gif' alt='unavailable'>

<ul><li><a href='http://thebrain.mcgill.ca/flash/a/a_02/a_02_cr/a_02_cr_vis/a_02_cr_vis_3a.jpg'>Paths from Retina to Parietal Cortex and IT</a> - see <a href='http://thebrain.mcgill.ca/flash/i/i_02/i_02_cr/i_02_cr_vis/i_02_cr_vis.html'>Reference</a></li></ul>

<img src='http://thebrain.mcgill.ca/flash/a/a_02/a_02_cr/a_02_cr_vis/a_02_cr_vis_3a.jpg' alt='unavailable'>

<ul><li><a href='http://ars.els-cdn.com/content/image/1-s2.0-S1053810011000080-gr3.jpg'>Cortico-Cortical Connectivity</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S1053810011000080'>Reference</a></li></ul>

<img src='http://ars.els-cdn.com/content/image/1-s2.0-S1053810011000080-gr3.jpg' alt='unavailable'>

<ul><li><a href='http://www.nature.com/nrn/journal/v3/n2/images/nrn726-f3.jpg'>McNaughton Spatial Processing Network</a> - see <a href='http://www.nature.com/nrn/journal/v3/n2/fig_tab/nrn726_F3.html'>Reference</a></li></ul>

<img src='http://www.nature.com/nrn/journal/v3/n2/images/nrn726-f3.jpg' alt='unavailable'>

<ul><li><a href='http://ars.els-cdn.com/content/image/1-s2.0-S0006899301025987-gr1.gif'>Horizontal saccades and smooth pursuit movements</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S0006899301025987'>Reference</a></li></ul>

<img src='http://ars.els-cdn.com/content/image/1-s2.0-S0006899301025987-gr1.gif' alt='unavailable'>

<ul><li><a href='http://www.nature.com/nrn/journal/v5/n3/images/nrn1345-i1.jpg'>Saccadic Vision</a> - see <a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>Reference</a></li></ul>

<img src='http://www.nature.com/nrn/journal/v5/n3/images/nrn1345-i1.jpg' alt='unavailable'>

<ul><li><a href='http://img.springerimages.com/Images/Springer/PUB=Springer-Verlag-Berlin-Heidelberg/JOU=00359/VOL=2005.191/ISU=3/ART=2004_565/MediaObjects/WATER_s00359-004-0565-9fhc1.jpg'>Oculomotor decision-making</a> - see <a href='http://www.springerimages.com/Images/LifeSciences/1-10.1007_s00359-004-0565-9-0'>Reference</a></li></ul>

<img src='http://img.springerimages.com/Images/Springer/PUB=Springer-Verlag-Berlin-Heidelberg/JOU=00359/VOL=2005.191/ISU=3/ART=2004_565/MediaObjects/WATER_s00359-004-0565-9fhc1.jpg' alt='unavailable'>

<ul><li><a href='http://www.hindawi.com/journals/nri/2012/719056.fig.001.jpg'>Visual Dorsal Pathway</a> - see <a href='http://www.hindawi.com/journals/nri/2012/719056'>Reference</a></li></ul>

<img src='http://www.hindawi.com/journals/nri/2012/719056.fig.001.jpg' alt='unavailable'>

<ul><li><a href='http://ars.els-cdn.com/content/image/1-s2.0-S0028393205003568-gr1.jpg'>Postero-lateral and medial views of hemisphere of human</a> - see <a href='http://www.sciencedirect.com/science/article/pii/S0028393205003568'>Reference</a></li></ul>

<img src='http://ars.els-cdn.com/content/image/1-s2.0-S0028393205003568-gr1.jpg' alt='unavailable'>

<ul><li><a href='http://cercor.oxfordjournals.org/content/early/2012/02/28/cercor.bhs048/F9.medium.gif'>IPL Receptors</a> - see <a href='http://cercor.oxfordjournals.org/content/early/2012/02/28/cercor.bhs048/F9.expansion.html'>Reference</a></li></ul>

<img src='http://cercor.oxfordjournals.org/content/early/2012/02/28/cercor.bhs048/F9.medium.gif' alt='unavailable'>

<ul><li><a href='http://learnmem.cshlp.org/content/18/6/384/F1.large.jpg'>Contributions of Diencephalon to Recognition Memory</a> - see <a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>Reference</a></li></ul>

<img src='http://learnmem.cshlp.org/content/18/6/384/F1.large.jpg' alt='unavailable'>

<ul><li><a href='http://what-when-how.com/wp-content/uploads/2012/04/tmp3649_thumb1_thumb.jpg'>Thalamocortical relationships</a> - see <a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>Reference</a></li></ul>

<img src='http://what-when-how.com/wp-content/uploads/2012/04/tmp3649_thumb1_thumb.jpg' alt='unavailable' height='400width=400'>


<h1>References</h1>
(generated)<br>
<br>
<ul><li><a href='http://www.sciencedirect.com/science/article/pii/S0166223697010679'>http://www.sciencedirect.com/science/article/pii/S0166223697010679</a>
</li><li><a href='http://thebrain.mcgill.ca/flash/i/i_02/i_02_cr/i_02_cr_vis/i_02_cr_vis.html'>http://thebrain.mcgill.ca/flash/i/i_02/i_02_cr/i_02_cr_vis/i_02_cr_vis.html</a>
</li><li><a href='http://www.sciencedirect.com/science/article/pii/S1053810011000080'>http://www.sciencedirect.com/science/article/pii/S1053810011000080</a>
</li><li><a href='http://www.nature.com/nrn/journal/v3/n2/fig_tab/nrn726_F3.html'>http://www.nature.com/nrn/journal/v3/n2/fig_tab/nrn726_F3.html</a>
</li><li><a href='http://www.sciencedirect.com/science/article/pii/S0006899301025987'>http://www.sciencedirect.com/science/article/pii/S0006899301025987</a>
</li><li><a href='http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html'>http://www.nature.com/nrn/journal/v5/n3/box/nrn1345_BX1.html</a>
</li><li><a href='http://www.springerimages.com/Images/LifeSciences/1-10.1007_s00359-004-0565-9-0'>http://www.springerimages.com/Images/LifeSciences/1-10.1007_s00359-004-0565-9-0</a>
</li><li><a href='http://www.hindawi.com/journals/nri/2012/719056'>http://www.hindawi.com/journals/nri/2012/719056</a>
</li><li><a href='http://www.sciencedirect.com/science/article/pii/S0028393205003568'>http://www.sciencedirect.com/science/article/pii/S0028393205003568</a>
</li><li><a href='http://cercor.oxfordjournals.org/content/early/2012/02/28/cercor.bhs048/F9.expansion.html'>http://cercor.oxfordjournals.org/content/early/2012/02/28/cercor.bhs048/F9.expansion.html</a>
</li><li><a href='http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html'>http://learnmem.cshlp.org/content/18/6/384/F1.expansion.html</a>
</li><li><a href='http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/'>http://what-when-how.com/neuroscience/the-thalamus-and-cerebral-cortex-integrative-systems-part-2/</a></li></ul>
