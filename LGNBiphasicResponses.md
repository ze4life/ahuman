[Home](Home.md) -> [SensorsResearch](SensorsResearch.md) -> [VisionResearch](VisionResearch.md) -> [LGNBiphasicResponses](LGNBiphasicResponses.md)



---


**Article:**
  * Predictive Feedback Can Account for Biphasic Responses in the Lateral Geniculate Nucleus, 2009 - Janneke F. M. Jehee, Dana H. Ballard

# Abstract #

  * **biphasic neural response** - best response when quick switching between two opposite patterns - detected in LGN, V1, MT
  * article describes: **hierarchical model of predictive coding** and simulations that capture these temporal variations in neuronal response properties
  * focus on the **LGN-V1 circuit**
  * after training on natural images the model exhibits the brain’s LGN-V1 connectivity structure:
    * structure of V1 receptive fields is linked to the spatial alignment and properties of center-surround cells in the LGN
    * spatio-temporal response profile of LGN model neurons is biphasic in structure, resembling the biphasic response structure of neurons in cat LGN
    * model displays a specific pattern of influence of feedback, where LGN receptive fields that are aligned over a simple cell receptive field zone of the same polarity decrease their responses while neurons of opposite polarity increase their responses with feedback
  * predictive feedback is a general coding strategy in the brain

# Introduction #

  * layout of V1-to-LGN feedback connections follows the structure of LGN-to-V1 feedforward connections
  * LGN cells have center-surround organization
  * LGN regions switch between bright- to dark-excitatory in 20 ms
    * what computational reason can change preferred simulus
    * biphasic dynamics follow from neural mechanisms of **predictive coding**
  * to be efficient - early-level visual processing removes correlations in the input, resulting in a more sparse and statistically independent output
    * early visual areas remove correlations by removing the predictable components in their input
    * center-surround structure of LGN receptive fields can be explained using predictive coding mechanisms - center pixel intensity value can be replaced with the difference between the center value and a prediction from a linear weighted sum of its surrounding values
  * works for interaction of lower-order and higher-order visual areas
    * low-order and high-order visual areas are reciprocally connected
    * higher-level receptive fields represent the predictions of the visual world
    * lower-level areas signal the error between predictions and actual visual input
    * explains end-stopping

