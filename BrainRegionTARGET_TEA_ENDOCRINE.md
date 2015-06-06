@@[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [BrainAreaTEA](BrainAreaTEA.md) -> [BrainRegionTARGET\_TEA\_ENDOCRINE](BrainRegionTARGET_TEA_ENDOCRINE.md)

---


This page covers biological details of component Endocrine Glands.
Region is part of aHuman target integrated biological model.

  * **Top-down path to region**: Target -> Human Effectors (aHumanEffectors) -> Endocrine Glands (TARGET.TEA.ENDOCRINE) (see [Mind Maps](OverallMindMaps.md))
  * **Type**: effector
  * **Brain area**: [Effector Area](BrainAreaTEA.md)
  * **Role**: unknown
  * **Function**: Secrete hormones directly into the circulatory system to be carried toward a distant target organ
(generated)
# Components #
(generated)


**Component items**:
  * **Endocrine head** (**endocrine-head**)
    * **Endocrine - pituitary gland**: release hormones by request from HT
      * Adenohypophysis ([LAC.FD.HT.AR](BrainRegionLAC_FD_HT_AR.md) -> endocrine-adenohypophysis): secrete releasing hormones into blood
        * **Distal Part of Hypophysis**
        * **Intermediate Part of Hypophysis**
        * **Tuberal Part of Hypophysis**
      * Neurohypophysis ([LAC.FD.HT.SO](BrainRegionLAC_FD_HT_SO.md) -> endocrine-neurohypophysis-vasopressin): transport vasopressin secreted in hypothalamus to blood
        * **Infundibular Stem**
        * **Pars Nervosa of Hypophysis**
      * Nucleus of Medial Eminence ([LAC.FD.HT.PV](BrainRegionLAC_FD_HT_PV.md) -> endocrine-neurohypophysis-oxytocin): transport oxytocin secreted in hypothalamus to blood
        * **Anterior Median Eminence**
        * **Posterior Median Eminence**
      * **Lateral Eminence of Hypophysis**
    * **Endocrine - pineal gland** (**endocrine-pineal-gland**): control of sexual development
  * **Endocrine neck** (**endocrine-neck**)
    * [Endocrine - thyroid gland](http://en.wikipedia.org/wiki/Thyroid) ([LAC.PN.SYM.MCG](BrainRegionLAC_PN_SYM_MCG.md) -> [endocrine-thyroid-gland](HumanMusclesHead.md)): release thyroid hormones into blood to rise oxygen use and heat production
    * [Endocrine - parathyroid gland](http://en.wikipedia.org/wiki/Thyroid) ([LAC.PN.SYM.MCG](BrainRegionLAC_PN_SYM_MCG.md) -> [endocrine-parathyroid-gland](HumanMusclesHead.md)): release parathyroid hormones into blood to increase in blood calcium levels
  * **Endocrine body** (**endocrine-body**)
    * **Endocrine - pancreas** (**endocrine-pancreas**): release digestive enzymes that act in small intestine to increase rate of glucose uptake and metabolism by most body cells
      * [Endocrine - pancreas, sympathetic](http://en.wikipedia.org/wiki/Pancreas) ([LAC.PN.SYM.CEG](BrainRegionLAC_PN_SYM_CEG.md) -> [endocrine-pancreas-adrenergic](HumanMusclesHead.md)): sympathetic, a2: decreases secretion from beta cells, increases secretion from alpha cells, b2: increases secretion from beta cells
      * [Endocrine - pancreas, parasympathetic](http://en.wikipedia.org/wiki/Pancreas) ([LAC.PN.PSYM.GUT](BrainRegionLAC_PN_PSYM_GUT.md) -> [endocrine-pancreas-muscarinic](HumanMusclesHead.md)): parasympathetic, stimulates insulin secretion, M3: increases stimulation of alpha cells and beta cells
    * [Endocrine - adrenal gland](http://en.wikipedia.org/wiki/Adrenal_gland) ([LAC.PN.SYM.SMG](BrainRegionLAC_PN_SYM_SMG.md) -> [endocrine-adrenal-gland](HumanMusclesTorso.md)): releasing hormones in response to stress
  * **Endocrine - gonads** (**endocrine-gonads**): release estrogen, progesterone and testosterone hormones to promote maturation of reproductive organs
    * [Endocrine - testicle gland](http://en.wikipedia.org/wiki/Testicle) ([LAC.PN.SYM.ARG](BrainRegionLAC_PN_SYM_ARG.md) -> [endocrine-testicle-gland](HumanMusclesTorso.md)): produce androgens, primarily testosterone (growth of muscle mass and strength, regulator of cognitive and physical energy, sperm development
    * [Endocrine - ovary gland](http://en.wikipedia.org/wiki/Ovary) ([LAC.PN.SYM.ARG](BrainRegionLAC_PN_SYM_ARG.md) -> [endocrine-ovary-gland](HumanMusclesTorso.md)): secretes estrogen (maturation and maintenance of the reproductive organs), testosterone (prepares the uterus for pregnancy, and the mammary glands for lactation) and progesterone (promoting menstrual cycle changes in the endometrium

# Connectivity #
(generated)


![http://ahuman.googlecode.com/svn/images/dot/aHuman/TARGET.TEA.ENDOCRINE.dot.png](http://ahuman.googlecode.com/svn/images/dot/aHuman/TARGET.TEA.ENDOCRINE.dot.png)

**Inbound Region Connections:**

| **Source Area** | **Source Region** | **Source Name** | **Type** | **Reference** |
|:----------------|:------------------|:----------------|:---------|:--------------|
| [FAM](BrainAreaFAM.md) | [FAM.FD.MHB](BrainRegionFAM_FD_MHB.md) | Medial Habenula | endocrine-pineal-gland | [Habenula Connections (MHb -> PB)](http://www.scholarpedia.org/article/Habenula) |
| [LAC](BrainAreaLAC.md) | [LAC.FD.HT.AR](BrainRegionLAC_FD_HT_AR.md) | Arcuate Nucleus of Hypothalamus | endocrine-adenohypophysis | (unknown reference) |
|                 | [LAC.FD.HT.PV](BrainRegionLAC_FD_HT_PV.md) | Paraventricular Nucleus | endocrine-neurohypophysis-oxytocin | [Amygdalar disruption of prefrontal cortex (HT.PV -> PUT)](http://neuropolitics.org/defaultmay10.asp) |
|                 | [LAC.FD.HT.SO](BrainRegionLAC_FD_HT_SO.md) | Supraoptic Nucleus | endocrine-neurohypophysis-vasopressin | (unknown reference) |
|                 | [LAC.PN.PSYM.GUT](BrainRegionLAC_PN_PSYM_GUT.md) | Parasympathetic Gut Brain | endocrine-pancreas-muscarinic | (unknown reference) |
|                 | [LAC.PN.SYM.ARG](BrainRegionLAC_PN_SYM_ARG.md) | Aorticorenal Ganglion | endocrine-ovary-gland | (unknown reference) |
|                 | [LAC.PN.SYM.CEG](BrainRegionLAC_PN_SYM_CEG.md) | Coelic Ganglion | endocrine-pancreas-adrenergic | (unknown reference) |
|                 | [LAC.PN.SYM.MCG](BrainRegionLAC_PN_SYM_MCG.md) | Middle Cervical Ganglion | endocrine-parathyroid-gland | (unknown reference) |
|                 | [LAC.PN.SYM.SMG](BrainRegionLAC_PN_SYM_SMG.md) | Superior Mesenteric Ganglion | endocrine-adrenal-gland | (unknown reference) |

**Outbound Region Connections:**
  * no connections

# Thirdparty Circuits #
(generated)

  * [Habenula Connections](http://www.scholarpedia.org/w/images/thumb/2/2d/Hb-connections-small.jpg/800px-Hb-connections-small.jpg) - see [Reference](http://www.scholarpedia.org/article/Habenula)

<img src='http://www.scholarpedia.org/w/images/thumb/2/2d/Hb-connections-small.jpg/800px-Hb-connections-small.jpg' alt='unavailable'>

<ul><li><a href='http://neuropolitics.org/connect-amygdala.jpg'>Amygdalar disruption of prefrontal cortex</a> - see <a href='http://neuropolitics.org/defaultmay10.asp'>Reference</a></li></ul>

<img src='http://neuropolitics.org/connect-amygdala.jpg' alt='unavailable'>


<h1>References</h1>
(generated)<br>
<br>
<ul><li><a href='http://www.scholarpedia.org/article/Habenula'>http://www.scholarpedia.org/article/Habenula</a>
</li><li><a href='http://neuropolitics.org/defaultmay10.asp'>http://neuropolitics.org/defaultmay10.asp</a></li></ul>
