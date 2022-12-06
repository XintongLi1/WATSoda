#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include "watcard.h"
#include <queue>

class Printer;
class Bank;

_Task WATCardOffice {
	Printer & prt;
	Bank & bank;
	unsigned int numCouriers;

	struct Args {
		unsigned int sid, amount;
		WATCard * card;
	};
	
	struct Job {						// marshalled arguments and return future
		Args args;							// call arguments (YOU DEFINE "Args")
		WATCard::FWATCard result;			// return future
		Job( Args args ) : args( args ) {}
	};

	_Task Courier { 					// communicates with bank
		unsigned int id;
		WATCardOffice * office;
		Printer & prt;
		Bank & bank;

		void main();

	  public:
		Courier(unsigned int id, WATCardOffice * office, Printer & prt, Bank & bank);

	};

	Courier ** couriers;
	std::queue<Job *> jobs;		// a list of jobs

	void main();
  public:
	_Event Lost {};							// lost WATCard
	WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
	WATCard::FWATCard create( unsigned int sid, unsigned int amount )
		__attribute__(( warn_unused_result ));
	WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card )
		__attribute__(( warn_unused_result ));
	Job * requestWork() __attribute__(( warn_unused_result ));
	~WATCardOffice();
};

#endif