/*  Elf_Reader_64.cpp

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

/*
  Code for most of this file was obtained from the GNU Binutils
  readelf.c file. Below is the copyright for the original code. The
  original code was used as a inspiration on how to design an Elf
  file reader. I give full credit of this excellent set of code to
  the original developers. Thanks for the hard work.

  Copyright 1998, 1999, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

  Originally developed by Eric Youngdale <eric@andante.jic.com>
  Modifications by Nick Clifton <nickc@redhat.com>

  This file is part of GNU Binutils.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
*/

#include "Elf_Reader_64.h"
#include "Elf_Header_64.h"
#include "Elf_File.h"
#include "Elf_File_Header_64.h"
#include "Elf_Section_Header_64.h"
#include "Elf_Common.h"
#include "Elf_Symbol_64.h"
#include "Elf_Meta_Info.h"

#include "data_containers/Memory_Map.h"
#include "io/File_ID.h"
#include "errors/IO_Exception.h"

#include <sstream>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse
{
  namespace elf_module
  {

    Elf_Reader_64::Elf_Reader_64 ( io_types::File_ID::const_ptr_t target_file )
      : m_elf_file ( new Elf_File ( target_file ) ),
	m_convert ( false ),
	m_elf_data ( new Elf_Header_64() )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_Reader_64 constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Elf_Reader_64::~Elf_Reader_64 ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Inside Elf_Reader_64 destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_Reader_64::read_File_Header ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::read_File_Header" );
#endif /* LIBREVERSE_DEBUG */


      if ( ! m_elf_file->init() )
	{


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::ERROR,
			       "Error initializing file. Checking standard output for error message." );
#endif /* LIBREVERSE_DEBUG */


	  return;
	}

      if ( ! m_elf_data->is_File_Header_Set() )
	{
	  elf_types::Elf_File_Header_64::ptr_t new_file_hdr ( new Elf_File_Header_64() );

	  m_elf_file->read_Elf_File_Header ( new_file_hdr );

	  if ( new_file_hdr->needs_Convert() )
	    {
	      new_file_hdr->convert();
	      m_convert = true;
	    }

	  m_elf_data->set_File_Header ( new_file_hdr );


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DATA,
			       "---- Elf Header dump: -----" );
	  
	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DATA,
			       new_file_hdr->to_String() );
#endif /* LIBREVERSE_DEBUG */

	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::read_File_Header" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_Reader_64::read_Section_Headers ()
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::read_Section_Headers" );
#endif /* LIBREVERSE_DEBUG */


      read_File_Header();

      std::vector< elf_types::Elf_Section_Header_64::ptr_t > m_section_list;

      // Move read point to position of section header table offset
      elf_types::Elf_File_Header_64::const_ptr_t file_hdr_ptr = m_elf_data->get_File_Header();

      if ( ( file_hdr_ptr->get_Section_Header_Count() > 0 ) &&
	   ( ! m_elf_data->has_Section_Headers() ) )
	{
	  // Start by moving to the section header offset
	  boost::uint64_t sec_offset = file_hdr_ptr->get_Section_Header_Offset();

	  m_elf_file->seek ( sec_offset );

	  boost::uint16_t sec_count = file_hdr_ptr->get_Section_Header_Count();

	  boost::uint16_t string_token_index = file_hdr_ptr->get_String_Token_Index();
	  
	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DATA,
			       "index type flag addr offset size link info address_align ent_size" );

	  for ( boost::uint32_t i = 0;
		i < sec_count;
		i++ )
	    {
	      elf_types::Elf_Section_Header_64::ptr_t temp ( new Elf_Section_Header_64 ( file_hdr_ptr->get_Machine_Value() ) );

	      m_elf_file->read_Elf_Section_Header ( temp );
	      
	      if ( m_convert )
		{
		  temp->convert();
		}

	      m_section_list.push_back ( temp );
	    }

	  if ( ! m_section_list.empty() )
	    {
	      elf_types::Elf_Section_Header_64::ptr_t string_hdr =
		m_section_list[ string_token_index ];

	      // Copy from elf_file to table_data
	      m_elf_file->seek ( string_hdr->get_Section_Offset() );


	      // TODO error handling
	      m_string_table_ptr =
		m_elf_file->subset
		( string_hdr->get_Section_Size() );

	      for ( std::vector< elf_types::Elf_Section_Header_64::ptr_t >::iterator pos =
		      m_section_list.begin();
		    pos != m_section_list.end();
		    pos++ )
		{

		  elf_types::Elf_Section_Header_64::ptr_t sec_hdr_ptr = ( *pos );

		  if ( sec_hdr_ptr->get_Section_Name_Index() >= string_hdr->get_Section_Size() )
		    {
		      sec_hdr_ptr->set_Section_String_Name ( "<corrupt>" );


#ifdef LIBREVERSE_DEBUG
		      Trace::write_Trace ( TraceArea::IO,
					   TraceLevel::DATA,
					   boost::str ( boost::format ( "%|-18|" ) %
							sec_hdr_ptr->get_Section_String_Name() ) );
#endif /* LIBREVERSE_DEBUG */


		    }
		  else
		    {
		      sec_hdr_ptr->set_Section_String_Name
			( this->get_String_Name ( sec_hdr_ptr->get_Section_Name_Index() ) );


#ifdef LIBREVERSE_DEBUG
		      Trace::write_Trace ( TraceArea::IO,
					   TraceLevel::DATA,
					   boost::str ( boost::format ( "%|-18|" ) %
							sec_hdr_ptr->get_Section_String_Name() ) );
#endif /* LIBREVERSE_DEBUG */

		    }

		  m_elf_data->push_Back_Section_Header ( sec_hdr_ptr );


#ifdef LIBREVERSE_DEBUG
		  Trace::write_Trace ( TraceArea::IO,
				       TraceLevel::DATA,
				       sec_hdr_ptr->to_String() );
#endif /* LIBREVERSE_DEBUG */

		}


#ifdef LIBREVERSE_DEBUG
	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   "Key to Flags:" );

	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   "  W (write), A (alloc), X (execute), M (merge), S (strings)" );

	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   "  I (info), L (link order), G (group), x (unknown)" );

	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   "  O (extra OS processing required) o (OS specific), " );

	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   "p (processor specific)" );
