/*  Unpacker_Java_Algorithm.h

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

#ifndef UNPACKER_JAVA_ALGORITHM_H
#define UNPACKER_JAVA_ALGORITHM_H

#include "Unpacker_Algorithm.h"
#include "meta/meta_object.h"

namespace libreverse { namespace component {

    class Unpacker_Java_Algorithm : public Unpacker_Algorithm {
    public:

        virtual data_types::memory_map::const_ptr_t run ( meta::meta_object::const_ptr_t,
                                                          data_types::memory_map::const_ptr_t );

        virtual void print_Color_Map (void);

        infrastructure_types::Component::Meta_List_t
        get_Meta_Input_List_Impl (void);

    private:

        void create_Color_Map (void);

        enum COLOR_VALUE {
            WHITE = 0,
            RED,
            GREEN
        };

        static const std::string RED_STRING;
        static const std::string GREEN_STRING;
        static const std::string WHITE_STRING;

        //------------------------------
        //         TYPES
        //------------------------------
        /*! \brief key is the index to the memory map for the correct
          value. Data is the color used when printing */
        typedef std::map<boost::uint32_t, COLOR_VALUE> Color_Map_t;

        //------------------------------
        //         VARIABLES
        //------------------------------
        Color_Map_t m_color_map;

        data_types::memory_map::const_ptr_t m_file_map;
    };

} /* namespace component */
} /* namespace libreverse */

#endif /* UNPACKAGE_JAVA_ALGORITHM_H */
