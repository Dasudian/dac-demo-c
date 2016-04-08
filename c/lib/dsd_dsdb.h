#ifndef DSD_DSDB_H
#define DSD_DSDB_H
#include "dsd_cloud.h" 

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct dsdb_result_s
{
    int length;
    char **result;
    char *next_page_id;
    
}dsdb_result_s;

typedef struct dsdb_cond_item 
{  
     char *cond;
     struct dsdb_cond_item *next;
}dsdb_cond_item;

typedef struct dsdb_search 
{  
     dsdb_cond_item *item;
     int length;
}dsdb_search;


enum
{
    dsd_dsdb_success=0,
    dsd_dsdb_error=1
};
dsdb_search* dsdb_cond_init();

int dsdb_insert_string_cond(dsdb_search *cond, char *key, char *value);

int dsdb_insert_number_cond(dsdb_search *cond, char *key, float value);

int dsdb_insert_range_string_cond(dsdb_search *cond, char *key, char *start, char *end);

int dsdb_insert_range_number_cond(dsdb_search *cond , char *key, float start , float end );

void dsdb_cond_free(dsdb_search *to);

int dsdb_put(dsd_cloud_instance_t * p, char * database, char *key, char *value);

dsdb_result_s* dsdb_get(dsd_cloud_instance_t * p, char* database, char *key); 

int dsdb_delete_key(dsd_cloud_instance_t * p, char *database, char *key);

dsdb_result_s* dsdb_search_string(dsd_cloud_instance_t * p, char *database, char *key, char *value);

dsdb_result_s* dsdb_search_number(dsd_cloud_instance_t * p, char * database, char *key, float value);

dsdb_result_s* dsdb_search_string_pagination(dsd_cloud_instance_t * p, char *database, char *key, char *value, char *next_seq, int num_per_page);

dsdb_result_s* dsdb_search_number_pagination(dsd_cloud_instance_t * p, char *database, char *key, float value, char *next_seq, int num_per_page);

dsdb_result_s* dsdb_search_string_range(dsd_cloud_instance_t * p, char *database, char *key, char *start, char *end);

dsdb_result_s* dsdb_search_number_range(dsd_cloud_instance_t * p, char *database, char *key, float start, float end);

dsdb_result_s* dsdb_search_string_range_pagination(dsd_cloud_instance_t * p, char *database, char *key, char *start, char *end, char *next_seq, int num_per_page);

dsdb_result_s* dsdb_search_number_range_pagination(dsd_cloud_instance_t * p, char *database, char *key, float start, float end, char *next_seq, int num_per_page);

dsdb_result_s* dsdb_search_or(dsd_cloud_instance_t * p, char *database, dsdb_search* conditions);

dsdb_result_s* dsdb_search_and(dsd_cloud_instance_t * p, char *database, dsdb_search* conditions);

dsdb_result_s* dsdb_search_or_pagination(dsd_cloud_instance_t * p, char *database, dsdb_search *conditions, char *next_seq, int num_per_page);

dsdb_result_s* dsdb_search_and_pagination(dsd_cloud_instance_t * p, char *database, dsdb_search* conditions, char *next_seq, int num_per_page);

dsdb_result_s* dsdb_search_value_string(dsd_cloud_instance_t * p, char *database, char *key, char *value);

dsdb_result_s* dsdb_search_value_number(dsd_cloud_instance_t * p, char *database, char *key, float value);

dsdb_result_s* dsdb_search_value_string_pagination(dsd_cloud_instance_t * p, char *database, char *key, char *value, char *next_seq, int num_per_page);

dsdb_result_s* dsdb_search_value_number_pagination(dsd_cloud_instance_t * p, char *database, char *key, float value, char *next_seq, int num_per_page);

dsdb_result_s* dsdb_search_value_string_range(dsd_cloud_instance_t * p, char *database, char *key, char *start, char *end);

dsdb_result_s* dsdb_search_value_number_range(dsd_cloud_instance_t * p, char *database, char *key, float start, float end);

dsdb_result_s* dsdb_search_value_string_range_pagination(dsd_cloud_instance_t * p, char *database, char *key, char *start, char *end, char *next_seq, int num_per_page);

dsdb_result_s* dsdb_search_value_number_range_pagination(dsd_cloud_instance_t * p, char *database, char *key, float start, float end, char *next_seq, int num_per_page);

dsdb_result_s* dsdb_search_value_or(dsd_cloud_instance_t * p, char *database, dsdb_search* conditions);

dsdb_result_s* dsdb_search_value_and(dsd_cloud_instance_t * p, char *database, dsdb_search* conditions);

dsdb_result_s* dsdb_search_value_or_pagination(dsd_cloud_instance_t * p, char *database, dsdb_search *conditions, char *next_seq, int num_per_page);

dsdb_result_s* dsdb_search_value_and_pagination(dsd_cloud_instance_t * p, char *database, dsdb_search *conditions, char *next_seq, int num_per_page);

dsdb_result_s* dsdb_list_all(dsd_cloud_instance_t * p, char *database);

void dsdb_result_free(dsdb_result_s *res);

#ifdef __cplusplus
}
#endif

#endif

