#!/bin/bash
DEFAULT_OUTFILE=ioproftrace.log

function help() {
	echo "Simple wrapper around strace call. Part of IOapps suite." >&2
	echo >&2
	echo "Save strace output to <out_file> (defaults to $DEFAULT_OUTFILE" >&2
	echo "and also adds .log to the name if not specified)" >&2
   echo "If -b is specified, ioreplay gets called to convert the trace to" >&2
   echo "binary form and .bin is appended." >&2
   echo "Either file can be opened by ioprofiler to visualize the io profile" >&2
   echo "If you want to know more, read this script and/or for more info on ioapps," >&2
	echo "see: http://code.google.com/p/ioapps/" >&2
	echo >&2
	echo "Usage:">&2
	echo "       $(basename $1) [-o out_file] [-b] program [args]">&2
	echo "or for tracing already running programs">&2
	echo "       $(basename $1) [-o out_file] [-b] -p pid">&2
}


while getopts ":bho:p:" opt; do
	case $opt in
		b)
			TOBIN=yes
			;;
		o)
			OUTFILE=$OPTARG
			;;
		p)
			PID=$OPTARG
			;;
		h)
			help $0
			exit 0
			;;
		\?)
			echo "Invalid option: -$OPTARG" >&2
			echo
			help $0
			exit 1
			;;
	esac
done
shift $((OPTIND-1))

OUTFILE=${OUTFILE:-$DEFAULT_OUTFILE}
OUTFILE=${OUTFILE%.log}.log
if [ -z $PID ]; then
	if [ $# -eq 0 ]; then
		echo "Not enough parameters."
		echo
		help $0
		exit 1
	fi
	strace -q -a1 -s0 -f -tttT -o${OUTFILE} -e trace=file,desc,process,socket "$@"
else
	strace -q -a1 -s0 -f -tttT -o${OUTFILE} -e trace=file,desc,process,socket -p $PID
fi

if [ -n "$TOBIN" ]; then
    BIN_OUTFILE=${OUTFILE%.log}.bin
    echo running ioreplay to convert ${OUTFILE} to ${BIN_OUTFILE} >&2
    ioreplay -c -f ${OUTFILE} -o ${BIN_OUTFILE}
fi
