#ifndef __GROUPOFF_H__
#define __GROUPOFF_H__

_Task Groupoff {
	unsigned int numStudents, sodaCost, groupoffDelay ;
	bool * gifted;

	WATCard::FWATCard * cards;

	Printer & prt;
	unsigned int getNextCard();
	void main();
  public:
	Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
	~Groupoff();
	WATCard::FWATCard giftCard();
};

#endif