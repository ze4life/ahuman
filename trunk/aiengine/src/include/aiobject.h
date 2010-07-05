// generic low-level functions

#ifndef	INCLUDE_AIOBJECT_H
#define INCLUDE_AIOBJECT_H

/*#########################################################################*/
/*#########################################################################*/

// object interface
class Object;
class SerializeObject;
class ObjectField;

// object-based helper classes
class Scale;
class Random;

#define TP_CHAR			'c'
#define TP_INT			'd'
#define TP_STRING		's'
#define TP_FLOAT		'f'
#define TP_OBJECT		'o'

/*#########################################################################*/
/*#########################################################################*/

class Object
{
public:
	virtual const char *getClass();
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );
	virtual String getPK();

public:
	SerializeObject *getSerializeObject();
	Logger& getLogger() { return( logger ); };
	static void serialize( Object *o , SerializeObject& so );
	static void deserialize( Object *parent , Object *o , SerializeObject& so );
	static Object *createObject( const char *className );

	const char *getInstance();
	void setInstance( const char *instance );

protected:
	Object() {};
	Logger logger;
	String instance;
};

/*#########################################################################*/
/*#########################################################################*/

class SerializeObject : public Object
{
	// read single item
	typedef union {
		void *V;

		char charV;
		int intV;
		float floatV;
		char *stringV;
		Object *objectV;

		int *intVL;
		float *floatVL;
		char **stringVL;
		ClassList<Object> *objectVL;
	} FieldData;

public:
	// Object interface
	virtual const char *getClass();
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );
	virtual String getPK();

	static Object *onCreate( const char *className ) { return( new SerializeObject ); };
	static void createSerializeObject();
	static SerializeObject *getSerializeObject();

public:
	SerializeObject();
	SerializeObject( Object *o );
	SerializeObject( const char *className );
	~SerializeObject();

	void setFactoryMethod( Object *( *pfnCreateObject )( const char *className ) );
	Object *createObject();
	const char *getObjectClass();
	const char *getEffectiveObjectClass();
	void setEffectiveObjectClass( const char *className );
	void clearData();

	String getDataStringNameToValue();
	String getDataStringIdToValue();

	static const char *readFromString( const char *p , SerializeObject *so , SerializeObject *soSrc , Object **pv );

	ObjectField *addFieldChar( const char *name , int id = 0 );
	ObjectField *addFieldInt( const char *name , int id = 0 );
	ObjectField *addFieldIntList( const char *name , int id = 0 );
	ObjectField *addFieldFloat( const char *name , int id = 0 );
	ObjectField *addFieldFloatList( const char *name , int id = 0 );
	ObjectField *addFieldFloatTwoIndexArray( const char *name , int id = 0 );
	ObjectField *addFieldString( const char *name , int id = 0 );
	ObjectField *addFieldStringList( const char *name , int id = 0 );
	ObjectField *addFieldObject( const char *name , SerializeObject *so , int id = 0 );
	ObjectField *addFieldObjectList( const char *name , SerializeObject *so , int id = 0 );
	ObjectField *addFieldBool( const char *name , int id = 0 );

	ObjectField *getFieldById( int id );
	ObjectField *getFieldById( int id , SerializeObject *so );
	ObjectField *getFieldByName( const char *name );

	char getPropChar( const char *p_field );
	int getPropInt( const char *p_field );
	int *getPropIntList( const char *p_field , int *n , bool clearOwn );
	const char *getPropString( const char *p_field , bool clearOwn );
	const char **getPropStringList( const char *p_field , int *n , bool clearOwn );
	float getPropFloat( const char *p_field );
	float *getPropFloatList( const char *p_field , int *n , bool clearOwn );
	void getPropFloatList( FlatList<float>& p_val , const char *p_field , bool clearOwn );
	Object *getPropObject( const char *p_field , bool clearOwn );
	const FlatList<Object *> *getPropObjectList( const char *p_field );
	void getPropObjectList( ClassList<Object>& p_val , const char *p_field , bool clearOwn );
	bool getPropBool( const char *p_field );
	TwoIndexClassArray<Object> *getPropTwoIndexClassArray( const char *p_field );
	TwoIndexArray<float> *getPropFloatTwoIndexArray( const char *p_field );

	void setPropChar( char p_val , const char *p_field );
	void setPropInt( int p_val , const char *p_field );
	void setPropIntList( int *p_val , int n , const char *p_field , bool setOwn );
	void setPropIntList( FlatList<int>& p_val , const char *p_field );
	void setPropIntListFromStructList( void *p_val , int n , int sizeStruct , int offset , const char *p_field );
	void setPropIntListFromStructPtrList( void ** p_val , int n , int sizeStruct , int offset , const char *p_field );
	void setPropString( const char *p_val , const char *p_field , bool setOwn );
	void setPropStringList( const char **p_val , int n , const char *p_field , bool setOwn );
	void setPropFloat( float p_val , const char *p_field );
	void setPropFloatList( float *p_val , int n , const char *p_field , bool setOwn );
	void setPropFloatListFromStructList( void *p_val , int n , int sizeStruct , int offset , const char *p_field );
	void setPropFloatListFromStructPtrList( void **p_val , int n , int sizeStruct , int offset , const char *p_field );
	void setPropFloatList( FlatList<float>& p_val , const char *p_field );
	void setPropObject( Object *p_val , const char *p_field , bool setOwn );
	void setPropObject( Object& p_val , const char *p_field );
	void setPropObjectList( ClassList<Object>& p_val , const char *p_field , bool setOwn );
	void setPropBool( bool p_val , const char *p_field );
	void setPropFloatTwoIndexArray( TwoIndexArray<float> *p_val , const char *p_field );

	void ref();
	void deref();

