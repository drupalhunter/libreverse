/*  test_fibonacci.cpp

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

#include <boost/test/unit_test.hpp>
#include "libreverse/io/input/File_Readers/Java_Class/Reader.h"
#include "libreverse/io/input/File_Readers/Java_Class/Class_Header.h"
#include "libreverse/io/input/File_Readers/Java_Class/Method_Info.h"
#include "libreverse/io/input/File_Readers/Java_Class/Attribute_Info.h"
#include "libreverse/io/input/File_Readers/Java_Class/Attribute_Tags.h"
#include "libreverse/io/input/File_Readers/Java_Class/Code_Attribute.h"
#include "test_base.h"
#include "libreverse/io/File_ID.h"
#include "libreverse/data_containers/memory_map.h"
#include <iostream>
#include "libreverse/include/config.h"

using namespace libreverse::java_module;
using namespace boost::unit_test;
using namespace boost::unit_test_framework;

void check_Constant_Pool_Info ( java_types::Class_Header::Constant_Pool_Info_Map_t::const_iterator pool_ptr )
{
    // #1
  Test_Base::check_Constant_Method_Info ( (*pool_ptr).second, 0xE, 0x1B );
  ++pool_ptr;

  // #2
  Test_Base::check_Constant_Method_Info ( (*pool_ptr).second, 0x3, 0x1C );
  ++pool_ptr;

  // #3
  Test_Base::check_Constant_Class_Info ( (*pool_ptr).second, 0x1D );
  ++pool_ptr;

  // #4
  Test_Base::check_Constant_Method_Info ( (*pool_ptr).second, 0x3, 0x1B );
  ++pool_ptr;    

  // #5
  Test_Base::check_Constant_Method_Info ( (*pool_ptr).second, 0x1E, 0x1F );
  ++pool_ptr;

  // #6
  Test_Base::check_Constant_Field_Info ( (*pool_ptr).second, 0x20, 0x21 );
  ++pool_ptr;

  // #7
  Test_Base::check_Constant_Class_Info ( (*pool_ptr).second, 0x22 );
  ++pool_ptr;

  // #8
  Test_Base::check_Constant_Method_Info ( (*pool_ptr).second, 0x7, 0x1B );
  ++pool_ptr;

  // #9
  Test_Base::check_Constant_String_Info ( (*pool_ptr).second, 0x23 );
  ++pool_ptr;

  // #10
  Test_Base::check_Constant_Method_Info ( (*pool_ptr).second, 0x7, 0x24 );
  ++pool_ptr;

  // #11
  Test_Base::check_Constant_Method_Info ( (*pool_ptr).second, 0x7, 0x25 );
  ++pool_ptr;

  // #12
  Test_Base::check_Constant_Method_Info ( (*pool_ptr).second, 0x7, 0x26 );
  ++pool_ptr;

  // #13
  Test_Base::check_Constant_Method_Info ( (*pool_ptr).second, 0x27, 0x28 );
  ++pool_ptr;

  // #14
  Test_Base::check_Constant_Class_Info ( (*pool_ptr).second, 0x29 );
  ++pool_ptr;

  // #15
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x6, "<init>" );
  ++pool_ptr;

  // #16
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x3, "()V" );
  ++pool_ptr;

  // #17
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x4, "Code" );
  ++pool_ptr;

  // #18
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0xF, "LineNumberTable" );
  ++pool_ptr;

  // #19
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x9, "calculate" );
  ++pool_ptr;

  // #20
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x4, "(I)I" );
  ++pool_ptr;

  // #21
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0xD, "StackMapTable" );
  ++pool_ptr;

    // #22
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x4, "main" );
  ++pool_ptr;
  
  // #23
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x16, "([Ljava/lang/String;)V" );
  ++pool_ptr;

  // #24
  Test_Base::check_Constant_Class_Info ( (*pool_ptr).second, 0x1D );
  ++pool_ptr;

  // #25
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0xA, "SourceFile" );
  ++pool_ptr;

  // #26
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0xE, "Fibonacci.java" );
  ++pool_ptr;

  // #27
  Test_Base::check_Constant_Name_And_Type_Info ( (*pool_ptr).second, 0xF, 0x10 );
  ++pool_ptr;

  // #28
  Test_Base::check_Constant_Name_And_Type_Info ( (*pool_ptr).second, 0x13, 0x14 );
  ++pool_ptr;

  // #29
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x9, "Fibonacci" );
  ++pool_ptr;
  
  // #30
  Test_Base::check_Constant_Class_Info ( (*pool_ptr).second, 0x2A );
  ++pool_ptr;

  // #31
  Test_Base::check_Constant_Name_And_Type_Info ( (*pool_ptr).second, 0x2B, 0x2C );
  ++pool_ptr;

  // #32
  Test_Base::check_Constant_Class_Info ( (*pool_ptr).second, 0x2D );
  ++pool_ptr;

  // #33
  Test_Base::check_Constant_Name_And_Type_Info ( (*pool_ptr).second, 0x2E, 0x2F );
  ++pool_ptr;

  // #34
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x17, "java/lang/StringBuilder" );
  ++pool_ptr;

  // #35
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x1D, "Calculated fibonacci number: " );
  ++pool_ptr;
    
  // #36
  Test_Base::check_Constant_Name_And_Type_Info ( (*pool_ptr).second, 0x30, 0x31 );
  ++pool_ptr;

  // #37
  Test_Base::check_Constant_Name_And_Type_Info ( (*pool_ptr).second, 0x30, 0x32 );
  ++pool_ptr;

  // #38
  Test_Base::check_Constant_Name_And_Type_Info ( (*pool_ptr).second, 0x33, 0x34 );
  ++pool_ptr;

  // #39
  Test_Base::check_Constant_Class_Info ( (*pool_ptr).second, 0x35 );
  ++pool_ptr;

  // #40
  Test_Base::check_Constant_Name_And_Type_Info ( (*pool_ptr).second, 0x36, 0x37 );
  ++pool_ptr;

  // #41
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x10, "java/lang/Object" );
  ++pool_ptr;

  // #42
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x11, "java/lang/Integer" );
  ++pool_ptr;
    
  // #43
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x8, "parseInt" );
  ++pool_ptr;

  // #44
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x15, "(Ljava/lang/String;)I" );
  ++pool_ptr;

  // #45
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x10, "java/lang/System" );
  ++pool_ptr;

  // #46
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x3, "out" );
  ++pool_ptr;

  // #47
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x15, "Ljava/io/PrintStream;" );
  ++pool_ptr;

  // #48
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x6, "append" );
  ++pool_ptr;

  // #49
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x2D, "(Ljava/lang/String;)Ljava/lang/StringBuilder;" );
  ++pool_ptr;

  // #50
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x1C, "(I)Ljava/lang/StringBuilder;" );
  ++pool_ptr;

  // #51
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x8, "toString" );
  ++pool_ptr;

  // #52
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x14, "()Ljava/lang/String;" );
  ++pool_ptr;

  // #53
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x13, "java/io/PrintStream" );
  ++pool_ptr;

  // #54
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x7, "println" );
  ++pool_ptr;

  // #55
  Test_Base::check_Constant_Utf8_Info ( (*pool_ptr).second, 0x15, "(Ljava/lang/String;)V" );
}

void check_Method_Info_One ( java_types::Method_Info::ptr_t method_ptr )
{
    BOOST_CHECK_EQUAL ( method_ptr->get_Access_Flags(),
                        static_cast<boost::uint16_t>(0x0) );

    BOOST_CHECK_EQUAL ( method_ptr->get_Name_Index(),
                        static_cast<boost::uint16_t>(0xF) );

    BOOST_CHECK_EQUAL ( method_ptr->get_Descriptor_Index(),
                        static_cast<boost::uint16_t>(0x10) );

    BOOST_CHECK_EQUAL ( method_ptr->get_Attributes_Count(),
                        static_cast<boost::uint16_t>(0x1) );

    java_types::Class_Header::Attribute_Info_Map_t::const_iterator attrib_pos = method_ptr->attribute_Begin();

    java_types::Attribute_Info::ptr_t attrib_ptr = (*attrib_pos).second;

    BOOST_CHECK ( attrib_ptr->is_Type ( Attribute_Tags::CODE ) );

    java_types::Code_Attribute::ptr_t code_ptr =
        boost::dynamic_pointer_cast<Code_Attribute>(attrib_ptr);

    BOOST_CHECK_EQUAL ( code_ptr->get_Name_Index(),
                        static_cast<boost::uint16_t>(0x11) );

    BOOST_CHECK_EQUAL ( code_ptr->get_Attribute_Length(),
                        static_cast<boost::uint16_t>(0x1D) );

    BOOST_CHECK_EQUAL ( code_ptr->get_Max_Stack(),
                        static_cast<boost::uint16_t>(0x1) );

    BOOST_CHECK_EQUAL ( code_ptr->get_Max_Locals(),
                        static_cast<boost::uint16_t>(0x1) );

    BOOST_CHECK_EQUAL ( code_ptr->get_Code_Length(),
                        static_cast<boost::uint32_t>(0x15) );

    BOOST_CHECK_EQUAL ( code_ptr->get_Name_Index(),
                        static_cast<boost::uint16_t>(0x11) );

    java_types::Code_Attribute::Code_List_t::const_iterator code_list_pos =
        code_ptr->get_Code_Begin();

    BOOST_CHECK_EQUAL ( (*code_list_pos),
                        static_cast<boost::uint8_t>(0x2A) );
    ++code_list_pos;

    BOOST_CHECK_EQUAL ( (*code_list_pos),
                        static_cast<boost::uint8_t>(0xB7) );
    ++code_list_pos;

    BOOST_CHECK_EQUAL ( (*code_list_pos),
                        static_cast<boost::uint8_t>(0x00) );
    ++code_list_pos;

    BOOST_CHECK_EQUAL ( (*code_list_pos),
                        static_cast<boost::uint8_t>(0x01) );
    ++code_list_pos;

    BOOST_CHECK_EQUAL ( (*code_list_pos),
                        static_cast<boost::uint8_t>(0xB1) );

    BOOST_CHECK_EQUAL ( code_ptr->get_Exception_Table_Length(),
                        static_cast<boost::uint16_t>(0x0) );

    BOOST_CHECK_EQUAL ( code_ptr->get_Attributes_Count(),
                        static_cast<boost::uint16_t>(0x1) );

    java_types::Code_Attribute::Attribute_Table_t::const_iterator code_attrib_pos = code_ptr->get_Attributes_Begin();
    
    Test_Base::check_Line_Number_Table_Attribute ( (*code_attrib_pos),
						   
}

void test_class_header_read ()
{
    io_types::File_ID::ptr_t m_file ( new libreverse::io::File_ID ( PWD_PREFIX
                                                                    "/test_targets/Fibonacci.class" ) );

    Reader m_reader ( m_file, true, true );

    m_reader.read_Class_Header ();

    java_types::Class_Header::ptr_t class_ptr = m_reader.get_Header ();

    BOOST_CHECK_EQUAL ( class_ptr->get_Magic_Number(),
                        Class_Header::CLASS_MAGIC_SIGNATURE );

    BOOST_CHECK_EQUAL ( class_ptr->get_Minor_Version(),
                        static_cast<boost::uint16_t>(0) );

    BOOST_CHECK_EQUAL ( class_ptr->get_Major_Version(),
                        static_cast<boost::uint16_t>(50) );

    BOOST_CHECK_EQUAL ( class_ptr->get_Constant_Pool_Count(),
                        static_cast<boost::uint16_t>(56) );

    check_Constant_Pool_Info ( class_ptr->get_Constant_Pool_Begin() );

    BOOST_CHECK_EQUAL ( class_ptr->get_Access_Flags(),
                        static_cast<boost::uint16_t>(32) );

    BOOST_CHECK_EQUAL ( class_ptr->get_This_Class(),
                        static_cast<boost::uint16_t>(3) );

    BOOST_CHECK_EQUAL ( class_ptr->get_Super_Class(),
                        static_cast<boost::uint16_t>(14) );

    BOOST_CHECK_EQUAL ( class_ptr->get_Interfaces_Count(),
                        static_cast<boost::uint16_t>(0) );

    BOOST_CHECK_EQUAL ( class_ptr->get_Field_Count(),
                        static_cast<boost::uint16_t>(0) );

    BOOST_CHECK_EQUAL ( class_ptr->get_Method_Count(),
                        static_cast<boost::uint16_t>(3) );

    java_types::Class_Header::Method_Info_Map_t::const_iterator method_pos =
        class_ptr->get_Method_Begin();

    //check_Method_Info ( (*method_pos).second );

    BOOST_CHECK_EQUAL ( class_ptr->get_Attribute_Count(),
                        static_cast<boost::uint16_t>(1) );
    
}

test_suite*
init_unit_test_suite ( int , char** )
{
    test_suite* test = BOOST_TEST_SUITE ( "Fibonacci test suite" );

    test->add ( BOOST_TEST_CASE ( &test_class_header_read ) );

    return test;
}
