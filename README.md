# g4_py8_decayer

This a simple example that shows how to use Pythia8 to decay Geant4 particles.

It is done through 
a) replacing Geant4 native decay tables for selected resonances by Pythia8-based features
b) supplying Pythia8-based decay features to all resonances where Geant4 native decay table
   is not implemented by default 

Check it out with ssh:
git clone git@github.com:yarba/g4_py8_decayer.git 

Alternative (no write/push):
git clone https://github.com/yarba/g4_py8_decayer.git

Below are the steps for building Pythia8, Geant4, and this example.
These instructions have been tested on FNAL WC-IC cluster (head node wc.fnal.gov).
They're expected to work also on FNAL Geant4 VM (geant4vmgp01.fnal.gov).

In general, only setting the compiler and cmake are kind of "FNAL-centric"; 
apart from that the described procedure should work on other platforms, e.g. lxplus,cern.sh, etc.

* Setup compiler and cmake

source  /cvmfs/larsoft.opensciencegrid.org/products/setup

setup gcc v8_2_0

setup cmake v3_17_3

* Pythia8

cd path/to/your/pythia8/area

wget http://home.thep.lu.se/~torbjorn/pythia8/pythia8305.tgz

tar xzf pythia8305.tgz

cd pythia8305

export CXX=\`which g++\`

./configure --prefix=$PWD --cxx=$CXX

make

export PYTHIA8=$PWD

NOTE-1: By default, Pythia8 (as of 8.3.0.5) builds with C++11 standards. If one wants to turn 
to e.g. C++17 standard, one needs to override flags via --cxx-common argument to configure script. 


NOTE-2: Pythia8 itself comes with a fairly rich collection of examples that exemplify many features, 
including e.g. use of EvtGen (on top of native Pythia8) to decay b's and c's (main48)

NOTE-3: In the g4_py8_decayer/py8gun_examples which is described later in this document there're 
mini-examples of using Pythia8 (alone) as "particle gun with decay"; however, the Makefile to them 
is not very sophisticated and may need a cleanup. 


* Geant4

cd /path/to/your/geant4/area

git clone ssh://git@gitlab.cern.ch:7999/geant4/geant4-dev.git geant4-10-07-ref-04

cd  geant4-10-07-ref-04

git checkout  geant4-10-07-ref-04

export G4INSTALL=$PWD

cd ..

mkdir geant4-10-07-ref-04-build

cd  geant4-10-07-ref-04-build

NOTE: Here Geant4 is build as Debug but it's just an example...

cmake -DCMAKE_INSTALL_PREFIX=$G4INSTALL -DCMAKE_CXX_COMPILER=g++ -DGEANT4_BUILD_CXXSTD=17 -DCMAKE_BUILD_TYPE=Debug $G4INSTALL

make -j8

make install

* Example g4_py8_decayer

cd /path/to/your/work/dir

git clone https://github.com/yarba/g4_py8_decayer.git

mkdir g4_py8_decayer-build

cd g4_py8_decayer-build

cmake -DCMAKE_PREFIX_PATH=$G4INSTALL -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Debug ../g4_py8_decayer

make

* Run it is follows (no input/config macro, everything is hardcoded at this point):

./g4_py8_decayer

By default it'll run 5 single tau- events using Pythia8 to decays them.
Alternatively tau+, B+, or B- can be specified as a primary particle. 

The job is done through the use of components Py8Decayer and Py8DecayerPhysics; 
Geant4 native tau+/- or B+/- decay modes are DISABLED and replaced by Pythia-8 based component.  
It should print some Pythia8 event information, including on decays. 

Please bear in mind that the decay of pi0's by Pythia8 is disabled as the idea is to hand 
the pi0's back to Geant4 and make Geant4 decay them.

Another alternative is Pythi8-based Z -> tau tau "particle gun" is also availble (Py8Z2TauGun code).

DO NOT FORGET TO SET UP GEANT4 EXTERNAL DATASETS BEFORE RUNNING !!!

* A WORD OF WARNING

If you pass a single tau (no parents) to Pythia8, it may complain that modeling polarization 
isn't possible, e.g.
PYTHIA Warning in TauDecays::decay: unknown uncorrelated tau production, assuming unpolarized

One can explicitly (re)set tau polarization from it's default=9.0, e.g. to -1. for tau-;
in such case TauDecays::decay will eventually treat it as "external tau" even if TauDecay::mode 
will remain at 1 (D) rather than being formally reset to 5 (external tau).

Resetting TauDecays::mode to 5 and/or changing TauDecays::externalMode from its default=1 
to e.g. 0 will NOT eliminate the warning in question unless polarization is explicitly set.

Bear in mind that a valid polarization should be -1, 0., or 1; a number like 0.999 will NOT
be treated sensibly, so if one calculates, one better rounds it up to the nearest integer.


