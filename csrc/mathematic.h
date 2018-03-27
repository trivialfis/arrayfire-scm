/* Wrapper mathematical functions.
   Copyright © 2018 Fis Trivial <ybbs.daans@hotmail.com>

This file is part of arrayfire-scm.

arrayfire-scm is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

arrayfire-scm is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with arrayfire-scm.  If not, see <http://www.gnu.org/licenses/>.    */

#ifndef ARRAYFIRE_SCM_MATH_H
#define ARRAYFIRE_SCM_MATH_H

#include "arrayfire_scm.h"
SCM and_w(SCM _lhs, SCM _rhs, SCM batch_p);
SCM bitand_w(SCM _lhs, SCM _rhs, SCM batch_p);
SCM bitor_w(SCM _lhs, SCM _rhs, SCM batch_p);
SCM bitxor_w(SCM _lhs, SCM _rhs, SCM batch_p);
SCM eq_w(SCM _lhs, SCM _rhs, SCM batch_p);
SCM ge_w(SCM _lhs, SCM _rhs, SCM batch_p);
SCM gt_w(SCM _lhs, SCM _rhs, SCM batch_p);
SCM le_w(SCM _lhs, SCM _rhs, SCM batch_p);
SCM lt_w(SCM _lhs, SCM _rhs, SCM batch_p);
SCM neq_w(SCM _lhs, SCM _rhs, SCM batch_p);
SCM not_w(SCM _in);

#endif