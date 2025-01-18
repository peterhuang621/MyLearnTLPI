link_libraries(lib)
add_executable(check_password_caps check_password_caps.c ../lib/error_functions.c)
target_link_libraries(check_password_caps cap crypt)