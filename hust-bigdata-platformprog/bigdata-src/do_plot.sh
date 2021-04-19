#!/bin/bash
[[ $2 = '' ]] && echo 'Usage: ./do_plot.sh ~/prepared-totalCheckins.txt output.png' && exit 1
python plot/plot.py "$1" .tmp.txt &&
gnuplot -c plot/gnuplot.script &&
rm .tmp.txt &&
mv .tmp.png "$2"

exit $?
