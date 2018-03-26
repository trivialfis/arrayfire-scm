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
#include "image.h"

SCM afarray_type;

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


SCM print_array_w(SCM ar)
{
  af_array value = scm_foreign_object_ref(ar, 0);
  af_print_array(value);
  return SCM_BOOL_T;
}

AS_API void arrayfire_scm_init()
{
  init_afarray_type();
  init_type_hash();

  scm_c_define_gsubr("print-array", 1, 0, 0, (void*)&print_array_w);
  scm_c_define_gsubr("randu", 3, 0, 0, (void*)&randu_w);
  scm_c_define_gsubr("from-array", 1, 0, 0, (void*)&from_scm_array);

  scm_c_define_gsubr("afand", 2, 1, 0, (void*)&and_w);
  scm_c_define_gsubr("afbitand", 2, 1, 0, (void*)&bitand_w);
  scm_c_define_gsubr("afbitor", 2, 1, 0, (void*)&bitor_w);
  scm_c_define_gsubr("afbitxor", 2, 1, 0, (void*)&bitxor_w);
  scm_c_define_gsubr("afeq", 2, 1, 0, (void*)&eq_w);
  scm_c_define_gsubr("afge", 2, 1, 0, (void*)&ge_w);
  scm_c_define_gsubr("afgt", 2, 1, 0, (void*)&gt_w);
  scm_c_define_gsubr("afle", 2, 1, 0, (void*)&le_w);
  scm_c_define_gsubr("aflt", 2, 1, 0, (void*)&lt_w);
  scm_c_define_gsubr("afneq", 2, 1, 0, (void*)&neq_w);
  scm_c_define_gsubr("afnot", 1, 0, 0, (void*)&not_w);

  scm_c_define_gsubr("dot", 2, 0, 0, (void*)&dot_w);
  scm_c_define_gsubr("matmul", 2, 0, 0, (void*)&matmul_w);
  scm_c_define_gsubr("transpose", 1, 0, 0, (void*)&transpose_w);
  scm_c_define_gsubr("inverse", 1, 0, 0, (void*)&inverse_w);

  scm_c_define_gsubr("load-image", 1, 1, 0, (void*)&load_image_w);
}
