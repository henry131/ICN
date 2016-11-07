
README for hw5115 Individual Project for Imperial College MSc Computing Science, 2016
--------------------------------------------------------------------------------------------------------
Title: Future Internet: Information Centric Networks
Author: Henry Williams
Supervisor: Professor Kin K. Leung
Email: henryhamiltonwilliams@gmail.com
Date Created: 12th August 2016
--------------------------------------------------------------------------------------------------------

PLEASE READ INSTALLATION SECTION IN ENTIRETY BEFORE PROCEEDING

########################################################################################################

1. Set-up

Download the latest version of ccnSim into a directory to be subsequently termed $CCNSIM_DIR

Unzip the hw5115 archive into $CCNSIM_DIR (v.important it is in the initial directory)

We have to install ccnSim, please follow the ccnSim instruction on INSTALL.txt using the latest version (or use v0.4-Alpha if there are subsequent compatibility issues).

Please note that we must install Omnet++ (dependancy of ccnSim).

N.B. DONT install Omnet++ version >= 5.0:

v5.0 introduced some non-backward-compatible changes with ccnSim 
To succesfully install ccnSim with omnet++ 5.0, you need to use the slightly modified
ctopology.cc and ctopology.h, avaliable from the ccnSim website
and you need to copy ctopology.h to $OMNET_DIR/include/omnetpp
(instead of the folder commonly used for v4.x (below))

-->!! To negate this complication, we installed Omnet++ version 4.6 - recommend proceed the same.

[No lost functionality relating to ccnSim (other network tools)]

PLEASE REFER TO THE CCNSIM MANUAL v3.0 (AVAILABLE ON ccnSim WEBSITE) IF PROBLEMS ARISE

ccnSim website: http://perso.telecom-paristech.fr/~drossi/index.php?n=Software.CcnSim

###########################################################################################################

2. Installation of hw5115 content

In order to patch the relevant files required to run hw5115 simulations

Simply cd into the patch directory of the archive and run the patch_files.sh
	
	cd $CCNSIM_DIR/archive/patch/
	./patch_files.sh


That will copy the requisite files to the correct locations 
provided all the above steps were correctedly followed

##########################################################################################################

2. Creating ternary tree topologies


To create the teranry trees with probabilistic linking for scenarios A and D
need to compile and run make_ternary_trees.cpp:

	cd $CCNSIM_DIR/archive/ternary_tree/
	make
	./nets 4

The 200 .ned files required for ternary tree simulations have now been created in $CCNSIM_DIR/networks/ 

Note to create larger tress sizes (up to 8 levels) simply run the program
with the second command line input stating the desired number of levels, e.g. for 5 levels

	./nets 5

##########################################################################################################

3. Running Simulations

Once the ternary tree is in place, all of the scenarios can be run.

To do so, mv the run.sh script in the archive into the $CCNSIM_DIR then cd into that directory

	mv run.sh ../
	cd ..
	
then you can run any scenario you wish from the $CCNSIM_DIR
by calling the run script followed the desired scenario letter:
e.g. for scenario A

	./run.sh A
	
##########################################################################################################

ChangeLog (integrated --> unrelated to simulation files in archive)

- Added Filter First Caching and it's variants - integrated using patch files
- Improved and cleaned debugging (improved SEVERE_DEBUG output)
	(add #STREAM_DEBUG in $CCNSIM_DIR/include/ccnsim.h to enable packet by packet debugging)
- Fixed incorrect pre-stabilization for LRU caching
- Resolved memory leaks where possible (mosty resolved in patch files):
	to avoid memory leak using nrr routing, call the MonolithicPathStrategy::finish() function
	from the nrr::finish() function

##########################################################################################################

#Please see below ccnSim readme (not relevant to hw5115 project)
-----------------------------------------------------------------------------------------------------------


                  / _____)_	      
  ____ ____ ____ ( (____ (_)_ __ ___  
 / ___) ___)  _ \ \____ \| | '_ ` _ \ 
( (__( (___| | | |_____) | | | | | | |
 \____)____)_| |_(______/|_|_| |_| |_|


Thank you for joining the ccnSim community!  This is ccnSim v0.4-Alpha.


To install ccnSim, please follow the instructions on INSTALL.txt  After you
succesfully installed ccnSim, run your first simulation with:

	./ccnSim -u Cmdenv -f ED_TTL-omnetpp.ini r 0

The default .ini file is ED_TTL-omnetpp.ini (in which each parameter is documented).
It simulates a simple topology and scenario for the sake of illustration.
Results are produced inside the "results/" folder in the form of .sca files.
For a set of more representative scripts and scenarios please refer to the
ccnSim website. 

This version of ccnSim provides, also, an example script: 

- runsim_script_ED_TTL.sh

which sets the parameters of the .ini file according to the ones inserted from the command line,
and automatically collects metrics of interest. After the simulation ends, results 
are produced under directories "logs/", "results/", and "infoSim/". In particular,
a summary of all the collected parameters is written in the produced file inside "infoSim/ALL_MEASURES_*"
## Remark: please see the note about the Memory measurement inside the file "runsim_script_ED_TTL.sh".

Furthermore, a set of other scenarios, with the correspondent command line parameters,
is provided inside the file:

- run_ED_TTL_scanarios.sh

Note that TTL-based scenarios require files with Tc values to be present inside the folder "Tc_Values";
these files can be produced either by executing the ED-sim version of the correspondent scenario
through the runsim_script_ED_TTL.sh (in this case they will be automatically added to the folder),
or added manually. The rationale is that the first line contains the Tc of Node 0, the second line
the Tc of Node 1, and so on.

For more details about the output files, please refer to the ccnSim manual.
