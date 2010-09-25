#include "htm_custom.h"
#include "..\libbn_impl.h"

/*#########################################################################*/
/*#########################################################################*/

class LibHtmCustom : public AILibBNVariant
{
public:
	LibHtmCustom() : AILibBNVariant( "LibHtmCustom" ) {};
	
	void init() {
		// register serialisable classes
		HtmCortex::createSerializeObject();
	}
};

/*#########################################################################*/
/*#########################################################################*/

AILibBNVariant *AILibBNImpl::createHtmCustom()
{
	LibHtmCustom *lib = new LibHtmCustom();
	lib -> init();
	return( lib );
}
