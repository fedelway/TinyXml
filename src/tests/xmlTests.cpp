#pragma once

#include "gtest\gtest.h"
#include "../XmlNode.h"

TEST(XmlTests, ParseSimpleXml)
{
	auto xml = XmlNode("<Parent>"
		"<Child>CHILD!</Child>"
		"</Parent>");

	try {
		auto hijoText = xml["Parent"]["Child"].toString();

		ASSERT_EQ(hijoText, "CHILD!");
	}
	catch (...)
	{
		FAIL() << "Should not have thrown";
	}
}

TEST(XmlTests, TestCount)
{
	auto xml = XmlNode("<TAG></TAG>");

	ASSERT_TRUE(xml.hasTag("TAG"));
	ASSERT_FALSE(xml.hasTag("Invalid tag"));
}

TEST(XmlTests, NumberOfTags)
{
	auto oneTag = XmlNode("<TAG></TAG>");
	auto twoTag = XmlNode("<Tag1></Tag1><Tag2><Tag3></Tag3></Tag2>");

	ASSERT_EQ(oneTag.numberOfTags(), 1);
	ASSERT_EQ(twoTag.numberOfTags(), 2);
	ASSERT_EQ(twoTag["Tag2"].numberOfTags(), 1);
}

TEST(XmlTests, WrongXMLShouldNotThrow)
{
	try {
		auto xml = XmlNode("Any text");

		ASSERT_EQ(xml.numberOfTags(), 0);
	}
	catch (...)
	{
		FAIL() << "Should not throw";
	}
}

TEST(XmlTests, EmptyXmlShouldNotThrow)
{
	try {
		auto xml = XmlNode("");

		ASSERT_EQ(xml.numberOfTags(), 0);
	}
	catch (...)
	{
		FAIL() << "Should not throw";
	}
}

TEST(XmlTests, BadlyClosedTag)
{
	auto xml = XmlNode("<parentTag>"
		"<Tag1>"
		"<Tag2>"
		"</Tag1>"
		"</Tag2>"
		"</parentTag>");

	try {
		auto& tagGrande = xml["parentTag"];

		ASSERT_TRUE(tagGrande.hasTag("Tag1"));
		ASSERT_FALSE(tagGrande.hasTag("Tag2"));

		ASSERT_EQ(tagGrande["Tag1"].toString(), "<Tag2>");
	}
	catch (...) {
		FAIL() << "Should not throw";
	}
}

TEST(XmlTests, TagNotFoundShouldThrow)
{
	auto xml = XmlNode("<Tag1></Tag1>");

	ASSERT_ANY_THROW({
		xml["NonExistingTag"];
		});
}

TEST(XmlTests, ImplicitStringConversion) {

	std::string text = "Text";
	auto xml = XmlNode("<Tag1>" + text + "</Tag1>");

	std::string textFromXml = xml["Tag1"];

	ASSERT_EQ(text, textFromXml);
}

TEST(XmlTests, Vector)
{
	auto xml = XmlNode(
		"<Tag1>"
		"<Tag2>1</Tag2>"
		"<Tag2>2</Tag2>"
		"<Tag2>3</Tag2>"
		"</Tag1>");

	auto& vector = xml["Tag1"].getVector("Tag2");

	ASSERT_EQ(vector.size(), 3);
}

TEST(XmlTests, VectorTakesFirst)
{
	auto xml = XmlNode(
		"<Tag1>"
		"<Tag2>1</Tag2>"
		"<Tag2>2</Tag2>"
		"<Tag2>3</Tag2>"
		"</Tag1>");

	ASSERT_EQ(xml["Tag1"]["Tag2"].toString(), "1");
}

TEST(XmlTests, VectorOperator)
{
	auto xml = XmlNode(
		"<Tag1>"
		"<Tag2>1</Tag2>"
		"<Tag2>2</Tag2>"
		"<Tag2>3</Tag2>"
		"</Tag1>");

	ASSERT_EQ(xml["Tag1"]("Tag2", 0).toString(), "1");
	ASSERT_EQ(xml["Tag1"]("Tag2", 1).toString(), "2");
	ASSERT_EQ(xml["Tag1"]("Tag2", 2).toString(), "3");
}

TEST(XmlTests, XmlDeclaration)
{
	auto xml = XmlNode(
		"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
		"<Tag1>"
		"<Tag2>hello</Tag2>"
		"</Tag1>");

	ASSERT_EQ(xml.numberOfTags(), 1);
	ASSERT_TRUE(xml.hasTag("Tag1"));

	ASSERT_EQ(xml["Tag1"]["Tag2"].toString(), "hello");
}