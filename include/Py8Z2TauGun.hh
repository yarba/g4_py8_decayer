#ifndef Py8PrimaryGeneratorAction_H
#define Py8PrimaryGeneratorAction_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4LorentzVector.hh"
#include "globals.hh"

#include "Pythia8/Pythia.h"

// #include <vector>

class Py8Z2TauGun  : public G4VUserPrimaryGeneratorAction 
{

   public:
   
      // ctor & dtor
      Py8Z2TauGun();
      ~Py8Z2TauGun();
      
      // methods/fuctions
      virtual void GeneratePrimaries( G4Event* );
   
   private:
   
      // data members
      Pythia8::Pythia* fMasterGen;
      int              fPartID;
      double           fPartP;
      G4LorentzVector  fVtx;

};

#endif
