/*  InternalData.cpp

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

//
// C++ Implementation: InternalData
//
// Description:
//
//
// Author: Stephen Torri <storri@torri.org>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "InternalData.h"

namespace parserGen
{
void InternalData::setCPU( boost::shared_ptr<CPU> cpu )
{
    if ( m_cpu != cpu )
    {
        m_cpu = cpu;
    }
}

void InternalData::addTable( boost::shared_ptr<Table> table )
{
    TableMap::iterator pos = m_tableMap.find( table->Name() );
    if ( pos == m_tableMap.end() )
    {
        m_tableMap.insert( std::make_pair( table->Name(), table ) );
    }
}

void InternalData::addToken ( boost::shared_ptr<Token> token )
{
    TokenMap::iterator pos = m_tokenMap.find( token->Name() );
    if ( pos == m_tokenMap.end() )
    {
        m_tokenMap.insert( std::make_pair( token->Name(), token ) );
    }
}

void InternalData::addRule ( boost::shared_ptr<Rule> rule )
{
    RuleMap::iterator pos = m_ruleMap.find( rule->Name() );
    if ( pos == m_ruleMap.end() )
    {
        m_ruleMap.insert( std::make_pair( rule->Name(), rule ) );
    }
}
}
