/*  test_base.h

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

#ifndef JAVA_TEST_BASE
#define JAVA_TEST_BASE

#include "libreverse/io/input/File_Readers/Java_Class/Constant_Pool_Info.h"
#include "libreverse/io/input/File_Readers/Java_Class/Constant_Class_Info.h"
#include "libreverse/io/input/File_Readers/Java_Class/Constant_Fieldref_Info.h"
#include "libreverse/io/input/File_Readers/Java_Class/Constant_Methodref_Info.h"
#include "libreverse/io/input/File_Readers/Java_Class/Constant_Name_And_Type_Info.h"
#include "libreverse/io/input/File_Readers/Java_Class/Constant_Pool_Tags.h"
#include "libreverse/io/input/File_Readers/Java_Class/Constant_String_Info.h"
#include "libreverse/io/input/File_Readers/Java_Class/Constant_Utf8_Info.h"
#include "libreverse/io/input/File_Readers/Java_Class/Java_Types.h"
#include "libreverse/io/input/File_Readers/Java_Class/Line_Number_Table_Attribute.h"

using namespace libreverse;
using namespace libreverse::java_module;

class Test_Base {
public:

    static void check_Constant_Method_Info ( java_types::Constant_Pool_Info::ptr_t pool_ptr,
                                             boost::uint16_t class_index,
                                             boost::uint16_t name_type_index )
    {
        BOOST_CHECK ( pool_ptr->is_Type ( Constant_Pool_Tags::METHOD_REF ) );

        java_types::Constant_Methodref_Info::ptr_t method_ptr =
            boost::dynamic_pointer_cast<Constant_Methodref_Info>(pool_ptr);
        
        BOOST_CHECK_EQUAL ( method_ptr->get_Class_Index(), class_index );
        
        BOOST_CHECK_EQUAL ( method_ptr->get_Name_And_Type_Index(), name_type_index );
    }

    static void check_Constant_Class_Info ( java_types::Constant_Pool_Info::ptr_t pool_ptr,
                                            boost::uint16_t name_index )
    {
        BOOST_CHECK ( pool_ptr->is_Type ( Constant_Pool_Tags::CLASS ) );

        java_types::Constant_Class_Info::ptr_t class_ptr =
            boost::dynamic_pointer_cast<Constant_Class_Info>(pool_ptr);

        BOOST_CHECK_EQUAL ( class_ptr->get_Name_Index(), name_index );    
    }

    static void check_Constant_Field_Info ( java_types::Constant_Pool_Info::ptr_t pool_ptr,
                                            boost::uint16_t class_index,
                                            boost::uint16_t name_type_index )
    {
        BOOST_CHECK ( pool_ptr->is_Type ( Constant_Pool_Tags::FIELD_REF ) );

        java_types::Constant_Fieldref_Info::ptr_t field_ptr =
            boost::dynamic_pointer_cast<Constant_Fieldref_Info>(pool_ptr);

        BOOST_CHECK_EQUAL ( field_ptr->get_Class_Index(), class_index );

        BOOST_CHECK_EQUAL ( field_ptr->get_Name_And_Type_Index(), name_type_index );
    }

    static void check_Constant_String_Info ( java_types::Constant_Pool_Info::ptr_t pool_ptr,
                                             boost::uint16_t string_index )
    {
        BOOST_CHECK ( pool_ptr->is_Type ( Constant_Pool_Tags::STRING ) );

        java_types::Constant_String_Info::ptr_t string_ptr =
            boost::dynamic_pointer_cast<Constant_String_Info>(pool_ptr);

        BOOST_CHECK_EQUAL ( string_ptr->get_String_Index(), string_index );    
    }

    static void check_Constant_Utf8_Info ( java_types::Constant_Pool_Info::ptr_t pool_ptr,
                                           boost::uint16_t length,
                                           std::string text )
    {
        BOOST_CHECK ( pool_ptr->is_Type ( Constant_Pool_Tags::UTF8 ) );

        java_types::Constant_Utf8_Info::ptr_t utf8_ptr =
            boost::dynamic_pointer_cast<Constant_Utf8_Info>(pool_ptr);

        BOOST_CHECK_EQUAL ( utf8_ptr->get_Length(), length );    

        BOOST_CHECK_EQUAL ( utf8_ptr->get_Text(), text );
    }

    static void check_Constant_Name_And_Type_Info ( java_types::Constant_Pool_Info::ptr_t pool_ptr,
                                                    boost::uint16_t name_index,
                                                    boost::uint16_t desc_index )
    {
        BOOST_CHECK ( pool_ptr->is_Type ( Constant_Pool_Tags::NAME_AND_TYPE ) );

        java_types::Constant_Name_And_Type_Info::ptr_t name_and_type_ptr =
            boost::dynamic_pointer_cast<Constant_Name_And_Type_Info>(pool_ptr);

        BOOST_CHECK_EQUAL ( name_and_type_ptr->get_Name_Index(), name_index );

        BOOST_CHECK_EQUAL ( name_and_type_ptr->get_Descriptor_Index(),
                            desc_index );
    }

    static void check_Line_Number_Table_Attribute ( java_types::Attribute_Info::ptr_t attrib_ptr,
                                                    boost::uint16_t name_index,
						    std::string
                                                    boost::uint16_t desc_index )
    {
        BOOST_CHECK ( attrib_ptr->is_Type ( Attribute_Tags::LINE_NUMBER_TABLE ) );

	java_types::Line_Number_Table_Attribute::const_ptr_t line_number_ptr =
	  boost::dynamic_pointer_cast<Line_Number_Table_Attribute const>(attrib_ptr);

        BOOST_CHECK_EQUAL ( line_number_ptr->get_Name_Index(), name_index );

        BOOST_CHECK_EQUAL ( name_and_type_ptr->get_Descriptor_Index(),
                            desc_index );
    }

};

#endif /* JAVA_TEST_BASE */
