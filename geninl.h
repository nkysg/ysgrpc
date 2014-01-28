#ifndef __GENINL_H_
#define __GENINL_H_

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

	public:
		GenInl(const string&  classname);
		~GenInl();
		void Addvar(const protovar & var);

	protected:
		void genparam();
		void genctor();
		void genclone();
		void genmarshal();
		void genunmarshal();
		void genprior();
		void gensize();
};

#endif
