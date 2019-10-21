
#include "EventAct.hh"
#include "StepAct.hh"

EventAct::EventAct(RunAct *runAct):run(runAct)
{

}

//EventAct::~EventAct()


void EventAct::BeginOfEventAction(const G4Event *anEvent)
{
    EnergyDep1 = 0;
    EnergyDep1_1 = 0;
    EnergyDep2 = 0;



}

void EventAct::EndOfEventAction(const G4Event *anEvent)
{
//    Run* run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    run->AddEvent1(EnergyDep1);
    run->AddEvent1_1(EnergyDep1_1);
    run->AddEvent2(EnergyDep2);


}

void EventAct::AddEnDep1(G4double en1)
{
    EnergyDep1 = en1;
}

void EventAct::AddEnDep1_1(G4double en1_1)
{
    EnergyDep1_1 = en1_1;
}

void EventAct::AddEnDep2(G4double en2)
{
    EnergyDep2 += en2;
}

