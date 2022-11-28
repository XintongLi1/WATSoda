#include "watcardOffice.h"


WATCardOffice::Courier::Courier(unsigned int id, WATCardOffice * office, Printer & prt, Bank & bank) :
    id(id), office(office), prt(prt), bank(bank) {}

void WATCardOffice::Courier::main(){
    //  start
    prt.print(Printer::Courier, 'S');
    for (;;){
        Job * job = office->requestWork();
        if (job == nullptr){
            // end 
            prt.print(Printer::Courier, 'F');
            return;
        }
        if (cprng(6) == 0){
            // lost watcard
            prt.print(Printer::Courier, 'L', job->args.sid);
            job->result.delivery(new Lost);
            delete job->args.card;
        } else {
            // start funds transfer
            prt.print(Printer::Courier, 't', jobs->args.sid, jobs->args.amount);
            bank.withdraw(jobs->args.sid, jobs->args.amount);
            job->card->deposit(job->args.amount);
            // complete funds transfer
            prt.print(Printer::Courier, 'T', jobs->args.sid, jobs->args.amount);
            job->result.delivery(job->args.card);
        }
        delete job;
    }
}

// ========================= End of Courier Implementation =================================
// ========================= Start of WATCardOffice Implementation =========================


WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers )
    : prt(prt), bank(bank), numCouriers(numCouriers) {
        couriers = new Courier* [numCouriers]; // create a courier pool
    }

WATCardOffice::~WATCardOffice(){
    for (unsigned int i = 0; i < numCouriers; ++i){
        delete couriers[i];
    }
    delete [] couriers;
}

void WATCardOffice::main(){
    //  start
    prt.print(Printer::WATCardOffice, 'S');
    //  start all couriers in the pool
    for (unsigned int i = 0; i < numCouriers; ++i){
        couriers[i] = new Courier(i, this, prt, bank);
    }

    for (;;){
        _Accept( ~WATCardOffice ){
            while (!jobs.empty()){
                _Accept ( requestWork );
            }
            break;
        }
        or _Accept( create || transfer );
        or _When (!jobs.empty()) _Accept ( requestWork ){
            // request work call complete
            prt.print(Printer::WATCardOffice, 'W');
        }
    }
    // finish
    prt.print(Printer::WATCardOffice, 'F');
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    newJob = new Job(Args{sid, amount, new WATCard()});
    jobs.push(newJob);
    // create call complete
    prt.print(Printer::WATCardOffice, 'C', sid, amount);
    return newJob->result;
}

 
WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ) {
    newJob = new Job(Args{sid, amount, card});
    jobs.push(newJob);
    // transfer call complete
    prt.print(Printer::WATCardOffice, 'T', sid, amount);
    return newJob->result;
}
   
Job * WATCardOffice::requestWork() {
    if (jobs.empty()){  // no job available
        return nullptr;
    }
    Job* job = jobs.front();
    jobs.pop();     // remove the first job from queue
    return job;    
}
