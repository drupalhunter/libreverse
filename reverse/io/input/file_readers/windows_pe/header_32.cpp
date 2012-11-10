/*  Header_32.cpp

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

#include "Header_32.h"
#include "DOS_Header.h"
#include "PE_Header_32.h"
#include "PE_Section_Header.h"
#include "PE_Optional_Header_32.h"
#include "PE_Resource_Directory.h"
#include "PE_Export_Directory.h"
#include "PE_Import_Directory.h"
#include "PE_Debug_Directory.h"
#include "PE_Load_Config_Directory.h"
#include <iostream>
#include <sstream>
#include <boost/format.hpp>
#include "Trace.h"

using namespace libreverse::api;
using namespace libreverse::trace;

namespace libreverse { namespace wpef_module {

    Header_32::Header_32()
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32 constructor" );
    }

    Header_32::~Header_32()
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32 destructor" );
    }

    void
    Header_32::convert ()
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Header_32::convert" );

        m_dos_hdr->convert ();
        m_pe_hdr->convert ();

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Header_32::convert" );
    }

    std::string
    Header_32::to_String ()
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Header_32::to_String" );

        std::stringstream output_str;

        output_str << "---- WPEF Header dump: -----" << std::endl;
        output_str << m_dos_hdr->to_String() << std::endl;

        output_str << "---- WPEF PE Header dump: -----" << std::endl;
        output_str << m_pe_hdr->to_String() << std::endl;

        output_str << "---- WPEF Section Header dump: -----" << std::endl;
        for ( wpef_types::Header_32::Section_Header_Map_t::iterator pos = m_sec_hdrs.begin();
              pos != m_sec_hdrs.end();
              ++pos)
            {
                output_str << ((*pos).second)->to_String() << std::endl;
            }

		if ( m_res_ptr.get() != 0 )
            {
                output_str << "---- WPEF Resource Directory dump: -----" << std::endl;
                output_str << m_res_ptr->to_String() << std::endl;
            }

		if ( m_export_dir_ptr.get() != 0 )
            {
                wpef_types::PE_Optional_Header_32::ptr_t opt_ptr = m_pe_hdr->get_Optional_Header();
                
                output_str << "---- WPEF Export Directory dump: -----" << std::endl;
                output_str << m_export_dir_ptr->to_String ( opt_ptr->get_Image_Base() ) << std::endl;
            }

		if ( !m_import_dir_list.empty() )
            {
                output_str << "---- WPEF Import Directory dump: -----" << std::endl;
                for ( wpef_types::Header_32::Import_Directory_List_t::const_iterator pos = m_import_dir_list.begin();
                      pos != m_import_dir_list.end();
                      pos++ )
                    {
                        output_str << (*pos)->to_String() << std::endl;
                    }
            }

		if ( m_debug_ptr.get() != 0 )
            {
                output_str << "---- WPEF Debug Directory dump: -----" << std::endl;
                output_str << m_debug_ptr->to_String() << std::endl;
            }

		if ( m_load_config_ptr.get() != 0 )
            {
                output_str << "---- WPEF Load_Config Directory dump: -----" << std::endl;
                output_str << m_load_config_ptr->to_String() << std::endl;
            }

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Header_32::to_String" );

        return output_str.str();
    }

    void
    Header_32::get_Text_String ( io_types::Text_Data::data_type* output )
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Header_32::get_Text_String" );

        output->push_back ( this->to_String() );
    }

    /*-----------------------------*/
    /*        DOS HEADER           */
    /*-----------------------------*/

    wpef_types::DOS_Header::ptr_t
    Header_32::get_DOS_Header (void) const
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32::get_DOS_Header" );

        return m_dos_hdr;
    }

    void Header_32::set_DOS_Header ( wpef_types::DOS_Header::ptr_t hdr )
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Header_32::set_DOS_Header" );

        m_dos_hdr = hdr;

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Header_32::set_DOS_Header" );
    }

    /*-----------------------------*/
    /*         PE HEADER           */
    /*-----------------------------*/

    wpef_types::PE_Header_32::const_ptr_t
    Header_32::get_PE_Header (void) const
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32::get_PE_Header" );

        return m_pe_hdr;
    }

    void Header_32::set_PE_Header ( wpef_types::PE_Header_32::ptr_t hdr)
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Header_32::set_PE_Header" );

        m_pe_hdr = hdr;

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Header_32::set_PE_Header" );

    }

    /*-----------------------------*/
    /*        SECTION HEADER       */
    /*-----------------------------*/

    /*
        bool
      Header_32::has_PE_Section_Header (std::string const name)
      {
      bool result = false;

      // IF we have a header associated with a name THEN return true
      // ELSE return false
      Section_Header_Map::const_iterator pos = m_sec_hdrs.find ( name );
      if ( pos != m_sec_name_map.end() )
      {
      result = true;
      }

      return result;
      }
    */

    wpef_types::Header_32::Section_Header_Map_t::const_iterator
    Header_32::get_PE_Section_Header ( std::string name ) const
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Header_32::get_PE_Section_Header" );

        wpef_types::Header_32::Section_Header_Map_t::const_iterator pos = m_sec_hdrs.find ( name );

        if ( pos == m_sec_hdrs.end() )
            {
                Trace::write_Trace ( TraceArea::IO,
                                     TraceLevel::ERROR,
                                     boost::str ( boost::format ( "Invalid section name given: %s" )
                                                  % name ) );
            }

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Header_32::get_PE_Section_Header" );

        return pos;
    }

    boost::uint32_t
    Header_32::get_PE_Section_Header_Count (void) const
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32::get_PE_Section_Header_Count" );

        return m_sec_hdrs.size();
    }

    wpef_types::Header_32::Section_Header_Map_t::const_iterator
    Header_32::get_PE_Section_Header_List_Begin () const
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32::get_PE_Section_Header_List_Begin" );

        return m_sec_hdrs.begin();
    }

    wpef_types::Header_32::Section_Header_Map_t::const_iterator
    Header_32::get_PE_Section_Header_List_End () const
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32::get_PE_Section_Header_List_End" );

        return m_sec_hdrs.end();
    }

    void Header_32::set_PE_Section_Header ( wpef_types::PE_Section_Header::ptr_t hdr)
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Header_32::set_PE_Section_Header " );

        m_sec_hdrs.insert ( std::make_pair ( hdr->get_Name(), hdr ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Header_32::set_PE_Section_Header " );

    }

    /*-----------------------------*/
    /*      RESOURCE DIRECTORY     */
    /*-----------------------------*/

    void
    Header_32::set_Resource_Directory ( wpef_types::PE_Resource_Directory::ptr_t r_ptr )
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Header_32::set_Resource_Directory" );

        m_res_ptr = r_ptr;

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Header_32::set_Resource_Directory" );
    }

    /*-----------------------------*/
    /*       EXPORT DIRECTORY      */
    /*-----------------------------*/

    void
    Header_32::set_Export_Directory ( wpef_types::PE_Export_Directory::ptr_t exp_ptr )
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Header_32::set_Export_Directory" );

        m_export_dir_ptr = exp_ptr;

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Header_32::set_Export_Directory" );
    }

    wpef_types::PE_Export_Directory::ptr_t
    Header_32::get_Export_Directory () const
    {
        return m_export_dir_ptr;
    }

    /*-----------------------------*/
    /*       IMPORT DIRECTORY      */
    /*-----------------------------*/

    void
    Header_32::add_Import_Directory ( wpef_types::PE_Import_Directory::ptr_t exp_ptr )
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Header_32::add_Import_Directory" );

        m_import_dir_list.push_back ( exp_ptr );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Header_32::add_Import_Directory" );
    }

    boost::uint32_t
    Header_32::get_PE_Import_Directory_Count (void) const
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32::get_PE_Import_Directory_Count" );

        return m_import_dir_list.size();
    }

    wpef_types::Header_32::Import_Directory_List_t::iterator
    Header_32::get_PE_Import_Directory_List_Begin ()
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32::get_PE_Import_Directory_List_Begin" );

        return m_import_dir_list.begin();
    }

    wpef_types::Header_32::Import_Directory_List_t::iterator
    Header_32::get_PE_Import_Directory_List_End ()
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32::get_PE_Import_Directory_List_End" );

        return m_import_dir_list.end();
    }

    wpef_types::Header_32::Import_Directory_List_t::const_iterator
    Header_32::get_PE_Import_Directory_List_Begin () const
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32::get_PE_Import_Directory_List_Begin (const)" );

        return m_import_dir_list.begin();
    }

    wpef_types::Header_32::Import_Directory_List_t::const_iterator
    Header_32::get_PE_Import_Directory_List_End () const
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32::get_PE_Import_Directory_List_End (const)" );

        return m_import_dir_list.end();
    }

    /*-----------------------------*/
    /*        DEBUG DIRECTORY      */
    /*-----------------------------*/

    void
    Header_32::set_Debug_Directory ( wpef_types::PE_Debug_Directory::ptr_t d_ptr )
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Header_32::set_Debug_Directory" );

        m_debug_ptr = d_ptr;

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Header_32::set_Debug_Directory" );

    }

    wpef_types::PE_Debug_Directory::ptr_t
    Header_32::get_Debug_Directory () const
    {
        return m_debug_ptr;
    }

    /*-----------------------------*/
    /*     LOAD CONFIG DIRECTORY   */
    /*-----------------------------*/

    void
    Header_32::set_Load_Config_Directory ( wpef_types::PE_Load_Config_Directory::ptr_t d_ptr )
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Header_32::set_Load_Config_Directory" );

        m_load_config_ptr = d_ptr;

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Header_32::set_Load_Config_Directory" );
    }

    wpef_types::PE_Resource_Directory::ptr_t
    Header_32::get_PE_Resource_Directory ()
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Header_32::get_PE_Resource_Directory" );

        return m_res_ptr;
    }

    /*-----------------------------*/
    /*       IMPORT DIRECTORY      */
    /*-----------------------------*/

    void
    Header_32::add_Exception_Table_Entry ( wpef_types::PE_Exception_Table_Entry::const_ptr_t exp_ptr )
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Header_32::add_Exception_Table_Entry" );

        m_exception_list.push_back ( exp_ptr );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Header_32::add_Exception_Table_Entry" );
    }

    boost::uint32_t
    Header_32::get_PE_Exception_Table_Entry_Count (void) const
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32::get_PE_Exception_Table_Entry_Count" );

        return m_exception_list.size();
    }

    wpef_types::Header_32::Exception_Table_List_t::iterator
    Header_32::get_PE_Exception_Table_List_Begin ()
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32::get_PE_Exception_Table_List_Begin" );

        return m_exception_list.begin();
    }

    wpef_types::Header_32::Exception_Table_List_t::iterator
    Header_32::get_PE_Exception_Table_List_End ()
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32::get_PE_Exception_Table_List_End" );

        return m_exception_list.end();
    }

    wpef_types::Header_32::Exception_Table_List_t::const_iterator
    Header_32::get_PE_Exception_Table_List_Begin () const
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32::get_PE_Exception_Table_List_Begin (const)" );

        return m_exception_list.begin();
    }

    wpef_types::Header_32::Exception_Table_List_t::const_iterator
    Header_32::get_PE_Exception_Table_List_End () const
    {
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Header_32::get_PE_Exception_Table_List_End (const)" );

        return m_exception_list.end();
    }

} /* namespace wpef_module */
} /* namespace libreverse */
