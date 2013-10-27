
/*  Elf_Symbol_Utils.cpp

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

#include <reverse/io/input/file_readers/linux_elf/elf_symbol_utils.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_common.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_sparc.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_hppa.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_arm.hpp>
#include <reverse/trace.hpp>

#include <string>

#include <iomanip>

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace linux_elf {

	  std::string
	  elf_symbol_utils::get_symbol_binding ( boost::uint8_t symbol_binding )
	  {
	    trace::io_detail ( "entering elf_symbol_utils::get_symbol_binding" );

	    std::string output_str;

	    switch ( symbol_binding )
	      {
	      case elf_common::STB_LOCAL:   output_str = "LOCAL"; break;
	      case elf_common::STB_GLOBAL:  output_str = "GLOBAL"; break;
	      case elf_common::STB_WEAK:    output_str = "WEAK"; break;
	      default:
                {
		  if ((symbol_binding >= elf_common::STB_LOPROC) &&
		      (symbol_binding <= elf_common::STB_HIPROC))
		    {
		      output_str = boost::str ( boost::format ( "<processor specific>: %1%" ) % symbol_binding );
		    }
		  else if ((symbol_binding >= elf_common::STB_LOOS) &&
			   (symbol_binding <= elf_common::STB_HIOS))
		    {
		      output_str = boost::str ( boost::format ( "<OS specific>: %1%" ) % symbol_binding );
		    }
		  else
		    {
		      output_str = boost::str ( boost::format ( "<unknown>: %1%" ) % symbol_binding );
		    }
                }
	      }

	    trace::io_detail ( "Exiting elf_Symbol_Utils::get_Symbol_Binding" );

	    return output_str;
	  }

	  std::string
	  elf_symbol_utils::get_symbol_index_type ( boost::uint16_t st_shndx )
	  {
	    trace::io_detail ( "entering elf_symbol_utils::get_symbol_index_type" );

	    std::string output_str;

	    switch (st_shndx)
	      {
	      case elf_common::SHN_UNDEF:	output_str = "UND"; break;
	      case elf_common::SHN_ABS:	        output_str = "ABS"; break;
	      case elf_common::SHN_COMMON:	output_str = "COM"; break;
	      default:
                if ( (st_shndx >= elf_common::SHN_LOPROC) &&
                     (st_shndx <= elf_common::SHN_HIPROC) )
		  {
		    output_str = boost::str ( boost::format ("PRC[%1%]") %
		      boost::io::group( std::setfill('0'), std::hex,
					std::setw(4), st_shndx) );
		  }
                else if ( (st_shndx >= elf_common::SHN_LOOS) &&
                          (st_shndx <= elf_common::SHN_HIOS) )
		  {
		    output_str = boost::str ( boost::format ("OS[%1%]") %
					      boost::io::group(std::setfill('0'), std::hex,
							       std::setw(4), st_shndx) ); 
		  }
                else if (st_shndx >= elf_common::SHN_LORESERVE)
		  {
		    output_str = boost::str ( boost::format ("RSV[%1%]") %
					      boost::io::group(std::setfill('0'), std::hex,
							       std::setw(4), st_shndx) );
		  }
                else
		  {
		    output_str = st_shndx;
		  }
                break;
	      }

	    trace::io_detail ( "exiting elf_symbol_utils::get_symbol_index_type" );

	    return output_str;
	  }

	  std::string
	  elf_symbol_utils::get_symbol_type ( boost::uint8_t symbol_type,
					      boost::uint16_t e_machine )
	  {
	    trace::io_detail ( "entering elf_symbol_utils::get_symbol_type" );

	    std::string output_str;

	    switch ( symbol_type )
	      {
	      case elf_common::STT_NOTYPE:	output_str = "NOTYPE"; break;
	      case elf_common::STT_OBJECT:	output_str = "OBJECT"; break;
	      case elf_common::STT_FUNC:	        output_str = "FUNC"; break;
	      case elf_common::STT_SECTION:	output_str = "SECTION"; break;
	      case elf_common::STT_FILE:	        output_str = "FILE"; break;
	      case elf_common::STT_COMMON:	output_str = "COMMON"; break;
	      case elf_common::STT_TLS:	        output_str = "TLS"; break;

	      default:
                if ( (symbol_type >= elf_common::STT_LOPROC) &&
                     (symbol_type <= elf_common::STT_HIPROC) )
		  {
		    if ( (e_machine == elf_common::EM_ARM) &&
			 (symbol_type == elf_arm::STT_ARM_TFUNC) )
		      {
			output_str = "THUMB_FUNC";
		      }
		    else if ( (e_machine == elf_common::EM_SPARCV9) &&
			      (symbol_type == elf_sparc::STT_REGISTER) )
		      {
			output_str = "REGISTER";
		      }
		    else if ( (e_machine == elf_common::EM_PARISC) &&
			      (symbol_type == elf_hppa::STT_PARISC_MILLI) )
		      {
			output_str = "PARISC_MILLI";
		      }
		    else
		      {
			output_str = boost::str ( boost::format ( "<processor specific>: %1%" ) % symbol_type );
		      }
		  }
                else if ( (symbol_type >= elf_common::STT_LOOS) &&
                          (symbol_type <= elf_common::STT_HIOS) )
		  {
		    if (e_machine == elf_common::EM_PARISC)
		      {
			if (symbol_type == elf_hppa::STT_HP_OPAQUE)
			  {
			    output_str = "HP_OPAQUE";
			  }
			else if (symbol_type == elf_hppa::STT_HP_STUB)
			  {
			    output_str = "HP_STUB";
			  }
		      }
		    else {
		      output_str = boost::str ( boost::format ( "<OS specific>: %1%" ) % symbol_type );
		    }
		  }
                else
		  {
		    output_str = boost::str ( boost::format("<unknown>:%1% ") %
					      boost::io::group( std::setfill('0'), std::hex,
								std::setw(4), symbol_type) );
		  }
	      }

	    trace::io_detail ( "exiting elf_symbol_utils::get_symbol_type" );

	    return output_str;
	  }

	  std::string
	  elf_symbol_utils::get_symbol_visibility ( boost::uint8_t st_other )
	  {
	    trace::io_detail ( "entering elf_symbol_utils::get_symbol_visibility" );

	    std::string output_str;

	    boost::uint8_t visibility = (st_other & 0x3);

	    switch (visibility)
	      {
	      case elf_common::STV_DEFAULT:   output_str = "DEFAULT"; break;
	      case elf_common::STV_INTERNAL:  output_str = "INTERNAL"; break;
	      case elf_common::STV_HIDDEN:    output_str = "HIDDEN"; break;
	      case elf_common::STV_PROTECTED: output_str = "PROTECTED"; break;
	      default:                        output_str = "UKNOWN"; break;
	      }

	    trace::io_detail ( "exiting elf_symbol_utils::get_symbol_visibility" );

	    return output_str;
	  }

	} // namespace linux_elf
      } // namespace file_readers
    } // namespace input
  } //  namespace io
} // namespace reverse

