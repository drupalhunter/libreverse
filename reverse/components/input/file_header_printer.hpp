/*  File_Header_Printer.h

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

#ifndef FILE_HEADER_PRINTER_H
#define FILE_HEADER_PRINTER_H

#include "infrastructure/Component.h"
#include "infrastructure/Component_Actor.h"
#include <boost/enable_shared_from_this.hpp>

namespace reverse { namespace component {

    class File_Header_Printer : public infrastructure::Component,
                                public infrastructure::Component_Actor,
                                public boost::enable_shared_from_this<File_Header_Printer>
    {
    public:

        explicit File_Header_Printer ();
	  
        explicit File_Header_Printer ( infrastructure_types::Component_State::ptr_t state_ptr );

        File_Header_Printer ( File_Header_Printer const& rhs );

        virtual ~File_Header_Printer();

        File_Header_Printer& operator= ( File_Header_Printer const& rhs );

        void swap ( File_Header_Printer& rhs );

        //------------------------------
        // Component required functions
        //------------------------------
        virtual void received_Input_Source_Data ( boost::uint32_t id );

        virtual void add_Input_Source ( boost::uint32_t id );

        virtual std::string get_Name (void) const;

        virtual void run ( infrastructure_types::Component_Graph::Data_Map_t* m_input_data );

        virtual infrastructure_types::Data_Source_Base::ptr_t results (void);

        virtual void set_State ( boost::uint32_t mode );


        virtual boost::uint32_t get_ID (void) const;

        virtual infrastructure_types::Component_Data::Input_Token_t::const_iterator get_Source_List_Begin (void) const;

        virtual infrastructure_types::Component_Data::Input_Token_t::const_iterator get_Source_List_End (void) const;

        //------------------------------
        // Component Actor required functions
        //------------------------------
        virtual void process (void);

    protected:

        static const std::string m_name;

    private:

        infrastructure_types::Component_State::ptr_t m_state_ptr;
    };
} /* namespace component */
} /* namespace reverse */

#endif /* ENTRY_POINT_DECTECTOR_H */
