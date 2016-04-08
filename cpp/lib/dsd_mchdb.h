#ifndef DSD_MCHDB_H
#define DSD_MCHDB_H

#include "dsd_cloud.h" 

#ifdef __cplusplus
extern "C"
{
#endif

char* dsd_memCachDB_get_key(dsd_cloud_instance_t * api, char *service_name ,char *key);

int dsd_memCachDB_add_key(dsd_cloud_instance_t * api, char *service_name , char *key,char *value);

int dsd_memCachDB_add_key_expiredTime(dsd_cloud_instance_t * api, char *service_name , char *key, char *value, int expire_time);

int dsd_memCachDB_set_key(dsd_cloud_instance_t * api, char *service_name , char *key, char *value);

int dsd_memCachDB_set_key_expiredTime(dsd_cloud_instance_t * api, char *service_name , char *key,char *value, int expire_time);

int dsd_memCachDB_replace_key(dsd_cloud_instance_t * api, char *service_name , char *key, char *value);

int dsd_memCachDB_delete_key(dsd_cloud_instance_t * api, char *service_name , char *key);

char* dsd_memCachDB_version(dsd_cloud_instance_t * api, char *service_name);

int dsd_memCachDB_flush(dsd_cloud_instance_t * api, char *service_name);

int dsd_memCachDB_append_key(dsd_cloud_instance_t * api, char *service_name , char *key, char * value);

int dsd_memCachDB_prepend_key(dsd_cloud_instance_t * api, char *service_name , char *key, char * value) ;


#ifdef __cplusplus
}
#endif

#endif





