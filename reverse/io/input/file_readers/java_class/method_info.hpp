/*  Method_Info.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_METHOD_INFO_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_METHOD_INFO_HPP_INCLUDED

#include <reverse/io/input/file_readers/java_class/class_header.hpp>

#include <string>
#include <vector>

/* Comments for the variables in the class are taken from
   T. Lindholm and F. Yellin
   The Java Virtual Machine Specification Second Edition
   Sun Microsystems
   1999
*/

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace java_class {


	  /*!
	   * \class Method_Info
	   * \date 2007
	   * \author Stephen Torri
	   */
	  class method_info {

	  public:

	    friend class class_file;

	    /*!
	     * \brief Default Constructor
	     */
	    method_info();

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~method_info(){}

	    /*!
	     * \brief String representation of JAVA Header
	     * \return String output of header
	     */
	    std::string to_string ( boost::uint16_t indent_count );

	    boost::uint16_t get_access_flags ( void ) const;

	    /*!
	     * The value of the name_index item must be a valid index into
	     * the constant_pool table. The constant_pool entry at that
	     * index must be a CONSTANT_Utf8_info (§4.4.7) structure
	     * representing either one of the special method names (§3.9),
	     * <init> or <clinit>, or a valid method name in the Java
	     * programming language (§2.7), stored as a simple name
	     * (§2.7.1).
	     */
	    boost::uint16_t get_name_index ( void ) const;

	    std::string get_name_string ( void ) const;

	    /*!
	     * The value of the descriptor_index item must be a valid
	     * index into the constant_pool table. The constant_pool entry
	     * at that index must be a CONSTANT_Utf8_info (§4.4.7)
	     * structure representing a valid method descriptor (§4.3.3).
	     */
	    boost::uint16_t get_descriptor_index ( void ) const;

	    std::string get_descriptor_string ( void ) const;

	    java_class::class_header::attribute_info_map_t::const_iterator attribute_begin(void) const;

	    java_class::class_header::attribute_info_map_t::const_iterator attribute_end(void) const;

	    boost::uint16_t get_attributes_count ( void ) const ;

	  private:

	    /*!
	     * \brief The value of the access_flags item is a mask of
	     * flags used to denote access permission to and properties of
	     * this method.
	     */
	    boost::uint16_t m_access_flags;

	    /*!
	     * \brief The value of the name_index item must be a valid
	     * index into the constant_pool table. The constant_pool entry
	     * at that index must be a CONSTANT_Utf_info structure which
	     * must represent a valid method name stored as a simple name.
	     */
	    boost::uint16_t m_name_index;
	    std::string m_name_string;

	    /*!
	     * \brief The value of the descriptor_index must be a valid
	     * index into the constant_pool table. The constant_pool entry
	     * at that index must be a CONSTANT_Utf8_info structure that
	     * must represent a valid method descriptor.
	     */
	    boost::uint16_t m_descriptor_index;
	    std::string m_descriptor_string;

	    /*!
	     * \brief The value of attributes_count item indicates the
	     * number of additional attributes of this method.
	     */
	    boost::uint16_t m_attributes_count;

	    /*!
	     * \brief Each value of the attributes table must be an
	     * attribute structure. A method can have any number of
	     * attributes associated with it. The attributes defined by
	     * this specification as appearing in the attributes table of
	     * a method_info structure are the ConstantValue, Synthetic,
	     * and Deprecated attributes.
	     */
	    java_class::class_header::attribute_info_map_t m_attributes;
	  };

	} // namespace java_class
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_METHOD_INFO_HPP_INCLUDED
