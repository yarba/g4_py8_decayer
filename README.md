# g4_py8_decayer

This a simple example that shows how to use Pythia8 to decay Geant4 particles.

Check it out with ssh:
git clone git@github.com:yarba/g4_py8_decayer.git 

Alternative (no write/push):
git clone https://github.com/yarba/g4_py8_decayer.git

Below are the steps for building Pythia8, Geant4, and this example.
These instructions have been tested on FNAL Wilson cluster (head node tev.fnal.gov).
However, they're expected to work also on FNAL Geant4 VM (geant4vmgp01.fnal.gov).

* Setup compiler and cmake

source  /cvmfs/larsoft.opensciencegrid.org/products/setup
setup gcc v8_2_0
setup cmake v3_14_3

* Pythia8

cd path/to/your/pythia8/area
wget http://home.thep.lu.se/~torbjorn/pythia8/pythia8301.tgz
tar xzf pythia8301.tgz
cd pythia8301

export CXX=`which g++`
./configure --prefix=$PWD --cxx=$CXX
make

export PYTHIA8_DIR=$PWD
export PYTHIA8_INCLUDE_DIR=$PYTHIA8_DIR/include
export PYTHIA8_LIB_DIR=$PYTHIA8_DIR/lib

NOTE-1: In the py8gun_examples there're mini-examples of using Pythia8 as "particle gun with decay" 

NOTE: Pythia8 itself comes with a fairly rich collection of examples that exemplify many features, including even use of EvtGen (on top of native Pythia8) to decay b's and c's (main48)

* Geant4

cd /path/to/your/geant4/area
git clone ssh://git@gitlab.cern.ch:7999/geant4/geant4-dev.git geant4-10-06-ref-02
cd  geant4-10-06-ref-02
git checkout  geant4-10-06-ref-02
export G4INSTALL=$PWD

cd ..
mkdir geant4-10-06-ref-02-build
cd  geant4-10-06-ref-02-build
cmake -DCMAKE_INSTALL_PREFIX=$G4INSTALL \
-DCMAKE_CXX_COMPILER=g++ -DGEANT4_BUILD_CXXSTD=17 \
-DCMAKE_BUILD_TYPE=Debug \
$G4INSTALL
make -j8
make install

* Example g4_py8_decayer

cd /path/to/your/work/dir
git clone https://github.com/yarba/g4_py8_decayer.git
mkdir g4_py8_decayer-build
cd g4_py8_decayer-build
cmake -DGeant4_DIR=$G4INSTALL/lib64/Geant4-10.6.1  -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Debug ../g4_py8_decayer
make

DO NOT FORGET TO SET UP GEANT4 EXTERNAL DATASETS BEFORE RUNNING !!!

* A WORD OF WARNING

If you pass a single tau (no parents) to Pythia8, it may complain that modeling polarization isn't possible, e.g.
PYTHIA Warning in TauDecays::decay: unknown uncorrelated tau production, assuming unpolarized 



