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

#ifndef REVERSE_INFRASTRUCTURE_CONFIGURATION_DATA_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_CONFIGURATION_DATA_HPP_INCLUDED


#include <boost/shared_ptr.hpp>

#include <functional>
#include <string>


namespace reverse {
  namespace infrastructure {

    namespace data_source {
      class data_source_config_base;
    } // namespace data_source

    class string_compare : public std::binary_function<std::string, std::string, bool>
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
    
    class configuration_data {
    public:

      configuration_data ();
      
      virtual ~configuration_data(){}
      
      boost::shared_ptr < infrastructure::data_source::data_source_config_base > get_transfer_config();
      
      void set_transfer_config ( boost::shared_ptr < infrastructure::data_source::data_source_config_base > obj );
      
      void set_formula_directory ( std::string const& obj );
      
      std::string get_formula_directory (void) const;
      
      void set_grnn_data_file ( std::string const& obj );
      
      std::string get_grnn_data_file (void) const;
      
      /*
        void add_DLL_Path ( std::string name,
	Path_t location );
	
        Path_t const&
        get_DLL_Path ( std::string const& name );
      */
      
      void dump (void) const;
      
    private:
      
        // Method for passing data
      boost::shared_ptr < infrastructure::data_source::data_source_config_base > m_data;

      // Where to look for the individual formula files (e.g. input, analysis)
      std::string m_formula_directory;
      
      // Path to the GRNN training data
      std::string m_grnn_data_file;
      
    };

  } /* namespace infrastructure */
} /* namespace reverse */

#endif /* REVERSE_INFRASTRUCTURE_CONFIGURATION_DATA_HPP_INCLUDED */
