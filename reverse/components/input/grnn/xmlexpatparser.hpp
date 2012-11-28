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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_XML_EXPAT_PARSER_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_XML_EXPAT_PARSER_HPP_INCLUDED

//#pragma warning(disable : 4786)

#include "expat.h"

#include <string>
#include <map>

typedef std::map< std::string, std::string > attribute_map_t;

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

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	class xml_expat_parser
	{
	public:
	  
	  explicit xml_expat_parser();
	  virtual ~xml_expat_parser();

	  // ----------------------------------------------------------------------------
	  // Overridable callbacks
	  // --------------------------------------------------------------------------

	  // Parametser
	  // - first: starting element name
	  // - second: list of attributes
	  virtual void start_element ( const std::string&, const attribute_map_t& )
	  {}

	  // Parameter
	  // - first: ending element name
	  virtual void end_element ( const std::string& )
	  {}

	  // Parameter
	  // - first: character data
	  virtual void char_data ( const std::string& )
	  {}

	  virtual void start_cdata_section()
	  {}

	  virtual void end_cdata_section()
	  {}

	  // ----------------------------------------------------------------------------
	  // Create parser
	  // --------------------------------------------------------------------------
	  bool create_parser();

	  // ----------------------------------------------------------------------------
	  // Destroy parser
	  // --------------------------------------------------------------------------
	  void destroy_parser();

	  // ----------------------------------------------------------------------------
	  // Parsing function
	  // --------------------------------------------------------------------------
	  int parse ( const char* buffer, int len );

	  // ----------------------------------------------------------------------------
	  // Informational functions
	  // --------------------------------------------------------------------------
	  XML_Error
	  get_error_code()
	  {
	    return XML_GetErrorCode ( m_pXMLExpatParser );
	  }


	  const char* get_error_string ( XML_Error nErrorCode )
	  {
	    return XML_ErrorString ( nErrorCode );
	  }

	  int get_current_line_number()
	  {
	    return XML_GetCurrentLineNumber ( m_pXMLExpatParser );
	  }
	  int get_current_column_number()
	  {
	    return XML_GetCurrentColumnNumber ( m_pXMLExpatParser ) + 1;
	  }

	  // ----------------------------------------------------------------------------
	  // Helper functions
	  // --------------------------------------------------------------------------
	  int get_depth()
	  {
	    return m_depth;
	  }
	  bool get_ignore_white_space()
	  {
	    return m_ignore_whitespace;
	  }
	  void set_ignore_white_space ( bool b )
	  {
	    m_ignore_whitespace = b;
	  }
	  bool is_char_data_in_cdata_section()
	  {
	    return m_is_char_data_in_cdata_section;
	  }

	  static bool is_blank ( const char *c );

	private:

	  // ----------------------------------------------------------------------------
	  // Expat callbacks
	  // --------------------------------------------------------------------------
	  static void start_element_callback ( void *userData, const XML_Char* name, const XML_Char** atts );
	  static void end_element_callback ( void *userData, const XML_Char* name );
	  static void char_data_callback ( void *userData, const XML_Char* s, int len );
	  static void start_cdata_section_callback ( void *userData );
	  static void end_cdata_section_callback ( void *userData );

	private:

	  // Holds the Expat XML Parser.
	  XML_Parser m_pXMLExpatParser;

	  // Holds pointer to the xml characters to parse.
	  char* m_pxmlbuffer;

	  // Holds the xml start tag name.
	  static std::string m_start_element;

	  // Holds the xml end tag name.
	  static std::string m_end_element;

	  // Holds the xml character data.
	  static std::string m_char_data;

	  // Holds the xml start tag attributes
	  static attribute_map_t m_attributes;

	  // Holds depth of current xml tag. Root element has depth = 1.
	  static long m_depth;

	  // True if the parser should ignore whitespace.
	  static bool m_ignore_whitespace;

	  // True if the charData was inside of a CDATA section.
	  static bool m_is_char_data_in_cdata_section;
	};

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse


#endif // REVERSE_COMPONENTS_INPUT_GRNN_XML_EXPAT_PARSER_HPP_INCLUDED


