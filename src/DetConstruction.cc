
#include "DetConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

G4VPhysicalVolume* DetConstruction::Construct()
{

   // Define materials via NIST manager
  
   auto worldMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"); 
   auto detMaterial   = G4NistManager::Instance()->FindOrBuildMaterial("G4_C"); 

   // World volume
 
   G4ThreeVector worldSize( 200.*CLHEP::cm, 200.*CLHEP::cm, 200.*CLHEP::cm );
  

   fWorld = new G4PVPlacement( 0, G4ThreeVector(), "world_phys",
                               new G4LogicalVolume( new G4Box( "world_solid", 
			                                       0.5*worldSize.x(), 
							       0.5*worldSize.y(), 
							       0.5*worldSize.z() ),
			                            worldMaterial, "world_log", 0, 0, 0 ), 
			       0,
			       false, 0 );

  // "Detector"

  double rmin    = 10.*CLHEP::cm;
  double rmax    = 80.*CLHEP::cm;
  double zlength = 98.*CLHEP::cm;
  
  G4VSolid* sDet = new G4Tubs( "det_solid", rmin, rmax, 0.5*zlength, 0., 2.*CLHEP::pi );
  
  G4LogicalVolume* lDet = new G4LogicalVolume( sDet, detMaterial, "det_log", 0, 0, 0 );
  
  fDet = new G4PVPlacement( 0, G4ThreeVector(), "det_phys",
                            lDet, 
		            fWorld,       // it's mother (physical) volume 
		            false, 0 );
  
  
  //always return the root volume
  //
  return fWorld;

}
