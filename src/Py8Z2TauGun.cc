
#include "Py8Z2TauGun.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
// ---> comes w/G4Event.hh ---> #include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

using namespace Pythia8;

Py8Z2TauGun::Py8Z2TauGun()
  : G4VUserPrimaryGeneratorAction(),
    fMasterGen(nullptr)
{

   // use default path to the xml/configs but do NOT print banner
   //
   fMasterGen = new Pythia( "../share/Pythia8/xmldoc", false );

   fMasterGen->readString("ProcessLevel:all = off"); // the trick to make it work 
                                                     // as a "decayer"
   fMasterGen->readString("ProcessLevel::resonanceDecays=on");
    
   // shut down Py8 verbosity
   //
   fMasterGen->readString("Init:showAllSettings=false");
   fMasterGen->readString("Init:showChangedSettings=false");
   fMasterGen->readString("Init:showAllParticleData=false");
   fMasterGen->readString("Init::showChangedParticleData=false");
   //
   fMasterGen->readString("Next::numberShowProcess = 0" );
   fMasterGen->readString("Next:numberShowEvent = 0");
            
   fMasterGen->init();
   
   fPartID = 23; // Z
   fPartP  = 100.; // GeV/c
   fVtx    = G4LorentzVector( 0., 0., 0., 0. );
   
   fMasterGen->readString("23:onMOde = off"); // turn off all Z decays
   fMasterGen->readString("23:onIfAny = 15"); // turn ON Z->tautau
   
   fMasterGen->readString("15:onMode = off"); // turn off tau decays
                                              // as we want Geant4 to handle them ! 
}

Py8Z2TauGun::~Py8Z2TauGun()
{

   if ( fMasterGen ) 
   {
      delete fMasterGen;
      fMasterGen = nullptr;
   }
   
}

void Py8Z2TauGun::GeneratePrimaries( G4Event* evt )
{

   double phi = -1. * CLHEP::pi + CLHEP::twopi * G4UniformRand();
   double theta = CLHEP::pi/4. + CLHEP::halfpi * G4UniformRand();
   
   double x = sin(theta) * cos(phi);
   double y = sin(theta) * sin(phi);
   double z = cos(theta);
   
   double partMass = fMasterGen->particleData.mSel(fPartID);
   
   double partE = sqrt( fPartP*fPartP + partMass*partMass );
   
   fMasterGen->event.reset();
   
   fMasterGen->event.append( fPartID, 1, 0, 0, 
                             fPartP*x, fPartP*y, fPartP*z, partE, partMass ); 
   
   fMasterGen->next();
   
   // now pick up Z-decay products and make them into G4Event
   // NOTE: there doesn't seem to a definition for Z in G4
   
   G4ParticleTable* pdt = G4ParticleTable::GetParticleTable();
   int current_mo = -1;
   int previous_mo = -1;
   for ( int i=1; i<fMasterGen->event.size(); ++i ) // not starting from i=0
                                                    // because 0th is "system" 
   {
      int dau1 = fMasterGen->event[i].daughter1();
      int dau2 = fMasterGen->event[i].daughter2();
      if ( !( dau1  == 0 && dau2 == 0 ) ) continue;
      if ( fMasterGen->event[i].mother2() != 0 ) continue; // something strange, not a decay...
      
      current_mo = fMasterGen->event[i].mother1();
      
      int pdecID    = fMasterGen->event[i].id();
      double pdecpx = fMasterGen->event[i].px() * CLHEP::GeV;
      double pdecpy = fMasterGen->event[i].py() * CLHEP::GeV;
      double pdecpz = fMasterGen->event[i].pz() * CLHEP::GeV;
      double pdece  = fMasterGen->event[i].e()  * CLHEP::GeV;
      double pdecp  = sqrt( pdecpx*pdecpx + pdecpy*pdecpy + pdecpz*pdecpz );
      
      double vx = fMasterGen->event[i].xProd() / CLHEP::mm;
      double vy = fMasterGen->event[i].yProd() / CLHEP::mm;
      double vz = fMasterGen->event[i].zProd() / CLHEP::mm;
      double t  = fMasterGen->event[i].tProd() / CLHEP::c_light;
      
      // NOTE: Py8 particle record has provisions for pol() (polarization)
      //       but the 8.3.0.1 manual says it's not used except for W/Z
      
      if ( current_mo != previous_mo )
      {
         // create new vertex
	 evt->AddPrimaryVertex( new G4PrimaryVertex(vx,vy,vz,t) );
	 //
	 previous_mo = current_mo;
      }
      
      // add tracks to the most recent vertex
      //
      int ivtx = evt->GetNumberOfPrimaryVertex() - 1;
      G4PrimaryVertex* vtx = evt->GetPrimaryVertex(ivtx);
      G4ParticleDefinition* pd = pdt->FindParticle( pdecID );
      vtx->SetPrimary( new G4PrimaryParticle(pd) );
      int iprt = vtx->GetNumberOfParticle() - 1;
      G4PrimaryParticle* prt = vtx->GetPrimary(iprt);
      prt->SetMass( pd->GetPDGMass() );
      prt->SetKineticEnergy( pdece - pd->GetPDGMass() );
      prt->SetMomentumDirection( G4ThreeVector( pdecpx/pdecp, pdecpy/pdecp, pdecpz/pdecp ) );
      prt->SetCharge( pd->GetPDGCharge() );
      // set polarization to (0,0,0)
      prt->SetPolarization( 0., 0., 0. );
         
   }
   
   return;

}
