#!/usr/bin/fish

function run_once
    set exe $argv[1]
    set case $argv[2]
    set win 16
    echo "Running $exe, with test case $case, window size $win..."
    and eval ./$exe -i $case -o $case.dup -w $win > /dev/null
    and echo "Done. Diff result is ---"
    and diff $case $case.dup
    and echo "$exe passed the test."
    or echo "$exe failed the test."
    return $status
end

scons -c
and scons

and echo '***********************************************'
and echo 'Using Google Cpplint code (6245lines) for test.'
and run_once gbn test/cpplint.py
and run_once sr test/cpplint.py
and run_once tcp test/cpplint.py
and run_once stopwait test/cpplint.py
and rm test/*.dup
exit $status

