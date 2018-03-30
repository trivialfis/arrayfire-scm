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

extern SCM afarray_type;
extern SCM af_error;

#endif	// arrayfire_scm_EXPORTS
