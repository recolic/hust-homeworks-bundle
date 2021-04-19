#!/usr/bin/python

with open('wserver','rb') as fd:
    binstr=fd.read()
print('char binarr[] = {')
cter=0
for binint in binstr:
    print(str(binint)+',', end='')
    cter+=1
    if cter % 16 == 0:
        print('')
print('};')
print('unsigned long binarr_len='+str(cter))
print(';')
