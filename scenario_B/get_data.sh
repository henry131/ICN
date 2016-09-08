#!/bin/sh
hits=ih.DATA
hops=hc.DATA
alpha="0.5 0.6 0.7 0.8 0.9 1"
caches="lce fix0.1 fix0.05 fix0.01 fix0.005 fix0.001 prob_cache lcd ffc ffc0.25 ffc0.2 ffc0.1 ffc0.05 ffc0.01 tfc wfc0.25 wfc0.1 wfc0.05 wfc0.01 wfc0.005 wfc0.001"
:>$hops
echo "F D 0.5 0.6 0.7 0.8 0.9 1" > $hops
for f in nrr;do
	for d in $caches; do
	echo -n "$f $d "
		for a in $alpha; do
		grep -P "statistics\s+hdistance" results/bus/F-$f/D-$d/R-lru/alpha-$a/ccn-id0.sca | awk '{ h=$4 } END {printf h}'
		echo -n " "
		done
	echo ""
	done
done >> $hops

:> $hits
echo "F D 0.5 0.6 0.7 0.8 0.9 1" > $hits
for f in nrr;do
	for d in $caches; do
	echo -n "$f $d "
		for a in $alpha; do
		grep -P "statistics\s+inner_hit" results/bus/F-$f/D-$d/R-lru/alpha-$a/ccn-id0.sca | awk '{ h=$4 } END {printf h}'
		echo -n " "
		done
	echo ""
	done
done >> $hits




