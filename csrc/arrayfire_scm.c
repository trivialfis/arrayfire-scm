/* Initialize arrayfire-scm.
   Copyright © 2018 Fis Trivial <ybbs.daans@hotmail.com>

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

#include "arrayfire_scm.h"
#include "construction.h"
#include "linear_algebra.h"
#include "mathematic.h"
#include "index.h"
#include "io.h"
#include "array.h"
#include "statistics.h"

SCM afarray_type;
SCM af_error;

static void finalize_afarray(SCM array)
{
  fprintf(stderr, "finalize array.\n");
  af_array ar = (af_array)scm_foreign_object_unsigned_ref(array, 0);
  if (ar != NULL)
    scm_foreign_object_unsigned_set_x(array, 0, -1);
  af_release_array(ar);
}

void init_afarray_type(void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer;

  name = scm_from_utf8_symbol("afarray");
  slots = scm_list_1(scm_from_utf8_symbol("data"));
  finalizer = finalize_afarray;

  afarray_type = scm_make_foreign_object_type(name, slots, finalizer);
}

SCM print_array_w(SCM ar)
{
  af_array value = scm_foreign_object_ref(ar, 0);
  af_print_array(value);
  return SCM_BOOL_T;
}

SCM info_w()
{
  af_err _errno = af_info();
  SCM errno = scm_from_int(_errno);
  return errno;
}

SCM init_w()
{
  af_err _errno = af_init();
  SCM errno = scm_from_int(_errno);
  return errno;
}

AS_API void arrayfire_scm_init()
{
  init_afarray_type();
  af_error = scm_string_to_symbol(scm_from_utf8_string("misc-error"));

  scm_c_define_gsubr("print-array", 1, 0, 0, (void*)&print_array_w);
  scm_c_define_gsubr("af-info", 0, 0, 0, (void*)&info_w);
  scm_c_define_gsubr("af-init", 0, 0, 0, (void*)&init_w);

  init_array();
  init_constructor();
  init_index();
  init_io();
  init_linear_algebra();
  init_mathematic();
  init_statistics();
}
