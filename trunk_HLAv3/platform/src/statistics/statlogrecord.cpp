#include <ah_platform.h>
#include <ah_statistics_impl.h>

// #############################################################################
// #############################################################################

StatLogRecord::StatLogRecord() {
	metric = NULL;
	aggregateType = StatMetric::MetricAggregate_Unknown;
}

StatLogRecord::~StatLogRecord() {
}

void StatLogRecord::configure( Xml config ) {
	metricName = config.getAttribute( "metric" );
	aggregateTypeName = config.getAttribute( "aggregate" );

	if( aggregateTypeName.equals( "average" ) )
		aggregateType = StatMetric::MetricAggregate_Average;
	else
		ASSERTFAILED( "Cannot parse type for log aggregate metric=" + metricName + ", value= " + aggregateTypeName );
}

void StatLogRecord::create() {
	StatService *ss = StatService::getService();
	metric = ss -> getMetricByName( metricName );
	metric -> prepareCalculate( aggregateType );
}

String StatLogRecord::getLogString() {
	String log = "metric=" + metricName + ", aggregate=" + aggregateTypeName + ", value=";

	if( metric -> getCount() == 0 )
		log += "(no values)";
	else {
		int value = metric -> calculate( aggregateType );
		log += value;
	}

	return( log );
}

void StatLogRecord::resetMetric() {
	metric -> reset();
}
