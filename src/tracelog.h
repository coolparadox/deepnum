/*
 * Copyright 2019 Rafael Lorandi <coolparadox@gmail.com>
 *
 * This file is part of dn-clarith, a library for performing arithmetic
 * in continued logarithm representation.
 * 
 * dn-clarith is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * dn-clarith is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with dn-clarith.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef SRC_TRACELOG_H_
#define SRC_TRACELOG_H_

#include <config.h>

#if TRACE

#include <iostream>

#define tracelog(X) std::clog << "\n" << this << "." << __FUNCTION__ << ": " << X

#else  // TRACE

#define tracelog(X) ((void) 0)

#endif  // TRACE

#endif  // SRC_TRACELOG_H_
