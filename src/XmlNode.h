#ifndef _XML_NODE_DEFINED_
#define _XML_NODE_DEFINED_

#include <string>
#include <vector>
#include <unordered_map>

#ifdef _WIN32
#define EXPORT_ATTR __declspec(dllexport)
#else
#define EXPORT_ATTR
#endif

const class EXPORT_ATTR XmlNode{

public:
	XmlNode();
	XmlNode(const std::string& xmlText);
	~XmlNode();

	static XmlNode ReadFile(const std::string& filename);

	std::string toString();
	XmlNode& getNode(const std::string& key);
	std::vector<XmlNode>& getVector(const std::string& key);
	
	int numberOfTags();
	bool hasTag(const std::string& name);

	XmlNode& operator[] (const std::string& key);
	XmlNode& operator() (const std::string& key, int index);
	operator std::string();

private:
	std::unordered_map<std::string,std::vector<XmlNode>> tags;
	std::string content;
};

#endif