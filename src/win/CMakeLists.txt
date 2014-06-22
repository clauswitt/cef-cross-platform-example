include_directories (${CMAKE_SOURCE_DIR}/cef3/win/${arch} ${CMAKE_SOURCE_DIR}/cef3/win/${arch}/include)
link_directories (${CMAKE_SOURCE_DIR}/cef3/win/${arch}/Release)

# MAX WARNINGS
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ansi -pedantic")
endif()

add_definitions(-DCEF_ENABLE_SANDBOX=0)
add_executable (example main.cpp)

# /SUBSYSTEM:WINDOWS
IF (WIN32) # Check if we are on Windows
  if (MSVC) # Check if we are using the Visual Studio compiler
    set_target_properties(example PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
  else()
    message (SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
  endif()
elseif (UNIX)
  # Nothing special required
else ()
  message(SEND_ERROR "You are on an unsupported platform! (Not Win32 or Unix)")
endif ()

target_link_libraries (example comctl32 shlwapi rpcrt4 libcef_dll_wrapper libcef cef_sandbox)

file (COPY ${CMAKE_SOURCE_DIR}/cef3/win/${arch}/Resources/locales DESTINATION ${CMAKE_BINARY_DIR}/bin)
file (COPY ${CMAKE_SOURCE_DIR}/cef3/win/${arch}/Resources/cef.pak DESTINATION ${CMAKE_BINARY_DIR}/bin)
file (COPY ${CMAKE_SOURCE_DIR}/cef3/win/${arch}/Resources/devtools_resources.pak DESTINATION ${CMAKE_BINARY_DIR}/bin)
file (COPY ${CMAKE_SOURCE_DIR}/cef3/win/${arch}/Resources/icudtl.dat DESTINATION ${CMAKE_BINARY_DIR}/bin)
file (COPY ${CMAKE_SOURCE_DIR}/cef3/win/${arch}/Release/libcef.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
