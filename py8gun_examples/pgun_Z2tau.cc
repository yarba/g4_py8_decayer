
#include "Pythia8/Pythia.h"
using namespace Pythia8;

int main()
{

   // use default path to the xml/configs but do NOT print banner
   //
   Pythia pythia( "../share/Pythia8/xmldoc", false );
   ParticleData& pdt = pythia.particleData;

    pythia.readString("ProcessLevel:all = off"); // the trick!
    pythia.readString("ProcessLevel::resonanceDecays=on");
    
    pythia.readString("Init:showAllSettings=false");
    pythia.readString("Init:showChangedSettings=false");
    pythia.readString("Init:showAllParticleData=false");
    pythia.readString("Init::showChangedParticleData=false");

    pythia.readString("Next::numberShowProcess = 0" );
    pythia.readString("Next:numberShowEvent = 1");
            
    pythia.init();
    
    int partID = 23; // Z
    
    pythia.readString("23:onMode = off"); // turn off all Z decays
    pythia.readString("23:onIfAny = 15"); // turn ON Z->tautau
    
    pythia.readString("15:onMode = off" ); // turn off all tau decays
    pythia.readString("15:onIfAny = 11" ); // turn on tau->e-
    
    // this will print *ALL* settings (huge list !)
    //
    // pythia.settings.listAll();
        
    // function mSel(id) seems to select according to Breit-Wigner 
    // finction mass(id) doesn't seem to work/exist anymore...
    //
    double partMass = pdt.mSel(partID);
    
    double partE = 100.0; // make sure it's above Z-mass !!!
    double partP = sqrt( partE*partE - partMass*partMass );
    double partPz = partP;
    
    pythia.event.reset();
        
    //                                    px  py
    pythia.event.append( partID, 1, 0, 0, 0., 0., partPz, partE, partMass );
    
    pythia.next();
        
    std::cout << "Everything is done " << std::endl;
    
   return 0;

}
