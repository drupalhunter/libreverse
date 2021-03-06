/*  Class_Header.cpp

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

#include "Class_Header.h"
#include "Class_Access_Flags.h"
#include "Constant_Pool_Info.h"
#include "Constant_Pool_Tags.h"
#include "Constant_String_Info.h"
#include "Constant_Utf8_Info.h"
#include "Field_Info.h"
#include "Method_Info.h"
#include "Attribute_Info.h"

#include <sstream>
#include <boost/format.hpp>
#include <iostream>

#include "errors/IO_Exception.h"
#include "io/Output.h"

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */


namespace reverse { namespace java_module {

    boost::uint32_t const Class_Header::CLASS_MAGIC_SIGNATURE = 0xCAFEBABE;

    Class_Header::Class_Header()
        : m_magic ( 0 ),
          m_minor_version ( 0 ),
          m_major_version ( 0 ),
          m_constant_pool_count ( 0 ),
          m_access_flags ( 0 ),
          m_this_class ( 0 ),
          m_super_class ( 0 ),
          m_interfaces_count ( 0 ),
          m_field_count ( 0 ),
          m_methods_count ( 0 ),
          m_attributes_count ( 0 )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Class_Header::convert ()
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::convert" );
#endif /* LIBREVERSE_DEBUG */


        // Do nothing since we use values in the Class_Header object
        // during reading we must convert the values there. So we just
        // convert all the values as they are read rather than those
        // that are used. This eliminates any confusion later as to
        // which values need to be converted.
    }

