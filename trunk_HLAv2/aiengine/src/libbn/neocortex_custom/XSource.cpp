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

XPatternSource::XPatternSource(unsigned x, unsigned y, unsigned pSeqLen)
{
	outputsX = x;
	outputsY = y;
	sequenceLength = pSeqLen;
	patternNumber = 0;
	parent = NULL;
}

//return the pattern for Sub-region (x, y) in the calling region
//sideCompr is calling region's side compression
//the result 1-D array must be allocated before
void XPatternSource::getPattern(unsigned x, unsigned y, unsigned sideXCompr, unsigned sideYCompr, unsigned *result)
{
	unsigned resultIndex = 0;
	for(unsigned i = x * sideXCompr; i < (x+1) * sideXCompr; i++)
		for(unsigned j = y * sideYCompr; j < (y+1) * sideYCompr; j++)
			result[resultIndex++] = getNameOutput(i, j);
}

void XPatternSource::getLambda(unsigned x, unsigned y, unsigned sideXCompr, unsigned sideYCompr, vector<vector<double> > &result)
{
	result.resize(0);
	for(unsigned i = x * sideXCompr; i < (x+1) * sideXCompr; i++)
		for(unsigned j = y * sideYCompr; j < (y+1) * sideYCompr; j++)
			result.push_back(getLambdaOutput(i, j));
}

void XPatternSource::setPi(unsigned x, unsigned y, unsigned sideXCompr, unsigned sideYCompr, vector<vector<double> > &pi)
{
	int piIndex = 0;
	int lPiSize = pi.size();

	for(unsigned i = x * sideXCompr; i < (x+1) * sideXCompr; i++)
		for(unsigned j = y * sideYCompr; j < (y+1) * sideYCompr; j++)	{
			// DG Check valid
			if ( piIndex < lPiSize ) {
				setPiInput(i, j, pi[piIndex++]);
			}
		}
}

XContextSource::XContextSource() {
	child = NULL;
}