![http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/LGN-V1.png](http://ahuman.googlecode.com/svn/images/wiki/research/biomodel/LGN-V1.png)

# Results #

## Hierarchical model of predictive coding ##

  * two layers - LGN and V1
  * Steps
    * 1. V1 receives input from LGN
    * 2. V1 neuron with receptive field that best matched the input feeds its prediction back to LGN
    * 3. LGN neurons compute error between prediction and actual input
    * 4. LGN sends error forward to correct prediction
    * 5. process is repeated, single feedforward-feedback cycle takes around 20 milliseconds
  * connection weights of the model are adapted to the input by minimizing the description length or entropy of the joint distribution of inputs and neural responses
    * minimizes the model’s prediction errors
    * improves the sparseness of the neural code
    * model converges to a set of connection weights that is optimal for predicting that input

## LGN-V1 connectivity structure after training ##

  * feedforward connection weights from on-center type and off-center type LGN cells coding for the same spatial location are summed for each of the model’s 128 V1 cells
    * V1 responses in the model are linear across their on and off inputs
    * after training, the receptive fields show orientation tuning as found for simple cells in V1
  * relation between the learned receptive fields in model V1 and the properties of LGN units:
    * connections are initially random and are adjusted as a consequence of the model’s learning rule together with exposure to natural images
    * after training, on- and off-center units are spatially aligned with the on- and off-zones of the model V1 receptive field

## Reversal of polarity due to predictive feedback ##

  * first consider a **model with non-biphasic inputs**
    * spatio-temporal response of model on-center type geniculate cells is calculated using a reverse correlation algorithm
    * as in cat LGN, model on-center type receptive fields are arranged in center and surround, and the bright-excitatory phase is followed by a dark-excitatory phase
    * removing feedback in the model causes the previously biphasic responses to disappear
  * then model is modified to **simulate biphasic retinal inputs**
    * temporal response profile of model on-center type cells is obtained using reverse correlation
    * predictive feedback interactions cause reversals of polarity in LGN to be more pronounced than the retinal input
  * why **biphasic responses appear in the mapped model LGN receptive fields**
    * reverse correlation leads to visual changes occurring much faster than most natural input the system would encode
    * consider stimulus consisting primarily of bright regions
    * on-center type LGN cells will respond to the onset of this stimulus
    * on zones in the LGN are linked to on zones of receptive fields in V1, which soon start to increase activation and make predictions
    * by the time that predictions of the first stimulus arrive in lower-level areas, areas, the initial representation of the bright stimulus has been replaced by a second white noise stimulus, and the prediction is compared against a new and unexpected stimulus representation
    * in reverse correlation, predictive processing shows up as a comparison against this running average whitenoise stimulation
    * predicted bright region is of higher luminance than the average second stimulus, causing off-center type cells to respond to the offset of the bright reference stimulus
  * reversals in polarity of model LGN cells are most profound in a small time window after presentation of the reference stimulus but disappear gradually later on
    * initial prediction is dynamically updated to include predictions of stimuli presented after the reference stimulus
    * new predictions are closer to the average white-noise stimulation
    * reversals in polarity will appear as long as predictions deviate from the average white-noise stimulation
    * precise amount of overlap between prediction and stimulus is not critical
  * simple cell off-zones mediate inhibitory influences to off-center LGN cells and excitatory influences to on-center LGN cells
  * for all model on or off-center LGN receptive fields that are aligned over a V1 receptive field region of the same polarity, firing rates decrease due to feedback
  * where the overlapping fields are of reversed polarity, there is an increase in firing rate
  * neurophysiology: influence of V1 simple cells on LGN on- and off-cells is phase-reversed

# Discussion #

  * model that encodes an image using predictive feedforward-feedback cycles:
    * can learn the brain’s LGNV1 connectivity structure
    * structure of V1 receptive fields is linked to the spatial alignment and properties of centersurround cells in the LGN
    * captures reversals in polarity of neuronal responses in LGN
    * captures phase-reversed pattern of influence from V1 simple cells on LGN cells
  * confirms idea that visual system uses predictive feedforward-feedback interactions to efficiently encode natural input
  * natural visual world is dominated by low temporal frequencies
    * retinal image to be relatively stable over the periods of time considered in the model
    * under certain conditions visual inputs do change rapidly—more rapidly than most natural inputs the system would encode
  * geniculate cells receive many more feedback connections (~30%) than feedforward connections (~10%)
    * feedback signals from V1 affect the response properties of LGN cells
    * feedback from V1 seems to affect the strength of center-surround interactions in LGN
    * LGN cells respond strongly to bars that are roughly the same size as the center of their receptive field
    * responses are attenuated or eliminated when the bar extends beyond the receptive field center (end-stopping)
    * this property has been found to depend on feedback signals from V1
  * previous model
    * captured endstopping and some other modulations
    * predictive feedback model was trained on natural images, in which lines are usually longer rather than shorter
    * higher-level receptive fields optimized for representing longer bars
    * when presented with shorter bars, the model’s higher-level units could not predict their lower-level input, error responses in the lower-level neurons could not be suppressed
  * in new model the predictive feedback framework also includes rebound effects in LGN
    * biphasic responses are stronger in geniculate neurons than in the retinal neurons
    * result from predictive feedback interactions, similar to endstopping and some other inhibitory effects
    * reversals in polarity have also been described for several cortical areas that do not receive direct input from biphasic retinal cells
  * other explanations of stronger biphasic responses in the LGN
    * higher LGN thresholds
    * inhibitory feedback from the perigeniculate nucleus
    * feedforward inhibition
  * framework features:
    * captures biphasic responses and orientation selectivity
    * captures phase-reversed influence of cortical feedback to LGN
    * explains end-stopping and some other modulations due to surround inhibition in V1 and LGN
    * explains reversals in polarity for many areas in cortex
  * computationally advantageous to implement predictive operations through feedback projections
    * allow the system to remove redundancy and decorrelate visual responses between areas
    * higher-level cortical receptive fields are larger and encode more complex stimuli
    * allows predictions of higher complexity and larger regions in the visual field
  * biphasic responses are attenuated in the LGN, or absent in cortex, without cortical feedback
  * model uses subtractive feedback to compare higher-level predictions with actual lower-level input
    * could be mediated by, for example, local inhibitory neurons in the same-level area together with long-range excitatory connections from the next higher-level area
  * model could easily be extended to include more cortical areas
    * each level would have both coding units and difference detecting units
    * coding units predict their lower-level input
    * coding units convey the current estimate to the error detectors of the same-level area
    * error detectors then signal the difference between their input and its prediction to the next higher level
    * finally one prediction becomes dominant in the entire system
  * more accurate higher-level predictions (or equivalently greater overlap between the visual input and higher-level receptive fields) results in reduced activity of lower-level difference detectors
    * when top-down predictions in the model are off, lower-level difference detectors enhance their responses
    * higher-level coding neurons enhance their activity when stimuli are presented that match their receptive field properties
    * subsequent feedforward-feedback passes refine the initial predictions, until finally the entire system settles on the mostly likely interpretation
  * recurrent cycles of processing are less costly in time when the system forms a hierarchy
    * most likely predictions are computed first and sent on to higher-level processing areas, which do not have to wait to begin their own computations, enabling initial rapid gist-of-the-scene processing and subsequent feedforward-feedback cycles to fill in the missing details
    * some global aspects of a stimulus can be detected very rapidly while detailed aspects are reported later in time
  * top-down signals serve many computational functions
    * sparsifying mechanism
    * effect of top-down signals in general is not best described as either inhibitory or excitatory
    * higher-level areas feed anticipatory signals back to earlier areas, enhancing neural responses to a stimulus that would otherwise fall below threshold
    * excitatory interaction between higher-level anticipation and the incoming lower-level signal
    * feedback could also act as a bayesian style prior, and adapt early level signals according to different sensory or behavioral conditions
    * mechanism presented here should be regarded as a relatively lowlevel mechanism that automatically creates sparser solutions
  * rebound effects are a common feature in reverse correlation mapping and have been described in several visual areas
    * biphasic responses have been found for neurons in LGN and V1
    * reversals in selectivity in the motion domain have also been found for neurons in MT