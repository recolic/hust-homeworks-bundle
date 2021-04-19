#!/usr/bin/env python3

with open('main.asm') as f:
    cont = f.read()

cter = 0
new_cont = []
for line in cont.split('\n'):
    if 'nop' in line:
        cter += 1
        if cter == 1:
            new_cont.append('    call r_print_impl')
        elif cter == 2:
            new_cont.append('    call r_getchar_impl')
        elif cter == 3:
            new_cont.append('    call r_exit_impl')
        else:
            raise RuntimeError("Bad nop cter")
    elif 'PUBLIC' in line:
        if 'fake_main' in line or 'SEGMENT' in line:
            new_cont.append(line)
    elif 'near ptr r_print_' in line:
        continue
    else:
        new_cont.append(line)
    if 'ASSUME' in line:
        new_cont.append('   include fake_c.asm')

print(new_cont)
new_cont = '\r\n'.join(new_cont)

with open('main.asm', 'w+') as f:
    f.write(new_cont)
