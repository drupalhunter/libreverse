/*  formula_parser.cpp

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
#include <reverse/infrastructure/formula_parser.hpp>
#include <reverse/infrastructure/component.hpp>
#include <reverse/infrastructure/component_graph.hpp>
#include <reverse/infrastructure/component_state.hpp>
#include <reverse/components/component_factory.hpp>
#include <reverse/errors/parsing_exception.hpp>
#include <reverse/data_containers/memory_map.hpp>

#include <json_spirit/reader.h>

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/make_shared.hpp>

#include <sstream>
#include <fstream>


namespace reverse {
        namespace infrastructure {

                formula_parser::formula_parser ()
                        : m_id ( 0 ),
                          m_name ( "" ),
                          m_file ( "" )
                {
                        trace::infrastructure_detail ( "Inside formula_parser constructor" );
                }

                boost::shared_ptr < infrastructure::component > formula_parser::get_component ( json_spirit::Object::const_iterator cpos )
                {
                        trace::infrastructure_detail ( "Entering formula_parser::get_component" );

                        const std::string& name = cpos->first;
                        const json_spirit::Value& value = cpos->second;
                        const json_spirit::Object& component_obj = value.getObject();
                        const int id = component_obj.find ( "id" )->second.getInt();

                        // Add Component_State object
                        boost::shared_ptr < infrastructure::component_state > state_ptr ( new component_state ( id ) );

                        trace::infrastructure_data ( "Creating component: %s", name );

                        if ( name == "file_type" ) {
                                        return components::component_factory::instance().get_file_type_detector ( state_ptr );
                                }
                        else if ( name == "arch_type" ) {
                                        return components::component_factory::instance().get_arch_type_detector ( state_ptr );
                                }
                        else if ( name == "meta_writer" ) {
                                        return components::component_factory::instance().get_meta_writer ( state_ptr, component_obj );
                                }
                        else if ( name == "unpacker" ) {
                                        return components::component_factory::instance().get_unpacker ( state_ptr );
                                }
                        else if ( name == "code_section" ) {
                                        return components::component_factory::instance().get_code_section ( state_ptr );
                                }
                        else if ( name == "data_section" ) {
                                        return components::component_factory::instance().get_data_section ( state_ptr );
                                }
                        else if ( name == "entry_point" ) {
                                        return components::component_factory::instance().get_entry_point ( state_ptr );
                                }
                        else if ( name == "null" ) {
                                        return components::component_factory::instance().get_null_component ( state_ptr );
                                }
                        else if ( name == "memory_map_producer" ) {
                                        return components::component_factory::instance().get_memory_map_producer ( state_ptr );
                                }
                        else if ( name == "file_header_printer" ) {
                                        return components::component_factory::instance().get_file_header_printer ( state_ptr );
                                }
                        else if ( name == "tevis_zero_filled_checker" ) {
                                        return components::component_factory::instance().get_tevis_zero_filled_checker ( state_ptr );
                                }
                        else if ( name == "tevis_unknown_region_checker" ) {
                                        return components::component_factory::instance().get_tevis_unknown_region_checker ( state_ptr );
                                }
                        else if ( name == "compiler_classifier" ) {
                                        return components::component_factory::instance().get_compiler_classifier ( state_ptr );
                                }
                        else {
                                        trace::infrastructure_error<> ( "Unknown component, %s, requested in formula.\nDouble check formula file.", name );
                                        trace::infrastructure_error<> ( "Exception throw in %s at line %d", __FILE__, __LINE__ );
                                        throw errors::parsing_exception ( errors::parsing_exception::unknown_component );
                                }

                        trace::infrastructure_detail ( "Exiting formula_parser::get_component" );
                }

                void formula_parser::read_components ( json_spirit::Object const& obj )
                {
                        trace::infrastructure_detail ( "Entering formula_parser::read_components" );

                        for ( json_spirit::Object::const_iterator cpos = obj.begin();
                                        cpos != obj.end();
                                        ++cpos ) {

                                        boost::shared_ptr<infrastructure::component > obj_ptr = this->get_component ( cpos );

                                        const json_spirit::Value& value = cpos->second;
                                        const json_spirit::Object& component_obj = value.getObject();
                                        const json_spirit::Array& predecessor_list = component_obj.find ( "parent_id" )->second.getArray();

                                        for ( unsigned int index = 0;
                                                        index < predecessor_list.size();
                                                        ++index ) {
                                                        unsigned int parent_id = predecessor_list[index].getInt();
                                                        obj_ptr->add_input_source ( parent_id );
                                                }

                                        m_graph->add_component ( obj_ptr );
                                }

                        trace::infrastructure_detail ( "Exiting formula_parser::read_components" );
                }

                boost::shared_ptr < infrastructure::component_graph >
                formula_parser::get_graph ( std::string filename,
                                            std::string directory )
                {
                        trace::infrastructure_detail ( "Entering formula_parser::get_Graph" );

                        m_graph = boost::make_shared < infrastructure::component_graph > ();

                        // Parse file and generate graph
                        boost::filesystem::path full_path ( directory );
                        full_path /= filename;

                        std::ifstream input ( full_path.c_str() );

                        json_spirit::Value top_value;
                        json_spirit::read ( input, top_value );

                        read_components ( top_value.getObject() );

                        trace::infrastructure_detail ( "Exiting formula_parser::get_Graph" );

                        // return graph
                        return m_graph;
                }

        } /* namespace infrastructure */
} /* namespace reverse */