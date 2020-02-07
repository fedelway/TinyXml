#ifndef _TINY_XML_DEFINED_
#define _TINY_XML_DEFINED_

#include <string>
#include "XmlNode.h"

const class TinyXml {

public:
	TinyXml(const std::string& xmlText);

	static TinyXml ReadFile(const std::string& filename);

	std::string toString();
	std::string_view toStringView();
	XmlNode& getNode(const std::string& key);
	std::vector<XmlNode>& getVector(const std::string& key);

	int numberOfTags();
	bool hasTag(const std::string& name);

	XmlNode& operator[] (const std::string& key);
	XmlNode& operator() (const std::string& key, int index);
	operator std::string();
	operator std::string_view();
	operator XmlNode();

private:
	XmlNode xml;
	std::string xmlText;
};

#endif //_TINY_XML_DEFINED_