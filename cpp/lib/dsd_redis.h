#ifndef DSD_REDIS_H
#define DSD_REDIS_H
#include <stdio.h>
#include "dsd_cloud.h"
#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _dsd_redis_reply
{
   int err;
   void *reply;
   int reply_len;
} dsd_redis_reply;

dsd_redis_reply dsd_redis_exe(dsd_cloud_instance_t *api ,char *service_name , char *cmd);

dsd_redis_reply dsd_redis_exes(dsd_cloud_instance_t *api ,char *service_name, int cmd_c , char**cmds);

#ifdef __cplusplus
}
#endif

#endif