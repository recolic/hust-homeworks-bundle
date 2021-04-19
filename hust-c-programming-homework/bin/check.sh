#!/bin/bash

function _failed () {
    if [ "$2" == "fatal" ]; then
        echo '***************fatal*****************'
    else
        echo '*************************************'
    fi
    echo "Check bin/object $1 failed"
    echo 'Ignore this tip may cause fa_tal problem!'
    echo '*************************************'
}

function _assert () {
    echo "Checking $3..."
    $1 | grep $2 > /dev/null
    ret=$?
    if [ $ret != 0 ]; then
        if [ "$3" == "" ]; then
            _failed $1
        else
            _failed $3
        fi
    fi
}

function _libexist () {
    echo "Checking $1..."
    if [ ! -f /lib/$1 ] && [ ! -f /lib64/$1 ]; then
        _failed $1 fatal
        echo 'You must download failed lib I want from your repo provided by your distri
            or try https://tdl.recolic.net/homework/libs-for-hustc.tar.xz for your lost libs.'
    fi
}

echo '
Runtime depencency confirmation for chw.
For github.com/recolic/chw branch "pure_source".
Recolic Keghart
'
_assert 'uname' 'Linux' 'linux'
_assert 'uname -r' '^4\.1[0-9]\.' 'linux-version'
_assert 'grep --help' 'basic-regexp' 'grep'
_assert 'mkdir --help' '^.' 'mkdir'
_assert 'sort --help' 'field-separator=' 'sort'

echo 'Skipped runtime-lib check on compilation time.'
exit 0

_libexist libc.so.6
_libexist libgcc_s.so.1
_libexist libm.so.6
_libexist libstdc++.so.6
_libexist libboost_system.so.1.64.0
