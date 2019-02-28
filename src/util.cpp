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

#include "tracelog.h"

using deepnum::clarith::protocol::Protocol;

namespace deepnum
{
namespace clarith
{

int Util::Compare(Number* n1, Number* n2)
{
    traceloc("comparing " << n1 << " and " << n2);
    Protocol v1, v2;
    int polarity = 1;
    while (true)
    {
        traceloc("querying " << n1);
        v1 = n1->Egest();
        traceloc("got " << v1 << " from " << n1);
        traceloc("querying " << n2);
        v2 = n2->Egest();
        traceloc("got " << v2 << " from " << n2);
        if (v1 == Protocol::End && v2 == Protocol::End) { goto RETURN_ZERO; }
        if (v1 != v2) { break; }
        if (v1 == Protocol::Uncover || v1 == Protocol::Turn || v1 == Protocol::Reflect) { polarity *= -1; }
    }

    if (v1 == Protocol::Ground) { goto RETURN_NEG_POLARITY; }
    if (v2 == Protocol::Ground) { goto RETURN_POS_POLARITY; }

    if (v1 == Protocol::Reflect) { goto RETURN_NEG_POLARITY; }
    if (v2 == Protocol::Reflect) { goto RETURN_POS_POLARITY; }

    if (v1 == Protocol::Turn) { goto RETURN_POS_POLARITY; }
    if (v2 == Protocol::Turn) { goto RETURN_NEG_POLARITY; }

    if (v1 == Protocol::Uncover) { goto RETURN_POS_POLARITY; }
    if (v2 == Protocol::Uncover) { goto RETURN_NEG_POLARITY; }

    if (v1 == Protocol::Amplify) { goto RETURN_POS_POLARITY; }

RETURN_NEG_POLARITY:
    delete n1;
    delete n2;
    traceloc(n1 << " is " << (polarity < 0 ? "greater" : "lesser") << " than " << n2);
    return -polarity;

RETURN_POS_POLARITY:
    delete n1;
    delete n2;
    traceloc(n1 << " is " << (polarity > 0 ? "greater" : "lesser") << " than " << n2);
    return polarity;

RETURN_ZERO:
    delete n1;
    delete n2;
    traceloc(n1 << " is equal to " << n2);
    return 0;

}

}  // namespace clarith
}  // namespace deepnum
