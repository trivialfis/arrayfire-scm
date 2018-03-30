/* Wrapper for linear algebra.
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

#include "linear_algebra.h"

SCM dot_w(SCM _lhs, SCM _rhs)
{
  af_array out = 0;

  scm_assert_foreign_object_type(afarray_type, _lhs);
  scm_assert_foreign_object_type(afarray_type, _rhs);
  af_array lhs = scm_foreign_object_ref(_lhs, 0);
  af_array rhs = scm_foreign_object_ref(_rhs, 0);

  af_err errno = AF_SUCCESS;
  errno = af_dot(&out, lhs, rhs, AF_MAT_NONE, AF_MAT_NONE);
  if (errno != AF_SUCCESS)
    {
      if (errno == AF_ERR_TYPE)
	fprintf(stderr, "Only floating point is supported, namely, f32, f64");
      fprintf(stderr, "errno: %d\n", errno);
      SCM message;
      message = scm_from_utf8_string("af_dot error.\n");
      scm_throw(af_error, message);
    }

  SCM result = scm_make_foreign_object_1(afarray_type, (af_array)out);
  return result;
}

SCM matmul_w(SCM _lhs, SCM _rhs)
{
  af_array out = 0;

  scm_assert_foreign_object_type(afarray_type, _lhs);
  scm_assert_foreign_object_type(afarray_type, _rhs);
  af_array lhs = scm_foreign_object_ref(_lhs, 0);
  af_array rhs = scm_foreign_object_ref(_rhs, 0);
  af_err errno = AF_SUCCESS;

  errno = af_matmul(&out, lhs, rhs, AF_MAT_NONE, AF_MAT_NONE);
  AFS_ASSERT("matmul", errno);

  SCM result = scm_make_foreign_object_1(afarray_type, (af_array)out);
  return result;
}

SCM transpose_w(SCM _in)
{
  scm_assert_foreign_object_type(afarray_type, _in);
  af_array in = scm_foreign_object_ref(_in, 0);
  af_array out = 0;
  af_err errno = af_transpose(&out, in, false);
  if (errno != AF_SUCCESS)
    {
      SCM message;
      message = scm_from_utf8_string("transpose_w failed.\n");
      scm_throw(af_error, message);
    }
  SCM result = scm_make_foreign_object_1(afarray_type, (af_array)out);
  return result;
}

SCM inverse_w(SCM _in)
{
  scm_assert_foreign_object_type(afarray_type, _in);
  af_array in = scm_foreign_object_ref(_in, 0);
  af_array out = 0;
  af_err errno = af_inverse(&out, in, AF_MAT_NONE);
  if (errno != AF_SUCCESS)
    {
      SCM message;
      fprintf(stderr, "Errno: %d\n", errno);
      message = scm_from_utf8_string("inverse_w failed.\n");
      scm_throw(af_error, message);
    }
  SCM result = scm_make_foreign_object_1(afarray_type, (af_array)out);
  return result;
}

void init_linear_algebra()
{
  scm_c_define_gsubr("af-dot", 2, 0, 0, (void*)&dot_w);
  scm_c_define_gsubr("af-matmul", 2, 0, 0, (void*)&matmul_w);
  scm_c_define_gsubr("af-transpose", 1, 0, 0, (void*)&transpose_w);
  scm_c_define_gsubr("af-inverse", 1, 0, 0, (void*)&inverse_w);
}
