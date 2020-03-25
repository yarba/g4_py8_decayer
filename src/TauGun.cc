
#include "TauGun.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"

TauGun::TauGun()
   : G4VUserPrimaryGeneratorAction(),
     fPartGun(nullptr),
     fGunP(0.)
{

   int nParts = 1;
   fPartGun = new G4ParticleGun( nParts );
   
   fGunP = 25.0;
   
   G4ParticleTable* pdt = G4ParticleTable::GetParticleTable();
   G4ParticleDefinition* pd = pdt->FindParticle( "tau-" );
   fPartGun->SetParticleDefinition( pd );
   fPartGun->SetParticlePosition( G4ThreeVector(0.,0.,0.) );
   double mass = pd->GetPDGMass();
   double energy = sqrt( fGunP*fGunP + mass*mass );
   fPartGun->SetParticleEnergy( energy );
   
   // do not set momentum directions as it'll be generated event-by-event

}

TauGun::~TauGun()
{

   if ( fPartGun )
   {
      delete fPartGun;
      fPartGun = nullptr;
   }

}

void TauGun::GeneratePrimaries(G4Event* anEvent)
{

   double phi = -1. * CLHEP::pi + CLHEP::twopi * G4UniformRand();
   double theta = CLHEP::pi/4. + CLHEP::halfpi * G4UniformRand();
   
   double x = sin(theta) * cos(phi);
   double y = sin(theta) * sin(phi);
   double z = cos(theta);
   
   fPartGun->SetParticleMomentumDirection( G4ThreeVector(x,y,z) );
   
   fPartGun->GeneratePrimaryVertex(anEvent);
   
   return;

}
