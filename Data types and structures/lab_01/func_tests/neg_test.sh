#!/bin/bash

ok=0
err_rc=3

n=$1

../app.exe < ./neg_${n}_in.txt > out.txt

rc=$?

if [ ${rc} -ne 0 ]
then
	echo -e "${GREEN}NEGATIVE TEST ${n}: PASSED ${GREEN}"
	ex=${ok}
else
	echo -e "${RED}NEGATIVE TEST ${n}: FAILED ${RED}"
	ex=${err_rc}
fi

rm out.txt
exit ${ex}