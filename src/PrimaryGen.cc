
#include "PrimaryGen.hh"
#include "G4RandomTools.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "vector"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "PrimaryGenMessenger.hh"
#include <ctime>

using namespace std;

class PrimaryGenMessenger1;


PrimaryGen::PrimaryGen()
{


    primarygenmessenger1 = new PrimaryGenMessenger1(this);
    primarygenmessenger2 = new PrimaryGenMessenger2(this);

    GPSgun = new G4GeneralParticleSource();

   gun = new G4ParticleGun(1);

    gun->SetParticleDefinition(G4Neutron::Neutron());       // for ING_07

   gun->SetNumberOfParticles(1);

#ifdef SingleEnergy
    gun->SetParticleEnergy(0.059*MeV);
#endif

#ifdef OuterSpectra

    ew = new map <G4double, G4double>;

    G4int FileSize=0;

    char *str = new char [1024];

    ifstream infile;
    infile.open(outerspectrapath);
    while(!infile.eof()){
        infile.getline(str, 1024, '\n');
        FileSize++;
    }

    delete str;
    infile.close();

    FileSize = FileSize-1;

    ifstream infile1;
    infile1.open(outerspectrapath);
    G4double P;
    G4double E;

    G4double **Spectr = new G4double*[FileSize];

    for(G4int count =0; count <FileSize; count++)
    {
        Spectr[count] = new G4double [2];
    }

//    infile1 >> E >> P;

    for (int i = 0; i < FileSize; i++)
    {
        infile1 >> E >> P;
        Spectr[i][1] = E;
        Spectr[i][2] = P;
    }
    infile1.close();

    G4double  K=0;

    for (int i=0; i<FileSize; i++)
    {
        K = K+Spectr[i][2];
    }

    G4double  * Pspectr = new G4double[FileSize];
    G4double  K1=0;

    for (int i=0; i<FileSize; i++)
    {
        K1 = K1+Spectr[i][2];
        Pspectr[i] = K1;
    }

    G4double * Pnorm = new G4double [FileSize];

    for (int i = 0; i < FileSize; i++)
    {
        Pnorm[i] = Pspectr[i]/K;
    }

    fstream fout1(outerspectrapath2, ios::out);
    for (int i=0; i<FileSize; i++)
        fout1 << Pnorm[i] << '\t'<< Spectr[i][1] << '\n';
    fout1.close();

    G4double P1;
    G4double E1;

    ifstream infile2;
    infile2.open(outerspectrapath2);

    do
    {infile2 >> P1 >> E1;
        ew->insert(std::pair<G4double, G4double> (P1, E1));
    }
    while(!infile2.eof());

    for (int count=0; count<FileSize;count++)
    { delete [] Spectr[count];}

    delete [] Pnorm;
    delete [] Pspectr;
#endif

}

PrimaryGen::~PrimaryGen()
{
#ifdef OuterSpectra
    delete ew;
#endif

delete gun;

//delete GPSgun;

delete primarygenmessenger1;
delete primarygenmessenger2;

}

void PrimaryGen::GeneratePrimaries(G4Event* anEvent)
{

    //for outer energy spectra
#ifdef OuterSpectra
    G4double rand = G4UniformRand();

    map<G4double, G4double>::iterator it=ew->lower_bound(rand);

    gun->SetParticleEnergy(it->second*MeV);
#endif

    //set the cylinder beam particle distribution

   /* G4double R=0.025*cm;
    G4double cosTheta = 2*G4UniformRand()-1., phi = twopi*G4UniformRand();
    G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
    G4double ux = R*sinTheta*std::sin(phi),
            uy = R*cosTheta,
            uz = 1.35*cm;  //for ING_07

    gun->SetParticlePosition(G4ThreeVector(ux,uy,uz));*/

   //set the point source in the center of the World

    gun->SetParticlePosition(G4ThreeVector(0,0,0));

    //set the square beam particle distribution

//    G4double XY=1.99*cm;
//    G4double Z = 0.049*cm;
//
//    double ux = XY*(2*G4UniformRand()-1);
//    double uy = XY*(2*G4UniformRand()-1);
//    double uz = 0*cm+Z*(2*G4UniformRand()-1);
//
//
//    gun->SetParticlePosition(G4ThreeVector(ux,uy,uz));



//    gun->SetParticlePosition(G4ThreeVector(0,0,4*cm));

    double dX, dY, dZ;

//set the cone particle distribution

    /*
    G4double cosTheta = 0.3*G4UniformRand()-1., phi = twopi*G4UniformRand();
    G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
    G4double ux = sinTheta*std::cos(phi),
            uy = sinTheta*std::sin(phi),
            uz = cosTheta;

    gun->SetParticlePosition(G4ThreeVector(0.0*m,0.0*m,1.125*cm));

    gun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,-uz));

    */

//set the isotropic particle distribution

    G4double cosTheta1 = 2*G4UniformRand()-1, phi1 = twopi*G4UniformRand();
    G4double sinTheta1 = std::sqrt(1. - cosTheta1*cosTheta1);
    dX = sinTheta1*std::cos(phi1),
    dY = sinTheta1*std::sin(phi1),
    dZ = cosTheta1;

//    gun->SetParticleMomentumDirection(G4ThreeVector(dX,dY,dZ));
    gun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));

    gun->GeneratePrimaryVertex(anEvent);

//GPSgun->GeneratePrimaryVertex(anEvent);



    Counter += 1;
    Sum += 1;

    double t = clock();

    if (Sum == (Step/2))
    {
        t1 = t/1000000;
    }

    if (Sum == (Step/2+100))
    {
        t2 = t/1000000;
    }

    dt = t2 - t1;

    if (Counter == Step)
    {
        cout << "Amount of shooted particle: " << Sum << endl;
        cout << "Time from start, s = " << t / 1000000 << endl;
        cout << "Time left, s = " << dt * ((PCounts-Sum) /100) << endl;
        cout << endl;
        Counter = 0;
    }

}
