#!/bin/bash

ok=0
err_cmp=2
err_rc=3

n=$1
file_in=./pos_${n}_in.txt
file_out=./pos_${n}_out.txt
out=./out.txt

../app.exe < ./pos_${n}_in.txt > out.txt

rc=$?

if [ ${rc} -ne 0 ]
then 
  echo -e "${RED}POSITIVE TEST ${n}: FAILED with rc == ${rc} ${RED}"
  exit ${err_rc}
fi

if diff "$out" "$file_out" > changes.txt

then
	echo -e "${GREEN}POSITIVE TEST ${n}: PASSED ${GREEN}"
	ex=${ok}
else
	echo -e "${RED}POSITIVE TEST ${n}: FAILED ${RED}"
	ex=${err_cmp}
fi

rm changes.txt 
rm out.txt 

exit ${ex}