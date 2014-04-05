/*  Tevis_Unknown_Region_Checker_ELF_Algorithm.cpp

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

#include "Tevis_Unknown_Region_Checker_ELF_Algorithm.h"

#include "data_containers/memory_map.h"
#include "meta/meta_object.h"
#include "io/input/File_Readers/Reader_Factory.h"
#include "io/input/File_Readers/Elf/Elf_Reader_32.h"
#include "io/input/File_Readers/Elf/Elf_Header_32.h"
#include "Trace.h"

using namespace reverse::api;
using namespace reverse::trace;

namespace reverse { namespace component {

    std::string
    Tevis_Unknown_Region_Checker_ELF_Algorithm::run ( std::string filename )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
             "Entering Tevis_Unknown_Region_Checker_ELF_Algorithm::run" );

        elf_types::Elf_Reader_32::ptr_t file_reader_ptr = boost::dynamic_pointer_cast< elf_module::Elf_Reader_32 >
            ( ( io::Reader_Factory::Instance() ).create_File_Reader ( filename ) );

        file_reader_ptr->read_Section_Headers();

        elf_types::Elf_Header_32::ptr_t hdr_ptr = file_reader_ptr->get_Header();

        // Grab reference to the memory_map associated with the file
        data_types::memory_map::ptr_t mem_ptr = file_reader_ptr->get_memory_map ();

        std::string meta_output = "";

        // Get size of image
        boost::uint32_t unaccounted_size = mem_ptr->size();

        for ( elf_types::Elf_Header_32::Section_Header_Map_t::const_iterator cpos = hdr_ptr->get_Section_Header_Begin();
              cpos != hdr_ptr->get_Section_Header_End();
              ++cpos )
            {
                // Get the Section header
                elf_types::Elf_Section_Header_32::const_ptr_t sec_ptr = (*cpos).second;
                
                // Get the size of the section in memory
                boost::uint32_t virt_size = sec_ptr->get_Section_Size();

                // Subtract out the size of the section
                unaccounted_size -= virt_size;
            }

        //   set meta string to uncharted_regions:TRUE
        if ( unaccounted_size != 0 )
            {
                meta_output = "uncharted_regions:TRUE";
            }
        else
            {
                meta_output = "uncharted_regions:FALSE";
            }

        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
             "Exiting Tevis_Unknown_Region_Checker_ELF_Algorithm::run" );

        return meta_output;
    }

} /* namespace component */
} /* namespace reverse */

