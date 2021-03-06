#include <iostream>

#include "spec.hpp"
#include "report.hpp"
#include "fileReader.hpp"
#include "comparator.hpp"

int main( int argc, char** argv )
{
	Comparator c;
	FileReader f;
	Report r;
	Spec s( "specifications/bwf.json" );
	
	c.check( s, f, r );

	r.print();
}

