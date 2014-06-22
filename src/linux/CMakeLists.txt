# Use the package PkgConfig to detect GTK+ headers/library files
find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK2 REQUIRED gtk+-2.0)
# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories (${GTK2_INCLUDE_DIRS})
link_directories (${GTK2_LIBRARY_DIRS})

include_directories (${CMAKE_SOURCE_DIR}/cef3/linux/${arch} ${CMAKE_SOURCE_DIR}/cef3/linux/${arch}/include)
link_directories (${CMAKE_SOURCE_DIR}/cef3/linux/${arch}/Release)

# Add other flags to the compiler
add_definitions (${GTK2_CFLAGS_OTHER} -DCEF_ENABLE_SANDBOX=0)
add_executable (example main.cpp)
target_link_libraries (example ${GTK2_LIBRARIES} cef cef_dll_wrapper)

file (COPY ${CMAKE_SOURCE_DIR}/cef3/linux/${arch}/Resources/locales DESTINATION ${CMAKE_BINARY_DIR}/bin)
file (COPY ${CMAKE_SOURCE_DIR}/cef3/linux/${arch}/Resources/cef.pak DESTINATION ${CMAKE_BINARY_DIR}/bin)
file (COPY ${CMAKE_SOURCE_DIR}/cef3/linux/${arch}/Resources/devtools_resources.pak DESTINATION ${CMAKE_BINARY_DIR}/bin)
file (COPY ${CMAKE_SOURCE_DIR}/cef3/linux/${arch}/Resources/icudtl.dat DESTINATION ${CMAKE_BINARY_DIR}/bin)
file (COPY ${CMAKE_SOURCE_DIR}/cef3/linux/${arch}/Release/libcef.so DESTINATION ${CMAKE_BINARY_DIR}/bin)
