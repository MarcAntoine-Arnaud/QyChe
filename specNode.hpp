#ifndef _QICHE_SPECNODE_HPP_
#define _QICHE_SPECNODE_HPP_

#include "common.hpp"

#include <set>
#include <memory>
#include <sstream>

class Element;

class SpecNode
{
public:
	SpecNode( std::shared_ptr< Element > p = std::shared_ptr< Element >() )
		: index( globalIndex++ )
		, parent( p )
	{
	}
	
	SpecNode* next( std::shared_ptr< Element > parent ) const
	{
		if( index == 8 ||
			index == 10 ||
			index == 12 ||
			index == 17 ||
			index == 18 )
			return NULL;
		
		SpecNode* s = new SpecNode( parent );
		std::ostringstream id;
		id << "next " << index;
		s->setId( id.str() );
		s->setType( eTypeData );
		return s;
	}
	
	void setId   ( const std::string& i ){ id = i;    }
	void setLabel( const std::string& l ){ label = l; }
	void setType ( const EType& t )      { type = t;  }
	
	std::string getId( )    const { return id; }
	std::string getLabel( ) const { return label; }
	size_t      getIndex( ) const { return index; }
	EType       getType( )  const { return type; }
	
	bool isGroup() const
	{
		if( index == 2 ||
			index == 5 ||
			index == 14 )
			return true;
		return false;
	}
	
	size_t isRepeated() const
	{
		if( index == 4 )
			return 3;

		if( index == 5 )
			return 2;
		
		return 1;
	}
	
	bool isOrdered() const
	{
		if( index == 14 )
			return false;
		return true;
	}
	
	bool isOptional() const
	{
		if( index == 7 )
			return true;
		return false;
	}
	
	SpecNode* firstChild( std::shared_ptr< Element > e ) const
	{
		SpecNode* s = new SpecNode( e );
		std::ostringstream id;
		id << "child " << index;
		s->setId( id.str() );
		s->setType( eTypeNumber );
		return s;
	}
	
	std::shared_ptr< Element > getParent() const { return parent; }
	
	std::set< std::string > getChildNodes() const
	{
		std::set< std::string > list;
		list.insert( "child" );
		list.insert( "prout" );
		return list;
	}
	
private:
	std::string id;
	std::string label;
	size_t      index;
	EType       type;
	
	std::shared_ptr< Element > parent;
	
	static size_t globalIndex;
};

size_t SpecNode::globalIndex = 0;

#endif
