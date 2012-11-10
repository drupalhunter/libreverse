/*  File_Data_Transfer.h

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
  			file_data_transfer.h - Copyright storri

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

#ifndef FILE_DATA_TRANSFER_H
#define FILE_DATA_TRANSFER_H

#include "Data_Transfer_Base.h"
#include "infrastructure/Component_Types.h"

namespace libreverse { namespace infrastructure {

    class File_Data_Transfer : public Data_Transfer_Base {
    public:

        struct variant_saver
        {
            typedef void result_type;

            template<typename Archive, typename Type>
            void operator ()( Archive & a, Type const & t ) const
            {
                a << t;
            }
        };

        explicit File_Data_Transfer( infrastructure_types::File_Data_Source_Config::const_ptr_t config );

        virtual ~File_Data_Transfer(){}

        /**
         *
         */
        virtual void close ();

        /**
         *
         */
        virtual infrastructure_types::Data_Object::const_ptr_t get () const;

        /**
         *
         */
        virtual void open ();

        /**
         *
         * @param data
         */
        virtual void put ( infrastructure_types::Data_Object::const_ptr_t data);

    private:

        infrastructure_types::File_Data_Source_Config::const_ptr_t m_config;
        
        infrastructure_types::Data_Object::ptr_t m_data;

    };
} /* namespace infrastructure */
} /* namespace libreverse */

#endif //FILE_DATA_TRANSFER_H

