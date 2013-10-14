
env = Environment().Clone()

import os
print os.environ['CC']
print os.environ['CXX']

if os.environ['CC'] != "":
	env.Replace( CC = os.environ['CC'] )
if os.environ['CXX'] != "":
        env.Replace( CXX = os.environ['CXX'] )

env.Append(
                CPPPATH = [
                        '#',
                        ]
        )

env.Append(
                CXXFLAGS = [
                        '-std=c++11'
                        ]
        )


env.Append(
                LINKFLAGS = [
                        ]
        )

env.Program(
                'qyche',
                Glob( '*.cpp' ),
                LIBPATH='.',
        )


