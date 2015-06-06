@@[Home](Home.md) -> [BiologicalLifeResearch](BiologicalLifeResearch.md) -> [BrainAreaTEA](BrainAreaTEA.md) -> [BrainRegionTARGET\_TEA\_URETER](BrainRegionTARGET_TEA_URETER.md)

---


This page covers biological details of component Ureter.
Region is part of aHuman target integrated biological model.

  * **Top-down path to region**: Target -> Human Effectors (aHumanEffectors) -> Ureter (TARGET.TEA.URETER) (see [Mind Maps](OverallMindMaps.md))
  * **Type**: effector
  * **Brain area**: [Effector Area](BrainAreaTEA.md)
  * **Role**: unknown
  * **Function**: Extract urine from blood in kidney and propel urine to urinary bladder and to outside
(generated)
# Components #
(generated)


**Component items**:
  * **Ureter sensory data** (**ureter-sensory-data**)
    * Ureter - ureter visceral receptors (ureter-visceral-receptors -> [LPC.PN.SG.LDRG](BrainRegionLPC_PN_SG_LDRG.md)): respond to stretch and free nerve endings in the bladder mucosa that respond to pain and temperature
  * **Ureter autonomic** (**ureter-autonomic**)
    * [Ureter - detrusor urinae muscle, parasympathetic](http://en.wikipedia.org/wiki/Detrusor_urinae_muscle) ([LAC.PN.PSYM.PPG](BrainRegionLAC_PN_PSYM_PPG.md) -> [detrusor-urinae-muscle-parasympathetic](HumanMusclesTorso.md)): parasympathetic contracts, to urinate
    * [Ureter - internal sphincter muscle of urethra, parasympathetic](http://en.wikipedia.org/wiki/Internal_sphincter_muscle_of_urethra) ([LAC.PN.PSYM.PPG](BrainRegionLAC_PN_PSYM_PPG.md) -> [internal-urethral-sphincter-parasympathetic](HumanMusclesTorso.md)): parasympathetic relaxes the muscle
    * [Ureter - detrusor urinae muscle, sympathetic](http://en.wikipedia.org/wiki/Detrusor_urinae_muscle) ([LAC.PN.SYM.IMG](BrainRegionLAC_PN_SYM_IMG.md) -> [detrusor-urinae-muscle-sympathetic](HumanMusclesTorso.md)): sympathetic relaxes, to store urine
    * [Ureter - internal sphincter muscle of urethra, sympathetic](http://en.wikipedia.org/wiki/Internal_sphincter_muscle_of_urethra) ([LAC.PN.SYM.IMG](BrainRegionLAC_PN_SYM_IMG.md) -> [internal-urethral-sphincter-sympathetic](HumanMusclesTorso.md)): sympathetic contracts the muscle
  * **Ureter conscious** (**ureter-conscious**)
    * [Ureter - external sphincter muscle of female urethra](http://en.wikipedia.org/wiki/External_sphincter_muscle_of_female_urethra) ([LPC.SC.VH.ONF](BrainRegionLPC_SC_VH_ONF.md) -> [external-urethral-sphincter-female](HumanMusclesTorso.md)): control urination, constricts urethra, maintain urinary continence
    * [Ureter - external sphincter muscle of male urethra](http://en.wikipedia.org/wiki/External_sphincter_muscle_of_male_urethra) ([LPC.SC.VH.ONF](BrainRegionLPC_SC_VH_ONF.md) -> [external-urethral-sphincter-male](HumanMusclesTorso.md)): control urination, constricts urethra, maintain urinary continence

# Connectivity #
(generated)


![http://ahuman.googlecode.com/svn/images/dot/aHuman/TARGET.TEA.URETER.dot.png](http://ahuman.googlecode.com/svn/images/dot/aHuman/TARGET.TEA.URETER.dot.png)

**Inbound Region Connections:**

| **Source Area** | **Source Region** | **Source Name** | **Type** | **Reference** |
|:----------------|:------------------|:----------------|:---------|:--------------|
| [LAC](BrainAreaLAC.md) | [LAC.PN.PSYM.PPG](BrainRegionLAC_PN_PSYM_PPG.md) | Pelvic Peripheral Ganglion | detrusor-urinae-muscle-parasympathetic | (unknown reference) |
|                 | [LAC.PN.SYM.IMG](BrainRegionLAC_PN_SYM_IMG.md) | Inferior Mesenteric Ganglion | detrusor-urinae-muscle-sympathetic | (unknown reference) |
| [LPC](BrainAreaLPC.md) | [LPC.SC.VH.ONF](BrainRegionLPC_SC_VH_ONF.md) | Onuf's Nucleus  | external-urethral-sphincter-female | (unknown reference) |

**Outbound Region Connections:**

| **Target Area** | **Target Region** | **Target Name** | **Type** | **Reference** |
|:----------------|:------------------|:----------------|:---------|:--------------|
| [LPC](BrainAreaLPC.md) | [LPC.PN.SG.LDRG](BrainRegionLPC_PN_SG_LDRG.md) | Lower Dorsal Root Ganglion | ureter-visceral-receptors | (unknown reference) |

# Thirdparty Circuits #
(generated)

  * no circuits defined

# References #
(generated)

  * no references defined
