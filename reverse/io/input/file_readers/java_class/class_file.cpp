/*  Class_File.cpp

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

#include "Class_File.h"
#include "Append_Frame.h"
#include "Attribute_Info.h"
#include "Attribute_Info_Factory.h"
#include "Chop_Frame.h"
#include "Class_Header.h"
#include "Code_Attribute.h"
#include "Constant_Class_Info.h"
#include "Constant_Double_Info.h"
#include "Constant_Fieldref_Info.h"
#include "Constant_Float_Info.h"
#include "Constant_Info_Factory.h"
#include "Constant_Integer_Info.h"
#include "Constant_InterfaceMethodref_Info.h"
#include "Constant_Long_Info.h"
#include "Constant_Methodref_Info.h"
#include "Constant_Name_And_Type_Info.h"
#include "Constant_Pool_Info.h"
#include "Constant_Pool_Tags.h"
#include "Constant_String_Info.h"
#include "Constant_Utf8_Info.h"
#include "Constant_Value_Attribute.h"
#include "Deprecated_Attribute.h"
#include "Enclosing_Method_Attribute.h"
#include "Exceptions_Attribute.h"
#include "Exception_Table_Entry.h"
#include "Field_Info.h"
#include "Full_Frame.h"
#include "Inner_Classes_Attribute.h"
#include "Inner_Class_Reference.h"
#include "Line_Number_Item.h"
#include "Line_Number_Table_Attribute.h"
#include "Local_Variable.h"
#include "Local_Variable_Table_Attribute.h"
#include "Method_Info.h"
#include "Object_Variable_Info.h"
#include "Same_Frame_Extended.h"
#include "Same_Locals_One_Stack_Item_Frame.h"
#include "Same_Locals_One_Stack_Item_Frame_Extended.h"
#include "Signature_Attribute.h"
#include "Source_File_Attribute.h"
#include "Stack_Map_Frame_Factory.h"
#include "Stack_Map_Table_Attribute.h"
#include "Synthetic_Attribute.h"
#include "Unknown_Attribute.h"
#include "Uninitialized_Variable_Info.h"
#include "Verification_Type_Factory.h"
#include "Verification_Type_Info.h"

#include "io/Byte_Converter.h"
#include "io/File_ID.h"
#include "io/Preconditions.h"
#include "io/String_Converter.h"
#include "errors/Internal_Exception.h"

#include <iostream>
#include <math.h>
#include <float.h>
#include <boost/format.hpp>



using namespace reverse::io;

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse { namespace java_module {

    Class_File::Class_File ( io_types::File_ID::const_ptr_t filename)
        : m_file ( filename )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File (string) constructor" );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "filename: %1%" ) % filename ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File (string) constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Class_File::Class_File ( data_types::memory_map::ptr_t file_img_ptr,
                             io_types::File_ID::const_ptr_t filename )
        : m_file ( file_img_ptr, filename )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File (memory_map,string) constructor" );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "filename: %1%" ) % filename ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File (memory_map,string) constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    bool
    Class_File::init (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_File::init" );
#endif /* LIBREVERSE_DEBUG */


        return m_file.init();
    }

    void Class_File::read_Class_Header ( java_types::Class_Header::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Class_Header" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read(&(obj->m_magic));

        io::Byte_Converter::convert ( obj->m_magic );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Magic: %|2$X|" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_magic ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read(&(obj->m_minor_version));
        io::Byte_Converter::convert ( obj->m_minor_version );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Minor version: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_minor_version
                                          % obj->m_minor_version ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read(&(obj->m_major_version));
        io::Byte_Converter::convert ( obj->m_major_version );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Major version: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_major_version
                                          % obj->m_major_version ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read(&(obj->m_constant_pool_count));
        io::Byte_Converter::convert ( obj->m_constant_pool_count );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Constant pool count: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_constant_pool_count
                                          % obj->m_constant_pool_count ) );
#endif /* LIBREVERSE_DEBUG */


        // For X = 1 to m_constant_pool_count - 1
        for ( boost::uint16_t i = 1;
              i <= obj->m_constant_pool_count - 1;
              ++i )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::IO,
                                     TraceLevel::DATA,
                                     boost::str ( boost::format ( " -- Constant Pool Item #%1% ---" ) % i ) );
#endif /* LIBREVERSE_DEBUG */


                //   Read Constant_Pool
                java_types::Constant_Pool_Info::ptr_t new_cp_ptr = this->read_Constant_Pool_Info ();

		//   Long and Double constant pool entries take up
		//   "two spots" in the constant pool table
		if ( ( new_cp_ptr->get_Tag() == Constant_Pool_Tags::LONG ) ||
		     ( new_cp_ptr->get_Tag() == Constant_Pool_Tags::DOUBLE ) )
		  {
		    ++i;
		  }

                //   Add to m_constant_pool
                obj->m_constant_pool.insert ( std::make_pair ( i, new_cp_ptr ) );
            }


        m_file.read(&(obj->m_access_flags));
        io::Byte_Converter::convert ( obj->m_access_flags );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Access flags: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_access_flags
                                          % obj->m_access_flags ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read(&(obj->m_this_class));
        io::Byte_Converter::convert ( obj->m_this_class );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) This class: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_this_class
                                          % obj->m_this_class ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read(&(obj->m_super_class));
        io::Byte_Converter::convert ( obj->m_super_class );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Super class: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_super_class
                                          % obj->m_super_class ) );
#endif /* LIBREVERSE_DEBUG */


        // For x = 0 to m_interaces_count
        //   Create boost::uint16_t
        //   Read boost::uint16_t
        //   Add value to m_interfaces
        m_file.read(&(obj->m_interfaces_count));
        io::Byte_Converter::convert ( obj->m_interfaces_count );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Interfaces count: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_interfaces_count
                                          % obj->m_interfaces_count ) );
