#ifndef _QICHE_ELEMENT_HPP_
#define _QICHE_ELEMENT_HPP_

#include "common.hpp"

#include <set>
#include <vector>
#include <memory>

class Data;
class Number;

class Element
{
public:
	Element( const SpecNode* node, const std::shared_ptr< Element > prev )
		: id           ( node->getId() )
		, label        ( node->getLabel() )
		, index        ( node->getIndex() )
		, type         ( node->getType() )
		, specNode     ( node )
		, status       ( eStatusNotCheck )
		, parent       ( node->getParent() )
		, checkedGroup ( false )
		, iteration    ( 1 )
		, previous     ( prev )
	{
		if( node->isRepeated() > 1 && ( prev.use_count() != 0 ) )
		{
			std::shared_ptr<Element> e( prev );
			while( e.use_count() != 0 )
			{
				if( e->id == node->getId() )
				{
					iteration = e->iteration + 1;
					break;
				}
				else
				{
					if( e->getParent().use_count() == 0 )
						break;

					e = e->getParent().lock();
				}
			}
		}
	}

	virtual void check() = 0;
	
	EStatus getStatus() { return status; }
	
	const SpecNode* next( )
	{
		if( status == eStatusNotCheck )
		{
			return specNode;
		}
		
		std::shared_ptr< Element > p;
		if( parent.use_count() != 0 )
		{
			std::shared_ptr< Element > tmp( parent );
			p.swap( tmp );
		}

		if( specNode->isOptional() &&
			status == eStatusInvalid )
		{
			return specNode->next( p );
		}

		if( status == eStatusInvalidButSkip &&
			parent.use_count() != 0 &&
			( ! p->specNode->isOrdered() ) )
		{
			std::cout << "Unordered, check one another baby !" << std::endl;
			status = eStatusInvalidButSkip;
			
			return p->specNode->firstChild( p );
		}
		
		if( specNode->isGroup() && ! checkedGroup )
		{
			checkedGroup = true;
			std::shared_ptr< Element > t( this );
			return specNode->firstChild( t );
		}

		size_t count = specNode->isRepeated();

		if( count > 1 )
		{
			if( iteration < count )
				return specNode;
		}
		
		const SpecNode* sn = specNode->next( p );
		
		if( sn == NULL &&
			parent.use_count() != 0 )
		{
			if( ! p->specNode->isOrdered() )
			{
				std::set< std::string > childIds;
				
				childIds = p->specNode->getChildNodes();

				std::shared_ptr<Element> prev;
				if( previous.use_count() != 0 )
				{
					std::shared_ptr<Element> tmp( previous );
					prev.swap( tmp );

                    while( prev->id != p->id )
					{
						for( auto curId : childIds )
						{
                            if( prev->id == curId )
							{
								childIds.erase( curId );
							}
						}
						std::shared_ptr<Element> p( prev->previous );
						prev.swap( p );
					}
				}
				
				if( childIds.size() != 0 )
				{
					//status = eStatusInvalid;
					p->status = eStatusInvalidForUnordered;
				}
			}
			return p->next( );
		}

		return sn;
	}
		
	std::string getStringStatus() const
	{
		switch( status )
		{
			case eStatusValid               : return "valid";
			case eStatusInvalid             : return "invalid";
			case eStatusInvalidButOptional  : return "invalid but optional";
			case eStatusInvalidForUnordered : return "invalid for unordered";
			case eStatusPassOverData        : return "pass over data";
			case eStatusSkip                : return "skip";
			case eStatusNotCheck            : return "not check";
			case eStatusInvalidButSkip      : return "invalid but skip";
		}
		return "";
	}
	
	const std::weak_ptr< Element > getParent() const { return parent; }
	
public:
	const std::string id;
	const std::string label;
	char*             data;
	const EType       type;
	
	bool              checkedGroup;

	const size_t      index;
	size_t            iteration;
	EStatus           status;
	
	const SpecNode*                specNode;
	const std::weak_ptr< Element > parent;
	const std::weak_ptr< Element > previous;
	std::vector<Element*>          children;
};

#endif
