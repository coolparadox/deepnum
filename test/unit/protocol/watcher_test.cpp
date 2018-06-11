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

namespace deepnum {
namespace clarith {
namespace protocol {

TEST_GROUP(WatcherTest) {
};

TEST(WatcherTest, ReturnsCopyOfInput) {
    LONGS_EQUAL(Protocol::kEnd, Watcher().Watch(Protocol::kEnd));
    LONGS_EQUAL(Protocol::kTwo, Watcher().Watch(Protocol::kTwo));
    LONGS_EQUAL(Protocol::kOne, Watcher().Watch(Protocol::kOne));
    LONGS_EQUAL(Protocol::kZero, Watcher().Watch(Protocol::kZero));
    LONGS_EQUAL(Protocol::kNeg, Watcher().Watch(Protocol::kNeg));
}

TEST(WatcherTest, ThrowsOnNonFinalEndMessage) {
    {
        Watcher watcher;
        watcher.Watch(Protocol::kEnd);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::kTwo));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::kEnd);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::kOne));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::kEnd);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::kZero));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::kEnd);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::kNeg));
    }
}

TEST(WatcherTest, ThrowsOnNonInitialNegMessage) {
    {
        Watcher watcher;
        watcher.Watch(Protocol::kEnd);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::kNeg));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::kTwo);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::kNeg));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::kOne);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::kNeg));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::kZero);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::kNeg));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::kNeg);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::kNeg));
    }
}

TEST(WatcherTest, ThrowsOnNonInitialZeroMessage) {
    {
        Watcher watcher;
        watcher.Watch(Protocol::kEnd);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::kZero));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::kTwo);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::kZero));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::kOne);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::kZero));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::kZero);
        CHECK_THROWS(ViolationError, watcher.Watch(Protocol::kZero));
    }
    {
        Watcher watcher;
        watcher.Watch(Protocol::kNeg);
        watcher.Watch(Protocol::kZero);
    }
}

TEST(WatcherTest, ThrowsOnTwoMessageFollowedByEndMessage) {
    Watcher watcher;
    watcher.Watch(Protocol::kTwo);
    CHECK_THROWS(ViolationError, watcher.Watch(Protocol::kEnd));
}

}  // namespace protocol
}  // namespace clarith
}  // namespace deepnum

