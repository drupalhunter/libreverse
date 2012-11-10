/*  Code_Attribute.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_CODE_ATTRIBUTE_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_CODE_ATTRIBUTE_HPP_INCLUDED

#include <reverse/io/input/file_readers/java_class/attribute_info.hpp>

#include <boost/enable_shared_from_this.hpp>

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
	  class class_file;
	  class exception_table_entry;
	  
	  /*!
	   * \class Code_Attribute
	   * \date 2007
	   * \author Stephen Torri
	   */
	  class code_attribute : public attribute_info,
				 public boost::enable_shared_from_this<code_attribute>
	  {
	  public:

            typedef std::vector<boost::uint8_t> code_list_t;

            typedef std::vector< boost::shared_ptr < const reverse::io::input::file_readers::java_class::attribute_info > > attribute_table_t;

            typedef std::vector< boost::shared_ptr < const reverse::io::input::file_readers::java_class::exception_table_entry > > exception_table_t;

	    friend class class_file;

	    /*!
	     * \brief Default Constructor
	     */
	    code_attribute ( boost::uint16_t index );

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~code_attribute(){}

	    /*!
	     * \brief String representation of JAVA Header
	     * \return String output of header
	     */
	    virtual std::string to_string ( boost::uint16_t index = 0 ) const;

	    virtual std::string get_tag (void) const;

	    virtual void read_input ( boost::shared_ptr < const reverse::io::input::file_readers::java_class::class_file >& file_ptr,
				      boost::shared_ptr < const reverse::io::input::file_readers::java_class::class_header >& hdr_ptr );

	    virtual bool is_type ( std::string id ) const;

	    boost::uint16_t get_name_index (void) const;

	    std::string get_attribute_name (void) const; 
          
	    boost::uint32_t get_attribute_length (void) const;

	    boost::uint16_t get_max_stack (void) const;

	    boost::uint16_t get_max_locals (void) const;

	    boost::uint32_t get_code_length (void) const;

	    code_list_t::const_iterator get_code_begin (void) const;

	    code_list_t::const_iterator get_code_end (void) const;

	    code_list_t::const_iterator get_code_iterator ( boost::uint32_t index ) const;

	    boost::uint8_t get_code ( boost::uint32_t index ) const;

	    boost::uint16_t get_exception_table_length (void) const;

	    exception_table_t::const_iterator get_exception_table_begin (void) const;

	    exception_table_t::const_iterator get_exception_table_end (void) const;

	    boost::uint16_t get_attributes_count (void) const;

	    attribute_table_t::const_iterator get_attributes_begin (void) const;

	    attribute_table_t::const_iterator get_attributes_end (void) const;

	  private:

	    boost::uint16_t m_name_index;

	    std::string m_attribute_name;

	    boost::uint32_t m_attribute_length;

	    /*!
	     * \brief The value of the max_stack item gives the maximum
	     * depth of the operand stack of this method at any point
	     * during execution of the method.
	     */
	    boost::uint16_t m_max_stack;

	    /*!
	     * \brief The value of the max_stack item gives the maximum
	     * depth of the operand stack of this method at any point
	     * during execution of the method.
	     */
	    boost::uint16_t m_max_locals;

	    /*!
	     * \brief The value of the code_length item gives the number of
	     * bytes in the code array for this method. The value of
	     * code_length must be greater than zero; the code array must
	     * not be empty.
	     */
	    boost::uint32_t m_code_length;

	    /*!
	     * \brief The code array gives the actual bytes of Java virtual
	     * machine code that implement the method.
	     */
	    code_list_t m_code;

	    /*!
	     * The value of the exception_table_length item gives the
	     * number of entries in the exception_table table.
	     */
	    boost::uint16_t m_exception_table_length;

	    /*!
	     * \brief Each entry in the exception_table array describes
	     * one exception handler in the code array. The order of the
	     * handlers in the exception_table array is
	     * significant.
	     */
	    exception_table_t m_exception_table;

	    /*!
	     * \brief The value of the attributes_count item indicates the
	     * number of attributes of the Code attribute.
	     */
	    boost::uint16_t m_attributes_count;

	    /*!
	     * \brief Each value of the attributes table must be an
	     * attribute structure.  A Code attribute can have any number
	     * of optional attributes associated with it.
	     *
	     * Currently, the LineNumberTable and
	     * LocalVariableTable,attributes which contain debugging
	     * information, as well as the StackMapTable attribute, are
	     * defined and used with the Code attribute.
	     *
	     * A Java virtual machine implementation is permitted to
	     * silently ignore any or all attributes in the attributes
	     * table of a Code attribute, except for the StackMapTable
	     * attribute, which must be recognized if the class file
	     * version number is 50.0 or above. Attributes not defined in
	     * this specification are not allowed to affect the semantics
	     * of the class file, but only to provide additional
	     * descriptive information.
	     */
	    attribute_table_t m_attributes;

	  };

	} // namespace java_class
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

#endif // #ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_CODE_ATTRIBUTE_HPP_INCLUDED
