#ifndef UGID_FUNCTIONS_H
#define UGID_FUNCTIONS_H

#include "../lib/tlpi_hdr.h"

char* userNameFromId(uid_t uid);

uid_t userIdFromName(const char* name);

char* groupNameFromId(gid_t gid);

gid_t groupIdFromName(const char* name);

#endif