private:
	ObjectField *addField( int id , const char *name , char type );
	ObjectField *addFieldList( int id , const char *name , char type );
	ObjectField *addField( ObjectField *field , int id , const char *name );

	void init();
	void fillMapString( String& s , bool useName , int level );
	
	static const char *skipSpaces( const char *p );
	static const char *skipFieldData( const char *p );
	static const char *skipString( const char *p );
	static const char *skipBlock( const char *p );
	static const char *skipListDelimiter( const char *p , bool *endOfList );
	
	int readListCount( const char *p );
	const char *readFieldData( Object *o , const char *p , ObjectField *field , ObjectField *fieldSrc , FieldData *data , int *pn );
	const char *readFieldDataList( Object *o , const char *p , ObjectField *field , ObjectField *fieldSrc , FieldData *data , int *pn );
	static const char *readString( const char *p , bool pAlloc , char **pvAlloc , char *pvNoAlloc );
	const char *readObject( Object *parent , const char *p , Object **pv , SerializeObject *so , SerializeObject *soSrc );
	const char *readChar( const char *p , char *p_v );
	const char *readInt( const char *p , int *p_v );
	const char *readFloat( const char *p , float *p_v );
	void setFieldData( ObjectField *field , void *dataValue /* FieldData* */, int dataListCount );

	void addInt( String& s , int v );
	void addFloat( String& s , float v );
	void addCharEscaped( String& s , char v );
	void addStringEscaped( String& s , const char *p );

private:
	String objectClass;
	String effectiveObjectClass;
	Object *( *pfnCreateObject )( const char *className );

	String data;
	rfc_ptrmap *mapIdToField;
	rfc_strmap *mapNameToField;
	ClassList<ObjectField> fieldList;
	int refCount;
};

/*#########################################################################*/
/*#########################################################################*/

class ObjectField : public Object
{
public:
	// Object interface
	virtual const char *getClass();
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );
	virtual String getPK();

	static Object *onCreate( const char *className ) { return( new ObjectField ); };
	static void createSerializeObject();
	static SerializeObject *getSerializeObject();

public:
	ObjectField();
	ObjectField( int p_id , const char *p_name , char p_type , bool isList );
	ObjectField( int p_id , const char *p_name , SerializeObject *p_so , bool isList );
	~ObjectField();
	void init();

	bool isChar();
	bool isInt();
	bool isFloat();
	bool isString();
	bool isObject();
	bool isList();
	char getBaseType();

	int getId();
	const char *getName();
	SerializeObject *getFieldSerializeObject();
	void attach( SerializeObject *so );

	char getChar();
	int	getInt();
	float getFloat();
	const char *getString( bool clearOwn );
	Object *getObject( bool clearOwn );

	int	*getIntList( int *p_size , bool clearOwn );
	float *getFloatList( int *p_size , bool clearOwn );
	const char **getStringList( int *p_size , bool clearOwn );
	FlatList<Object *> *getObjectList();

	void setChar( char v );
	void setInt( int v );
	void setFloat( float v );
	void setString( const char *v , bool setOwn );
	void setObject( Object *v , bool setOwn );

	void setIntList( int *v , int p_size , bool setOwn );
	void setFloatList( float *v , int p_size , bool setOwn );
	void setStringList( const char **v , int p_size , bool setOwn );
	void setObjectList( ClassList<Object> *v , bool setOwn );
	void clearData( bool pFree = true );

private:
	int id;
	String name;
	char type;
	SerializeObject *soField;
	SerializeObject *soFieldSrc;
	bool isOwnData;

	// value
	union 
	{
		void *value;

		char charValue;
		int intValue;
		int *intListValue;
		float floatValue;
		float *floatListValue;
		const char *stringValue;
		const char **stringListValue;
		Object *objectValue;
		FlatList<Object *> *objectListValue;
	} value;

	int sizeOfList; // for all lists, except object list
};

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
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };

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

// #############################################################################
// #############################################################################

class Random : public Object
{
	typedef enum {
		RND_UNKNOWN = 0 ,
		RND_RANGEFLOAT = 1 ,
		RND_TWORANGEFLOAT = 2 ,
		RND_RANGEINT = 3 ,
		RND_TWORANGEINT = 4
	} RandomType;

public:
	// Object interface
	virtual const char *getClass() { return( "Random" ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( "Random" ) ); };
	static Object *onCreate( const char *className ) { return( new Random ); };

public:
	Random();
	~Random();

	void createRangeRandomsFloat( float min , float max );
	void createTwoRangeRandomsFloat( float min1 , float max1 , float min2 , float max2 );
	void createRangeRandomsInt( int min , int max );
	void createTwoRangeRandomsInt( int min1 , int max1 , int min2 , int max2 );

	int getRandomInt();
	float getRandomFloat();
	float getRandomFloat( float min , float max );

	void collectStatisticsInt();
	void collectStatisticsFloat( int count );
	void showStatistics();

	static int getRandomIntStatic( int min , int max );
	static float getRandomFloatStatic( float min , float max );

private:
	static float randFloat();

private:
	static int instanceCount;
	RandomType type;
	RFC_TYPE min1;
	RFC_TYPE max1;
	RFC_TYPE min2;
	RFC_TYPE max2;

	// random stat
	bool collect;
	int *statCounts;
	int statBuckets;
	float bucketSize;
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIOBJECT_H
