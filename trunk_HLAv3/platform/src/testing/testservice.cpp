#include <ah_platform.h>

Service *TestService::newService() {
	return( new TestService() );
}
