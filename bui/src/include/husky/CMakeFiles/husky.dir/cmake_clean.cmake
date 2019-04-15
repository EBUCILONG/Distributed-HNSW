file(REMOVE_RECURSE
  "libhusky.pdb"
  "libhusky.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/husky.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
