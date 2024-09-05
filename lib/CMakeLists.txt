file(GLOB_RECURSE libsrc *.c)
file(GLOB_RECURSE libheader *.h)
add_library(lib SHARED ${libsrc})
target_link_directories(lib PUBLIC ${libheader})
