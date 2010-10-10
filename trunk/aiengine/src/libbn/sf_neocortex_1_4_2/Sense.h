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

#ifndef SenseH
#define SenseH

class Sense : public PatternSource
{
private:
	unsigned overlap; //number of overlapping pixels between adjacent parent sub-regions

public:
	Sense( unsigned sizeX , unsigned sizeY , unsigned overlap );

	void getPattern( unsigned x , unsigned y , unsigned sideCompr , unsigned *result );
	virtual unsigned getNameOutput( unsigned x, unsigned y ) { return( 0 ); };

	// Never called
	vector<double> getLambdaOutput(unsigned x, unsigned y) { std::vector<double> *lRet = NULL; return *lRet; };
	void setPiInput(unsigned x, unsigned y, vector<double> &pi) {};
};

class BitmapVision : public Sense {
private:
	TwoIndexArray<unsigned> pixArray;

public:
	BitmapVision( SFNeoCortex& nc , unsigned bitmapSizeX , unsigned bitmapSizeY );
	BitmapVision( unsigned x, unsigned y, unsigned overlap );

	TwoIndexArray<unsigned>& getBitmap() { return( pixArray ); };

	virtual unsigned getNameOutput( unsigned x, unsigned y );
	virtual int getSequence( unsigned x, unsigned y ) { return getNameOutput(x, y); } //dummy
	virtual void feedForward( unsigned learningRegion, bool feedbackStage );

	// See declaration in PatternSource
};

#endif
