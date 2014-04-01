/*  Master_Formula_Parser.h

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

#ifndef REVERSE_INFRASTRUCTURE_MASTER_FORMULA_PARSER_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_MASTER_FORMULA_PARSER_HPP_INCLUDED

#include <reverse/infrastructure/configurator.hpp>
#include <json_spirit/json_spirit.hpp>

#include <boost/shared_ptr.hpp>

namespace reverse {
  namespace infrastructure {

    class master_formula_parser {
    public:

      explicit master_formula_parser();

      virtual ~master_formula_parser(){}

      boost::shared_ptr < const infrastructure::configurator::formula_map_t >
      get_formula_map ( std::string const& filename );

    private:

      void read_formula_map ( json_spirit::Object const& obj );

      void set_input_type ( std::string const& value );

      void set_output_type ( std::string const& value );

        static const int MATCH;

      boost::shared_ptr < infrastructure::configurator::formula_map_t > m_map;
      boost::uint32_t m_input_type;
      boost::uint32_t m_output_type;
      std::string m_input_formula_file;
      std::string m_analysis_formula_file;
      std::string m_output_formula_file;
    };
  } /* namespace infrastructure */
} /* namespace reverse */

#endif /* REVERSE_INFRASTRUCTURE_MASTER_FORMULA_PARSER_HPP_INCLUDED */
