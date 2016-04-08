#include "dsd_cloud.hpp"
#include "dsd_dsdb.hpp"
#include <string>
#include <list>
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
		//string *pres_s;
		string res_key;
		string res_value;
		list<string> res_list;
		int flag1=0;
		int flag2=0;
		log<<"start operator\n"<<endl;
		log<<"the request is "<<(char *)request<<"\n"<<endl;
		log<<fflush;
       if((request_info ==NULL)||strlen((char *)request_info)==0){
	   	     api.return_(command, name, pattern,(void*)(""),0,"request is null",strlen("request is null"),timeout,trans_id,pid,pid_size);	
	   	}

	   
		string req_s= string((char *)request);
		int index=req_s.find_first_of('|');
		res_key=req_s.substr(0,index);
		res_value=req_s.substr(index+1,req_s.length()-index-1);

		log<<"key is "<<res_key<<"value is "<<res_value<<endl;
		log<<fflush;
		//flag2=a.put(string("/db/dsdb/ocean/my_db"),string("octestb"),string("{\"oc\":\"zhang\",\"oh\":\"hai\"}"));
		//flag2=a.put(string("/db/dsdb/ocean/my_db"),res_key,res_value);
#if 0
		if(flag2!=DSD_dsdb::SUCCESS){
			log<<"put  return error\n"<<endl;
			log<<fflush;
		}
		else
		{
		   log<<"put  return success\n"<<endl;
		   log<<fflush;
		}
#endif
		flag2=a.search(string("/db/dsdb/ocean/my_db"), res_key, res_value);
        list<string>::iterator  it;
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
		//pres_s=a.get(string("/db/dsdb/ocean/my_db"),res_key);
		//og<<"get octest_4"<<*pres_s<<"\n"<<endl;
		//delete pres_s;
		api.return_(command, name, pattern,(void*)(""),0,(void*)api.get_response(),api.get_response_size(),timeout,trans_id,pid,pid_size);	
   }

private:
	API & m_api;
};
int main(int args, char **arg)
{ 
      log.open("/tmp/cxxlog4.txt", ios::app);
	   clog_init_path(SDK_LOG,"/tmp/cxxsdk4.log");
	   clog_set_level(SDK_LOG, CLOG_INFO);
      API m=API(0);
      API::function_object_cxx *cb= new cxx_callback(m);
      m.subscribe(string("cxxs/post"),cb);
      m.poll();
      return 0;
	
}
