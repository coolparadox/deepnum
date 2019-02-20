/*
 * Copyright 2018 Rafael Lorandi <coolparadox@gmail.com>
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

#include "watcher.hpp"

#include "protocol.hpp"
#include "violation_error.hpp"

namespace deepnum
{
namespace clarith
{
namespace protocol
{

Protocol Watcher::Watch(Protocol message)
{
    if (!primed_)
    {
        primed_ = true;
        previous_ = message;
        return message;
    }
    if (previous_ == Protocol::End && message != Protocol::End)
    {
        throw ViolationError("forbidden non final '0'");
    }
    switch (message)
    {
        case Protocol::End:
            switch (previous_)
            {
                case Protocol::Amplify:
                    throw ViolationError("forbidden '20' sequence");
            }
            break;
        case Protocol::Turn:
            throw ViolationError("forbidden non initial '/'");
        case Protocol::Reflect:
            throw ViolationError("forbidden non initial '-'");
        case Protocol::Ground:
            throw ViolationError("forbidden non initial '-/'");

    }
    previous_ = message;
    return message;
}

}  // namespace protocol
}  // namespace clarith
}  // namespace deepnum
