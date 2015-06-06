@@[Home](Home.md) -> [MemoryPredictionResearch](MemoryPredictionResearch.md) -> [NumentaResearch](NumentaResearch.md)

---


## References ##

  * Jeff Hawkins and others - [Sequence memory for prediction, inference and behaviour](http://rstb.royalsocietypublishing.org/content/364/1521/1203.full.pdf) - This paper proposes how each region of neocortex might learn the sequences necessary for this theory
  * 2010 Lecture by Jeff Hawkins - [link](http://www.youtube.com/watch?v=TDzr0_fbnVk)
  * 2010 Understanding the Bitworm NuPIC HTM Example Program - [Link](http://www.openicon.com/mu/mu_blog/2010/mu_04_04_2010.html)

## Hierarchical Memory Models ##

  * **Spatial only**: Convolutional Neural Networks (Le Cun & Bengio) - 1995; HMAX (Riesenhuber & Poggio) - 1999
  * **Temporal**: HHMM - hierarchical hidden Markov model (Fine et al.) - 1998
  * **Spatial and Temporal**: HTM (Numenta) - 2005

## Constraints ##

Requirements that a biological sequence memory must meet, which are different from linear computer memory.

  * **Probabilistic prediction** - input and prediction are probability distributions
  * **Simultaneous learning and recall** - simultaneously recalling and predicting
  * **Auto-associative recall** - recognize sequences even if it is presented with a partial sequence from the middle of a previously learned sequence; naturally auto-associative
  * **Variable-order memory** - ‘ABCDE’ and ‘YBCDZ’ - correctly predict the last element of the sequence based on an input that occurred many time steps earlier; the internal representation of an afferent pattern must change depending on the temporal context in which it occurs; the representation for the elements ‘B’, ‘C’ and ‘D’ must be somehow different when preceded by ‘A’ than by ‘Y’
  * **Biological constraints** - any proposed mechanism should map to one or more prominent features of neocortical anatomy

## Biological Implications ##

  * **Sparsification of response** - general cell activity in the neocortex should become more sparse and selective when receiving input in naturally occurring sequences versus receiving spatial inputs in temporal isolation or random order; sparse encoding - efficient method of representation in neural tissue
  * **Inhibitory requirements** - excitatory lateral input to one or a few cells inhibits all the other cells in the near proximity; this laterally induced inhibition must be stronger and faster than the feed-forward excitation
  * **Distributed representations** - distributed representations in two ways:
    * in almost all cases, multiple cells are simultaneously active, although the pattern of activation will always be sparse
    * activations are distributed; every region of the hierarchy passes a distribution of potentially active sequences to its parent regions
  * **Efficient computation** - use information from previous inputs when making predictions, and both the history of inputs and the forward predictions are distributions over many states; calculation using dynamic programming by Bellman (see George, D. 2008 How the brain might work: a hierarchical and temporal model for learning and recognition. PhD thesis, Stanford University. §4.6.2)
  * **Cortical layers** - some cell layers are learning feed-forward sequences (layers 4 and 3) and other layers are learning feedback sequences (layers 2 and 6). Layer 5 is where they are combined to form a belief
  * **Sequence timing** - remember the duration for each element in the sequence; can speed up or slow down a recalled sequence, but the absolute duration of the sequence elements is stored and can be recalled; needs a neural mechanism that can encode the durations of sequence elements; this neural mechanism should exist in all regions of the neocortex and should be tightly coupled with the sequence memory mechanism; duration limits need not be fixed, but could depend on the parameters of the model
  * **Memory capacity** - if have 12 columns each with 50 cells, where each column represents one of the 12 musical tones inWestern music, then:
    * it could learn a single sequence of 600 notes using exactly 50 of each of the 12 tones
    * it could learn 100 sequences of six notes each
    * capacity of HTM derives primarily from the hierarchy, not the sequence memory in each node; the hierarchy allows learned sequences to be used repeatedly in different combinations

## Implementation Hints ##

cortex implementation:
  * columns with neurons having the same inputs
  * lateral excitatory and inhibitory connections to model sequence activation; in human brain neocortex lateral connections are 90%, with only 10% feed-forward ones
  * if one cell in the column becomes active it uses inhibitory lateral connections to hide other cells in the same column - "shut up the other guys"

general:
  * bayesian network
  * dynamic programming by Bellman to re-use history
  * FDR - Fixed-sparsity Distributed Representation

spatial details:
  * RBFs are used to make quantization points
  * continuous representaion is ultimate goal, still not implemented in HTM

temporal patterns:
  * variable-order Markov chain
  * sequences of different length
  * no sequence begin/end marks
  * able to match sequence by middle part
  * state-splitting algorithm
  * store duration for each sequence item

## Regions ##

  * Region 1: run Spatial Pooler ->
  * Region 1: run Temporal Pooler (form sequence memory) ->
  * Region 2: run Spatial Pooler -> ...