    std::string
    Class_Header::to_String (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_Header::to_String" );
#endif /* LIBREVERSE_DEBUG */

        std::stringstream output;

	boost::uint32_t indent_value = 2;

        output << "Class_Header" << std::endl
               << io::Output::indent ( indent_value )
	       << boost::format ("Magic:               %X")    % m_magic << std::endl
               << io::Output::indent ( indent_value )
               << boost::format ("Version:             %d.%d") % m_major_version % m_minor_version << std::endl
               << io::Output::indent ( indent_value )
               << boost::format ("Constant Pool count: %d" )   % m_constant_pool_count << std::endl
               << io::Output::indent ( indent_value )
               << boost::format ("Access flags:        %1$04X" )   % m_access_flags << std::endl;

        if ( Class_Access_Flags::has_Valid_Flags ( m_access_flags ) )
	  {
	    output << io::Output::indent ( indent_value + 2 )
		   << "VALID" << std::endl;
	  }
	else
	  {
	    output << io::Output::indent ( indent_value + 2 )
		   << "INVALID" << std::endl;
	  }

        output << io::Output::indent ( indent_value + 2 )
	       << boost::format ("  flags: %s")
	  % Class_Access_Flags::to_String ( m_access_flags )
               << std::endl;

	/*
        output << boost::format ("  This class:          %d" )
            % m_this_class << std::endl
               << boost::format ("  Super class:         %d" )
            % m_super_class << std::endl
               << boost::format ("  Interfaces count:    %d" )
            % m_interfaces_count << std::endl
               << boost::format ("  Field count:         %d" )
            % m_field_count << std::endl
            // Add listing Field info objects
               << boost::format ("  Method count:        %d" )
            % m_methods_count << std::endl
            // Add listing Method info objects
               << boost::format ("  Attribute count:     %d" )
            % m_attributes_count << std::endl;
        // Add listing Attribute info objects
	*/

        output << "  Constant Pool: " << std::endl;
        
        for ( java_types::Class_Header::Constant_Pool_Info_Map_t::const_iterator cpos = m_constant_pool.begin();
              cpos != m_constant_pool.end();
              cpos++ )
            {
	      output << boost::format ( "    %1%: %2%" )
		% (*cpos).first
		% (*cpos).second->to_String() << std::endl;	

            }
      
        output << boost::format ("  Access flags (%d):  %s" )
            % m_access_flags
            % Class_Access_Flags::to_String ( m_access_flags ) << std::endl
               << boost::format ("  This class:         %d" )
            % m_this_class << std::endl
               << boost::format ("  Super class:        %d" )
            % m_super_class << std::endl
               << boost::format ("  Interface count:    %d" )
            % m_interfaces_count << std::endl;  

        boost::uint16_t indent_count = 2;

        if ( m_interfaces_count > 0 )
            {
                output << "  Interfaces: " << std::endl;

                for ( java_types::Class_Header::Interfaces_List_t::const_iterator cpos = m_interfaces.begin();
                      cpos != m_interfaces.end();
                      cpos++ )
                    {
		      output << "    " << (*cpos) << std::endl;
                    }
            }

        output << boost::format ("  Field count:    %d" ) % m_field_count << std::endl;  

        if ( m_field_count > 0 )
            {
                output << "  Fields: " << std::endl;

                for ( java_types::Class_Header::Field_Info_Map_t::const_iterator cpos =
                          m_fields.begin();
                      cpos != m_fields.end();
                      cpos++ )
                    {
                        output << (*cpos).second->to_String ( indent_count + 2 ) << std::endl;			
                    }
            }

        output << boost::format ("  Method count:    %d" )
            % m_methods_count << std::endl;  

        if ( m_methods_count > 0 )
            {
                output << "  Methods: " << std::endl;

                for ( java_types::Class_Header::Method_Info_Map_t::const_iterator cpos =
                          m_methods.begin();
                      cpos != m_methods.end();
                      cpos++ )
                    {
                        output << (*cpos).second->to_String ( indent_count ) << std::endl;			
                    }
            }

        output << boost::format ("  Attribute count:    %d" )
            % m_attributes_count << std::endl;  

        if ( m_attributes_count > 0 )
            {
                output << "  Attributes: " << std::endl;

                for ( java_types::Class_Header::Attribute_Info_Map_t::const_iterator cpos = m_attributes.begin();
                      cpos != m_attributes.end();
                      ++cpos )
                    {
                        output << (*cpos).second->to_String ( indent_count ) << std::endl;			
                    }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_Header::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output.str();
    }

    bool
    Class_Header::is_Java_File (void) const
    {


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_Header::is_Java_File" );
#endif /* LIBREVERSE_DEBUG */

                             
            /* Excerpt from file utility 'cafebabe' file:

            # Cafe Babes unite!
            #
            # Since Java bytecode and Mach-O fat-files have the same magic number, the test
            # must be performed in the same "magic" sequence to get both right.  The long
            # at offset 4 in a mach-O fat file tells the number of architectures; the short at
            # offset 4 in a Java bytecode file is the JVM minor version and the
            # short at offset 6 is the JVM major version.  Since there are only
            # only 18 labeled Mach-O architectures at current, and the first released
            # Java class format was version 43.0, we can safely choose any number
            # between 18 and 39 to test the number of architectures against
            # (and use as a hack). Let's not use 18, because the Mach-O people
            # might add another one or two as time goes by...
            #
            */
            
        bool result = false;


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
			     boost::str ( boost::format (  "Read magic value: %1$X" ) % m_magic ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
			     boost::str ( boost::format (  "Compared against the save magic value: %1$X" ) % CLASS_MAGIC_SIGNATURE ) );

        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DATA,
			     boost::str ( boost::format (  "Major version: %1$X (%2$d)" ) % m_major_version % m_major_version ) );
#endif /* LIBREVERSE_DEBUG */


        if ( ( m_magic == CLASS_MAGIC_SIGNATURE ) && ( m_major_version > 30 ) )
            {
                result = true;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_Header::is_Java_File" );
#endif /* LIBREVERSE_DEBUG */


        return result;
    }

    std::string
    Class_Header::get_String_Constant ( boost::uint16_t val ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Class_Header::get_String_Constant" );
#endif /* LIBREVERSE_DEBUG */


        // IF there is a key at the position 'val' THEN
        //   Grab Constant_Pool_Info object from constant_pool 
        //   Check to see if the object is a Constant_Utf8_Info object
        //   IF true THEN
        //     grab string from object
        //   ELSE
        //     throw an exception that the target object is not a Constant_Utf8_Info object
        // ELSE
        //   throw an invalid index exception
        java_types::Class_Header::Constant_Pool_Info_Map_t::const_iterator cpos = m_constant_pool.find ( val );

        if ( cpos != m_constant_pool.end() )
            {
                java_types::Constant_Pool_Info::ptr_t target_ptr = (*cpos).second;
                if ( target_ptr->is_Type ( Constant_Pool_Tags::UTF8 ) )
                    {
                        java_types::Constant_Utf8_Info::ptr_t utf_ptr = boost::dynamic_pointer_cast<Constant_Utf8_Info>( target_ptr );

                        return utf_ptr->get_Text();
                    }
		else if ( target_ptr->is_Type ( Constant_Pool_Tags::STRING ) )
		  {
                        java_types::Constant_String_Info::ptr_t string_ptr =
			  boost::dynamic_pointer_cast<Constant_String_Info>( target_ptr );

			return this->get_String_Constant ( string_ptr->get_String_Index() );
		  }
                else 
                    {

#ifdef LIBREVERSE_DEBUG
		      Trace::write_Trace ( TraceArea::IO,
					   TraceLevel::ERROR,
					   boost::str ( boost::format("Invalid index(%d) given. Object found was not a Constant_Utf8_Info object." ) % val ) );

		      Trace::write_Trace ( TraceArea::IO,
					   TraceLevel::ERROR,
					   target_ptr->to_String() );
#endif /* LIBREVERSE_DEBUG */


                        throw errors::IO_Exception ( errors::IO_Exception::INVALID_INDEX );
                    }
            }
        else
            {
                std::cerr << boost::format("Invalid index(%d) given. No object found")
                    % val << std::endl;

                throw errors::IO_Exception ( errors::IO_Exception::INVALID_INDEX );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Class_Header::get_String_Constant" );
#endif /* LIBREVERSE_DEBUG */

    }

    boost::uint32_t
    Class_Header::get_Magic_Number() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Magic_Number" );
#endif /* LIBREVERSE_DEBUG */

        return m_magic;
    }

    boost::uint16_t
    Class_Header::get_Minor_Version() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Minor_Version" );
#endif /* LIBREVERSE_DEBUG */

        return m_minor_version;
    }

