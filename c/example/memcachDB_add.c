#include "dsd_cloud.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dsd_log.h"
#include "dsd_mchdb.h"
static void hello_world(dsd_cloud_instance_t * api,
                        int const command,
                        char const * const name,
                        char const * const pattern,
                        void const * const request_info,
                        uint32_t const request_info_size,
                        void const * const request,
                        uint32_t const request_size,
                        uint32_t timeout,
                        int8_t priority,
                        char const * const trans_id,
                        char const * const pid,
                        uint32_t const pid_size)
{
    int flag=0;
    int pos=0;
    
    char *mch_serv="/db/memcached/oc1/ocean1";
    char *req=strdup((char *)request);
    char *find_=req;
    for(pos; pos<strlen(req); pos++){
        find_=req+pos;
        if(*find_ =='|')
            break;
     }
    *find_='\0';
    char *key=req;
    char *value=find_+1;
    flag=dsd_memCachDB_add_key(api, mch_serv,key , value);
    char *ret_fail="flush /db/memcached/oc1/ocean1 fail";
    char *ret_suc="flush /db/memcached/oc1/ocean1 success";
    free(req);
    if(flag ==0){
        dsd_log_info("fail");
        dsd_cloud_return(api, command, name, pattern, "", 0,
                  ret_suc, strlen(ret_suc),
                  timeout, trans_id, pid, pid_size);
    }
    else
    {
        dsd_log_info("success");
        dsd_cloud_return(api, command, name, pattern, "", 0,
                  ret_fail, strlen(ret_fail),
                  timeout, trans_id, pid, pid_size);       
    }
}
int main(int argc, char ** argv)
{
    unsigned int thread_count;
    dsd_log_init();
    dsd_log_set_level(CLOG_DEBUG);
    int result = dsd_cloud_initialize_thread_count(&thread_count);
    assert(result == dsd_cloud_success);
    assert(thread_count == 1);
    dsd_cloud_instance_t api;
    result = dsd_cloud_initialize(&api, 0);
    assert(result == dsd_cloud_success);
    dsd_log_info("start memcached service");
    result = dsd_cloud_subscribe(&api, "mch_add_c/post",
                              &hello_world);
    assert(result == dsd_cloud_success);
    result = dsd_cloud_poll(&api, -1);
    dsd_cloud_destroy(&api);
    return result;
}
