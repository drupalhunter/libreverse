/*  Database_Data_Transfer.h

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

#ifndef DATABASE_DATA_TRANSFER_H
#define DATABASE_DATA_TRANSFER_H

#include "Data_Transfer_Base.h"
#include <boost/shared_ptr.hpp>
#include "infrastructure/Component_Types.h"

namespace libreverse { namespace infrastructure {

    class Database_Data_Transfer : public Data_Transfer_Base {
    public:

        /**
         *
         */
        explicit Database_Data_Transfer( infrastructure_types::Database_Data_Source_Config::ptr_t cfg );

        explicit Database_Data_Transfer( Database_Data_Transfer const& rhs );

        virtual ~Database_Data_Transfer();

        /**
         *
         */
        virtual void close ();

        /**
         *
         */
        virtual infrastructure_types::data_object::const_ptr_t get () const;

        /**
         *
         */
        virtual void open ();

        /**
         *
         * @param data
         */
        virtual void put ( infrastructure_types::data_object::const_ptr_t data );

        Database_Data_Transfer& operator= ( Database_Data_Transfer const& rhs );
        
        void swap ( Database_Data_Transfer& rhs );

    private:

        /**
         * Fields
         */
        infrastructure_types::Database_Data_Source_Config::ptr_t m_config;

        infrastructure_types::data_object::const_ptr_t m_data;
    };

} /* namespace infrastructure */
} /* namespace libreverse */

#endif //DATABASE_DATA_TRANSFER_H

