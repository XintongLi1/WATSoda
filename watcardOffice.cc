#include <uPRNG.h>
#include "watcardOffice.h"
#include "bank.h"
#include "printer.h"

WATCardOffice::Courier::Courier(unsigned int id, WATCardOffice * office, Printer & prt, Bank & bank) :
    id(id), office(office), prt(prt), bank(bank) {}

void WATCardOffice::Courier::main(){
    //  start
    prt.print(Printer::Courier, id, 'S');
    for (;;){
        _Accept (~Courier) {
            break;
        } _Else {
            Job * job = office->requestWork();

            if ( job == nullptr ) break;

            if (prng(6) == 0){
                // lost watcard
                prt.print(Printer::Courier, id, 'L', job->args.sid);
                job->result.delivery(new Lost);
                delete job->args.card;
            } else {
                // start funds transfer
                prt.print(Printer::Courier, id, 't', job->args.sid, job->args.amount);
                bank.withdraw(job->args.sid, job->args.amount);
                job->args.card->deposit(job->args.amount);
                // complete funds transfer
                prt.print(Printer::Courier, id, 'T', job->args.sid, job->args.amount);
                job->result.delivery(job->args.card);
            }
            delete job;
        }
    }
    prt.print(Printer::Courier, id, 'F');
}

// ========================= End of Courier Implementation =================================
// ========================= Start of WATCardOffice Implementation =========================


WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers )
    : prt(prt), bank(bank), numCouriers(numCouriers) {
    couriers = new Courier*[numCouriers]; // create a courier pool
    //  start all couriers in the pool
    for (unsigned int i = 0; i < numCouriers; ++i){
        couriers[i] = new Courier(i, this, prt, bank);
    }
}

WATCardOffice::~WATCardOffice(){
    for (unsigned int i = 0; i < numCouriers; ++i){
        delete couriers[i];
    }	
    delete [] couriers;

    while (!jobs.empty()) {
        Job* job = jobs.front();
        delete job;
        jobs.pop();     // remove the first job from queue
    }
}

void WATCardOffice::main(){
    //  start
    prt.print(Printer::WATCardOffice, 'S');

    for (;;){
        _Accept( ~WATCardOffice ){
            for (unsigned int i = 0; i < numCouriers; i += 1){
                _Accept ( requestWork );
            }
            break;
        }        
        or _When (!jobs.empty()) _Accept ( requestWork ){
            // request work call complete
            prt.print(Printer::WATCardOffice, 'W');
        }
        or _Accept( create || transfer );
    }
    // finish
    prt.print(Printer::WATCardOffice, 'F');
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    Job * newJob = new Job(Args{sid, amount, new WATCard()});
    jobs.push(newJob);
    // create call complete
    prt.print(Printer::WATCardOffice, 'C', sid, amount);
    return newJob->result;
}

 
WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ) {
    Job * newJob = new Job(Args{sid, amount, card});
    jobs.push(newJob);
    // transfer call complete
    prt.print(Printer::WATCardOffice, 'T', sid, amount);
    return newJob->result;
}
   
WATCardOffice::Job * WATCardOffice::requestWork() {
    if (jobs.empty()){  // no job available
        return nullptr;
    }
    Job* job = jobs.front();
    jobs.pop();     // remove the first job from queue
    return job;    
}
