
#include "Py8DecayerPhysics.hh"
#include "Py8Decayer.hh"

#include <G4ParticleDefinition.hh>
#include <G4ProcessManager.hh>
#include <G4Decay.hh>
#include <G4DecayTable.hh>

Py8DecayerPhysics::Py8DecayerPhysics(const G4String& name)
  : G4VPhysicsConstructor(name)
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
	    // set ext decayer to all particles that don't have a decay table
	    if ( !particle->GetDecayTable() )
	    {
	       decay->SetExtDecayer(extDecayer);
	    }
	    // now for tau's remove the existing decay table and set ext decayer
	    if ( abs(particle->GetPDGEncoding()) == 15 )
	    {
	       if ( particle->GetDecayTable() )
	       {
	          delete particle->GetDecayTable();
		  particle->SetDecayTable(nullptr);
	       }
	       decay->SetExtDecayer(extDecayer);
	    }
	 }
      }              
   }

   return;
   
}