#endif /* LIBREVERSE_DEBUG */

	    }
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::read_Section_Headers" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_Reader_64::read_Program_Headers ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::read_Program_Headers" );
#endif /* LIBREVERSE_DEBUG */


      read_File_Header();

      elf_types::Elf_File_Header_64::const_ptr_t file_hdr_ptr = m_elf_data->get_File_Header();

      if ( ( file_hdr_ptr->get_Program_Header_Count() > 0 ) &&
	   ( ! m_elf_data->has_Program_Headers() ) )
	{
	  m_elf_file->seek ( file_hdr_ptr->get_Program_Header_Offset() );

	  for ( unsigned int i = 0;
		i < file_hdr_ptr->get_Program_Header_Count();
		++i )
	    {
	      elf_types::Elf_Program_Header_64::ptr_t prg_hdr
		( new Elf_Program_Header_64 ( file_hdr_ptr->get_Machine_Value() ) );

	      m_elf_file->read_Elf_Program_Header ( prg_hdr );

	      /* Get dynamic header symbols */
	      if ( prg_hdr->get_Type () == Elf_Common::PT_DYNAMIC )
		{
		  read_Dynamic_Headers ();
		}

	      if ( m_convert )
		{
		  prg_hdr->convert();
		}

	      m_elf_data->push_Back_Program_Header ( prg_hdr );
	    }


#ifdef LIBREVERSE_DEBUG

	  if ( m_elf_data->has_Program_Headers() )
	    {
	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   "Program Headers:" );

	      std::stringstream output;

	      output << boost::format ( "  %|-15| " ) % "TYPE"
		     << boost::format ( "%|-10| " ) % "Offset"
		     << boost::format ( "%|-12| " ) % "Virtaddr"
		     << boost::format ( "%|-12| " ) % "Physaddr"
		     << boost::format ( "%|-8| " ) % "Filesiz"
		     << boost::format ( "%|-10| " ) % "Memsiz"
		     << boost::format ( "%|-4| " ) % "Flg"
		     << boost::format ( "%|-5|" ) % "Align";

	      Trace::write_Trace ( TraceArea::IO,
				   TraceLevel::DATA,
				   m_elf_data->get_Program_Header_String () );
	    }