#endif /* LIBREVERSE_DEBUG */


        if ( obj->m_interfaces_count > 0 )
            {
                boost::uint16_t val = 0;

                for ( boost::uint16_t i = 0;
                      i < obj->m_interfaces_count;
                      ++i )
                    {

#ifdef LIBREVERSE_DEBUG
                        Trace::write_Trace ( TraceArea::IO,
                                             TraceLevel::DATA,
                                             boost::str ( boost::format ( " -- Interface #%1% ---" ) % i ) );
#endif /* LIBREVERSE_DEBUG */


                        m_file.read(&val);
                        io::Byte_Converter::convert ( val );
                        obj->m_interfaces.push_back ( val );


#ifdef LIBREVERSE_DEBUG
			Trace::write_Trace ( TraceArea::IO,
					     TraceLevel::DATA,
					     boost::str ( boost::format ( "(0x%|1$X|) Value = %|2$d| (%|3$X|0)" )
							  % m_file.get_Map_Ptr()->get_Previous_Position_Address()
							  % val
							  % val ) );
#endif /* LIBREVERSE_DEBUG */


                    }
            }

        // For X = 0 to m_field_count
        //   Create Field_Info pointer
        //   Read Field_Info
        //   Add to m_fields
        m_file.read(&(obj->m_field_count));
        io::Byte_Converter::convert ( obj->m_field_count );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Field count: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_field_count
                                          % obj->m_field_count ) );
#endif /* LIBREVERSE_DEBUG */


        if ( obj->m_field_count > 0 )
            {
                for ( boost::uint16_t i = 0;
                      i < obj->m_field_count;
                      ++i )
                    {

#ifdef LIBREVERSE_DEBUG
                        Trace::write_Trace ( TraceArea::IO,
                                             TraceLevel::DATA,
                                             boost::str ( boost::format ( " -- Field #%1% ---" ) % i ) );
#endif /* LIBREVERSE_DEBUG */


                        java_types::Field_Info::ptr_t new_fi_ptr ( new Field_Info () );
		
                        this->read_Field_Info ( new_fi_ptr, obj );
		
                        obj->m_fields.insert ( std::make_pair ( i, new_fi_ptr ) );
                    }
            }

        // For X = 0 to m_methods_count
        //   Create Method_Info pointer
        //   Read Method_Info
        //   Add to m_methods
        m_file.read(&(obj->m_methods_count));
        io::Byte_Converter::convert ( obj->m_methods_count );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Methods count: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_methods_count
                                          % obj->m_methods_count ) );
#endif /* LIBREVERSE_DEBUG */


        if ( obj->m_methods_count > 0 )
            {
                for ( boost::uint16_t i = 0;
                      i < obj->m_methods_count;
                      ++i )
                    {

#ifdef LIBREVERSE_DEBUG
                        Trace::write_Trace ( TraceArea::IO,
                                             TraceLevel::DATA,
                                             boost::str ( boost::format ( " -- Method #%1% ---" ) % i ) );
#endif /* LIBREVERSE_DEBUG */


                        java_types::Method_Info::ptr_t new_mi_ptr ( new Method_Info () );

                        this->read_Method_Info ( new_mi_ptr,
                                                 obj );

                        obj->m_methods.insert ( std::make_pair ( i, new_mi_ptr ) );
                    }
            }

        // For X = 0 to m_attributes_count
        //   Create Attribute_Info pointer
        //   Read Attribute_Info
        //   Add to m_attributes

        m_file.read(&(obj->m_attributes_count));
        io::Byte_Converter::convert ( obj->m_attributes_count );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Attributes count: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_attributes_count
                                          % obj->m_attributes_count ) );

        if ( obj->m_attributes_count > 0 )
            {
                for ( boost::uint16_t i = 0;
                      i < obj->m_attributes_count;
                      ++i )
                    {
                        Trace::write_Trace ( TraceArea::IO,
                                             TraceLevel::DATA,
                                             boost::str ( boost::format ( " -- Attribute #%1% ---" ) % i ) );

                        //   Read Attribute_Info
                        Attribute_Info::ptr_t new_attribute_info_ptr =
                            this->read_Attribute_Info ( obj );

                        obj->m_attributes.insert
                            ( std::make_pair ( i, new_attribute_info_ptr ) );
                    }
            }

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Class_Header" );
#endif /* LIBREVERSE_DEBUG */

    }

    java_types::Constant_Pool_Info::ptr_t
    Class_File::read_Constant_Pool_Info ( void )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Constant_Pool_Info" );
#endif /* LIBREVERSE_DEBUG */


        boost::uint8_t tag = 0;
        m_file.read(&( tag ));


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) ID found: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % static_cast<boost::uint16_t>(tag)
                                          % static_cast<boost::uint16_t>(tag) ) );
#endif /* LIBREVERSE_DEBUG */


        // Based on the value of 'tag' determines what we do
        // here. Implement the factory pattern which will create the
        // appropriate object but return a Constant_Pool_Info pointer.
        java_types::Constant_Pool_Info::ptr_t cpi_ptr =  Constant_Info_Factory::create ( tag );

        cpi_ptr->read_Input ( this->shared_from_this() );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "Constant component found was: %1%" ) % cpi_ptr->to_String() ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Constant_Pool_Info" );
#endif /* LIBREVERSE_DEBUG */

        return cpi_ptr;
    }

    void
    Class_File::read_Field_Info ( java_types::Field_Info::ptr_t obj,
                                  java_types::Class_Header::ptr_t hdr_obj )
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Field_Info" );
#endif /* LIBREVERSE_DEBUG */

	io::Preconditions::is_set ( obj );
	io::Preconditions::is_set ( hdr_obj );

        m_file.read(&(obj->m_access_flags));
        io::Byte_Converter::convert ( obj->m_access_flags );

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Access flags: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_access_flags
                                          % obj->m_access_flags ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read(&(obj->m_name_index));
        io::Byte_Converter::convert ( obj->m_name_index );
	obj->m_name_string = this->get_String_From_Constant_Pool ( obj->m_name_index, hdr_obj );
	
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Name index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_name_index
                                          % obj->m_name_index ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read(&(obj->m_descriptor_index));
        io::Byte_Converter::convert ( obj->m_descriptor_index );
	obj->m_descriptor_string = this->get_String_From_Constant_Pool ( obj->m_descriptor_index, hdr_obj );

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Descriptor index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_descriptor_index
                                          % obj->m_descriptor_index ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read(&(obj->m_attributes_count));
        io::Byte_Converter::convert ( obj->m_attributes_count );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Attribute count: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_attributes_count
                                          % obj->m_attributes_count ) );
