/*  Tevis_Zero_Filled_Checker_WPEF_Algorithm.cpp

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

#include "Tevis_Zero_Filled_Checker_WPEF_Algorithm.h"

#include "data_containers/memory_map.h"
#include "meta/meta_object.h"
#include "io/input/File_Readers/Reader_Factory.h"
#include "io/input/File_Readers/Windows_PE/Reader_32.h"
#include "io/input/File_Readers/Windows_PE/Header_32.h"
#include "io/input/File_Readers/Windows_PE/PE_Header_32.h"
#include "io/input/File_Readers/Windows_PE/PE_Optional_Header_32.h"
#include "io/input/File_Readers/Windows_PE/PE_Section_Header.h"
#include "io/File_ID.h"
#include "Trace.h"

#include <boost/format.hpp>

using namespace libreverse::api;
using namespace libreverse::trace;

namespace libreverse { namespace component {

    std::string
    Tevis_Zero_Filled_Checker_WPEF_Algorithm::run ( std::string filename )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              "Entering Tevis_Zero_Filled_Checker_WPEF_Algorithm::run" );

	io_types::File_ID::const_ptr_t id_ptr ( new io::File_ID ( filename ) );

	// Support only 32-bit for now.
	//
	// Future:
	// - create 32-bit and 64-bit functions
	// - Call 32-bit function first. If return is true then the 32-bit was run. Otherwise call 64-bit function
        wpef_types::Reader_32::ptr_t file_reader_ptr ( new wpef_module::Reader_32 ( id_ptr ) );

        file_reader_ptr->get_memory_map();

        wpef_types::Header_32::ptr_t hdr_ptr = file_reader_ptr->get_Header();

        // Grab reference to the memory_map associated with the file
        data_types::memory_map::ptr_t mem_ptr = file_reader_ptr->get_memory_map ();

        // Get the base address
        wpef_types::PE_Header_32::const_ptr_t pe_hdr = hdr_ptr->get_PE_Header();
        wpef_types::PE_Optional_Header_32::ptr_t opt_hdr = pe_hdr->get_Optional_Header();
        boost::uint32_t image_base = opt_hdr->get_Image_Base();

        // Initialize counter
        boost::uint32_t counter = 0;

        // Initialize meta_string
        bool zero_byte_count_exceeded = false;
        std::string meta_output = "";

        for ( wpef_types::Header_32::Section_Header_Map_t::const_iterator cpos = hdr_ptr->get_PE_Section_Header_List_Begin();
              cpos != hdr_ptr->get_PE_Section_Header_List_End();
              ++cpos )
            {
                // Get the Section header
                wpef_types::PE_Section_Header::const_ptr_t sec_ptr = (*cpos).second;
                
                // Get the starting address and size of the section in memory
                boost::uint32_t virt_addr = sec_ptr->get_Virtual_Address();
                boost::uint32_t virt_size = sec_ptr->get_Virtual_Size();

                // Set Memory Map to the starting address
                mem_ptr->address_Seek ( image_base + virt_addr );

                boost::uint8_t byte = 0;

                // FOR i = 0 TO i < section size
                for ( boost::uint32_t index = 0;
                      index < virt_size;
                      ++index )
                    {
                        //   check byte at address
                        mem_ptr->read ( &byte, sizeof(byte) );

                        //   If byte is 0x0 increment counter
                        if ( byte == 0x0 )
                            {
                                ++counter;
                            }

                        //   Move to next address
                        mem_ptr->address_Seek ( image_base + virt_addr + index );
                    }

                Trace::write_Trace
                    ( TraceArea::COMPONENTS,
                      TraceLevel::DATA,
                      boost::str ( boost::format("  scanned region 0x%X - 0x%X (0x%X bytes) found %d zero bits." )
                                   % ( image_base + sec_ptr->get_Virtual_Address() )
                                   % ( image_base + sec_ptr->get_Virtual_Address() + sec_ptr->get_Virtual_Size() )
                                   % virt_size
                                   % counter ) );

                // IF counter > 50 mark Section has potentially malicious code
                if ( counter > Tevis_Zero_Filled_Checker_Algorithm::MINIMUM_COUNT )
                    {
                        //   Print out to Info: (Section name, address, size)
                        zero_byte_count_exceeded = true;
                    }

                // Reset counter
                counter = 0;
            }

        //   set meta string to zerobyteregions:TRUE
        if ( zero_byte_count_exceeded )
            {
                meta_output = "suspicious_zero_byte_regions:TRUE";
            }
        else
            {
                meta_output = "suspicious_zero_byte_regions:FALSE";
            }

        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              "Exiting Tevis_Zero_Filled_Checker_WPEF_Algorithm::run" );

        return meta_output;
    }

} /* namespace component */
} /* namespace libreverse */

