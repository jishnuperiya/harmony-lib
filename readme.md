# Jishnu

## Goals

This project is a vehicle for learning about the C++ language.

## Project Layout

To get up and running quickly, and without knowing more about just what actual libraries and executables we will need, I have made some arbitrary choices, all of which can be changed later as needed:

- *jishnu-lib*: a static link library that contains the bulk of the code we will write together.

- *jishnu-test*: a doctest-based harness that links against *jishnu-lib*.

- *jishnu*: an executable that links against _jishnu-lib_.

The test harnesses implements a rich command line interface, and is RapidCheck enabled.

## Prerequisites

### MacOS:

    sudo port -N install clang-20 cmake doxygen

## Building

    mkdir .bld
    cd .bld
    cmake ..
    make -j

Also:

    make help

to see a list of possible of build targets.

## Running

To run the _jishnu_ test harness:

    ./jishnu-test

To run the _jishnu_ executable:

    ./jishnu

# Contributors

- jishnuperiya@gmail.com
- jonathon.bell@gmail.com
