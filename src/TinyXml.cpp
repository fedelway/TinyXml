#include "TinyXml.h"

#include <sstream>
#include <fstream>

TinyXml::TinyXml(const std::string& xmlParam) : xmlText(xmlParam)
{
	xml = XmlNode(xmlText);
}

TinyXml TinyXml::ReadFile(const std::string& filename)
{
	std::ifstream file(filename.c_str());

	std::stringstream buffer;
	buffer << file.rdbuf();

	return TinyXml(buffer.str());
}

std::string TinyXml::toString()
{
	return xml.toString();
}
std::string_view TinyXml::toStringView()
{
	return xml.toStringView();
}

XmlNode& TinyXml::getNode(const std::string& key)
{
	return xml.getNode(key);
}

std::vector<XmlNode>& TinyXml::getVector(const std::string& key)
{
	return xml.getVector(key);
}

int TinyXml::numberOfTags()
{
	return xml.numberOfTags();
}

bool TinyXml::hasTag(const std::string& name)
{
	return xml.hasTag(name);
}

XmlNode& TinyXml::operator[] (const std::string& key)
{
	return xml[key];
}

XmlNode& TinyXml::operator() (const std::string& key, int index)
{
	return xml(key, index);
}

TinyXml::operator std::string()
{
	return (std::string)xml;
}

TinyXml::operator std::string_view()
{
	return (std::string_view)xml;
}

TinyXml::operator XmlNode()
{
	return this->xml;
}