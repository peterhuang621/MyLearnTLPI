link_libraries(lib)
include_directories(. ../time ../users_groups)
add_executable(t_fork t_fork.c)
add_executable(fork_file_sharing fork_file_sharing.c)
add_executable(t_vfork t_vfork.c)
add_executable(fork_whos_on_first fork_whos_on_first.c)
add_executable(fork_sig_sync fork_sig_sync.c ../time/curr_time.c)
add_executable(exit_handles exit_handles.c)
add_executable(fork_stdio_buf fork_stdio_buf.c)
add_executable(multi_wait multi_wait.c ../time/curr_time.c)
add_executable(child_status child_status.c print_wait_status.c)
add_executable(make_zombie make_zombie.c)
add_executable(multi_SIGCHLD multi_SIGCHLD.c print_wait_status.c ../time/curr_time.c)
add_executable(t_execve t_execve.c)
add_executable(envargs envargs.c)
add_executable(t_execlp t_execlp.c)
add_executable(t_execle t_execle.c)
add_executable(t_execl t_execl.c)
add_executable(closeonexec closeonexec.c)
add_executable(t_system t_system.c print_wait_status.c)
add_executable(acct_on acct_on.c)
add_executable(acct_view acct_view.c ../users_groups/ugid_functions.c)
add_executable(t_clone t_clone.c)