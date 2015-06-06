@@[Home](Home.md) -> [Features](Features.md) -> [MindTargetFeatures](MindTargetFeatures.md)

---


## Modeling Tool ##

**Actuator Representation**:
  * assign actuators to area in target.xml and reflect it in area-aligned diagrams
  * add sensor/motor to diagram as picture using approach at http://www.graphviz.org/content/kennedyanc
    * add actuators for related area on area-aligned pages in area cluster
    * add actuators as non-cluster to circuit-aligned pages only if explicitly referenced by means of 

&lt;receptorlink region="region" receptor="receptor"/&gt;

 or 

&lt;effectorlink region="region" effector="effector"/&gt;


    * automatically add actuators directly linked to focus items in region-aligned diagrams as non-cluster
    * labels like "Sensor: eye"
  * define picture in target.xml
  * reference links with actuators in connectivity tables
  * sensor and motor nodes should have green and blue colors respectively, links to them better have dotted style.
  * if implemented, feature will make e.g. http://code.google.com/p/ahuman/wiki/BrainAreaVBA page much more consistent and explaining neural workflow.