#endif /* LIBREVERSE_DEBUG */


	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::read_Program_Headers" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_Reader_64::read_Dynamic_Headers ( void )
    {


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::read_Dynamic_Headers" );
#endif /* LIBREVERSE_DEBUG */


      //Elf_Dynamic_Header_64 *dyn_hdr = new Elf_Dynamic_Header_64();

      /*
      // Find the appropriate symbol table.
      if (dynamic_symbols == NULL)
      {
      for (i = 0, entry = dynamic_segment;
      i < dynamic_size;
      ++i, ++entry)
      {
      Elf_Internal_Shdr section;

      if (entry->d_tag != DT_SYMTAB)
      continue;

      dynamic_info[DT_SYMTAB] = entry->d_un.d_val;

      // Since we do not know how big the symbol table is,
      //   we default to reading in the entire file (!) and
      //   processing that.  This is overkill, I know, but it
      //   should work.
      section.sh_offset = entry->d_un.d_val - loadaddr;

      if (fseek (file, 0, SEEK_END))
      error (_("Unable to seek to end of file!"));

      section.sh_size = ftell (file) - section.sh_offset;
      if (is_32bit_elf)
      section.sh_entsize = sizeof (Elf32_External_Sym);
      else
      section.sh_entsize = sizeof (Elf64_External_Sym);

      num_dynamic_syms = section.sh_size / section.sh_entsize;
      if (num_dynamic_syms < 1)
      {
      error (_("Unable to determine the number of symbols to load\n"));
      continue;
      }

      dynamic_symbols = GET_ELF_SYMBOLS (file, &section);
      }
      }

      // Similarly find a string table.
      if (dynamic_strings == NULL)
      {
      for (i = 0, entry = dynamic_segment;
      i < dynamic_size;
      ++i, ++entry)
      {
      unsigned long offset;
      long str_tab_len;

      if (entry->d_tag != DT_STRTAB)
      continue;

      dynamic_info[DT_STRTAB] = entry->d_un.d_val;

      // Since we do not know how big the string table is,
      //   we default to reading in the entire file (!) and
      //   processing that.  This is overkill, I know, but it
      //   should work.

      offset = entry->d_un.d_val - loadaddr;
      if (fseek (file, 0, SEEK_END))
      error (_("Unable to seek to end of file\n"));
      str_tab_len = ftell (file) - offset;

      if (str_tab_len < 1)
      {
      error
      (_("Unable to determine the length of the dynamic string table\n"));
      continue;
      }

      dynamic_strings = (char *) get_data (NULL, file, offset, str_tab_len,
      _("dynamic string table"));
      break;
      }
      }

      // And find the syminfo section if available.
      if (dynamic_syminfo == NULL)
      {
      unsigned long syminsz = 0;

      for (i = 0, entry = dynamic_segment;
      i < dynamic_size;
      ++i, ++entry)
      {
      if (entry->d_tag == DT_SYMINENT)
      {
      // Note: these braces are necessary to avoid a syntax
      //   error from the SunOS4 C compiler.
      assert (sizeof (Elf_External_Syminfo) == entry->d_un.d_val);
      }
      else if (entry->d_tag == DT_SYMINSZ)
      syminsz = entry->d_un.d_val;
      else if (entry->d_tag == DT_SYMINFO)
      dynamic_syminfo_offset = entry->d_un.d_val - loadaddr;
      }

      if (dynamic_syminfo_offset != 0 && syminsz != 0)
      {
      Elf_External_Syminfo *extsyminfo;
      Elf_Internal_Syminfo *syminfo;

      // There is a syminfo section.  Read the data.
      extsyminfo = ((Elf_External_Syminfo *)
      get_data (NULL, file, dynamic_syminfo_offset,
      syminsz, _("symbol information")));
      if (!extsyminfo)
      return 0;

      dynamic_syminfo = (Elf_Internal_Syminfo *) malloc (syminsz);
      if (dynamic_syminfo == NULL)
      {
      error (_("Out of memory\n"));
      return 0;
      }

      dynamic_syminfo_nent = syminsz / sizeof (Elf_External_Syminfo);
      for (i = 0, syminfo = dynamic_syminfo; i < dynamic_syminfo_nent;
      ++i, ++syminfo)
      {
      syminfo->si_boundto = BYTE_GET (extsyminfo[i].si_boundto);
      syminfo->si_flags = BYTE_GET (extsyminfo[i].si_flags);
      }

      free (extsyminfo);
      }
      }

      if (do_dynamic && dynamic_addr)
      printf (_("\nDynamic segment at offset 0x%lx contains %ld entries:\n"),
      dynamic_addr, (long) dynamic_size);
      if (do_dynamic)
      printf (_("  Tag        Type                         Name/Value\n"));

      for (i = 0, entry = dynamic_segment;
      i < dynamic_size;
      i++, entry++)
      {
      if (do_dynamic)
      {
      const char *dtype;

      putchar (' ');
      print_vma (entry->d_tag, FULL_HEX);
      dtype = get_dynamic_type (entry->d_tag);
      printf (" (%s)%*s", dtype,
      ((is_32bit_elf ? 27 : 19)
      - (int) strlen (dtype)),
      " ");
      }

      switch (entry->d_tag)
      {
      case DT_FLAGS:
      if (do_dynamic)
      puts (get_dynamic_flags (entry->d_un.d_val));
      break;

      case DT_AUXILIARY:
      case DT_FILTER:
      case DT_CONFIG:
      case DT_DEPAUDIT:
      case DT_AUDIT:
      if (do_dynamic)
      {
      switch (entry->d_tag)
      {
      case DT_AUXILIARY:
      printf (_("Auxiliary library"));
      break;

      case DT_FILTER:
      printf (_("Filter library"));
      break;

      case DT_CONFIG:
      printf (_("Configuration file"));
      break;

      case DT_DEPAUDIT:
      printf (_("Dependency audit library"));
      break;

      case DT_AUDIT:
      printf (_("Audit library"));
      break;
      }

      if (dynamic_strings)
      printf (": [%s]\n", dynamic_strings + entry->d_un.d_val);
      else
      {
      printf (": ");
      print_vma (entry->d_un.d_val, PREFIX_HEX);
      putchar ('\n');
      }
      }
      break;

      case DT_FEATURE:
      if (do_dynamic)
      {
      printf (_("Flags:"));

      if (entry->d_un.d_val == 0)
      printf (_(" None\n"));
      else
      {
      unsigned long int val = entry->d_un.d_val;

      if (val & DTF_1_PARINIT)
      {
      printf (" PARINIT");
      val ^= DTF_1_PARINIT;
      }
      if (val & DTF_1_CONFEXP)
      {
      printf (" CONFEXP");
      val ^= DTF_1_CONFEXP;
      }
      if (val != 0)
      printf (" %lx", val);
      puts ("");
      }
      }
      break;

      case DT_POSFLAG_1:
      if (do_dynamic)
      {
      printf (_("Flags:"));

      if (entry->d_un.d_val == 0)
      printf (_(" None\n"));
      else
      {
      unsigned long int val = entry->d_un.d_val;

      if (val & DF_P1_LAZYLOAD)
      {
      printf (" LAZYLOAD");
      val ^= DF_P1_LAZYLOAD;
      }
      if (val & DF_P1_GROUPPERM)
      {
      printf (" GROUPPERM");
      val ^= DF_P1_GROUPPERM;
      }
      if (val != 0)
      printf (" %lx", val);
      puts ("");
      }
      }
      break;

      case DT_FLAGS_1:
      if (do_dynamic)
      {
      printf (_("Flags:"));
      if (entry->d_un.d_val == 0)
      printf (_(" None\n"));
      else
      {
      unsigned long int val = entry->d_un.d_val;

      if (val & DF_1_NOW)
      {
      printf (" NOW");
      val ^= DF_1_NOW;
      }
      if (val & DF_1_GLOBAL)
      {
      printf (" GLOBAL");
      val ^= DF_1_GLOBAL;
      }
      if (val & DF_1_GROUP)
      {
      printf (" GROUP");
      val ^= DF_1_GROUP;
      }
      if (val & DF_1_NODELETE)
      {
      printf (" NODELETE");
      val ^= DF_1_NODELETE;
      }
      if (val & DF_1_LOADFLTR)
      {
      printf (" LOADFLTR");
      val ^= DF_1_LOADFLTR;
      }
      if (val & DF_1_INITFIRST)
      {
      printf (" INITFIRST");
      val ^= DF_1_INITFIRST;
      }
      if (val & DF_1_NOOPEN)
      {
      printf (" NOOPEN");
      val ^= DF_1_NOOPEN;
      }
      if (val & DF_1_ORIGIN)
      {
      printf (" ORIGIN");
      val ^= DF_1_ORIGIN;
      }
      if (val & DF_1_DIRECT)
      {
      printf (" DIRECT");
      val ^= DF_1_DIRECT;
      }
      if (val & DF_1_TRANS)
      {
      printf (" TRANS");
      val ^= DF_1_TRANS;
      }
      if (val & DF_1_INTERPOSE)
      {
      printf (" INTERPOSE");
      val ^= DF_1_INTERPOSE;
      }
      if (val & DF_1_NODEFLIB)
      {
      printf (" NODEFLIB");
      val ^= DF_1_NODEFLIB;
      }
      if (val & DF_1_NODUMP)
      {
      printf (" NODUMP");
      val ^= DF_1_NODUMP;
      }
      if (val & DF_1_CONLFAT)
      {
      printf (" CONLFAT");
      val ^= DF_1_CONLFAT;
      }
      if (val != 0)
      printf (" %lx", val);
      puts ("");
      }
      }
      break;

      case DT_PLTREL:
      dynamic_info[entry->d_tag] = entry->d_un.d_val;
      if (do_dynamic)
      puts (get_dynamic_type (entry->d_un.d_val));
      break;

      case DT_NULL    :
      case DT_NEEDED  :
      case DT_PLTGOT  :
      case DT_HASH    :
      case DT_STRTAB  :
      case DT_SYMTAB  :
      case DT_RELA    :
      case DT_INIT    :
      case DT_FINI    :
      case DT_SONAME  :
      case DT_RPATH   :
      case DT_SYMBOLIC:
      case DT_REL :
      case DT_DEBUG   :
      case DT_TEXTREL :
      case DT_JMPREL  :
      case DT_RUNPATH :
      dynamic_info[entry->d_tag] = entry->d_un.d_val;

      if (do_dynamic)
      {
      char *name;

      if (dynamic_strings == NULL)
      name = NULL;
      else
      name = dynamic_strings + entry->d_un.d_val;

      if (name)
      {
      switch (entry->d_tag)
      {
      case DT_NEEDED:
      printf (_("Shared library: [%s]"), name);

      if (strcmp (name, program_interpreter) == 0)
      printf (_(" program interpreter"));
      break;

      case DT_SONAME:
      printf (_("Library soname: [%s]"), name);
      break;

      case DT_RPATH:
      printf (_("Library rpath: [%s]"), name);
      break;

      case DT_RUNPATH:
      printf (_("Library runpath: [%s]"), name);
      break;

      default:
      print_vma (entry->d_un.d_val, PREFIX_HEX);
      break;
      }
      }
      else
      print_vma (entry->d_un.d_val, PREFIX_HEX);

      putchar ('\n');
      }
      break;

      case DT_PLTRELSZ:
      case DT_RELASZ  :
      case DT_STRSZ   :
      case DT_RELSZ   :
      case DT_RELAENT :
      case DT_SYMENT  :
      case DT_RELENT  :
      dynamic_info[entry->d_tag] = entry->d_un.d_val;
      case DT_PLTPADSZ:
      case DT_MOVEENT :
      case DT_MOVESZ  :
      case DT_INIT_ARRAYSZ:
      case DT_FINI_ARRAYSZ:
      case DT_GNU_CONFLICTSZ:
      case DT_GNU_LIBLISTSZ:
      if (do_dynamic)
      {
      print_vma (entry->d_un.d_val, UNSIGNED);
      printf (" (bytes)\n");
      }
      break;

      case DT_VERDEFNUM:
      case DT_VERNEEDNUM:
      case DT_RELACOUNT:
      case DT_RELCOUNT:
      if (do_dynamic)
      {
      print_vma (entry->d_un.d_val, UNSIGNED);
      putchar ('\n');
      }
      break;

      case DT_SYMINSZ:
      case DT_SYMINENT:
      case DT_SYMINFO:
      case DT_USED:
      case DT_INIT_ARRAY:
      case DT_FINI_ARRAY:
      if (do_dynamic)
      {
      if (dynamic_strings != NULL && entry->d_tag == DT_USED)
      {
      char *name;

      name = dynamic_strings + entry->d_un.d_val;

      if (*name)
      {
      printf (_("Not needed object: [%s]\n"), name);
      break;
      }
      }

      print_vma (entry->d_un.d_val, PREFIX_HEX);
      putchar ('\n');
      }
      break;

      case DT_BIND_NOW:
      // The value of this entry is ignored.
      if (do_dynamic)
      putchar ('\n');
      break;

      case DT_GNU_PRELINKED:
      if (do_dynamic)
      {
      struct tm *tmp;
      time_t time = entry->d_un.d_val;

      tmp = gmtime (&time);
      printf ("%04u-%02u-%02uT%02u:%02u:%02u\n",
      tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday,
      tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

      }
      break;

      default:
      if ((entry->d_tag >= DT_VERSYM) && (entry->d_tag <= DT_VERNEEDNUM))
      version_info[DT_VERSIONTAGIDX (entry->d_tag)] =
      entry->d_un.d_val;

      if (do_dynamic)
      {
      switch (elf_header.get_Machine_Value())
      {
      case EM_MIPS:
      case EM_MIPS_RS3_LE:
      dynamic_segment_mips_val (entry);
      break;
      case EM_PARISC:
      dynamic_segment_parisc_val (entry);
      break;
      case EM_IA_64:
      dynamic_segment_ia64_val (entry);
      break;
      default:
      print_vma (entry->d_un.d_val, PREFIX_HEX);
      putchar ('\n');
      }
      }
      break;
      }
      }

      return 1;
      */


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::read_Dynamic_Headers" );
#endif /* LIBREVERSE_DEBUG */

    }

    std::string
    Elf_Reader_64::get_File_Type ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::get_File_Type" );
