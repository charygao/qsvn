/***************************************************************************
 *   This file is part of QSvn Project http://qsvn.berlios.de              *
 *   Copyright (c) 2004-2005 Andreas Richter <ar@oszine.de>                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
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

#ifndef WORKINGCOPY_H
#define WORKINGCOPY_H

//Qt
#include <qobject.h>

//QSvn classes
class AddWorkingCopy;
class Checkout;
class WorkingCopyItem;

//Qt classes
class QListView;
class QListViewItem;
class QString;


/**
This Class handles working copies
 
@author Andreas Richter
*/


class WorkingCopy : public QObject
{
    Q_OBJECT
public:
    static WorkingCopy* Exemplar();
    static void releaseExemplar();
    
    QWidget* getWidget();
    WorkingCopyItem* selectedWorkingCopyItem(); //!< give the selected WorkingCopyItem

    void updateElement( WorkingCopyItem *element );

signals:
    void directoryChanged( QString );

public slots:
    void addExistingWorkingCopySlot( QString directoyString );
    void addExistingWorkingCopySlot();
    void removeCurrentWorkingCopySlot();
    void updateCurrentWorkingCopySlot();
    void checkoutSlot();

private:
    WorkingCopy( QObject *parent = 0, const char *name = 0 );
    ~WorkingCopy();

    static WorkingCopy* _exemplar;

    AddWorkingCopy *addWorkingCopy;
    Checkout *checkout;
    QListView *listViewWorkingCopy;

    void removeWorkingCopy( WorkingCopyItem *element );

private slots:
    void changeElement();
};

#endif