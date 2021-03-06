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

class Sequence {
private:
	unsigned length;         //current number of patterns stored

	void createData();
	void deleteData();

protected:
	unsigned sequenceLength; //number of steps that form a sequence (time)
	unsigned inputCount;     //number of unsigned inputs (space)
	unsigned **data; //dimensions SequenceLength x InputCount    

public:
	Sequence( unsigned sequenceLegth , unsigned inutCount );
	virtual ~Sequence();

	virtual void init( unsigned sequenceLength , unsigned inputCount );
	void addPattern( unsigned *pattern );
	void clear();
	unsigned getLength() { return length; }
	bool complete() { return length == sequenceLength; }
	double compare( Sequence &s );
	double compare( Sequence &s , unsigned length );
	virtual void assign( Sequence &s );
	unsigned getElement( unsigned patternIndex , unsigned elementIndex );
};

class LearnedSequence : public Sequence {
private:
	unsigned frequency;

public:
	LearnedSequence();
	LearnedSequence( unsigned sequenceLegth , unsigned inutCount );
	virtual ~LearnedSequence(){};

	virtual void init( unsigned sequenceLegth , unsigned inutCount );
	void increaseFrequency(){ frequency++; }
	virtual void assign( Sequence &s );
	void assign( LearnedSequence &s );
	bool canDiscard();
	unsigned getFrequency() { return frequency; }
};
