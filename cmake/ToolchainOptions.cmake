set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

if(NOT DEFINED LOG_LEVEL)
	set(LOG_LEVEL 1)
endif()
add_definitions(-DLOG_LEVEL=${LOG_LEVEL})

# Misc. find out if clang compiler is used
if(CMAKE_CXX_COMPILER MATCHES ".*clang")
	set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()

# Setup general compiler options
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
	set(CXX_ONLY_FLAGS "-Wall -Wextra -pedantic -Wunreachable-code -Wwrite-strings -Wpointer-arith -Wcast-align -Wcast-qual -Wno-unused-parameter -fPIC -fno-rtti ${CXX_ONLY_FLAGS}")

	# Release build
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
	# Release build with debug symbols
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O3")
	# Debug Build
	set(CMAKE_CXX_FLAGS_DEBUG "-Og")
	# Release build optimized for size
	set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")

	# COMMON_FLAGS is unsued for now
	set(CMAKE_CXX_FLAGS  "${CXX_ONLY_FLAGS} ${COMMON_FLAGS} ${CMAKE_CXX_FLAGS}")
endif()

# set default build type
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UPPER)

if(CMAKE_BUILD_TYPE_UPPER STREQUAL "DEBUG")
	set(EXE_SUFFIX "Debug")
elseif(CMAKE_BUILD_TYPE_UPPER STREQUAL "RELEASE")
	set(EXE_SUFFIX "")
elseif(CMAKE_BUILD_TYPE_UPPER STREQUAL "RELWITHDEBINFO")
	set(EXE_SUFFIX "RelDebg")
elseif(CMAKE_BUILD_TYPE_UPPER STREQUAL "MINSIZEREL")
	set(EXE_SUFFIX "RelMin")
else()
	message(WARNING "Unknown exe suffix found.")
	set(EXE_SUFFIX "Unknown")
endif()

if(CMAKE_BUILD_TYPE_UPPER STREQUAL "RELWITHDEBINFO")
	set(ALL_CXX_FLAGS ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
elseif(CMAKE_BUILD_TYPE_UPPER STREQUAL "RELEASE")
	set(ALL_CXX_FLAGS ${CMAKE_CXX_FLAGS_RELEASE})
elseif(CMAKE_BUILD_TYPE_UPPER STREQUAL "MINSIZEREL")
	set(ALL_CXX_FLAGS ${CMAKE_CXX_FLAGS_MINSIZEREL})
else()
	# Fallback to Debug
	set(ALL_CXX_FLAGS ${CMAKE_CXX_FLAGS_DEBUG})
endif()

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Logging level: ${LOG_LEVEL}")
message(STATUS "Compiler Flags (Modus): ${ALL_CXX_FLAGS}")
message(STATUS "Compiler Flags (cmake): ${CMAKE_CXX_FLAGS}")
