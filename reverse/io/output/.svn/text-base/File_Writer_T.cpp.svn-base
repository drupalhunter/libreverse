/*  File_Writer_T.cpp

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

#include "File_Writer_T.hpp"
#include <input/File_Base.hpp>
#include <iostream>

namespace kurt {

  template <typename Data_Type>
  File_Writer<Data_Type>::File_Writer (File_ID* file_ref,
                                       Data_Type* data)
    : m_data (data),
      m_file_ref (file_ref)
  {}

  template <typename Data_Type>
  File_Writer<Data_Type>::~File_Writer ()
  {
    m_data = 0;
  }

  template <typename Data_Type>
  File_ID* File_Writer<Data_Type>::get_File()
  {
    return m_file_ref;
  }

  template <typename Data_Type>
  void File_Writer<Data_Type>::write_Timestamp (mpf_class& obj)
    ACE_THROW_SPEC((kurt::KURT_IOException))
  {
    ACE_TRY
      {
        m_file_handle.precision(obj.get_prec());
        file_Op(obj, "mpf_class value");
      }
    ACE_CATCH(kurt::KURT_IOException,ex)
      {
        std::stringstream error;
        error << "File_Writer<Data_Type>::operator<<(mpf_class) error:";
        error << std::endl << ex.print() << std::endl;
        ACE_THROW(kurt::KURT_IOException(((error).str()).c_str()));
      }
    ACE_ENDTRY;

  }

  template <typename Data_Type>
  void File_Writer<Data_Type>::write (boost::uint32_t* data)
    ACE_THROW_SPEC((kurt::KURT_IOException))
  {
    if (m_file_handle.is_open())
      {
	m_file_handle.write((char*)data, sizeof(boost::uint32_t));
      }
    else
      {
	std::stringstream error;
	error << "File_Writer<Data_Type>: Write operation attempted";
        error << " on a already" << std::endl;
	error << "closed file. Application logic is incorrect." << std::endl;
	ACE_THROW(KURT_IOException(ACE_TEXT((error.str()).c_str())));
      }
  }

} /* namespace kurt */

