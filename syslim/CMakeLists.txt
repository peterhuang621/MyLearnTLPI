link_libraries(lib)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -save-temps")
add_executable(t_sysconf t_sysconf.c)
add_executable(t_fpathconf t_fpathconf.c)