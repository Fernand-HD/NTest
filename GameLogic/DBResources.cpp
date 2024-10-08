// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../Render/DBRenderResources.h"
#include "DBResources.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( CurrencyDescriptionList );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CurrencyDescription::CurrencyDescription()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CurrencyDescription::operator&( IBinSaver &saver )
{
	saver.Add( 2, &Id );
	saver.Add( 3, &Description );
	saver.Add( 4, &Icon );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CurrencyDescription::operator&( IXmlSaver &saver )
{
	saver.Add( "Id", &Id );
	saver.Add( "Description", &Description );
	saver.Add( "Icon", &Icon );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CurrencyDescriptionList::CurrencyDescriptionList()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CurrencyDescriptionList::operator&( IBinSaver &saver )
{
	saver.Add( 2, &CurrencyList );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CurrencyDescriptionList::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CurrencyDescriptionList* parentPtr = (CurrencyDescriptionList*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CurrencyDescriptionList::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "CurrencyList", &CurrencyList );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CurrencyDescriptionList::Assign( const CurrencyDescriptionList& _currencyDescriptionList )
{
	CurrencyList = _currencyDescriptionList.CurrencyList;
}
}; // namespace NDb
