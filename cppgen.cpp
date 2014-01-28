#include <cstdio>
#include "tinyxml2.h"

void ParseInlProtocol(XMLDocument* doc);
//void ParseRpcData(XMLDocument* doc);
//void ParseState(XMLDocument* doc);
//void ParseManager(XMLDocument* doc);
//void ParseService(XMLDocument* doc);

std::map<int, std::string> name_map;

int main(int argc, char * argv[])
{
	const char * xml_file = "rpcall.xml";
	if (argc > 1) xml_file = argv[1];
	
	XMLDocument doc;
	doc.LoadFile(xml_file);

	ParseInlProtocol(&doc);
	//ParseRpcData(&doc);
	
	//ParseService(&doc);
	//ParseState(&doc);
	//ParseManager(&doc);

}


void ParseInlProtocol(XMLDocument* doc)
{

	name_map.clear();
	XMLElement * ele = doc.FirstChildElement("protocol");
	for (;ele ; ele = ele->NextSiblingElement("protocol"))
	{
		string protoname (ele->Attribute("name"));
		unsigned protosize = ele->UnsignedAttribute("maxsize");
		int protoprior = ele->IntAttribute("prior");
		int types = ele->IntAttribute("types");
		GenInl inl(protoname);
		inl.setprior(protoprior);
		inl.setsize(protosize);
		if (name_map.find(type) != name_map.end())
		{
			fprintf(stderr,"type is duplatied protocol name = %s\n",protoname.c_str());
			return;
		}
		name_map.insert(std::make_pair(types,"PROTOCOL_" + protoname));
		XMLElement * childele = ele->FirstChildElement();

		for (;childele ; childele = childele->NextSiblingElement())
		{
			protovar var;
			var.varname = childele->Attribute("name");
			var.vartype = childele->Attribute("type");
			bool var.hasref = false;
			char * attr;
			if (attr = childele->Attribute("attr") && strcmp(attr,"ref") == 0)
			{
				var.hasref = true;
			} 
			char *vardefault;
			if (vardefault = childele->Attribute("default"))
			{
				var.strdefault = vardefault;
			}
			inl.addvar(protovar);
		}
	}
}
