#!/usr/bin/env python3

import sys
import re

if len(sys.argv) < 3:
    print('Usage: obfuser.py <code file> <dict file>')
    exit(1)

fCode, fDict = sys.argv[1], sys.argv[2]

with open(fDict) as f:
    txtDict = f.read()
with open(fCode) as f:
    txtCode = f.read()

symTable = {}

for line in txtDict.split('\n'):
    line = line.strip()
    if line == '':
        continue
    if line[0] == '#':
        continue
    
    ar = line.split(' ')
    if len(ar) != 2:
        print("Invalid line |{}|.".format(line))
        exit(3)
    
    key, alter = ar[0], ar[1]
    txtCode = re.sub(r"\b%s\b" % key, alter, txtCode)

print(txtCode)