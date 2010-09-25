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

#include <vector>

using namespace std;

class NeoRegion;
class Sequence;
class SFNeoCortex;

class SubRegion {
private:
	SFNeoCortex& neocortex;

	unsigned sequenceLength; //number of steps that form a sequence (time)
	unsigned inputCount;     //number of inputs (space)
	NeoRegion &myRegion;
	int nameOutput; //output value of the Sub-region; negative values are special situations
	unsigned memIndex; //for level1 indexes in Mem
	Sequence *currentSequence;

	//vector<vector<double> > cCPDMatrix;
	// This is a map based sparse matrix to replace <vector<vector>>
	std::map<AccessKey, double> cpdMatrix;
	std::vector<double> belStar, lambdaOut, piIn;

	struct BestMatch {
		//Sequence * Sequence;
		double precision;
		unsigned int index;
	};

	void findBestMatch( Sequence &s , unsigned &retIndex , double &retPrecision );
	int findLowUsage( unsigned maxUsage );

public:
	SubRegion( SFNeoCortex& nc , unsigned sequenceLength , unsigned inputCount , NeoRegion &r );
	virtual ~SubRegion();

	bool feedForward( unsigned *pattern , bool memorize , unsigned pLowUsageThreshold );
	void contextual( unsigned parentContext );
	void initForInference( unsigned parentMemCount );
	void beginRecognition( unsigned parentMemCount );
	void recognize( vector<vector<double> > &lambda , vector<vector<double> > &piOut );

	vector<double> getLambdaOutput();
	void setPiInput( vector<double> &pi );
	unsigned getNameOutput();
};
