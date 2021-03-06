/*  Master_Formula_Parser.cpp

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

#include <reverse/reverse.hpp>
#include <reverse/trace.hpp>
#include <reverse/errors/parsing_exception.hpp>
#include <reverse/infrastructure/formula_list.hpp>
#include <reverse/infrastructure/master_formula_parser.hpp>

#include <json_spirit/reader.h>

#include <boost/format.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/make_shared.hpp>

#include <fstream>

namespace reverse {
        namespace infrastructure {

                master_formula_parser::master_formula_parser()
                        : m_map ( new infrastructure::configurator::formula_map_t() ),
                          m_input_type ( 0 ),
                          m_output_type ( 0 ),
                          m_input_formula_file ( "" ),
                          m_analysis_formula_file ( "" ),
                          m_output_formula_file ( "" )
                {
                        trace::infrastructure_detail ( "Inside Master_Formula_Parser constructor" );
                }

                boost::shared_ptr < const infrastructure::configurator::formula_map_t >
                master_formula_parser::get_formula_map ( std::string const& filename )
                {
                        trace::infrastructure_detail ( "Entering Master_Formula_Parser::get_Formula_Map" );

                        m_map->clear();

                        if ( ! boost::filesystem::exists ( filename ) ) {
                                trace::infrastructure_error ( "Exception throw in %s at line %d",
                                                              __FILE__,
                                                              __LINE__ );

                                throw errors::parsing_exception ( errors::parsing_exception::missing_file );
                        }

                        std::ifstream input ( filename.c_str() );

                        // Create JSON parser
                        //
                        // Master formula map has five entries
                        // - input type
                        // - output type
                        // - input formula map file name
                        // - analysis formula map file name
                        // - output formula map file name
                        //
                        // Parse array of JSON objects
                        //
                        // For each object in array
                        //   - grab file name
                        //   - parser file
                        //   - store in appropriate variable
                        json_spirit::Value top_value;
                        json_spirit::read ( input, top_value );

                        read_formula_map ( top_value.getObject() );

                        trace::infrastructure_detail ( "Exiting Master_Formula_Parser::get_Formula_Map" );

                        return boost::make_shared < infrastructure::configurator::formula_map_t > ( *m_map );
                }

                void master_formula_parser::read_formula_map ( json_spirit::Object const& obj )
                {
                        trace::infrastructure_detail ( "Entering Master_Formula_Parser::read_formula_map" );

                        for ( json_spirit::Object::const_iterator cpos = obj.begin();
                                        cpos != obj.end();
                                        ++cpos ) {
                                const std::string& name = cpos->first;
                                const json_spirit::Value& value = cpos->second;

                                if ( name == "input_type" ) {
                                        this->set_input_type ( value.getString() );
                                } else if ( name == "output_type" ) {
                                        this->set_output_type ( value.getString() );
                                } else if ( name == "input_formula" ) {
                                        m_input_formula_file = value.getString();
                                } else if ( name == "analysis_formula" ) {
                                        m_analysis_formula_file = value.getString();
                                } else if ( name == "output_formula" ) {
                                        m_output_formula_file = value.getString();
                                }
                        }

                        trace::infrastructure_detail ( "Exiting Master_Formula_Parser::charData" );
                }

                void master_formula_parser::set_input_type ( std::string const& value )
                {
                        if ( value == "binary" ) {
                                m_input_type = input_types::binary;
                        } else {
                                throw errors::parsing_exception ( errors::parsing_exception::unknown_type );
                        }
                }

                void master_formula_parser::set_output_type ( std::string const& value )
                {
                        if ( value == "C++" ) {
                                m_output_type = output_types::cplusplus;
                        } else if ( value == "c" ) {
                                m_output_type = output_types::c;
                        } else if ( value == "java" ) {
                                m_output_type = output_types::java;
                        } else if ( value == "uml" ) {
                                m_output_type = output_types::uml;
                        } else {
                                trace::infrastructure_error ( "Exception throw in %s at line %d",
                                                              __FILE__,
                                                              __LINE__ );

                                throw errors::parsing_exception ( errors::parsing_exception::unknown_type );
                        }
                }

        } /* namespace infrastructure */
} /* namespace reverse */
