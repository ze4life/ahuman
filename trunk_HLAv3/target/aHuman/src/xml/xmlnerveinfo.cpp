#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

void XmlNerveInfo::getMotorNuclei( StringList& items ) {
	for( int k = 0; k < fibers.count(); k++ ) {
		XmlNerveFiberInfo& fiber = fibers.getRef( k );
		getFiberMotorNuclei( fiber , items );
	}

	for( int k = 0; k < childs.count(); k++ ) {
		XmlNerveInfo& child = childs.getClassRefByIndex( k );
		child.getMotorNuclei( items );
	}
}

void XmlNerveInfo::getSensoryNuclei( StringList& items ) {
	for( int k = 0; k < fibers.count(); k++ ) {
		XmlNerveFiberInfo& fiber = fibers.getRef( k );
		getFiberSensoryNuclei( fiber , items );
	}

	for( int k = 0; k < childs.count(); k++ ) {
		XmlNerveInfo& child = childs.getClassRefByIndex( k );
		child.getSensoryNuclei( items );
	}
}

void XmlNerveInfo::getFiberMotorNuclei( XmlNerveFiberInfo& fiber , StringList& items ) {
	if( fiber.type.equals( "GSE" ) || fiber.type.equals( "GVE" ) || fiber.type.equals( "SVE" ) ) {
		String item;
		if( fiber.mids.count() > 0 )
			item = fiber.mids.last();
		else
			item = fiber.src;

		items.addnew( item );
	}
}

void XmlNerveInfo::getFiberSensoryNuclei( XmlNerveFiberInfo& fiber , StringList& items ) {
	if( !( fiber.type.equals( "GSE" ) || fiber.type.equals( "GVE" ) || fiber.type.equals( "SVE" ) ) ) {
		String item;
		if( fiber.mids.count() > 0 )
			item = fiber.mids.first();
		else
			item = fiber.dst;

		items.addnew( item );
	}
}

void XmlNerveInfo::getNervesByComponent( String item , StringList& nerves ) {
	for( int k = 0; k < fibers.count(); k++ ) {
		XmlNerveFiberInfo& fiber = fibers.getRef( k );
		if( fiber.src.equals( item ) || fiber.dst.equals( item ) || fiber.mids.find( item ) >= 0 )
			nerves.addnew( name );
	}

	for( int k = 0; k < childs.count(); k++ ) {
		XmlNerveInfo& child = childs.getClassRefByIndex( k );
		child.getNervesByComponent( item , nerves );
	}
}

