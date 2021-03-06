/*
 *      Copyright (C) 2005-2008 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#ifndef XBPYTHREAD_H_
#define XBPYTHREAD_H_

#if (defined HAVE_CONFIG_H) && (!defined WIN32)
  #include "config.h"
#endif
#if (defined USE_EXTERNAL_PYTHON)
  #if (defined HAVE_LIBPYTHON2_6)
    #include <python2.6/Python.h>
  #elif (defined HAVE_LIBPYTHON2_5)
    #include <python2.5/Python.h>
  #elif (defined HAVE_LIBPYTHON2_4)
    #include <python2.4/Python.h>
  #else
    #error "Could not determine version of Python to use."
  #endif
#else
  #include "Python/Include/Python.h"
#endif
#include "utils/Thread.h"

class XBPython;

class XBPyThread : public CThread
{
public:
  XBPyThread(XBPython *pExecuter, int id);
  virtual ~XBPyThread();
  int evalFile(const CStdString &src);
  int evalString(const CStdString &src);
  int setArgv(const std::vector<CStdString> &argv);
  bool isStopping();
  void stop();

protected:
  XBPython      *m_pExecuter;
  PyThreadState *m_threadState;

  char m_type;
  char *m_source;
  char **m_argv;
  unsigned int  m_argc;
  bool m_stopping;
  int  m_id;

  virtual void OnStartup();
  virtual void Process();
  virtual void OnExit();
  virtual void OnException();
};

#endif // XBPYTHREAD_H_
