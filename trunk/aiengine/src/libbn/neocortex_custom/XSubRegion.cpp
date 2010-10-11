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

XSubRegion::XSubRegion( XNeoCortex& p_nc , unsigned pSeqLen, unsigned ic, XNeoRegion &r ) 
:	nc( p_nc ) , myRegion(r)
{
	sequenceLength = pSeqLen;
	inputCount = ic;
	currentSequence = new XSequence( sequenceLength , inputCount );
	nameOutput = nc.OUTPUT_NONE;
}

XSubRegion::~XSubRegion()
{
	delete currentSequence;
	cpdMatrix.clear();
}

//finds a sequence in the array of learned sequences
// It always finds a match
void XSubRegion::findBestMatch( XSequence &s , unsigned &retIndex , double &retPrecision )
{
	double precision;
	retPrecision = 0;
	retIndex = 0;

	for(unsigned i = 0; i < myRegion.getMemCount(); i++) {
		precision = myRegion.memory(i).compare( s );
		if( precision > retPrecision ) {
			retPrecision = precision;
			retIndex = i;

			if( retPrecision == 1 ) //can't be better
				return;
		}
	}  
}

int XSubRegion::findLowUsage( unsigned pMaxUsage )
{
	for(unsigned i = 0; i < myRegion.getMemCount(); i++) {
		if( myRegion.memory(i).getFrequency() < (pMaxUsage+1) ) {
			return i;
		}
	}  
	return -1;
};

//take input pattern, process it and remember the output
//pattern is array of length InputCount containing the input pattern
bool XSubRegion::feedForward( unsigned *pattern, bool memorize, unsigned pLowUsageThreshold )
{
	bool lRetCode = true;
	// CurrentSequence is the single sequence that is being worked on
	// Sequence length is always one.
	currentSequence -> addPattern( pattern );

	if( currentSequence -> complete() ) {
		unsigned int lLearnedIndex;
		double lMatchPrecision;
		BestMatch lBestMatch;
		findBestMatch(*currentSequence, lLearnedIndex, lMatchPrecision);

		lBestMatch.precision = lMatchPrecision;
		lBestMatch.index = lLearnedIndex;

		if( memorize && lBestMatch.precision < 1) { // potentially treat as a new sequence
			int lRetIndex = 0;
			lRetIndex = myRegion.addSequence( *currentSequence );

			if ( -1 ==  lRetIndex ) {
				// New at version 1.4
				// Memory full so add it to the best place we can find
				// But only for a reasonably good match
				// 
				if ( lBestMatch.precision > nc.bestMatchPrecision ) {
					myRegion.memory( lBestMatch.index ).increaseFrequency();  
				}
				else {
					int lLowUsageIndex = findLowUsage( pLowUsageThreshold );
					if ( lLowUsageIndex != -1 ) {
						// Replace the memory with the one at the top 
						myRegion.forgetMemory( lLowUsageIndex );
						// Add the new sequence to the top
						lRetIndex = myRegion.addSequence( *currentSequence );
						if ( -1 ==  lRetIndex ) {
							lRetCode = false;
							lBestMatch.index = nc.OUTPUT_NONE;
						}
						else {
							lBestMatch.index = (unsigned int) lRetIndex; // this should be the top of memory
						}
					}
					else {
						// Sequence was not added.
						lRetCode = false;
						lBestMatch.index = nc.OUTPUT_NONE;
						// Would be nice to log - but we do not have logging in this class right now.
						//std::ostringstream  lLogStream;
						//lLogStream << "Cannot find a low-usage slot for new sequence." << " Memory is full."; //<< std::endl; 
						//cGuiUtils->Log( std::string( lLogStream.str() ) );
					}
				}
			}
			else {
				// Memory already had space for the new sequence (frequency is already set to 1)
				lBestMatch.index = (unsigned int) lRetIndex;
			}
		}
		else {
			if ( memorize && lBestMatch.precision == 1 ) {
				// Match precision is 100%
				myRegion.memory( lBestMatch.index ).increaseFrequency();  
			}
		}

		nameOutput = lBestMatch.index; //index of the best match for the new sequence
		memIndex = lBestMatch.index;   //used in Contextual
		currentSequence -> clear();
	}

	return lRetCode;
}

