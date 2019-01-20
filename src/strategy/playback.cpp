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

#include "protocol/protocol.hpp"
#include "strategy/infinity.hpp"
#include "strategy/exhaustion_error.hpp"
#include "strategy/unavailable_error.hpp"

#include "playback.hpp"

using deepnum::clarith::protocol::Protocol;

namespace deepnum
{
namespace clarith
{
namespace strategy
{

Playback::Playback(gsl::owner<std::forward_list<protocol::Protocol>*> sequence)
        : sequence_(sequence)
{
    if (!sequence_)
    {
        sequence_ = new std::forward_list<protocol::Protocol>();
    }
}

Playback::~Playback()
{
    delete sequence_;
}

Protocol Playback::Egest()
{
    if (sequence_->empty())
    {
        watcher_.Watch(Protocol::kEnd);
        throw ExhaustionError();
    }
    Protocol answer = sequence_->front();
    sequence_->pop_front();
    return watcher_.Watch(answer);
}

gsl::not_null<gsl::owner<Strategy*>> Playback::GetNewStrategy() const
{
    if (!sequence_->empty())
    {
        throw UnavailableError();
    }
    return gsl::not_null<gsl::owner<Infinity*>>(new Infinity());
}

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum

