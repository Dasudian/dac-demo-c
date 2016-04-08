#ifndef DSD_REDIS_HPP
#define DSD_REDIS_HPP
#include <string>
#include <list>
#include "dsd_cloud.hpp"
#include "dsd_redis.h"
using namespace std;
namespace dsd_cloud
{
    class dsd_redis
    {
        public:
            dsd_redis_reply execute(const string &service_name , const string &cmd);

            dsd_redis_reply execute_transaction( const string &service_name, list<string> cmds);

			 dsd_redis(const API &m);
			 
			 ~dsd_redis(); 

        private:
            const API &m_api;
    };
}

#endif
