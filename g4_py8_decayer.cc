//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file eventgenerator/pythia/decayer6/pythia6_decayer.cc
/// \brief Main program of the pythia6Decayer example

#include "Py8DecayerPhysics.hh"

#include "DetConstruction.hh"
#include "SinglePartGun.hh"
// ---> if needs be ---> #include "Py8Z2TauGun.hh"

#include "G4RunManager.hh"
#include "FTFP_BERT.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4GeometryManager.hh"

// int main(int argc,char** argv)
int main()
{

   // Choose the Random engine
   //
   G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
   // Construct the default run manager
   //
   G4RunManager * runManager = new G4RunManager();

   // Set mandatory initialization classes
   //
   // Geometry
   //
   runManager->SetUserInitialization(new DetConstruction);
   runManager->GeometryHasBeenModified();
   //
   // Physics
   //
   G4VModularPhysicsList* physicsList = new FTFP_BERT();
   physicsList->RegisterPhysics(new Py8DecayerPhysics());
   runManager->SetUserInitialization(physicsList);
   //
   // Set user action classes, e.g. prim.generator (tau- gun), etc.
   //
   //                                          prt_name prt_mom
   runManager->SetUserAction( new SinglePartGun( "tau-", 25.0 ) );
//
// ---> if needs be --->     runManager->SetUserAction( new Py8Z2TauGun() );

   // Run initialization
   //
   runManager->InitializeGeometry();
   runManager->InitializePhysics();      
   runManager->Initialize();
   //
   runManager->ConfirmBeamOnCondition();
   runManager->RunInitialization(); // this is part of BeamOn 
                                    // and needs be done (at least) to set GeomClosed status 

   // Run event loop
   // 
   for (G4int iev=0; iev<5; ++iev) 
   {
      runManager->ProcessOneEvent( iev );
   }

   // It speaks for itself ^_^
   //
   runManager->RunTermination();

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !
  delete runManager;

  return 0;

}
