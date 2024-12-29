# CMakeList.txt : CMake project for MonopolyCPP, include source and define
# project specific logic here.
#

function(GroupSourcesByFolder target)
  set(SOURCE_GROUP_DELIMITER "/")
  set(last_dir "")
  set(files "")

  get_target_property(sources ${target} SOURCES)

  foreach(file ${sources})
    file(RELATIVE_PATH relative_file "${PROJECT_SOURCE_DIR}" ${file})
    get_filename_component(dir "${relative_file}" PATH)
    if(NOT "${dir}" STREQUAL "${last_dir}")
      if(files)
        source_group("${last_dir}" FILES ${files})
      endif()
      set(files "")
    endif()
    set(files ${files} ${file})
    set(last_dir "${dir}")
  endforeach()

  if(files)
    source_group("${last_dir}" FILES ${files})
  endif()
endfunction()

message("Test ${PROJECT_SOURCE_DIR}")

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

file(GLOB_RECURSE all_SRCS
        "${PROJECT_SOURCE_DIR}/MonopolyCPP/include/Monopoly/*.h"
        "${PROJECT_SOURCE_DIR}/MonopolyCPP/include/Monopoly/*.hpp"
        "${PROJECT_SOURCE_DIR}/MonopolyCPP/src/Monopoly/*.cpp"
        "${PROJECT_SOURCE_DIR}/MonopolyCPP/src/Monopoly/*.c"
        )

# Add source to this project's executable.
add_executable (MonopolyCPP ${all_SRCS})

target_link_libraries(MonopolyCPP PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(MonopolyCPP PUBLIC "${PROJECT_SOURCE_DIR}/MonopolyCPP/include")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MonopolyCPP PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
