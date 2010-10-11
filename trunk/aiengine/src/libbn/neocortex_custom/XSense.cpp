/*
Neocortex - Memory-Prediction Framework
Copyright (C) 2007 Saulius J. Garalevicius
Modified by David Green (QT based GUI, event-model data sources, User interface enhancements)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

CUSTOMISED
*/

#include "XNeoCortex.h"

/*#########################################################################*/
/*#########################################################################*/

XSense::XSense( unsigned sizeX , unsigned sizeY ) : XPatternSource( sizeX , sizeY , 1 )
{
}

// return the pattern for Sub-region (x, y) in the calling region
// the result 1-D array must be allocated before
// eye must take overlap into account
void XSense::getPattern( unsigned posX , unsigned posY , unsigned sizePatchX , unsigned sizePatchY , unsigned overlap , unsigned *result)
{
	unsigned resultIndex = 0;
	unsigned incrementX = sizePatchX - overlap;
	unsigned incrementY = sizePatchY - overlap;
	for( unsigned i = posX * incrementX; i < posX * incrementX + sizePatchX; i++ )
		for( unsigned j = posY * incrementY; j < posY * incrementY + sizePatchY; j++ )
			result[resultIndex++] = getNameOutput(i, j);
}

//assume input data are set
void XSense::feedForward( unsigned learningRegion , bool feedbackStage )
{ 
	parent -> feedForward(learningRegion, feedbackStage);
}

/*#########################################################################*/
/*#########################################################################*/

XDirectSense::XDirectSense( unsigned *p_externalData , unsigned sizeX , unsigned sizeY )
:	XSense( sizeX , sizeY ) ,
	externalData( p_externalData )
{
}

unsigned XDirectSense::getNameOutput( unsigned posX , unsigned posY )
{
	return( externalData[ posY * XPatternSource::outputsX + posX ] );
}

/*#########################################################################*/
/*#########################################################################*/

XOwnedSense::XOwnedSense( unsigned sizeX , unsigned sizeY )
:	XSense( sizeX , sizeY )
{
	parent = NULL;
	data.create( sizeX , sizeY );
}

// feed forward the value of the pixel
unsigned XOwnedSense::getNameOutput( unsigned x , unsigned y )
{
	return data[x][y];
}

/*#########################################################################*/
/*#########################################################################*/
