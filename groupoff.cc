#include "groupoff.h"

Groupoff::Groupoff( unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) : prt(prt), numStudents(numStudents), sodaCost(sodeCost), groupOffDelay(groupoffDelay) {
    prt.print(Printer::Kind::Groupoff, 'S');
}

unsigned int Groupoff::getNextCard(unsigned int cardsCreated, unsigned int cardsGifted) {
    unsigned int baseIndex = prng(cardsCreated - cardsGifted);

    while (gifted[baseIndex]) baseIndex = (baseIndex + 1) % cardsCreated;

    return baseIndex;
}

Groupoff::~Groupoff() {
    for (int i = 0; i < numStudents) {
        if (gifted[i]) delete cards[i];
    }
}

WATCard::FWATCard Groupoff::giftCard() {
    WATCard::FWATCard c;
    cards.push_back(c);
    return c;
}


void Groupoff::main() {
    unsigned int cardsCreated = 0, cardsGifted = 0;
    // first accept a call from all students to recieve a future giftcard
    while (cardsCreated < numStudents) {
        _Accept(giftCard) cardsCreated += 1;
    }

    while (cardsGifted < numStudents) {

        for (;;) {

            _Accept(~Groupoff) break;
            _Else {
                if (cardsCreated == 0) break;
                // yields non random amount
                yield(groupoffDelay);

                // select a random future giftcard - non repeating
                unsigned int index = getNextCard(cardsGifted);

                // create real giftcard and give sodaCost
                cards[index] = new WATCard::WATCard();
                cards[index].deposit(sodaCost);

                prt.print(Printer::Kind::Groupoff, 'D', sodaCost);

                cardsGifted += 1;

            }
        }
    }
   prt.print(Printer::Kind::Groupoff, 'F');
}
