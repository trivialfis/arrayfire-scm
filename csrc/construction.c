#include "construction.h"

static SCM TYPE_HASH = 0;

static void init_type_hash()
{
  if (TYPE_HASH != 0)
    {
      fprintf(stderr, "Reinitialize TYPE_HASH\n");
      return;
    }
  SCM entries_num = scm_from_int(12);
  TYPE_HASH = scm_make_hash_table(entries_num);
  SCM scm_u8 = scm_string_to_symbol(scm_from_utf8_string("u8"));
  SCM scm_u16 = scm_string_to_symbol(scm_from_utf8_string("u16"));
  SCM scm_u32 = scm_string_to_symbol(scm_from_utf8_string("u32"));
  SCM scm_u64 = scm_string_to_symbol(scm_from_utf8_string("u64"));

  SCM scm_s8 = scm_string_to_symbol(scm_from_utf8_string("s8"));
  SCM scm_s16 = scm_string_to_symbol(scm_from_utf8_string("s16"));
  SCM scm_s32 = scm_string_to_symbol(scm_from_utf8_string("s32"));
  SCM scm_s64 = scm_string_to_symbol(scm_from_utf8_string("s64"));

  SCM scm_f32 = scm_string_to_symbol(scm_from_utf8_string("f32"));
  SCM scm_f64 = scm_string_to_symbol(scm_from_utf8_string("f64"));

  SCM scm_c32 = scm_string_to_symbol(scm_from_utf8_string("c32"));
  SCM scm_c64 = scm_string_to_symbol(scm_from_utf8_string("c64"));

  scm_hash_set_x(TYPE_HASH, scm_symbol_hash(scm_u8), scm_from_int(u8));
  scm_hash_set_x(TYPE_HASH, scm_symbol_hash(scm_u16), scm_from_int(u16));
  scm_hash_set_x(TYPE_HASH, scm_symbol_hash(scm_u32), scm_from_int(u32));
  scm_hash_set_x(TYPE_HASH, scm_symbol_hash(scm_u64), scm_from_int(u64));
  scm_hash_set_x(TYPE_HASH, scm_symbol_hash(scm_s8), scm_from_int(b8));
  scm_hash_set_x(TYPE_HASH, scm_symbol_hash(scm_s16), scm_from_int(s16));
  scm_hash_set_x(TYPE_HASH, scm_symbol_hash(scm_s32), scm_from_int(s32));
  scm_hash_set_x(TYPE_HASH, scm_symbol_hash(scm_s64), scm_from_int(s64));
  scm_hash_set_x(TYPE_HASH, scm_symbol_hash(scm_f32), scm_from_int(f32));
  scm_hash_set_x(TYPE_HASH, scm_symbol_hash(scm_f64), scm_from_int(f64));
  scm_hash_set_x(TYPE_HASH, scm_symbol_hash(scm_c32), scm_from_int(c32));
  scm_hash_set_x(TYPE_HASH, scm_symbol_hash(scm_c64), scm_from_int(c64));
}


static af_dtype scm_to_af_dtype(SCM _dtype)
{
  SCM hash_val = scm_hash_ref(TYPE_HASH, scm_symbol_hash(_dtype), SCM_BOOL_F);
  if (scm_is_false(hash_val))
    {
      SCM message;
      message = scm_from_utf8_string("Unknown type.");
      scm_throw(af_error, message);
    }
  int _dtype_int = scm_to_int(hash_val);
  af_dtype dtype = (af_dtype)_dtype_int;
  return dtype;
}


static dim_t* handle_dims(SCM _dims, SCM _ndims)
{
  SCM _listp = scm_list_p(_dims);
  SCM _dims_len = 0;
  unsigned ndims = scm_to_uint64(_ndims);
  if (scm_is_true(_listp))
    {
      _dims_len = scm_length(_dims);
    }
  else
    {
      SCM message;
      message = scm_from_utf8_string("Expecting list as dims.");
      scm_throw(af_error, message);
    }

  if (scm_is_false(scm_equal_p(_ndims, _dims_len)))
    {
      SCM message;
      message = scm_from_utf8_string("Wrong dim.");
      scm_throw(af_error, message);
    }
  int dims_len = scm_to_int(_dims_len);
  dim_t *dims = (dim_t*)malloc(sizeof(dim_t)*dims_len);
  for (int i = 0; i < ndims; ++i)
    {
      SCM temp = scm_car(_dims);
      dims[i] = scm_to_int(temp);
    }
  return dims;
}


