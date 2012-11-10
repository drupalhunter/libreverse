/*  Configuration_Data.h

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

#ifndef CONFIG_DATA_H_
#define CONFIG_DATA_H_

#include <functional>
#include <string>
#include <boost/shared_ptr.hpp>
#include "Component_Types.h"

namespace libreverse { namespace infrastructure {

    class String_Compare : public std::binary_function<std::string, std::string, bool>
    {
    private:

        /* Function taken from pg. 213 of "The C++ Standard Library" by Josuttis */
        static bool nocase_compare ( char c1,
                                     char c2 )
        {
            return c1 < c2;
        }

    public:

        bool operator() ( std::string const& lhs,
                          std::string const& rhs )
        {
            return lexicographical_compare ( lhs.begin(), lhs.end(),
                                             rhs.begin(), rhs.end(),
                                             nocase_compare );
        }
    };

    class Configuration_Data {
    public:

        Configuration_Data ();

        virtual ~Configuration_Data(){}

        infrastructure_types::Data_Source_Config_Base::ptr_t get_Transfer_Config();

        void set_Transfer_Config ( infrastructure_types::Data_Source_Config_Base::ptr_t obj );

        void set_Formula_Directory ( std::string const& obj );

        std::string get_Formula_Directory (void) const;

        void set_GRNN_Data_File ( std::string const& obj );

        std::string get_GRNN_Data_File (void) const;

        /*
        void add_DLL_Path ( std::string name,
                            Path_t location );

        Path_t const&
        get_DLL_Path ( std::string const& name );
        */

        void dump (void) const;

    private:

        // Method for passing data
        infrastructure_types::Data_Source_Config_Base::ptr_t m_data;

        // Where to look for the individual formula files (e.g. input, analysis)
        std::string m_formula_directory;

        // Path to the GRNN training data
        std::string m_grnn_data_file;

    };

} /* namespace infrastructure */
} /* namespace libreverse */

#endif /* CONFIG_DATA_H_ */
