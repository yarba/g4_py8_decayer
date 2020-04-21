#ifndef Py8DecayerPhysics_H
#define Py8DecayerPhysics_H

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

class G4Decay;

class Py8DecayerPhysics: public G4VPhysicsConstructor
{
  public:
  Py8DecayerPhysics(G4int verb=1);
    virtual ~Py8DecayerPhysics();

  protected:
    // methods
          // construct particle and physics
    virtual void ConstructParticle();
    virtual void ConstructProcess();

  private:

/*
    // DO WE NEED TO IMPLEMENT THESE ?
    /// Not implemented
    Py8DecayerPhysics(const Py8DecayerPhysics& right);
    /// Not implemented
    Py8DecayerPhysics& operator=(const Py8DecayerPhysics& right);
*/

};



#endif
