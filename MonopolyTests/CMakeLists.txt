cmake_minimum_required(VERSION 3.13)

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

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.7.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE all_SRCS
        "${PROJECT_SOURCE_DIR}/MonopolyTests/include/MonopolyTests/*.h"
        "${PROJECT_SOURCE_DIR}/MonopolyTests/include/MonopolyTests/*.hpp"
        "${PROJECT_SOURCE_DIR}/MonopolyTests/src/MonopolyTests/*.cpp"
        "${PROJECT_SOURCE_DIR}/MonopolyTests/src/MonopolyTests/*.c"
        )

# Add source to this project's executable.
add_executable (MonopolyTests ${all_SRCS})

GROUPSOURCESBYFOLDER(MonopolyTests)

target_link_libraries(MonopolyTests PRIVATE MonopolyCPP)
target_link_libraries(MonopolyTests PUBLIC Catch2::Catch2WithMain)

target_include_directories(MonopolyTests PUBLIC "${PROJECT_SOURCE_DIR}/../MonopolyCPP/include")
target_include_directories(MonopolyTests PUBLIC "${PROJECT_SOURCE_DIR}/MonopolyTests/include")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MonopolyTests PROPERTY CXX_STANDARD 20)
endif()