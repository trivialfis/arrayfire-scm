#include "linear_algebra.h"

SCM dot_w(SCM _lhs, SCM _rhs)
{
  af_array out = 0;
  af_array lhs = scm_foreign_object_ref(_lhs, 0);
  af_array rhs = scm_foreign_object_ref(_rhs, 0);
  /* af_err errno = af_print_array(lhs); */
  /* if (errno != AF_SUCCESS) */
  /*   printf("print error %d", errno); */
  /* errno = af_print_array(rhs); */
  /* if (errno != AF_SUCCESS) */
  /*   printf("print error %d", errno);
   */
  af_err errno = AF_SUCCESS;
  errno = af_dot(&out, lhs, rhs, AF_MAT_NONE, AF_MAT_NONE);
  printf("%d", errno);
  fflush(stdout);
  af_print_array(out);
  if (errno != AF_SUCCESS)
    {
      SCM message;
      message = scm_from_utf8_string("af_dot error.\n");
      scm_throw(af_error, message);
    }

  SCM result = scm_make_foreign_object_1(afarray_type, (af_array)out);
  return result;
}
