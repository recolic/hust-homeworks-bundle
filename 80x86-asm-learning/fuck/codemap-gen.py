#!/usr/bin/env python3

import sys
if len(sys.argv) < 2:
    print('Usage: upperToLower.py <code file>')
    exit(1)

fCode = sys.argv[1]

with open(fCode) as f:
    cont = f.read()

# Available codespace: 101-299
counter = 101

def try_keyword(line, word):
    global counter
    line = line.strip()
    pos = line.find(word)
    if pos == -1:
        return False
    else:
        key = line[:pos].strip()
        if ' ' in key:
            return False
        if key == 'start':
            return False

        value = 'tmp' + str(counter)
        counter += 1
        print(key, value)
        return True


for line in cont.split('\n'):
    for keyword in [':', ' proc', ' macro']:
        if try_keyword(line, keyword):
            break