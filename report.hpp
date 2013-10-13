#ifndef _QICHE_REPORT_HPP_
#define _QICHE_REPORT_HPP_

#include "element.hpp"

#include <iomanip>

class Report
{
public:
	Report()
	{
	}
	
	void addElement( const std::shared_ptr< Element > e )
	{
		elements.push_back( e );
		//print( e );
	}
	
	void print( const std::shared_ptr< Element > e )
	{
		size_t count = 0;
		std::shared_ptr< Element > elem( e );
		while( elem.use_count() != 0 )
		{
			count++;
			std::weak_ptr< Element > p = elem->getParent();

			std::shared_ptr< Element > tmp;
			if( p.use_count() != 0 )
			{
				std::shared_ptr< Element > sTmp( p );
				tmp.swap( sTmp );
			}
			elem.swap( tmp );
		}

		std::cout << std::setw( 5*count ) << " " << "-------------------------------------------------" << std::endl;
		std::cout << std::setw( 5*count ) << " " << "| " << e->getIndex() << "\t" << e->getId() << " (" << e->getStringStatus() << ") - " << e->getIteration()  << std::endl;
		std::cout << std::setw( 5*count ) << " " << "-------------------------------------------------" << std::endl;
	}

	void print()
	{
		for( auto e : elements )
		{
			print( e );
		}
	}

private:

	std::vector< std::shared_ptr< Element > > elements;

};

#endif