#endif /* LIBREVERSE_DEBUG */


      std::string result = Elf_Meta_Info::FILE_TYPE_64BIT;


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::get_File_Type" );
#endif /* LIBREVERSE_DEBUG */


      return result;
    }

    std::string
    Elf_Reader_64::get_Arch_Type ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::get_Arch_Type" );
#endif /* LIBREVERSE_DEBUG */


      read_File_Header();

      elf_types::Elf_File_Header_64::const_ptr_t file_hdr_ptr = m_elf_data->get_File_Header();

      std::string result = file_hdr_ptr->get_Arch_Type();


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::get_Arch_Type" );
#endif /* LIBREVERSE_DEBUG */


      return result;
    }

    std::string
    Elf_Reader_64::get_Section_Offset ( std::string name )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::get_Section_Offset" );
#endif /* LIBREVERSE_DEBUG */


      read_File_Header();

      elf_types::Elf_File_Header_64::const_ptr_t file_hdr_ptr = m_elf_data->get_File_Header();

      if ( file_hdr_ptr->get_Section_Header_Count() > 0 )
	{
	  read_Section_Headers();
	}

      elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr_ptr =
	m_elf_data->get_Section_Header ( this->get_Section_String ( name ) );

      std::stringstream output;
      output << sec_hdr_ptr->get_Section_Offset ();


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::get_Section_Offset" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    std::string
    Elf_Reader_64::get_Section_Length ( std::string name )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::get_Section_Length" );
