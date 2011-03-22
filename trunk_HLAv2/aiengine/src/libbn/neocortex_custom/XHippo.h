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

CUSTOMIZED
*/

/*#########################################################################*/
/*#########################################################################*/

class XHippocampus : public XContextSource {
private:
	XNeoCortex& nc;
	Logger logger;

	// initial parameters
	unsigned maxMemorySize;
	unsigned hippoOutputSizeX;
	unsigned hippoOutputSizeY;
	unsigned srcPatchSizeX; // number of children = SideCompression*SideCompression
	unsigned srcPatchSizeY; // number of children = SideCompression*SideCompression

	// calculated
	unsigned hippoOutputSize;

	std::string *mem; //[thisMaxMemSize];
	unsigned memCount;        // number of filled spots in memory array
	int sequenceOutput;
	vector<double> belStar;
	vector<double> piIn;
	vector<double> combinedBelief;
	vector<double> maxBel;
	vector<unsigned> maxIndex;

// ContextSource
public:
    virtual void feedForward(int learningRegion, bool feedbackStage) {};
    virtual void contextual() {};
    virtual unsigned getMemCount() { return memCount; }
	virtual int getSequence( unsigned xPos , unsigned yPos ) { return sequenceOutput; }

public:
    XHippocampus( XNeoCortex& nc , unsigned srcPatchSizeX , unsigned srcPatchSizeY , unsigned hippoOutputSizeX , unsigned hippoOutputSizeY , unsigned maxMemorySize );
    ~XHippocampus() { delete [] mem; };

    void setTextOutput( std::string name );

    void initForInference();
    void beginRecognition();
    void recognize();

    void displayResults( bool pLog , bool pImages );
    void calculateResults( unsigned saccadeCount );
    std::string getResultName( unsigned resultNumber );    

    void displayAllMemories();
};
