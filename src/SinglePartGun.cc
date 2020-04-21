#include "SinglePartGun.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"

/*
SinglePartGun::SinglePartGun()
   : G4VUserPrimaryGeneratorAction(),
     fGun(nullptr),
     fMomentum(0.)
{
}
*/
SinglePartGun::SinglePartGun( const G4String& pname, const double pmom )
   : G4VUserPrimaryGeneratorAction(),
     fGun(nullptr),
     fMomentum(pmom)
{
   int nParts = 1;
   fGun = new G4ParticleGun( nParts );

   G4ParticleTable* pdt = G4ParticleTable::GetParticleTable();
   G4ParticleDefinition* pd = pdt->FindParticle( pname );
   fGun->SetParticleDefinition( pd );
   fGun->SetParticlePosition( G4ThreeVector(0.,0.,0.) );
   double mass = pd->GetPDGMass();
   double energy = sqrt( fMomentum*fMomentum + mass*mass );
   fGun->SetParticleEnergy( energy );

   // do not set momentum directions as it'll be generated event-by-event

}

SinglePartGun::~SinglePartGun()
{

   if ( fGun )
   {
      delete fGun;
      fGun = nullptr;
   }

}

void SinglePartGun::GeneratePrimaries( G4Event* anEvent )
{

   if ( !fGun )
   {
      G4cout << " ParticleGun is NOT set up; BAIL OUT from this event " << G4endl;
      G4cout << " Check if you are using ctor SinglePartGun(const G4string& partname, const double pmom ) " << G4endl;
      return;
   }

   double phi = -1. * CLHEP::pi + CLHEP::twopi * G4UniformRand();
   double theta = CLHEP::pi/4. + CLHEP::halfpi * G4UniformRand();

   double x = sin(theta) * cos(phi);
   double y = sin(theta) * sin(phi);
   double z = cos(theta);

   fGun->SetParticleMomentumDirection( G4ThreeVector(x,y,z) );

   // rhatcher 2020-04-21:  hard code this for testing purposes
   // probably tau_bar should be +1
   G4cout << "######### set polarization -1 * p3" << G4endl;
   fGun->SetParticlePolarization(G4ThreeVector(-1.0*x,-1.0*y,-1.0*z));

   fGun->GeneratePrimaryVertex(anEvent);

   return;

}
