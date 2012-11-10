/*  Constant_Pool_Info.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_CONSTANT_POOL_INFO_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_CONSTANT_POOL_INFO_HPP_INCLUDED

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

	  class Class_File;

	  /*!
	   * \class Constant_Pool_Info
	   * \date 2007
	   * \author Stephen Torri
	   */
	  class Constant_Pool_Info {

	  public:

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~Constant_Pool_Info(){}

	    virtual boost::uint8_t get_Tag (void) const = 0;

	    virtual std::string to_String (void) const = 0;

	    virtual void read_Input ( boost::shared_ptr < const reverse::io::input::file_readers::java_class::Class_File >& file_ptr ) = 0;

	    virtual bool is_Type ( boost::uint8_t id ) const = 0;

	  };

	} // namespace java_class
      } // namespace file_readers
    } // namespace input 
  } // namespace io
} // namespace reverse

#endif // #ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_CONSTANT_POOL_INFO_HPP_INCLUDED
