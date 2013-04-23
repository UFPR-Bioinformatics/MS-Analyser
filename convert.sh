#!/bin/bash

IFS=$'\n'

LEFT=();
RIGHT=();
DIST=();

while IFS="	" read -r f0 f1 f2 f3
do
	if [ $f0 -eq $f0 2> /dev/null ];
	then
		LEFT=( "${LEFT[@]}" "$f1" )
		RIGHT=( "${RIGHT[@]}" "$f2" )
		DIST=( "${DIST[@]}" "$f3" )
	fi
done <"${HOME}/MS-Analyser/nodes.txt"

LEAVES=($(cat ~/MS-Analyser/leaf.txt))

CUTOFF=0.4
GROUP=()
NODES=()

#echo ${NODES[@]}
#echo ${GROUP[@]}

for i in "${!LEFT[@]}"
do
#	if [ $(echo "${DIST[$i]} < ${CUTOFF}" | bc ) -eq 1 ];
#	then
#		if [ "${LEFT[$i]}" -lt 0 -o "${RIGHT[$i]}" -lt 0 ] 2>&-;
#		then
#			for n in "${!GROUP[@]}"
#			do
#				echo ${GROUP[$n][@]}
#			done
#		else
#			G=(5)
#			G=( ${G[@]} "$( echo "-$i - 1" | bc )" )
#			GROUP=( ${GROUP[@]} "$G" )
#		fi
#	fi

	if [ ${LEFT[$i]} -ge 0 2> /dev/null ];
	then
		LEFT[$i]=${LEAVES[${LEFT[$i]}]}
	fi

	if [ ${RIGHT[$i]} -ge 0 2> /dev/null ];
	then
		RIGHT[$i]=${LEAVES[${RIGHT[$i]}]}
	fi

	dst=$( echo "scale=6;${DIST[$i]} / 2" | bc )

	NODES[$i]="(${LEFT[$i]}:$dst,${RIGHT[$i]}:$dst)"
done

#echo ${GROUP[@]}

for i in "${!NODES[@]}"
do
	if [ ${LEFT[$i]} -lt 0 2> /dev/null ];
	then
		NODES[$i]="${NODES[ $i ]/(${LEFT[$i]}:/(${NODES[$(echo "${LEFT[$i]} * -1 - 1" | bc)]}:}"
	fi

	if [ ${RIGHT[$i]} -lt 0 2> /dev/null ];
	then
		NODES[$i]="${NODES[ $i ]/,${RIGHT[$i]}:/,${NODES[$(echo "${RIGHT[$i]} * -1 - 1" | bc)]}:}"
	fi
done


echo "${NODES[$i]};" > ~/MS-Analyser/newick.txt

#rm ${HOME}/MS-Analyser/nodes.txt ${HOME}/MS-Analyser/leaf.txt