    boost::uint16_t
    Class_Header::get_Major_Version() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Major_Version" );
#endif /* LIBREVERSE_DEBUG */

        return m_major_version;
    }

    double
    Class_Header::get_Version() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Version" );
#endif /* LIBREVERSE_DEBUG */


	std::stringstream num_string;
	double output = 0.0;
	num_string << boost::str ( boost::format ( "%1%.%2%" ) % m_major_version % m_minor_version );
	num_string >> output;
	return output;
    }

    boost::uint16_t
    Class_Header::get_Constant_Pool_Count () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Constant_Pool_Count" );
#endif /* LIBREVERSE_DEBUG */

        return m_constant_pool_count;
    }
    
    java_types::Class_Header::Constant_Pool_Info_Map_t::const_iterator
    Class_Header::get_Constant_Pool_Begin() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Constant_Pool_Begin" );
#endif /* LIBREVERSE_DEBUG */

        return m_constant_pool.begin();
    }

    java_types::Class_Header::Constant_Pool_Info_Map_t::const_iterator
    Class_Header::get_Constant_Pool_End() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Constant_Pool_End" );
#endif /* LIBREVERSE_DEBUG */

        return m_constant_pool.end();
    }

    java_types::Class_Header::Constant_Pool_Info_Map_t::const_iterator
    Class_Header::get_Constant_Pool_Item ( boost::uint16_t index )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Constant_Pool_Item" );
#endif /* LIBREVERSE_DEBUG */

        java_types::Class_Header::Constant_Pool_Info_Map_t::const_iterator pos = m_constant_pool.find ( index );

        if ( pos == m_constant_pool.end() )
            {

#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace
                    ( TraceArea::INFRASTRUCTURE,
                      TraceLevel::ERROR,
                      boost::str ( boost::format("Exception throw in %s at line %d")
                                   % __FILE__
                                   % __LINE__ ) );
#endif /* LIBREVERSE_DEBUG */

                throw errors::IO_Exception ( errors::IO_Exception::INVALID_INDEX );
            }

        return pos;
    }

    boost::uint16_t
    Class_Header::get_Access_Flags() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Access_Flags" );
#endif /* LIBREVERSE_DEBUG */

        return m_access_flags;
    }
    
    boost::uint16_t
    Class_Header::get_This_Class() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_This_Class" );
