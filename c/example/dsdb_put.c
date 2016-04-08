#include "dsd_cloud.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>  
#include <time.h>
#include "clog.h"
#include "dsd_dsdb.h"

char *logN ="/tmp/cdbp.log";
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
    //int j=0;
    //int k=0;
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
    #if 0
    char *pR=request;
    while(*pR!='\0')
    {
       j=0;
       while( (*pR !='|')&&(*pR !='\0') )
       {
          cmd[i][j]=*pR;
          pR++;
          j++;
       }
       fprintf(logF,"%s \n",cmd[i]);
       fflush(logF);
       i++; 

       if(*pR == '|')
       {
          pR++;
       }
       else{
         break;
       }
  
    }
    if(i==0)
    {
       return ;
    }
    dsd_redis_reply rp;
    fprintf(logF,"================\n");
    fflush(logF);
    
    for(k;k<i;k++)
    {
       fprintf(logF,"%s \n",*(cmd+k));
       fflush(logF);
       cmds[k]=*(cmd+k);
    }
    #endif
    pslash=strchr((char *)request,'|');
    strncpy(key, (char *)request, pslash-(char *)request);
    strcpy(value, pslash+1);
    
    fprintf(logF,"key is [%s], value is [%s]",key ,value);
    
    flag=dsdb_put(api,"/db/dsdb/ocean/my_db", key, value);

    char *value2="12345678";
    if(flag ==dsd_dsdb_error){
        fprintf(logF,"put error\n");
        fflush(logF);
        dsd_cloud_return(api, command, name, pattern, "", 0,
                  "put error", strlen("search error"),
                  timeout, trans_id, pid, pid_size);
    }
    else
   {
            
        dsd_cloud_return(api, command, name, pattern, "", 0,
                  "put success", strlen("put success"),
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
int main(int argc, char ** argv)
{
    logF= fopen(logN,"w+");
    unsigned int thread_count;
    clog_init_path(SDK_LOG,"/tmp/csdk_dbp.log");
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
    result = dsd_cloud_subscribe(&api, "dbp/post",
                              &hello_world);
	fprintf(logF,"subscribe result %d \n",result);
	fflush(logF);
    assert(result == dsd_cloud_success);
    result = dsd_cloud_poll(&api, -1);
    dsd_cloud_destroy(&api);
    return result;
}
