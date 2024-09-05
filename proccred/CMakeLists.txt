add_executable(idshow idshow.c ../users_groups/ugid_functions.c ../users_groups/ugid_functions.h)
target_link_libraries(idshow PUBLIC lib)