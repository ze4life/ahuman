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

/*#########################################################################*/
/*#########################################################################*/

class XNeoRegion : public XPatternSource, public XContextSource {
private:
	unsigned thisRegionLevel;           //level of region in hierarchy (0-lowest)
	unsigned thisRegionSideXCompression; //how many times the side of forward input is compressed
	unsigned thisRegionSideYCompression; //how many times the side of forward input is compressed
	unsigned subRegionInputCount;//number of inputs to a Sub-region (space) 
	XSubRegion ***subRegions;
	XLearnedSequence *mem; //[NeoParameters::MaxMemSize]; //learned vectors for this region
	unsigned memCount;       //number of filled spots in memory array

	unsigned int thisMaxMemSize;
	unsigned lowUsageFailureCount;

public:
	XNeoRegion( XNeoCortex& nc, unsigned outputSizeX, unsigned outputSizeY, unsigned sequenceLength, unsigned sideXCompression, unsigned sideYCompression, unsigned regionLevel );
	virtual ~XNeoRegion();

// ContextSource
public:
	virtual void feedForward(unsigned learningRegion, bool feedbackStage);
	virtual void contextual();
	virtual int getSequence(unsigned x, unsigned y);
	virtual unsigned getMemCount() { return memCount; }

// PatternSource
public:
	virtual vector<double> getLambdaOutput(unsigned x, unsigned y);
	virtual void setPiInput(unsigned x, unsigned y, vector<double> &pi);
	virtual unsigned getNameOutput(unsigned x, unsigned y);

// others
public:
	// counting discarded new patterns
	void InitLowUsageFailureCount() { lowUsageFailureCount = 0; };
	unsigned GetLowUsageFailureCount() { return lowUsageFailureCount; };
	
	// forget learned sequences if frequency less than ct.RegionForgetThreshold / frequency of sequence delimiting ct.RegionForgetThreshold sequences sorted by frequence
	void forgetRareMemories( bool forgettingOn );
	// forget memory item
	void forgetMemory( unsigned memPos );
	// initialise after all regions created
	void initForInference();
	// initialise before recognition
	void beginRecognition();
	// find pattern
	void recognize();

	// access to memory from subregions
	XLearnedSequence& memory( unsigned index );
	// add sequence to memory - called from subregions
	int addSequence( XSequence &s );

private:
	void getLevel0Lambda( unsigned xPos , unsigned yPos , vector<vector<double> > &lambda );
};
