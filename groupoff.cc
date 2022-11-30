#include "groupoff.h"
#include "printer.h"

Groupoff::Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) : prt(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay) {
    fcards = new WATCard::FWATCard[numStudents];
    cards = new WATCard*[numStudents];
    gifted = new bool[numStudents];
    prt.print(Printer::Kind::Groupoff, 'S');
}


Groupoff::~Groupoff() {
    for (unsigned int i = 0; i < numStudents; i += 1) {
        if (gifted[i]) delete cards[i];
    }
    delete gifted;
}

unsigned int Groupoff::getNextCard(unsigned int cardsCreated, unsigned int cardsGifted) {
    unsigned int baseIndex = prng(cardsCreated - cardsGifted);

    while (gifted[baseIndex]) baseIndex = (baseIndex + 1) % cardsCreated;

    return baseIndex;
}

WATCard::FWATCard Groupoff::giftCard() {
    WATCard::FWATCard c;
    fcards[cardsCreated] = c;
    return c;
}


void Groupoff::main() {
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
                unsigned int index = getNextCard(cardsCreated, cardsGifted);

                // create real giftcard and give sodaCost
                cards[index] = new WATCard();
                cards[index]->deposit(sodaCost);
                gifted[index] = true;

                prt.print(Printer::Kind::Groupoff, 'D', sodaCost);

                cardsGifted += 1;

            }
        }
    }
   prt.print(Printer::Kind::Groupoff, 'F');
}