#endif /* LIBREVERSE_DEBUG */


        for ( boost::uint16_t i = 0;
              i < obj->m_attributes_count;
              ++i )
            {

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   boost::str ( boost::format ( "--- Attribute #%1% ---" ) % i ) );
#endif /* LIBREVERSE_DEBUG */


                Attribute_Info::ptr_t new_ai_ptr = this->read_Attribute_Info ( hdr_obj );

                obj->m_attributes.insert ( std::make_pair ( i, new_ai_ptr ) );
            }

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Field_Info" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Method_Info ( java_types::Method_Info::ptr_t obj,
                                   java_types::Class_Header::ptr_t hdr_obj )
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Method_Info" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );
	io::Preconditions::is_set ( hdr_obj );

        m_file.read(&(obj->m_access_flags));
        io::Byte_Converter::convert ( obj->m_access_flags );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Access flags: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_access_flags
                                          % obj->m_access_flags ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read(&(obj->m_name_index));
        io::Byte_Converter::convert ( obj->m_name_index );
        obj->m_name_string = hdr_obj->get_String_Constant ( obj->m_name_index );	

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Name (%2$s) index: %|3$d| (%|4$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
					  % obj->m_name_string
                                          % obj->m_name_index
                                          % obj->m_name_index ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read(&(obj->m_descriptor_index));
        io::Byte_Converter::convert ( obj->m_descriptor_index );
        obj->m_descriptor_string = hdr_obj->get_String_Constant ( obj->m_descriptor_index );

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Descriptor (%2$s)  index: %|3$d| (%|4$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
					  % obj->m_descriptor_string
                                          % obj->m_descriptor_index
                                          % obj->m_descriptor_index ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read(&(obj->m_attributes_count));
        io::Byte_Converter::convert ( obj->m_attributes_count );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Attribute count: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_attributes_count
                                          % obj->m_attributes_count ) );
#endif /* LIBREVERSE_DEBUG */


        for ( boost::uint16_t i = 0;
              i < obj->m_attributes_count;
              ++i )
            {

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   boost::str ( boost::format ( "--- Attribute #%1% ---" ) % i ) );
#endif /* LIBREVERSE_DEBUG */


                Attribute_Info::ptr_t new_ai_ptr = this->read_Attribute_Info ( hdr_obj );

                obj->m_attributes.insert ( std::make_pair ( i, new_ai_ptr ) );
            }

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Method_Info" );
#endif /* LIBREVERSE_DEBUG */

    }

    Attribute_Info::ptr_t
    Class_File::read_Attribute_Info ( java_types::Class_Header::ptr_t hdr_obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Enterng Class_File::read_Attribute_Info" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( hdr_obj );

        boost::uint16_t tag = 0;
        m_file.read(&( tag ));
        io::Byte_Converter::convert ( tag );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "Tag found: 0x%|1$d| (0x%|2$X|)")
					  % static_cast<boost::uint16_t>(tag)
					  % static_cast<boost::uint16_t>(tag) ) );
#endif /* LIBREVERSE_DEBUG */


        // Based on the value of 'tag' determines what we do
        // here. Implement the factory pattern which will create the
        // appropriate object but return a Attribute_Info pointer.

        std::string tag_name = hdr_obj->get_String_Constant ( tag );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "Tag name: %1%") % tag_name ) );
#endif /* LIBREVERSE_DEBUG */


        Attribute_Info::ptr_t attribute_info_ptr = Attribute_Info_Factory::create ( tag, tag_name );

        attribute_info_ptr->read_Input ( this->shared_from_this(),
                                         hdr_obj );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "Attribute found was:\n %1%") % attribute_info_ptr->to_String() ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Attribute_Info" );
#endif /* LIBREVERSE_DEBUG */


        return attribute_info_ptr;
    }

    void
    Class_File::read_Inner_Class_Reference ( java_types::Inner_Class_Reference::ptr_t obj,
                                             java_types::Class_Header::ptr_t hdr_ptr )
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Inner_Class_Reference" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_inner_class_info_index) );
        io::Byte_Converter::convert ( obj->m_inner_class_info_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Inner class info index: %|2$d| (%|3$X|)")
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_inner_class_info_index
                                          % obj->m_inner_class_info_index ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_outer_class_info_index) );
        io::Byte_Converter::convert ( obj->m_outer_class_info_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Outer class info index: %|2$d| (%|3$X|)")
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_outer_class_info_index
                                          % obj->m_outer_class_info_index ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_inner_name_index) );
        io::Byte_Converter::convert ( obj->m_inner_name_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Inner name index: %|2$d| (%|3$X|)")
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_inner_name_index
                                          % obj->m_inner_name_index ) );
#endif /* LIBREVERSE_DEBUG */

	if ( obj->m_inner_name_index != 0 )
	  {
	    obj->m_inner_name = hdr_ptr->get_String_Constant ( obj->m_inner_name_index );
	  }
	else
	  {
	    obj->m_inner_name = "<anonymous>";
	  }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Inner class name: %|2$s|")
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_inner_name
                                          % obj->m_inner_name ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_inner_class_access_flags) );
        io::Byte_Converter::convert ( obj->m_inner_class_access_flags );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Inner class access flags: %|2$d| (%|3$X|)")
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_inner_class_access_flags
                                          % obj->m_inner_class_access_flags ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Inner_Class_Reference" );
