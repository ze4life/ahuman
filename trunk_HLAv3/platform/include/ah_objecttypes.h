#ifndef	INCLUDE_AH_OBJECTTYPES_H
#define INCLUDE_AH_OBJECTTYPES_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_objects.h"

// object-based helper classes
class Scale;

/*#########################################################################*/
/*#########################################################################*/

class Scale : public Object
{
public:
	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static Object *onCreate( const char *className ) { return( new Scale ); };
	static SerializeObject *getSerializeObject()
		{ return( ObjectService::getService() -> getSerializeObject( NAME ) ); };

public:
	Scale();

	void set( const Scale& scale );
	void setRangeFrom( float minValue , float maxValue );
	void setRangeTo( float minValue , float maxValue );
	void setDoScale( bool p_doScale );
	bool getDoScale() { return( doScale ); };

	float getFromMin() { return( rangeFromMin ); };
	float getFromMax() { return( rangeFromMax ); };
	float getFromRange() { return( rangeFromMax - rangeFromMin ); };
	float getToMin() { return( rangeToMin ); };
	float getToMax() { return( rangeToMax ); };
	float getToRange() { return( rangeToMax - rangeToMin ); };
	float getRate() { return( rateFromTo ); };

	float scale( float value );
	float unscale( float value );
	float unscaleDiffNormalized( float toValue1 , float toValue2 );

private:
	void recalculateRate();

private:
	float rangeFromMin;
	float rangeFromMax;
	float rangeToMin;
	float rangeToMax;
	float rateFromTo;

	bool doScale;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_OBJECTTYPES_H
