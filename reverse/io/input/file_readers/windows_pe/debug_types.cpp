/*  Debug_Types.cpp

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

#include "Debug_Types.h"
#include <sstream>
#include <boost/format.hpp>
#include "Trace.h"

using namespace libreverse::api;
using namespace libreverse::trace;

namespace libreverse { namespace wpef_module {

    std::string
    Debug_Types::get_Type_Name ( boost::uint32_t type )
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Debug_Types::get_Type_Name" );

        std::string result = "";

        switch ( type )
            {
            case IMAGE_DEBUG_TYPE_UNKNOWN:
                {
                    result = "PE:debug_type_unknown";
                    break;
                }
            case IMAGE_DEBUG_TYPE_COFF:
                {
                    result = "PE:debug_type_coff";
                    break;
                }
            case IMAGE_DEBUG_TYPE_CODEVIEW:
                {
                    result = "PE:debug_type_codeview";
                    break;
                }
            case IMAGE_DEBUG_TYPE_FPO:
                {
                    result = "PE:debug_type_frame_pointer_omission";
                    break;
                }
            case IMAGE_DEBUG_TYPE_MISC:
                {
                    result = "PE:debug_type_dbg_file_location";
                    break;
                }
            case IMAGE_DEBUG_TYPE_EXCEPTION:
                {
                    result = "PE:debug_type_copy_of_pdata";
                    break;
                }
            case IMAGE_DEBUG_TYPE_FIXUP:
                {
                    result = "PE:debug_type_reserved";
                    break;
                }
            case IMAGE_DEBUG_TYPE_OMAP_TO_SRC:
                {
                    result = "PE:debug_type_mapping_omap_to_src";
                    break;
                }
            case IMAGE_DEBUG_TYPE_OMAP_FROM_SRC:
                {
                    result = "PE:debug_type_mapping_omap_from_src";
                    break;
                }
            case IMAGE_DEBUG_TYPE_BORLAND:
                {
                    result = "PE:debug_type_borland_reserved";
                    break;
                }
            case IMAGE_DEBUG_TYPE_RESERVED10:
                {
                    result = "PE:debug_type_reserved_10";
                    break;
                }
            case IMAGE_DEBUG_TYPE_CLSID:
                {
                    result = "PE:debug_type_reserved_clsid";
                    break;
                }
            }

        std::stringstream output;
        output << boost::format("%1s (%2X)") % result % type;

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Debug_Types::get_Type_Name" );

        return output.str();
    }
} /* namespace wpef_module */
} /* namespace libreverse */

