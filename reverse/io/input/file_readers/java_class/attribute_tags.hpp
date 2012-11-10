/*  Attribute_Tags.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_ATTRIBUTE_TAGS_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_ATTRIBUTE_TAGS_HPP_INCLUDED

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

	  /*!
	   * \class Attribute_Tags
	   * \date 2007
	   * \author Stephen Torri
	   */
	  class attribute_tags {
	  public:

	    static const std::string source_file;
	    static const std::string constant_value;
	    static const std::string code;
	    static const std::string stack_map_table;
	    static const std::string exceptions;
	    static const std::string inner_classes;
	    static const std::string enclosing_method;
	    static const std::string synthetic;
	    static const std::string signature;
	    static const std::string line_number_table;
	    static const std::string local_variable_table;
	    static const std::string deprecated;
	    static const std::string unknown;
	  };

	} // namespace java_class
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

#endif // ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_ATTRIBUTE_TAGS_HPP_INCLUDED
