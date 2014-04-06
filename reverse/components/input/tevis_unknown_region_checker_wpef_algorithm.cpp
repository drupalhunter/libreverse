/*  Tevis_Unknown_Region_Checker_WPEF_Algorithm.cpp

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

#include "Tevis_Unknown_Region_Checker_WPEF_Algorithm.h"

#include "data_containers/memory_map.h"
#include "meta/meta_object.h"
#include "io/input/File_Readers/Reader_Factory.h"
#include "io/input/File_Readers/Windows_PE/Header_32.h"
#include "io/input/File_Readers/Windows_PE/Reader_32.h"
#include "io/input/File_Readers/Windows_PE/PE_Header_32.h"
#include "io/input/File_Readers/Windows_PE/PE_Section_Header.h"
#include "Trace.h"

using namespace reverse::api;
using namespace reverse::trace;

namespace reverse { namespace component {

    std::string
    Tevis_Unknown_Region_Checker_WPEF_Algorithm::run ( std::string filename )
    {
      Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              "Entering Tevis_Unknown_Region_Checker_WPEF_Algorithm::run" );

        wpef_types::Reader_32::ptr_t file_reader_ptr = boost::dynamic_pointer_cast< wpef_module::Reader_32 >
	  ( ( io::Reader_Factory::Instance() ).create_File_Reader ( filename ) );

        file_reader_ptr->get_memory_map();

        wpef_types::Header_32::ptr_t hdr_ptr = file_reader_ptr->get_Header();

        // Grab reference to the memory_map associated with the file
        data_types::memory_map::ptr_t mem_ptr = file_reader_ptr->get_memory_map ();

        // Get the base address
        wpef_types::PE_Header_32::const_ptr_t pe_hdr = hdr_ptr->get_PE_Header();
        wpef_types::PE_Optional_Header_32::ptr_t opt_hdr = pe_hdr->get_Optional_Header();

        std::string meta_output = "";

        // Get size of image
        boost::uint32_t unaccounted_size = mem_ptr->size();

        for ( wpef_types::Header_32::Section_Header_Map_t::const_iterator cpos = hdr_ptr->get_PE_Section_Header_List_Begin();
              cpos != hdr_ptr->get_PE_Section_Header_List_End();
              ++cpos )
            {
                // Get the Section header
                wpef_types::PE_Section_Header::const_ptr_t sec_ptr = (*cpos).second;
                
                // Get the size of the section in memory
                boost::uint32_t virt_size = sec_ptr->get_Virtual_Size();

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
              "Exiting Tevis_Unknown_Region_Checker_WPEF_Algorithm::run" );

        return meta_output;
    }

} /* namespace component */
} /* namespace reverse */

