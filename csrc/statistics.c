#include "statistics.h"

SCM mean_w(SCM _in, SCM _dim)
{
  scm_assert_foreign_object_type(afarray_type, _in);
  af_array in = scm_foreign_object_ref(_in, 0);
  dim_t dim = scm_to_long_long(_dim);
  af_array out = 0;
  af_err errno = af_mean(&out, in, dim);
  if (errno != AF_SUCCESS)
    {
      SCM message;
      message = scm_from_utf8_string("mean_w failed.\n");
      scm_throw(af_error, message);      
    }
  SCM result = scm_make_foreign_object_1(afarray_type, (af_array)out);
  return result;
}

void init_statistics()
{
  scm_c_define_gsubr("mean", 2, 0, 0, (void*)&mean_w);
}
