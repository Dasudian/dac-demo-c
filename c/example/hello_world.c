#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>  
#include <time.h>  
#include "dsd_cloud.h"
#include "dsd_log.h"

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

    dsd_log_info("in hello_world\n");
    dsd_log_info("request is %s \n", (char *)request);
    dsd_cloud_return(api, command, name, pattern, "", 0,
                  request, strlen((char*)request),
                  timeout, trans_id, pid, pid_size);

}
int main(int argc, char ** argv)
{
    unsigned int thread_count;
    dsd_log_init();
    dsd_log_set_level(CLOG_DEBUG);
    int result = dsd_cloud_initialize_thread_count(&thread_count);
    assert(result == dsd_cloud_success);
   // assert(thread_count == 1);
    dsd_cloud_instance_t api;
    result = dsd_cloud_initialize(&api, 0);
    dsd_log_info("init result is %d\n",result);
    assert(result == dsd_cloud_success);
    result = dsd_cloud_subscribe(&api, "hello/post",
                              &hello_world);
    assert(result == dsd_cloud_success);
    result = dsd_cloud_poll(&api, -1);
    dsd_cloud_destroy(&api);
    return result;
}
