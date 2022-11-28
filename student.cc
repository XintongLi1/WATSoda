#include "student.h"

Student::Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
                    unsigned int id, unsigned int maxPurchases ) : prt(prt), nameServer(nameServer), cardOffice(cardOffice), groupoff(groupoff), id(id), maxPurchases(maxPurchases) {
    // select number of bottles to purchase
    unsigned int amount = prng(1, MaxPurchases);
    
    // select a favourite flavour
    unsigned int flavour = prng(0, 3);
    prt.print(Printer::Kind::Student, id, 'S', flavour, amount);

    // create WATCard with $5 balance
    card = cardOffice.create(id, 5);

    // create gift card with value of SodaCost
    giftCard = groupoff.giftCard();

    // find vending machine location
    vm = nameServer.getMachine();
    prt.print(Printer::Kind::Student, id, 'V', (int)(vm->getId()));
}

void Student::main() {
    unsigned int purchased = 0;
    while ( purchased < amount ) {
        // yield random number 1 - 10 to decide next purchase
        yield(prng(1, 10));

        for (;;) {

            try {
                unsigned int giftCardBalance = giftCard.getBalance(), cardBalance = card.getBalance(), sodaCost = vm.cost();
                
                // wait until enough funds
                while (giftCardBalance < sodaCost && cardBalance < sodaCost ) {

                }
                
                // purchase (Use gift card first)
                WATCard::FWATCard purchaseCard = giftCardBalance >= sodaCost ? giftCard : card;

                vm.buy(flavour, purchaseCard);
                purchased += 1;
                prt.print(Printer::Kind::Student, id, 'G', flavour, (int)card->getBalance());
                break;
            } catch ( VendingMachine::Free & ) {
                //  must watch an ad
                yield(4);
                purchased += 1;
                prt.print(Printer::Kind::Student, id, 'a', flavour, get->getBalance());
                break;
            } catch ( VendingMachine::Funds & ) {
                // insufficient funds
                cardOffice.transfer(id, 5 + vendingMachine->cost(), card);
            } catch (VendingMachine::Stock &) {
                // out of stock change machine and try again
                vm = cardOffice.getMachine();
                prt.print(Printer::Kind::Student, id, 'V', vm->getId());
            } catch( WATCardOffice::Lost & ) {
                // lost card try again
                prt.print(Printer::Kind::Student, id, 'L');
                // create WATCard with $5 balance
                card = cardOffice.create(id, 5);
            }
        }
    }
    prt.print(Printer::Kind::Student, id, 'F');
}
