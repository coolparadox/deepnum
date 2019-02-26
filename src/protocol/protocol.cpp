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

#include "protocol.hpp"

#if TRACE
#include <stdexcept>
#endif  // TRACE

namespace deepnum
{
namespace clarith
{
namespace protocol
{

#if TRACE
std::ostream& operator<<(std::ostream& os, const Protocol& message)
{
    switch (message)
    {
        case Protocol::End:
            os << "End";
            break;
        case Protocol::Amplify:
            os << "Amplify";
            break;
        case Protocol::Uncover:
            os << "Uncover";
            break;
        case Protocol::Turn:
            os << "Turn";
            break;
        case Protocol::Reflect:
            os << "Reflect";
            break;
        case Protocol::Ground:
            os << "Ground";
            break;
        default:
            throw std::logic_error("unknown Protocol message");
    }
    return os;
}
#endif  // TRACE

}  // namespace protocol
}  // namespace clarith
}  // namespace deepnum

