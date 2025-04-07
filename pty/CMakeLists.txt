link_libraries(lib)
include_directories(.)
add_executable(script script.c ../tty/tty_functions.c pty_fork.c pty_master_open.c)