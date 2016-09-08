# Postprocessing for illustration purposes
levels=$1
cache="spr-Edge nrr-Edge spr-lce spr-lcd spr-fix0.1 spr-fix0.01 nrr-lce nrr-lcd nrr-fix0.1 nrr-fix0.01"
probs="00 01 02 03 04 05 06 07 08 09 10"
for k in $cache;  
do   
    :> $k.DATA 
    echo -e "p Hops Hit_Ratio" > $k.DATA
    for u in $probs; do
       uu=$u
       echo -en "$u "        
       grep -P "statistics\s+hdistance" ./l$levels/$k/u$u/ccn-id*.sca | awk -v u=$uu '{ a+=$4 } END { printf a/NR }'
       echo -en " "   
       grep -P "statistics\s+inner_hit" ./l$levels/$k/u$u/ccn-id*.sca | awk -v u=$uu '{ a+=$4 } END { print a/NR }'
    done >> $k.DATA
    mv $k.DATA ./l$levels/results/
done

 
