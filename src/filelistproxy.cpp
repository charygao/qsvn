/***************************************************************************
 *   This file is part of QSvn Project http://ar.oszine.de/projects/qsvn   *
 *   Copyright (c) 2004-2007 Andreas Richter <ar@oszine.de>                *
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
 ***************************************************************************/

//QSvn
#include "filelistproxy.h"

//SvnQt
#include "svnqt/client.hpp"
#include "svnqt/status.hpp"

//Qt
#include <QtCore>
#include <QSortFilterProxyModel>

FileListProxy::FileListProxy(QObject *parent)
        : QSortFilterProxyModel(parent)
{
    m_visibleStats << svn_wc_status_none;
    m_visibleStats << svn_wc_status_unversioned;
    m_visibleStats << svn_wc_status_normal;
    m_visibleStats << svn_wc_status_added;
    m_visibleStats << svn_wc_status_missing;
    m_visibleStats << svn_wc_status_deleted;
    m_visibleStats << svn_wc_status_replaced;
    m_visibleStats << svn_wc_status_modified;
    m_visibleStats << svn_wc_status_merged;
    m_visibleStats << svn_wc_status_conflicted;
    m_visibleStats << svn_wc_status_ignored;
    m_visibleStats << svn_wc_status_obstructed;
    m_visibleStats << svn_wc_status_external;
    m_visibleStats << svn_wc_status_incomplete;

    m_statusEntriesModel = new StatusEntriesModel(this, m_visibleStats);
    setSourceModel(m_statusEntriesModel);
}

FileListProxy::~FileListProxy()
{
    delete(m_statusEntriesModel);
}

void FileListProxy::readDirectory(QString directory, const bool descend, const bool force)
{
    return m_statusEntriesModel->readDirectory(directory, descend, force);
}

svn::Status FileListProxy::at(const QModelIndex &index)
{
    return m_statusEntriesModel->at(mapToSource(index).row());
}

bool FileListProxy::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    svn::Status status = m_statusEntriesModel->at(source_row);
    /*    if (!status.isVersioned())
            return false;*/

    if (QFileInfo(status.path()).isDir()) // don't show any directories in filelist
        return false;

    return true;
}
