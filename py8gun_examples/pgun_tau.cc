
#include "Pythia8/Pythia.h"

using namespace Pythia8;

int main()
{

   // Generator; shorthand for particleData
   Pythia pythia;
   ParticleData& pdt = pythia.particleData;

    pythia.readString("ProcessLevel:all = off"); // the trick!
    pythia.readString("ProcessLevel::resonanceDecays=on");

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
    
    pythia.next();
    
    std::cout << "Everything is done " << std::endl;
    
   return 0;

}
