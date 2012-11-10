
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

#include "Elf_Symbol_Utils.h"
#include "Elf_Common.h"
#include "Elf_sparc.h"
#include "Elf_hppa.h"
#include "Elf_arm.h"

#include "io/Byte_Converter.h"

#include <sstream>
#include <iomanip>
#include <boost/format.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse { namespace elf_module {

    std::string
    Elf_Symbol_Utils::get_Symbol_Binding ( boost::uint8_t symbol_binding )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Symbol_Utils::get_symbol_binding" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output_str;

        switch ( symbol_binding )
            {
            case Elf_Common::STB_LOCAL:   output_str << "LOCAL"; break;
            case Elf_Common::STB_GLOBAL:  output_str << "GLOBAL"; break;
            case Elf_Common::STB_WEAK:    output_str << "WEAK"; break;
            default:
                {
                    if ((symbol_binding >= Elf_Common::STB_LOPROC) &&
                        (symbol_binding <= Elf_Common::STB_HIPROC))
                        {
                            output_str << "<processor specific>: " << symbol_binding;
                        }
                    else if ((symbol_binding >= Elf_Common::STB_LOOS) &&
                             (symbol_binding <= Elf_Common::STB_HIOS))
                        {
                            output_str << "<OS specific>: " << symbol_binding;
                        }
                    else
                        {
                            output_str << "<unknown>: " << symbol_binding;
                        }
                }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Symbol_Utils::get_Symbol_Binding" );
#endif /* LIBREVERSE_DEBUG */


        return output_str.str();
    }

    std::string
    Elf_Symbol_Utils::get_Symbol_Index_Type ( boost::uint16_t st_shndx )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Symbol_Utils::get_symbol_index_type" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output_str;

        switch (st_shndx)
            {
            case Elf_Common::SHN_UNDEF:	output_str << "UND"; break;
            case Elf_Common::SHN_ABS:	        output_str << "ABS"; break;
            case Elf_Common::SHN_COMMON:	output_str << "COM"; break;
            default:
                if ( (st_shndx >= Elf_Common::SHN_LOPROC) &&
                     (st_shndx <= Elf_Common::SHN_HIPROC) )
                    {
                        output_str << boost::format ("PRC[%1%]") %
                            boost::io::group( std::setfill('0'), std::hex,
                                              std::setw(4), st_shndx);
                    }
                else if ( (st_shndx >= Elf_Common::SHN_LOOS) &&
                          (st_shndx <= Elf_Common::SHN_HIOS) )
                    {
                        output_str << boost::format ("OS[%1%]") %
                            boost::io::group(std::setfill('0'), std::hex,
                                             std::setw(4), st_shndx);
                    }
                else if (st_shndx >= Elf_Common::SHN_LORESERVE)
                    {
                        output_str << boost::format ("RSV[%1%]") %
                            boost::io::group(std::setfill('0'), std::hex,
                                             std::setw(4), st_shndx);
                    }
                else
                    {
                        output_str << st_shndx;
                    }
                break;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Symbol_Utils::get_symbol_index_type" );
#endif /* LIBREVERSE_DEBUG */


        return output_str.str();
    }

    std::string
    Elf_Symbol_Utils::get_Symbol_Type ( boost::uint8_t symbol_type,
					boost::uint16_t e_machine )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Symbol_Utils::get_symbol_type" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output_str;

        switch ( symbol_type )
            {
            case Elf_Common::STT_NOTYPE:	output_str << "NOTYPE"; break;
            case Elf_Common::STT_OBJECT:	output_str << "OBJECT"; break;
            case Elf_Common::STT_FUNC:	        output_str << "FUNC"; break;
            case Elf_Common::STT_SECTION:	output_str << "SECTION"; break;
            case Elf_Common::STT_FILE:	        output_str << "FILE"; break;
            case Elf_Common::STT_COMMON:	output_str << "COMMON"; break;
            case Elf_Common::STT_TLS:	        output_str << "TLS"; break;

            default:
                if ( (symbol_type >= Elf_Common::STT_LOPROC) &&
                     (symbol_type <= Elf_Common::STT_HIPROC) )
                    {
                        if ( (e_machine == Elf_Common::EM_ARM) &&
                             (symbol_type == Elf_arm::STT_ARM_TFUNC) )
                            {
                                output_str << "THUMB_FUNC";
                            }
                        else if ( (e_machine == Elf_Common::EM_SPARCV9) &&
                                  (symbol_type == Elf_sparc::STT_REGISTER) )
                            {
                                output_str << "REGISTER";
                            }
                        else if ( (e_machine == Elf_Common::EM_PARISC) &&
                                  (symbol_type == Elf_hppa::STT_PARISC_MILLI) )
                            {
                                output_str << "PARISC_MILLI";
                            }
                        else
                            {
                                output_str << "<processor specific>: " << symbol_type;
                            }
                    }
                else if ( (symbol_type >= Elf_Common::STT_LOOS) &&
                          (symbol_type <= Elf_Common::STT_HIOS) )
                    {
                        if (e_machine == Elf_Common::EM_PARISC)
                            {
                                if (symbol_type == Elf_hppa::STT_HP_OPAQUE)
                                    {
                                        output_str << "HP_OPAQUE";
                                    }
                                else if (symbol_type == Elf_hppa::STT_HP_STUB)
                                    {
                                        output_str << "HP_STUB";
                                    }
                            }
                        else {
                            output_str << "<OS specific>: " << symbol_type;
                        }
                    }
                else
                    {
                        output_str << boost::format("<unknown>:%1% ") %
                            boost::io::group( std::setfill('0'), std::hex,
                                              std::setw(4), symbol_type);
                    }
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Symbol_Utils::get_symbol_type" );
#endif /* LIBREVERSE_DEBUG */


        return output_str.str();
    }

    std::string
    Elf_Symbol_Utils::get_Symbol_Visibility ( boost::uint8_t st_other )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Elf_Symbol_Utils::get_symbol_visibility" );
#endif /* LIBREVERSE_DEBUG */


        std::stringstream output_str;

        boost::uint8_t visibility = (st_other & 0x3);

        switch (visibility)
            {
            case Elf_Common::STV_DEFAULT:   output_str << "DEFAULT"; break;
            case Elf_Common::STV_INTERNAL:  output_str << "INTERNAL"; break;
            case Elf_Common::STV_HIDDEN:    output_str << "HIDDEN"; break;
            case Elf_Common::STV_PROTECTED: output_str << "PROTECTED"; break;
            default:                        output_str << "UKNOWN"; break;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Elf_Symbol_Utils::get_symbol_visibility" );
#endif /* LIBREVERSE_DEBUG */


        return output_str.str();
    }

  } /* namespace elf_module */
} /* namespace libreverse */
