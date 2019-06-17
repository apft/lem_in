#!/bin/sh

# recuperer le nombre de chemin : 1ere ligne
# creer le tableau de longeur des chemind
# pour le reste des fourmis, checker que la longeur de son chemin est coherente
# verifier qu'une fourmi ne se deplace qu'une fois par ligne
# verifier que le chemin est valide
# lecture ligne a ligne de la sortie du prgm ./lem-in

# Colors
RED='\x1b[1;31m'
GREEN='\x1b[1;32m'
YELLOW='\x1b[1;33m'
BLUE='\x1b[1;34m'
MAGENTA='\x1b[1;35m'
NC='\x1b[0m'

# Print error message
print_error(){
	printf "${RED}%s${NC}\n" "$1"
}

# Print message ok
print_ok(){
	printf "${GREEN}%s${NC}\n" "$1"
}

# Print warning message
print_warn(){
	printf "${YELLOW}%s${NC}\n" "$1"
}

function print_usage()
{
	echo "usage:"
	echo "\t$0 exec map"
	exit 1
}

function rm_tmp_files()
{
	for file in $@
	do
		[ -f "$file" ] && rm $file
	done
}

function extract_command()
{
	local room=$1

	grep -A 1 "##$room" $MAP | tail -n 1 | cut -d ' ' -f 1
}

function check_diff_output_map()
{
	local output_map
	local line_sep
	local diff

	output_map=".out_map"
	line_sep=`grep -nh "^$" $OUTPUT | cut -d ':' -f 1`
	((line_sep--))
	head -n ${line_sep} $OUTPUT > ${output_map}
	diff=$(diff $MAP ${output_map})
	if [ "$diff" ]; then
		print_error "Output map is different from input"
		echo "diff -y input_map your_output_map"
		diff -y $MAP ${output_map}
		rm_tmp_files $OUTPUT $output_map
		exit 1
	else
		print_ok "Output map is correct"
	fi
}

function print_paths()
{
	for i in `seq ${NB_PATH}`
	do
		printf "%d: " $i
		grep -E -o "L$i-[A-Z][a-z_]{2}[0-9]" $OUTPUT | cut -d '-' -f 2 | tr '\n' ' '
		printf "\n"
	done
}

function length()
{
	local	index="$1"
	grep "L${index}-" $OUTPUT | wc -l | bc
}

function run_main()
{
	[ $# -ne 2 ] && print_usage

	EXEC="$1"
	MAP="$2"

	OUTPUT=".out_checker"
	$EXEC < $MAP > $OUTPUT

	NB_ANTS=`head -n 1 $MAP`
	NB_PATH=`grep "^L" $OUTPUT | head -n 1 | grep -o "L" | wc -l | bc`

	check_diff_output_map

	ROOM_START=`extract_command "start"`
	ROOM_END=`extract_command "end"`
	echo "start: ${ROOM_START}"
	echo "end: ${ROOM_END}"

	echo "ants: ${NB_ANTS}"
	echo "path: ${NB_PATH}"

	print_paths

	for i in `seq ${NB_PATH}`
	do
		PATH_LENGTH[$i]=`length $i`
	done

	echo "path length: ${PATH_LENGTH[@]}"

	for i in `seq ${NB_ANTS}`
	do
		length=`length $i`
		echo "${PATH_LENGTH[@]}" | grep "$length" > /dev/null
		if [ $? -ne 0 ]; then
			echo "error: ant $i goes through a path length of $length"
			exit
		fi
	done

	rm_tmp_files $OUTPUT
}

run_main $@
