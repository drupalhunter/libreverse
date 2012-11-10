
#!/bin/bash

license_prefix="/* "

license_body="
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
"

# Find files
#files=`find -name '*.cpp'`
#files=`find -name '*.cpp'`
files=`find -name '*.cpp'`

# For all files
for f in $files; do
    # Copy original to a new name
    echo "mv $f $f"_tmp""
    mv $f $f"_tmp"

    filename=`echo "$f" | sed -e 's/\.\/\([a-zA-Z_]\+\/\)*//'`

    echo "$license_prefix $filename" > $f
    echo "$license_body" >> $f
    cat $f"_tmp" >> $f
done