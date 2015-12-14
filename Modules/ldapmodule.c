/* See http://www.python-ldap.org/ for details.
 * $Id: ldapmodule.c,v 1.9 2009/04/17 12:19:09 stroeder Exp $ */

#include "common.h"
#include "version.h"
#include "constants.h"
#include "errors.h"
#include "functions.h"
#include "schema.h"
#include "ldapcontrol.h"

#include "LDAPObject.h"

#define LDAP_NAME "_ldap"

#ifdef IS_PY3K
static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    LDAP_NAME,           /* m_name */
    NULL,                /* m_doc */
    -1,                  /* m_size */
    NULL,                /* m_methods */
    NULL,                /* m_reload */
    NULL,                /* m_traverse */
    NULL,                /* m_clear */
    NULL,                /* m_free */
};
#define init_ldap PyInit__ldap
#define PYMOD_INIT_RETURN(m) return m
#else
#ifndef PyMODINIT_FUNC
#define PyMODINIT_FUNC DL_EXPORT(void)
#endif
#define PYMOD_INIT_RETURN(m) return
#endif

/* module initialisation */

PyMODINIT_FUNC
init_ldap(void)
{
	PyObject *m, *d;

    m = NULL;
    d = NULL;

    if (PyType_Ready(&LDAP_Type) < 0)
        PYMOD_INIT_RETURN(m);

    /* Create the module and add the functions */
#ifdef IS_PY3K
    m = PyModule_Create(&moduledef);
#else
    m = Py_InitModule(LDAP_NAME, NULL);
#endif

	/* Add some symbolic constants to the module */
	d = PyModule_GetDict(m);

	LDAPinit_version(d);
	LDAPinit_constants(d);
	LDAPinit_errors(d);
	LDAPinit_functions(d);
	LDAPinit_schema(d);
	LDAPinit_control(d);

	/* Check for errors */
	if (PyErr_Occurred()) {
		Py_FatalError("can't initialize module _ldap");
        PYMOD_INIT_RETURN(m);
    }
    PYMOD_INIT_RETURN(m);
}
