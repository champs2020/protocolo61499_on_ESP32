file(REMOVE_RECURSE
  "libforte-static.a"
  "libforte-static.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/forte-static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
