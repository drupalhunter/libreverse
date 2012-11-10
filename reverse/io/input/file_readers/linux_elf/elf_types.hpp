/*  Elf_Types.h

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

#ifndef ELF_TYPES_H_
#define ELF_TYPES_H_

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <map>
#include <string>

namespace libreverse {

    namespace elf_module
    {
        class Elf_Dynamic_Header_32;
	class Elf_Dynamic_Header_64;
        class Elf_Dynamic_Tag_32;
        class Elf_Dynamic_Tag_64;
        class Elf_File;
        class Elf_File_Header_32;
        class Elf_File_Header_64;
        class Elf_Header_32;
        class Elf_Header_64;
        class Elf_Header_Eident;
        class Elf_Program_Header_32;
        class Elf_Program_Header_64;
        class Elf_Reader_32;
        class Elf_Reader_64;
        class Elf_Relocation_32;
        class Elf_Relocation_64;
        class Elf_Relocation_Add_32;
        class Elf_Relocation_Add_64;
        class Elf_Section_Header_32;
        class Elf_Section_Header_64;
        class Elf_Symbol_32;
        class Elf_Symbol_64;
    }

    namespace elf_types {

        class Elf_Dynamic_Tag_32 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Dynamic_Tag_32 > ptr_t;
        };

        class Elf_Dynamic_Tag_64 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Dynamic_Tag_64 > ptr_t;
        };

        class Elf_Dynamic_Header_32 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Dynamic_Header_32 > ptr_t;
            typedef std::vector< elf_types::Elf_Dynamic_Tag_32::ptr_t > Tag_List_t;
        };

        class Elf_Dynamic_Header_64 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Dynamic_Header_64 > ptr_t;
            typedef std::vector< elf_types::Elf_Dynamic_Tag_64::ptr_t > Tag_List_t;
        };

        class Elf_File {
        public:
            typedef boost::shared_ptr < elf_module::Elf_File > ptr_t;
            typedef boost::shared_ptr < elf_module::Elf_File const > const_ptr_t;
        };

        class Elf_File_Header_32 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_File_Header_32 > ptr_t;
            typedef boost::shared_ptr < elf_module::Elf_File_Header_32 const > const_ptr_t;
        };

        class Elf_File_Header_64 {
        public:
	  typedef boost::shared_ptr < elf_module::Elf_File_Header_64 > ptr_t;
	  typedef boost::shared_ptr < elf_module::Elf_File_Header_64 const > const_ptr_t;
        };

        class Elf_Program_Header_32 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Program_Header_32 > ptr_t;
            typedef boost::shared_ptr < elf_module::Elf_Program_Header_32 const > const_ptr_t;
        };

        class Elf_Program_Header_64 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Program_Header_64 > ptr_t;
            typedef boost::shared_ptr < elf_module::Elf_Program_Header_64 const > const_ptr_t;
        };

        class Elf_Reader_32 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Reader_32 > ptr_t;
            typedef boost::shared_ptr < elf_module::Elf_Reader_32 const > const_ptr_t;
        };

        class Elf_Reader_64 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Reader_64 > ptr_t;
            typedef boost::shared_ptr < elf_module::Elf_Reader_64 const > const_ptr_t;
        };

        class Elf_Relocation_32 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Relocation_32 > ptr_t;
            typedef boost::shared_ptr < elf_module::Elf_Relocation_32 const > const_ptr_t;
        };

        class Elf_Relocation_64 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Relocation_64 > ptr_t;
            typedef boost::shared_ptr < elf_module::Elf_Relocation_64 const > const_ptr_t;
        };

        class Elf_Relocation_Add_32 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Relocation_Add_32 > ptr_t;
            typedef boost::shared_ptr < elf_module::Elf_Relocation_Add_32 const > const_ptr_t;
        };

        class Elf_Relocation_Add_64 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Relocation_Add_64 > ptr_t;
            typedef boost::shared_ptr < elf_module::Elf_Relocation_Add_64 const > const_ptr_t;
        };

        class Elf_Section_Header_32 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Section_Header_32 > ptr_t;
            typedef boost::shared_ptr < elf_module::Elf_Section_Header_32 const > const_ptr_t;
        };

        class Elf_Section_Header_64 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Section_Header_64 > ptr_t;
            typedef boost::shared_ptr < elf_module::Elf_Section_Header_64 const > const_ptr_t;
        };

        class Elf_Symbol_32 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Symbol_32 > ptr_t;
            typedef boost::shared_ptr < elf_module::Elf_Symbol_32 const > const_ptr_t;
        };

        class Elf_Symbol_64 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Symbol_64 > ptr_t;
            typedef boost::shared_ptr < elf_module::Elf_Symbol_64 const > const_ptr_t;
        };

        class Elf_Header_32 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Header_32 > ptr_t;
            typedef std::vector < elf_types::Elf_Program_Header_32::const_ptr_t > Program_Header_List_t;
            typedef std::map < std::string, elf_types::Elf_Section_Header_32::const_ptr_t > Section_Header_Map_t;
            typedef std::vector< std::string > Section_Header_Index_List_t;
            typedef std::vector< elf_types::Elf_Symbol_32::const_ptr_t > Symbol_List_t;
            typedef std::vector< elf_types::Elf_Relocation_32::const_ptr_t > Relocation_List_t;
            typedef std::vector< elf_types::Elf_Relocation_Add_32::const_ptr_t > Relocation_Add_List_t;
        };

        class Elf_Header_64 {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Header_64 > ptr_t;
            typedef std::vector < elf_types::Elf_Program_Header_64::const_ptr_t > Program_Header_List_t;
            typedef std::map < std::string, elf_types::Elf_Section_Header_64::const_ptr_t > Section_Header_Map_t;
            typedef std::vector< std::string > Section_Header_Index_List_t;
            typedef std::vector< elf_types::Elf_Symbol_64::const_ptr_t > Symbol_List_t;
            typedef std::vector< elf_types::Elf_Relocation_64::const_ptr_t > Relocation_List_t;
            typedef std::vector< elf_types::Elf_Relocation_Add_64::const_ptr_t > Relocation_Add_List_t;
        };

        class Elf_Header_Eident {
        public:
            typedef boost::shared_ptr < elf_module::Elf_Header_Eident > ptr_t;
        };

    } /* namespace elf_types */

} /* namespace libreverse */

#endif /* ELF_FILE_H_ */
