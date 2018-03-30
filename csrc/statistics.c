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

#include "statistics.h"

SCM mean_w(SCM _in, SCM _dim)
{
  scm_assert_foreign_object_type(afarray_type, _in);
  af_array in = scm_foreign_object_ref(_in, 0);
  dim_t dim = scm_to_long_long(_dim);

  af_array out = 0;
  af_err errno = af_mean(&out, in, dim);
  AFS_ASSERT("mean", errno);

  SCM result = scm_make_foreign_object_1(afarray_type, (af_array)out);
  return result;
}

void init_statistics()
{
  scm_c_define_gsubr("af-mean", 2, 0, 0, (void*)&mean_w);
}
