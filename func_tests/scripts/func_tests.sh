#!/bin/bash

touch out.txt

neg=$(find ../data/ -name "neg_[0-9][0-9]*_in.txt" | wc -l)
pos=$(find ../data/ -name "pos_[0-9][0-9]*_in.txt" | wc -l)


failed=0
for ((i=1; i <= pos; i++)); do
	if [ -f "../data/pos_0${i}_args.txt" ]; then
		bash pos_case.sh "../../func_tests/data/pos_0${i}_in.txt" "../../func_tests/data/pos_0${i}_out.txt" "../../func_tests/data/pos_0${i}_args.txt"
	else
		if [ $i -ge 10 ]; then
			bash pos_case.sh "../data/pos_${i}_in.txt" "../data/pos_${i}_out.txt"
		else
			bash pos_case.sh "../data/pos_0${i}_in.txt" "../data/pos_0${i}_out.txt"
		fi
	fi
	if [ "$?" -eq 0 ]; then
		echo -e "Pos_test${i} SUCCCESS"
	else
		echo -e "Pos_test${i} FAILURE"
		failed=$((failed+1))
	fi
done

for ((i=1; i <= neg; i++)); do
	if [ -f "../data/neg_0${i}_args.txt" ]; then
		bash neg_case.sh "../../func_tests/data/neg_0${i}_in.txt" "../../func_tests/data/neg_0${i}_out.txt" "../../func_tests/data/neg_0${i}_args.txt"
	else
		if [ $i -ge 10 ]; then
			bash neg_case.sh "../data/neg_${i}_in.txt" "../data/neg_${i}_out.txt"
		else
			bash neg_case.sh "../data/neg_0${i}_in.txt" "../data/neg_0${i}_out.txt"
		fi
	fi
	if [ "$?" -eq 0 ]; then
		echo -e "Neg_test${i} SUCCCESS"
	else
		echo -e "Neg_test${i} FAILURE"
		failed=$((failed+1))
	fi
done

echo -e "FAILED: $failed"
rm -rf ./out.txt