SCM randu_w(SCM _ndims, SCM _dims, SCM _dtype)
{
  af_dtype dtype = scm_to_af_dtype(_dtype);
  unsigned ndims = scm_to_uint64(_ndims);
  dim_t *dims = handle_dims(_dims, _ndims);

  af_array out = 0;
  af_err errno = af_randu(&out, ndims, dims, dtype);
  if (errno != AF_SUCCESS)
    {
      SCM message;
      message = scm_from_utf8_string("af_randu failed.");
      scm_throw(af_error, message);
    }
  free(dims);
  SCM _ar = scm_make_foreign_object_1(afarray_type, (void*)out);

  return _ar;
}

SCM from_scm_array(SCM ar)
{
  if (!scm_is_array(ar))
    {
      SCM message;
      message = scm_from_utf8_string("Not an array.");
      scm_throw(af_error, message);
    }
  scm_t_array_handle handle;
  scm_array_get_handle(ar, &handle);
  SCM _dtype_scm = scm_array_type(ar);

  void* _content =  (void*)scm_array_handle_uniform_elements(&handle);

  size_t _ndims = scm_array_handle_rank(&handle);
  scm_t_array_dim *_dims = scm_array_handle_dims(&handle);
  dim_t *dims = (dim_t*)malloc(sizeof(dim_t)*_ndims);
  /* printf("_ndims:%lu\n", _ndims); */
  for (int i = 0; i < _ndims; ++i)
    {
      dims[i] = (_dims[i].ubnd - _dims[i].lbnd) + 1;
    }
  af_err errno = AF_SUCCESS;

  af_array out = 0;

  SCM hash_val = scm_hash_ref(TYPE_HASH, scm_symbol_hash(_dtype_scm), SCM_BOOL_F);
  if (scm_is_false(hash_val))
    {
      SCM message;
      message = scm_from_utf8_string("Unknown type.");
      scm_throw(af_error, message);
    }
  int _dtype_int = scm_to_int(hash_val);
  af_dtype _dtype = (af_dtype)_dtype_int;
  errno = af_create_array(&out, _content, _ndims, dims, _dtype);
  if (errno != AF_SUCCESS)
    {
      SCM message;
      fprintf(stderr, "Error code:%d", errno);
      message = scm_from_utf8_string("af_create_array failed.");
      scm_throw(af_error, message);
    }
  free(dims);

  SCM _ar = scm_make_foreign_object_1(afarray_type, (void*)out);
  scm_array_handle_release(&handle);

  return _ar;
}


SCM constant_w(SCM _val, SCM _ndims, SCM _dims, SCM _dtype)
{
  double value = scm_to_double(_val);
  af_dtype dtype = scm_to_af_dtype(_dtype);
  unsigned ndims = scm_to_uint64(_ndims);

  dim_t *dims = handle_dims(_dims, _ndims);

  af_array out = 0;
  af_err errno = af_constant(&out, value, ndims, dims, dtype);

  free(dims);

  SCM _ar = scm_make_foreign_object_1(afarray_type, (void*)out);
  return _ar;
}


SCM assign_gen_w(SCM _lhs, SCM _ndims, SCM _indices, SCM _rhs)
{
  scm_assert_foreign_object_type(afarray_type, _lhs);
}


/* SCM copy_array_w() */
/* { */

/* } */


SCM retain_array_w(SCM _in)
{
  scm_assert_foreign_object_type(afarray_type, _in);

  af_array in = scm_foreign_object_ref(_in, 0);

  af_array out = 0;
  af_err errno = af_retain_array(&out, in);
  SCM _ar = scm_make_foreign_object_1(afarray_type, (void*)out);
  return _ar;
}


/* SCM create_handle_w(SCM _ndims, SCM _dims, SCM _dtype) */
/* { */

/* } */


SCM create_empty_array()
{
  af_array out = 0;
  dim_t dims[] = {0, 1, 1, 1};
  af_err errno =  af_create_handle(&out, AF_MAX_DIMS, dims, f32);
  if (errno != AF_SUCCESS)
    {
      SCM message;
      message = scm_from_utf8_string("af_create_handle failed.");
      scm_throw(af_error, message);
    }
  SCM _ar = scm_make_foreign_object_1(afarray_type, (void*)out);
  return _ar;
}


void init_constructor()
{
  init_type_hash();
  scm_c_define_gsubr("af-randu", 3, 0, 0, (void*)&randu_w);
  scm_c_define_gsubr("af-from-array", 1, 0, 0, (void*)&from_scm_array);
  scm_c_define_gsubr("af-constant", 4, 0, 0, (void*)&constant_w);
  scm_c_define_gsubr("af-create-empty", 0, 0, 0, (void*)&create_empty_array);
  scm_c_define_gsubr("af-retain-array", 1, 0, 0, (void*)&retain_array_w);
}
