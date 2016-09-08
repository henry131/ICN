# Postprocessing for illustration purposes
cache="ffc ffc0.3 ffc0.25 ffc0.2 tfc wfc0.01 wfc0.001 wfc0.0001"

for k in $cache;  
do   
    :> $k.DATA 
    echo -e "p Hops Hit_Ratio" > $k.DATA
    for u in 00 01 02 03 04 05 06 07 08 09 10; do
       uu=$u
       echo -en "$u "        
       grep -P "statistics\s+hdistance" ./nrr-$k/u$u/ccn-id*.sca | awk -v u=$uu '{ a+=$4 } END { printf a/NR }'
       echo -en " "   
       grep -P "statistics\s+inner_hit" ./nrr-$k/u$u/ccn-id*.sca | awk -v u=$uu '{ a+=$4 } END { printf a/NR }'
	echo ""
    done >> $k.DATA
    mv $k.DATA results/
done

 