#endif /* LIBREVERSE_DEBUG */


      read_File_Header();

      elf_types::Elf_File_Header_64::const_ptr_t file_hdr_ptr = m_elf_data->get_File_Header();

      if ( file_hdr_ptr->get_Section_Header_Count() > 0 )
	{
	  read_Section_Headers();
	}

      elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr_ptr =
	m_elf_data->get_Section_Header ( this->get_Section_String ( name ) );

      std::stringstream output;
      output << sec_hdr_ptr->get_Section_Size ();


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::get_Section_Length" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    std::string
    Elf_Reader_64::get_Entry_Point ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::get_Entry_Point" );
#endif /* LIBREVERSE_DEBUG */


      read_File_Header();

      elf_types::Elf_File_Header_64::const_ptr_t file_hdr_ptr = m_elf_data->get_File_Header();

      std::stringstream output;
      output << file_hdr_ptr->get_Entry ();


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::get_Entry_Point" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    std::string
    Elf_Reader_64::get_Base_Address ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::get_Base_Address" );
#endif /* LIBREVERSE_DEBUG */


      read_Program_Headers();

      std::stringstream output;

      output << m_elf_data->get_Base_Address();


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::get_Base_Address" );
#endif /* LIBREVERSE_DEBUG */


      return output.str();
    }

    void
    Elf_Reader_64::read_Symbol_Token ()
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::read_Symbol_Token" );
#endif /* LIBREVERSE_DEBUG */


      /*
	Elf_File_Header_64::ptr_t file_hdr =
	m_elf_data->get_File_Header();

	Elf_Section_Header_64::ptr_t sec_hdr;

	boost::uint16_t pos = 0;
	for ( ; pos != file_hdr->get_Section_Header_Count();
	++pos)
	{

	sec_hdr = m_elf_data->get_Section_Header(pos);

	if (sec_hdr->get_Section_Type() == Elf_Common::SHT_SYMTAB)
	{
	break;
	}
	}

	if (pos == file_hdr->get_Section_Header_Count())
	{
	return;
	}

	Elf_Section_Header_64::ptr_t symbol_hdr = sec_hdr;

	Elf_Section_Header_64::ptr_t symbol_string_hdr =
	m_elf_data->get_Section_Header (symbol_hdr->get_Next_Section_Index());

	char* string_table =
	(char*)m_elf_file->read (symbol_string_hdr->get_Section_Offset(),
	symbol_string_hdr->get_Section_Size());

	boost::uint32_t num_symbols = symbol_hdr->get_Section_Size() /
	symbol_hdr->get_Section_Token_Size();

	m_elf_file->seek (symbol_hdr->get_Section_Offset());

	for (boost::uint32_t i = 0; i < num_symbols; ++i)
	{
	Elf_Symbol_64::ptr_t symbol
	(new Elf_Symbol_64 (file_hdr->get_Machine_Value()));

	m_elf_file->read_Elf_Symbol (symbol);
	m_elf_data->push_Back_Symbol (symbol);
	}

	std::cout << std::endl << "Symbol Token:" << std::endl
	<< boost::format("%|8|") % "Num:"
	<< boost::format("%|9|") % "Value"
	<< boost::format("%|6|") % "Size"
	<< boost::format(" %|-9|") % "Type"
	<< boost::format("%|-9|") % "Bind"
	<< boost::format("%|-7|") % "Vis"
	<< boost::format("%|4|") % "Ndx"
	<< boost::format(" %|4|") % "Name" << std::endl;

	std::cout << m_elf_data->get_Symbol_Token_String (string_table)
	<< std::endl;
      */


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::read_Symbol_Token" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Elf_Reader_64::read_Relocations ()
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::read_Relocations" );
#endif /* LIBREVERSE_DEBUG */


      read_File_Header();

      elf_types::Elf_File_Header_64::const_ptr_t file_hdr = m_elf_data->get_File_Header();

      if ( file_hdr->get_Section_Header_Count() > 0 )
	{

	  read_Section_Headers();

	  elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr;

	  for ( boost::uint16_t pos = 0 ;
		pos != file_hdr->get_Section_Header_Count();
		++pos )
	    {
	      sec_hdr = m_elf_data->get_Section_Header ( pos );

	      switch ( sec_hdr->get_Section_Type() )
		{
		case Elf_Common::SHT_RELA:
		  {
		    // If the Relocation Symbols have not been retrieved
		    // then read the symbols into Elf Header
		    if ( !m_elf_data->has_Symbols() )
		      {
			this->read_Relocation_Symbols ( sec_hdr, file_hdr );
		      }

		    // Read the Relocation Addend Headers into Elf Header
		    this->read_Relocation_Addend_Headers ( sec_hdr, file_hdr );

		    break;
		  }
		case Elf_Common::SHT_REL:
		  {
		    // If the Relocation Symbols have not been retrieved
		    // then read the symbols into Elf Header
		    if ( !m_elf_data->has_Symbols() )
		      {
			this->read_Relocation_Symbols ( sec_hdr, file_hdr );
		      }

		    // Read the Relocation Addend Headers into Elf Header
		    this->read_Relocation_Headers ( sec_hdr, file_hdr );

		    break;
		  }
		default:
		  {
		    continue;
		  }
		}
	    }
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::read_Relocations" );
#endif /* LIBREVERSE_DEBUG */


    }

    bool
    Elf_Reader_64::support_File_Type ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::support_File_Type" );
