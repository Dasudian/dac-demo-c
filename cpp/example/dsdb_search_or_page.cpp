#include "dsd_cloud.hpp"
#include "dsd_dsdb.hpp"
#include <string>
#include<fstream>
#include "clog.h"

using namespace std;
using namespace dsd_cloud;
ofstream log;
class cxx_callback : public API::function_object_cxx
{	
public:
	cxx_callback(API &m):m_api(m)
	{
	}
	void operator()(API const &api, int const command, string const &name , string const &pattern, void const * const request_info, uint32_t const request_info_size, void const * const request, uint32_t const request_size, uint32_t timeout, int8_t priority, char const * const trans_id, char const * const pid, uint32_t const pid_size)
	{
		string res=string("hello world");
		int res_size=res.length();
		dsd_dsdb a(api);
		string *pres_s;
		string res_key;
		string res_value;
		string res_page;
		int flag1=0;
		int flag2=0;
		log<<"start operator\n"<<endl;
		log<<"the request is "<<(char *)request<<"\n"<<endl;
		log<<fflush;
       if((request_info ==NULL)||strlen((char *)request_info)==0){
	   	     api.return_(command, name, pattern,(void*)(""),0,"request is null",strlen("request is null"),timeout,trans_id,pid,pid_size);	
	   	}

	   
	   string req_s= string((char *)request);
	   int index1=req_s.find_first_of('|');
	   int index2=req_s.find('|',index1+1);
	   res_key=req_s.substr(0,index1);
	   res_value=req_s.substr(index1+1,index2-index1-1);
	   res_page=req_s.substr(index2+1,req_s.length()-index2-1);


		log<<"key is "<<res_key<<" value is "<<res_value<<" page is "<<res_page<<endl;
		log<<fflush;

 	    dsdb_search_cond s_cond;
	    s_cond.dsdb_cond_insert(string("com"),string("dsd"));
	    s_cond.dsdb_cond_insert(string("first"),string("sunshine"));
		
		flag2=a.search_or_pagination(string("/db/dsdb/ocean/my_db"), s_cond,res_page, 3);
		list<string> res_list;
		list<string>::iterator  it;
		const char *p=api.get_response();
	    if(flag2==dsd_dsdb::SUCCESS)
		{
		     log<<"get next page id "<<a.get_result_page_id()<<endl;
			 res_list=a.get_result_value();
			 it=res_list.begin();
			 for(it;it!=res_list.end(); it++)
			 {
			    log<<"list1 "<<*it<<"\n"<<endl; 
			 }
		}
		int i=0;
		for(i; i<api.get_response_size(); i++)
		{
		    log<<"i"<<i<<":  "<<dec<<int(*(p+i))<<endl;
		}
		api.return_(command, name, pattern,(void*)(""),0,(void*)api.get_response(),api.get_response_size(),timeout,trans_id,pid,pid_size);	
   }

private:
	API & m_api;
};
int main(int args, char **arg)
{ 
      log.open("/tmp/cxxlogand.txt", ios::app);
	   clog_init_path(SDK_LOG,"/tmp/cxxsdkand.log");
	   clog_set_level(SDK_LOG, CLOG_INFO);
      API m=API(0);
      API::function_object_cxx *cb= new cxx_callback(m);
      m.subscribe(string("cxxs_or_page/post"),cb);
      m.poll();
      return 0;
	
}
