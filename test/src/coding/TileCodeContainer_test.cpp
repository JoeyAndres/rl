/**
 * rl - Reinforcement Learning
 * Copyright (C) 2016  Joey Andres<yeojserdna@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "rl"
#include "catch.hpp"

#ifdef ENABLE_DB

SCENARIO("TileCodeContainer, encapsulates the weight storage in tile code.",
         "[TileCodeContainer]") {
  GIVEN("Uninitialized underlying db") {
    WHEN("Created") {
      THEN("Schema is created") {
        rl::db::initialize();
      }
    }
  }

  GIVEN("Initialized underlying db") {
    WHEN("New TileCodeContainer instance is created with the "
           "id agnostic constructor") {
      rl::coding::TileCodeContainer<'i', 'd', '1'> tcc(1000, 0.0F);
      THEN("It is added in db") {
        tcc.delete2();
      }
    }

    WHEN("Terminate") {
      THEN("Connection is ceased.") {
        rl::db::terminate();
      }
    }
  }

  GIVEN("An inserted TileCodeContainer") {
    rl::coding::TileCodeContainer<'i', 'd', '2'> tcc(1000, 0.0F);

    WHEN("A member is accessed.") {
      THEN("It is first 0.0") {
        REQUIRE(tcc[0] == 0.0);
      }
    }

    WHEN("A member is modified") {
      THEN("It is modified") {
        tcc[0] = 69.0F;
        REQUIRE(tcc[0] == 69.0);
        REQUIRE(tcc[1] == 0.0);  // Sanity check.
      }
    }

    WHEN("TileCodeContainer is deleted") {
      tcc.delete2();
      THEN("id disappears") {
        // Not practically to query cassandra ourselves.
      }
    }
  }
}

#endif  // #ifdef ENABLE_DB
