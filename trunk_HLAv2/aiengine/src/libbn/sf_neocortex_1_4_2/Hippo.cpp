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

Hippocampus::Hippocampus(SFNeoCortex& nc , unsigned sideComprX , unsigned sideComprY ) 
:	ContextSource( nc ) 
{
	memCount = 0;
	sequenceOutput = SFNeoCortex::OUTPUT_NONE;
	sideCompressionX = sideComprX;
	sideCompressionY = sideComprY;

	maxBel.resize( neocortex.predictionCount , 0 );
	maxIndex.resize( neocortex.predictionCount , 0 );

	thisMaxMemSize = 1000;
	mem = new std::string[ thisMaxMemSize ];
}

void Hippocampus::setTextOutput( std::string name ){
	unsigned i;
	for(i = 0; i < memCount; i++)
		if( mem[i] == name )
			break; //i is the sequence number found

	if( i == memCount )
		mem[ memCount++ ] = name; 

	sequenceOutput = i;
}

void Hippocampus::initForInference(){
// DG Check valid
//   if ( MemCount == 0 ) {
//    return;
//}
	piIn.resize( memCount , 1. / memCount );
	belStar.resize( memCount , 0 ); // memCount will not change after learning
	combinedBelief.resize( memCount , 0 );
	std::ostringstream lLogStream;

	neocortex.log( String( "Hippocampus memories: " ) + memCount );
}

void Hippocampus::beginRecognition(){
	piIn.assign( memCount , 1. / memCount ); //reinitialize PiIn before each recognition
	combinedBelief.assign( memCount , 0 );
}

void Hippocampus::recognize() {
	vector<vector<double> > lambda;
	child -> getLambda( 0 , 0 , sideCompressionX , sideCompressionY , lambda);

	unsigned r, c;

	//multiply all lambdas into lambdaProd
	vector<double> lambdaProd( memCount , 1 );
	for( c = 0; c < memCount; c++)
		for( r = 0; r < lambda.size(); r++ )
			lambdaProd[c] *= lambda[r][c];

	belStar.assign( memCount , 0 );
	double sumBelStar = 0;
	for( c = 0; c < memCount; c++ ) {
		belStar[c] = lambdaProd[c] / memCount;
		sumBelStar += belStar[c];
	}

	// Optimisation by Greg Kochaniak
	if( sumBelStar > 0 ) { //else we get too little probabilities (not similar to anything)
		double recipSumBelStar = 1.0 / sumBelStar;  //  Just one division here allows us to multply instead of dividing
		for( c = 0; c < memCount; c++ )
			combinedBelief[c] += belStar[c] * recipSumBelStar; //normalize (let SumBelStar = 1)
	}

	vector<vector<double> > piOut;
	piOut.resize( lambda.size() );       //lambda.size() = NumberOfChildren
	for(r = 0; r < piOut.size(); r++) { //piOut.size()  = NumberOfChildren
		piOut[r].resize( memCount );
		for( c = 0; c < memCount; c++ )
			if( lambda[r][c] == 0 )
				piOut[r][c] = 0;
			else
				piOut[r][c] = belStar[c] / lambda[r][c];
	}
	child -> setPi( 0 , 0 , sideCompressionX , sideCompressionY , piOut ); //distribute piOut to each child Sub-region
}

//noOfResults that was used for recognition of moving image
void Hippocampus::calculateResults( unsigned noOfResults ) { //find N best results
	unsigned c;
	for( c = 0; c < memCount; c++ )
		combinedBelief[c] /= noOfResults; //normalize so that sum(CombinedBelief) = 1

	maxBel.assign( neocortex.predictionCount , 0 );
	maxIndex.assign( neocortex.predictionCount , 0 );
	for( unsigned i = 0; i < neocortex.predictionCount; i++ ) {
		for( c = 0; c < memCount; c++ )
			if( combinedBelief[c] > maxBel[i] ) {
				maxBel[i] = combinedBelief[c];
				maxIndex[i] = c;
			}

		combinedBelief[maxIndex[i]] = 0; //will find next maximum
	}
}

//noOfResults that was used for recognition of moving image
void Hippocampus::displayResults( bool pLog, bool pImages ) { //display N best results
	if ( pLog ) {
		for(unsigned i = 0; i < neocortex.predictionCount; i++) {
			if( maxBel[i] > 0 )
				neocortex.log( String("Hippocampus::displayResults - ") + (i+1) + ": " + mem[maxIndex[i]].c_str() + "    " + (maxBel[i]) );
		}
   }
   //cGuiUtils.Plot(MaxBel); - no TChart in Turbo C++ 
   if ( pImages ) {
		displayPredictionImages();
   }
}

std::string Hippocampus::getResultName( unsigned resultNumber ){
  return mem[ maxIndex[resultNumber] ];
}

void Hippocampus::displayPredictionImages() {
}

void Hippocampus::displayAllMemories(){
	neocortex.log( "" );
	neocortex.log( "Memory of hippocampus:" );
	for(unsigned i = 0; i < thisMaxMemSize; i++)
		if ( !(mem[i].length() == 0) )
			neocortex.log( String( "Hippocampus::displayAllMemories - " ) + i + "\t" + mem[i].c_str() );
}
