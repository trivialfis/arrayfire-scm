#include <libguile.h>
#include <arrayfire.h>

#include "arrayfire_scm.h"

typedef struct afarray
{
  af::array *ar;
} afarray;

static SCM afarray_type;

AS_API SCM make_afarray(SCM width)
{
  af::array *ar;
  // ar = (af::array*) scm_gc_malloc(sizeof(af::array), "array");
  int value = scm_to_int(width);
  ar = new af::array(value, value);
  return scm_make_foreign_object_1(afarray_type, ar);
}

AS_API void init_type()
{
  scm_c_define_gsubr("make-afarray", 1, 0, 0, (scm_t_subr)&make_afarray);
}
