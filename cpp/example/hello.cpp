#include "dsd_cloud.hpp"
#include <string>
#include<fstream>
#include "dsd_log.h"

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
        dsd_log_info("hello in %s ",res.c_str());
	    api.return_(command, name, pattern,(void*)(""),0,(void*)(res.c_str()),res.length(),timeout,trans_id,pid,pid_size);	
   }

private:
	API & m_api;
};
int main(int args, char **arg)
{ 
	
	 dsd_log_init();
     dsd_log_set_level(CLOG_DEBUG);
     dsd_log_info("start log test in cxx");
	  API m=API(0);
      API::function_object_cxx *cb= new cxx_callback(m);
      m.subscribe(string("cxxhello/get"),cb);
      m.poll();
      return 0;
	
}
