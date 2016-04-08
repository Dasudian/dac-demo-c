/* -*-
 *
 * Copyright (c) 2015-2016, Dasudian.com <barco@dasudian.com>
 * All rights reserved.
 * 
 */

#ifdef DSD_CLOUD_HPP
#warning "Only need to include dsd_cloud.h (C), not dsd_cloud.hpp (C++)"
#endif
#ifndef DSD_CLOUD_H
#define DSD_CLOUD_H

#include <stdint.h>

#if defined __cplusplus
extern "C"
{
#endif

#define DSD_CLOUD_MAX_BUFFERSIZE 2147483648U /* 2GB */

typedef struct dsd_cloud_instance_t
{
    int fd_in;
    int fd_out;
    int use_header;
    int initialization_complete;
    int terminate;
    uint32_t buffer_size;
    void * lookup;
    void * buffer_send;
    void * buffer_recv;
    uint32_t buffer_recv_index;
    void * buffer_call;
    void * poll_timer;
    void * request_timer;
    uint32_t request_timeout;
    uint32_t process_index;
    uint32_t process_count;
    uint32_t process_count_max;
    uint32_t process_count_min;
    char * prefix;
    uint32_t timeout_initialize;
    uint32_t timeout_async;
    uint32_t timeout_sync;
    uint32_t timeout_terminate;
    int8_t priority_default;
    uint8_t request_timeout_adjustment;
    char * response_info;
    uint32_t response_info_size;
    char * response;
    uint32_t response_size;
    char * trans_id;          /* always 16 characters (128 bits) length */
    uint32_t trans_id_count;
    uint32_t subscribe_count;

} dsd_cloud_instance_t;

/* command values */
#define DSD_CLOUD_ASYNC     1
#define DSD_CLOUD_SYNC     -1

typedef void (*dsd_cloud_callback_t)(dsd_cloud_instance_t * p,
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
                                  uint32_t const pid_size);


#define dsd_cloud_get_response(p)               ((p)->response)
#define dsd_cloud_get_response_size(p)          ((p)->response_size)
#define dsd_cloud_get_response_info(p)          ((p)->response_info)
#define dsd_cloud_get_response_info_size(p)     ((p)->response_info_size)
#define dsd_cloud_get_trans_id_count(p)         ((p)->trans_id_count)
#define dsd_cloud_get_trans_id(p, i)            (&((p)->trans_id[i * 16]))
#define dsd_cloud_get_subscribe_count(p)        ((p)->subscribe_count)
#define dsd_cloud_get_process_index(p)          ((p)->process_index)
#define dsd_cloud_get_process_count(p)          ((p)->process_count)
#define dsd_cloud_get_process_count_max(p)      ((p)->process_count_max)
#define dsd_cloud_get_process_count_min(p)      ((p)->process_count_min)
#define dsd_cloud_get_prefix(p)                 ((p)->prefix)
#define dsd_cloud_get_timeout_initialize(p)     ((p)->timeout_initialize)
#define dsd_cloud_get_timeout_async(p)          ((p)->timeout_async)
#define dsd_cloud_get_timeout_sync(p)           ((p)->timeout_sync)
#define dsd_cloud_get_timeout_terminate(p)      ((p)->timeout_terminate)
#define dsd_cloud_get_priority_default(p)       ((p)->priority_default)

int dsd_cloud_initialize(dsd_cloud_instance_t * p,
                      unsigned int const thread_index);
int dsd_cloud_initialize0(dsd_cloud_instance_t * p);                  

void dsd_cloud_destroy(dsd_cloud_instance_t * p);

int dsd_cloud_initialize_thread_count(unsigned int * const thread_count);

int dsd_cloud_subscribe(dsd_cloud_instance_t * p,
                     char const * const pattern,
                     dsd_cloud_callback_t f);

int dsd_cloud_subscribe_count(dsd_cloud_instance_t * p,
                           char const * const pattern);

int dsd_cloud_unsubscribe(dsd_cloud_instance_t * p,
                       char const * const pattern);

int dsd_cloud_send_async(dsd_cloud_instance_t * p,
                      char const * const name,
                      void const * const request,
                      uint32_t const request_size);

int dsd_cloud_send_async_(dsd_cloud_instance_t * p,
                       char const * const name,
                       void const * const request_info,
                       uint32_t const request_info_size,
                       void const * const request,
                       uint32_t const request_size,
                       uint32_t timeout,
                       int8_t const priority);

int dsd_cloud_send_sync(dsd_cloud_instance_t * p,
                     char const * const name,
                     void const * const request,
                     uint32_t const request_size);

int dsd_cloud_send_sync_(dsd_cloud_instance_t * p,
                      char const * const name,
                      void const * const request_info,
                      uint32_t const request_info_size,
                      void const * const request,
                      uint32_t const request_size,
                      uint32_t timeout,
                      int8_t const priority);

int dsd_cloud_publish(dsd_cloud_instance_t * p,
                       char const * const name,
                       void const * const request,
                       uint32_t const request_size);

int dsd_cloud_publish_(dsd_cloud_instance_t * p,
                        char const * const name,
                        void const * const request_info,
                        uint32_t const request_info_size,
                        void const * const request,
                        uint32_t const request_size,
                        uint32_t timeout,
                        int8_t const priority);

int dsd_cloud_forward(dsd_cloud_instance_t * p,
                   int const command,
                   char const * const name,
                   void const * const request_info,
                   uint32_t const request_info_size,
                   void const * const request,
                   uint32_t const request_size,
                   uint32_t timeout,
                   int8_t const priority,
                   char const * const trans_id,
                   char const * const pid,
                   uint32_t const pid_size);

int dsd_cloud_forward_async(dsd_cloud_instance_t * p,
                         char const * const name,
                         void const * const request_info,
                         uint32_t const request_info_size,
                         void const * const request,
                         uint32_t const request_size,
                         uint32_t timeout,
                         int8_t const priority,
                         char const * const trans_id,
                         char const * const pid,
                         uint32_t const pid_size);

int dsd_cloud_forward_sync(dsd_cloud_instance_t * p,
                        char const * const name,
                        void const * const request_info,
                        uint32_t const request_info_size,
                        void const * const request,
                        uint32_t const request_size,
                        uint32_t timeout,
                        int8_t const priority,
                        char const * const trans_id,
                        char const * const pid,
                        uint32_t const pid_size);

int dsd_cloud_return(dsd_cloud_instance_t * p,
                  int const command,
                  char const * const name,
                  char const * const pattern,
                  void const * const response_info,
                  uint32_t const response_info_size,
                  void const * const response,
                  uint32_t const response_size,
                  uint32_t timeout,
                  char const * const trans_id,
                  char const * const pid,
                  uint32_t const pid_size);

int dsd_cloud_return_async(dsd_cloud_instance_t * p,
                        char const * const name,
                        char const * const pattern,
                        void const * const response_info,
                        uint32_t const response_info_size,
                        void const * const response,
                        uint32_t const response_size,
                        uint32_t timeout,
                        char const * const trans_id,
                        char const * const pid,
                        uint32_t const pid_size);

int dsd_cloud_return_sync(dsd_cloud_instance_t * p,
                       char const * const name,
                       char const * const pattern,
                       void const * const response_info,
                       uint32_t const response_info_size,
                       void const * const response,
                       uint32_t const response_size,
                       uint32_t timeout,
                       char const * const trans_id,
                       char const * const pid,
                       uint32_t const pid_size);

int dsd_cloud_recv_async(dsd_cloud_instance_t * p,
                      uint32_t timeout,
                      char const * const trans_id,
                      int consume);

int dsd_cloud_poll(dsd_cloud_instance_t * p,
                int timeout);

char const ** dsd_cloud_request_http_qs_parse(void const * const request,
                                           uint32_t const request_size);
void dsd_cloud_request_http_qs_destroy(char const ** p);

char const ** dsd_cloud_info_key_value_parse(void const * const request_info,
                                          uint32_t const request_info_size);
void dsd_cloud_info_key_value_destroy(char const ** p);

enum
{
    dsd_cloud_success                             =   0,
    // programs can use exit status values [1..6] without conflicts
    // with internal dsd_cloud error conditions

    // API specific errors
    dsd_cloud_terminate                           = 110, // dsd_cloud_error_poll_HUP
    dsd_cloud_timeout                             =   7,
    dsd_cloud_error_function_parameter            =   8,
    dsd_cloud_error_read_underflow                =   9,
    dsd_cloud_error_ei_decode                     =  10,
    // reuse some exit status values from os_spawn
    dsd_cloud_invalid_input                       =  11,
    dsd_cloud_out_of_memory                       =  12,
    // reuse some exit status values from GEPD
    dsd_cloud_error_read_EAGAIN                   =  81,
    dsd_cloud_error_read_EBADF                    =  82,
    dsd_cloud_error_read_EFAULT                   =  83,
    dsd_cloud_error_read_EINTR                    =  84,
    dsd_cloud_error_read_EINVAL                   =  85,
    dsd_cloud_error_read_EIO                      =  86,
    dsd_cloud_error_read_EISDIR                   =  87,
    dsd_cloud_error_read_null                     =  88,
    dsd_cloud_error_read_overflow                 =  89,
    dsd_cloud_error_read_unknown                  =  90,
    dsd_cloud_error_write_EAGAIN                  =  91,
    dsd_cloud_error_write_EBADF                   =  92,
    dsd_cloud_error_write_EFAULT                  =  93,
    dsd_cloud_error_write_EFBIG                   =  94,
    dsd_cloud_error_write_EINTR                   =  95,
    dsd_cloud_error_write_EINVAL                  =  96,
    dsd_cloud_error_write_EIO                     =  97,
    dsd_cloud_error_write_ENOSPC                  =  98,
    dsd_cloud_error_write_EPIPE                   =  99,
    dsd_cloud_error_write_null                    = 100,
    dsd_cloud_error_write_overflow                = 101,
    dsd_cloud_error_write_unknown                 = 102,
    dsd_cloud_error_ei_encode                     = 103,
    dsd_cloud_error_poll_EBADF                    = 104,
    dsd_cloud_error_poll_EFAULT                   = 105,
    dsd_cloud_error_poll_EINTR                    = 106,
    dsd_cloud_error_poll_EINVAL                   = 107,
    dsd_cloud_error_poll_ENOMEM                   = 108,
    dsd_cloud_error_poll_ERR                      = 109,
    dsd_cloud_error_poll_HUP                      = 110,
    dsd_cloud_error_poll_NVAL                     = 111,
    dsd_cloud_error_poll_unknown                  = 112
};

#if defined __cplusplus
}
#endif

#endif /* DSD_CLOUD_H */

