#include "image.h"

SCM load_image_w(SCM _filename, SCM _is_color)
{
  scm_dynwind_begin(0);
  int is_color = 1;
  if (! scm_is_eq(_is_color, SCM_UNDEFINED) && scm_is_false(_is_color))
    {
      is_color = 0;
    }
  const char *filename = scm_to_locale_string(_filename);
  scm_dynwind_unwind_handler (free, (void*)filename, SCM_F_WIND_EXPLICITLY);
  af_array out = 0;
  af_load_image(&out, filename, is_color);

  SCM result = scm_make_foreign_object_1(afarray_type, (af_array)out);

  scm_dynwind_end ();
  return result;
}
