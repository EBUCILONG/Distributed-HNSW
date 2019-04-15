file(REMOVE_RECURSE
  "libhusky-base.pdb"
  "libhusky-base.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/husky-base.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
