/*  Data_Transfer_Base.h

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
  			data_transfer_base.h - Copyright storri

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

#ifndef REVERSE_INFRASTRUCTURE_DATA_SOURCE_DATA_TRANSFER_BASE_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_DATA_SOURCE_DATA_TRANSFER_BASE_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

namespace reverse {
  namespace infrastructure {
    namespace data_source {

      class data_object;

      class data_transfer_base {

      public:

        virtual ~data_transfer_base(){}

        /**
         *
         */
        virtual void close (void) = 0;

        /**
         *
         */
        virtual boost::shared_ptr<data_object const> get (void) const = 0;

        /**
         *
         */
        virtual void open (void) = 0;

        /**
         *
         * @param data
         */
        virtual void put ( boost::shared_ptr< infrastructure::data_source::data_object>& data ) = 0;

      };

    } // namespace data_source
  } // namespace infrastructure
} // namespace reverse

#endif // #ifndef REVERSE_INFRASTRUCTURE_DATA_SOURCE_DATA_TRANSFER_BASE_HPP_INCLUDED

