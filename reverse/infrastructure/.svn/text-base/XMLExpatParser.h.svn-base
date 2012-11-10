/*  XMLExpatParser.h

   Copyright (C) 2008 Stephen Torri

   This file is part of Libreverse.

   Libreverse is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3, or (at your
   option) any later version.

   Libreverse is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see
   <http://www.gnu.org/licenses/>.
*/

// ----------------------------------------------------------------------------
// XMLExpatParser.h: interface for classes: designed by Allan Saywitz May 21, 2003
// -  XMLExpatParser
// ----------------------------------------------------------------------------

#ifndef __XMLEXPATPARSER_H
#define __XMLEXPATPARSER_H

//#pragma warning(disable : 4786)

#include <string>
#include <map>
#include "expat.h"

typedef std::map< std::string, std::string > Attribute_Map_t;

// ----------------------------------------------------------------------------
// class XMLExpatParser
// 
// This class is used to parse an xml character buffer by providing a very
// this wrapper around the Expat XML Parser.
//
// Note: We are currently using version 1.95.2 of Expat XML Parser.
//
//       Expat XML Parser Home Page: http://expat.sourceforge.net
//
// Usage: Simple derive a class from XMLExpatParser and override callbacks.
//
//        class MyParser : public XMLExpatParser
//        {
//           virtual void startElement(const string& sName, const VectorString& attributes);
//           virtual void endElement(const string& sName);
//           virtual void charData(const string& sValue);
//        }
//
//        MyParser parser;
//
//        if (parser.create())
//        {
//           parser.parse(xmlBuffer, length)
//        }
//        
//
// How it works:
//
//   The *userData which expat maintains is simply a pointer to an instance of your object.
//   Then the expat callback functions simply call your object's overridden virtual method.
//   If your object doesn't override a method, the empty method in the base class is called.
//
// Notes:
//    
//   Do not need to call destroy() because it will get called by destructor.
// ----------------------------------------------------------------------------
class XMLExpatParser  
{
public:

	explicit XMLExpatParser();
	virtual ~XMLExpatParser();

	// ----------------------------------------------------------------------------
	// Overridable callbacks
	// --------------------------------------------------------------------------

    // Parametser
    // - first: starting element name
    // - second: list of attributes
	virtual void startElement (const std::string&, const Attribute_Map_t&) {}

    // Parameter
    // - first: ending element name
	virtual void endElement (const std::string&) {}

    // Parameter
    // - first: character data
	virtual void charData(const std::string&) {}

	virtual void startCdataSection() {}
	virtual void endCdataSection() {}

	// ----------------------------------------------------------------------------
	// Create parser
	// --------------------------------------------------------------------------
	bool createParser();

	// ----------------------------------------------------------------------------
	// Destroy parser
	// --------------------------------------------------------------------------
	void destroyParser();

	// ----------------------------------------------------------------------------
	// Parsing function
	// --------------------------------------------------------------------------
	int  parse(const char* buffer, int len);
	
	// ----------------------------------------------------------------------------
	// Informational functions
	// --------------------------------------------------------------------------
	XML_Error
    getErrorCode()
    {
        return XML_GetErrorCode(m_pXMLExpatParser);
    }


	const char* getErrorString ( XML_Error nErrorCode )
    {
        return XML_ErrorString(nErrorCode);
    }

	int         getCurrentLineNumber()             { return XML_GetCurrentLineNumber(m_pXMLExpatParser); }
	int         getCurrentColumnNumber()           { return XML_GetCurrentColumnNumber(m_pXMLExpatParser) + 1; }

	// ----------------------------------------------------------------------------
	// Helper functions
	// --------------------------------------------------------------------------
	int         getDepth()                         { return m_nDepth;            }
	bool        getIgnoreWhiteSpace()              { return m_bIgnoreWhiteSpace; }
	void        setIgnoreWhiteSpace(bool b)        { m_bIgnoreWhiteSpace = b;    }
	bool        isCharDataInCdataSection()         { return m_bIsCharDataInCdataSection; }
	static bool isBlank(const char *c);

private:

	// ----------------------------------------------------------------------------
	// Expat callbacks
	// --------------------------------------------------------------------------
	static void startElementCallback(void *userData, const XML_Char* name, const XML_Char** atts);
	static void endElementCallback(void *userData, const XML_Char* name);
	static void charDataCallback(void *userData, const XML_Char* s, int len);
	static void startCdataSectionCallback(void *userData);
	static void endCdataSectionCallback(void *userData);

private:
	
	// Holds the Expat XML Parser.
	XML_Parser m_pXMLExpatParser;

	// Holds pointer to the xml characters to parse.
	char* m_pXmlBuffer;

	// Holds the xml start tag name.
	static std::string m_sStartElement;

	// Holds the xml end tag name.
	static std::string m_sEndElement;

	// Holds the xml character data.
	static std::string m_sCharData;

	// Holds the xml start tag attributes
	static Attribute_Map_t m_attributes;

	// Holds depth of current xml tag. Root element has depth = 1.
	static long m_nDepth;

	// True if the parser should ignore whitespace.
	static bool m_bIgnoreWhiteSpace;

	// True if the charData was inside of a CDATA section.
	static bool m_bIsCharDataInCdataSection;
};


#endif


