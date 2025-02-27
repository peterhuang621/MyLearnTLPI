link_libraries(lib)
add_executable(simple_pipe simple_pipe.c)
add_executable(pipe_sync pipe_sync.c ../time/curr_time.c)