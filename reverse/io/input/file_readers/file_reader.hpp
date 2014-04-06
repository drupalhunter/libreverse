/*  File_Reader.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_FILE_READERS_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_FILE_READERS_HPP_INCLUDED


#include <reverse/data_containers/memory_map.hpp>

#include <boost/shared_ptr.hpp>

#include <unicode/ustring.h>

#include <string>

namespace reverse {
  namespace io {
        
    class file_reader
    {
    public:

        typedef boost::shared_ptr<file_reader> ptr_t;

        virtual ~file_reader(){}

        virtual bool support_file_type () = 0;

        virtual void read_headers (void) = 0;

        virtual boost::shared_ptr < data_containers::memory_map > get_memory_map ( void ) = 0;

	virtual std::string get_file_type (void) = 0;

        /** 
         * Dump content of reader as a text string
         */
        virtual std::string to_string (void) = 0;

        /** 
         * Obtain an iterator pair to a list of human readable text
         * strings found in the binary file. First iterator points to
         * the first element in the list. The second iterator points
         * to the after the last element in the list.
         */
      virtual std::vector<std::string> get_text_strings (void) = 0;

        /** 
         * Obtain an iterator pair to a list of UTF-16 text strings
         * found in the binary file. First iterator points to the
         * first element in the list. The second iterator points to
         * the after the last element in the list.
         *
         * For now the locale will be the default locale for the
         * system.
         */
      virtual std::vector<std::string> get_utf16_strings (void) = 0;

        // Each reader needs to:
        // - Have a File class that inherits from io::File
        // - Store prepared memory map of the load segments/sections

    private:

        /*
          This was put here in case we wanted to grab stuff by section
          name (e.g. 'code' ). This can work for Elf and Windows PE
          files but not Java. At least not yet. We do not know what
          the equivalent section names are for Java class files since
          the file format is not that well understood.
        */
        virtual std::string get_section_string ( std::string name ) const = 0;

    };

  } // namespace io
} // namespace reverse

// TODO: Make file readers serializable
// BOOST_IS_ABSTRACT(reverse::io::File_Reader)

#endif // REVERSE_IO_INPUT_FILE_READERS_FILE_READERS_HPP_INCLUDED 

