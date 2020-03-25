#ifndef TauGun_H
#define TauGun_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

// fwd declarations
//
class G4ParticleGun;
class G4Event;

class TauGun : public G4VUserPrimaryGeneratorAction
{

   public:
   
      //ctor & dtor
      TauGun();
      ~TauGun();
      
      // methods/functions
      virtual void GeneratePrimaries(G4Event*);   
   
   private:
   
      // data members
      G4ParticleGun* fPartGun;
      double         fGunP;
};

#endif
