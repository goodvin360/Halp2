#include "DetGeometry.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Color.hh"
#include "G4RotationMatrix.hh"
#include "G4Sphere.hh"
#include "G4SubtractionSolid.hh"

DetGeometry::DetGeometry() {

}

DetGeometry::~DetGeometry() {}

G4VPhysicalVolume* DetGeometry::Construct(){

    G4NistManager* nist = G4NistManager::Instance();

    G4double Size = 1*m;

    WorldX = WorldY = WorldZ = 1*Size;

    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

    G4Box* solidWorld =
      new G4Box("World",
         WorldX/2, WorldY/2, WorldZ/2);

    G4LogicalVolume* logicWorld =
      new G4LogicalVolume(solidWorld,
                          world_mat,
                          "World");

logicWorld->SetVisAttributes(G4VisAttributes::Invisible);

 G4VPhysicalVolume* physWorld =
      new G4PVPlacement(0,
                        G4ThreeVector(),
                        logicWorld,
                        "World",
                        0,
                        false,
                        0);

    //define materials

    G4Material*ferrum = nist->FindOrBuildMaterial("G4_Fe");
    G4Material*carbon = nist->FindOrBuildMaterial("G4_C");
    G4Material*poly = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
    G4Material*void_mat =nist->FindOrBuildMaterial("G4_Galactic");
    G4Material*water = nist->FindOrBuildMaterial("G4_WATER");



    // body creating

    G4ThreeVector body_pos = G4ThreeVector(0, 0, 0);

    G4Box*body = new G4Box("Body", WorldX/2-1, WorldY/2-1, WorldZ/2-1);

    G4LogicalVolume*logic_bdy = new G4LogicalVolume(body, ferrum, "Body");

    G4VisAttributes*logic_Vis_bdy = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));

    logic_bdy->SetVisAttributes(logic_Vis_bdy);


    new G4PVPlacement(0,
                      body_pos,
                      logic_bdy,
                      "Body",
                      logicWorld,
                      false,
                      0);


    return physWorld;
}
