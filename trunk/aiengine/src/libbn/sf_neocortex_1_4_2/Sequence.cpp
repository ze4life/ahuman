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

void Sequence::createData(){
	if( sequenceLength > 0 && inputCount > 0 ) {
		data = new unsigned*[sequenceLength];      //create 2-D array
		for( unsigned i = 0; i < sequenceLength; i++ ) {
			data[i] = new unsigned[inputCount];
			for ( unsigned j = 0; j < inputCount; j++ ) {
				data[i][j] = 0;
			}
		}
	}
}

void Sequence::deleteData() {
	if( sequenceLength > 0 && inputCount > 0) {
		for(unsigned i = 0; i < sequenceLength; i++)
			delete data[i];
		delete data;
	}
}

Sequence::Sequence(unsigned pSeqLen, unsigned ic) {
	sequenceLength = pSeqLen;
	inputCount = ic;
	createData();    //create empty array in advance
	length = 0;
}

Sequence::~Sequence() {
	deleteData();
}

void Sequence::init(unsigned pSeqLen, unsigned ic) {
	deleteData();
	sequenceLength = pSeqLen;
	inputCount = ic;
	createData();
}

//add the pattern to the end of the sequence
//pattern is an array of length InputCount
void Sequence::addPattern(unsigned *pattern) {
	if(length < sequenceLength) {
		//copy pattern array
		for(unsigned i = 0; i < inputCount; i++)
			data[length][i] = pattern[i];
		length++;
	}
	else {
		// << "Length: " << Length << " is out of bounds. Cannot add pattern."<< std::endl;
		// TO DO Can't log here at the moment: no IO available.  Need to pass in reference to constructor.
		//IO.Log( std::string( lLogStream.str() ) );
	}
	//  else
	//     throw std::exception("Sequence is already filled.");
}

void Sequence::clear(){
	length = 0;
}

//returns percentage of similarity (1 if sequences are identical)
//assuming sequence lengths and input counts match
//s may be incomplete
double Sequence::compare( Sequence &s , unsigned length ) {
	if( sequenceLength != s.sequenceLength || inputCount != s.inputCount)  {
		// lLogStream << "Cannot compare sequences of different lengths."<< std::endl;
		// TO DO Can't log here at the moment: no IO available.  Need to pass in reference to constructor.
		//IO.Log( std::string( lLogStream.str() ) );
	}

	//     throw std::exception("Cannot compare sequences of different lengths.");
	if( !complete() ) {
		//std::ostringstream  lLogStream;
		// lLogStream << "Cannot compare with incomplete sequence."<< std::endl;
		// TO DO Can't log here at the moment: no IO available.  Need to pass in reference to constructor.
		//IO.Log( std::string( lLogStream.str() ) );
		return 0; // crashes if sequences unequal - DG fixed 05/05/2008
	}

	//     throw std::exception("Cannot compare with incomplete sequence.");
	unsigned matches = 0;
	for( unsigned i = 0; i < length; i++ )
		for( unsigned j = 0; j < inputCount; j++ )
			if( data[i][j] == s.data[i][j] )
				matches++;

	return (double)matches / (length * inputCount); //precision of match
}

double Sequence::compare( Sequence &s ) {
	return compare( s, s.length ); //compare only filled part
}

void Sequence::assign(Sequence &s) {
	if( sequenceLength != s.sequenceLength || inputCount != s.inputCount)
		init( s.sequenceLength, s.inputCount );

	length = s.length;
	for( unsigned i = 0; i < sequenceLength; i++ )
		for( unsigned j = 0; j < inputCount; j++ )
			data[i][j] = s.data[i][j];
}

unsigned Sequence::getElement(unsigned patternIndex, unsigned elementIndex){
	return data[patternIndex][elementIndex];
}

///////////////////////////////////////////////////////////////////////////////
LearnedSequence::LearnedSequence()
: Sequence(0, 0){
	frequency = 0; //empty sequence
}

LearnedSequence::LearnedSequence(unsigned sl, unsigned ic)
: Sequence(sl, ic)
{
	frequency = 0; //empty sequence
}

void LearnedSequence::init(unsigned sl, unsigned ic)
{
	Sequence::init(sl, ic);
	frequency = 0; //empty sequence
}

void LearnedSequence::assign(Sequence &s)
{
  Sequence::assign(s);
  frequency = 1; //not empty sequence - frequency must be > 0
}

void LearnedSequence::assign(LearnedSequence &s)
{
  Sequence::assign(s);
  frequency = s.frequency;
}

bool LearnedSequence::canDiscard() {
  return frequency <= 1;
}
