/*  Attribute_Info.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_ATTRIBUTE_INFO_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_ATTRIBUTE_INFO_HPP_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>

#include <string>

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

	  class class_file;
	  class class_header;

	  /*!
	   * \class Attribute_Info
	   * \date 2007
	   * \author Stephen Torri
	   */
	  class attribute_info
	  {

	  public:

	    virtual ~attribute_info(){}

	    /*!
	     * \brief String representation of JAVA Header
	     * \return String output of header
	     */
	    virtual std::string to_string ( boost::uint16_t index = 0 ) const = 0 ;

	    virtual std::string get_tag (void) const = 0;

	    virtual void read_input ( boost::shared_ptr < const reverse::io::input::file_readers::java_class::class_file>& file_ptr,
				      boost::shared_ptr < const reverse::io::input::file_readers::java_class::class_header>& hdr_ptr ) = 0;

	    virtual bool is_type ( std::string id ) const = 0;

	  };

	} // namespace java_class
      } // namespace file_readers
    } // namespace input 
  } // namespace io
} // namespace reverse

#endif // REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_ATTRIBUTE_INFO_HPP_INCLUDED 
