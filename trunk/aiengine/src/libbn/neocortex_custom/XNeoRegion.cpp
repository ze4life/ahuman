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

#include "XNeoCortex.h"

XNeoRegion::XNeoRegion( XNeoCortex& nc , unsigned outputSizeX , unsigned outputSizeY , unsigned pSeqLen , unsigned sideXCompression , unsigned sideYCompression , unsigned regionLevel )
:	XPatternSource(outputSizeX, outputSizeY, pSeqLen), XContextSource( nc ) {
	thisRegionLevel = regionLevel;
	thisRegionSideXCompression = sideXCompression;
	thisRegionSideYCompression = sideYCompression;
	subRegionInputCount = thisRegionSideXCompression * thisRegionSideYCompression; //number of inputs to a Sub-region
	memCount = 0;
	thisMaxMemSize = neocortex.regionMemorySize[ thisRegionLevel ];

	// Initialise memory - we could create it as we go along but in practice the memory always fills up anyway so better do it here
	// This leaves open the possibility of 'grafting' new memory on later.
	// Maybe in a real brain if the memory fills up there is a mechanism for growing more.
	// The premise here is that, in adults at least, we normally have fixed amount of tissue to work with.
	mem = new XLearnedSequence[thisMaxMemSize];

	subRegions = new XSubRegion**[outputsX];
	for( unsigned i = 0; i < outputsX; i++ ) {
		subRegions[i] = new XSubRegion*[outputsY];
		for(unsigned j = 0; j < outputsY; j++)
			subRegions[i][j] = new XSubRegion( nc , sequenceLength , subRegionInputCount , *this );
	}
}

XNeoRegion::~XNeoRegion() {
	for( unsigned x = 0; x < outputsX; x++ ){
		for(unsigned y = 0; y < outputsY; y++)
			delete subRegions[x][y];

		delete subRegions[x];
	}

	delete subRegions;
	delete [] mem;
}

//take inputs, process them and remember the output
void XNeoRegion::feedForward(unsigned learningRegion, bool feedbackStage)
{
	unsigned lLowUsageThreshold = 0;
	unsigned *pattern = new unsigned[subRegionInputCount];
	bool memorize = learningRegion == thisRegionLevel && !feedbackStage;
	unsigned x, y;
	for(x = 0; x < outputsX; x++) {
		for(y = 0; y < outputsY; y++) {
			child -> getPattern( x , y , thisRegionSideXCompression , thisRegionSideYCompression , pattern );

			// Version 1.4
			lLowUsageThreshold = neocortex.regionLowUsageThreshold[ learningRegion ];

			bool lRetcode = subRegions[x][y] -> feedForward( pattern , memorize , lLowUsageThreshold ); //process and remember output
			// Version 1.4    - there is only one error condition that is reported
			//                - it happens if a low usage slot cannot be found.
			if ( !lRetcode ) {
				lowUsageFailureCount++;
			}
		}
	}

	delete pattern;

	if( ++patternNumber == sequenceLength ) { //sequence processed and names are ready
		if( thisRegionLevel < learningRegion )   //stop feed-forward chain at learning region
			parent -> feedForward( learningRegion , feedbackStage );

		patternNumber = 0;
	}
}

void XNeoRegion::contextual(){ //parent is the learning region
	unsigned x, y, parentContext;
	for(x = 0; x < outputsX; x++)
		for(y = 0; y < outputsY; y++) {
			parentContext = parent -> getSequence(x, y); //name output from parent
			subRegions[x][y] -> contextual(parentContext);
		}
}

void XNeoRegion::forgetRareMemories( bool pForgettingOn )
{
	unsigned lTotalObserved = 0;
	unsigned lOldMemCount = memCount;

	// Just display total frequency and return
	if ( !pForgettingOn ) {
		for(unsigned j = 0; j < memCount; j++) { 
			unsigned lFrequency = mem[j].getFrequency();
			lTotalObserved += lFrequency;
		}

		std::ostringstream  lLogStream;
		lLogStream << "Region " << thisRegionLevel << " total observations: " << lTotalObserved;
		lLogStream << ". Number of Memories: " << memCount;
		// cGuiUtils->Summary( std::string( lLogStream.str() ) );
		return;
	}

	// For forgetting by percentage
	std::vector<unsigned>lFrequencies;
	for(unsigned j = 0; j < memCount; j++) { 
		unsigned lFrequency = mem[j].getFrequency();
		lTotalObserved += lFrequency;
		lFrequencies.push_back(lFrequency);
	}

	std::sort(lFrequencies.begin(), lFrequencies.end());
	int frequency = ( int )( memCount * neocortex.regionForgetThreshold[ thisRegionLevel ] / 100 );
	float lPercentageThreshold = (float)lFrequencies[ frequency ];

	float lMemThreshold = 0.0;
	if( neocortex.deletionByPercentage ) {
		lMemThreshold = lPercentageThreshold;
	}
	else {
		// Original calculation
		lMemThreshold = ( float )( neocortex.regionForgetThreshold[ thisRegionLevel ] * (float) lTotalObserved / (float) ( memCount ) );
	}

	if ( lMemThreshold > 0 ) {
		for(unsigned i = 0; i < memCount; i++)
			if( mem[i].getFrequency() < lMemThreshold ) { //forget this sequence
				mem[i--].assign( mem[--memCount] ); //overwrite with last element
			}
	}

	neocortex.log( String( "Region " ) + thisRegionLevel + " total observations: " + lTotalObserved );
	if (lMemThreshold > 0 ) {
		neocortex.log( String( "Memories before forgetting: " ) + lOldMemCount + ", Memories after forgetting : " + memCount );
	}
	else {
		neocortex.log( String( "Number of Memories: " ) + lOldMemCount );
	}
}

