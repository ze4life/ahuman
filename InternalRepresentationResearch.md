@@[Home](Home.md) -> [NeoCortexResearch](NeoCortexResearch.md) -> [InternalRepresentationResearch](InternalRepresentationResearch.md)

---


## References ##

  * High level requirements - see http://code.google.com/p/ahuman/wiki/aMatterRequirements

## Final Design ##

  * spatial poolers - several, overlapping
  * temporal poolers - several

## Constructing Regions ##

Source parameters:
  * input rectangular region of size X,Y
  * outputs is also some rectangle, where each output item is probability of corresponding sequence
  * low-probability items will not be activated if use accumulated activation
  * spacial factor defines how big are recognised spacial patterns
  * temporal factor defines how complex can be recognised sequence - temporal pattern
  * depth factor defines how complex is spacial-temporal pattern

Sequences and Columns:
  * item corresponds to cortical column
  * column stores spacial-temporal sequence
  * until allocated (filled), column is empty or half-empty
  * column defines maximum sequence size
  * half-empty sequence can be recognised, not trying to enlarge - means supporting variable-length sequences
  * so column can be: empty, partial/full unrecognized/recognised
  * column is recognised if frequence is high enough
  * sequence can be forgotten by column

Regions:
  * biologically plausible is having several regions equivalent in inputs/output sizes
  * can enlarge from bottom (intput) to top (output)
  * can have asymmetric sizes compression
  * if area overlap is zero, then input item is presented only in one output item; it means spacial inputs patterns are mapped to several outputs items, no one item represents whole picture; input pattern is represented by output pattern
  * if area overlap is not zero - then it can require too many regions to enable represent any inputs pattern by one outputs item
  * if find most active column on top level it is classical Jeff's HTM