#endif /* LIBREVERSE_DEBUG */


    }

    void
    Class_File::read_Line_Number_Item ( java_types::Line_Number_Item::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Line_Number_Item" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_start_pc) );
        io::Byte_Converter::convert ( obj->m_start_pc );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Start program counter: %|2$d| (%|3$X|)")
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_start_pc
                                          % obj->m_start_pc ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_line_number ) );
        io::Byte_Converter::convert ( obj->m_line_number );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Line number: %|2$d| (%|3$X|)")
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_line_number
                                          % obj->m_line_number ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Line_Number_Item" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Append_Frame ( java_types::Append_Frame::ptr_t obj )
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Append_Frame" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_offset_delta) );
        io::Byte_Converter::convert ( obj->m_offset_delta );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Offset delta: %|2$d| (%|3$X|)")
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_offset_delta
                                          % obj->m_offset_delta ) );
#endif /* LIBREVERSE_DEBUG */


        boost::uint8_t local_count = obj->m_tag - 251;
        boost::uint8_t verification_tag = 0;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format("Local count total: #%1%") % static_cast<boost::uint16_t>(local_count) ) );
#endif /* LIBREVERSE_DEBUG */


        for ( boost::uint8_t i = 0; i < local_count; ++i )
            {

#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   boost::str ( boost::format("Local count #%1%") % static_cast<boost::uint16_t>(i) ) );
#endif /* LIBREVERSE_DEBUG */


                m_file.read ( &verification_tag );

                java_types::Verification_Type_Info::ptr_t data_ptr = Verification_Type_Factory::create ( verification_tag );

                data_ptr->read_Input ( this->shared_from_this() );

                obj->m_data.push_back ( data_ptr );
            }

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Append_Frame" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Source_File_Attribute ( java_types::Source_File_Attribute::ptr_t obj,
                                             java_types::Class_Header::ptr_t hdr_ptr )
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Source_File_Attribute " );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

	m_file.read ( &(obj->m_attribute_length) );
	io::Byte_Converter::convert ( obj->m_attribute_length );

        m_file.read ( &(obj->m_source_file_index) );
        io::Byte_Converter::convert ( obj->m_source_file_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Source file index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_source_file_index
                                          % obj->m_source_file_index ) );
#endif /* LIBREVERSE_DEBUG */


        obj->m_source_file_name = hdr_ptr->get_String_Constant ( obj->m_source_file_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Name: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_source_file_name
                                          % obj->m_source_file_name ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Source_File_Attribute" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Code_Attribute ( java_types::Code_Attribute::ptr_t obj,
                                      java_types::Class_Header::ptr_t hdr_ptr )
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Code_Attribute" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_attribute_length) );
        io::Byte_Converter::convert ( obj->m_attribute_length );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Attribute length: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_attribute_length
                                          % obj->m_attribute_length ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_max_stack) );
        io::Byte_Converter::convert ( obj->m_max_stack );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Max stack: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_max_stack
                                          % obj->m_max_stack ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_max_locals) );
        io::Byte_Converter::convert ( obj->m_max_locals );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Max locals: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_max_locals
                                          % obj->m_max_locals ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_code_length) );
        io::Byte_Converter::convert ( obj->m_code_length );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Code length: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_code_length
                                          % obj->m_code_length ) );

#endif /* LIBREVERSE_DEBUG */


        boost::uint8_t byte = 0;
        for ( boost::uint16_t i = 0;
              i < obj->m_code_length;
              ++i )
            {
                m_file.read ( &byte );
                obj->m_code.push_back ( byte );


#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::IO,
                                     TraceLevel::DATA,
                                     boost::str ( boost::format ( "(0x%|1$X|) Byte: %|2$02X|" )
                                                  % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                                  % static_cast<boost::uint16_t>( byte ) ) );
#endif /* LIBREVERSE_DEBUG */

            }


        m_file.read ( &(obj->m_exception_table_length) );
        io::Byte_Converter::convert ( obj->m_exception_table_length );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Exception table length: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_exception_table_length
                                          % obj->m_exception_table_length ) );
#endif /* LIBREVERSE_DEBUG */


	// Read exception table entries
        for ( boost::uint16_t i = 0;
              i < obj->m_exception_table_length;
              ++i )
            {
	      java_types::Exception_Table_Entry::ptr_t except_ptr = this->read_Exception_Table_Entry ();

	      obj->m_exception_table.push_back ( except_ptr );
            }

        java_types::Attribute_Info::ptr_t attrib_ptr;

        m_file.read ( &obj->m_attributes_count );
        io::Byte_Converter::convert ( obj->m_attributes_count );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Attribute count: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_attributes_count
                                          % obj->m_attributes_count ) );
#endif /* LIBREVERSE_DEBUG */


        for ( boost::uint16_t i = 0;
              i < obj->m_attributes_count;
              ++i )
            {
                attrib_ptr = this->read_Attribute_Info ( hdr_ptr );

                obj->m_attributes.push_back ( attrib_ptr );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Code_Attribute" );
#endif /* LIBREVERSE_DEBUG */

    }

    java_types::Exception_Table_Entry::ptr_t 
    Class_File::read_Exception_Table_Entry ()
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Exceptions_Attibute" );
#endif /* LIBREVERSE_DEBUG */


	java_types::Exception_Table_Entry::ptr_t obj ( new java_module::Exception_Table_Entry() );

	io::Preconditions::is_set ( obj );

	m_file.read ( &(obj->m_start_pc) );
	io::Byte_Converter::convert ( obj->m_start_pc );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Start PC: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_start_pc
                                          % obj->m_start_pc ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_end_pc) );
        io::Byte_Converter::convert ( obj->m_end_pc );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) End PC: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_end_pc
                                          % obj->m_end_pc ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_handler_pc) );
        io::Byte_Converter::convert ( obj->m_handler_pc );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) End PC: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_handler_pc
                                          % obj->m_handler_pc ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_catch_type) );
        io::Byte_Converter::convert ( obj->m_catch_type );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) End PC: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_catch_type
                                          % obj->m_catch_type ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Exception_Table_Entry" );