void XNeoRegion::initForInference(){
	for(unsigned x = 0; x < outputsX; x++)
		for(unsigned y = 0; y < outputsY; y++)
			subRegions[x][y] -> initForInference( parent -> getMemCount() );

	neocortex.log( String( "NeoRegion::initForInference - " ) + thisRegionLevel + " level memories: " + memCount );
}

void XNeoRegion::beginRecognition() {
	for(unsigned x = 0; x < outputsX; x++)
		for( unsigned y = 0; y < outputsY; y++ )
			subRegions[x][y] -> beginRecognition( parent -> getMemCount() );
}

//lambda = 1 x 139 from uniqueL1_vectors
//lambda is exponential of the hamming distance between the input and each unique vector
void XNeoRegion::getLevel0Lambda( unsigned x , unsigned y , vector<vector<double> > &lambda ) {
	unsigned i, j;
	int hammDist;
	unsigned *pattern = new unsigned[ subRegionInputCount ];
	double newLambda;
	child -> getPattern( x , y , thisRegionSideXCompression , thisRegionSideYCompression , pattern ); //image patch from Eye
	lambda.resize(1);
	lambda[0].resize(0);

	for( i = 0; i < memCount; i++ ) { //hamming distance
		hammDist = 0;
		for(j = 0; j < subRegionInputCount; j++)
			hammDist += pattern[j] ^ mem[i].getElement( 0 , j );

		newLambda = exp(-((double)hammDist*(double)hammDist));
		lambda[0].push_back(newLambda);
	}

	delete pattern;
}

void XNeoRegion::recognize(){
	vector<vector<double> > lambda, piOut;

	for( unsigned x = 0; x < outputsX; x++)
		for(unsigned y = 0; y < outputsY; y++){
			//get lambda from each child of the region
			//(similarity to observed patterns from children)
			if( thisRegionLevel == 0 )
				getLevel0Lambda( x , y , lambda ); //lambda = 1 x 139 from uniqueL1_vectors
			else //ThisRegionLevel=1: 4x1037, ThisRegionLevel=2: 16x91
				child -> getLambda( x , y , thisRegionSideXCompression , thisRegionSideYCompression , lambda );

			subRegions[x][y] -> recognize( lambda , piOut );
			child -> setPi( x , y , thisRegionSideXCompression , thisRegionSideYCompression , piOut ); //distribute PiOut to each child of the region
		}
}

vector<double> XNeoRegion::getLambdaOutput(unsigned x, unsigned y){
	return subRegions[x][y] -> getLambdaOutput();
}

void XNeoRegion::setPiInput( unsigned x , unsigned y , vector<double> &pi ) {
	subRegions[x][y] -> setPiInput( pi );
}

unsigned XNeoRegion::getNameOutput( unsigned x , unsigned y ) {
	return subRegions[x][y] -> getNameOutput();
}

//x, y are the coordinates of a Sub-region in lower region that is requesting the sequence
int XNeoRegion::getSequence( unsigned x , unsigned y ) {
	unsigned mySubRegionX = x / thisRegionSideXCompression; //coordinates of the column of current region
	unsigned mySubRegionY = y / thisRegionSideYCompression;
	return subRegions[ mySubRegionX ][ mySubRegionY ] -> getNameOutput();
}

XLearnedSequence &XNeoRegion::memory(unsigned index) {
	if( index < memCount )
		return mem[index];
	else {
		neocortex.log( String( "Memory index: " ) + index + " is out of bounds." );
		// DG 05/05/2008 This is not ideal but does output some information
		//               The fault is probably non-recoverable.
		return * ( new XLearnedSequence() ); 
	}
}

void XNeoRegion::forgetMemory( unsigned i )
{
	mem[i].assign( mem[--memCount] ); //overwrite element [i] with last element and free the last element
}

// Returns -1 if memory is full
int XNeoRegion::addSequence( XSequence &s )
{
	if( memCount < thisMaxMemSize ) {
		// MemCount is one more than the current maximum index
		// But MemCount is the old value and we do have a new entry
		mem[memCount++].assign(s); // set frequency to 1
		// Success in assigning new memory
		return memCount-1;
	}
	else {
		// Failed to assign
		return -1;
		//std::ostringstream  lLogStream;
		//lLogStream << "Cannot add sequence at: " << MemCount << " memory is full."; //<< std::endl; 
		//cGuiUtils->Log( std::string( lLogStream.str() ) );
	}
	//   throw std::exception("Cannot add sequence: memory full.");
}
