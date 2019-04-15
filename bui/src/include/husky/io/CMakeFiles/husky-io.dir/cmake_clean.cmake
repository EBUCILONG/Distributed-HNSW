file(REMOVE_RECURSE
  "libhusky-io.pdb"
  "libhusky-io.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/husky-io.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
