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

#include "number.hpp"
#include "protocol/protocol.hpp"

#include "util.hpp"

using deepnum::clarith::protocol::Protocol;

namespace deepnum
{
namespace clarith
{

int Util::Compare(std::unique_ptr<Number> n1, std::unique_ptr<Number> n2, bool pedantic)
{
    Protocol v1, v2;
    int polarity = 1;
    bool v1_may_be_zero = true;
    bool v2_may_be_zero = true;
    while (true)
    {
        v1 = n1->Egest();
        v2 = n2->Egest();
        if (!pedantic)
        {
            if (v1_may_be_zero && (v1 == Protocol::kOne || v1 == Protocol::kTwo || v1 == Protocol::kEnd)) { v1_may_be_zero = false; }
            if (v2_may_be_zero && (v2 == Protocol::kOne || v2 == Protocol::kTwo || v2 == Protocol::kEnd)) { v2_may_be_zero = false; }
        }
        if (v1 == Protocol::kEnd && v2 == Protocol::kEnd) { return 0; }
        if (v1 != v2) { break; }
        if (v1 == Protocol::kNeg || v1 == Protocol::kOne || v1 == Protocol::kZero) { polarity *= -1; }
    }
    if (v1 == Protocol::kNeg)
    {
        if (!pedantic && v2_may_be_zero && n1->Egest() == Protocol::kZero && n1->Egest() == Protocol::kEnd && n2->Egest() == Protocol::kEnd) { return 0; }
        return -polarity;
    }
    if (v2 == Protocol::kNeg)
    {
        if (!pedantic && v1_may_be_zero && n2->Egest() == Protocol::kZero && n2->Egest() == Protocol::kEnd && n1->Egest() == Protocol::kEnd) { return 0; }
        return polarity;
    }
    if (v1 == Protocol::kZero) { return -polarity; }
    if (v2 == Protocol::kZero) { return polarity; }
    if (v1 == Protocol::kOne) { return -polarity; }
    if (v2 == Protocol::kOne) { return polarity; }
    if (v1 == Protocol::kTwo) { return -polarity; }
    return polarity;
}

}  // namespace clarith
}  // namespace deepnum
