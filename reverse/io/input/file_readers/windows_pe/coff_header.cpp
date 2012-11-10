/*  Coff_Header.cpp

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

#include "Coff_Header.h"
#include "PE_Machine_Types.h"
#include "PE_Characteristics.h"

#include "io/Byte_Converter.h"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse
{
    namespace wpef_module
    {

        COFF_Header::COFF_Header()
                : m_machine ( 0 ),
                m_number_of_sections ( 0 ),
                m_time_date_stamp ( 0 ),
                m_pointer_to_symbol_table ( 0 ),
                m_number_of_symbols ( 0 ),
                m_size_of_optional_header ( 0 ),
                m_characteristics ( 0 )
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside COFF_Header constructor" );
#endif /* LIBREVERSE_DEBUG */

        }

        /*!
         * \brief Convert the header data into a string representation
         * \return String representation of header data
         */
        std::string
        COFF_Header::to_String ( void )
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering COFF_Header::to_String" );
#endif /* LIBREVERSE_DEBUG */


            std::stringstream output_str;

            output_str << "COFF Header:" << std::endl;

            output_str << boost::format ( "  Machine:              %1%" )
	      % boost::io::group ( std::hex,
				   m_machine );
	    
            output_str << " (" << this->get_Machine_Name() << ")" << std::endl;

            boost::posix_time::ptime epoch ( boost::gregorian::date ( 1970, 1, 1 ) );
            boost::posix_time::seconds s_time ( m_time_date_stamp );
            boost::posix_time::ptime creation_date = epoch + s_time;

            output_str << boost::format ( "  Number of sections:  %1%" )
	      % boost::io::group ( std::hex,
				   m_number_of_sections )
		       << std::endl;

            output_str << "  Time stamp: "
		       << boost::posix_time::to_simple_string ( creation_date )
		       << std::endl;
	    
            output_str << boost::format ( "  Symbol Token offset:  %1%" ) %
	      boost::io::group ( std::hex,
				 m_pointer_to_symbol_table )
		       << std::endl;

            output_str << boost::format ( "  Number of symbols:    %1%" ) %
	      boost::io::group ( std::hex,
				 m_number_of_symbols )
		       << std::endl;
	    
            output_str << boost::format ( "  Optional header size: %1%" ) %
	      boost::io::group ( std::hex,
				 m_size_of_optional_header )
		       << std::endl;
	    
            output_str << boost::format ( "  Characteristics: %1%" ) %
	      boost::io::group ( std::hex,
				 m_characteristics )
		       << std::endl
		       << this->get_Characteristics_String()
		       << std::endl;
	    

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting COFF_Header::to_String" );
#endif /* LIBREVERSE_DEBUG */

            return output_str.str();
        }

        /*!
         * \brief Convert the bit order of the stored data
         */
        void
        COFF_Header::convert ()
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering COFF_Header::convert" );
#endif /* LIBREVERSE_DEBUG */


            io::Byte_Converter::convert ( m_machine );
            io::Byte_Converter::convert ( m_number_of_sections );
            io::Byte_Converter::convert ( m_time_date_stamp );
            io::Byte_Converter::convert ( m_pointer_to_symbol_table );
            io::Byte_Converter::convert ( m_number_of_symbols );
            io::Byte_Converter::convert ( m_size_of_optional_header );
            io::Byte_Converter::convert ( m_characteristics );


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting COFF_Header::to_String" );
#endif /* LIBREVERSE_DEBUG */

        }

        std::string
        COFF_Header::get_Machine_Name ( void )
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside COFF_Header::get_Machine_Name" );
#endif /* LIBREVERSE_DEBUG */

            return PE_Machine_Types::get_String_Name ( m_machine );
        }

        boost::uint16_t
        COFF_Header::get_Optional_Header_Size ( void ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside COFF_Header::get_Optional_Header_Size" );
#endif /* LIBREVERSE_DEBUG */

            return m_size_of_optional_header;
        }

        std::string
        COFF_Header::get_Characteristics_String ( void )
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering COFF_Header::get_Characteristics_String" );
#endif /* LIBREVERSE_DEBUG */


            std::stringstream result;

            result << PE_Characteristics::get_String_Name_List ( m_characteristics );


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting COFF_Header::get_Characteristics_String" );
#endif /* LIBREVERSE_DEBUG */

            return result.str();
        }

        bool
        COFF_Header::is_Valid () const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside COFF_Header::is_Valid" );
#endif /* LIBREVERSE_DEBUG */

            return PE_Machine_Types::is_Valid_Value ( m_machine ) &&
	      ( m_time_date_stamp != 0 ) &&
	      ( m_pointer_to_symbol_table == 0 ) &&
	      ( m_number_of_symbols == 0 ) &&
	      ( m_size_of_optional_header != 0 );
        }

        boost::uint16_t
        COFF_Header::get_Machine_Number ( void ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside COFF_Header::get_Machine_Number" );
#endif /* LIBREVERSE_DEBUG */

            return m_machine;
        }

        boost::uint16_t
        COFF_Header::get_Section_Header_Count ( void ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside COFF_Header::get_Section_Header_Count" );
#endif /* LIBREVERSE_DEBUG */

            return m_number_of_sections;
        }

        boost::uint32_t
        COFF_Header::get_Time_Stamp_Number ( void ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside COFF_Header::get_Time_Stamp_Number" );
#endif /* LIBREVERSE_DEBUG */

            return m_time_date_stamp;
        }

        boost::uint32_t
        COFF_Header::get_Symbol_Table_Pointer ( void ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside COFF_Header::get_Symbol_Table_Pointer" );
#endif /* LIBREVERSE_DEBUG */

            return m_pointer_to_symbol_table;
        }

        boost::uint32_t
        COFF_Header::get_Number_Of_Symbols ( void ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside COFF_Header::get_Number_Of_Symbols" );
#endif /* LIBREVERSE_DEBUG */

            return m_number_of_symbols;
        }

        bool
        COFF_Header::is_Executable ( void ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering COFF_Header::is_Executable" );
#endif /* LIBREVERSE_DEBUG */

            bool result = false;

            if ( m_characteristics & PE_Characteristics::PE_IMAGE_FILE_EXECUTABLE_IMAGE )
            {
                result = true;
            }


#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting COFF_Header::is_Executable" );
#endif /* LIBREVERSE_DEBUG */

            return result;
        }

        boost::uint16_t
        COFF_Header::get_Characteristic_Value ( void ) const
        {

#ifdef LIBREVERSE_DEBUG
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside COFF_Header::get_Characteristic_Value" );
#endif /* LIBREVERSE_DEBUG */

            return m_characteristics;
        }

    } /* namespace wpef_module */
} /* namespace libreverse */
