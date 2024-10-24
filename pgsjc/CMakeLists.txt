add_executable(t_setsid t_setsid.c ../lib/error_functions.c)
add_executable(catch_SIGHUP catch_SIGHUP.c ../lib/error_functions.c)
add_executable(disc_SIGHUP disc_SIGHUP.c ../lib/error_functions.c)
add_executable(job_mon job_mon.c ../lib/error_functions.c)