#endif /* LIBREVERSE_DEBUG */


      bool result = true;

      if ( ! m_elf_file->init() )
	{


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::ERROR,
			       "Error initializing file. Checking standard output for error message." );
#endif /* LIBREVERSE_DEBUG */


	  result = false;
	}
      else
	{
	  elf_types::Elf_Header_Eident::ptr_t eident_header ( new Elf_Header_Eident() );

	  m_elf_file->read_Elf_Header_Eident ( eident_header );


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DETAIL,
			       "Exiting Elf_Reader::support_File_Type" );
#endif /* LIBREVERSE_DEBUG */


	  result = eident_header->is_Elf_File();


#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DETAIL,
			       "Exiting Elf_Reader::support_File_Type" );
#endif /* LIBREVERSE_DEBUG */

	}

      return result;
    }

    void
    Elf_Reader_64::read_Relocation_Headers ( elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr,
					     elf_types::Elf_File_Header_64::const_ptr_t file_hdr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::read_Relocation_Headers" );
#endif /* LIBREVERSE_DEBUG */


      // Setup file for position to reading Relocation headers
      m_elf_file->seek ( sec_hdr->get_Section_Offset() );
      boost::uint32_t number_relocs = sec_hdr->get_Section_Size() /
	sec_hdr->get_Section_Token_Size();


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DATA,
			   boost::str
			   ( boost::format ( "Relocations section '%s' at offset %d contains %d entries:" )
			     % sec_hdr->get_Section_String_Name()
			     % sec_hdr->get_Section_Offset()
			     % number_relocs ) );

      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DATA,
			   " Offset     Info       Type            Sym.Value     Sym.Name" );
#endif /* LIBREVERSE_DEBUG */
      
      // Read Relocation headers and add to Elf_Header.
      for ( boost::uint32_t i = 0; i < number_relocs; ++i )
	{
	  elf_types::Elf_Relocation_64::ptr_t reloc_hdr ( new Elf_Relocation_64 ( file_hdr ) );

	  m_elf_file->read_Elf_Relocation ( reloc_hdr );

	  if ( m_convert )
	    {
	      reloc_hdr->convert ();
	    }


#ifdef LIBREVERSE_DEBUG
	  elf_types::Elf_Symbol_64::const_ptr_t reloc_symbol = m_elf_data->get_Symbol ( reloc_hdr->get_Symbol_Token_Index() );

	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DATA,
			       boost::str
			       ( boost::format ( "%s   %s" )
				 % reloc_hdr->to_String()
				 % reloc_symbol->to_String() ) );
#endif /* LIBREVERSE_DEBUG */
      

	  m_elf_data->push_Back_Relocation_Header ( reloc_hdr );
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::read_Relocation_Headers" );
#endif /* LIBREVERSE_DEBUG */
      
    }

    void
    Elf_Reader_64::read_Relocation_Addend_Headers ( elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr,
						    elf_types::Elf_File_Header_64::const_ptr_t file_hdr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::read_Relocation_Addend_Headers" );
#endif /* LIBREVERSE_DEBUG */
      

      m_elf_file->seek ( sec_hdr->get_Section_Offset() );

      boost::uint32_t number_relocs =
	sec_hdr->get_Section_Size() /
	sec_hdr->get_Section_Token_Size();


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DATA,
			   boost::str
			   ( boost::format ( "Relocations section '%s' at offset %d contains %d entries:" )
			     % sec_hdr->get_Section_String_Name()
			     % sec_hdr->get_Section_Offset()
			     % number_relocs ) );
