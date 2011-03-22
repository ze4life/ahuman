#include "aiapi.h"

class AIHtmOps
{
public:
	AIHtmOps();
	~AIHtmOps();

	bool connect( const char *url );
	void disconnect();

	void createCortex( int p_width , int p_height );
	void sendPicture( const char *hexbytes );

private:
	AIApi api;
};
