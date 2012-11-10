/*  Class_Header.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_CLASS_HEADER_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_CLASS_HEADER_HPP_INCLUDED

#include <reverse/io/input/file_readers/base_header.hpp>

#include <unicode/ustring.h>

#include <map>
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

	  class attribute_info;
	  class constant_pool_info;
	  class field_info;
	  class method_info;

	  /*!
	   * \class Class_Header
	   * \date 2003
	   * \author Stephen Torri
	   */
	  class class_header : public reverse::io::input::base_header {
	  public:

            typedef std::vector<boost::uint16_t> interfaces_list_t;

            typedef std::map < boost::uint16_t,
	      boost::shared_ptr< reverse::io::input::file_readers::java_class::constant_pool_info >
	      > constant_pool_info_map_t;

            typedef std::map < boost::uint16_t,
	      boost::shared_ptr< reverse::io::input::file_readers::java_class::field_info >
	      > field_info_map_t;

            typedef std::map < boost::uint16_t,
	      boost::shared_ptr< reverse::io::input::file_readers::java_class::method_info >
	      > method_info_map_t;

            typedef std::map < boost::uint16_t,
	      boost::shared_ptr< reverse::io::input::file_readers::java_class::attribute_info >
	      > attribute_info_map_t;

	    friend class class_file;

	    static boost::uint32_t const class_magic_signature;

	    /*!
	     * \brief Default Constructor
	     */
	    class_header();

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~class_header(){}

	    /*!
	     * \brief Change the bit-ordering if required
	     */
	    virtual void convert ();

	    /*!
	     * \brief String representation of JAVA Header
	     * \return String output of header
	     */
	    std::string to_string (void) const;

	    bool is_java_file (void) const;

	    std::string get_string_constant ( boost::uint16_t val ) const;

	    boost::uint32_t get_magic_number() const;

	    boost::uint16_t get_minor_version () const;

	    boost::uint16_t get_major_version () const;

	    double get_version () const;

	    boost::uint16_t get_constant_pool_count () const;

	    constant_pool_info_map_t::const_iterator
	    get_constant_pool_begin() const;

	    constant_pool_info_map_t::const_iterator
	    get_constant_pool_end() const;

	    constant_pool_info_map_t::const_iterator
	    get_constant_pool_item ( boost::uint16_t index );

	    boost::uint16_t get_access_flags() const;

	    boost::uint16_t get_this_class() const;

	    boost::uint16_t get_super_class() const;

	    boost::uint16_t get_interfaces_count () const;

	    interfaces_list_t::const_iterator get_interfaces_begin() const;

	    interfaces_list_t::const_iterator get_interfaces_end() const;

	    boost::uint16_t get_field_count () const;

	    field_info_map_t::const_iterator get_field_begin() const;

	    field_info_map_t::const_iterator get_field_end() const;

	    boost::uint16_t get_method_count () const;

	    method_info_map_t::const_iterator get_method_begin() const;

	    method_info_map_t::const_iterator get_method_end() const;

	    boost::uint16_t get_attribute_count () const;

	    attribute_info_map_t::const_iterator get_attribute_begin() const;

	    attribute_info_map_t::const_iterator get_attribute_end() const;

	    std::vector < std::string > get_text_strings() const;

	    std::vector<UChar> get_raw_strings() const;

	  private:

	    /*!
	     * \brief The magic item supplies the magic number
	     * identifying the class file format.
	     */
	    boost::uint32_t m_magic;

	    /*!
	     * \brief The values of the minor_version and major_version
	     * items are the minor and major version numbers of this class
	     * file. Together, a major and minor version number determine
	     * the version of the class file format. If a class file has
	     * major version number M and a minor version number m, we
	     * denote the version of its class file format as M.m.
	     */
	    boost::uint16_t m_minor_version;
	    boost::uint16_t m_major_version;

	    /*!
	     * \brief The value of the constant_pool_count item is equal
	     * to the number of entries in the constant_pool table plus
	     * one.
	     */
	    boost::uint16_t m_constant_pool_count;

	    /*!
	     * \brief The constant_pool is a table of structures
	     * representing various string constants, class, and interface
	     * names, field names, and other constants that are referred
	     * to within the ClassFile structure.
	     */
	    constant_pool_info_map_t m_constant_pool;

	    /*!
	     * \brief The value of the access_flags item is a mask of
	     * flags used to denote access permissions to and properties
	     * of this class or interface.
	     */
	    boost::uint16_t m_access_flags;

	    /*!
	     * \brief The value of this_class item must be a valid index
	     * into the constant_pool table. The constant_pool entry at
	     * that index must be a CONSTANT_Class_info structure
	     * representing the class or interface defined by this class
	     * file.
	     */
	    boost::uint16_t m_this_class;

	    /*!
	     * \brief For a class, the value of the super_class item
	     * either must be zero or must be a valid index into the
	     * constant_pool table. If the value is non-zero, the
	     * constant_pool entry at that index must be a
	     * CONSTANT_Class_info structure representing the direct
	     * superclass of teh class defined by this class file. Neither
	     * the direct superclass nor any of its superclasses may be a
	     * final class.  interface defined by this class file.
	     */
	    boost::uint16_t m_super_class;

	    /*!
	     * \brief The value of the interfaces_count item gives the
	     * number of direct superinterfaces of this class or interface
	     * type.
	     */
	    boost::uint16_t m_interfaces_count;

	    /*!
	     * \brief Each value in the interfaces array must be a valid
	     * index into the constant_pool table.
	     */
	    interfaces_list_t m_interfaces;

	    /*!
	     * \brief The value of the fields_count item gives the number
	     * of field_info structures in the fields table.
	     */
	    boost::uint16_t m_field_count;

	    /*!
	     * \brief Each value in the fields table must be a field_info
	     * structure giving a complete description of a field in this
	     * class or interface.
	     */
	    field_info_map_t m_fields;

	    /*!
	     * \brief The value of the methods_count item gives the number
	     * of method_info structures in the methods table.
	     */
	    boost::uint16_t m_methods_count;

	    /*!
	     * \brief Each value in the methods table must be a
	     * method_info structure giving a complete description of a
	     * method in this class or interface.
	     */
	    method_info_map_t m_methods;

	    /*!
	     * \brief The value of the attributes_count item gives the
	     * number of attribute_info structures in the attributes
	     * table.
	     */
	    boost::uint16_t m_attributes_count;

	    /*!
	     * \brief Each value in the attributes table must be a
	     * attribute_info structure giving a complete description of a
	     * attribute in this class or interface.
	     */
	    attribute_info_map_t m_attributes;

	  };

	} // namespace java_class
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

#endif // #ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_CLASS_HEADER_HPP_INCLUDED
