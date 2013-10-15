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
		SpecNode* s = new SpecNode();

		assert( d["header"].IsArray() );
		assert( d["header"].Size() > 0 );

		s->setId( d["header"][0u]["id"].GetString() );
		s->setLabel( d["header"][0u]["label"].GetString() );
		s->setType( eTypeNumber );
		return s;
	}

private:
	rapidjson::Document d;
	std::string label;
	std::string id;
	std::string type;
	std::vector<std::string> extensions;
};

#endif
