#include "dsd_cloud.h"
#include <string.h>
#include <assert.h>
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
	char const * const sql = "{put, \"key1\", \"{\\\"age\\\": 20, \\\"name\\\":\\\"Jack\\\"}\"}";
	char const * const sql2 = "{put, \"key2\", \"{\\\"age\\\": 22, \\\"name\\\":\\\"villianm\\\"}\"}";
	char const * const sql3 = "{put, \"key3\", \"{\\\"age\\\": 25, \\\"name\\\":\\\"lala\\\"}\"}";
	char const * const sql4 = "{get, \"key1\"}";
	uint32_t const sql_size = strlen(sql);
	uint32_t const sql2_size = strlen(sql2);
	uint32_t const sql3_size = strlen(sql3);
	uint32_t const sql4_size = strlen(sql4);
	char const * const mysql = "/db/dsdb/sunwoda";
	dsd_cloud_send_sync(api, mysql, sql, sql_size); 
	dsd_cloud_send_sync(api, mysql, sql2, sql2_size); 
	dsd_cloud_send_sync(api, mysql, sql3, sql3_size); 
	dsd_cloud_send_sync(api, mysql, sql4, sql4_size); 
    char const * const message = dsd_cloud_get_response(api);
    uint32_t const message_size = strlen(message);
    dsd_cloud_return(api, command, name, pattern, "", 0,
                  message, message_size,
                  timeout, trans_id, pid, pid_size);
}
int main(int argc, char ** argv)
{
    unsigned int thread_count;
    int result = dsd_cloud_initialize_thread_count(&thread_count);
    assert(result == dsd_cloud_success);
    assert(thread_count == 1);
    dsd_cloud_instance_t api;
    result = dsd_cloud_initialize(&api, 0);
    assert(result == dsd_cloud_success);
    result = dsd_cloud_subscribe(&api, "get/get",
                              &hello_world);
    assert(result == dsd_cloud_success);
    result = dsd_cloud_poll(&api, -1);
    dsd_cloud_destroy(&api);
    return result;
}

