# Note that this script can accept some limited command-line arguments, run
# `julia build_tarballs.jl --help` to see a usage message.
using BinaryBuilder

name = "TetGen"
version = v"1.5"

# Collection of sources required to build tetgen
sources = [
    "https://github.com/ufz/tetgen.git" =>
    "9c4b70d479c6f67cb9e16dbe65f81ec3b821acad",
    "https://github.com/JuliaGeometry/TetgenBuilder.git" =>
    "f3fd2796459b3b4217ff4c240603e9193940b7ea"
]

# Bash recipe for building across all platforms
script = raw"""
cd $WORKSPACE/srcdir
cd tetgen/
${CXX} -c -fPIC -std=c++11 -O3 predicates.cxx -o predicates.o
${CXX} -c -fPIC -std=c++11 -O3 -DTETLIBRARY -c tetgen.cxx -o tetgen.o
libdir="lib"
if [[ ${target} == *-mingw32 ]]; then     libdir="bin"; else     libdir="lib"; fi
mkdir ${prefix}/${libdir}
cp tetgen.h ../TetgenBuilder/tetgen.h
${CXX} $LDFLAGS -shared -fPIC tetgen.o predicates.o -DTETLIBRARY -o ${prefix}/${libdir}/libtet.${dlext} ../TetgenBuilder/cwrapper.cpp

exit
"""

# These are the platforms we will build for by default, unless further
# platforms are passed in on the command line
platforms = BinaryBuilder.supported_platforms()

# The products that we will ensure are always built
products(prefix) = [
    LibraryProduct(prefix, "libtet", :libtet)
]

# Dependencies that must be installed before this package can be built
dependencies = [
]

# Build the tarballs, and possibly a `build.jl` as well.
build_tarballs(ARGS, name, version, sources, script, platforms, products, dependencies)