#endif /* LIBREVERSE_DEBUG */


	return obj;
    }

    void
    Class_File::read_Line_Number_Table_Attribute ( java_types::Line_Number_Table_Attribute::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Line_Number_Table_Attibute" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

	m_file.read ( &(obj->m_attribute_length) );
	io::Byte_Converter::convert ( obj->m_attribute_length );

        m_file.read ( &(obj->m_line_number_table_length) );
        io::Byte_Converter::convert ( obj->m_line_number_table_length );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Line number table length: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_line_number_table_length
                                          % obj->m_line_number_table_length ) );
#endif /* LIBREVERSE_DEBUG */


        for ( boost::uint16_t i = 0;
              i < obj->m_line_number_table_length;
              ++i )
            {
                java_types::Line_Number_Item::ptr_t line_item_ptr ( new Line_Number_Item() );

                this->read_Line_Number_Item ( line_item_ptr );

                obj->m_line_number_table.push_back ( line_item_ptr );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Line_Number_Table_Attibute" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Deprecated_Attribute ( java_types::Deprecated_Attribute::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Deprecated_Attribute" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

	m_file.read ( &(obj->m_attribute_length) );
	io::Byte_Converter::convert ( obj->m_attribute_length );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Deprecated_Attribute" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Synthetic_Attribute ( java_types::Synthetic_Attribute::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Synthetic_Attribute" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

	m_file.read ( &(obj->m_attribute_length) );
	io::Byte_Converter::convert ( obj->m_attribute_length );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Synthetic_Attribute" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Unknown_Attribute ( java_types::Unknown_Attribute::ptr_t obj )
    {


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Unknown_Attribute" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_attribute_length) );
        io::Byte_Converter::convert ( obj->m_attribute_length );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format("  Attribute length: %1%" ) % obj->m_attribute_length ) );
#endif /* LIBREVERSE_DEBUG */


        // Skipping past unknown attribute
        boost::uint8_t byte = 0;

        for ( boost::uint16_t i = 0;
              i < obj->m_attribute_length;
              ++i )
            {
                m_file.read ( &byte );
                obj->m_bytes.push_back ( byte );
                
#ifdef LIBREVERSE_DEBUG
		Trace::write_Trace ( TraceArea::IO,
                                     TraceLevel::DATA,
                                     boost::str ( boost::format ( "(0x%|1$X|) Byte: %|2$02X|" )
                                                  % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                                  % static_cast<boost::uint16_t>( byte ) ) );
#endif /* LIBREVERSE_DEBUG */

            }

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Unknown_Attribute" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Signature_Attribute ( java_types::Signature_Attribute::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Signature_Attibute" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

	m_file.read ( &(obj->m_attribute_length) );
	io::Byte_Converter::convert ( obj->m_attribute_length );

        m_file.read ( &(obj->m_signature_index) );
        io::Byte_Converter::convert ( obj->m_signature_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Signature index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_signature_index
                                          % obj->m_signature_index ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Signature_Attibute" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Enclosing_Method_Attribute ( java_types::Enclosing_Method_Attribute::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Enclosing_Method_Attibute" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

	m_file.read ( &(obj->m_attribute_length) );
	io::Byte_Converter::convert ( obj->m_attribute_length );

        m_file.read ( &(obj->m_class_index) );
        io::Byte_Converter::convert ( obj->m_class_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Class index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_class_index
                                          % obj->m_class_index ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_method_index) );
        io::Byte_Converter::convert ( obj->m_method_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Method index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_method_index
                                          % obj->m_method_index ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Enclosing_Method_Attibute" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Inner_Classes_Attribute ( java_types::Inner_Classes_Attribute::ptr_t obj,
                                               java_types::Class_Header::ptr_t hdr_ptr )
    {


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Inner_Classes_Attibute" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

	m_file.read ( &(obj->m_attribute_length) );
	io::Byte_Converter::convert ( obj->m_attribute_length );

        m_file.read ( &(obj->m_number_of_classes) );
        io::Byte_Converter::convert ( obj->m_number_of_classes );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Number of classes: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_number_of_classes
                                          % obj->m_number_of_classes ) );
#endif /* LIBREVERSE_DEBUG */


        for ( boost::uint16_t i = 0;
              i < obj->m_number_of_classes;
              ++i )
            {
                java_types::Inner_Class_Reference::ptr_t inner_ptr ( new Inner_Class_Reference() );

                inner_ptr->read_Impl ( this->shared_from_this(), hdr_ptr );
                
                obj->m_classes.push_back ( inner_ptr );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Inner_Classes_Attibute" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Exceptions_Attribute ( java_types::Exceptions_Attribute::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Exceptions_Attibute" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

	m_file.read ( &(obj->m_attribute_length) );
	io::Byte_Converter::convert ( obj->m_attribute_length );

        m_file.read ( &(obj->m_number_of_exceptions) );
        io::Byte_Converter::convert ( obj->m_number_of_exceptions );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Number of exceptions: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_number_of_exceptions
                                          % obj->m_number_of_exceptions ) );
#endif /* LIBREVERSE_DEBUG */


        boost::uint16_t word = 0;
        for ( boost::uint16_t i = 0;
              i < obj->m_number_of_exceptions;
              ++i )
            {
                m_file.read ( &word );
                io::Byte_Converter::convert ( word );

                obj->m_exceptions_index_table.push_back ( word );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Exceptions_Attibute" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Stack_Map_Table_Attribute ( java_types::Stack_Map_Table_Attribute::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Stack_Map_Table_Attibute" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Name index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_name_index
                                          % obj->m_name_index ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_attribute_length) );
        io::Byte_Converter::convert ( obj->m_attribute_length );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Attribute length: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_attribute_length
                                          % obj->m_attribute_length ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_number_of_entries) );
        io::Byte_Converter::convert ( obj->m_number_of_entries );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Number of entries: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_number_of_entries
                                          % obj->m_number_of_entries ) );
