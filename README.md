# g4_py8_decayer

This a simple example that shows how to use Pythia8 to decay Geant4 particles.

Check it out with ssh:
git clone git@github.com:yarba/g4_py8_decayer.git 

Alternative (no write/push):
git clone https://github.com/yarba/g4_py8_decayer.git

Below are the steps for building Pythia8, Geant4, and this example.
These instructions have been tested on FNAL WC-IC cluster (head node wc.fnal.gov).
They're expected to work also on FNAL Geant4 VM (geant4vmgp01.fnal.gov).

In general, only setting the compiler and cmake are kind of /"FNAL-centric/"; 
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

export CXX=/`which g++/`

./configure --prefix=$PWD --cxx=$CXX

make

export PYTHIA8_DIR=$PWD

export PYTHIA8_INCLUDE_DIR=$PYTHIA8_DIR/include

export PYTHIA8_LIB_DIR=$PYTHIA8_DIR/lib

NOTE-1: Pythia8 itself comes with a fairly rich collection of examples that exemplify many features, including e.g. use of EvtGen (on top of native Pythia8) to decay b's and c's (main48)

NOTE-2: In the g4_py8_decayer/py8gun_examples which is described later in this document there're mini-examples of using Pythia8 (alone) as "particle gun with decay"; however, the Makefile to them is not very sophisticated and may need a cleanup. 


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

By default it'll run 5 single tau events using Pythia8 to decays them (through the use 
of components Py8Decayer and Py8DecayerPhysics; Geant4 native tau decay modes are DISABLED).  
It should print some Pythia8 event information, including on decays. 
Please bear in mind that the decay of pi0's by Pythia8 is disabled as the idea is to hand 
the pi0's back to Geant4 and make Geant4 decay them.

Alternatively Pythi8-based Z -> tau tau "particle gun" is also availble (Py8Z2TauGun code).

DO NOT FORGET TO SET UP GEANT4 EXTERNAL DATASETS BEFORE RUNNING !!!

* A WORD OF WARNING

If you pass a single tau (no parents) to Pythia8, it may complain that modeling polarization isn't possible, e.g.

PYTHIA Warning in TauDecays::decay: unknown uncorrelated tau production, assuming unpolarized 



