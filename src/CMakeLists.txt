include_directories(${CMAKE_SOURCE_DIR}/include)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    subdirs (mac)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    subdirs (linux)
elseif (WIN32)
    subdirs (win)
endif ()
