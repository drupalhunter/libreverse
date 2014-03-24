/*  File_Data_Source_Config.h

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

/************************************************************************
  			file_data_source_config.h - Copyright storri

Here you can write a license for your code, some comments or any other
information you want to have in your generated code. To to this simply
configure the "headings" directory in uml to point to a directory
where you have your heading files.

or you can just replace the contents of this file with your own.
If you want to do this, this file is located at

/usr/kde/3.2/share/apps/umbrello/headings/heading.h

-->Code Generators searches for heading files based on the file extension
   i.e. it will look for a file name ending in ".h" to include in C++ header
   files, and for a file name ending in ".java" to include in all generated
   java code.
   If you name the file "heading.<extension>", Code Generator will always
   choose this file even if there are other files with the same extension in the
   directory. If you name the file something else, it must be the only one with that
   extension in the directory to guarantee that Code Generator will choose it.

you can use variables in your heading files which are replaced at generation
time. possible variables are : author, date, time, filename and filepath.
just write %variable_name%

This file was generated on Fri Sep 10 2004 at 21:33:48
The original location of this file is 
**************************************************************************/

#ifndef REVERSE_INFRASTRUCTURE_DATA_SOURCE_FILE_DATA_SOURCE_CONFIG_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_DATA_SOURCE_FILE_DATA_SOURCE_CONFIG_HPP_INCLUDED

#include <reverse/infrastructure/data_source/data_source_config_base.hpp>

#include <boost/shared_ptr.hpp>

#include <string>

namespace reverse {
  namespace infrastructure {
    namespace data_source {

      class file_data_source_config : public data_source_config_base {
      public:
	
        explicit file_data_source_config ( std::string prefix = "file" );

        explicit file_data_source_config ( file_data_source_config const& rhs );

        virtual ~file_data_source_config ();

        std::string get_filename (void) const;

        virtual boost::uint32_t get_type() const;

        virtual void set_id ( boost::uint32_t id );

        virtual boost::uint32_t get_id (void) const;

        file_data_source_config& operator= ( file_data_source_config const& rhs );

        void swap ( file_data_source_config& rhs );

    private:

        /**
         * Fields
         */
        boost::uint32_t m_id;

        std::string m_prefix;

        static boost::uint32_t const type;
    };

    } // namespace data_source
  } // namespace infrastructure
} // namespace reverse

#endif //REVERSE_INFRASTRUCTURE_DATA_SOURCE_FILE_DATA_SOURCE_CONFIG_HPP_INCLUDED

