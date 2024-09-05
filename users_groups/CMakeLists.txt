add_executable(check_password check_password.c)
target_link_libraries(check_password PUBLIC lib -lcrypt)
