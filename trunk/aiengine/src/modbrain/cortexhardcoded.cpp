#include "brain_impl.h"

CortexHardcoded::CortexHardcoded( MindArea *p_area , int p_inputs , int p_outputs , CortexEventHandler *p_handler )
{
	area = p_area;
	inputs = p_inputs;
	outputs = p_outputs;
	handler = p_handler;

	// reflect created
	handler -> onCreate();
}

CortexHardcoded::~CortexHardcoded()
{
	// reflect destroyed
	handler -> onDestroy();
}

void CortexHardcoded::updateInputs()
{
	handler -> onInputsUpdated();
}

void CortexHardcoded::updateOutputs()
{
	handler -> onOutputsUpdated();
}