#endif /* LIBREVERSE_DEBUG */

        // Get poiner to Stack Map Frame factory
        
        boost::uint8_t tag = 0;

        for ( boost::uint16_t i = 0;
              i < obj->m_number_of_entries;
              ++i )
            {
                // Call factory with tag
                m_file.read ( &tag );

                java_types::Stack_Map_Frame::ptr_t stack_ptr = Stack_Map_Frame_Factory::create ( tag );

                // Have the object read itself

                stack_ptr->read_Input ( this->shared_from_this() );

                obj->m_entries.push_back ( stack_ptr );
            }

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Stack_Map_Table_Attibute" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Constant_Value_Attribute ( java_types::Constant_Value_Attribute::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Constant_Value_Attibute" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

	m_file.read ( &(obj->m_attribute_length) );
	io::Byte_Converter::convert ( obj->m_attribute_length );

        m_file.read ( &(obj->m_constant_value_index) );
        io::Byte_Converter::convert ( obj->m_constant_value_index );        

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Constan value index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_constant_value_index
                                          % obj->m_constant_value_index ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Constant_Value_Attibute" );
#endif /* LIBREVERSE_DEBUG */

    }

    java_types::Local_Variable::ptr_t
    Class_File::read_Local_Variable ( java_types::Class_Header::ptr_t hdr_ptr )
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Local_Variable" );
#endif /* LIBREVERSE_DEBUG */


        java_types::Local_Variable::ptr_t obj ( new java_module::Local_Variable() );

	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_start_pc) );
        io::Byte_Converter::convert ( obj->m_start_pc );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Start PC: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_start_pc
                                          % obj->m_start_pc ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_length) );
        io::Byte_Converter::convert ( obj->m_length );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Length: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_length
                                          % obj->m_length ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_name_index) );
        io::Byte_Converter::convert ( obj->m_name_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Name index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_name_index
                                          % obj->m_name_index ) );
#endif /* LIBREVERSE_DEBUG */


        obj->m_name_string = hdr_ptr->get_String_Constant ( obj->m_name_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Name: %|2$s|" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_name_string ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_descriptor_index) );
        io::Byte_Converter::convert ( obj->m_descriptor_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Descriptor index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_descriptor_index
                                          % obj->m_descriptor_index ) );
#endif /* LIBREVERSE_DEBUG */


        obj->m_descriptor_string = hdr_ptr->get_String_Constant ( obj->m_descriptor_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Descriptor: %|2$s|" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_descriptor_string ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_index) );
        io::Byte_Converter::convert ( obj->m_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Local_Variable" );
#endif /* LIBREVERSE_DEBUG */


        return obj;
    }

    void
    Class_File::read_Local_Variable_Table_Attribute ( java_types::Local_Variable_Table_Attribute::ptr_t obj,
                                                      java_types::Class_Header::ptr_t hdr_ptr )
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Local_Variable_Table_Attribute" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Attribute name index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_attribute_name_index
                                          % obj->m_attribute_name_index ) );
#endif /* LIBREVERSE_DEBUG */


        obj->m_attribute_name = hdr_ptr->get_String_Constant ( obj->m_attribute_name_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Attribute name: %|2$s|" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_attribute_name ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_attribute_length) );
        io::Byte_Converter::convert ( obj->m_attribute_length );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Attribute length: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_attribute_length
                                          % obj->m_attribute_length ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_local_variable_table_length) );
        io::Byte_Converter::convert ( obj->m_local_variable_table_length );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Local variable table length: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_local_variable_table_length
                                          % obj->m_local_variable_table_length ) );
