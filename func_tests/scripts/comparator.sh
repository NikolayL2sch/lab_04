#!/bin/bash

first_file=$1
second_file=$2

if cmp "$first_file" "$second_file" &>/dev/null; then
	exit 0
exit 1
fi
