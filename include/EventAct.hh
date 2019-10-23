

#ifndef CPROJECT_EVENTACT_HH
#define CPROJECT_EVENTACT_HH

#include "G4UserEventAction.hh"
#include "G4RunManager.hh"
#include "RunAct.hh"
#include "Run.hh"
#include <vector>

using namespace std;

class RunAct;

class EventAct : public G4UserEventAction
{
public:
    EventAct(RunAct* runAct);
   // ~EventAct();

      void BeginOfEventAction(const G4Event* anEvent);
      void EndOfEventAction(const G4Event* anEvent);
      void AddEnDep1 (G4double en1);
      void AddEnDep1_1 (G4double en1_1);
      void AddEnDep2 (G4double en2);
      vector <double> VecEnergy;
      vector <double> VecTime;



private:
      RunAct *run;
      G4double EnergyDep1;
      G4double EnergyDep1_1;
      G4double EnergyDep2;

};

#endif //CPROJECT_EVENTACT_HH
