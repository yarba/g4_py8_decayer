
#include "Py8DecayerPhysics.hh"
#include "Py8Decayer.hh"

#include <G4ParticleDefinition.hh>
#include <G4ProcessManager.hh>
#include <G4Decay.hh>
#include <G4DecayTable.hh>

// factory
#include "G4PhysicsConstructorFactory.hh"
// register it with contructor factory
G4_DECLARE_PHYSCONSTR_FACTORY(Py8DecayerPhysics);


Py8DecayerPhysics::Py8DecayerPhysics(G4int)
  : G4VPhysicsConstructor("Py8DecayerPhysics")
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Py8DecayerPhysics::~Py8DecayerPhysics() 
{
}

void Py8DecayerPhysics::ConstructParticle()
{
   // Nothing needs to be done here
}

void Py8DecayerPhysics::ConstructProcess()
{

   // Loop over all particles instantiated and add external decayer
   // to all decay processes where there's no decay table, plus tau's

   // Create external decayer for G4Decay process
   // NOTE: The extDecayer will be deleted in G4Decay destructor
   Py8Decayer* extDecayer = new Py8Decayer();

   auto particleIterator=GetParticleIterator();
   particleIterator->reset();
   while ((*particleIterator)())
   {    
      G4ParticleDefinition* particle = particleIterator->value();
      G4ProcessManager* pmanager = particle->GetProcessManager();    
/*
      if ( verboseLevel > 1 ) {
         G4cout << "Setting ext decayer for: " 
                <<  particleIterator->value()->GetParticleName()
                << G4endl;
      } 
*/    
      G4ProcessVector* processVector = pmanager->GetProcessList();
      for ( size_t i=0; i<processVector->length(); ++i ) 
      {    
         G4Decay* decay = dynamic_cast<G4Decay*>((*processVector)[i]);
         if ( decay ) 
	 {
	    // remove native/existing decay table for
	    // a)tau's 
	    // b) B+/- 
	    // and replace with external decayer
	    if ( abs(particle->GetPDGEncoding()) == 15 ||
	         abs(particle->GetPDGEncoding()) == 521 )
	    {
	       if ( particle->GetDecayTable() )
	       {
	          delete particle->GetDecayTable();
		  particle->SetDecayTable(nullptr);
	       }
	       decay->SetExtDecayer(extDecayer);
	    }
	    // now set external decayer to all particles 
	    // that don't yet have a decay table
	    if ( !particle->GetDecayTable() )
	    {
	       decay->SetExtDecayer(extDecayer);
	    }
	 }
      }              
   }

   return;
   
}
