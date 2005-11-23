/*
 * ====================================================================
 * Copyright (c) 2002-2005 The RapidSvn Group.  All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library (in the file LGPL.txt); if not,
 * write to the Free Software Foundation, Inc., 51 Franklin St,
 * Fifth Floor, Boston, MA  02110-1301  USA
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 */
#if defined( _MSC_VER) && _MSC_VER <= 1200
#pragma warning( disable: 4786 )// debug symbol truncated
#endif

// subversion api
#include "svn_client.h"

// svncpp
#include "client.hpp"
#include "exception.hpp"
#include "pool.hpp"
#include "targets.hpp"

namespace svn
{
  svn_revnum_t
  Client::checkout (const QString& url,
                    const Path & destPath,
                    const Revision & revision,
                    bool recurse) throw (ClientException)
  {
    Pool subPool;
    apr_pool_t * apr_pool = subPool.pool ();

    svn_revnum_t revnum = 0;
    svn_error_t * error =
      svn_client_checkout (&revnum,
#if QT_VERSION < 0x040000
                           url.utf8(),
#else
                           url.toUtf8(),
#endif
                           destPath.cstr(),
                           revision.revision (),
                           recurse,
                           *m_context,
                           apr_pool);

    if(error != NULL)
      throw ClientException (error);
    return revnum;
  }

  void
  Client::remove (const Path & path,
                  bool force) throw (ClientException)
  {
    Pool pool;
    Targets targets (path.path());
    svn_client_commit_info_t *commit_info = NULL;

    svn_error_t * error =
      svn_client_delete (&commit_info,
                         const_cast<apr_array_header_t*> (targets.array (pool)),
                         force,
                         *m_context,
                         pool);
    if(error != NULL)
      throw ClientException (error);
  }

  void
  Client::remove (const Targets & targets,
                  bool force) throw (ClientException)
  {
    Pool pool;
    svn_client_commit_info_t *commit_info = NULL;

    svn_error_t * error =
      svn_client_delete (&commit_info,
                         const_cast<apr_array_header_t*> (targets.array (pool)),
                         force,
                         *m_context,
                         pool);
    if(error != NULL)
      throw ClientException (error);
  }

  void
  Client::revert (const Targets & targets,
                  bool recurse) throw (ClientException)
  {
    Pool pool;

    svn_error_t * error =
      svn_client_revert ((targets.array (pool)),
                         recurse,
                         *m_context,
                         pool);

    if(error != NULL)
      throw ClientException (error);
  }

  void
  Client::add (const Path & path,
               bool recurse) throw (ClientException)
  {
    Pool pool;

    svn_error_t * error =
      svn_client_add (path.cstr (),
                      recurse,
                      *m_context,
                      pool);

    if(error != NULL)
      throw ClientException (error);
  }

  Revisions
  Client::update (const Targets & path,
                  const Revision & revision,
                  bool recurse,
                  bool ignore_externals) throw (ClientException)
  {
    Pool pool;
    Revisions resulting;
    svn_error_t * error;

    apr_pool_t *apr_pool = pool.pool();
    apr_array_header_t *apr_revisions = apr_array_make (apr_pool,
                      path.size(),
                      sizeof (svn_revnum_t));
    error = svn_client_update2(&apr_revisions,path.array(pool),revision.revision(),recurse,ignore_externals,*m_context,pool);
    if (error!=NULL) {
        throw ClientException(error);
    }
    for (int i = 0; i < apr_revisions->nelts; ++i)
    {
      svn_revnum_t * _rev =
        &APR_ARRAY_IDX (apr_revisions, i, svn_revnum_t);

      resulting.push_back((*_rev));
    }
    return resulting;
  }

  svn_revnum_t Client::update_old(const Path&path,const Revision&revision,bool recurse)throw (ClientException)
  {
    Pool pool;
    svn_revnum_t revnum = 0;
    svn_error_t * error =
      svn_client_update (&revnum,
                         path.cstr (),
                         revision.revision (),
                         recurse,
                         *m_context,
                         pool);
    if(error != NULL)
      throw ClientException (error);
    return revnum;
  }

  svn_revnum_t
  Client::commit (const Targets & targets, const QString& message,
                  bool recurse) throw (ClientException)
  {
    Pool pool;

    m_context->setLogMessage (message);

    svn_client_commit_info_t *commit_info = NULL;
    svn_error_t * error =
      svn_client_commit (&commit_info,
                         targets.array (pool),
                         !recurse,
                         *m_context,
                         pool);
    if (error != NULL)
      throw ClientException (error);

    if (commit_info && SVN_IS_VALID_REVNUM (commit_info->revision))
      return commit_info->revision;

    return -1;
  }

  void
  Client::copy (const Path & srcPath,
                const Revision & srcRevision,
                const Path & destPath) throw (ClientException)
  {
    Pool pool;
    svn_client_commit_info_t *commit_info = NULL;
    svn_error_t * error =
      svn_client_copy (&commit_info,
                       srcPath.cstr (),
                       srcRevision.revision (),
                       destPath.cstr (),
                       *m_context,
                       pool);

    if(error != NULL)
      throw ClientException (error);
  }

