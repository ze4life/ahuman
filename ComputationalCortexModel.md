@@[Home](Home.md) -> [NeoCortexResearch](NeoCortexResearch.md) -> [ComputationalCortexModel](ComputationalCortexModel.md)

---


This page covers describing model of neocortex region which satisfies requirements.
The model show architectural implementation details which demonstrate how required workflow cases are implemented.

## Thoughts ##

  * consider sequence - word "concatenation"
    * sequences are based on emotional stressing - con-cate-nation
    * consider you start hearing "ncate"
    * you will ignore "n" as it could be part of "in category"
    * you will surely map "cate" to strong subsequence
    * so your expected word will be "cate-gory"
    * you will recognise "(con)-cate-nation" - after hearing "nation" - like you go to wrong direction then confused and returned to the forked way
  * consider similarity between invariant representation in neocortex and error function as content of feed-forward flow
    * invariant representation of auditory information - relative intervals, not absolute notes are stored and recognized