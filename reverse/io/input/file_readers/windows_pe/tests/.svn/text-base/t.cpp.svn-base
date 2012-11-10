/*  t.cpp

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

#include <vector>
#include <iostream>
#include <boost/cstdint.hpp>
#include <boost/format.hpp>
#include <unicode/ucnv.h>

int main (int, char**)
{
    std::vector<boost::uint8_t> data;
    data.push_back(0x48);
    data.push_back(0x00);
    data.push_back(0x65);
    data.push_back(0x00);
    data.push_back(0x6C);
    data.push_back(0x00);
    data.push_back(0x6C);
    data.push_back(0x00);
    data.push_back(0x6F);
    data.push_back(0x00);

    UErrorCode error ( U_ZERO_ERROR );
    UConverter* conv = ucnv_open(NULL, &error);

    std::vector<char> dest_string ( data.size() );
    boost::int32_t len = ucnv_fromUChars ( conv,
                                           &(*(dest_string.begin())),
                                           data.size(),
                                           reinterpret_cast<const UChar*>(&(*(data.begin()))),
                                           data.size(),
                                           &error );

    if ( U_FAILURE ( error ) )
        {
            std::cout <<
                boost::format("Unknown error code: %1X (%2s)")
                % error % u_errorName (error) << std::endl;
        }
    else
        {
            std::string result ( &(*dest_string.begin() ) );
            std::cout << "Resulting string is " << result << std::endl;
        }

	return 0;
}
