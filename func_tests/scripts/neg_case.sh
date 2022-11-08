#!/bin/bash

args=""

if [ $# -gt 2 ]; then
	args=$(cat "${3}")
fi
if eval "../../app.exe ${args}< ${1} >./out.txt"; then
	exit 1
fi
if ! eval "bash ./comparator.sh ${2} ./out.txt"; then
	exit 1
fi
exit 0