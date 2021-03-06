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

#include "io.h"

void check_image_io()
{
  int io_available = 1;
  af_err errno = af_is_image_io_available((bool*)&io_available);
  if (errno != AF_SUCCESS)
    {
      SCM message = scm_from_utf8_string("Check image io failed.\n");
      scm_throw(af_error, message);
    }
  if (!io_available)
    {
      SCM message = scm_from_utf8_string("Image io is not compiled.\n");
      scm_throw(af_error, message);
    }
}

SCM load_image_w(SCM _filename, SCM _is_color)
{
  check_image_io();

  scm_dynwind_begin(0);
  int is_color = 1;
  if (! scm_is_eq(_is_color, SCM_UNDEFINED) && scm_is_false(_is_color))
    {
      is_color = 0;
    }
  const char *filename = scm_to_locale_string(_filename);
  scm_dynwind_unwind_handler (free, (void*)filename, SCM_F_WIND_EXPLICITLY);

  af_array out = 0;
  af_err errno = af_load_image(&out, filename, is_color);
  AFS_ASSERT("load_image", errno);

  SCM result = scm_make_foreign_object_1(afarray_type, (af_array)out);

  scm_dynwind_end ();
  return result;
}

SCM save_image_w(SCM _filename, SCM _in)
{
  check_image_io();
  scm_dynwind_begin(0);

  const char *filename = scm_to_locale_string(_filename);
  scm_dynwind_unwind_handler (free, (void*)filename, SCM_F_WIND_EXPLICITLY);
  scm_assert_foreign_object_type(afarray_type, _in);
  af_array in = scm_foreign_object_ref(_in, 0);

  af_err errno = af_save_image(filename, in);
  AFS_ASSERT("save_image", errno);

  scm_dynwind_end();
  return SCM_BOOL_T;
}

SCM save_array_w(SCM _index, SCM _key, SCM _arr, SCM _filename, SCM _append)
{
  scm_dynwind_begin(0);

  int append = 0;
  if (! scm_is_eq(_append, SCM_UNDEFINED) && scm_is_false(_append))
    {
      append = 0;
    }
  int index = scm_to_int(_index);
  const char* key = scm_to_locale_string(_key);
  scm_dynwind_unwind_handler (free, (void*)key, SCM_F_WIND_EXPLICITLY);
  const char* filename = scm_to_locale_string(_filename);
  scm_dynwind_unwind_handler (free, (void*)key, SCM_F_WIND_EXPLICITLY);

  scm_assert_foreign_object_type(afarray_type, _arr);
  af_array arr = scm_foreign_object_ref(_arr, 0);

  af_err errno = af_save_array(&index, key, arr, filename, append);
  AFS_ASSERT("save_array", errno);

  scm_dynwind_end();
  return SCM_BOOL_T;
}

void init_io()
{
  scm_c_define_gsubr("load-image", 1, 1, 0, (void*)&load_image_w);
  scm_c_define_gsubr("save-image", 2, 0, 0, (void*)&save_image_w);
  scm_c_define_gsubr("save-array", 3, 1, 0, (void*)&save_array_w);
}
