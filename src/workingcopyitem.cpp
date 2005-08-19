/***************************************************************************
 *   This file is part of QSvn Project http://qsvn.berlios.de              *
 *   Copyright (c) 2004-2005 Andreas Richter <ar@oszine.de>                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License Version 2        *
 *   as published by the Free Software Foundation.                         *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                         *
 *   As a special exception, permission is given to link this program      *
 *   with any edition of Qt, and distribute the resulting executable,      *
 *   without including the source code for Qt in the source distribution.  *
 ***************************************************************************/


//QSvn
#include "workingcopyitem.h"
#include "svnwrapper.h"

#ifdef Q_WS_X11
//SvnCpp
#include "svncpp/wc.hpp"
#endif

//Qt
#include <QList>
#include <QPixmap>
#include <QVariant>


WorkingCopyItem::WorkingCopyItem( const QList< QVariant > &data, WorkingCopyItem *parent )
{
    parentItem = parent;
    itemData = data;

#ifdef Q_WS_WIN    
    svnDirectory = SvnWrapper::Exemplar()->isWorkingCopy( itemData.value( 1 ).toString() );
#endif
#ifdef Q_WS_X11
    svnDirectory = svn::Wc::checkWc( itemData.value( 1 ).toString().toLocal8Bit() );
#endif
}

WorkingCopyItem::~WorkingCopyItem()
{
    deleteAllChilds();
}

void WorkingCopyItem::appendChild( WorkingCopyItem *child )
{
    childItems.append( child );
}

void WorkingCopyItem::deleteAllChilds()
{
    qDeleteAll( childItems );
}

WorkingCopyItem * WorkingCopyItem::child( int row )
{
    return childItems.value( row );
}

int WorkingCopyItem::childCount( ) const
{
    return childItems.count();
}

int WorkingCopyItem::columnCount( ) const
{
    return itemData.count();
}

QVariant WorkingCopyItem::data( int column ) const
{
    return itemData.value( column );
}

int WorkingCopyItem::row( ) const
{
    if ( parentItem )
        return parentItem->childItems.indexOf( const_cast<WorkingCopyItem*>( this ) );

    return 0;
}

WorkingCopyItem * WorkingCopyItem::parent( )
{
    return parentItem;
}

QPixmap WorkingCopyItem::getPixmap()
{
    if ( svnDirectory )
        return QPixmap( ":folder.png" );
    else
        return QPixmap( ":unknownfolder.png" );
}