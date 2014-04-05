/*  Class_File.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_CLASS_FILE_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_CLASS_FILE_HPP_INCLUDED

#include <reverse/io/File.h>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>

namespace reverse { 
  namespace data_container {

    class memory_map;

  } // namespace data_container
} // namespace reverse


namespace reverse { 
  namespace io {

    class File_ID;

  } // namespace io
} // namespace reverse

namespace reverse { 
  namespace io {
    namespace input {
      namespace file_readers {
	namespace java_class {

	  class Append_Frame;
	  class Attribute_Info;
	  class Chop_Frame;
	  class Class_Header;
	  class Code_Attribute;
	  class Constant_Class_Info;
	  class Constant_Double_Info;
	  class Constant_Fieldref_Info;
	  class Constant_Float_Info;
	  class Constant_InterfaceMethodref_Info;
	  class Constant_Integer_Info;
	  class Constant_Long_Info;
	  class Constant_Method_Info;
	  class Constant_Methodref_Info;
	  class Constant_Name_And_Type_Info;
	  class Constant_Pool_Info;
	  class Constant_String_Info;
	  class Constant_Utf8_Info;
	  class Constant_Value_Attribute;
	  class Deprecated_Attribute;
	  class Enclosing_Method_Attribute;
	  class Exception_Table_Entry;
	  class Exceptions_Attribute;
	  class Field_Info;
	  class Full_Frame;
	  class Inner_Class_Reference;
	  class Inner_Classes_Attribute;
	  class Line_Number_Item;
	  class Line_Number_Table_Attribute;
	  class Local_Variable;
	  class Local_Variable_Table_Attribute;
	  class Method_Info;
	  class Object_Variable_Info;
	  class Same_Frame_Extended;
	  class Same_Locals_One_Stack_Item_Frame;
	  class Same_Locals_One_Stack_Item_Frame_Extended;
	  class Signature_Attribute;
	  class Source_File_Attribute;
	  class Stack_Map_Table_Attribute;
	  class Synthetic_Attribute;
	  class Unknown_Attribute;
	  class Uninitialized_Variable_Info;

	  /*!
	   * \class Class_File
	   *
	   * \brief Class_File contains all the elf specific functionality to
	   * read binary data from a target file.
	   *
	   * \date 2004
	   */
	  class Class_File : public boost::enable_shared_from_this<Class_File>
	  {
	  public:

            /*! \brief Narrow? (Copy Constructor?)
             *  \param f_ref Reference to the File object to copy
             */
	    Class_File ( boost::shared_ptr< const reverse::io::File_ID >& filename );
	  
	    Class_File ( boost::shared_ptr < reverse::data_container::memory_map>& file_img_ptr,
			 boost::shared_ptr< const reverse::io::File_ID >& filename );

	    bool init (void);

	    /* Read ClassFile header from file */
	    void read_Class_Header ( boost::shared_ptr < const reverse::io::input::file_readers::java_class::Class_Header>& obj );

            boost::shared_ptr < reverse::io::input::file_readers::java_class::Attribute_Info >
            read_Attribute_Info ( boost::shared_ptr < const reverse::io::input::file_readers::java_class::Class_Header>& hdr_obj );

            void read_Inner_Class_Reference ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Inner_Class_Reference >& obj,
                                              boost::shared_ptr < const reverse::io::input::file_readers::java_class::Class_Header>& hdr_ptr );

            void read_Line_Number_Item ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Line_Number_Item >& obj );

            void read_Append_Frame ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Append_Frame >& obj );

            void read_Source_File_Attribute ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Source_File_Attribute >& obj,
                                              boost::shared_ptr < const reverse::io::input::file_readers::java_class::Class_Header>& hdr_ptr );

            void read_Code_Attribute ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Code_Attribute >& obj,
                                       boost::shared_ptr < const reverse::io::input::file_readers::java_class::Class_Header>& hdr_ptr );

	    boost::shared_ptr < reverse::io::input::file_readers::java_class::Exception_Table_Entry > read_Exception_Table_Entry ( void );

            void read_Deprecated_Attribute ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Deprecated_Attribute >& obj );

            void read_Synthetic_Attribute ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Synthetic_Attribute >& obj );

            void read_Unknown_Attribute ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Unknown_Attribute >& obj );

            void read_Line_Number_Table_Attribute ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Line_Number_Table_Attribute >& obj );

            void read_Signature_Attribute ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Signature_Attribute >& obj );

            void read_Enclosing_Method_Attribute ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Enclosing_Method_Attribute >& obj );

            void read_Inner_Classes_Attribute ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Inner_Classes_Attribute >& obj,
                                                boost::shared_ptr < const reverse::io::input::file_readers::java_class::Class_Header>& hdr_obj );

            void read_Exceptions_Attribute ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Exceptions_Attribute >& obj );

            void read_Stack_Map_Table_Attribute ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Stack_Map_Table_Attribute >& obj );

            void read_Constant_Value_Attribute ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Constant_Value_Attribute >& obj );

            boost::shared_ptr < reverse::io::input::file_readers::java_class::Local_Variable > read_Local_Variable ( boost::shared_ptr < const reverse::io::input::file_readers::java_class::Class_Header>& hdr_ptr );

            void read_Local_Variable_Table_Attribute ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Local_Variable_Table_Attribute >& obj,
                                                       boost::shared_ptr < const reverse::io::input::file_readers::java_class::Class_Header>& hdr_ptr );

            void read_Chop_Frame ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Chop_Frame >& obj );

            void read_Constant_Class_Info ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Constant_Class_Info >& obj );

            void read_Constant_Double_Info ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Constant_Double_Info >& obj );

            void read_Constant_Fieldref_Info ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Constant_Fieldref_Info >& obj );

            void read_Constant_Float_Info ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Constant_Float_Info >& obj );

            void read_Constant_Name_And_Type_Info ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Constant_Name_And_Type_Info >& obj );

            void read_Constant_InterfaceMethodref_Info ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Constant_InterfaceMethodref_Info >& obj );

            void read_Constant_Methodref_Info ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Constant_Methodref_Info >& obj );

            void read_Constant_String_Info ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Constant_String_Info >& obj );

            void read_Constant_Utf8_Info ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Constant_Utf8_Info >& obj );

            void read_Constant_Long_Info ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Constant_Long_Info >& obj );

            void read_Constant_Integer_Info ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Constant_Integer_Info >& obj );

            void read_Full_Frame ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Full_Frame >& obj );

            void read_Object_Variable_Info ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Object_Variable_Info >& obj );

            void read_Same_Frame_Extended ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Same_Frame_Extended >& obj );

            void read_Same_Locals_One_Stack_Item_Frame ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Same_Locals_One_Stack_Item_Frame >& obj );

            void read_Same_Locals_One_Stack_Item_Frame_Extended ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Same_Locals_One_Stack_Item_Frame_Extended >& obj );

            void read_Uninitialized_Variable_Info ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Uninitialized_Variable_Info >& obj );

            io::File const& get_File (void) const;

	  private:

            /* Read Constant_Pool_Info object from file */
            boost::shared_ptr < reverse::io::input::file_readers::java_class::Constant_Pool_Info > read_Constant_Pool_Info ( void );

            void read_Field_Info ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Field_Info >& obj,
                                   boost::shared_ptr < const reverse::io::input::file_readers::java_class::Class_Header>& hdr_obj );

            void read_Method_Info ( boost::shared_ptr < reverse::io::input::file_readers::java_class::Method_Info >& obj,
                                    boost::shared_ptr < const reverse::io::input::file_readers::java_class::Class_Header>& hdr_obj );

	    std::string get_String_From_Constant_Pool ( boost::uint16_t index,
							boost::shared_ptr < const reverse::io::input::file_readers::java_class::Class_Header>& hdr_obj );
	    
            io::File m_file;
	  };


	} // namespace java_class
      } // namespace file_readers
    } // namespace input 
  } // namespace io
} // namespace reverse

#endif // #ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_CLASS_FILE_HPP_INCLUDED
