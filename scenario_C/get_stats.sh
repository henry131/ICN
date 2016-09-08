# Postprocessing for illustration purposes
nets="dtelecom geant level3 tiger abilene"
#dtelecom geant level3 tiger abilene
routing="nrr" #spr nrr
caching="never lce fix0.05 fix0.005 lcd ffc tfc ffc0.2 ffc0.1 ffc0.05"
 
for k in $nets; do
	:> $k.DATA
	echo "F D hops ih ch" > $k.DATA
	for f in $routing; do
		for d in $caching; do
			rr=$d
			echo -n "$f $d "
			grep -P "statistics\s+hdistance" results/$k/F-$f/D-$d/R-lru/alpha-0.9/ccn-id*.sca | awk -v d=$rr '{ a+=$4 } END { printf a/NR }'
			echo -n " "
			grep -P "statistics\s+inner_hit" results/$k/F-$f/D-$d/R-lru/alpha-0.9/ccn-id*.sca | awk -v d=$rr '{ a+=$4 } END { printf a/NR }'	
			echo -n " "
			grep -P "statistics\s+p_hit" results/$k/F-$f/D-$d/R-lru/alpha-0.9/ccn-id*.sca | awk -v d=$rr '{ a+=$4 } END { printf a/NR }'
			echo ""	
    		done
	done >> $k.DATA
    mv $k.DATA data/
done

 
