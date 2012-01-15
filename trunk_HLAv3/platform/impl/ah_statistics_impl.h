#ifndef	INCLUDE_AH_STATISTICS_IMPL_H
#define INCLUDE_AH_STATISTICS_IMPL_H

/*#########################################################################*/
/*#########################################################################*/

#include <ah_platform.h>

// core classes
class StatMetric;
class StatLogTask;
class StatLogRecord;

/*#########################################################################*/
/*#########################################################################*/

class StatMetric : public Object {
public:
	typedef enum {
		MetricType_Unknown = 0 ,
		MetricType_Percentage = 1
	} MetricType;

	typedef enum {
		MetricAggregate_Unknown = 0 ,
		MetricAggregate_Average = 1
	} MetricAggregate;

public:
	StatMetric();
	~StatMetric();
	virtual const char *getClass() { return( "StatMetric" ); };

public:
	void configure( Xml config );

	void addMetricValue( int value );
	void prepareCalculate( MetricAggregate aggregateType );

	int getCount();
	int calculate( MetricAggregate aggregateType );
	void reset();

private:
// utility
	String name;
	MetricType type;

	bool calculateSum;

	RFC_INT64 sumValues;
	int count;
};

/*#########################################################################*/
/*#########################################################################*/

class StatLogTask : public Object , public MessageSubscriber {
public:
	StatLogTask();
	~StatLogTask();
	virtual const char *getClass() { return( "StatLogTask" ); };

public:
	void configure( Xml config );

	void create();
	void start();
	void stop();
	void resetMetrics();
	
private:
	virtual void onTextMessage( TextMessage *msg );

private:
// utility
	String name;
	int intervalSec;

// own data
	ClassList<StatLogRecord> logRecordList;
};

/*#########################################################################*/
/*#########################################################################*/

class StatLogRecord : public Object {
public:
	StatLogRecord();
	~StatLogRecord();
	virtual const char *getClass() { return( "StatLogRecord" ); };

public:
	void configure( Xml config );

	void create();
	String getLogString();
	void resetMetric();

private:
// utility
	String metricName;
	String aggregateTypeName;
	StatMetric::MetricAggregate aggregateType;

// references
	StatMetric *metric;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_STATISTICS_IMPL_H
