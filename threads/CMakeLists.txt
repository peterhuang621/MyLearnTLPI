add_executable(simple_thread simple_thread.c ../lib/error_functions.c)
add_executable(thread_incr thread_incr.c ../lib/get_num.c ../lib/error_functions.c)
add_executable(thread_incr_mutex thread_incr_mutex.c ../lib/get_num.c ../lib/error_functions.c)
add_executable(prod_condvar prod_condvar.c ../lib/error_functions.c)
add_executable(thread_multijoin thread_multijoin.c ../lib/error_functions.c ../lib/get_num.c)

# non thread-safe
# add_executable(strerror_test strerror_test.c ../lib/error_functions.c strerror.c)
add_executable(strerror_test strerror_test.c ../lib/error_functions.c strerror_tsd.c)

# thread local variables
# add_executable(strerror_test strerror_test.c ../lib/error_functions.c strerror_tls.c)
add_executable(thread_cancel thread_cancel.c ../lib/error_functions.c)

add_executable(thread_cleanup thread_cleanup.c ../lib/error_functions.c)
