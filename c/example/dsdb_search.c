#include "dsd_cloud.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h> 
#include <limits.h> 
#include <unistd.h>
#include <time.h>
#include "clog.h"
#include "dsd_dsdb.h"

char *logN ="./cdbs.log";
FILE *logF;
void log_w(FILE *fp , char *format ,...)
{
       if(fp ==NULL)
            return;
        
       va_list ap;
       va_start(ap,format);
       if(ap != NULL)
             fprintf(fp,format,ap);
       va_end(ap);
       fflush(fp);
}
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
    int i=0;
    char cmd[12][64]={{0}};
    char *cmds[12]={NULL};
    int flag;
    char key[32]={0,};
    char value[128]={0,};
    char * pslash=NULL;
    int index2=0;
    fprintf(logF,"--------------------\n");
    fflush(logF);
    fprintf(logF,"request is %s\n",(char *)request);
    fflush(logF);
    dsdb_result_s *resp=NULL;
    pslash=strchr((char *)request,'|');
    strncpy(key, (char *)request, pslash-(char *)request);
    strcpy(value, pslash+1);
    
    fprintf(logF,"key is [%s], value is [%s]",key ,value);
    
    resp=dsdb_search_string(api,"/db/dsdb/ocean/my_db", key, value);

    char *value2="12345678";
    if(resp ==NULL){
        fprintf(logF,"search error\n");
        fflush(logF);
        dsd_cloud_return(api, command, name, pattern, "", 0,
                  "search error", strlen("search error"),
                  timeout, trans_id, pid, pid_size);
    }
    else
   {
        for(i=0; i<resp->length; i++)
        {
            fprintf(logF,"result[%d] is [%s]\n",i, *(resp->result+i));
            fflush(logF);
        }
        fprintf(logF,"next id is [%s]",resp->next_page_id);
        fflush(logF);
        dsdb_result_free(resp);
        dsd_cloud_return(api, command, name, pattern, "", 0,
                  value2, strlen(value2),
                  timeout, trans_id, pid, pid_size);
   }
#if 0
    if(rp.err ==0)
    {
       for(i;i<rp.reply_len;i++)
       {
          fprintf(logF,"%02x \n", *((unsigned char *)(rp.reply)+i));
       }
    }
#endif 

}
size_t get_executable_path( char* processdir,char* processname, size_t len) 
{ 
        char* path_end; 
        if(readlink("/proc/self/exe", processdir,len) <=0) 
                return -1; 
        path_end = strrchr(processdir,  '/'); 
        if(path_end == NULL) 
                return -1; 
        ++path_end; 
        strcpy(processname, path_end); 
        *path_end = '\0'; 
        return (size_t)(path_end - processdir); 
}

int main(int argc, char ** argv)
{
    char path[128]={0};
    char name[128]={0};
    char logName[256]={0};
    int flag=0;
    flag=get_executable_path(path, name, 128);
    if(flag <=0)
    {
        
        logF= fopen(logN,"w+");
        clog_init_path(SDK_LOG,logN);
    }
    else
    {
        sprintf(logName,"%s/cdbs.log",path);
        logF=fopen(logName,"w+");
        clog_init_path(SDK_LOG,logName);
    }
    unsigned int thread_count;

    int result = dsd_cloud_initialize_thread_count(&thread_count);
    assert(result == dsd_cloud_success);
    //assert(thread_count == 1);
    fprintf(logF,"start init cloud api\n");
    fflush(logF);
    dsd_cloud_instance_t api;
    result = dsd_cloud_initialize(&api, 0);
    assert(result == dsd_cloud_success);
    fprintf(logF,"start subscribe dbs\n");
    fflush(logF);
    result = dsd_cloud_subscribe(&api, "dbs/post",
                              &hello_world);
	fprintf(logF,"subscribe result %d \n",result);
	fflush(logF);
    assert(result == dsd_cloud_success);
    result = dsd_cloud_poll(&api, -1);
    dsd_cloud_destroy(&api);
    return result;
}
