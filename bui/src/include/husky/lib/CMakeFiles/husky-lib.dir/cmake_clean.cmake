file(REMOVE_RECURSE
  "libhusky-lib.pdb"
  "libhusky-lib.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/husky-lib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