  void
  Client::move (const Path & srcPath,
                const Revision & srcRevision,
                const Path & destPath,
                bool force) throw (ClientException)
  {
    Pool pool;
    svn_client_commit_info_t *commit_info = NULL;
    svn_error_t * error =
      svn_client_move (&commit_info,
                       srcPath.cstr (),
                       srcRevision.revision (),
                       destPath.cstr (),
                       force,
                       *m_context,
                       pool);

    if(error != NULL)
      throw ClientException (error);
  }

  void
  Client::mkdir (const Path & path,
                 const QString& message) throw (ClientException)
  {
    Pool pool;
    m_context->setLogMessage (message);

    Targets targets(path.path());

    svn_client_commit_info_t *commit_info = NULL;
    svn_error_t * error =
      svn_client_mkdir (&commit_info,
                        const_cast<apr_array_header_t*>
                        (targets.array (pool)),
                        *m_context, pool);

    if(error != NULL)
      throw ClientException (error);
  }

  void
  Client::mkdir (const Targets & targets,
                 const QString& message) throw (ClientException)
  {
    Pool pool;
    m_context->setLogMessage (message);

    svn_client_commit_info_t *commit_info = NULL;
    svn_error_t * error =
      svn_client_mkdir (&commit_info,
                        const_cast<apr_array_header_t*>
                        (targets.array (pool)),
                        *m_context, pool);

    if(error != NULL)
      throw ClientException (error);
  }

  void
  Client::cleanup (const Path & path) throw (ClientException)
  {
    Pool subPool;
    apr_pool_t * apr_pool = subPool.pool ();

    svn_error_t * error =
      svn_client_cleanup (path.cstr (), *m_context, apr_pool);

    if(error != NULL)
      throw ClientException (error);
  }

  void
  Client::resolved (const Path & path,
                    bool recurse) throw (ClientException)
  {
    Pool pool;
    svn_error_t * error =
      svn_client_resolved (path.cstr (),
                           recurse,
                           *m_context,
                           pool);

    if(error != NULL)
      throw ClientException (error);
  }

  svn_revnum_t
  Client::doExport (const Path & srcPath,
                    const Path & destPath,
                    const Revision & revision,
                    bool force) throw (ClientException)
  {
    Pool pool;
    svn_revnum_t revnum = 0;
    svn_error_t * error =
      svn_client_export(&revnum,
                        srcPath.cstr(),
                        destPath.cstr(),
                         const_cast<svn_opt_revision_t*>
                         (revision.revision ()),
                         force,
                         *m_context,
                         pool);

    if(error != NULL)
      throw ClientException (error);
    return revnum;
  }

  svn_revnum_t
  Client::doSwitch (const Path & path,
                    const QString& url,
                    const Revision & revision,
                    bool recurse) throw (ClientException)
  {
    Pool pool;
    svn_revnum_t revnum = 0;
    svn_error_t * error =
      svn_client_switch (&revnum,
                         path.cstr(),
#if QT_VERSION < 0x040000
                         url.utf8(),
#else
                         url.toUtf8(),
#endif
                         revision.revision (),
                         recurse,
                         *m_context,
                         pool);

    if(error != NULL)
      throw ClientException (error);
    return revnum;
  }

  void
  Client::import (const Path & path,
                  const QString& url,
                  const QString& message,
                  bool recurse) throw (ClientException)
  {
    Pool pool;
    svn_client_commit_info_t *commit_info = NULL;

    m_context->setLogMessage (message);

    svn_error_t * error =
      svn_client_import (&commit_info,
                         path.cstr (),
#if QT_VERSION < 0x040000
                         url.utf8(),
#else
                         url.toUtf8(),
#endif
                         !recurse,
                         *m_context,
                         pool);

    if(error != NULL)
      throw ClientException (error);
  }

  void
  Client::merge (const Path & path1, const Revision & revision1,
                 const Path & path2, const Revision & revision2,
                 const Path & localPath, bool force,
                 bool recurse,
                 bool notice_ancestry,
                 bool dry_run) throw (ClientException)
  {
    Pool pool;
    svn_error_t * error =
      svn_client_merge (path1.cstr (),
                        revision1.revision (),
                        path2.cstr (),
                        revision2.revision (),
                        localPath.cstr (),
                        recurse,
                        !notice_ancestry,
                        force,
                        dry_run,
                        *m_context,
                        pool);

    if(error != NULL)
      throw ClientException (error);
  }

  void
  Client::relocate (const Path & path,
                    const QString& from_url,
                    const QString& to_url,
                    bool recurse) throw (ClientException)
  {
    Pool pool;
    svn_error_t * error =
      svn_client_relocate (path.cstr (),
#if QT_VERSION < 0x040000
                         from_url.utf8(),
                         to_url.utf8(),
#else
                         from_url.toUtf8(),
                         to_url.toUtf8(),
#endif
                         recurse,
                         *m_context,
                         pool);

    if(error != NULL)
      throw ClientException (error);
  }

}

/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../../rapidsvn-dev.el")
 * end:
 */
