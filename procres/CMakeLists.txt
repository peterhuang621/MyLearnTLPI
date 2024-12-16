link_libraries(lib)
add_executable(rlimit_nproc rlimit_nproc.c ../lib/get_num.c ../lib/error_functions.c print_rlimit.c)