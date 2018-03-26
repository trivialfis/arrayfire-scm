#ifndef ARRAYFIRE_SCM_CONSTRUCTION_H
#define ARRAYFIRE_SCM_CONSTRUCTION_H

#include "arrayfire_scm.h"

SCM randu_w(SCM _ndims, SCM _dims, SCM _dtype);
SCM from_scm_array(SCM ar);
void init_type_hash();

#endif
