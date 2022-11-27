#include <fstream>
#include <iostream>
#include <sstream>
#include <uPRNG.h>
#include "printer.h"
#include "nameServer.h"
#include "watCardOffice.h"
#include "groupoff.h"
#include "student.h"

using namespace std;

static intmax_t convert( const char * str ) {			// convert C string to integer
	char * endptr;
	errno = 0;											// reset
	intmax_t val = strtoll( str, &endptr, 10 );			// attempt conversion
	if ( errno == ERANGE ) throw std::out_of_range("");
	if ( endptr == str ||								// conversion failed, no characters generated
		 *endptr != '\0' ) throw std::invalid_argument(""); // not at end of str ?
	return val;
} // convert

int main( int argc, char * argv[] ) {
	istream * config = new ifstream("soda.config");
	intmax_t seed, processors = 1;				// defaults

	try {
		switch ( argc ) {
          case 4: processors = if ( strcmp( argv[2], "d" ) != 0 ) { convert( argv[3] ); if ( processors <= 0 ) throw 1; }
		  case 3: seed = if ( strcmp( argv[2], "d" ) != 0 ) { convert( argv[2] ); if ( seed <= 0 ) throw 1; else set_seed(seed); }
		  case 2: config = if ( strcmp( argv[2], "d" ) != 0 ) { delete config; new ifstream( argv[1] ); if ( config.fail() ) { cerr << "Error! Could not open input file \"" << argv[3] << "\"" << endl; throw 1; }}
		  case 1: break;								// use defaults
		  default: throw 1;
		} // switch
	} catch( ... ) {
		cout << "Usage: " << argv[0] << " [ config-file | ’d’ [ seed (> 0) | ’d’  [ processors (> 0)| ’d’ ] ] ]" << endl;
		exit( 1 );
	} // try

	Printer & prt;
	NameServer & nameServer;
	WATCardOffice & cardOffice;
	Groupoff & groupoff;

	Student* studs[NumStudents];
    uProcessor p[processors - 1] __attribute__(( unused )); // create more kernel threads
    {
		for (int i = 0; i < numStudents; i += 1) {
			studs[i] = new Student(prt, nameServer, cardOffice, groupoff, i + 1, maxPurchases);
		}

		for (int i = 0; i < numStudents; i += 1) delete studs[i];
    }
} // main
