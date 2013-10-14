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
		int count = -1;
		std::shared_ptr< Element > elem( e );
		while( elem.use_count() != 0 )
		{
			count++;

			if( elem->getParent().use_count() == 0 )
				break;

			elem = elem->getParent().lock();
		}

		std::cout << std::setw( 5 * count ) << " " << "| " << e->getIndex() << "\t" << e->getId() << " (" << e->getStringStatus() << ") - " << e->getIteration()  << std::endl;
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
