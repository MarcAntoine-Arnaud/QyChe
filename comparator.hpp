#ifndef _QICHE_COMPARATOR_HPP_
#define _QICHE_COMPARATOR_HPP_

#include "element.hpp"
#include "data.hpp"
#include "number.hpp"
#include "specNode.hpp"

class Comparator
{
public:
	Comparator()
	{
	}
	
private:
	
	std::shared_ptr< Element > getElement( const SpecNode* node, const std::shared_ptr< Element > previous )
	{
		switch( node->getType() )
		{
			case eTypeData:
			{
				std::shared_ptr< Data > d( new Data( node, previous ) );
				return static_cast< std::shared_ptr< Element > >( d );
				break;
			}
			case eTypeNumber:
			{
				std::shared_ptr< Number > n( new Number( node, previous ) );
				return static_cast< std::shared_ptr< Element > >( n );
				break;
			}
		}
		return nullptr;
	}
	
public:
	void check( Spec& spec, FileReader& reader, Report& report )
	{
		const SpecNode* s = NULL;
		std::shared_ptr< Number > wElem;
		std::shared_ptr< Element > e = getElement( spec.getFirstNode( ), wElem );

		while( ( s = e->next() ) != NULL )
		{
			e = getElement( s, e );
			e->check();
			
			if( e->getStatus() == eStatusInvalidButOptional ||
				e->getStatus() == eStatusInvalidButSkip )
			{
				std::cout << "go back in raw file" << std::endl;
				continue;
			}
			
			report.addElement( e );
			
			if( e->getIndex() > 20 )
				break;
		}
	}
};

#endif
