/*  Data_Section_Detector_Algorithm_Factory.cpp

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

#include "Data_Section_Detector_Algorithm_Factory.h"
#include "Data_Section_Detector_Elf32_Algorithm.h"
#include "Data_Section_Detector_Elf64_Algorithm.h"
#include "Data_Section_Detector_Java_Algorithm.h"
#include "Data_Section_Detector_WPEF32_Algorithm.h"
#include "Data_Section_Detector_WPEF64_Algorithm.h"

#include "io/input/File_Readers/Elf/Elf_Meta_Info.h"
#include "io/input/File_Readers/Java_Class/Java_Meta_Info.h"
#include "io/input/File_Readers/Windows_PE/PE_Meta_Info.h"
#include "errors/CPU_Exception.h"

#include <string>

namespace libreverse { namespace component {

    Data_Section_Detector_Algorithm::ptr_t
    Data_Section_Detector_Algorithm_Factory::get_Algorithm ( std::string file_type )
    {
      if ( file_type.compare ( elf_module::Elf_Meta_Info::FILE_TYPE_32BIT ) == 0 )
	{
	  return Data_Section_Detector_Algorithm::ptr_t ( new Data_Section_Detector_Elf32_Algorithm() );
	}
      else if ( file_type.compare ( elf_module::Elf_Meta_Info::FILE_TYPE_64BIT ) == 0 )
	{
	  return Data_Section_Detector_Algorithm::ptr_t ( new Data_Section_Detector_Elf64_Algorithm() );
	}
      else if ( file_type.compare ( java_module::Java_Meta_Info::FILE_TYPE ) == 0 )	
	{
	  return Data_Section_Detector_Algorithm::ptr_t ( new Data_Section_Detector_Java_Algorithm() );
	}
      else if ( file_type.compare ( wpef_module::PE_Meta_Info::PE_FILE_TYPE_32BIT ) == 0 )
	{
	  return Data_Section_Detector_Algorithm::ptr_t ( new Data_Section_Detector_WPEF32_Algorithm() );
	}
      else if ( file_type.compare ( wpef_module::PE_Meta_Info::PE_FILE_TYPE_64BIT ) == 0 )
	{
	  return Data_Section_Detector_Algorithm::ptr_t ( new Data_Section_Detector_WPEF64_Algorithm() );
	}
      else
	{
	  throw errors::CPU_Exception ( errors::CPU_Exception::UNSUPPORTED_ARCHITECTURE );
	}
    }

} /* namespace component */
} /* namespace libreverse */

