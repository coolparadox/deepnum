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

#ifndef SRC_PROTOCOL_WATCHER_HPP_
#define SRC_PROTOCOL_WATCHER_HPP_

namespace deepnum
{
namespace clarith
{
namespace protocol
{

enum class Protocol;

/**
 * Check for Protocol correctness.
 * Track Protocol messages, checking for violation of its invariants.
 * \see Protocol
 */
class Watcher
{
 public:
    /**
     * Check one more message of a Protocol sequence for violation errors.
     * \param[in] message Next message of a Protocol sequence.
     * \return Copy of input parameter.
     * \throw ViolationError
     */
    Protocol Watch(Protocol message);

 private:
    bool primed_ { false };
    Protocol previous_;
};

}  // namespace protocol
}  // namespace clarith
}  // namespace deepnum

#endif  // SRC_PROTOCOL_WATCHER_HPP_
