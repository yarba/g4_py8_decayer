#ifndef SinglePartGun_H
#define SinglePartGun_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

// fwd declarations
//
class G4ParticleGun;
class G4Event;

class SinglePartGun : public G4VUserPrimaryGeneratorAction
{

   public:

      //ctor & dtor
      // ---> SinglePartGun();
      SinglePartGun( const G4String&, const double );
      ~SinglePartGun();

      // methods/functions
      virtual void GeneratePrimaries( G4Event* );

   private:

      // data members
      G4ParticleGun* fGun;
      double         fMomentum;
};

#endif
