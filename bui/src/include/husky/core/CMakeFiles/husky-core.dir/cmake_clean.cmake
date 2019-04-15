file(REMOVE_RECURSE
  "libhusky-core.pdb"
  "libhusky-core.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/husky-core.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
