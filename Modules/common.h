/* common utility macros
 * See http://www.python-ldap.org/ for details.
 * $Id: common.h,v 1.8 2009/04/17 12:19:09 stroeder Exp $ */

#ifndef __h_common 
#define __h_common 

#define PY_SSIZE_T_CLEAN

#include "Python.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(MS_WINDOWS)
#include <winsock.h>
#else /* unix */
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#endif

/* Backwards compability with Python prior 2.5 */
#if PY_VERSION_HEX < 0x02050000
typedef int Py_ssize_t;
#define PY_SSIZE_T_MAX INT_MAX
#define PY_SSIZE_T_MIN INT_MIN
#endif

#if PY_MAJOR_VERSION >= 3
#define IS_PY3K

/* Provide Python3 int equivalents for PyInt* functions */
#define PyInt_FromLong(v) PyLong_FromLong(v)

/* Provide Python3 string equivalents for PyString* functions */
#define PyString_Check(s) (PyUnicode_Check(s) || PyBytes_Check(s))
inline char* __Py3CompatString_AsString(PyObject *string);
#define PyString_AsString(s) __Py3CompatString_AsString(s)
inline Py_ssize_t __Py3CompatString_Size(PyObject *string);
#define PyString_Size(s) __Py3CompatString_Size(s)
inline PyObject* __Py3CompatString_FromStringAndSize(const char *v, Py_ssize_t len);
#define PyString_FromStringAndSize(s, len) __Py3CompatString_FromStringAndSize(s, len)
#define PyString_FromString(s) PyString_FromStringAndSize(s, strlen(s))
#endif /* PY_MAJOR_VERSION */

#include <string.h>
#define streq( a, b ) \
	( (*(a)==*(b)) && 0==strcmp(a,b) )

void LDAPadd_methods( PyObject*d, PyMethodDef*methods );
#define PyNone_Check(o) ((o) == Py_None)

#endif /* __h_common_ */

