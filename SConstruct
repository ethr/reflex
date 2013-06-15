import glob

# create build environment
env = Environment()

# determine compiler and linker flags for SDL
env.ParseConfig('sdl-config --cflags')
env.ParseConfig('sdl-config --libs')


# add additional compiler flags
env.Append(CCFLAGS = ['-g', '-Wall'])
env.Append(LIBS = ['-lSDL_gfx', '-lSDL_ttf', '-lSDL_image'])

# build target
# gather a list of source files
# output executable will be "game"
SOURCES = glob.glob('src/*.cpp')
env.Program(target = 'game', source = SOURCES)
