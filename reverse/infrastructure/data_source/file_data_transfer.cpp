/*  File_Data_Transfer.cpp

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
  			file_data_transfer.cpp - Copyright storri

Here you can write a license for your code, some comments or any other
information you want to have in your generated code. To to this simply
configure the "headings" directory in uml to point to a directory
where you have your heading files.

or you can just replace the contents of this file with your own.
If you want to do this, this file is located at

/usr/kde/3.2/share/apps/umbrello/headings/heading.cpp

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

#include "File_Data_Transfer.h"
#include <fstream>
#include <iostream>
#include <boost/format.hpp>
#include "errors/Component_Exception.h"
#include "Data_Object.h"

namespace libreverse { namespace infrastructure {

    File_Data_Transfer::File_Data_Transfer ( infrastructure_types::File_Data_Source_Config::const_ptr_t config)
        : m_config (config),
          m_data ( new Data_Object() )
    {}

    void File_Data_Transfer::close ()
    {
        // close file
    }

    void File_Data_Transfer::open ()
    {
        // open file
    }

  void File_Data_Transfer::put ( infrastructure_types::Data_Object::const_ptr_t data_ptr )
    {
        if ( data_ptr.get() == 0 )
            {
                std::cerr << boost::format("Exception throw in %s at line %d")
                    % __FILE__
                    % __LINE__
                          << std::endl;

                throw errors::Component_Exception
                    ( errors::Component_Exception::NULL_POINTER );
            }

        /*
          std::ofstream output_file ( (m_config->get_Filename()).c_str() );
          boost::archive::binary_oarchive oa (output_file);
          oa << data.which();

          apply_visitor ( boost::bind (variant_saver(), boost::ref(oa), _1),
          data );
        */
    }

  infrastructure_types::Data_Object::const_ptr_t
  File_Data_Transfer::get () const
    {
        /*
          Data_Object data;

          std::ifstream input_file ( (m_config->get_Filename()).c_str() );
          boost::archive::binary_iarchive oa (input_file);

          boost::uint32_t index;
          oa >> index;

          switch (index)
          {
          case 0:
          {
          bool t;
          oa >> t;
          data = t;
          break;
          }
          case 1:
          {
          std::string t;
          oa >> t;
          data = t;
          break;
          }
          case 2:
          {
          boost::shared_ptr<io::File_Reader> t;
          oa >> t;
          data = t;
          break;
          }
          }

          return data;
        */
        return m_data;
    }

} /* namespace infrastructure */
} /* namespace libreverse */
