/*  test_basic_graph.cpp

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

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test basic graph test suite

#include <boost/test/unit_test.hpp>

#include "libreverse/api/Reverse_Impl.h"
#include "libreverse/errors/Reverse_Exception.h"
#include "libreverse/infrastructure/data_source/Data_Source_T.h"
#include "libreverse/infrastructure/data_source/Memory_Data_Transfer.h"
#include "libreverse/infrastructure/data_source/Memory_Data_Source_Config.h"
#include "libreverse/infrastructure/Formula_Parser.h"
#include "libreverse/components/Null_Component.h"
#include "libreverse/infrastructure/Component.h"
#include "libreverse/infrastructure/Component_Actor.h"
#include "libreverse/infrastructure/Component_Graph.h"
#include "libreverse/infrastructure/Component_State.h"
#include "libreverse/infrastructure/Component_Types.h"
#include "libreverse/components/Component_Factory.h"
#include "config.h"

using namespace boost::unit_test;
using namespace boost::unit_test_framework;
using namespace libreverse::infrastructure;
using namespace libreverse::api;
using namespace libreverse::component;
using namespace libreverse::data_types;
using namespace libreverse;

infrastructure_types::Data_Source<Memory_Data_Transfer>::ptr_t
prepare_Data_Source ( std::string const& target_file )
{
    std::cout << "prepare_Data_Source - target file = " << target_file << std::endl;

    infrastructure_types::Memory_Data_Source_Config::ptr_t mem_config
        ( new infrastructure::Memory_Data_Source_Config () );

    infrastructure_types::Memory_Data_Transfer::ptr_t mem_ptr
        ( new infrastructure::Memory_Data_Transfer ( mem_config ) );

    infrastructure_types::Data_Source < infrastructure::Memory_Data_Transfer >::ptr_t
        input_data  ( new infrastructure::Data_Source < infrastructure::Memory_Data_Transfer > ( mem_ptr ) );

    infrastructure_types::Data_Object::ptr_t input_data_source_ptr
        ( new infrastructure::Data_Object() );

    data_types::Filename::const_ptr_t file_ptr
        ( new data_container::Filename ( target_file ) );

    std::cout << "prepare_Data_Source - stored target file = "
              << file_ptr->to_String() << std::endl;

    input_data_source_ptr->set_Data ( file_ptr );

    input_data->put ( input_data_source_ptr );

    std::cout << "prepare_Data_Source - dump data source" << std::endl;

    std::cout << input_data->to_String() << std::endl;

    return input_data;
}

infrastructure_types::Component::ptr_t
prepare_Component (void)
{
  infrastructure_types::Component_State::ptr_t state_ptr ( new Component_State ( infrastructure::Component::SOURCE_ID ) );
  
  boost::shared_ptr<component::Null_Component> comp_ptr =
    boost::dynamic_pointer_cast<component::Null_Component> ( Component_Factory::Instance().get_Null_Component ( state_ptr ) );

    comp_ptr->add_Data_Output("target_filename");

    return comp_ptr;
}

infrastructure_types::Component_Graph::ptr_t
parse_Graph ( std::string const& filename,
              std::string const& directory )
{
    infrastructure::Formula_Parser parser_ref;
    return parser_ref.get_Graph ( filename, directory );
}

void test_one_node_graph ()
{
    Reverse_Impl m_api;

    infrastructure_types::Component::ptr_t comp_ptr = prepare_Component();

    infrastructure_types::Data_Source<Memory_Data_Transfer>::ptr_t data_ptr =
        prepare_Data_Source ( PWD_PREFIX
                              "/test_targets/kernel32.dll" );


    std::cout << data_ptr->to_String() << std::endl;

    infrastructure::Formula_Parser form_parse_ref;

    infrastructure_types::Component_Graph::Map_ptr_t master_map
        ( new infrastructure_types::Component_Graph::Map_t() );

    (*master_map)["input"] = form_parse_ref.get_Graph ( "one_node.xml",
                                                        PWD_PREFIX
                                                        "/libreverse/api/tests" );

    m_api.execute_Input_Section ( master_map, data_ptr, comp_ptr );
}

void test_one_node_two_graphs ()
{
    Reverse_Impl m_api;

    infrastructure_types::Component::ptr_t comp_ptr = prepare_Component();

    infrastructure_types::Data_Source<Memory_Data_Transfer>::ptr_t data_ptr =
        prepare_Data_Source ( PWD_PREFIX
                              "/test_targets/kernel32.dll" );

    Formula_Parser form_parse_ref;

    infrastructure_types::Component_Graph::Map_ptr_t master_map
        ( new infrastructure_types::Component_Graph::Map_t() );

    (*master_map)["input"] = form_parse_ref.get_Graph ( "one_node.xml",
                                                        PWD_PREFIX
                                                        "/libreverse/api/tests" );
    (*master_map)["analysis"] = form_parse_ref.get_Graph ( "one_node.xml",
                                                           PWD_PREFIX
                                                           "/libreverse/api/tests" );

    Reverse_Impl::Return_Type_t input_results =
        m_api.execute_Input_Section ( master_map, data_ptr, comp_ptr );

    m_api.execute_Analysis_Section ( master_map, input_results );
}

void test_one_node_three_graphs ()
{
    Reverse_Impl m_api;

    infrastructure_types::Component::ptr_t comp_ptr = prepare_Component();

    infrastructure_types::Data_Source<Memory_Data_Transfer>::ptr_t data_ptr =
        prepare_Data_Source ( PWD_PREFIX
                              "/test_targets/kernel32.dll" );

    Formula_Parser form_parse_ref;

    infrastructure_types::Component_Graph::Map_ptr_t master_map
        ( new infrastructure_types::Component_Graph::Map_t() );
    (*master_map)["input"] = form_parse_ref.get_Graph ( "one_node.xml",
                                                        PWD_PREFIX
                                                        "/libreverse/api/tests" );
    (*master_map)["analysis"] = form_parse_ref.get_Graph ( "one_node.xml",
                                                           PWD_PREFIX
                                                           "/libreverse/api/tests" );
    (*master_map)["output"] = form_parse_ref.get_Graph ( "one_node.xml",
                                                         PWD_PREFIX
                                                         "/libreverse/api/tests" );

    Reverse_Impl::Return_Type_t input_results =
        m_api.execute_Input_Section ( master_map, data_ptr, comp_ptr );

    Reverse_Impl::Return_Type_t analysis_results =
        m_api.execute_Analysis_Section ( master_map, input_results );

    m_api.execute_Output_Section ( master_map, analysis_results );
}

test_suite*
init_unit_test_suite ( int , char** )
{
  test_suite* test = BOOST_TEST_SUITE ( "Reverse_Impl test suite" );

  test->add ( BOOST_TEST_CASE ( &test_one_node_graph ) );
  test->add ( BOOST_TEST_CASE ( &test_one_node_two_graphs ) );
  test->add ( BOOST_TEST_CASE ( &test_one_node_three_graphs ) );

  return test;
}

