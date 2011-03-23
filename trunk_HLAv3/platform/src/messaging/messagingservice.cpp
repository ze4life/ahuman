#include <ah_platform.h>

// #############################################################################
// #############################################################################

Service *MessagingService::newService() {
	return( new MessagingService() );
}
