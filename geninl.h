#ifndef __GENINL_H_
#define __GENINL_H_

#include <string>
#include <vector>

struct protovar
{
	string vartype;
	string varname;
	string strdefault;
	bool hasref;
};

class GenInl
{
	private:
			string _classname;
			string _filename;
			string _protoname;
			std::vector<protovar> _vec_protovar;
			string _prior;
			string _size;
			
			char buf[4096];
			int len;
			int addlen;

	public:
		GenInl(const string&  classname);
		~GenInl();
		void addvar(const protovar & var);
		void setprior(const string& prior);
		void setsize(const string& size);
		string& getprotoname()
		{
			return _protoname;
		}

	protected:
		void genparam();
		void genctor();
		void genmarshal();
		void genunmarshal();
		void genprior();
		void gensize();
};
#endif
