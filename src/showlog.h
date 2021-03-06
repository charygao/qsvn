/********************************************************************************
 *   This file is part of QSvn Project http://www.anrichter.net/projects/qsvn   *
 *   Copyright (c) 2004-2010 Andreas Richter <ar@anrichter.net>                 *
 *                                                                              *
 *   This program is free software; you can redistribute it and/or modify       *
 *   it under the terms of the GNU General Public License Version 2             *
 *   as published by the Free Software Foundation.                              *
 *                                                                              *
 *   This program is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 *   GNU General Public License for more details.                               *
 *                                                                              *
 *   You should have received a copy of the GNU General Public License          *
 *   along with this program; if not, write to the                              *
 *   Free Software Foundation, Inc.,                                            *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                  *
 *                                                                              *
 *******************************************************************************/

#ifndef SHOWLOG_H
#define SHOWLOG_H

//QSvn
#include "ui_showlog.h"

class LogEntriesModel;

class LogChangePathEntriesModel;

//SvnQt
#include "svnqt/client.hpp"

//Qt
#include <QDialog>

class QSortFilterProxyModel;


class ShowLog : public QDialog, public Ui::ShowLog
{
        Q_OBJECT

    public:
        static void doShowLog(QWidget *parent, const QString path,
                              const svn::Revision revisionStart,
                              const svn::Revision revisionEnd);

    protected:
        bool eventFilter(QObject *watched, QEvent *event);

    private:
        svn::LogEntries *m_logEntries;
        LogEntriesModel *m_logEntriesModel;
        LogChangePathEntriesModel *m_logChangePathEntriesModel;

        QSortFilterProxyModel *m_logEntriesProxy,
        *m_logChangePathEntriesProxy;

        QMenu *menuPathEntries, *menuLogEntries;
        QString m_path, m_url, m_repos, m_repos_path;
        svn::Revision m_revisionStart, m_revisionEnd, m_revisionBeginShowLog;

        ShowLog(QWidget *parent = 0, const QString path = 0,
                const svn::Revision revisionStart = svn::Revision::UNDEFINED,
                const svn::Revision revisionEnd = svn::Revision::UNDEFINED);
        ~ShowLog();
        void initLogEntries();
        void initLogEntriesPath();
        void initMenus();

        svn::Revision getSelectedRevision();
        QString getSelectedPath();
        bool checkLocatedInWc();
        svn_revnum_t getSelectedStartRevision();
        void revertChanges(const QString url, const QString path, const svn::Revision revision);

    private slots:
        void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
        void buttonNextClicked(int limit);

        void on_checkBoxStrictNodeHistory_stateChanged();
        void on_buttonNext_clicked();
        void on_buttonShowAll_clicked();
        void on_comboBoxFilterKeyColumn_currentIndexChanged(int index);

        void on_actionDiff_triggered();
        void on_actionDiff_to_WORKING_triggered();
        void on_actionDiff_to_HEAD_triggered();
        void on_actionDiff_to_BASE_triggered();
        void on_actionDiff_to_START_triggered();
        void on_actionDiff_to_Revision_triggered();

        void on_actionMerge_triggered();
        void on_actionEditLogMessage_triggered();
        void on_actionEditAuthor_triggered();

        void on_actionRevertChangeset_triggered();
        void on_actionRevertPath_triggered();
};

#endif
