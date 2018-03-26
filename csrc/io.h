#ifndef AF_SCM_IMAGE_H
#define AF_SCM_IMAGE_H

#include "arrayfire_scm.h"

SCM load_image_w(SCM _filename, SCM _is_color);
SCM save_image_w(SCM _filename, SCM _in);
SCM save_array_w(SCM _index, SCM _key, SCM _arr, SCM _filename, SCM _append);

#endif
