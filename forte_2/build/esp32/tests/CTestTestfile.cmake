# CMake generated Testfile for 
# Source directory: C:/esp/projects/forte_2/tests
# Build directory: C:/esp/projects/forte_2/build/esp32/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(forte_test "/forte_test")
set_tests_properties(forte_test PROPERTIES  _BACKTRACE_TRIPLES "C:/esp/projects/forte_2/tests/CMakeLists.txt;138;add_test;C:/esp/projects/forte_2/tests/CMakeLists.txt;0;")
subdirs("arch")
subdirs("core")
subdirs("modules")
subdirs("stdfblib")
