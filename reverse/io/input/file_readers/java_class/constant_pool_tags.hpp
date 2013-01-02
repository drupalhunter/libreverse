/*  Constant_Pool_Tags.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_JAVA_CONSTANT_POOL_TAGS_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_JAVA_CONSTANT_POOL_TAGS_HPP_INCLUDED

#include <boost/cstdint.hpp>
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
	   * \class Constant_Pool_Tags
	   * \date 2007
	   * \author Stephen Torri
	   */
	  class constant_pool_tags {

	  public:

	    static const boost::uint16_t utf8_tag;    // 0x1
	    static const boost::uint16_t reserved_tag; // 0x2
	    static const boost::uint16_t integer_tag; // 0x3
	    static const boost::uint16_t float_tag;   // 0x4
	    static const boost::uint16_t long_tag;    // 0x5
	    static const boost::uint16_t double_tag;  // 0x6
	    static const boost::uint16_t class_tag;   // 0x7
	    static const boost::uint16_t string_tag;  // 0x8
	    static const boost::uint16_t field_ref_tag; //0x9
	    static const boost::uint16_t method_ref_tag; // 0xa
	    static const boost::uint16_t interface_method_ref_tag; // 0xb
	    static const boost::uint16_t name_and_type_tag; // 0xc

	    static bool is_valid_tag ( boost::uint16_t id );
	  };

	} // namespace java_class
      } //       namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

#endif /* ifdef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_JAVA_CONSTANT_POOL_TAGS_HPP_INCLUDED */
