/*  XMLExpatParser.cpp

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
// XMLExpatParser.h: implementation for classes:
// -  XMLExpatParser
// ----------------------------------------------------------------------------

#include "XMLExpatParser.h"


//=============================================================================
// Implementation of XMLExpatParser class.
//=============================================================================

// Initialize static data members 
std::string          XMLExpatParser::m_sStartElement     = "";
std::string          XMLExpatParser::m_sEndElement       = "";
std::string          XMLExpatParser::m_sCharData         = "";
bool            XMLExpatParser::m_bIgnoreWhiteSpace = true;
bool            XMLExpatParser::m_bIsCharDataInCdataSection = false;
long            XMLExpatParser::m_nDepth            = 0;
Attribute_Map_t XMLExpatParser::m_attributes;

//-----------------------------------------------------------------------------
// Name       : Default Constructor
//
// Description: Initialize member varibles.
//-----------------------------------------------------------------------------
XMLExpatParser::XMLExpatParser()
{
	m_pXMLExpatParser      = NULL;
	m_pXmlBuffer        = NULL;

	m_sStartElement.reserve(255);
	m_sEndElement.reserve(255);
	m_sCharData.reserve(512);
}

//-----------------------------------------------------------------------------
// Name       Destructor
//
// Description: Cleanup resources.
//-----------------------------------------------------------------------------
XMLExpatParser::~XMLExpatParser()
{
	destroyParser();
}

//-----------------------------------------------------------------------------
// Name       : createParser - designed by Allan Saywitz May 21, 2003
//
// Description: Create XML Parser.
//-----------------------------------------------------------------------------
bool XMLExpatParser::createParser()
{

	m_pXMLExpatParser = XML_ParserCreate(NULL);

	// Check to see if errror occurred creating parser.
	if ( m_pXMLExpatParser == NULL )
	{
		return false;
	}

	XML_SetUserData(m_pXMLExpatParser, this);
	XML_SetElementHandler(m_pXMLExpatParser, startElementCallback, endElementCallback);
	XML_SetCharacterDataHandler(m_pXMLExpatParser, charDataCallback);
	XML_SetCdataSectionHandler(m_pXMLExpatParser, startCdataSectionCallback, endCdataSectionCallback);

	return true;
}

//-----------------------------------------------------------------------------
// Name       : destroyParser
//
// Description: Destroy XML Parser.
//-----------------------------------------------------------------------------
void XMLExpatParser::destroyParser()
{
	if (m_pXMLExpatParser)  
	{
		XML_ParserFree(m_pXMLExpatParser);
		m_pXMLExpatParser = NULL;
	}

}

//-----------------------------------------------------------------------------
// Name       : parse
//
// Description: parse the passed in xml buffer.
//
// Note: If on mainframe, must convert entire xml character buffer to ASCII first 
//       because Expat XML Parser doesn't support ebcdic encoding.
//-----------------------------------------------------------------------------
int XMLExpatParser::parse(const char* buffer, int len) 
{
	m_pXmlBuffer = (char*) buffer;
	m_nDepth     = 0;

	return XML_Parse(m_pXMLExpatParser, m_pXmlBuffer, len, 1);
}

//-----------------------------------------------------------------------------
// Name       : isBlank
//
// Description: See if string contains blanks.
//-----------------------------------------------------------------------------
bool XMLExpatParser::isBlank(const char *c)
{
	while ( (*c) != '\0' )
	{
		if ( !isspace(*c) )
		{
			return false;
		}
		++c;
	}
	return true;
}

//=============================================================================
// Expat callbacks
//=============================================================================

//-----------------------------------------------------------------------------
// Name       : startElementCallback
//
// Description: Called by Expat when encounters xml start tag.
//
// Note: If on mainframe, must convert text to EBCDIC first because 
//       Expat XML Parser uses UTF-8 internally.
//-----------------------------------------------------------------------------
void XMLExpatParser::startElementCallback(void *userData, const XML_Char* name, const XML_Char** atts)
{
	std::string sTempAttributeName;
	std::string sTempAttributeValue;

	// Set start tag name.
	m_sStartElement = name;

	// Set depth
	++m_nDepth;

	// Reset the Is CharData inside of a CDATA Section flag.
	m_bIsCharDataInCdataSection = false;

	// Set start tag attributes.
	m_attributes.clear();

	for (int i = 0; atts[i]; i += 2)
	{

		sTempAttributeName  = atts[i];
		sTempAttributeValue = atts[i + 1];

		m_attributes.insert ( std::make_pair ( sTempAttributeName, sTempAttributeValue ) );

	}


	( static_cast<XMLExpatParser*>(userData) )->startElement(m_sStartElement, m_attributes);
}


//-----------------------------------------------------------------------------
// Name       : endElementCallback
//
// Description: Called by Expat when encounters xml end tag.
//
// Note: If on mainframe, must convert text to EBCDIC first because 
//       Expat XML Parser uses UTF-8 internally.
//-----------------------------------------------------------------------------
void XMLExpatParser::endElementCallback(void *userData, const XML_Char* name)
{
	// Set end tag name.
	m_sEndElement = name;

	// Set depth
	--m_nDepth;

	( static_cast<XMLExpatParser*>(userData) )->endElement(m_sEndElement);
}

//-----------------------------------------------------------------------------
// Name       : charDataCallback
//
// Description: Called by Expat when encounters xml character data.
//
// Note: The string (s) returned by Expat is not null terminated.  So we append
//       a null terminator for convenience.

// Note: If on mainframe, must convert text to EBCDIC first because 
//       Expat XML Parser uses UTF-8 internally.
//-----------------------------------------------------------------------------
void XMLExpatParser::charDataCallback(void *userData, const XML_Char* s, int len)
{
	m_sCharData.assign(s, len);

	if ( (m_bIgnoreWhiteSpace) && (isBlank(m_sCharData.c_str())) )
	{
		return;
	}

	( static_cast<XMLExpatParser*>(userData) )->charData(m_sCharData);
}

//-----------------------------------------------------------------------------
// Name       : startCdataSectionCallback
//
// Description: Called by Expat when encounters end of CDATA Section.
//-----------------------------------------------------------------------------
void XMLExpatParser::startCdataSectionCallback(void *userData)
{
	// Set the Is CharData inside of a CDATA Section flag.
	m_bIsCharDataInCdataSection = true;


	( static_cast<XMLExpatParser*>(userData) )->startCdataSection();
}

//-----------------------------------------------------------------------------
// Name       : endCdataSectionCallback
//
// Description: Called by Expat when encounters end of CDATA Section.
//-----------------------------------------------------------------------------
void XMLExpatParser::endCdataSectionCallback(void *userData)
{
	// Reset the Is CharData inside of a CDATA Section flag.
	m_bIsCharDataInCdataSection = false;

	( static_cast<XMLExpatParser*>(userData) )->endCdataSection();
}
