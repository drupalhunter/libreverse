/*  ARM_POWERPC_SH_Exception_Table_Entry_64.cpp

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

#include "ARM_POWERPC_SH_Exception_Table_Entry_64.h"
#include "PE_File.h"

#include <boost/format.hpp>
#include <sstream>

#include "Trace.h"

using namespace libreverse::api;
using namespace libreverse::trace;

namespace libreverse { namespace wpef_module {

    ARM_POWERPC_SH_Exception_Table_Entry_64::ARM_POWERPC_SH_Exception_Table_Entry_64 ()
        : m_begin_address ( 0 ),
          m_prolog_length ( 0 ),
          m_function_length ( 0 ),
          m_32bit_flag ( false ),
          m_exception_flag ( false )
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside ARM_POWERPC_SH_Exception_Table_Entry_64 () constructor" );
    }

    void
    ARM_POWERPC_SH_Exception_Table_Entry_64::read_Entry ( wpef_types::PE_File::ptr_t file_ptr )
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering ARM_POWERPC_SH_Exception_Table_Entry_64::read_Entry" );

        file_ptr->read_ARM_POWERPC_SH_Exception ( this->shared_from_this() );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting ARM_POWERPC_SH_Exception_Table_Entry_64::read_Entry" );
    }

    std::string
    ARM_POWERPC_SH_Exception_Table_Entry_64::to_String (void)
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering ARM_POWERPC_SH_Exception_Table_Entry_64::to_String" );

        std::stringstream output;

        output << boost::format("   begin address: 0x%|1X|") % m_begin_address
               << std::endl
               << boost::format("   prolog length: 0x%|1X|") % static_cast<boost::uint16_t>(m_prolog_length)
               << std::endl
               << boost::format("   function length: 0x%|1X|") % m_function_length
               << std::endl
               << "  32bit flag: ";

        if ( m_32bit_flag )
            {
                output << "TRUE" << std::endl;
            }
        else
            {
                output << "FALSE" << std::endl;
            }

        output << "  Exception flag set: ";

        if ( m_exception_flag )
            {
                output << "TRUE" << std::endl;
            }
        else
            {
                output << "FALSE" << std::endl;
            }

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting ARM_POWERPC_SH_Exception_Table_Entry_64::to_String" );

        return output.str();
    }

    void
    ARM_POWERPC_SH_Exception_Table_Entry_64::convert ()
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering ARM_POWERPC_SH_Exception_Table_Entry_64::convert" );
        /* There is no need to convert a ARM binary exception table
           entry since both the ARM (target) and Intel (host running
           libreverse) are both little endian */
    }

} /* namespace wpef_module */
} /* namespace libreverse */
