#ifndef ARRAYFIRE_SCM_H
#define ARRAYFIRE_SCM_H

#include <libguile.h>
#include <arrayfire.h>

#ifdef __cplusplus
# define AS_API extern "C"
#else
# define AS_API extern
#endif

static SCM afarray_type;
static SCM af_error;

#endif	// arrayfire_scm_EXPORTS
