#include "stdafx.h"

int main(int argc, char** argv)
{
	ServiceManager sm;
	sm.addPlatformServices();

	sm.createServices();
	sm.destroyServices();
}

