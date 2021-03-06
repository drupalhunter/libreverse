/*  Tevis_Unknown_Region_Checker_Algorithm_Factory.cpp

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

#include "Tevis_Unknown_Region_Checker_Algorithm_Factory.h"
#include "Tevis_Unknown_Region_Checker_WPEF_Algorithm.h"
#include "Tevis_Unknown_Region_Checker_ELF_Algorithm.h"
#include "errors/File_Reader_Exception.h"
#include "Trace.h"
#include <string>

using namespace reverse::api;
using namespace reverse::trace;

namespace reverse { namespace component {

    Tevis_Unknown_Region_Checker_Algorithm::ptr_t
    Tevis_Unknown_Region_Checker_Algorithm_Factory::get_Algorithm ( std::string name )
    {
        Trace::write_Trace
            ( TraceArea::COMPONENTS,
              TraceLevel::DETAIL,
              "Entering Tevis_Unknown_Region_Checker_Algorithm_Factory::get_Algorithm" );

        if ( name.compare ( "windows:pe_executable" ) == 0 )
            {
                Trace::write_Trace
                    ( TraceArea::COMPONENTS,
                      TraceLevel::DETAIL,
                      "Exiting Tevis_Unknown_Region_Checker_Algorithm_Factory::get_Algorithm" );

                return Tevis_Unknown_Region_Checker_Algorithm::ptr_t ( new Tevis_Unknown_Region_Checker_WPEF_Algorithm() );
            }
        else if ( ( name.compare ( "elf:executable" ) == 0 ) ||
                  ( name.compare ( "elf:dynamically_linked_library" ) == 0 ) )
            {
                Trace::write_Trace
                    ( TraceArea::COMPONENTS,
                      TraceLevel::DETAIL,
                      "Exiting Tevis_Unknown_Region_Checker_Algorithm_Factory::get_Algorithm" );

                return Tevis_Unknown_Region_Checker_Algorithm::ptr_t ( new Tevis_Unknown_Region_Checker_ELF_Algorithm() );
            }
        else
            {
                throw errors::File_Reader_Exception
                    ( errors::File_Reader_Exception::UNSUPPORTED_FILE_TYPE );
            }
    }

} /* namespace component */
} /* namespace reverse */