#endif /* LIBREVERSE_DEBUG */

        return m_this_class;
    }

    boost::uint16_t
    Class_Header::get_Super_Class() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Super_Class" );
#endif /* LIBREVERSE_DEBUG */

        return m_super_class;
    }

    boost::uint16_t
    Class_Header::get_Interfaces_Count () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Interfaces_Count" );
#endif /* LIBREVERSE_DEBUG */


        return m_interfaces_count;
    }

    java_types::Class_Header::Interfaces_List_t::const_iterator
    Class_Header::get_Interfaces_Begin() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Interfaces_Begin" );
#endif /* LIBREVERSE_DEBUG */


        return m_interfaces.begin();
    }

    java_types::Class_Header::Interfaces_List_t::const_iterator
    Class_Header::get_Interfaces_End() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Interfaces_End" );
#endif /* LIBREVERSE_DEBUG */

        return m_interfaces.end();
    }

    boost::uint16_t
    Class_Header::get_Field_Count () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Field_Count" );
#endif /* LIBREVERSE_DEBUG */


        return m_field_count;
    }

    java_types::Class_Header::Field_Info_Map_t::const_iterator
    Class_Header::get_Field_Begin() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Field_Begin" );
#endif /* LIBREVERSE_DEBUG */


        return m_fields.begin();
    }

    java_types::Class_Header::Field_Info_Map_t::const_iterator
    Class_Header::get_Field_End() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Field_End" );
#endif /* LIBREVERSE_DEBUG */


        return m_fields.end();
    }

    boost::uint16_t
    Class_Header::get_Method_Count () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Method_Count" );
#endif /* LIBREVERSE_DEBUG */

        return m_methods_count;
    }

    java_types::Class_Header::Method_Info_Map_t::const_iterator
    Class_Header::get_Method_Begin() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Method_Begin" );
#endif /* LIBREVERSE_DEBUG */

        return m_methods.begin();
    }

    java_types::Class_Header::Method_Info_Map_t::const_iterator
    Class_Header::get_Method_End() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Method_End" );
#endif /* LIBREVERSE_DEBUG */

        return m_methods.end();
    }

    boost::uint16_t
    Class_Header::get_Attribute_Count () const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Attribute_Count" );
#endif /* LIBREVERSE_DEBUG */

        return m_attributes_count;
    }

    java_types::Class_Header::Attribute_Info_Map_t::const_iterator
    Class_Header::get_Attribute_Begin() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Attribute_Begin" );
#endif /* LIBREVERSE_DEBUG */

        return m_attributes.begin();
    }

    java_types::Class_Header::Attribute_Info_Map_t::const_iterator
    Class_Header::get_Attribute_End() const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Class_Header::get_Attribute_End" );
#endif /* LIBREVERSE_DEBUG */

        return m_attributes.end();
    }

    std::vector < std::string > 
    Class_Header::get_Text_Strings() const
    {
      std::vector < std::string > output;

        for ( java_types::Class_Header::Constant_Pool_Info_Map_t::const_iterator pos = m_constant_pool.begin();
              pos != m_constant_pool.end();
              ++pos )
            {
                if ( ( (*pos).second )->get_Tag() == Constant_Pool_Tags::UTF8 )
                    {
			java_types::Constant_Utf8_Info::ptr_t string_ptr =
                            boost::dynamic_pointer_cast<java_module::Constant_Utf8_Info> ( (*pos).second );

                        output.push_back ( string_ptr->get_Text() );
                    }
            }

        return output;
    }

    std::vector<UChar>
    Class_Header::get_Raw_Strings() const
    {
        std::vector<UChar> output;

        for ( java_types::Class_Header::Constant_Pool_Info_Map_t::const_iterator pos = m_constant_pool.begin();
              pos != m_constant_pool.end();
              ++pos )
            {
                if ( ((*pos).second)->get_Tag() == Constant_Pool_Tags::UTF8 )
                    {
                        java_types::Constant_Utf8_Info::ptr_t string_ptr =
                            boost::dynamic_pointer_cast<java_module::Constant_Utf8_Info> ( (*pos).second );
                        
                        output.push_back ( string_ptr->get_Chars() );
                    }
            }

        return output;
    }

} /* namespace java_module */
} /* namespace reverse */
