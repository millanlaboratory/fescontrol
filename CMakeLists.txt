cmake_minimum_required(VERSION 3.2)


set(PROJECT_NAME fescontrol)
project(${PROJECT_NAME})

file(MAKE_DIRECTORY "external")
file(MAKE_DIRECTORY "build")

find_package(PkgConfig)

# To use coverage type cmake -DCMAKE_BUILD_TYPE=Coverage
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
  option(test "Build all tests." ON) # Makes boolean 'test' available.

  # Download and unpack googletest at configure time
  configure_file(CMakeLists.txt.in external/googletest-download/CMakeLists.txt)
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY external/googletest-download )
  if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
  endif()
  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY external/googletest-download )
  if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
  endif()

  # Prevent overriding the parent project's compiler/linker
  # settings on Windows
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  # Add googletest directly to our build. This defines
  # the gtest and gtest_main targets.
  add_subdirectory(external/googletest-src
                   external/googletest-build)

  # The gtest/gtest_main targets carry header search path
  # dependencies automatically when using CMake 2.8.11 or
  # later. Otherwise we have to add them here ourselves.
  if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories(BEFORE SYSTEM
      "${gtest_SOURCE_DIR}/include" "${gmock_SOURCE_DIR}/include")
  else()
    target_include_directories(gmock_main SYSTEM BEFORE INTERFACE
      "${gtest_SOURCE_DIR}/include" "${gmock_SOURCE_DIR}/include")
  endif()
  enable_testing()
endif()

pkg_search_module(FESLANGUAGE REQUIRED feslanguage)
pkg_search_module(JSONCPP REQUIRED jsoncpp)
pkg_search_module(CNBILOOP REQUIRED cnbiloop)
pkg_search_module(CNBICORE REQUIRED cnbicore)
pkg_search_module(TOBIID REQUIRED tobiid)
pkg_search_module(PYTHON REQUIRED python-2.7)

if(!JSONCPP_FOUND)
  execute_process(COMMAND sudo apt-get install libjsoncpp-dev)
endif()
if(!PYTHON_FOUND)
  execute_process(COMMAND sudo apt-get install python2.7-dev)
endif()

include_directories(
    ${FESLANGUAGE_INCLUDE_DIRS}
    ${JSONCPP_INCLUDE_DIRS}
    ${CNBILOOP_INCLUDE_DIRS}
    ${CNBICORE_INCLUDE_DIRS}
    ${TOBIID_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)
link_directories(${JSONCPP_INCLUDE_DIRS})

file(GLOB SRC
	"main.cpp"
  "src/GUI/*.h"
  "src/GUI/*.cpp"
)

file(GLOB test_SRC
	"test/*.cpp"
	"test/src/*.h"
	"test/src/*.cpp"
)

file(GLOB library_SRC
	"src/*.h"
	"src/*.cpp"
	"src/interfaces/*.h"
	"src/interfaces/*.cpp"
  "src/GUI/*.h"
  "src/GUI/*.cpp"
)

file(GLOB library_CORE_HEADERS
	"src/*.h"
)

file(GLOB library_INTERFACES_HEADERS
	"src/interfaces/*.h"
)

file(GLOB library_ERRORS_HEADERS
	"src/errors/*.h"
)

file(GLOB library_FESLANGUAGE_HEADERS
	"${FESLANGUAGE_INCLUDE_DIRS}/*.h"
)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "build")
add_library(fescontrol STATIC ${library_SRC})


execute_process(COMMAND pkg-config --cflags --libs feslanguage cnbiloop cnbicore tobiid jsoncpp python OUTPUT_VARIABLE _FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_CXX_FLAGS "-std=c++11  -g -Wall ${_FLAGS} ")
add_executable(fesControl ${SRC})

target_link_libraries(fescontrol feslanguage cnbiloop cnbicore tobiid jsoncpp python2.7)
target_link_libraries(fesControl fescontrol )

# To use coverage type cmake -DCMAKE_BUILD_TYPE=Coverage
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include("CodeCoverage.cmake")
    set(COVERAGE_EXCLUDES 'src/matplotlibcpp')
    APPEND_COVERAGE_COMPILER_FLAGS()
    SETUP_TARGET_FOR_COVERAGE(
     NAME testfesjson_coverage                    # New target name
     EXECUTABLE testfesjson -j ${PROCESSOR_COUNT} # Executable in PROJECT_BINARY_DIR
     DEPENDENCIES fescontrol gmock_main                      # Dependencies to build first
    )
    add_executable(testfesjson  ${test_SRC})

    target_link_libraries(testfesjson fescontrol gmock_main )
    add_test(NAME AllTests COMMAND testfesjson)
endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"





INSTALL(TARGETS ${PROJECT_NAME}   
    DESTINATION /usr/lib/${PROJECT_NAME}
)	
INSTALL(TARGETS fesControl  
    DESTINATION /usr/bin/
) 
INSTALL(FILES ${library_CORE_HEADERS}
    DESTINATION /usr/include/${PROJECT_NAME}
)
INSTALL(FILES ${library_INTERFACES_HEADERS}
    DESTINATION /usr/include/${PROJECT_NAME}/interfaces
)
INSTALL(FILES ${library_ERRORS_HEADERS}
    DESTINATION /usr/include/${PROJECT_NAME}/errors
)

INSTALL(FILES ${library_FESLANGUAGE_HEADERS} DESTINATION /usr/include/${PROJECT_NAME})
