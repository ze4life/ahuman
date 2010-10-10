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
*/

#include "sf_neocortex.h"

Sense::Sense(unsigned x, unsigned y, unsigned ovlap) : PatternSource(x, y, 1)
{
	overlap = ovlap;
}

//return the pattern for Sub-region (x, y) in the calling region
//sideCompr is calling region's side compression
//the result 1-D array must be allocated before
//eye must take overlap into account
void Sense::getPattern(unsigned x, unsigned y, unsigned sideCompr, unsigned *result)
{
	unsigned resultIndex = 0;
	unsigned pixelIncrement = sideCompr - overlap;
	for(unsigned i = x * pixelIncrement; i < x * pixelIncrement + sideCompr; i++)
		for(unsigned j = y * pixelIncrement; j < y * pixelIncrement + sideCompr; j++)
			result[resultIndex++] = getNameOutput(i, j);
}

/////////////////// BitmapVision //////////////////////////////////////
BitmapVision::BitmapVision( SFNeoCortex& nc , unsigned bitmapSizeX , unsigned bitmapSizeY )
:	Sense(nc.sensorAreaSideX, nc.sensorAreaSideY, nc.overlapSubRegions )
{
	parent = NULL;
	pixArray.create( bitmapSizeX , bitmapSizeY );
}

BitmapVision::BitmapVision(unsigned x, unsigned y, unsigned ovlap)
:	Sense(x, y, ovlap) 
{
	parent = NULL;
}

//assume Bitmap is assigned
void BitmapVision::feedForward(unsigned learningRegion, bool feedbackStage)
{ 
	parent -> feedForward(learningRegion, feedbackStage);
}

//feed forward the value of the pixel
unsigned BitmapVision::getNameOutput(unsigned x, unsigned y)
{
	return pixArray[x][y];
}
