#ifndef _QICHE_SPEC_HPP_
#define _QICHE_SPEC_HPP_

#include "specNode.hpp"
#include <limits>

#include <rapidjson/document.h>

#include <fstream>
#include <vector>

class Spec
{
public:
	Spec( const std::string filename )
	{
		std::filebuf fb;
		std::stringstream rawSpec;
		if( ! fb.open ( filename, std::ios::in ) )
			return;

		std::istream is( &fb );
		char line[512];
		while( is )
		{
			is.getline( line, 512 );
			rawSpec << line;
		}
		fb.close();

		d.Parse<0>( rawSpec.str().c_str() );

		label = d["standard"]["label"].GetString();
		id    = d["standard"]["id"].GetString();
		type  = d["standard"]["type"].GetString();

		const rapidjson::Value& ext = d["standard"]["extension"];
		assert( ext.IsArray() );
		for( rapidjson::SizeType i = 0; i < ext.Size(); i++ )
			extensions.push_back( ext[i].GetString() );
	}
	
	SpecNode* getFirstNode( )
	{
		return loadFromJson( d["header"][0u] );
	}

	SpecNode* loadFromJson( const rapidjson::Value& ref )
	{
		SpecNode* s = new SpecNode();
		s->setId( ref[ "id" ].GetString() );
		s->setLabel( ref[ "label" ].GetString() );
		s->setType( getType( ref[ "type" ].GetString() ) );
		
		s->setOrdered( ref.HasMember( "ordered" ) ? ref[ "ordered" ].GetBool() : true );
		s->setHasGroup( ref.HasMember( "group" ) ? ref[ "group" ].GetBool() : false );
		return s;
	}
	
protected:

	EType getType( const std::string& subTypeString )
	{
		switch( getSubType( subTypeString ) )
		{
			case eTypeRaw:
			case eTypeAscii:
			case eTypeHexa:
				return eTypeData;
			case eTypeUInt8:
			case eTypeInt8:
			case eTypeUInt16:
			case eTypeInt16:
			case eTypeUInt32:
			case eTypeInt32:
			case eTypeHalf:
			case eTypeFloat:
			case eTypeDouble:
				return eTypeNumber;
		}
	}

	ESubType getSubType( const std::string& subTypeString )
	{
		return mSubType[ subTypeString ];
	}

private:
	rapidjson::Document d;
	std::string label;
	std::string id;
	std::string type;
	std::vector<std::string> extensions;
};

#endif
