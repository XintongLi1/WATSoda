#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

class WATCard {
	WATCard( const WATCard & ) = delete;	// prevent copying
	WATCard( const WATCard && ) = delete;
	WATCard & operator=( const WATCard & ) = delete;
	WATCard & operator=( const WATCard && ) = delete;
  public:
	typedef Future_ISM<WATCard *> FWATCard;	// future watcard pointer
	WATCard();
	void deposit( unsigned int amount );
	void withdraw( unsigned int amount );
	unsigned int getBalance();
};

_Task WATCardOffice {
	struct Job {							// marshalled arguments and return future
		Args args;							// call arguments (YOU DEFINE "Args")
		WATCard::FWATCard result;			// return future
		Job( Args args ) : args( args ) {}
	};
	_Task Courier { ... };					// communicates with bank

	void main();
  public:
	_Event Lost {};							// lost WATCard
	WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
	WATCard::FWATCard create( unsigned int sid, unsigned int amount )
		__attribute__(( warn_unused_result ));
	WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card )
		__attribute__(( warn_unused_result ));
	Job * requestWork() __attribute__(( warn_unused_result ));
};

#endif