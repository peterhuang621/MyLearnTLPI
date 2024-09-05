link_libraries(lib)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lacl")
include_directories(/usr/include/sys)
include_directories(../users_groups/)
add_executable(acl_view acl_view.c ../users_groups/ugid_functions.c)
target_link_libraries(acl_view acl)
