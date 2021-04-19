#!/usr/bin/python3

import sys
if len(sys.argv) != 2:
    print('Usage: `./ccgen.py code` or `./ccgen.py help`')
    exit(1)

src = 'reflected_impl.hpp'
mode = sys.argv[1]

# DO NOT use macro in func_name! It'll gen wrong code!
macro_list = [
    ('stref','string'),
    ('void','null'),
]

size_arg = ['size_t']
int_arg = ['int', 'data_t']
string_arg = ['string']

void_ret = ['void', 'null']

def gen_code(line):
    line = line.replace('\t','').replace('\r', '').strip()
    if len(line) == 0:
        return
    ret_type = line.split(' ')[0]
    funcAndArgs = line[len(ret_type):].strip().split('(')
    func_name, args = funcAndArgs[0], funcAndArgs[1].split(')')[0]
    print('//__ccgen_debug__: `ret name(args)` is `{} {}({})`'.format(ret_type, func_name, args))

    args_string = []
    for arg in args.split(','):
        arg_type = arg.strip().split(' ')[0].replace(' ','')
        if len(arg_type) == 0:
            continue
        if arg_type in size_arg:
            args_string.append('SIZE_ARG({})'.format(len(args_string)+1)) # start from one
        elif arg_type in int_arg:
            args_string.append('INT_ARG({})'.format(len(args_string)+1)) # start from one
        elif arg_type in string_arg:
            args_string.append('STRING_ARG({})'.format(len(args_string)+1)) # start from one
        else:
            raise RuntimeError('Unclassed arg left here. line={}|arg_type={}'.format(line, arg_type))
    args_size = len(args_string)
    args_string = ', '.join(args_string)

    print('    IFCMD("{}") {{'.format(func_name))
    print('        WANT_ARG({})'.format(args_size))
    if ret_type not in void_ret:
        print('        HAVE_RETURN_VALUE')
    print('        impl.{}({});'.format(func_name, args_string))
    if ret_type not in void_ret:
        print('        PRINT_RETURN_VALUE')
    print('    }')

def gen_help(line):
    line = line.replace('\t','').replace('\r', '').strip()
    if len(line) == 0:
        return
    ret_type = line.split(' ')[0]
    funcAndArgs = line[len(ret_type):].strip().split('(')
    func_name, args = funcAndArgs[0], funcAndArgs[1].split(')')[0]
#    print('//__ccgen_debug__: `ret name(args)` is `{} {}({})`'.format(ret_type, func_name, args))
    if len(args) == 0:
        print('{} -> {}'.format(func_name, ret_type))
    else:
        print('{} [{}] -> {}'.format(func_name, args, ret_type))

if mode == 'code':
    fuck_a_line = gen_code
    print('//Code generated by ccgen.py below. Do not edit them by hand.')
else:
    fuck_a_line = gen_help
    print('FuncName [Argument ...] -> ReturnValue # Instructions')

with open(src) as fd:
    cont = fd.read()

for line in cont.split('\n'):
    if '__refl_func__' in line:
        line = line.replace('__refl_func__ ', '')
        for _from, _to in macro_list:
            line = line.replace(_from, _to)
        fuck_a_line(line)

if mode != 'code':
    exit(0)

print('''
    IFCMD("exit") {
        rlib::println("bye~");
        ::std::exit(0);
    }
    IFCMD("help") {
        help_msg();
    }
//impl.debug();
//Code generated by ccgen.py above. Do not edit them by hand.
''')
