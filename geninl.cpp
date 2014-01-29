#include <map>
#include "geninl.h"
#include "algorithm"
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
	len = addlen = 0;
}

void GenInl::genparam()
{
	addlen = snprintf(buf+len,sizoef(buf)-1-len,"%s","\tpublic:\n");
	len += addlen;
	int size_vec = _vec_protovar.size();
	for (size_t i = 0; i < size_vec ; ++i)
	{
		protovar& var = _vec_protovar[i];

		string::size_type pos = 0;
		if((pos = var.vartype.find("&lt;")) != string::npos)
		{
			var.vartype.replace(pos,4,"<");
		}
		pos = 0;
		if ((pos = var.vartype.find("&gt;")
		{
			var.vartype.replace(pos,4,">");
		}

		string param = "\t\t" + var.vartype + " " + var.varname + ";\n";
		addlen = snprintf(buf + len,sizeof(buf)-len-1,"%s",param.c_str());
		len += addlen;
	}
	string protype = "\t\tenum { PROTOCOL_TYPE = " + _protoname + " };\n";
	addlen = snprintf(buf+len,sizeof(buf)-len-1,"%s",protype.c_str());
	len += addlen;
}

void GenInl::genctor()
{
	addlen = snprintf(buf+len,sizeof(buf)-l-len,"%s","\tpublic:\n");
	len += addlen;

	string strctor = "\t\t" + _classname + "() { type = " + _protoname + "; }\n";
	addlen = snprintf(buf+len,sizeof(buf)-len-1,"%s",strctor.c_str());
	len += addlen;

	string strctor = "\t\t" + _protoname+"(void*) : Protocol(" + _protoname+") { }\n";
	addlen = snprintf(buf+len,sizeof(buf)-len-1,"%s",strctor.c_str());
	len += addlen; 

	size_t vec_size = _vec_protovar.size();
	string strctorparam = "\t\t" + _classname + " (";
	if (vec_size % 3)
	{
		for (size_t i = 0; i < vec_size ; ++i)
		{
			protovar& var = _vec_protovar[i];
			string strvar;
			if (var.hasref)
			{
				strvar = "const " + var.vartyep + "& l_" + var.varname;
			}
			else
			{
				strvar = var.vartype + " l_" + var.varname;
			}

			if (var.strdefault != "")
			{
				strvar += " = " + var.strdefault;
			}

			if (i < vec_size/3 * 3)
			{
				if (i % 3 == 2)
				{
					strvar += ",\n";
				}
				else
				{
					strvar += ",";
					if (i % 3 == 0 && i >= 3)
					{
						strvar += "\t\t\t" + strvar;
					}
				}
			}
			else
			{
				if (i == vec_size -1)
				{	
					strvar += ")\n";
				}
				else
				{
					strvar += ",";
				}
				if (i % 3 == 0 && i >= 3)
				{
					strvar = "\t\t\t" + strvar;
				}
			}
			strctorparam += strvar;
		}	
	}
	else
	{
		for (size_t i = 0; i < vec_size ; ++i)
		{
			protovar& var = _vec_protovar[i];
			string strvar;
			if (var.hasref)
			{
				strvar = "const " + var.vartyep + "& l_" + var.varname;
			}
			else
			{
				strvar = var.vartype + " l_" + var.varname;
			}

			if (var.strdefault != "")
			{
				strvar += " = " + var.strdefault;
			}

			if (i != vec_size -1 )
			{
				strvar +=  ","
				if (i % 3 == 2)
				{
					strvar += "\n";
				}
				if (i % 3 == 0 && i >= 3)
				{
					strvar = "\t\t\t" + strvar;
				}
			}
			else
			{
				strvar += ")\n";
			}
			strctorparam += strvar;
		}
	}

	addlen = snprintf(buf+len,sizeof(buf)-1-len,"%s",strctorparam.c_str());
	len += addlen;

	strparam += "\t\t\t : ";
	for (size_t i = 0; i < vec_size ; ++i)
	{
		protovar& var = _vec_protovar[i];
		string strvar = var.varname +"(l_"+var.varname+")";
		if (i >０)
		{
			strvar = "," + strvar;
			if (i % 3 == 0 && i >= 3)
			{
				strvar = "\t\t\t" + strvar;
			}
			if (i % 3 == 2 || i == vec_size -1)
			{
				strvar += "\n";
			}
		}
		if (vec_size == 1)
		{
			strvar += "\n";
		}
		strparam += strvar;
	}
	strparam += "\t\t{\n\t\t\ttype = " + _protoname + ";\n\t\t}\n";
	addlen = snprintf(buf+len,sizeof(buf)-1-len,"%s",strparam.c_str());
	len += addlen;

	string strcopyctor = "\n";
	strcopyctor += "\t\t" + _protoname + "(const " + _protoname + " &rhs)\n";
	strcopyctor += "\t\t\t: Protocol(rhs)";
	for (size_t i = 0; i < vec_size ; ++i)
	{
		protovar & var = _vec_protovar[i];
		string strvar = "," + var.varname + "(rhs." + var.varname + ")";
		if (i % 3 == 0 && i >= 3)
		{
			strvar = "\t\t\t" + strvar;
		}
		if (i % 3 == 2 || i == vec_size -1)
		{
			if (i == vec_size - 1)
			{
				strvar += " { }";
			}
			strvar += "\n";
		}
		strcopyctor += strvar;
	}
	addlen = snprintf(buf+len,sizeof(buf)-1-len,"%s",strcopyctor.c_str());
	len += addlen;

	string strclone = "\n\t\t";
	strclone = "GNET::Protocol *Clone() const { return new " + _protoname + "(*this); }\n";
	addlen = snprintf(buf+len,sizeof(buf)-1-len,"%s",strclone.c_str());
	len += addlen;
}

void GenInl::genmarshal()
{
	string strmarshal = "\n\t\t";
	strmarshal += "OctetsStream& marshal(OctetsStream & os) const\n";
	strmarshal += "\t\t{\n";
	int vec_size = _vec_protovar.size();
	for (int i = 0; i < vec_size; ++i )
	{
		protovar& var = _vec_protovar[i];
		strmarshal += "\t\t\tos << " + var.varname + "\n";
	}
	strmarshal += "\t\t\\treturn os;\n";
	strmarshal += "\t\t}\n";
	addlen = snprintf(buf+len,sizeof(buf)-1-len,"%s",strmarshal.c_str());
	len += addlen;
}

void GenInl::genunmarshal()
{
	string strmarshal = "\n\t\t";
	strmarshal += "OctetsStream& unmarshal(const OctetsStream & os)\n";
	strmarshal += "\t\t{\n";
	int vec_size = _vec_protovar.size();
	for (int i = 0; i < vec_size; ++i )
	{
		protovar& var = _vec_protovar[i];
		strmarshal += "\t\t\tos >> " + var.varname + "\n";
	}
	strmarshal += "\t\t\treturn os;\n";
	strmarshal += "\t\t}\n";
	addlen = snprintf(buf+len,sizeof(buf)-1-len,"%s",strmarshal.c_str());
	len += addlen;
}

void GenInl::genprior()
{
	if (_prior == "0")
	{
		return;
	}
	string strprior = "\n\t\t";
	strprior += "int PriorPolicy( ) const { return " + _prior + "; }\n";
	addlen = snprintf(buf+len,sizeof(buf)-1-len,"%s",strprior.c_str());
	len += addlen;
}

void GenInl::genosize()
{

	string strsize = "\n\t\t";
	strsize += "bool SizePolicy(size_t size) const { return size <= " + _size + "; }\r\n";
	addlen = snprintf(buf+len,sizeof(buf)-1-len,"%s",strsize.c_str());
	len += addlen;
}

GenInl::~GenInl()
{
	genparam();
	genctor();
	genmarshal();
	genunmarshal();
	genprior();
	gensize();

	string strfile = "inl/" + _filename;
	FILE * fp = fopen(strfile.c_str(),"wb");
	fwrite(buf,1,len,fp);
	fclose(fp);
}

void GenInl::addvar(const protovar & var)
{
	_vec_protovar.push_back(var);
}

void GenInl::setprior(const string& prior)
{
	_prior = prior;
}

void GenInl::setsize(const string& size)
{
	_size = size;
}
