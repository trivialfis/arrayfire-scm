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

#include "array.h"

SCM get_dims_w(SCM _in)
{
  scm_assert_foreign_object_type(afarray_type, _in);
  dim_t d0, d1, d2, d3;
  dim_t _dims[4];
  af_array in = scm_foreign_object_ref(_in, 0);
  af_err errno = af_get_dims(&_dims[0], &_dims[1], &_dims[2], &_dims[3], in);
  if (errno != AF_SUCCESS)
    {
      SCM message = scm_from_utf8_string("Get dims failed.\n");
      scm_throw(af_error, message);
    }
  SCM dims[4];
  for (int i = 0; i < 4; ++i)
    dims[i] = scm_from_long_long(_dims[i]);
  SCM result = scm_list_4(dims[0], dims[1], dims[2], dims[3]);
  return result;
}

void init_array()
{
  scm_c_define_gsubr("get-dims", 1, 0, 0, (void*)&get_dims_w);
}