#endif /* LIBREVERSE_DEBUG */
      

      for ( boost::uint32_t i = 0; i < number_relocs; ++i )
	{
	  elf_types::Elf_Relocation_Add_64::ptr_t reloc_add_hdr ( new Elf_Relocation_Add_64 ( file_hdr ) );

	  m_elf_file->read_Elf_Relocation_Add ( reloc_add_hdr );

	  if ( m_convert )
	    {
	      reloc_add_hdr->convert ();
	    }


#ifdef LIBREVERSE_DEBUG
	  elf_types::Elf_Symbol_64::const_ptr_t reloc_symbol = m_elf_data->get_Symbol ( reloc_add_hdr->get_Symbol_Token_Index() );

	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DATA,
			       boost::str
			       ( boost::format ( "%s   %s" )
				 % reloc_add_hdr->to_String()
				 % reloc_symbol->to_String() ) );
#endif /* LIBREVERSE_DEBUG */
      

	  m_elf_data->push_Back_Relocation_Add_Header ( reloc_add_hdr );
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::read_Relocation_Addend_Headers" );
#endif /* LIBREVERSE_DEBUG */
      

    }

    void
    Elf_Reader_64::read_Relocation_Symbols ( elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr,
					     elf_types::Elf_File_Header_64::const_ptr_t file_hdr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::read_Relocation_Symbols" );
#endif /* LIBREVERSE_DEBUG */
      

      // Setup file for position to reading Relocation Symbols
      elf_types::Elf_Section_Header_64::const_ptr_t sym_hdr =
	m_elf_data->get_Section_Header ( sec_hdr->get_Next_Section_Index() );

      elf_types::Elf_Section_Header_64::const_ptr_t sym_string_hdr =
	m_elf_data->get_Section_Header ( sym_hdr->get_Next_Section_Index() );

      m_elf_file->seek ( sym_string_hdr->get_Section_Offset() );

      m_string_table_ptr = m_elf_file->subset ( sym_string_hdr->get_Section_Size() );

      m_elf_file->seek ( sym_hdr->get_Section_Offset() );

      boost::uint32_t number_symbols =
	sym_hdr->get_Section_Size() /
	sym_hdr->get_Section_Token_Size();

      // Read Symbols
      for ( boost::uint32_t i = 0; i < number_symbols; ++i )
	{
	  elf_types::Elf_Symbol_64::ptr_t reloc_symbol ( new Elf_Symbol_64 ( file_hdr->get_Machine_Value() ) );

	  m_elf_file->read_Elf_Symbol ( reloc_symbol );

	  if ( m_convert )
	    {
	      reloc_symbol->convert();
	    }

	  this->set_Symbol_Name ( reloc_symbol );

	  m_elf_data->push_Back_Symbol ( reloc_symbol );
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::read_Relocation_Symbols" );
#endif /* LIBREVERSE_DEBUG */
      

    }

    void
    Elf_Reader_64::read_Headers ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::read_Headers" );
#endif /* LIBREVERSE_DEBUG */
      

      this->read_Program_Headers();
      this->read_Section_Headers();


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::read_Headers" );
#endif /* LIBREVERSE_DEBUG */
      
    }

    data_types::Memory_Map::ptr_t
    Elf_Reader_64::get_Memory_Map ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::get_Memory_Map" );
#endif /* LIBREVERSE_DEBUG */
      

      this->read_Headers();

      // Get base address of the image
      boost::uint64_t base_address = m_elf_data->get_Base_Address();
      std::cout << boost::format ( "Elf_Reader::get_Memory_Map - base_address = %1$-08X" ) % base_address << std::endl;

      // Steps to load elf
      /* 1. Build process image by loading all the sections.

	 The program header table tells the system how to create a
	 process image. Files used to build a process image (execute
	 a program) must have a program header table. A section
	 header table contains information describing the file's
	 sections. Every section has an entry in the table; each
	 entry gives information such as the section name, the
	 section size, etc. Files used during linking must have a
	 section header table.

	 A process image has segments that hold its text, data,
	 stack, and so on. The major sections in this part discuss
	 the following:

	 - Program header. This section complements Part 1,
	 describing object file structures that relate directly to
	 program execution. The primary data structure, a program
	 header table, locates segment images within the file and
	 contains other information necessary to create the memory
	 image for the program.

	 - Program loading. Given an object file, the system must
	 load it into memory for the program to run.

	 - Dynamic linking. After the system loads the program, it
	 must complete the process image by resolving symbolic
	 references among the object files that compose the process.

	 NOTE: For now ignore Dynamic programs (e_type == ET_DYN)

	 ALGORITHM:

	 if e_type == ET_DYN
	 EXCEPTION (Unsupported_Executable)

	 FOR all x:Elf_Program_Headers
	 IF x.p_type != LOAD THEN skip
	 Set memory protections based on x.p_flags
	 Map x into memory from file location to x.p_vaddr with
	 memory protections
      */
      elf_types::Elf_File_Header_64::const_ptr_t elf_file_hdr_ptr = m_elf_data->get_File_Header();

      boost::uint16_t const elf_type = elf_file_hdr_ptr->get_File_Type_Value();

      if ( elf_type != Elf_Common::ET_EXEC )
	{
	  // ERROR
	}
      /* 2. Perform relocations */

      /* (QUESTION?)3. Perform dynamic linking */
      data_types::Memory_Map::ptr_t result ( new data_container::Memory_Map ( 0 ) );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::get_Memory_Map" );
