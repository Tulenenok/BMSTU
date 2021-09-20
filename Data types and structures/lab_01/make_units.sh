#!/bin/bash

./make_units_tools.sh
./make_clean.sh

echo " "

./make_units_big_double_tools.sh
./make_clean.sh

echo " "

./make_units_big_double.sh
./make_clean.sh

echo " "

./make_units_big_int.sh
./make_clean.sh

echo " "

./make_units_big_types.sh
./make_clean.sh

echo " "


