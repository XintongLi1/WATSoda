#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

#include "bottlingPlant.h"

_Task NameServer;
class Printer;
class WATCard;

_Task VendingMachine {
	unsigned int id, sodaCost, * stock;
	bool restocking = false;

	Printer & prt;
	NameServer & nameServer;
	BottlingPlant::Flavours purchaseFlavour;
	WATCard & purchaseCard;
	void main();
  public:
	_Event Free {};						// free, advertisement
	_Event Funds {};					// insufficient funds
	_Event Stock {};					// flavour out of stock
	VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost );
	~VendingMachine();
	void buy( BottlingPlant::Flavours flavour, WATCard & card );
	unsigned int * inventory() __attribute__(( warn_unused_result ));
	void restocked();
	_Nomutex unsigned int cost() const;
	_Nomutex unsigned int getId() const;
};

#endif