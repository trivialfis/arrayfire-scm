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
#include "linear_algebra.h"

static void finalize_afarray(SCM array)
{
  printf("finalize array");
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

  afarray_type =scm_make_foreign_object_type(name, slots, finalizer);
}

SCM randu_w(SCM _ndims, SCM _dims, SCM _dtype)
{
  af_array out = 0;
  SCM dtype_scm = scm_symbol_to_string(_dtype);
  char *dtype = scm_to_locale_string(dtype_scm);

  unsigned ndims = scm_to_uint64(_ndims);
  SCM _listp = scm_list_p(_dims);
  SCM _dims_len = 0;
  if (scm_is_true(_listp))
    {
      _dims_len = scm_length(_dims);
    }
  int dl_debug = scm_to_int(_dims_len);
  int _ndl_debug = scm_to_int(_ndims);
  if (scm_is_false(scm_equal_p(_ndims, _dims_len)))
    {
      SCM message;
      message = scm_from_utf8_string("Wrong dim.");
      scm_throw(af_error, message);
    }
  int dims_len = scm_to_int(_dims_len);
  dim_t *dims = (dim_t*)malloc(sizeof(dim_t)*dims_len);
  for (int i = 0; i < ndims; ++i)
    {
      SCM temp = scm_car(_dims);
      dims[i] = scm_to_int(temp);
    }

  af_err errno = af_randu(&out, ndims, dims, f32);
  if (errno != AF_SUCCESS)
    {
      SCM message;
      message = scm_from_utf8_string("af_randu failed.");
      scm_throw(af_error, message);
    }
  free(dims);
  SCM _ar = scm_make_foreign_object_1(afarray_type, (void*)out);
  /* errno = af_print_array(out); */
  /* if (errno != AF_SUCCESS) */
  /*   printf("print error %d", errno); */
  return _ar;
}

AS_API void arrayfire_scm_init()
{
  init_afarray_type();

  scm_c_define_gsubr("randu", 3, 0, 0, (void*)&randu_w);
  scm_c_define_gsubr("dot", 2, 0, 0, (void*)&dot_w);
}
