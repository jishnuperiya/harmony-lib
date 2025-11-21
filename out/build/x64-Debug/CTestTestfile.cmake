# CMake generated Testfile for 
# Source directory: C:/git-repo/repo-no-name
# Build directory: C:/git-repo/repo-no-name/out/build/x64-Debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[jishnu.example]=] "C:/git-repo/repo-no-name/out/build/x64-Debug/jishnu-test.exe")
set_tests_properties([=[jishnu.example]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/git-repo/repo-no-name/CMakeLists.txt;101;add_test;C:/git-repo/repo-no-name/CMakeLists.txt;0;")
subdirs("_deps/doctest-build")
subdirs("_deps/rapidcheck-build")
