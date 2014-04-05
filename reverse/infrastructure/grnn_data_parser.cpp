/*  GRNN_Data_Parser.cpp

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

#include <reverse/trace.hpp>
#include <reverse/infrastructure/grnn_data_parser.hpp>
#include <reverse/infrastructure/component.hpp>
#include <reverse/infrastructure/component_graph.hpp>
#include <reverse/infrastructure/component_state.hpp>
#include <reverse/components/component_factory.hpp>
#include <reverse/errors/parsing_exception.hpp>
#include <reverse/data_containers/memory_map.hpp>
#include <reverse/components/input/grnn/grnn_data_entry.hpp>
#include <reverse/components/input/grnn/grnn_data_map.hpp>
#include <reverse/components/input/grnn/grnn_data_types.hpp>

#include <json_spirit/json_spirit.h>
#include <json_spirit/reader.h>

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/make_shared.hpp>

#include <fstream>


namespace reverse {
        namespace infrastructure {

                grnn_data_parser::grnn_data_parser()
                {
                        trace::infrastructure_detail ( "Inside GRNN_Data_Parser constructor" );
                }

                boost::shared_ptr < components::input::grnn::grnn_data_map >
                grnn_data_parser::get_data_map ( std::string filename )
                {
                        trace::infrastructure_detail ( "Entering GRNN_Data_Parser::get_Data_Map" );

                        m_data_map = boost::make_shared < components::input::grnn::grnn_data_map > ();

                        // Parse file and generate graph
                        trace::infrastructure_data ( "Parsing %s", filename );

                        boost::filesystem::path full_path ( filename );
                        std::ifstream input ( full_path.c_str() );

                        json_spirit::Value top_value;
                        json_spirit::read ( input, top_value );

                        // Parse file
                        json_spirit::Object& value_obj = top_value.getObject();

                        for ( json_spirit::Object::const_iterator cpos = value_obj.begin();
                                        cpos != value_obj.end();
                                        ++cpos ) {

                                const json_spirit::Value& value = cpos->second;
                                const json_spirit::Object& component_obj = value.getObject();
                                const std::string& type = cpos->first;
                                const double sigma = component_obj.find ( "sigma" )->second.getReal();
                                const std::string filename = component_obj.find ( "filename" )->second.getString();

                                // Add entry to GRNN_Data_Map
                                boost::shared_ptr < components::input::grnn::grnn_data_entry > entry_obj =
                                        boost::make_shared < components::input::grnn::grnn_data_entry > ( sigma, filename );

                                m_data_map->insert ( components::input::grnn::grnn_data_types::get_type ( type ), entry_obj );
                        }


                        trace::infrastructure_detail ( "Exiting GRNN_Data_Parser::get_Data_Map" );

                        return m_data_map;
                }

        } /* namespace infrastructure */
} /* namespace reverse */
