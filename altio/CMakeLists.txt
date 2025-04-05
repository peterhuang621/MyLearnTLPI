link_libraries(lib)
add_executable(t_select t_select.c)
add_executable(poll_pipes poll_pipes.c)
add_executable(demo_sigio demo_sigio.c ../tty/tty_functions.c)