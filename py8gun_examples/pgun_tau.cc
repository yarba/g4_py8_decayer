
#include "Pythia8/Pythia.h"

using namespace Pythia8;

int main()
{

   // Generator; shorthand for particleData
   Pythia pythia;
   ParticleData& pdt = pythia.particleData;

    pythia.readString("ProcessLevel:all = off"); // the trick!
    pythia.readString("ProcessLevel:resonanceDecays=on");
    
    // this will NOT do anything unless polarization is set
    // (see later in the code)
    //
    // pythia.readString("TauDecays:mode=5");    
    // pythia.readString("TauDecays:externalMode=0");

    pythia.init();
    
    int partID = 15; // tau
    
    // function mSel(id) - selects according to Breit-Wigner 
    // NOTE: method mass(...) doesn't seem to exist anymore...
    double partMass = pdt.mSel(partID);
    
    double partE = 20.0;
    double partP = sqrt( partE*partE - partMass*partMass );
    double partPz = partP;
    
    pythia.event.reset();
        
    //                                    px  py
    pythia.event.append( partID, 1, 0, 0, 0., 0., partPz, partE, partMass );
    
    // (re-)set polarization from its default=9.0 (which means hell knows what...)
    //
    // NOTE: in such case TauDecays::decay will eventually treat it
    //       as "external tau" even if TauDecay::mode will remain at 1 (D)
    //       rather than being formally reset to 5 (ext.tau)
    //
    pythia.event.back().pol(-1.);

    pythia.next();
    
    std::cout << "Everything is done " << std::endl;
    
   return 0;

}
