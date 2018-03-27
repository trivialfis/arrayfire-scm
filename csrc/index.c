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

#include "index.h"

SCM af_seq_type;

void init_af_seq_type(void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer = NULL;

  name = scm_from_utf8_symbol("seq");
  SCM beg = scm_from_utf8_symbol("begin");
  SCM end = scm_from_utf8_symbol("end");
  SCM step = scm_from_utf8_symbol("step");
  slots = scm_list_3(beg, end, step);

  af_seq_type = scm_make_foreign_object_type(name, slots, finalizer);
}

SCM seq_from_list(SCM _list)
{
  SCM _len = scm_length(_list);
  size_t len = scm_to_size_t(_len);
  if (len != 3)
    {
      SCM message = scm_from_utf8_string("Wrong length of seq.");
      scm_throw(af_error, message);
    }
  af_seq *_seq = (struct af_seq *)scm_gc_malloc(sizeof(af_seq), "seq");
  uint beg = scm_to_uint(scm_car(_list));
  uint end = scm_to_uint(scm_cadr(_list));
  uint step = scm_to_uint(scm_caddr(_list));

  _seq->begin = beg;
  _seq->end = end;
  _seq->step = step;

  SCM seq = scm_make_foreign_object_1(af_seq_type, _seq);
  return seq;
}

SCM index_w(SCM _in, SCM _ndims, SCM _index)
{
  scm_assert_foreign_object_type(afarray_type, _in);
  scm_assert_foreign_object_type(af_seq_type, _index);
  af_array in = scm_foreign_object_ref(_in, 0);

  const af_seq * const seq = (struct af_seq*)scm_foreign_object_ref(_index, 0);
  const unsigned ndims = scm_to_uint(_ndims);
  af_array out = 0;
  af_err errno = af_index(&out, in, ndims, seq);
  if (errno != AF_SUCCESS)
    {
      SCM message = scm_from_utf8_string("af_index failed.");
      scm_throw(af_error, message);
    }
  SCM result = scm_make_foreign_object_1(afarray_type, (af_array)out);
  return result;
}

SCM lookup_w(SCM _in, SCM _indices_ar, SCM _dim)
{
  scm_assert_foreign_object_type(afarray_type, _in);
  scm_assert_foreign_object_type(afarray_type, _indices_ar);
  af_array in = scm_foreign_object_ref(_in, 0);
  af_array indices = scm_foreign_object_ref(_indices_ar, 0);
  dim_t dim = scm_to_long_long(_dim);
  af_array out = 0;
  af_err errno = af_lookup(&out, in, indices, dim);
  if (errno != AF_SUCCESS)
    {
      SCM message;
      fprintf(stderr, "Errno: %d\n", errno);
      message = scm_from_utf8_string("lookup_w failed.\n");
      scm_throw(af_error, message);
    }
  SCM result = scm_make_foreign_object_1(afarray_type, (af_array)out);
  return result;
}

void init_index()
{
  init_af_seq_type();
  scm_c_define_gsubr("lookup", 3, 0, 0, (void*)&lookup_w);
  scm_c_define_gsubr("index", 3, 0, 0, (void*)&index_w);
  scm_c_define_gsubr("seq-from-list", 1, 0, 0, (void*)&seq_from_list);
}
