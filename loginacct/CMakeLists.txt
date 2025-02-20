link_libraries(lib)
add_executable(dump_utmpx dump_utmpx.c ../lib/error_functions.c)
add_executable(dump_login dump_login.c ../lib/error_functions.c ../lib/get_num.c)
add_executable(view_lastlog view_lastlog.c ../lib/error_functions.c ../users_groups/ugid_functions.c)