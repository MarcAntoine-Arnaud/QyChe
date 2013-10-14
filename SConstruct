
env = Environment().Clone()
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


