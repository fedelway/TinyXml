#ifndef _XML_NODE_DEFINED_
#define _XML_NODE_DEFINED_

#include <string>
#include <vector>
#include <unordered_map>
#include <string_view>

#ifdef _WIN32
#define EXPORT_ATTR __declspec(dllexport)
#else
#define EXPORT_ATTR
#endif

const class EXPORT_ATTR XmlNode{

public:
	XmlNode();
	XmlNode(const std::string_view& xmlText);
	~XmlNode();

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

private:
	std::unordered_map<std::string,std::vector<XmlNode>> tags;
	std::string_view content;
};

#endif