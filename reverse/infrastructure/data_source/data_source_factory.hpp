/*  Data_Source_Factory.h

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

#ifndef DATA_SOURCE_FACTORY_H
#define DATA_SOURCE_FACTORY_H

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include "Data_Source_Factory_Base.h"
#include "infrastructure/Component_Types.h"

namespace libreverse { namespace infrastructure {

    class Data_Source_Factory : public Data_Source_Factory_Base {

    public:

        virtual ~Data_Source_Factory(){}

        /**
         *
         */
        infrastructure_types::Data_Source_Base::ptr_t get_Data_Source ( boost::uint32_t id );
        
        /**
         *
         */
        static infrastructure_types::Data_Source_Factory::ptr_t Instance ();

        /**
         *
         * @param transfer_type
         * @param source_config
         */
        void init ( infrastructure_types::Data_Source_Config_Base::ptr_t source_config );


    private:

        Data_Source_Factory();

        /**
         * Fields
         */
        static infrastructure_types::Data_Source_Factory::ptr_t m_factory;

        /**
         *
         */
        infrastructure_types::Data_Source_Config_Base::ptr_t m_src_config;

    };
} /* namespace infrastructure */
} /* namespace libreverse */

#endif /* DATA_SOURCE_FACTORY_H */

