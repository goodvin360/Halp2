

#ifndef CPROJECT_STEPACT_HH
#define CPROJECT_STEPACT_HH

#include <G4UserRunAction.hh>
#include <G4UserSteppingAction.hh>
#include "EventAct.hh"
#include "Run.hh"

class StepAct: public G4UserSteppingAction
{
public:
    StepAct (EventAct* eventAct);

    void UserSteppingAction(const G4Step*);

private:

    EventAct* event;


};



#endif //CPROJECT_STEPACT_HH
