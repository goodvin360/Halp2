
#include "RunAct.hh"
#include "EventAct.hh"
#include "StepAct.hh"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <map>

using namespace std;

RunAct::RunAct()
{
    result1 = new std::map<G4double, G4int>;

    result1_1 = new std::map<G4double, G4int>;

    result2 = new std::map<G4double, G4int>;


}

RunAct::~RunAct()
{
    delete result1;

    delete result1_1;

    delete result2;


}

void RunAct::BeginOfRunAction(const G4Run *aRun)
{


    result1->clear();
    for (int i=0; i <nStep; i++)
        result1->insert(std::pair<G4double, G4int> (i *Tmax / nStep, 0));

    result1_1->clear();
    for (int i=0; i <nStep; i++)
        result1_1->insert(std::pair<G4double, G4int> (i *Tmax / nStep, 0));

    result2->clear();
    for (int i=0; i <nStep; i++)
        result2->insert(std::pair<G4double, G4int> (i *Tmax / nStep, 0));

}


void RunAct::EndOfRunAction(const G4Run *aRun)
{
    fstream fout1("/mnt/hgfs/VMplayer/Halp2/empty1.txt", ios::out);
    for (auto it1: *result1)
        fout1 << it1.first << " " << it1.second << '\n';
    fout1.close();

    fstream fout1_1("/mnt/hgfs/VMplayer/Halp2/t_diagram.txt", ios::out);
    for (auto it1_1: *result1_1)
        fout1_1 << it1_1.first << " " << it1_1.second << '\n';
    fout1_1.close();

    fstream fout2("/mnt/hgfs/VMplayer/Halp2/empty2.txt", ios::out);
    for (auto it2: *result2)
        fout2 << it2.first << " " << it2.second << '\n';
    fout2.close();

}

void RunAct::AddEvent1(G4double energy1)
{
    auto it1 = result1->lower_bound(energy1);
    it1->second++;
}

void RunAct::AddEvent1_1(G4double energy1_1)
{
    auto it1_1 = result1_1->lower_bound(energy1_1);
    it1_1->second++;
}

void RunAct::AddEvent2(G4double energy2)
{
    auto it2 = result2->lower_bound(energy2);
    it2->second++;

}




