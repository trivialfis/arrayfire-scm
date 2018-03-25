#include <libguile.h>
#include <arrayfire.h>

#include "arrayfire_scm.h"

struct array_warpper
{
  af_array ar;
};

static void finalize_afarray(SCM array)
{
  af_array ar = (af_array)scm_to_pointer(array);
  af_release_array(ar);
}

static SCM afarray_type;

SCM randu_w(SCM _ndims, SCM _dims, SCM _dtype)
{
  af_array out = 0;
  SCM dtype_scm = scm_symbol_to_string(_dtype);
  char *dtype = scm_to_locale_string(dtype_scm);
  unsigned ndims = scm_to_uint64(_ndims);
  SCM _listp = scm_list_p(_dims);
  SCM _dims_len = 0;
  if (scm_is_true(_listp))
    {
      _dims_len = scm_length(_dims);
    }
  if (!scm_equal_p(_ndims, _dims_len))
    {
      exit(1);
    }
  int dims_len = scm_to_int(_dims_len);
  dim_t *dims = (dim_t*)malloc(sizeof(dim_t)*dims_len);
  for (int i = 0; i < ndims; ++i)
    {
      SCM temp = scm_car(_dims);
      dims[i] = scm_to_int(temp);
    }
  af_err errno = af_randu(&out, ndims, dims, f32);
  free(dims);
  return scm_make_foreign_object_1(afarray_type, out);
}

/* SCM make_constant(SCM _value, SCM _size, SCM _ndims) */
/* { */
/*   double value = scm_to_double(_value); */
/*   unsigned int size = scm_to_int(_size); */
/*   dim_t ndims = scm_to_long_long(_ndims); */
/*   // af_array ar; */
/*   struct array_warpper *ar; */
/*   af::array temp = af::constant(value, ndims); */
/*   ar->ar = new af::array{std::move(temp)}; */
/*   // af_err errno = (af_err)af_constant(&ar, value, size, &ndims, f32); */
/*   return scm_make_foreign_object_1(afarray_type, ar); */
/* } */

AS_API void init_type()
{
  scm_c_define_gsubr("randu", 3, 0, 0, (void*)&randu_w);
}