void XSubRegion::contextual(unsigned parentContext) 
{
	//parentContext is name output from parent
	//  NO NEED to pre-create entries - only the ones that are required will be created
	std::map<XAccessKey, double> lIter; 
	XAccessKey lKey( parentContext , memIndex );

	// Returns false if entry did not exist
	if( cpdMatrix[lKey] == 0.0 ) {
	// Initialize new entry (note that it has been created by the attempted access
		cpdMatrix[lKey] = 1.0;
	}
	else {
		cpdMatrix[lKey] += 1.0;
	}
	//   Use insert to speed things up
	// May be quicker but may crash
	//lSuccess = cCPDMatrix->insert(std::make_pair(lKey, 1.0)).second;
	//if ( !lSuccess ) // i.e. row exists
	//{
	//   (*cCPDMatrix)[lKey] += 1.0;
	//}
}

void XSubRegion::initForInference(unsigned pParentMemCount)
{
	//cCPDMatrix has pParentMemCount rows and MemCount Sub-regions

	double sum = 0;
   
	// Declare map iterator.  This will return all elements row-major order.
	// Initialise Current row to the first row of the matrix
	std::map<XAccessKey, double>::iterator lIter = cpdMatrix.begin(); //, AccessKey::LessThan>::iterator lIter = cCPDMatrix->begin();
	unsigned lCurrentRow = lIter-> first.cPosition.first;

	std::vector<XAccessKey> lvPrev;
	std::vector<XAccessKey>::iterator lvPrevIter;

	unsigned lMaxCol = 0;
	unsigned lMaxRow = 0;

	// Normalise the results
	for ( lIter = cpdMatrix.begin(); lIter != cpdMatrix.end(); lIter++ ) {
		// NB the lIter->first is the key for the map.
		//    The key itself is also made up of a value pair - row and column, respectively, within cPosition.
		// 
		if ( lIter->first.cPosition.first != lCurrentRow ) { 
			// We use this next time through
			// Now we have to just normalise the current row and set the sum back to zero
			lCurrentRow = lIter->first.cPosition.first;
			if ( sum > 0 ) {
				lvPrevIter = lvPrev.begin();
				for ( lvPrevIter = lvPrev.begin(); lvPrevIter != lvPrev.end(); lvPrevIter++ ) {
					cpdMatrix[*lvPrevIter] /= sum;
				}

				sum = 0;
				lvPrev.clear();
			}
		}

		lvPrev.push_back(lIter->first); // save access key
		sum += lIter->second;
	}
   
	if ( lvPrev.size() > 0 ) {  // we have exited from the final row but this row has not been normalised
		// So do it now
		lvPrevIter = lvPrev.begin();
		for ( lvPrevIter = lvPrev.begin(); lvPrevIter != lvPrev.end(); lvPrevIter++ ) {
			cpdMatrix[*lvPrevIter] /= sum;
		}

		sum=0;
		lvPrev.clear();
	}   

	// Increment to give the actual row count
	piIn.resize(lCurrentRow+1, 1);
	// It seems that the following is sometimes too small:
	// cPiIn.resize(pParentMemCount, 1);
}

void XSubRegion::beginRecognition(unsigned parentMemCount)
{
	piIn.assign(parentMemCount, 1); //reinitialize cPiIn before each recognition
}

