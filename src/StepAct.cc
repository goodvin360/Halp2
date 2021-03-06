
#include "StepAct.hh"
#include "G4SystemOfUnits.hh"


StepAct::StepAct(EventAct *eventAct):event(eventAct)
{

}

void StepAct::UserSteppingAction(const G4Step *aStep)

{


//    G4Track*theTrack = aStep->GetTrack();


    if ((aStep->GetTrack()->GetVolume()->GetLogicalVolume()->GetName() =="Body") &&
        (aStep->GetTrack()->GetDynamicParticle()->GetParticleDefinition()->GetParticleName()=="neutron")&&
        (aStep->GetTrack()->GetTrackID()==1))


    {
        event->AddEnDep1(aStep->GetTrack()->GetKineticEnergy()*1E9);

    }

    /*if ((aStep->GetTrack()->GetTrackID()!=1))
    {
        aStep->GetTrack()->SetTrackStatus(fStopAndKill);
    }*/

    if ((aStep->GetTrack()->GetVolume()->GetLogicalVolume()->GetName() =="Body") &&
        (aStep->GetTrack()->GetDynamicParticle()->GetParticleDefinition()->GetParticleName()=="neutron")&&
            (aStep->GetTrack()->GetTrackID()==1)&&
            (aStep->GetTrack()->GetKineticEnergy()<=0.000000025)&&
//            (aStep->GetTrack()->GetKineticEnergy()>=0.000000024))
            (aStep->GetTrack()->GetKineticEnergy()>0))


    {
        event->AddEnDep1_1(aStep->GetTrack()->GetGlobalTime()/1E3);
        event->AddEnDep2(aStep->GetTrack()->GetGlobalTime()/1E3);

        /*G4cout <<endl;
        G4cout << endl << "Current Step number is " << aStep->GetTrack()->GetCurrentStepNumber();
        G4cout << endl << "Kinetic Energy is " << aStep->GetTrack()->GetDynamicParticle()->GetKineticEnergy() ;
        G4cout << endl << "Velocity is " << aStep->GetTrack()->GetVelocity() ;
        G4cout << endl << "Step lenght is " << aStep->GetTrack()->GetStepLength();
        G4cout << endl << "Global Time is " << aStep->GetTrack()->GetGlobalTime()/1E3;
        G4cout << endl << "Delta Time is " << aStep->GetDeltaTime()/1E3 ;
        G4cout << endl;*/

        aStep->GetTrack()->SetTrackStatus(fStopAndKill);
    }
}

