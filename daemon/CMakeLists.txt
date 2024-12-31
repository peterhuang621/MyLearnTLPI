link_libraries(lib)
add_executable(test_become_daemon test_become_daemon.c become_daemon.h become_daemon.c ../lib/get_num.c)
add_executable(daemon_SIGHUP daemon_SIGHUP.c become_daemon.h become_daemon.c ../lib/get_num.c ../lib/error_functions.c)