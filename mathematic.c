#include "mathematic.h"

SCM eq_w(SCM _lhs, SCM _rhs, SCM batch_p)
{
  char is_batch = 1;
  if (! scm_is_eq(batch_p, SCM_UNDEFINED) && scm_is_false(batch_p))
    {
      is_batch = 0;
    }
  scm_assert_foreign_object_type(afarray_type, _lhs);
  scm_assert_foreign_object_type(afarray_type, _rhs);

  af_array lhs = scm_foreign_object_ref(_lhs, 0);
  af_array rhs = scm_foreign_object_ref(_rhs, 0);
  af_array out = 0;

  af_err errno = AF_SUCCESS;

  errno = af_eq(&out, lhs, rhs, is_batch);
  if (errno != AF_SUCCESS)
    {
      SCM message;
      message = scm_from_utf8_string("af_eq failed.\n");
      scm_throw(af_error, message);
    }
  SCM result = scm_make_foreign_object_1(afarray_type, (af_array)out);
  return result;
}
