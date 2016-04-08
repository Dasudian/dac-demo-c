#ifndef DSD_DSDB_HPP
#define DSD_DSDB_HPP
#include <string>
#include <list>
#include "dsd_cloud.hpp" 


namespace dsd_cloud
{

class dsdb_search_cond
{
    private :
		std::list<std::string> m_conds;
	public :
		dsdb_search_cond()
		{
		    m_conds= std::list<std::string>();
		};
	    virtual ~dsdb_search_cond(){};
		int dsdb_cond_insert(const std::string &key, const std::string &value );
		int dsdb_cond_insert(const std::string &key, float value );
		int dsdb_cond_insert(const std::string &key, const std::string &start, const std::string &end);
		int dsdb_cond_insert(const std::string &key, float start, float end);

		std::list<std::string> dsdb_cond_get_all()
		{
		   
		    return m_conds;
		};
		std::string dsdb_cond_get(int i);
		int dsdb_cond_get_size(){ return m_conds.size();};
		bool dsdb_cond_is_empty()
		{
		    return m_conds.empty();
		};
};

class dsd_dsdb
{
	private:
		const API &m_api;
		std::list<std::string> m_result;
		std::string m_next_id;
		int json2reuslt(std::string &jsons, std::list<std::string> *m_result, std::string *m_next_id);
    public:
        //enum RET_FLAG {SUCCESS=0,ERROR=1};
        static const int SUCCESS=0;
		 static const int ERROR=1;
	public:
		dsd_dsdb(const API &m) :m_api(m){
            m_result = std::list<std::string>();
			 m_next_id = std::string("");
		};
		virtual ~dsd_dsdb(){};

	   int put(const std::string &database, const std::string &key, const std::string &value);

		int get(const std::string &database, const std::string &key); 

		int delete_key(const std::string &database, const std::string &key);

		int search(const std::string &database, const std::string &key, const std::string &value);
		
		int search(const std::string &database, const std::string &key, float value);

		int search_pagination(const std::string &database, const std::string &key, const std::string &value, const std::string &next_seq, int num_per_page);

		int search_pagination(const std::string &database, const std::string &key, float value, const std::string &next_seq, int num_per_page);

		int search_range(const std::string &database, const std::string &key, const std::string &start, const std::string &end);
		
		int search_range(const std::string &database, const std::string &key, float start, float end);

		int search_range_pagination(const std::string &database, const std::string &key, const std::string &start, const std::string &end, const std::string &next_seq, int num_per_page);

		int search_range_pagination(const std::string &database, const std::string &key, float start, float end, const std::string &next_seq, int num_per_page);

		int search_or(const std::string &database, dsdb_search_cond & conditions);

		int search_and(const std::string &database, dsdb_search_cond & conditions);
		
		int search_or_pagination(const std::string &database, dsdb_search_cond & conditions, const std::string &next_seq, int num_per_page);
		
		int search_and_pagination(const std::string &database, dsdb_search_cond & conditions, const std::string &next_seq, int num_per_page);

	    int search_value(const std::string &database, const std::string &key, const std::string &value);

	    int search_value(const std::string &database, const std::string &key, float value);

		int search_value_pagination(const std::string &database, const std::string &key, const std::string &value, const std::string &next_seq, int num_per_page);

		int search_value_pagination(const std::string &database, const std::string &key, float value, const std::string &next_seq, int num_per_page);

		int search_value_range(const std::string &database, const std::string &key, const std::string &start, const std::string &end);
		
		int search_value_range(const std::string &database, const std::string &key, float start, float end);

		int search_value_range_pagination(const std::string &database, const std::string &key, const std::string &start, const std::string &end, const std::string &next_seq, int num_per_page);

		int search_value_range_pagination(const std::string &database, const std::string &key, float start, float end, const std::string &next_seq, int num_per_page);

		int search_value_or(const std::string &database, dsdb_search_cond & conditions);

		int search_value_and(const std::string &database, dsdb_search_cond & conditions);
		
		int search_value_or_pagination(const std::string &database, dsdb_search_cond & conditions, const std::string &next_seq, int num_per_page);
		
		int search_value_and_pagination(const std::string &database, dsdb_search_cond & conditions, const std::string &next_seq, int num_per_page);
		
		int list_all(const std::string &database);

		std::list<std::string> get_result_value()
		{
		    return m_result;
		};
		std::string get_result_page_id()
		{
		    return m_next_id;
		};
		void clean_result()
		{
		    m_result.clear();
			m_next_id.clear();
		};

};


}
#endif
