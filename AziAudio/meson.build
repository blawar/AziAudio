# Platform config
target_os = target_machine.system()
build_os = build_machine.system()

# 32 bit
arch_bits = '-m32'
if get_option('x64')
  arch_bits = []
endif
if not meson.is_subproject()
  add_global_arguments(arch_bits, language : ['c', 'cpp'])
endif
arg_linker = [ arch_bits ]
args_platform = []
arg_options = ['-DGBI_FLOATS']


# for non-stubbed version
#sdl_dep = dependency('sdl', native: false)
#aziaudio_deps = [ sdl_dep ]

#stub
aziaudio_deps = [  ]
args_deps = ['-DUSE_SDL']



aziaudio_sources = [
#  'Mupen64plusHLE/audio.c',
#  'Mupen64plusHLE/memory.c',
#  'Mupen64plusHLE/Mupen64Support.c',
#  'Mupen64plusHLE/musyx.c',
  'ABI1.cpp', 
  'ABI2.cpp', 
  'ABI3.cpp', 
  'ABI3mp3.cpp', 
  'ABI_Adpcm.cpp', 
  'ABI_Buffers.cpp', 
  'ABI_Envmixer.cpp', 
  'ABI_Filters.cpp', 
  'ABI_MixerInterleave.cpp', 
  'ABI_Resample.cpp', 
  'Configuration.cpp', 
  'DirectSoundDriver.cpp', 
  'DirectSoundDriverLegacy.cpp', 
  'HLEMain.cpp', 
  'main.cpp', 
  'NoSoundDriver.cpp', 
  'SoundDriver.cpp', 
  'SoundDriverFactory.cpp', 
  'SoundDriverInterface.cpp', 
  'SoundDriverLegacy.cpp', 
  'WASAPISoundDriver.cpp', 
  'WaveOut.cpp', 
  'WaveOutSoundDriver.cpp', 
  'XAudio2SoundDriver.cpp', 
  'XAudio2SoundDriverLegacy.cpp'
]

aziaudio_stub_sources = [
'main_stub.cpp']

# Build type
aziaudio_dll_name = 'AziAudio'
if (get_option('buildtype') == 'release')
  args_platform += [ '-UDEBUG', '-DNDEBUG' ]
  message('Building Release version of AziAudio')
else
  aziaudio_dll_name = 'AziAudio'
  args_platform += [ '-UNDEBUG', '-DDEBUG' ]
  message('Building Debug version of AziAudio')
endif

# Compiler detection
###cc = meson.get_compiler('c')
###args_sdl = []
###sdl_include_path_full = '''#include <SDL2/SDL.h>
###void func() { SDL_Init(0); }
###'''
###sdl_include_path_short = '''#include <SDL.h>
###void func() { SDL_Init(0); }
###'''
###if sdl2_dep.type_name() == 'internal'
###  args_sdl += [ '-DUSE_SDL2_INCLUDE_PATH_SHORT' ]
###  message('Using SDL2 include path  <SDL.h>')
###else
###  result_sdl_path_long = cc.compiles( sdl_include_path_full, name : 'sdl_include_long', dependencies : sdl2_dep )
###  if result_sdl_path_long
###    message('Using SDL2 include path <SDL2/SDL.h>')
###  else
###    result_sdl_path_short = cc.compiles( sdl_include_path_short, name : 'sdl_include_short', dependencies : sdl2_dep )
###    if result_sdl_path_short
###      args_sdl += [ '-DUSE_SDL2_INCLUDE_PATH_SHORT' ]
###      message('Using SDL2 include path  <SDL.h>')
###    else
###      error('Could not find SDL2 include path')
###    endif
###  endif
###endif
#### Add what we learned to the platform args
###args_platform += args_sdl



# platform specific files
message('target_os = ' + target_os)
#if target_os == 'linux' or target_os == 'darwin'
#  gliden64_sources += gliden64_sources_unix
#  args_platform += [ '-DOS_LINUX', '-DNATIVE', '-DGL_USE_UNIFORMBLOCK' ]
#  arg_linker += [ '-pthread' ]
#  dl_dep = cc.find_library('dl')
#  gliden64_deps += dl_dep
#elif target_os == 'windows'
#  gliden64_sources += gliden64_sources_win
#  args_platform += [ '-DOS_WINDOWS', '-D__WIN32__', '-DWIN32', '-D_WIN32_ASM', '-D_CRT_SECURE_NO_WARNINGS', '-D__MSC__', '-DNATIVE', '-DGL_USE_UNIFORMBLOCK']
#  #arg_linker += [ '-lopengl32' ]
#endif

aziaudio_dll = shared_library(aziaudio_dll_name, sources: [ aziaudio_stub_sources ] ,
  cpp_args : [ arg_options, args_platform] , link_args : arg_linker,
  dependencies : aziaudio_deps,
  name_prefix: '',
  install : true)

AziAudio_dep = declare_dependency( link_args : arg_linker, link_with : aziaudio_dll )