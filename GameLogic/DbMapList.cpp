// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../PF_GameLogic/DBAdvMap.h"
#include "DbMapList.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( MapList );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MapList::MapList()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MapList::operator&( IBinSaver &saver )
{
	saver.Add( 2, &maps );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MapList::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MapList* parentPtr = (MapList*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapList::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "maps", &maps );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapList::Assign( const MapList& _mapList )
{
	maps = _mapList.maps;
}
}; // namespace NDb
