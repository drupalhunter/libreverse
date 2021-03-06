/*  CPU_SubType.cpp

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

#include "CPU_SubType.h"
#include "Trace.h"
#include "Reverse.h"
#include "CPU_Type.h"
#include "errors/Internal_Exception.h"
#include <boost/format.hpp>

using namespace reverse::api;
using namespace reverse::trace;

namespace reverse
{
    namespace mach_module
    {
                std::string
                CPU_SubType::get_VAX_String_Name ( boost::uint32_t cpu_subtype )
                {
                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Entering CPU_SubType::get_VAX_String_Name" );

                    std::string name = "";

                    switch ( cpu_subtype )
                    {
                        case CPU_SUBTYPE_VAX_ALL:
                            name = "All";
                            break;
                        case CPU_SUBTYPE_VAX780:
                            name = "VAX 780";
                            break;
                        case CPU_SUBTYPE_VAX785:
                            name = "VAX 785";
                            break;
                        case CPU_SUBTYPE_VAX750:
                            name = "VAX 750";
                            break;
                        case CPU_SUBTYPE_VAX730:
                            name = "VAX 730";
                            break;
                        case CPU_SUBTYPE_UVAXI:
                            name = "UVAX I";
                            break;
                        case CPU_SUBTYPE_UVAXII:
                            name = "UVAX II";
                            break;
                        case CPU_SUBTYPE_VAX8200:
                            name = "VAX 8200";
                            break;
                        case CPU_SUBTYPE_VAX8500:
                            name = "VAX 8500";
                            break;
                        case CPU_SUBTYPE_VAX8600:
                            name = "VAX 8600";
                            break;
                        case CPU_SUBTYPE_VAX8650:
                            name = "VAX 8650";
                            break;
                        case CPU_SUBTYPE_VAX8800:
                            name = "VAX 8800";
                            break;
                        case CPU_SUBTYPE_UVAXIII:
                            name = "UVAX II";
                            break;
                        default:
                        {
                            Trace::write_Trace ( TraceArea::IO,
                                                 TraceLevel::DATA,
                                                 boost::str ( boost::format ( "Invalid Index = %1%" ) % cpu_subtype ) );

                            throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_VALUE );
                        }
                    }

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DATA,
                                         boost::str ( boost::format ( "Name = %1%" ) % name ) );

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Exiting CPU_SubType::get_VAX_String_Name" );

                    return name;
                }

                std::string
                CPU_SubType::get_MIPS_String_Name ( boost::uint32_t cpu_subtype )
                {
                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Entering CPU_SubType::get_MIPS_String_Name" );

                    std::string name = "";

                    switch ( cpu_subtype )
                    {
                        case CPU_SUBTYPE_MIPS_ALL:
                            name = "All";
                            break;
                        case CPU_SUBTYPE_MIPS_R2300:
                            name = "R2300";
                            break;
                        case CPU_SUBTYPE_MIPS_R2600:
                            name = "R2600";
                            break;
                        case CPU_SUBTYPE_MIPS_R2800:
                            name = "R2800";
                            break;
                        case CPU_SUBTYPE_MIPS_R2000a:
                            name = "R2000a";
                            break;
                        case CPU_SUBTYPE_MIPS_R2000:
                            name = "R2000";
                            break;
                        case CPU_SUBTYPE_MIPS_R3000a:
                            name = "R3000a";
                            break;
                        case CPU_SUBTYPE_MIPS_R3000:
                            name = "R3000";
                            break;
                        default:
                        {
                            Trace::write_Trace ( TraceArea::IO,
                                                 TraceLevel::DATA,
                                                 boost::str ( boost::format ( "Invalid Index = %1%" ) % cpu_subtype ) );

                            throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_VALUE );
                        }
                    }

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DATA,
                                         boost::str ( boost::format ( "Name = %1%" ) % name ) );

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Exiting CPU_SubType::get_MIPS_String_Name" );

                    return name;
                }

                std::string
                CPU_SubType::get_Intel_String_Name ( boost::uint32_t cpu_subtype )
                {
                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Entering CPU_SubType::get_Intel_String_Name" );

                    std::string name = "";

                    switch ( cpu_subtype )
                    {
                        case CPU_SUBTYPE_386:
                            name = "386";
                            break;
                        case CPU_SUBTYPE_486:
                            name = "486";
                            break;
                        case CPU_SUBTYPE_486SX:
                            name = "486SX";
                            break;
                        case CPU_SUBTYPE_586:
                            name = "586";
                            break;
                        case CPU_SUBTYPE_PENTPRO:
                            name = "Pentium Pro";
                            break;
                        case CPU_SUBTYPE_PENTII_M3:
                            name = "Pentium II (M3)";
                            break;
                        case CPU_SUBTYPE_PENTII_M5:
                            name = "Pentium II (M5)";
                            break;
                        case CPU_SUBTYPE_CELERON:
                            name = "Celeron";
                            break;
                        case CPU_SUBTYPE_CELERON_MOBILE:
                            name = "Celeron (Mobile)";
                            break;
                        case CPU_SUBTYPE_PENTIUM_3:
                            name = "Pentium III";
                            break;
                        case CPU_SUBTYPE_PENTIUM_3_M:
                            name = "Pentium III (M)";
                            break;
                        case CPU_SUBTYPE_PENTIUM_3_XEON:
                            name = "Pentium III (Xeon)";
                            break;
                        case CPU_SUBTYPE_PENTIUM_M:
                            name = "Pentium M";
                            break;
                        case CPU_SUBTYPE_PENTIUM_4:
                            name = "Pentium 4";
                            break;
                        case CPU_SUBTYPE_PENTIUM_4_M:
                            name = "Pentium 4M";
                            break;
                        case CPU_SUBTYPE_ITANIUM:
                            name = "Itanium";
                            break;
                        case CPU_SUBTYPE_ITANIUM_2:
                            name = "Itanum II";
                            break;
                        case CPU_SUBTYPE_XEON:
                            name = "386";
                            break;
                        case CPU_SUBTYPE_XEON_MP:
                            name = "Xeon MP";
                            break;
                        default:
                        {
                            Trace::write_Trace ( TraceArea::IO,
                                                 TraceLevel::DATA,
                                                 boost::str ( boost::format ( "Invalid Index = %1%" ) % cpu_subtype ) );

                            throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_VALUE );
                        }
                    }

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DATA,
                                         boost::str ( boost::format ( "Name = %1%" ) % name ) );

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Exiting CPU_SubType::get_Intel_String_Name" );

                    return name;
                }

                std::string
                CPU_SubType::get_MC680x0_String_Name ( boost::uint32_t cpu_subtype )
                {
                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Entering CPU_SubType::get_MC680x0_String_Name" );

                    std::string name = "";

                    switch ( cpu_subtype )
                    {
                        case CPU_SUBTYPE_MC68030:
                            name = "MC68030";
                            break;
                        case CPU_SUBTYPE_MC68040:
                            name = "MC68040";
                            break;
                        case CPU_SUBTYPE_MC68030_ONLY:
                            name = "MC68030 (Only)";
                            break;
                        default:
                        {
                            Trace::write_Trace ( TraceArea::IO,
                                                 TraceLevel::DATA,
                                                 boost::str ( boost::format ( "Invalid Index = %1%" ) % cpu_subtype ) );

                            throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_VALUE );
                        }
                    }

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DATA,
                                         boost::str ( boost::format ( "Name = %1%" ) % name ) );

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Exiting CPU_SubType::get_MC680x0_String_Name" );

                    return name;
                }

                std::string
                CPU_SubType::get_MC98000_String_Name ( boost::uint32_t cpu_subtype )
                {
                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Entering CPU_SubType::get_MC98000_String_Name" );

                    std::string name = "";

                    switch ( cpu_subtype )
                    {
                        case CPU_SUBTYPE_MC98000_ALL:
                            name = "All";
                            break;
                        case CPU_SUBTYPE_MC98601:
                            name = "MC98601";
                            break;
                        default:
                        {
                            Trace::write_Trace ( TraceArea::IO,
                                                 TraceLevel::DATA,
                                                 boost::str ( boost::format ( "Invalid Index = %1%" ) % cpu_subtype ) );

                            throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_VALUE );
                        }
                    }

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DATA,
                                         boost::str ( boost::format ( "Name = %1%" ) % name ) );

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Exiting CPU_SubType::get_MC98000_String_Name" );

                    return name;
                }

                std::string
                CPU_SubType::get_HPPA_String_Name ( boost::uint32_t cpu_subtype )
                {
                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Entering CPU_SubType::get_HPPA_String_Name" );

                    std::string name = "";

                    switch ( cpu_subtype )
                    {
                        case CPU_SUBTYPE_HPPA_7100:
                            name = "7100";
                            break;
                        case CPU_SUBTYPE_HPPA_7100LC:
                            name = "7100LC";
                            break;
                        default:
                        {
                            Trace::write_Trace ( TraceArea::IO,
                                                 TraceLevel::DATA,
                                                 boost::str ( boost::format ( "Invalid Index = %1%" ) % cpu_subtype ) );

                            throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_VALUE );
                        }
                    }

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DATA,
                                         boost::str ( boost::format ( "Name = %1%" ) % name ) );

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Exiting CPU_SubType::get_HPPA_String_Name" );

                    return name;
                }

                std::string
                CPU_SubType::get_MC88000_String_Name ( boost::uint32_t cpu_subtype )
                {
                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Entering CPU_SubType::get_MC88000_String_Name" );

                    std::string name = "";

                    switch ( cpu_subtype )
                    {
                        case CPU_SUBTYPE_MC88000_ALL:
                            name = "All";
                            break;
                        case CPU_SUBTYPE_MC88100:
                            name = "MC88100";
                            break;
                        case CPU_SUBTYPE_MC88110:
                            name = "MC88110";
                            break;
                        default:
                        {
                            Trace::write_Trace ( TraceArea::IO,
                                                 TraceLevel::DATA,
                                                 boost::str ( boost::format ( "Invalid Index = %1%" ) % cpu_subtype ) );

                            throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_VALUE );
                        }
                    }

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DATA,
                                         boost::str ( boost::format ( "Name = %1%" ) % name ) );

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Exiting CPU_SubType::get_MC88000_String_Name" );

                    return name;
                }

                std::string
                CPU_SubType::get_I860_String_Name ( boost::uint32_t cpu_subtype )
                {
                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Entering CPU_SubType::get_I860_String_Name" );

                    std::string name = "";

                    switch ( cpu_subtype )
                    {
                        case CPU_SUBTYPE_I860_ALL:
                            name = "All";
                            break;
                        case CPU_SUBTYPE_I860_860:
                            name = "860";
                            break;
                        default:
                        {
                            Trace::write_Trace ( TraceArea::IO,
                                                 TraceLevel::DATA,
                                                 boost::str ( boost::format ( "Invalid Index = %1%" ) % cpu_subtype ) );

                            throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_VALUE );
                        }
                    }

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DATA,
                                         boost::str ( boost::format ( "Name = %1%" ) % name ) );

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Exiting CPU_SubType::get_I860_String_Name" );

                    return name;
                }

                std::string
                CPU_SubType::get_PowerPC_String_Name ( boost::uint32_t cpu_subtype )
                {
                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Entering CPU_SubType::get_PowerPC_String_Name" );

                    std::string name = "";

                    switch ( cpu_subtype )
                    {
                        case CPU_SUBTYPE_POWERPC_ALL:
                            name = "All";
                            break;
                        case CPU_SUBTYPE_POWERPC_601:
                            name = "601";
                            break;
                        case CPU_SUBTYPE_POWERPC_602:
                            name = "602";
                            break;
                        case CPU_SUBTYPE_POWERPC_603:
                            name = "603";
                            break;
                        case CPU_SUBTYPE_POWERPC_603e:
                            name = "603e";
                            break;
                        case CPU_SUBTYPE_POWERPC_603ev:
                            name = "603ev";
                            break;
                        case CPU_SUBTYPE_POWERPC_604:
                            name = "604";
                            break;
                        case CPU_SUBTYPE_POWERPC_604e:
                            name = "604e";
                            break;
                        case CPU_SUBTYPE_POWERPC_620:
                            name = "620";
                            break;
                        case CPU_SUBTYPE_POWERPC_750:
                            name = "750";
                            break;
                        case CPU_SUBTYPE_POWERPC_7400:
                            name = "7400";
                            break;
                        case CPU_SUBTYPE_POWERPC_7450:
                            name = "7450";
                            break;
                        case CPU_SUBTYPE_POWERPC_970:
                            name = "970";
                            break;
                        default:
                        {
                            Trace::write_Trace ( TraceArea::IO,
                                                 TraceLevel::DATA,
                                                 boost::str ( boost::format ( "Invalid Index = %1%" ) % cpu_subtype ) );

                            throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_VALUE );
                        }
                    }

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DATA,
                                         boost::str ( boost::format ( "Name = %1%" ) % name ) );

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Exiting CPU_SubType::get_PowerPC_String_Name" );

                    return name;
                }

                std::string
                CPU_SubType::get_String_Name ( boost::uint32_t cputype, boost::uint32_t cpu_subtype )
                {
                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Entering CPU_SubType::get_String_Name" );

                    std::string name = "";

                    switch ( cputype )
                    {
                        case CPU_Type::CPU_TYPE_VAX:
                            name = get_VAX_String_Name ( cpu_subtype );
                            break;
                        case CPU_Type::CPU_TYPE_MC680x0:
                            name = get_MC680x0_String_Name ( cpu_subtype );
                            break;
                        case CPU_Type::CPU_TYPE_X86:
                        case CPU_Type::CPU_TYPE_X86_64:
                            name = get_Intel_String_Name ( cpu_subtype );
                            break;
                        case CPU_Type::CPU_TYPE_MIPS:
                            name = get_MIPS_String_Name ( cpu_subtype );
                            break;
                        case CPU_Type::CPU_TYPE_MC98000:
                            name = get_MC98000_String_Name ( cpu_subtype );
                            break;
                        case CPU_Type::CPU_TYPE_HPPA:
                            name = get_HPPA_String_Name ( cpu_subtype );
                            break;
                        case CPU_Type::CPU_TYPE_MC88000:
                            name = get_MC88000_String_Name ( cpu_subtype );
                            break;
                        case CPU_Type::CPU_TYPE_SPARC:
                            name = "All";
                            break;
                        case CPU_Type::CPU_TYPE_I860:
                            name = get_I860_String_Name ( cpu_subtype );
                            break;
                        case CPU_Type::CPU_TYPE_POWERPC:
                        case CPU_Type::CPU_TYPE_POWERPC64:
                            name = get_PowerPC_String_Name ( cpu_subtype );
                            break;
                            /* No sub types defined for these CPU types */
                        case CPU_Type::CPU_TYPE_ALPHA:
                        case CPU_Type::CPU_TYPE_ARM:
                            name= "(No subtype)";
                            break;
                        default:
                        {
                            Trace::write_Trace ( TraceArea::IO,
                                                 TraceLevel::DATA,
                                                 boost::str ( boost::format ( "Invalid Index = %1$08X ( %2$d )" ) % cputype % cputype ) );

                            throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_VALUE );
                        }
                    }

                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DETAIL,
                                         "Exiting CPU_SubType::get_String_Name" );

                    return name;
                }

    } /* namespace mach_module */
} /* namespace reverse */
