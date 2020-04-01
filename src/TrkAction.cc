
#include "TrkAction.hh"

#include "globals.hh"
// #include "G4Step.hh"
#include "G4Track.hh"
#include "G4TrackingManager.hh"
// #include "G4EventManager.hh"

void TrkAction::PreUserTrackingAction( const G4Track* trk )
{

/*
   G4TrackingManager* trkMgr = 
      G4EventManager::GetEventManager()->GetTrackingManager();
*/

   G4cout << " trk ID: " << trk->GetTrackID() << G4endl;
   G4cout << " trk particle: " <<  trk->GetDefinition()->GetParticleName() << G4endl;
   G4cout << " trk kinetic energy: " << trk->GetKineticEnergy() << G4endl;
   G4cout << " trk parent: " << trk->GetParentID() << G4endl;
   G4cout << " phys.volume: " << trk->GetVolume()->GetName() << G4endl;
   G4cout << " log.volume at vertex: " << trk->GetLogicalVolumeAtVertex()->GetName() << G4endl;
   G4cout << " material: " << trk->GetVolume()->GetLogicalVolume()->GetMaterial()->GetName() << G4endl;
   
   if ( trk->GetParentID() == 1 && trk->GetDefinition()->GetPDGEncoding() == 111 )
   {
      G4cout << " particle: " << trk->GetDefinition()->GetParticleName() << G4endl;
      G4cout << " trk ID: " << trk->GetTrackID() << G4endl;
      G4cout << " creator process: " << trk->GetCreatorProcess()->GetProcessName() << G4endl;
      G4cout << " trk parent: " << trk->GetParentID() << G4endl;
   }
   
   return;

}

void TrkAction::PostUserTrackingAction( const G4Track* )
{

   return;

}