#endif /* LIBREVERSE_DEBUG */


        java_types::Local_Variable::ptr_t var_ptr;

        for ( boost::uint16_t i = 0;
              i < obj->m_local_variable_table_length;
              ++i )
            {
                var_ptr = this->read_Local_Variable ( hdr_ptr );

                obj->m_local_variable_table.push_back ( var_ptr );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Local_Variable_Table_Attribute" );
#endif /* LIBREVERSE_DEBUG */


    }

    void
    Class_File::read_Chop_Frame ( java_types::Chop_Frame::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Chop_Frame" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_offset_delta) );
        io::Byte_Converter::convert ( obj->m_offset_delta );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Offset delta: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_offset_delta
                                          % obj->m_offset_delta ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Chop_Frame" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Constant_Class_Info ( java_types::Constant_Class_Info::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Constant_Class_Info" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_name_index ) );
        io::Byte_Converter::convert ( obj->m_name_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Name index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_name_index
                                          % obj->m_name_index ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Constant_Class_Info" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Constant_Double_Info ( java_types::Constant_Double_Info::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Constant_Double_Info" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        boost::uint32_t high_bytes;
        boost::uint32_t low_bytes;

        // Read in high and low bytes in big endian order
        m_file.read ( &high_bytes );
        io::Byte_Converter::convert ( high_bytes );
        m_file.read ( &low_bytes );
        io::Byte_Converter::convert ( low_bytes );

        boost::uint64_t value = ( static_cast<boost::uint64_t>(high_bytes) << 32 ) + static_cast<boost::uint64_t>(low_bytes);

        // Perform double checks
        if ( value & 0x7FF0000000000000ULL )
            {
                // double value will be positive infinity
                obj->m_value = DBL_MAX;
            }
        else if ( value & 0xFFF0000000000000ULL )
            {
                // double value will be negative infinity
                obj->m_value = -DBL_MAX;
            }
        else if ( ( ( value <= 0x7FFFFFFFFFFFFFFFULL ) &&
                    ( value >= 0x7FF0000000000001ULL ) ) ||
                  ( ( value <= 0xFFF0000000000001ULL ) &&
                    ( value >= 0xFFFFFFFFFFFFFFFFULL ) ) )
            {
                // Value will be NaN
                obj->m_value = DBL_MAX;
            }
        else
            {
                int signed_value = -1;
                if ( ( value >> 63 ) == 0 )
                    {
                        signed_value = 1;
                    }

                int power_value = static_cast<int>( ( value >> 52 ) & 0x7FF );

                boost::int64_t val = 0;

                if ( power_value == 0 )
                    {
                        val = ( value & 0xFFFFFFFFFFFFFFFFLL ) << 1;
                    }
                else
                    {
                        val = ( value & 0xFFFFFFFFFFFFFFFFLL ) |
                            0x1000000000000000LL;
                    }

                double base = 2;
                double power = power_value - 1075;

                obj->m_value = signed_value * val * pow ( base, power );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Value: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_value
                                          % obj->m_value ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Constant_Double_Info" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Constant_Fieldref_Info ( java_types::Constant_Fieldref_Info::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Constant_Fieldref_Info" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_class_index) );
        io::Byte_Converter::convert ( obj->m_class_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Class index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_class_index
                                          % obj->m_class_index ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_name_and_type_index) );
        io::Byte_Converter::convert ( obj->m_name_and_type_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Name and Type index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_name_and_type_index
                                          % obj->m_name_and_type_index ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Constant_Fieldref_Info" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Constant_Float_Info ( java_types::Constant_Float_Info::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Constant_Float_Info" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        boost::uint32_t value = 0;
        m_file.read ( &value );
        io::Byte_Converter::convert ( value );

        if ( ( value & 0x7F800000 ) == 0x7F800000 )
            {
                // float value will be positive infinity
                obj->m_bytes = FLT_MAX;
            }
        else if ( ( value & 0xFF800000 ) == 0xFF800000 )
            {
                // float value will be negative infinity
                obj->m_bytes = -FLT_MAX;
            }
        else if ( ( ( value >= 0x7F800001 ) && ( value <= 0x7FFFFFFF ) ) ||
                  ( ( value >= 0xFF800001 ) && ( value <= 0xFFFFFFFF ) ) )
            {
                // float value will be NaN
                obj->m_bytes = FLT_MAX;
            }
        else
            {
                int signed_value = -1;
                if ( ( value >> 31 ) == 0 )
                    {
                        signed_value = 1;
                    }

                int power_value = static_cast<int>( ( value >> 23 ) & 0xFF );

                boost::int64_t val = 0;

                if ( power_value == 0 )
                    {
                        val = ( value & 0x7FFFF ) << 1;
                    }
                else
                    {
                        val = ( value & 0x7FFFF ) | 0x800000;
                    }

                float base = 2;
                float power = static_cast<float>(power_value - 150);

                obj->m_bytes = signed_value * val * pow ( base, power );
            }

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Value: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_bytes
                                          % obj->m_bytes ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Constant_Float_Info" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Constant_Name_And_Type_Info ( java_types::Constant_Name_And_Type_Info::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Constant_Name_And_Type_Info" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_name_index) );
        io::Byte_Converter::convert ( obj->m_name_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Name index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_name_index
                                          % obj->m_name_index ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_descriptor_index) );
        io::Byte_Converter::convert ( obj->m_descriptor_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Descriptor index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_descriptor_index
                                          % obj->m_descriptor_index ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Constant_Name_And_Type_Info" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Constant_InterfaceMethodref_Info ( java_types::Constant_InterfaceMethodref_Info::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Constant_InterfaceMethodref_Info" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_class_index) );
        io::Byte_Converter::convert ( obj->m_class_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Class index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_class_index
                                          % obj->m_class_index ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_name_and_type_index) );
        io::Byte_Converter::convert ( obj->m_name_and_type_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Name and Type index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_name_and_type_index
                                          % obj->m_name_and_type_index ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Constant_InterfaceMethodref_Info" );
#endif /* LIBREVERSE_DEBUG */


    }

    void
    Class_File::read_Constant_Methodref_Info ( java_types::Constant_Methodref_Info::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Constant_Methodref_Info" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_class_index) );
        io::Byte_Converter::convert ( obj->m_class_index );

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Class index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_class_index
                                          % obj->m_class_index ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &(obj->m_name_and_type_index) );
        io::Byte_Converter::convert ( obj->m_name_and_type_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Name and Type index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_name_and_type_index
                                          % obj->m_name_and_type_index ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Constant_InterfaceMethodref_Info" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Constant_String_Info ( java_types::Constant_String_Info::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Constant_String_Info" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_string_index) );
        io::Byte_Converter::convert ( obj->m_string_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) String index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_string_index
                                          % obj->m_string_index ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Constant_String_Info" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Constant_Utf8_Info ( java_types::Constant_Utf8_Info::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Constant_Utf8_Info" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_length) );
        io::Byte_Converter::convert ( obj->m_length );

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Length: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_length
                                          % obj->m_length ) );
#endif /* LIBREVERSE_DEBUG */


        obj->m_chars = m_file.read_8bit_Java_Unicode_String ( obj->m_length );

        obj->m_text = String_Converter::convert_From_UTF16_String ( obj->m_chars );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Text: %|2$s|" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_text ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Constant_Utf8_Info" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Constant_Long_Info ( java_types::Constant_Long_Info::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Constant_Long_Info" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        boost::uint32_t high_bytes;
        boost::uint32_t low_bytes;

        // Read in high and low bytes in big endian order
        m_file.read ( &high_bytes );


#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format("  High byte: %1$08X")
					  % high_bytes ) );
#endif /* LIBREVERSE_DEBUG */


        io::Byte_Converter::convert ( high_bytes );


#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format("  High byte (converted): %1$08X")
					  % high_bytes ) );
#endif /* LIBREVERSE_DEBUG */


        m_file.read ( &low_bytes );


#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format("  Low byte: %1$08X")
					  % low_bytes ) );
#endif /* LIBREVERSE_DEBUG */


        io::Byte_Converter::convert ( low_bytes );        


