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

#include <reverse/infrastructure/xmlexpatparser.hpp>

namespace reverse {
  namespace infrastructure {


    //=============================================================================
    // Implementation of XMLExpatParser class.
    //=============================================================================
    
    // Initialize static data members 
    std::string          xml_expat_parser::m_start_element     = "";
    std::string          xml_expat_parser::m_end_element       = "";
    std::string          xml_expat_parser::m_char_data         = "";
    bool            xml_expat_parser::m_ignore_white_space = true;
    bool            xml_expat_parser::m_is_char_data_in_cdata_section = false;
    long            xml_expat_parser::m_depth            = 0;
    attribute_map_t xml_expat_parser::m_attributes;
    
    //-----------------------------------------------------------------------------
    // Name       : Default Constructor
    //
    // Description: Initialize member varibles.
    //-----------------------------------------------------------------------------
    xml_expat_parser::xml_expat_parser()
    {
      m_xml_expat_parser      = NULL;
      m_xml_buffer        = NULL;
      
      m_start_element.reserve(255);
      m_end_element.reserve(255);
      m_char_data.reserve(512);
    }

    //-----------------------------------------------------------------------------
    // Name       Destructor
    //
    // Description: Cleanup resources.
    //-----------------------------------------------------------------------------
    xml_expat_parser::~xml_expat_parser()
    {
      destroy_parser();
    }

    //-----------------------------------------------------------------------------
    // Name       : createParser - designed by Allan Saywitz May 21, 2003
    //
    // Description: Create XML Parser.
    //-----------------------------------------------------------------------------
    bool xml_expat_parser::create_parser()
    {

      m_xml_expat_parser = XML_ParserCreate(NULL);

      // Check to see if errror occurred creating parser.
      if ( m_xml_expat_parser == NULL )
	{
	  return false;
	}

      XML_SetUserData ( m_xml_expat_parser, this );
      XML_SetElementHandler ( m_xml_expat_parser, start_element_callback, end_element_callback);
      XML_SetCharacterDataHandler ( m_xml_expat_parser, char_data_callback );
      XML_SetCdataSectionHandler ( m_xml_expat_parser, start_cdata_section_callback, end_cdata_section_callback );

      return true;
    }

    //-----------------------------------------------------------------------------
    // Name       : destroyParser
    //
    // Description: Destroy XML Parser.
    //-----------------------------------------------------------------------------
    void xml_expat_parser::destroy_parser()
    {
      if ( m_xml_expat_parser )  
	{
	  XML_ParserFree ( m_xml_expat_parser );
	  m_xml_expat_parser = NULL;
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
    int xml_expat_parser::parse(const char* buffer, int len) 
    {
      m_xml_buffer = (char*) buffer;
      m_depth     = 0;

      return XML_Parse(m_xml_expat_parser, m_xml_buffer, len, 1);
    }

    XML_Error xml_expat_parser::get_error_code()
    {
      return XML_GetErrorCode ( m_xml_expat_parser );
    }

    //-----------------------------------------------------------------------------
    // Name       : isBlank
    //
    // Description: See if string contains blanks.
    //-----------------------------------------------------------------------------
    bool xml_expat_parser::is_blank ( const char *c )
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

    const char* xml_expat_parser::get_error_string ( XML_Error nErrorCode )
    {
      return XML_ErrorString ( nErrorCode );
    }
    
    int xml_expat_parser::get_current_line_number()
    { 
      return XML_GetCurrentLineNumber(m_xml_expat_parser);
    }

    int xml_expat_parser::get_current_column_number()
    { 
      return XML_GetCurrentColumnNumber(m_xml_expat_parser) + 1;
    }

    int xml_expat_parser::get_depth()
    { 
      return m_depth;
    }

    bool xml_expat_parser::get_ignore_white_space()
    { 
      return m_ignore_white_space;
    }

    void xml_expat_parser::set_ignore_white_space ( bool b )
    { 
      m_ignore_white_space = b;
    }

    bool xml_expat_parser::is_char_data_in_cdata_section()      
    { 
      return m_is_char_data_in_cdata_section;
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
    void xml_expat_parser::start_element_callback(void *user_data, const XML_Char* name, const XML_Char** atts)
    {
      std::string sTempAttributeName;
      std::string sTempAttributeValue;

      // Set start tag name.
      m_start_element = name;

      // Set depth
      ++m_depth;

      // Reset the Is CharData inside of a CDATA Section flag.
      m_is_char_data_in_cdata_section = false;

      // Set start tag attributes.
      m_attributes.clear();

      for (int i = 0; atts[i]; i += 2)
	{

	  sTempAttributeName  = atts[i];
	  sTempAttributeValue = atts[i + 1];

	  m_attributes.insert ( std::make_pair ( sTempAttributeName, sTempAttributeValue ) );

	}


      ( static_cast<xml_expat_parser*>(userData) )->startElement(m_sStartElement, m_attributes);
    }


    //-----------------------------------------------------------------------------
    // Name       : endElementCallback
    //
    // Description: Called by Expat when encounters xml end tag.
    //
    // Note: If on mainframe, must convert text to EBCDIC first because 
    //       Expat XML Parser uses UTF-8 internally.
    //-----------------------------------------------------------------------------
    void xml_expat_parser::endElementCallback(void *userData, const XML_Char* name)
    {
      // Set end tag name.
      m_sEndElement = name;

      // Set depth
      --m_nDepth;

      ( static_cast<xml_expat_parser*>(userData) )->endElement(m_sEndElement);
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
    void xml_expat_parser::charDataCallback(void *userData, const XML_Char* s, int len)
    {
      m_sCharData.assign(s, len);

      if ( (m_bIgnoreWhiteSpace) && (isBlank(m_sCharData.c_str())) )
	{
	  return;
	}

      ( static_cast<xml_expat_parser*>(userData) )->charData(m_sCharData);
    }

    //-----------------------------------------------------------------------------
    // Name       : startCdataSectionCallback
    //
    // Description: Called by Expat when encounters end of CDATA Section.
    //-----------------------------------------------------------------------------
    void xml_expat_parser::startCdataSectionCallback(void *userData)
    {
      // Set the Is CharData inside of a CDATA Section flag.
      m_bIsCharDataInCdataSection = true;


      ( static_cast<xml_expat_parser*>(userData) )->startCdataSection();
    }

    //-----------------------------------------------------------------------------
    // Name       : endCdataSectionCallback
    //
    // Description: Called by Expat when encounters end of CDATA Section.
    //-----------------------------------------------------------------------------
    void xml_expat_parser::endCdataSectionCallback(void *userData)
    {
      // Reset the Is CharData inside of a CDATA Section flag.
      m_bIsCharDataInCdataSection = false;

      ( static_cast<xml_expat_parser*>(userData) )->endCdataSection();
    }

  } // namespace infrastructure
} // namespace reverse

