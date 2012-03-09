
set (MODULE_DIR "${SRC_DIR}/module")
set (GENERATED_DIR "${SRC_DIR}/generated")
set (CMAKE_CURRENT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_DIR}")
set (CMAKE_CURRENT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/${GENERATED_DIR}")
set (GENERATED_SRC "")

# Does this work everywhere?
find_package (SWIG)

macro (ugdk_add_scriptlang lang)
  swig_add_module (ugdk_${lang} ${lang} ${MODULE_SRC} ${FRAMEWORK_SRC})
  set (TEMP_ONLY_CXX)
  foreach (it ${swig_generated_sources})
    if (${it} MATCHES ".cc$")
      set (TEMP_ONLY_CXX ${TEMP_ONLY_CXX} ${it})
    endif ()
  endforeach (it)
  set (GENERATED_SRC ${GENERATED_SRC} ${TEMP_ONLY_CXX})
  unset (TEMP_ONLY_CXX)
endmacro (ugdk_add_scriptlang lang)

if (SWIG_FOUND)

  include (cmake/UseSWIG.cmake)
  
  # Is MODULE_SRC defined?
  if (NOT MODULE_SRC)
      message (FATAL_ERROR "Variable MODULE_SRC not defined! Please do so in the file src/module_list.cmake!")
  endif (NOT MODULE_SRC)
  
  set_source_files_properties (${MODULE_SRC} PROPERTIES CPLUSPLUS ON)
  set_source_files_properties (${MODULE_SRC} PROPERTIES SWIG_FLAGS "")
  
else (SWIG_FOUND)

  message (WARNING "Could NOT find SWIG. No script modules will be compiled.")

endif (SWIG_FOUND)

