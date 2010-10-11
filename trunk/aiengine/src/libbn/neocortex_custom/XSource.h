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

// structure that can produce a pattern in a form of unsigned matrix (x by y)
// has feed-forward outputs
// parent
class XPatternSource {
protected:
	XContextSource *parent;
	unsigned outputsX, outputsY;
	unsigned sequenceLength; // number of steps that form a sequence (time)
	unsigned patternNumber; // in the current sequence: from 0 to SequenceLength

protected:
	virtual vector<double> getLambdaOutput( unsigned xPos , unsigned yPos ) = 0;
public:
	virtual unsigned getNameOutput( unsigned xPos , unsigned yPos ) = 0;
	virtual void setPiInput( unsigned xPos , unsigned yPos , vector<double> &pi ) = 0;

public:
	XPatternSource( unsigned outputSizeX , unsigned outputSizeY , unsigned sequenceLength );
	virtual ~XPatternSource() {};

	void setParent( XContextSource *s ) { parent = s; }
	XContextSource *getParent() { return parent; }

public:
	virtual void getPattern( unsigned xPos , unsigned yPos , unsigned sideXCompression , unsigned sideYCompression , unsigned *result );
	virtual void getLambda( unsigned xPos , unsigned yPos , unsigned sideXCompression , unsigned sideYCompression , vector<vector<double> > &result );
	virtual void setPi( unsigned xPos , unsigned yPos , unsigned sideXCompression , unsigned sideYCompression , vector<vector<double> > &pi );
};

/*#########################################################################*/
/*#########################################################################*/

// child
class XContextSource {
protected:
	XPatternSource *child;

public:
	XContextSource();
	virtual ~XContextSource() {};

	void setChild( XPatternSource *s ) { child = s; }

public:
	virtual void feedForward( unsigned learningRegion, bool feedbackStage ) = 0;
	virtual void contextual() = 0;
	virtual int getSequence( unsigned xPos , unsigned yPos ) = 0;
	virtual unsigned getMemCount() = 0;
};
