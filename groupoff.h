#ifndef __GROUPOFF_H__
#define __GROUPOFF_H__

#include "watcard.h"

class Printer;

_Task Groupoff {
	Printer & prt;
	unsigned int numStudents, sodaCost, groupoffDelay, cardsCreated = 0, cardsGifted = 0;
	bool * gifted;

	WATCard::FWATCard * fcards;
	WATCard ** cards;

	unsigned int getNextCard(unsigned int cardsCreated, unsigned int cardsGifted);
	void main();
  public:
	Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
	~Groupoff();
	WATCard::FWATCard giftCard();
};

#endif