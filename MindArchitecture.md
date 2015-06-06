@@[Home](Home.md) -> [Architecture](Architecture.md) -> [MindArchitecture](MindArchitecture.md)



---


## Object Model ##

### Primary mind layers ###

  * mind target interface
    * MindTarget, MindSensor, MindEffector
    * MindSensorArea, MindEffectorArea
```
class MindTarget {MindSensorSet, MindEffectorSet, MindSensorArea, MindEffectorArea} in TOP
    (class SpecificMindTarget : MindTarget)
class MindSensorSet {MindSensor[]} in MindTarget
class MindEffectorSet {MindEffector[]} in MindTarget
class MindSensor : MindRegion {NeuroState, NeuroSignal} in MindSensorSet
    (class SpecificMindSensor : MindSensor)
class MindEffector : MindRegion in MindEffectorSet
    (class SpecificMindEffector : MindEffector)
class MindSensorArea : MindArea in MindTarget
class MindEffectorArea : MindArea in MindTarget
class MindSensorSetTracker in MindTarget
```
  * mind service
    * MindService, MindNet
```
class MindService {MindSpace, MindMap, MindNetSet, MindAreaSet, MindAreaLinkSet, MindActiveMemory} in TOP
class MindNet in MindNetSet
class MindNetSet {MindNet[]} in MindService
```
  * mind area
    * MindArea, MindAreaNet
    * PerceptionArea, ParietalArea, SomaticArea
    * LogicalCortexArea, FeelingCortexArea, PremotorCortexArea, MotorCortexArea
    * ThalamusArea, HippocampusArea, BasalGangliaArea
    * BrainStemArea, CranialNerveArea
    * SpinalCordArea, MotorNerveArea
```
class MindArea {MindRegionSet, MindRegionLinkSet, MindAreaNet[]} in MindAreaSet
    class ThalamusArea : MindArea
    class PerceptionArea : MindArea
    class SomaticArea : MindArea
    class HippocampusArea : MindArea
    class ParietalArea : MindArea
    class LogicalCortexArea : MindArea
    class FeelingCortexArea : MindArea
    class PremotorCortexArea : MindArea
    class MotorCortexArea : MindArea
    class BasalGangliaArea : MindArea
    class BrainStemArea : MindArea
    class SpinalCordArea : MindArea
    class BodyFeelingNerveArea : MindArea
    class CranialNerveArea : MindArea
    class MotorNerveArea : MindArea
class MindAreaSet {MindArea[]} in MindService
class MindAreaNet in MindArea
```
  * mind region
    * MindRegion
    * CortexRegion, NucleiRegion, NerveRegion
```
class MindRegion {NeuroPoolSet, NeuroLinkSet, MindLocation} in MindRegionSet
    class CortexRegion : MindRegion
    class NucleiRegion : MindRegion
    class NerveRegion : MindRegion
class MindRegionSet {MindRegion[]} in MindArea
class CortexRegionInfo in TOP
class NucleiRegionInfo in TOP
class NerveRegionInfo in TOP
```
  * mind matter
    * NeuroSignal, NeuroState, NeuroPool
    * NeuroLink, ExcitatoryLink, InhibitoryLink, ModulatoryLink
```
class NeuroState in MindSensor, specific MindRegion, NeuroPool
class NeuroSignal in MindSensor, specific MindRegion, MindMessage
class NeuroPool {NeuroState[], NeuroState} in NeuroPoolSet
class NeuroPoolSet {NeuroPool[]} in MindRegion
class NeuroLink in NeuroLinkSet
    class ExcitatoryLink : NeuroLink
    class InhibitoryLink : NeuroLink
    class ModulatoryLink : NeuroLink
class NeuroLinkSet {NeuroLink[]} in MindRegion
class NeuroLinkSource in MindRegion
class NeuroLinkTarget in MindRegion
```

### Auxiliary mind objects ###

  * mind stream
    * MindAreaLink, MindRegionLink
    * MindActiveMemory, MindMessage
```
class MindAreaLink {MindRegionLinkSet} in MindAreaLinkSet
class MindAreaLinkSet {MindAreaLink[]} in MindService
class MindRegionLink in MindRegionLinkSet
class MindRegionLinkSet {MindRegionLink[]} in MindArea, MindAreaLink
class MindActiveMemory in MindService
class MindMessage : BinaryMessage {NeuroSignal} in TOP
```
  * mind space
    * MindSpace
    * MindLocation, MindLocationInfo
```
class MindSpace in MindService
class MindLocation in MindAreaInfo, MindRegion
class MindLocationInfo in TOP
```
  * mind map
    * MindMap
    * MindNetInfo, MindNetworkType
    * MindLinkType, NeuroLinkInfo
    * MindAreaInfo, MindAreaLinkInfo, MindAreaNetInfo
```
class MindMap {MindNetInfo[], MindAreaInfo[], MindAreaLinkInfo[],
              MindNetworkType[], MindLinkType[]} in MindService
class MindNetInfo in MindMap
class MindNetworkType in MindMap
class MindAreaInfo {MindLocation, MindAreaNetInfo[]} in MindMap
class MindAreaNetInfo in MindAreaInfo
class MindAreaLinkInfo in MindMap
class MindLinkType {NeuroLinkInfo[]} in MindMap
class NeuroLinkInfo in MindLinkType
```
  * mind base
```
(low-level data types)
```