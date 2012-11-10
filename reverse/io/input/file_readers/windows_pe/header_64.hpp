/*  Header_64.h

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

#ifndef HEADER_64_H_
#define HEADER_64_H_

#include <boost/shared_ptr.hpp>
#include <string>
#include "io/input/File_Readers/Base_Header.h"
#include "io/IO_Types.h"
#include "PE_Types.h"

namespace libreverse { namespace wpef_module {

   
    /*!
     * \class Header
     * \date 2003
     * \author Stephen Torri
     */
    class Header_64 : public header::Base_Header {

    public:


        /*!
         * \brief Default Constructor
         */
        Header_64 ();

        /*!
         * \brief Default Destructor
         */
        virtual ~Header_64 ();

        /*!
         * \brief Change the bit-ordering if required
         */
        virtual void convert ();

        /*!
         * \brief String representation of WPEF Header
         * \return String output of header
         */
        std::string to_String (void);

        /*!
         * \brief Get the human readable strings from the header
         * \return String output of header
         */
        void get_Text_String ( io_types::Text_Data::data_type* output );

        /*-----------------------------*/
        /*        DOS HEADER           */
        /*-----------------------------*/
        wpef_types::DOS_Header::ptr_t get_DOS_Header (void) const;

        void set_DOS_Header ( wpef_types::DOS_Header::ptr_t hdr );

        /*-----------------------------*/
        /*        PE HEADER            */
        /*-----------------------------*/

        wpef_types::PE_Header_64::ptr_t get_PE_Header (void) const;

        void set_PE_Header ( wpef_types::PE_Header_64::ptr_t hdr );

        /*-----------------------------*/
        /*       SECTION HEADER        */
        /*-----------------------------*/

        /*
         * Return the iterator pointing to the PE Section Header. If
         * an incorrect name has been given the iterator will point to
         * the end of the PE Section Header list.
         */
        wpef_types::Header_64::Section_Header_Map_t::const_iterator get_PE_Section_Header ( std::string name ) const;

        boost::uint32_t get_PE_Section_Header_Count (void) const;

        void set_PE_Section_Header ( wpef_types::PE_Section_Header::ptr_t hdr );

        wpef_types::Header_64::Section_Header_Map_t::const_iterator get_PE_Section_Header_List_Begin () const;

        wpef_types::Header_64::Section_Header_Map_t::const_iterator get_PE_Section_Header_List_End () const;

        /*-----------------------------*/
        /*      RESOURCE DIRECTORY     */
        /*-----------------------------*/

	    void set_Resource_Directory ( wpef_types::PE_Resource_Directory::ptr_t r_ptr );

        /*-----------------------------*/
        /*      EXPORT DIRECTORY       */
        /*-----------------------------*/
	    void set_Export_Directory ( wpef_types::PE_Export_Directory::ptr_t exp_ptr );

        wpef_types::PE_Export_Directory::ptr_t get_Export_Directory () const;

        /*-----------------------------*/
        /*      IMPORT DIRECTORY       */
        /*-----------------------------*/

	    void add_Import_Directory ( wpef_types::PE_Import_Directory::ptr_t exp_ptr );

        boost::uint32_t get_PE_Import_Directory_Count (void) const;

        wpef_types::Header_64::Import_Directory_List_t::iterator get_PE_Import_Directory_List_Begin ();

        wpef_types::Header_64::Import_Directory_List_t::iterator get_PE_Import_Directory_List_End ();

        wpef_types::Header_64::Import_Directory_List_t::const_iterator get_PE_Import_Directory_List_Begin () const;

        wpef_types::Header_64::Import_Directory_List_t::const_iterator get_PE_Import_Directory_List_End () const;

        /*-----------------------------*/
        /*       DEBUG DIRECTORY       */
        /*-----------------------------*/

	    void set_Debug_Directory ( wpef_types::PE_Debug_Directory::ptr_t r_ptr );

	    wpef_types::PE_Debug_Directory::ptr_t get_Debug_Directory ( void ) const;

        /*-----------------------------*/
        /*    LOAD CONFIG DIRECTORY    */
        /*-----------------------------*/

	    void set_Load_Config_Directory ( wpef_types::PE_Load_Config_Directory::ptr_t r_ptr );

        wpef_types::PE_Resource_Directory::ptr_t get_PE_Resource_Directory ( void );

        /*-----------------------------*/
        /*    EXCEPTION TABLE LIST     */
        /*-----------------------------*/
	    void add_Exception_Table_Entry ( wpef_types::PE_Exception_Table_Entry::ptr_t exp_ptr );

        boost::uint32_t get_PE_Exception_Table_Entry_Count (void) const;

        wpef_types::Header_64::Exception_Table_List_t::iterator get_PE_Exception_Table_List_Begin ();

        wpef_types::Header_64::Exception_Table_List_t::iterator get_PE_Exception_Table_List_End ();

        wpef_types::Header_64::Exception_Table_List_t::const_iterator get_PE_Exception_Table_List_Begin () const;

        wpef_types::Header_64::Exception_Table_List_t::const_iterator get_PE_Exception_Table_List_End () const;

    private:

        /* Variables */

        /*! \brief WPEF DOS Header */
        wpef_types::DOS_Header::ptr_t m_dos_hdr;

        /*! \brief WPEF PE Header */
        wpef_types::PE_Header_64::ptr_t m_pe_hdr;

        /*! \brief List of PE Section Headers */
        wpef_types::Header_64::Section_Header_Map_t m_sec_hdrs;

        /*! \brief PE Resource Directories */
        wpef_types::PE_Resource_Directory::ptr_t m_res_ptr;

        /*! \brief PE Export Directories */
        wpef_types::PE_Export_Directory::ptr_t m_export_dir_ptr;

        /*! \brief PE Import Directories */
        wpef_types::Header_64::Import_Directory_List_t m_import_dir_list;

        /*! \brief PE Debug Directories */
        wpef_types::PE_Debug_Directory::ptr_t m_debug_ptr;

        /*! \brief PE Load_Config Directories */
        wpef_types::PE_Load_Config_Directory::ptr_t m_load_config_ptr;

        /*! \brief PE Exception Table entries */
        wpef_types::Header_64::Exception_Table_List_t m_exception_list;

    };

} /* namespace wpef_module */
} /* namespace libreverse */

#endif /* HEADER_64_H_ */
