#include "XmlNode.h"

using namespace std;

XmlNode::XmlNode()
{
}
XmlNode::~XmlNode()
{
}

XmlNode::XmlNode(const string_view& xmlText)
{
	content = xmlText;

	size_t start = 0;
	size_t end = 0;

	while( start != string::npos && end != string::npos )
	{
		//busco tag
		start = xmlText.find('<', start);

		if(start == string::npos)
			break;

		end = xmlText.find('>',start);

		if(end == string::npos)
			break;

		start+=1; //Salto el <

		string_view tagName = xmlText.substr(start,end-start);
		
		//Salvo la primer línea de la declaracion XML
		if(tagName[0] == '?'){
			start = end;
			continue;
		}

		bool isComment = false;
		if(tagName.substr(0,3) == "!--")
			isComment = true;

		if(isComment)
			end = xmlText.find("-->",start);
		else end = xmlText.find("</" + std::string(tagName) + ">",end);

		if(start == string::npos){
			start = end;
			continue;
		}

		if(!isComment){
			start += tagName.length() + 1; //Salto el nombre del tag y el >

			string_view content = xmlText.substr(start,end-start);

			//Si no existe el vector de nodos, lo creo
			if(this->tags.count(std::string(tagName)) == 0)
				this->tags[std::string(tagName)] = vector<XmlNode>();

			//Agrego recursivamente nodos xml
			this->tags[std::string(tagName)].push_back(XmlNode(content));
		}

		//Paso al siguiente tag
		if(!isComment)
			start = end + tagName.length() + 3;
		else start = end;
	}
}

string XmlNode::toString()
{
	return std::string(this->content);
}

std::string_view XmlNode::toStringView()
{
	return this->content;
}

XmlNode& XmlNode::getNode(const string& key)
{
	return this->tags.at(key).at(0);
}

vector<XmlNode>& XmlNode::getVector(const string& key)
{
	return this->tags.at(key);
}

XmlNode& XmlNode::operator[] (const std::string& key)
{
	return this->getNode(key);
}

XmlNode& XmlNode::operator() (const std::string& key, int index)
{
	return this->getVector(key).at(index);
}

XmlNode::operator std::string()
{
	return std::string(this->content);
}

XmlNode::operator std::string_view()
{
	return this->toStringView();
}

int XmlNode::numberOfTags()
{
	return this->tags.size();
}

bool XmlNode::hasTag(const std::string& name)
{
	return this->tags.count(name);
}