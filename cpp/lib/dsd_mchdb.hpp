#ifndef DSD_MCHDB_HPP
#define DSD_MCHDB_HPP
#include <string>
#include "dsd_cloud.hpp"
using namespace std;
namespace dsd_cloud
{
    class dsd_mchdb
    {
        public:
            string get_key( const string &service_name, const string &key);

            int  add_key(const string &service_name , const string &key, const string &value);

            int add_key_expiredTime(const string &service_name , const string &key, const string &value,int expire_time);

            int set_key(const string &service_name ,const string &key,const string &value);

            int set_key_expiredTime( const string &service_name , const string &key,const string &value,int expire_time);

            int replace_key( const string &service_name , const string &key, const string &value);

            int delete_key(const string &service_name , const string &key);

			 int prepend(const string &service_name , const string &key, const string &value);
			 
			 int append(const string &service_name , const string &key, const string &value);

            string get_version(const string &service_name);

            //int dsd_memCachDB_quit(dsd_cloud_instance_t * api, char *service_name);

            int flush(const string &service_name); 

            dsd_mchdb(const API &m);
            ~dsd_mchdb();

        private:
            const API &m_api;
    };
}
#endif

