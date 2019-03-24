file(REMOVE_RECURSE
  "interface_test.pdb"
  "interface_test"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/interface_test.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
