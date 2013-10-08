#ifndef _QICHE_SPECNODE_HPP_
#define _QICHE_SPECNODE_HPP_

#include "common.hpp"

class Element;

class SpecNode
{
public:
	SpecNode( Element* p = NULL )
		: index( globalIndex++ )
		, parent( p )
	{
	}
	
	SpecNode* next( Element* parent ) const
	{
		if( index == 8 ||
			index == 10 ||
			index == 12 ||
			index == 15 ||
			index == 18 )
			return NULL;
		
		SpecNode* s = new SpecNode( parent );
		s->setId( "next " + index );
		s->setType( eTypeData );
		return s;
	}
	
	void setId( const std::string& i ){ id = i;   }
	void setType( const EType& t )    { type = t; }
	
	std::string getId( )    const { return id; }
	size_t      getIndex( ) const { return index; }
	EType       getType( )  const { return type; }
	
	bool isGroup() const
	{
		if( index == 2 ||
			index == 5 )
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
		if( index == 5 )
			return false;
		return true;
	}
	
	SpecNode* firstChild( Element* e ) const
	{
		SpecNode* s = new SpecNode( e );
		s->setId( "child !!!" );
		s->setType( eTypeNumber );
		return s;
	}
	
	Element* getParent() const { return parent; }
	
private:
	std::string id;
	size_t      index;
	EType       type;
	
	Element*    parent;
	
	static size_t globalIndex;
};

size_t SpecNode::globalIndex = 0;

#endif
