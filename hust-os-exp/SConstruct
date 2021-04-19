ccflags = '-std=c++17'

# No need to compile rlib from source
# rlibenv=Environment(CPPPATH='./lib/rlib', CPPFLAGS='-std=c++17') 
# rlibenv.Library('r', ['lib/rlib/libr.cc'])

env=Environment(CPPDEFINES=[], LIBS=['r'], CPPFLAGS='-std=c++17')
env.Program('1', '1.cc', LIBS=['pthread','r'], CPPFLAGS='')
env.Program('2', '2.cc', LIBS=['pthread','r'])
env.Program('2-proc', '2-proc.cc', LIBS=['r'])
env.Program('3', '3.cc', LIBS=['r'])
env.Program('tree', '4.cc', LIBS=['stdc++fs','r'])

