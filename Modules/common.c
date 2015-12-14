/* Miscellaneous common routines
 * See http://www.python-ldap.org/ for details.
 * $Id: common.c,v 1.3 2009/04/17 12:19:09 stroeder Exp $ */

#include "common.h"

/* dynamically add the methods into the module dictionary d */

void
LDAPadd_methods( PyObject* d, PyMethodDef* methods ) 
{
    PyMethodDef *meth;

    for( meth = methods; meth->ml_meth; meth++ ) {
        PyObject *f = PyCFunction_New( meth, NULL );
        PyDict_SetItemString( d, meth->ml_name, f );
        Py_DECREF(f);
    }
}

#ifdef IS_PY3K
inline char* __Py3CompatString_AsString(PyObject *string)
{
    /*
     * Return string object as a character array. If it's a unicode object,
     * encode it as an UTF8 character array.
     */
    if PyUnicode_Check(string)
        return PyBytes_AsString(PyUnicode_AsUTF8String(string));
    return PyBytes_AsString(string);
}

inline Py_ssize_t __Py3CompatString_Size(PyObject *string)
{
    /*
     * Return size of string object. If it's a unicode object, return the
     * size of the encoded UTF8 character array.
     */
    if PyUnicode_Check(string)
        return PyBytes_Size(PyUnicode_AsUTF8String(string));
    return PyBytes_Size(string);
}

inline PyObject* __Py3CompatString_FromStringAndSize(const char *v, Py_ssize_t len)
{
    /*
     * Create and return an UTF8 object from the supplied character array.
     * If that fails, create and return a bytes object instead.
     */
    PyObject* retval = PyUnicode_DecodeUTF8(v, len, NULL);
    if (!retval)
        return PyBytes_FromStringAndSize(v, len);
    return retval;
}
#endif /* IS_PY3K */
