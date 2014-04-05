/*  Tevis_Zero_Filled_Checker_ELF_Algorithm.cpp

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

#include "Tevis_Zero_Filled_Checker_ELF_Algorithm.h"
#include "data_containers/memory_map.h"
#include "meta/meta_object.h"
#include "io/input/File_Readers/Reader_Factory.h"
#include "io/input/File_Readers/Elf/Elf_Reader_32.h"
#include "io/input/File_Readers/Elf/Elf_Header_32.h"
#include "Trace.h"

#include <boost/format.hpp>

using namespace reverse::api;
using namespace reverse::trace;

namespace reverse { namespace component {

    std::string
    Tevis_Zero_Filled_Checker_ELF_Algorithm::run ( std::string filename )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              "Entering Tevis_Zero_Filled_Checker_ELF_Algorithm::run" );

        elf_types::Elf_Reader_32::ptr_t file_reader_ptr = boost::dynamic_pointer_cast< elf_module::Elf_Reader_32 >
	  ( ( io::Reader_Factory::Instance() ).create_File_Reader ( filename ) );

        file_reader_ptr->read_Section_Headers();

        elf_types::Elf_Header_32::ptr_t hdr_ptr = file_reader_ptr->get_Header();

        // Grab reference to the memory_map associated with the file
        data_types::memory_map::ptr_t mem_ptr = file_reader_ptr->get_memory_map ();

        // Get the base address
        boost::uint32_t image_base = hdr_ptr->get_Base_Address();

        // Initialize counter
        boost::uint32_t counter = 0;

        // Initialize meta_string
        bool zero_byte_count_exceeded = false;
        std::string meta_output = "";

        for ( elf_types::Elf_Header_32::Section_Header_Map_t::const_iterator cpos = hdr_ptr->get_Section_Header_Begin();
              cpos != hdr_ptr->get_Section_Header_End();
              ++cpos )
            {
                // Get the Section header
                elf_types::Elf_Section_Header_32::const_ptr_t sec_ptr = (*cpos).second;
                
                // Get the starting address and size of the section in memory
                boost::uint32_t virt_addr = sec_ptr->get_Section_Offset();
                boost::uint32_t virt_size = sec_ptr->get_Section_Size();

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
                                   % ( image_base + sec_ptr->get_Section_Offset() )
                                   % ( image_base + sec_ptr->get_Section_Offset() + sec_ptr->get_Section_Size() )
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
              "Exiting Tevis_Zero_Filled_Checker_ELF_Algorithm::run" );

        return meta_output;
    }

} /* namespace component */
} /* namespace reverse */

