#custom build flags
warnFlags = ['-g', '-Wall', '-W']
defineFlags = ['LINUX']

#define installtion directories
bin_directory = '/usr/local/bin'
lib_directory = '/usr/local/lib'
header_directory = '/usr/local/include/bpg-v2'

#source groups
arecibo_src = [ Glob( 'src/arecibo/*.cpp' )]
common_src = [ Glob( 'src/common/*.cpp' ) ]
psu1_src = [ Glob( 'src/psu1/*.cpp' ) ]
generate_src = [ Glob( 'src/generate/*.cpp' ) ]
shell_src = [ 'src/shell/bpg-shell.cpp', 'src/shell/okFrontPanelDLL.cpp']
eeprom_src = [ 'src/shell/write-eeprom.cpp', 'src/shell/okFrontPanelDLL.cpp']

generate_prog_src = [ arecibo_src, common_src, psu1_src, generate_src ]
shell_prog_src = [ shell_src ]
eeprom_prog_src = [ eeprom_src ]

#setup library path
libPath=['/usr/lib','/usr/local/lib']
libs=['dl', 'pthread','usb','rt'];

#define build environment
env = Environment(LIBPATH=libPath,CXXFLAGS=warnFlags,CPPDEFINES=defineFlags);

#object = warnEnv.Object( target='bin/okFrontPanel', source='src/shell/okFrontPanelDLL.cpp' );
env.Program(target='bin/bpg-shell', source=shell_prog_src, LIBS=libs);
eeprom = env.Program(target='bin/write-eeprom', source=eeprom_prog_src, LIBS=libs);
env.Program(target='bin/bpg-generate', source=generate_prog_src, LIBS=libs);

bin_install = env.Install( dir=bin_directory, source=Glob( 'bin/bpg-*' ) )
lib_install = env.Install( dir=lib_directory, source=Glob( 'lib/*' ) )
header_install = env.Install( dir=header_directory, source=Glob( 'include/*' ) )

env.Alias( 'install', bin_directory, bin_install )
env.Alias( 'install', lib_directory, lib_install )
env.Alias( 'install-headers', header_directory, header_install )