//lambda is evidence from children, measures NumberOfChildren x MemCount
//for Level0: lambda[r][c] is probability that the input to the child r is
//the memorized pattern c (how close is the input to the memorized pattern)
//assume size(piOut) = number of children
void XSubRegion::recognize(vector<vector<double> > &lambda, vector<vector<double> > &piOut)
{
	unsigned r, c;

	XAccessKey lKey(0,0);

	unsigned rowCount = myRegion.getParent() -> getMemCount(); //cPiIn.size(); ?
	unsigned colCount = myRegion.getMemCount();

	//multiply all lambdas into lambdaProd
	//lambdaProd[c] is combined probability from children that the input to ALL of them
	//(total input to this Sub-region) is the memorized pattern c
	//(AND operation - multiplication)

	vector<double> lambdaProd(colCount, 1.0);
	for(c = 0; c < colCount; c++)
		for(r = 0; r < lambda.size(); r++) //lambda.size() = NumberOfChildren
			lambdaProd[c] *= lambda[r][c];

	// DG.  I think if we try to add new learning and forget rare memories that have been referenced by higher level memories, 
	//      the program can crash due to these orphaned memories still being in cCPDMatrix.
	//      (This version of the program does not allow addition of learning).
	//      We could consider deleting the orphaned memories from cCPDMatrix at this point.
	//
	// Exptl - can recalculate required array size in case forgetting memories results in incorrect value
	//         Probably not a very good strategy but code may be useful anyway.
	// std::map<AccessKey, double>::iterator lIter0, lIterEnd0;
	// lIterEnd0 = cCPDMatrix->end();
	//for ( lIter0 = cCPDMatrix->begin(); lIter0 != lIterEnd0; lIter0++ )
	//{
	//   const std::pair<unsigned,unsigned> lPosition= lIter0->first.cPosition;
	//   r=lPosition.first;
	//   c=lPosition.second;
	//   if ( r > rowCount )
	//      rowCount = r;
	//   if ( c > colCount )
	//      colCount = c;
	//}

	vector<double> v(colCount, 0);

	// fxu is the probability that the current input (classified as c) is
	//            part of the higher-level pattern r
	// Optimisation by Greg Kochaniak - fxu does not have to be a matrix if we just have a single loop.
	double fxu, lOut;
	belStar.assign(colCount, 0);
	lambdaOut.assign(rowCount, 0);

	std::map<XAccessKey, double>::iterator lIter, lIterEnd;
	lIterEnd = cpdMatrix.end();
	for ( lIter = cpdMatrix.begin(); lIter != lIterEnd; lIter++ ) {
		const std::pair<unsigned,unsigned> lPosition= lIter->first.cPosition;
		r=lPosition.first;
		c=lPosition.second;
		double lVal = lIter->second;
		lOut = lambdaProd[c] * lVal;
		fxu = lOut * piIn[r];

		if( belStar[c] < fxu ) {
			belStar[c] = fxu;
		}

		if( lambdaOut[r] < lOut ) {
			lambdaOut[r] = lOut;
		}
	}

	/*   The following code is no longer needed
	//cBelStar (belStarX) is the max for each column in fxu (max over u)
	// colCount is the number of memorised spatial pattern coincidences
	cBelStar.resize(colCount, 0);
	cBelStar.assign(colCount, 0);
	for(r = 0; r < rowCount; r++)
	for(c = 0; c < colCount; c++)
	if(cBelStar[c] < fxu[r][c])
	cBelStar[c] = fxu[r][c];

	//cLambdaOut is the max for each row in fxu divided by cPiIn - message to our parent
	cLambdaOut.resize(rowCount, 0);
	cLambdaOut.assign(rowCount, 0);
	for(r = 0; r < rowCount; r++)
	if(cPiIn[r] == 0)
	cLambdaOut[r] = 0;
	else{
	for(c = 0; c < colCount; c++) //max of each row
	if(cLambdaOut[r] < fxu[r][c])
	cLambdaOut[r] = fxu[r][c];
	cLambdaOut[r] /= cPiIn[r];
	}

	//lambda.size() = piOut.size() = InputCount(NumberOfChildren) (or 1 for lowest level)
	piOut.resize(lambda.size());
	for(r = 0; r < piOut.size(); r++){
	piOut[r].resize(colCount);
	for(c = 0; c < colCount; c++)
	if(lambda[r][c] == 0)
	piOut[r][c] = 0;
	else
	piOut[r][c] = cBelStar[c] / lambda[r][c];
	}
	*/
}

vector<double> XSubRegion::getLambdaOutput() {
	return lambdaOut;
}

void XSubRegion::setPiInput(vector<double> &pi) {
	piIn = pi; //copies all elements; pi.size() = pParentMemCount
}

unsigned XSubRegion::getNameOutput() {
	return nameOutput;
}
