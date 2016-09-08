for k in hw5115/scenario_$1/*.ini; 
do 
# for single CPU, feel free to adapt for multiple CPUs
	./ccnSim -u Cmdenv $k
done

 