#endif /* LIBREVERSE_DEBUG */
      

      return result;

    }

    std::string
    Elf_Reader_64::get_Section_String ( std::string name ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::get_Section_String" );
#endif /* LIBREVERSE_DEBUG */
      

      std::string output = name;

      if ( name.compare ( ".code" ) == 0 )
	{
	  output = ".text";
	}


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::get_Section_String" );
#endif /* LIBREVERSE_DEBUG */
      

      return output;
    }

    std::string
    Elf_Reader_64::to_String ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::to_String" );
#endif /* LIBREVERSE_DEBUG */
      

      this->read_Headers();

      std::string result = m_elf_data->to_String();


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::to_String" );
#endif /* LIBREVERSE_DEBUG */
      

      return result;
    }

    io_types::Text_Data::data_type
    Elf_Reader_64::get_Text_Strings ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::get_Text_String" );
#endif /* LIBREVERSE_DEBUG */
      

      io_types::Text_Data::data_type output;

      this->read_Headers();

      m_elf_data->get_Text_String ( &output );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::get_Text_String" );
#endif /* LIBREVERSE_DEBUG */
      

      return output;
    }

    io_types::Text_Data::data_type
    Elf_Reader_64::get_UTF16_Strings ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::get_UTF16_String" );
#endif /* LIBREVERSE_DEBUG */
      

      io_types::Text_Data::data_type output;

      // For each section
      //  - Read UTF-16 Strings


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::get_UTF16_String" );
#endif /* LIBREVERSE_DEBUG */
      

      return output;
    }

    std::string
    Elf_Reader_64::get_String_Name ( boost::uint32_t index ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::get_String_Name" );
#endif /* LIBREVERSE_DEBUG */
      

      data_types::Memory_Map::const_iterator pos =
	m_string_table_ptr->begin();

      const char* name = reinterpret_cast<const char*> ( & ( *pos ) + index );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Exiting Elf_Reader::get_String_Name" );
#endif /* LIBREVERSE_DEBUG */
      

      return std::string ( name );
    }

    void
    Elf_Reader_64::set_Symbol_Name ( elf_types::Elf_Symbol_64::ptr_t symbol_ptr )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::set_Symbol_Name" );
#endif /* LIBREVERSE_DEBUG */
      

      std::string name = "";

      // Does the symbol table entry have a string name index?
      if ( symbol_ptr->get_String_Token_Index() == 0 )
	{
	  name = "<null>";

	  // If not, is the symbol table entry associated with a section?
	  // If the answer is NO then the sec_name we defined will be used
	  // to say that name of the entry is "<null>".
	  if ( symbol_ptr->get_Symbol_Type_Value() == Elf_Common::STT_SECTION )
	    {
	      // Find section index assocaited with this symbol table entry
	      boost::uint16_t sec_index = 0;

	      if ( symbol_ptr->get_Index() < Elf_Common::SHN_LORESERVE )
		{
		  // Index is less then the lower bound of the
		  // the range of reserved indexes. The default
		  // is st_shndx.
		  sec_index = symbol_ptr->get_Index();
		}
	      else if ( symbol_ptr->get_Index() > Elf_Common::SHN_LORESERVE )
		{
		  // If a symbol's value refers to a specific location
		  // within a section, its section index member,
		  // st_shndx, holds an index into the section header
		  // table. (Elf)
		  sec_index = symbol_ptr->get_Index() -
		    ( Elf_Common::SHN_HIRESERVE + 1 - Elf_Common::SHN_LORESERVE );
		}

	      // If sec_index is set, Grab the section name
	      if ( sec_index != 0 )
		{
		  // Grab section header
		  elf_types::Elf_Section_Header_64::const_ptr_t sec_hdr = m_elf_data->get_Section_Header ( sec_index );

		  name = sec_hdr->get_Section_String_Name();
		}
	      else if ( symbol_ptr->get_Index() == Elf_Common::SHN_ABS )
		{
		  // The symbol has an absolute value that will not
		  // change because of relocation. (Elf)
		  name = "ABS";
		}
	      else if ( symbol_ptr->get_Index() == Elf_Common::SHN_COMMON )
		{
		  // The symbol labels a common block that has not yet
		  // been allocated. The symbol's value gives alignment
		  // constraints, similar to a section's sh_addralign
		  // member. That is, the link editor will allocate the
		  // storage for the symbol at an address that is a
		  // multiple of st_value. The symbol's size tells how
		  // many bytes are required. (Elf)
		  name = "COMMON";
		}
	      else
		{
		  std::stringstream default_str;
		  default_str << boost::format ( "<section 0x%1%>" ) %
		    boost::io::group ( std::setfill ( '0' ),
				       std::hex, std::setw ( 4 ),
				       symbol_ptr->get_Index() );
		  name = default_str.str();
		}
	    }
	}
      // Is the string table defined?
      else if ( m_string_table_ptr.get() == 0 )
	{
	  std::stringstream data;
	  data << "<string table index "
	       << symbol_ptr->get_String_Token_Index()
	       << ">";

	  name = data.str();
	}
      // Our symbol has a string name index and the string table is
      // defined.  Grab the symbol name from the string table.
      else
	{
	  name = this->get_String_Name ( symbol_ptr->get_String_Token_Index() );
	}

      symbol_ptr->set_Symbol_Name ( name );


#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::set_Symbol_Name" );
#endif /* LIBREVERSE_DEBUG */
      
    }

    elf_types::Elf_Header_64::ptr_t
    Elf_Reader_64::get_Header ( void )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::IO,
			   TraceLevel::DETAIL,
			   "Entering Elf_Reader::get_Header" );
#endif /* LIBREVERSE_DEBUG */
      

      return m_elf_data;
    }
  } /* namespace elf_module */
} /* namespace libreverse */
