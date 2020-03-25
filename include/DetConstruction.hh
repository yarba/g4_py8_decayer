#ifndef DetConstruction_H
#define DetConstruction_H

#include "G4VUserDetectorConstruction.hh"
// ---> #include "G4ThreeVector.hh"
#include "CLHEP/Units/SystemOfUnits.h"

class G4VPhysicalVolume;

class DetConstruction : public G4VUserDetectorConstruction
{

   public:

      // ctor & dtor
      //
      DetConstruction() : G4VUserDetectorConstruction(), 
                          fWorld(0), fDet(0)  {}
      ~DetConstruction() {} /* we don't need to delete fWorld or fDet 
                               as it'll be done "globally" */
    
      // methods/functions
      // 
      virtual G4VPhysicalVolume* Construct();
   
   private:

     // data members
     //
     G4VPhysicalVolume* fWorld;
     G4VPhysicalVolume* fDet;

};

#endif
