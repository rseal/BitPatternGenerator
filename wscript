import os

################################################################################
# Local method to remove directory tree
################################################################################
def remove_files(d):
   try:
      shutil.rmtree(d)
   except Exception as ex:
      print(ex)

################################################################################
# Installs symlink to include director for development
################################################################################
def install_symlinks(hdr):

   sym_path =  os.path.abspath('include')

   if not os.geteuid()==0:
      sys.exit('\nERROR: Root Acces is required to execute this script.\n')

   dst_dir = '/usr/local/include/bpg-v2'

   remove_files(dst_dir)

   try:
      print('Creating Directory Tree...')
      os.symlink(sym_path,dst_dir)
      print('Header installation complete.')
   except Exception as ex:
      print(ex)

################################################################################
# Installs a copy of header files in /usr/local/include
################################################################################
def install_headers(hdr):

   if not os.geteuid()==0:
      sys.exit('\nERROR: Root Acces is required to execute this script.\n')

   src_dir = 'include'
   dst_dir = '/usr/local/include/bpg-v2'

   remove_files(dst_dir)

   try:
      print('Creating Directory Tree...')
      shutil.copytree(src_dir,dst_dir,symlinks=True)
      print('Header installation complete.')
   except Exception as ex:
      print(ex)

################################################################################
# Loads c++ and java compiler options
################################################################################
def options(ctx):
   ctx.load('compiler_c compiler_cxx')

################################################################################
# Loads c++ and java compiler options
################################################################################
def configure(ctx):
   ctx.load('compiler_cxx')
   ctx.check(
      features = 'cxx cxxprogram',
      libpath  = ['/usr/lib','/usr/local/lib'],
      libs     = ['dl', 'pthread','usb','rt'],
      cxxflags = ['-Wall', '-std=c++11', '-march=native', '-Wno-unused-parameter', '-Wno-unused-value'],
   )

def options(ctx):
   ctx.load('compiler_cxx')


def build(ctx):

   arecibo_src  = ctx.path.ant_glob('src/arecibo/*.cpp')
   common_src   = ctx.path.ant_glob('src/common/*.cpp')
   psu1_src     = ctx.path.ant_glob('src/psu1/*.cpp')
   generate_src = ctx.path.ant_glob('src/generate/*.cpp')


   generate_prog_src = arecibo_src
   generate_prog_src.extend(common_src) 
   generate_prog_src.extend(psu1_src) 
   generate_prog_src.extend(generate_src)
   shell_prog_src    = [ 'src/shell/bpg-shell.cpp', 'src/shell/okFrontPanelDLL.cpp']
   eeprom_prog_src   = [ 'src/shell/write-eeprom.cpp', 'src/shell/okFrontPanelDLL.cpp']

   ctx(
      name     = 'shell',
      features = 'cxx cxxprogram',
      cxxflags = ['-march=native', '-Wall', '-std=c++11', '-W', '-Wno-unused-parameter', '-Wno-unused-value'],
      includes = ['include','dep/sthread/include', 'dep/clp/include'],
      defines  = {'LINUX':1},
      source   = shell_prog_src,
      target   = 'bpg-shell',
      libpath  = ['/usr/lib','/usr/local/lib'],
      lib      = ['dl', 'pthread','usb','rt','boost_system'],
      install_path = '${PREFIX}/bin'
   )

   ctx(
      name     = 'generate',
      features = 'cxx cxxprogram',
      cxxflags = ['-march=native', '-Wall', '-std=c++11', '-W', '-Wno-unused-parameter', '-Wno-unused-value'],
      includes = ['include','dep/sthread/include', 'dep/clp/include'],
      defines  = {'LINUX':1},
      source   = generate_prog_src,
      target   = 'bpg-generate',
      libpath  = ['/usr/lib','/usr/local/lib'],
      lib      = ['dl', 'pthread','usb','rt', 'boost_system'],
      install_path = '${PREFIX}/bin'
   )

   ctx(
      name     = 'write-eeprom',
      features = 'cxx cxxprogram',
      cxxflags = ['-march=native', '-Wall', '-std=c++11', '-W'],
      includes = ['include','dep/sthread/include', 'dep/clp/include'],
      defines  = {'LINUX':1},
      source   = eeprom_prog_src,
      target   = 'write-eeprom',
      libpath  = ['/usr/lib','/usr/local/lib'],
      lib      = ['dl', 'pthread','usb','rt', 'boost_system'],
      install_path = '${PREFIX}/bin'
   )

   ctx.install_files( '${PREFIX}/bpg/firmware', 'fpga/firmware/bpg.bit')
   ctx.install_files( '${PREFIX}/bpg/modes', 'test/psu.hif')
   ctx.install_files( '${PREFIX}/lib', 'lib/libokFrontPanel.so')

