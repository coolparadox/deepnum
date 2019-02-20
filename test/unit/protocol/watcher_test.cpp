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

#include <CppUTest/TestHarness.h>

#include "protocol/protocol.hpp"
#include "protocol/violation_error.hpp"
#include "protocol/watcher.hpp"

namespace deepnum
{
namespace clarith
{
namespace protocol
{

TEST_GROUP(WatcherTest)
{
};

TEST(WatcherTest, ReturnsCopyOfInput)
{
    LONGS_EQUAL(Protocol::End, Watcher().Watch(Protocol::End));
    LONGS_EQUAL(Protocol::Amplify, Watcher().Watch(Protocol::Amplify));
    LONGS_EQUAL(Protocol::Uncover, Watcher().Watch(Protocol::Uncover));
    LONGS_EQUAL(Protocol::Turn, Watcher().Watch(Protocol::Turn));
    LONGS_EQUAL(Protocol::Reflect, Watcher().Watch(Protocol::Reflect));
    LONGS_EQUAL(Protocol::Ground, Watcher().Watch(Protocol::Ground));
}

TEST(WatcherTest, ThrowsOnNonFinalEnd)
{
    {
        Watcher watcher;
        watcher.Watch(Protocol::End);
        watcher.Watch(Protocol::End);
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::End);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Amplify));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::End);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Uncover));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::End);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Turn));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::End);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Reflect));
    }{
        Watcher watcher;
        watcher.Watch(Protocol::End);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Ground));
    }
}

TEST(WatcherTest, ThrowsOnFinalAmplify)
{
    Watcher watcher;
    watcher.Watch(Protocol::Amplify);
    CHECK_THROWS(ViolationError, watcher.Watch(Protocol::End));
}

TEST(WatcherTest, ThrowsOnNonInitialTurn)
{
    {
        Watcher watcher;
        watcher.Watch(Protocol::End);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Turn));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::Amplify);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Turn));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::Uncover);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Turn));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::Turn);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Turn));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::Reflect);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Turn));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::Ground);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Turn));
    }
}

TEST(WatcherTest, ThrowsOnNonInitialReflect)
{
    {
        Watcher watcher;
        watcher.Watch(Protocol::End);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Reflect));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::Amplify);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Reflect));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::Uncover);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Reflect));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::Turn);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Reflect));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::Reflect);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Reflect));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::Ground);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Reflect));
    }
}

TEST(WatcherTest, ThrowsOnNonInitialGround)
{
    {
        Watcher watcher;
        watcher.Watch(Protocol::End);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Ground));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::Amplify);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Ground));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::Uncover);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Ground));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::Turn);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Ground));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::Reflect);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Ground));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::Ground);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::Ground));
    }
}

}  // namespace protocol
}  // namespace clarith
}  // namespace deepnum

