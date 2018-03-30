/* Copyright © 2018 Fis Trivial <ybbs.daans@hotmail.com>

This file is part of arrayfire-scm.

arrayfire-scm is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

arrayfire-scm is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with arrayfire-scm.  If not, see <http://www.gnu.org/licenses/>.    */

#ifndef ARRAYFIRE_SCM_H
#define ARRAYFIRE_SCM_H

#include <libguile.h>
#include <arrayfire.h>

#ifdef __cplusplus
# define AS_API extern "C"
#else
# define AS_API extern
#endif

#define STR_LINE(x) # x
#define STR_LINE_(x) STR_LINE(x)
#define AFS_LINE_ STR_LINE_(__LINE__)

extern SCM afarray_type;
extern SCM af_error;

#define AFS_ASSERT(mesg, errno)						\
  if (errno != AF_SUCCESS)						\
    {									\
      SCM message;							\
      message = scm_from_utf8_string(mesg);				\
      SCM _errno = scm_from_int((int) errno);				\
      SCM data = scm_list_1(_errno);					\
      SCM subr = scm_from_utf8_string("file: " __FILE__ " line: " AFS_LINE_); \
      scm_error_scm(af_error, subr, message, SCM_BOOL_F, _errno);	\
    }


#endif	// arrayfire_scm_EXPORTS
