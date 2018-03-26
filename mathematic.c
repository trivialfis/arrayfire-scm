#include "mathematic.h"

/* SCM eq_w(SCM _lhs, SCM _rhs, SCM batch_p) */
/* { */
/*   char is_batch = 1; */
/*   if (! scm_is_eq(batch_p, SCM_UNDEFINED) && scm_is_false(batch_p)) */
/*     { */
/*       is_batch = 0; */
/*     } */
/*   scm_assert_foreign_object_type(afarray_type, _lhs); */
/*   scm_assert_foreign_object_type(afarray_type, _rhs); */

/*   af_array lhs = scm_foreign_object_ref(_lhs, 0); */
/*   af_array rhs = scm_foreign_object_ref(_rhs, 0); */
/*   af_array out = 0; */

/*   af_err errno = AF_SUCCESS; */

/*   errno = af_eq(&out, lhs, rhs, is_batch); */
/*   if (errno != AF_SUCCESS) */
/*     { */
/*       SCM message; */
/*       message = scm_from_utf8_string("af_eq failed.\n"); */
/*       scm_throw(af_error, message); */
/*     } */
/*   SCM result = scm_make_foreign_object_1(afarray_type, (af_array)out); */
/*   return result; */
/* } */

SCM af_logical_op(SCM _lhs, SCM _rhs, SCM batch_p,
		   af_err(*op)(af_array*, af_array, af_array, bool))
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

  errno = op(&out, lhs, rhs, is_batch);
  if (errno != AF_SUCCESS)
    {
      SCM message;
      message = scm_from_utf8_string("af_<logic> failed.\n");
      scm_throw(af_error, message);
    }
  SCM result = scm_make_foreign_object_1(afarray_type, (af_array)out);
  return result;
}

SCM and_w(SCM _lhs, SCM _rhs, SCM batch_p)
{
  return af_logical_op(_lhs, _rhs, batch_p, af_and);
}
SCM bitand_w(SCM _lhs, SCM _rhs, SCM batch_p)
{
  return af_logical_op(_lhs, _rhs, batch_p, af_bitand);
}
SCM bitor_w(SCM _lhs, SCM _rhs, SCM batch_p)
{
  return af_logical_op(_lhs, _rhs, batch_p, af_bitor);
}
SCM bitxor_w(SCM _lhs, SCM _rhs, SCM batch_p)
{
  return af_logical_op(_lhs, _rhs, batch_p, af_bitxor);
}
SCM eq_w(SCM _lhs, SCM _rhs, SCM batch_p)
{
  return af_logical_op(_lhs, _rhs, batch_p, af_eq);
}
SCM ge_w(SCM _lhs, SCM _rhs, SCM batch_p)
{
  return af_logical_op(_lhs, _rhs, batch_p, af_ge);
}
SCM gt_w(SCM _lhs, SCM _rhs, SCM batch_p)
{
  return af_logical_op(_lhs, _rhs, batch_p, af_gt);
}
SCM le_w(SCM _lhs, SCM _rhs, SCM batch_p)
{
  return af_logical_op(_lhs, _rhs, batch_p, af_le);
}
SCM lt_w(SCM _lhs, SCM _rhs, SCM batch_p)
{
  return af_logical_op(_lhs, _rhs, batch_p, af_lt);
}

/* FIXME: neg missing */

SCM neq_w(SCM _lhs, SCM _rhs, SCM batch_p)
{
  return af_logical_op(_lhs, _rhs, batch_p, af_neq);
}

SCM not_w(SCM _in)
{
  scm_assert_foreign_object_type(afarray_type, _in);
  af_array in = scm_foreign_object_ref(_in, 0);
  af_array out = 0;
  af_err errno = af_not(&out, in);
  if (errno != AF_SUCCESS)
    {
      SCM message;
      message = scm_from_utf8_string("af_not failed.\n");
      scm_throw(af_error, message);     
    }
  SCM result = scm_make_foreign_object_1(afarray_type, (af_array)out);
  return result;
}
