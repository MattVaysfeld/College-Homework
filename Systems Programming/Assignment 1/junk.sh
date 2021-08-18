#!/bin/bash

######################################################################
# Author : Lukasz Asztemborski
# Author : Matthew Vaysfeld
# Date : February 9, 2021
# Pledge : I pledge my honor that I have abided by the Stevens Honor System.
# Description : junk.sh Junk files
######################################################################

readonly junk="/home/user/.junk"

enum=0
# [0 : no flags, 1 : h flag, 2 : l flag, 3 : p flag]

print_help() {
name=$(basename $0)
cat <<End-of-message
Usage: ${name} [-hlp] [list of files]
   -h: Display help.
   -l: List junked files.
   -p: Purge all files.
   [list of files] with no other arguments to junk those files.
End-of-message
}

while getopts ":hlp" o; do
	case "$o" in
	h) 
	if [ ! "$enum" -eq "0" ]; then
		echo "Error: Too many options enabled." >&2 
		print_help
		exit 1
	fi
	enum=1
	;;
	l) 
	if [ ! "$enum" -eq "0" ]; then 
		echo "Error: Too many options enabled." >&2 
		print_help
		exit 1
	fi
	enum=2
	;;
	p)
	if [ ! "$enum" -eq "0" ]; then 
		echo "Error: Too many options enabled." >&2 
		print_help
		exit 1
	fi
	enum=3
	;;
	?) echo "Error: Unknown option '-$OPTARG'." >&2
	   print_help
	   exit 1
	esac
done

shift "$(( OPTIND-1 ))"

declare -a filenames
index=0
files=0
for f in "$@"; do
	if [[ -d "$f" ]]; then 
		filenames[$index]="${f}"/
		(( ++index ))
	elif [ -f "$f" ]; then 
		filenames[$index]="$f"
		(( ++index ))
	else 
		if [[ "$enum" -eq "0" ]]; then echo "Warning: '${f}' not found." 
		fi
	fi
	(( ++files ))
done


if [[ ! "$files" -eq "0" && ! "$enum" -eq "0" ]]; then 
	echo "Error: Too many options enabled." >&2
	print_help
	exit 1
fi

# source : https://www.cyberciti.biz/faq/howto-check-if-a-directory-exists-in-a-bash-shellscript/
[ ! -d "$junk" ] && mkdir -p "$junk"
case "$enum" in
	"0")
	if [[ "$files" -eq "0" ]]; then
		print_help
		exit 0
	fi
	if [[ ! "$index" -eq "0" ]]; then
		for f in "${filenames[@]}"; do
			mv "$f" "$junk"
		done
	fi
	;;
	"1")
	print_help
	;;
	"2")
	ls -lAF "$junk"
	;;
	"3")
	rm -rf "$junk"/{*,.*} 2> /dev/null 
	;;
	?)
	exit 0
	;;
esac


exit 0









