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

#ifndef LISTENER_H
#define LISTENER_H

//svnqt
#include "svnqt/context_listener.hpp"

//Qt
#include <QObject>


class Listener : public QObject, public svn::ContextListener
{
        Q_OBJECT

    public:
        Listener(QObject *parent = 0);
        virtual ~Listener();

        virtual bool contextGetLogin(const QString & realm,
                                     QString & username,
                                     QString & password,
                                     bool & maySave);
        virtual void contextNotify(const char *path,
                                   svn_wc_notify_action_t action,
                                   svn_node_kind_t kind,
                                   const char *mime_type,
                                   svn_wc_notify_state_t content_state,
                                   svn_wc_notify_state_t prop_state,
                                   svn_revnum_t revision);
        virtual void contextNotify(const svn_wc_notify_t *action);

        virtual bool contextCancel();
        virtual bool contextGetLogMessage(QString &msg, const svn::CommitItemList&);
        virtual SslServerTrustAnswer contextSslServerTrustPrompt(const SslServerTrustData &data,
                apr_uint32_t &acceptedFailures);
        virtual bool contextSslClientCertPrompt(QString &certFile);
        virtual bool contextSslClientCertPwPrompt(QString &password,
                const QString &realm,
                bool &maySave);
        virtual bool contextLoadSslClientCertPw(QString&, const QString&)
        {
            return true;
        }

        virtual bool contextGetSavedLogin(const QString&, QString&, QString&)
        {
            return true;
        }

        virtual bool contextGetCachedLogin(const QString & realm, QString & username, QString & password)
        {
            return true;
        }

        virtual void contextProgress(long long int current, long long int max);

        void setCancel(bool cancel);
        void setVerbose(bool verbose);

    private:
        bool m_cancel, m_verbose;
};

#endif
