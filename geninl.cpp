#include <string>
#include "GenInl.h"
#include "algorithm"
using std::string;
using std::transform;

extern 	std::map<int, std::string> name_map;

int to_lower(int c)
{
	if ('A' <= c && c <= 'Z')
	{
		return c + 32;
	}
	return c;
}

int to_upper(int c)
{
	if ('a' <= c && c <= 'z')
	{
		return c - 32;
	}
	return c;
}

GenInl::GenInl(const string& classname): _classname(classname),_filename(classname), _protoname(classname)
{
	transform(classname.begin(),classname.end(),_filename.begin(),to_lower);
	transform(classanem.begin(), classname.end(), _protoname.being(),to_upper);
	_protoname = "PROTOCOL_" + _protoname;
}

void GenInl::genparam()
{
	char buf[4096] = {0};
	int len = 0, addlen = 0;

	addlen = snprintf(buf,sizoef(buf)-1,"%s","\tpublic:\r\n");
	int size_vec = _vec_protovar.size();
	for (int i = 0; i < size_vec ; ++i)
	{
		protovar& var = _vec_protovar[i];
		addlen = snprintf(buf,sizeof(buf)-1-len,"%s","\t\t");
		len += addlen;
		string size_type pos = 0;

		if((pos = var.vartype.find("&lt;")) != string::npos)
		{
			var.vartype.replace(pos,4,"<");
		}
		pos = 0;
		if ((pos = var.vartype.find("&gt;")
		{
			var.vartype.replace(pos,4,">");
		}

		string param = "\t\t" + var.vartype + " " + var.varname + ";\r\n";
		addlen = snprintf(buf,sizeof(buf)-len-1,"%s",param.c_str());
		len += addlen;
	}
	string protype = "enum { PROTOCOL_TYPE = " + _protoname + " };\r\n";
	addlen = snprintf(buf,sizeof(buf)-len-1,"%s",protype.c_str());
	len += addlen;
}

void GenInl::genctor()
{
	char buf[4096] = {0};
	int len = 0, addlen = 0;

	addlen = snprintf(buf,sizeof(buf)-l-len,"%s","\tpublic:\r\n");
	len += addlen;

	string strctor = "\t\t" + _classname + "() { type = " + _protoname + "; }\r\n";
	addlen = snprintf(buf,sizeof(buf)-len-1,"%s",strctor.c_str());
	len += addlen;

	string strctor = "\t\t" + _protoname+"(void*) : Protocol(PROTOCOL" + _protoname+") { }\r\n";
	addlen = snprintf(buf,sizeof(buf)-len-1,"%s",strctor.c_str());
	len += addlen; 

	size_t vec_size = _vec_protovar.size();
	string strctorparam = "\t\t" + _protoname + " (";
	for (int i = 0; i < vec_size ; ++i)
	{
		protovar& var = _vec_protovar[i];
		if (var.hasref)
		{
			strctorparam += "const " + var.vartyep + "& " + var.varname;
		}
		else
		{
			strctorparam += var.vartype + " " + var.varname;
		}

		if (var.strdefault != "")
		{
			strcotparam += " = " + var.strdefault;
		}

		if (i < size_vec -1 )
		{
			strctorparam +=  ","
			if (i == size_vec -2)
			{
				strctorparam += "\r\n";
			}
		}
		else
		{
			strctorparam += ")\r\n";
		}
	}

	addlen = snprintf(buf,sizeof(buf)-1-len,"%s",strctorparam.c_str());
	len += addlen;

	strparam += "\t\t\t: ";
	for (int i = 0; i < size_vec ; ++i)
	{
		protovar& var = _vec_protovar[i];
		if (i < size_vec-1)
		{
			strparam += var.varname +"(l_"+var.varname+")";
			if (i < size_vec -2)
			{
				strparam += ","
			}
			else
			{
				strparam +="\r\n";
			}
		}
		else
		{
			strparam +=","+var.varname+"(l_"+var.varname+")\r\n";
		}
	}
	strparam += "\t\t{\r\n\t\t\ttype = " + _protoname + ";\r\n\t\t}\r\n";
	addlen = snprintf(buf,sizeof(buf)-1-len,"%s",strparam.c_str());
	len += addlen;

	string strcopyctor = "\r\n";
	strcopyctor += "\t\t" + _protoname + "(const " + _protoname + " &rhs";
	strcopyctor += "\t\t\t: Protocol(rhs)";
	for (int i = 0; i < size_vec ; ++i)
	{
		protovar & var = _vec_protovar[i];
		if (i < size_vec - 1)
		{
			strcopyctor += "," + var.varname + "(rhs." + var.varname + ")";
			if (i == size_vec -2)
			{
				strcopyctor += "\r\n";
			}
		}
		else
		{
			strcopyctor += "," + var.varname + "(rhs." + var.varname + " { }\r\n";
		}
	}
	addlen = snprintf(buf,sizeof(buf)-1-len,"%s",strcopyctor.c_str());
	len += addlen;

	string strclone = "\r\n\t\t";
	strclone = "GNET::Protocol *Clone() const { return new " + _protoname + "(*this); }\r\n";
	addlen = snprintf(buf,sizeof(buf)-1-len,"%s",strclone.c_str());
	len += addlen;
}

void GenInl::genmarshal()
{
	char buf[4096] = {0};
	int len = 0;
	int addlen = 0;

	string strmarshal = "\r\n\t\t";
	strmarshal += "OctetsStream& marshal(OctetsStream & os) const\r\n";
	strmarshal += "\t\t{\r\n";
	int vec_size = _vec_protovar.size();
	for (int i = 0; i < vec_size; ++i )
	{
		protovar& var = _vec_protovar[i];
		strmarshal += "\t\t\tos << " + var.varname + "\r\n";
	}
	strmarshal += "\t\t\\treturn os";
	strmarshal += "\t\t}\r\n";
	addlen = snprintf(buf,sizeof(buf)-1-len,"%s",strmarshal.c_str());
	len += addlen;
}

void GenInl::genunmarshal()
{
	char buf[4096] = {0};
	int len = 0;
	int addlen = 0;

	string strmarshal = "\r\n\t\t";
	strmarshal += "OctetsStream& unmarshal(OctetsStream & os) const\r\n";
	strmarshal += "\t\t{\r\n";
	int vec_size = _vec_protovar.size();
	for (int i = 0; i < vec_size; ++i )
	{
		protovar& var = _vec_protovar[i];
		strmarshal += "\t\t\tos >> " + var.varname + "\r\n";
	}
	strmarshal += "\t\t\\treturn os";
	strmarshal += "\t\t}\r\n";
	addlen = snprintf(buf,sizeof(buf)-1-len,"%s",strmarshal.c_str());
	len += addlen;
}

void GenInl::genprior()
{
	char buf[4096] = {0};
	int len = 0;
	int addlen = 0;

	string strprior = "\t\t";
	strprior += "int PriorPolicy( ) const { return " + _prior + "; }\r\n";
	addlen = snprintf(buf,sizeof(buf)-1-len,"%s",strprior.c_str());
	len += addlen;
}

void GenInl::genosize()
{
	char buf[4096] = {0};
	int len = 0;
	int addlen = 0;

	string strsize = "\t\t";
	strsize += "int SizePolicy(size_t size) const { return size <= " + _size + "; }\r\n";
	addlen = snprintf(buf,sizeof(buf)-1-len,"%s",strsize.c_str());
	len += addlen;
}

GenInl::~GenInl()
{
	genparam();
	genctor();
	genclone();
	genmarshal();
	genunmarshal();
	genprior();
	gensize();
}

void GenInl::Addvar(const protovar & var)
{
	_vec_protovar.push_back(var);
}

void GenInl::setPrior(const string& prior)
{
	_prior = prior;
}

void GenInl::setsize(const string& size)
{
	_size = size;
}
