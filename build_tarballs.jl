# Note that this script can accept some limited command-line arguments, run
# `julia build_tarballs.jl --help` to see a usage message.
using BinaryBuilder

name = "TetGen"
version = v"1.5"

# Collection of sources required to build tetgen
sources = [
    "https://github.com/ufz/tetgen.git" =>
    "9c4b70d479c6f67cb9e16dbe65f81ec3b821acad",
]

# Bash recipe for building across all platforms
script = raw"""
cd $WORKSPACE/srcdir
cd tetgen/
${CXX} -fPIC -O0 -c predicates.cxx
${CXX} -fPIC -DTETLIBRARY -c tetgen.cxx
libdir="lib"
if [[ ${target} == *-mingw32 ]]; then     libdir="bin"; else     libdir="lib"; fi
mkdir ${prefix}/${libdir}
${CXX} $LDFLAGS -shared -fPIC tetgen.o predicates.o -o ${prefix}/${libdir}/libtet.${dlext}
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
