@@[Home](Home.md) -> [SensorsResearch](SensorsResearch.md) -> [SensorsDigital2NeuralTransformation](SensorsDigital2NeuralTransformation.md)

---


## Capture events ##

Certain:
  * conscious capture is performed by event
  * event is either control change command or spotted changes in external properties
  * conscious capture depends on capture resolution and capture area

Uncertain:
  * sensor has unconscious ongoing capture with constant low resolution but wide area
  * sensor can generate either full set of properties or only delta to previous transfer

## External stream ##

Certain:
  * one external stream item is transformed into zero, one or more sensor stream item
  * external item can be ignored if sensor stream is not consumed in time

Uncertain:
  * set of events produce external stream

## Sensor stream ##

Certain:
  * sensor stream has neural representation
  * sensor stream item is represented by vector of variables
  * sensor stream item is represented by sequence of vectors
  * sequence can be of different length depending on focus
  * width is the number of vector variables
  * all items of one sequence have the same width - sequence width

Uncertain:
  * vector variable is float
  * sensor stream is stateless - every sensor item is derived only from one external item
  * different sequences can have different width
  * sequence has energy which is proportional to sequence width and length
  * sequence energy is external stream item energy multiplied by energy amplifier
  * energy amplifier factor is part of focus conrol state

## Sensor neuron ##

Certain:
  * each vector variable corresponds to specific sensor neuron
  * sensor neuron can have multiple connections to neocortex networks
  * one sensor neuron represents the same external properties for the same resolution

Uncertain:
  * sensor neuron does not have fixed semantic
  * one sensor neuron can represent different external properties for different resolutions

## Finally for the project purposes ##

  * conscious capture by event
  * full property set transfer
  * throtteling of external stream
  * external stream item is represented by variable-length sequence of sensor stream items
  * float variables