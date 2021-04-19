#!/usr/bin/env python3
# Usage: ./testgen.py 1000000 > test.rfakesh

import sys
import random

HOW_MANY_PEOPLE_HAVE_FRIEND = 0.8
MAX_FRIEND_DO_PEOPLE_HAVE = 32
PEOPLE_SIZE = int(sys.argv[1])

print('''#!./hust-ds
# Generated by testgen.py, with size {}.
# Copyright (C) 2018 Recolic Keghart <root@recolic.net>
'''.format(PEOPLE_SIZE))

for i in range(PEOPLE_SIZE):
    print('new_person_at', i+1)
print('\n')

for what in ['friend', 'follower', 'following']:
    for person in range(PEOPLE_SIZE):
        person = person + 1
        if random.random() > HOW_MANY_PEOPLE_HAVE_FRIEND:
            continue # Sorry, you're alone.
        targets = []
        for _ in range(random.randint(0, MAX_FRIEND_DO_PEOPLE_HAVE)):
            target = random.randint(1, PEOPLE_SIZE)
            if target == person:
                continue # Sorry. Unlucky.
            targets.append(target)
        for target in set(targets):
            print('add', what, person, target)
    print()

print('save test/test.json')
