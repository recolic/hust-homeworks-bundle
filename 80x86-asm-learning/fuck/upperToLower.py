#!/usr/bin/env python3

import sys

if len(sys.argv) < 2:
    print('Usage: upperToLower.py <code file>')
    exit(1)

fCode = sys.argv[1]

with open(fCode) as f:
    cont = f.read()

with open(fCode, 'w+') as f:
    f.write(cont.lower())

