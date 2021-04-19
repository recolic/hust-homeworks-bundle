#!/bin/bash

echo 'Here is test script for recolic/chw, by Recolic Keghart, Mozilla licensed.'
[[ $1 == '' ]] && echo 'Usage: ./test.sh <bin dir> [disable stdout redirect]' && exit 1

bindir=$1
[[ $2 != '' ]] && redir="/dev/null" || redir="/dev/fd/1"

function assert () {
    CMD="$*"
    $CMD
    RET_VAL=$?
    if [ $RET_VAL != 0 ]; then
        echo "Assertion failed: $CMD returns $RET_VAL."
        exit $RET_VAL
    fi
}

function randstr4 () {
    < /dev/urandom tr -dc _A-Z-a-z-0-9 | head -c${1:-4};echo;
}

function randstr32 () {
    < /dev/urandom tr -dc _A-Z-a-z-0-9 | head -c${1:-32};echo;
}

function randint () {
    echo "$(( ( RANDOM % 100 )  + 1 ))"
}

function test_vcset () {
    ./chw-cli veg-class-set $(randint) $(randstr32)
}

function test_viset () {
    ./chw-cli veg-info-set $(randstr32) $(randint) $(randstr32)
}

function test_jset () {
    ./chw-cli job-set $(randint) $(randint) $(randint) "$(randint).$(randint)" $(randint)
}

function test_vcrm () {
    ./chw-cli veg-class-rm $(randint)
}

function test_virm () {
    ./chw-cli veg-info-rm $(randint)
}

function test_jrm () {
    ./chw-cli job-rm $(randint)
}

function test_ls () {
    echo 'performing ls...'
    echo 'veg-cls->'
    ./chw-cli veg-class-ls
    echo 'veg-inf->'
    ./chw-cli veg-info-ls
    echo 'job->'
    ./chw-cli job-ls
}

assert cd $bindir
assert ./clear_database.sh

echo 'perform 1000 veg class set...'
for i in {1..1000}
do
    echo -ne "\r$i"
    assert test_vcset > $redir
done
echo ' '
assert test_ls

echo 'perform 30 veg class rm, may fail...'
for i in {1..30}
do
    echo -ne "\r$i"
    test_vcrm
done
echo ' '
assert test_ls

echo 'perform 1000 veg class set...'
for i in {1..1000}
do
    echo -ne "\r$i"
    assert test_vcset > $redir
done
echo ' '

echo 'perform 300 veg info set...'
for i in {1..300}
do
    echo -ne "\r$i"
    test_viset > $redir
done
echo ' '
assert test_ls

echo 'Because veg name must be given, skipping veg-info-rm-test'

echo 'perform 1000 job set...'
for i in {1..1000}
do
    echo -ne "\r$i"
    test_jset > $redir
done
echo ' '
assert test_ls

echo 'perform 50 job rm, may fail...'
for i in {1..50}
do
    echo -ne "\r$i"
    test_jrm
done
echo ' '
assert test_ls

echo 'perform 1000 job set...'
for i in {1..1000}
do
    echo -ne "\r$i"
    test_jset > $redir
done
echo ' '

echo 'test done. Try filtered ls/summery manually.'
cd -

