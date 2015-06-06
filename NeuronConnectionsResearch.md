@@[Home](Home.md) -> [NeuralNetworksResearch](NeuralNetworksResearch.md) -> [NeuronConnectionsResearch](NeuronConnectionsResearch.md)

---


## What are connections ##

  * connection is made between two neurons
    * connection is uni-directional
    * source of connection is always axon branch of first neuron
    * target of connection can be dendrite, soma or initial axon segment of second neuron
    * axon-axon connections are usually ignored in neural network models
  * axon-dendrite connection elements are:
    * neuron1 soma
    * neuron1 initial axon segment
    * neuron1 axon trunk (myelinated)
    * neuron1 axon branchX
    * neuron1 axon branchX terminal
    * inter-neuron space (synaptic cleft)
    * receptors of post-synaptic cell membrane on spine of neuron2 dendrite
    * neuron2 dendrite trunk
    * neuron2 soma
  * there are two types of synapses, electrical and chemical
    * **electrical synapse** - protein junction forms hole between axon terminal and post-synaptic neuron membranes, allowing the electrical signal to pass directly from one cell to another;
    * electrical synapse is much faster than chemical synapse, but unlike chemical synapse, cannot be regulated or controlled
    * **chemical synapses** may be regulated and are affected by methamphetamine, signals always travel from presynaptic membrane, through synaptic cleft, and to postsynaptic membrane

## Connection dynamics ##

  * connection can be stronger or weaker, thus having connectivity factor (see Jeff Hawkins)
  * above certain connectivity factor threshold connection allows signal propagation, when presynaptic signal (action potential) produces post-synaptic signal
  * below threshold connection still exists, because activity in both neurons affects connectivity factor
  * connectivity factor differs from connection weight of classical neural networks, as weight always produces output which depends on weight value; connectivity factor is continuous, but its effect is binary

## When connection is enforced ##

**Options under consideration**:
  * when signal propagates through connection
  * when action potential encounters fire state (Hebb's learning), e.g.:
    * just after firing there is negative potential in all dendrites
    * which electically attracts axon terminal having positive action potential
    * while firing is impossible (refractory period) and action potential energy is spent for increasing connectivity factor
  * using interneurons and non-neuron interneuron matter (glia)
  * using complex structures as controllers (bump attractors and so on)