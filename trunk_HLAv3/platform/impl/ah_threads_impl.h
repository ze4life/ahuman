#ifndef	INCLUDE_AH_THREADS_IMPL_H
#define INCLUDE_AH_THREADS_IMPL_H

#include <ah_threads.h>

/*#########################################################################*/
/*#########################################################################*/

// thread data
class ThreadData
{
public:
	RFC_THREAD threadExtId;
	String name;
	unsigned long threadId;
	Object *object;
	void ( Object::*objectFunction )( void *p_arg );
	void *objectFunctionArg;

	MapStringToClass<ThreadObject> map;

public:
	ThreadData() {
		memset( &threadExtId , 0 , sizeof( RFC_THREAD ) );
		threadId = ( unsigned long )NULL;
		object = NULL;
		objectFunction = NULL;
		objectFunctionArg = NULL;
	}
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_THREADS_IMPL_H
