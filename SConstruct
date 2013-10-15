
env = Environment().Clone()

import os

if os.environ.has_key("CC") :
	env.Replace( CC = os.environ['CC'] )
if os.environ.has_key("CXX"):
        env.Replace( CXX = os.environ['CXX'] )

env.Append(
                CPPPATH = [
                        '#',
			'#3rdParty/rapidjson/include',
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