#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::IO,
			     TraceLevel::DATA,
			     boost::str ( boost::format("  Low byte (converted): %1$08X")
					  % low_bytes ) );
#endif /* LIBREVERSE_DEBUG */


	obj->m_value = ( static_cast<boost::uint64_t>(high_bytes) << 32 ) +
	  static_cast<boost::uint64_t>(low_bytes);


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Value: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_value
                                          % obj->m_value ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Constant_Long_Info" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Constant_Integer_Info ( java_types::Constant_Integer_Info::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Constant_Integer_Info" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_bytes) );
        io::Byte_Converter::convert ( obj->m_bytes );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Bytes: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_bytes
                                          % obj->m_bytes ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Constant_Integer_Info" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Full_Frame ( java_types::Full_Frame::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Full_Frame" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_offset_delta) );
        io::Byte_Converter::convert ( obj->m_offset_delta );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Offset delta: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_offset_delta
                                          % obj->m_offset_delta ) );
#endif /* LIBREVERSE_DEBUG */

        m_file.read ( &obj->m_number_of_locals );
        io::Byte_Converter::convert ( obj->m_number_of_locals );

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Number of locals: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_number_of_locals
                                          % obj->m_number_of_locals ) );
#endif /* LIBREVERSE_DEBUG */


        boost::uint8_t tag = 0;
        java_types::Verification_Type_Info::ptr_t temp_ptr;

        for ( boost::uint16_t i = 0;
              i < obj->m_number_of_locals;
              ++i )
            {
                m_file.read (&tag);

                temp_ptr = Verification_Type_Factory::create ( tag );
      
                temp_ptr->read_Input ( this->shared_from_this() );

                obj->m_locals.push_back ( temp_ptr );
            }

        m_file.read ( &(obj->m_number_of_stack_items) );
        io::Byte_Converter::convert ( obj->m_number_of_stack_items );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Number of stack items: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_number_of_stack_items
                                          % obj->m_number_of_stack_items ) );
#endif /* LIBREVERSE_DEBUG */


        for ( boost::uint16_t i = 0;
              i < obj->m_number_of_stack_items;
              ++i )
            {
                m_file.read (&tag);

                temp_ptr = Verification_Type_Factory::create ( tag );
      
                temp_ptr->read_Input ( this->shared_from_this() );

                obj->m_locals.push_back ( temp_ptr );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Full_Frame" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Object_Variable_Info ( java_types::Object_Variable_Info::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Object_Variable_Info" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_constant_pool_index) );
        io::Byte_Converter::convert ( obj->m_constant_pool_index );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Constant pool index: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_constant_pool_index
                                          % obj->m_constant_pool_index ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Object_Variable_Info" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Same_Frame_Extended ( java_types::Same_Frame_Extended::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Same_Frame_Extended" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_offset_delta) );
        io::Byte_Converter::convert ( obj->m_offset_delta );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Offset delta: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_offset_delta
                                          % obj->m_offset_delta ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Same_Frame_Extended" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_File::read_Same_Locals_One_Stack_Item_Frame ( java_types::Same_Locals_One_Stack_Item_Frame::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Same_Locals_One_Stack_Item_Frame" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        boost::uint8_t tag = 0;

        m_file.read (&tag);

        obj->m_data = Verification_Type_Factory::create ( tag );
      
        obj->m_data->read_Input ( this->shared_from_this() );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Same_Locals_One_Stack_Item_Frame" );
#endif /* LIBREVERSE_DEBUG */

    }
    
    void
    Class_File::read_Same_Locals_One_Stack_Item_Frame_Extended ( java_types::Same_Locals_One_Stack_Item_Frame_Extended::ptr_t obj )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Same_Locals_One_Stack_Item_Frame_Extended" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_offset_delta) );
        io::Byte_Converter::convert ( obj->m_offset_delta );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Offset delta: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_offset_delta
                                          % obj->m_offset_delta ) );
#endif /* LIBREVERSE_DEBUG */


        boost::uint8_t tag = 0;

        m_file.read (&tag);

        obj->m_data = Verification_Type_Factory::create ( tag );
      
        obj->m_data->read_Input ( this->shared_from_this() );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Same_Locals_One_Stack_Item_Frame_Extended" );
#endif /* LIBREVERSE_DEBUG */


    }
    
    void
    Class_File::read_Uninitialized_Variable_Info ( java_types::Uninitialized_Variable_Info::ptr_t obj )
    {


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_File::read_Unitialized_Variable_Info" );
#endif /* LIBREVERSE_DEBUG */


	io::Preconditions::is_set ( obj );

        m_file.read ( &(obj->m_offset) );
        io::Byte_Converter::convert ( obj->m_offset );


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
                             boost::str ( boost::format ( "(0x%|1$X|) Offset: %|2$d| (%|3$X|)" )
                                          % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                          % obj->m_offset
                                          % obj->m_offset ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_File::read_Unitialized_Variable_Info" );
#endif /* LIBREVERSE_DEBUG */

    }

    io::File const&
    Class_File::get_File (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_File::get_File" );
#endif /* LIBREVERSE_DEBUG */

       return m_file;
    }

    std::string
    Class_File::get_String_From_Constant_Pool ( boost::uint16_t index,
						java_types::Class_Header::ptr_t hdr_obj )
    {
      java_types::Class_Header::Constant_Pool_Info_Map_t::const_iterator info_pos =
	hdr_obj->get_Constant_Pool_Item ( index );

      std::string text = "";
      boost::uint16_t tag = ((*info_pos).second)->get_Tag();

      if ( tag == Constant_Pool_Tags::UTF8 )
	{
	  java_types::Constant_Utf8_Info::ptr_t utf8_info =
	    boost::dynamic_pointer_cast<java_module::Constant_Utf8_Info>((*info_pos).second);
	  text = utf8_info->get_Text();
	}

      return text;
    }

} /* namespace java_module */
} /* namespace reverse */
