#include <cmath>
#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Utility functions") {
	SECTION("auto euclidean_norm(euclidean_vector const& v) -> double") {
		auto a = comp6771::euclidean_vector(2);
		a[0] = 1;
		a[1] = 2;
		auto b = comp6771::euclidean_vector(2);
		b[0] = 1;
		b[1] = 2;

		auto c = comp6771::euclidean_norm(a);
		auto d = comp6771::euclidean_norm(b);
		REQUIRE(c == d);

		auto a1 = comp6771::euclidean_vector{-1, 0, 3, 9, 2};
		auto c1 = comp6771::euclidean_norm(a1);
		REQUIRE(c1 == std::sqrt(95));
	}

	SECTION("auto unit(euclidean_vector const& v) -> euclidean_vector") {
		auto a = comp6771::euclidean_vector(2);
		a[0] = 1;
		a[1] = 2;
		auto b = comp6771::euclidean_vector(2);
		b[0] = 1;
		b[1] = 2;

		auto c = comp6771::unit(a);
		auto d = comp6771::unit(b);
		REQUIRE(c == d);

		auto a1 = comp6771::euclidean_vector{-1, 0, 3, 9, 2};
		auto c1 = comp6771::unit(a1);
		CHECK(c1.at(0) == -1 / std::sqrt(95));
		CHECK(c1.at(1) == 0 / std::sqrt(95));
		CHECK(c1.at(2) == 3 / std::sqrt(95));
		CHECK(c1.at(3) == 9 / std::sqrt(95));
		CHECK(c1.at(4) == 2 / std::sqrt(95));

		auto const a2 = comp6771::euclidean_vector(0);
		CHECK_THROWS_WITH(comp6771::unit(a2),
		                  "euclidean_vector with no dimensions does not have a unit vector");
		a[0] = 0.0;
		a[1] = 0.0;
		CHECK_THROWS_WITH(comp6771::unit(a),
		                  "euclidean_vector with zero euclidean normal does not have a unit vector");
	}

	SECTION("auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double") {
		auto const a1 = comp6771::euclidean_vector(0);
		auto const a2 = comp6771::euclidean_vector();
		auto const a3 = comp6771::euclidean_vector{8989, 354.5456, 5647.005};
		auto const a4 = comp6771::euclidean_vector{8989.01};
		auto const a5 = comp6771::euclidean_vector{8989.01, 0, -1};
		auto const a6 = comp6771::euclidean_vector(3);

		CHECK(comp6771::dot(a1, a1) == 0);
		CHECK_THROWS_WITH(comp6771::dot(a1, a2), "Dimensions of LHS(0) and RHS(1) do not match");

		CHECK(comp6771::dot(a2, a2) == 0);

		CHECK(comp6771::dot(a4, a4) == Approx(8989.01 * 8989.01));

		CHECK(comp6771::dot(a3, a3) == Approx(8989 * 8989 + 354.5456 * 354.5456 + 5647.005 * 5647.005));

		CHECK(comp6771::dot(a3, a5) == Approx(8989 * 8989.01 + 0 + -5647.005));

		CHECK(comp6771::dot(a3, a6) == 0);

		CHECK(a1.dimensions() == 0);
		CHECK(a2.dimensions() == 1);
		CHECK(a3.dimensions() == 3);
		CHECK(a4.dimensions() == 1);
		CHECK(a5.dimensions() == 3);
		CHECK(a6.dimensions() == 3);

		CHECK(a2.at(0) == 0);

		CHECK(a3.at(0) == 8989);
		CHECK(a3.at(1) == 354.5456);
		CHECK(a3.at(2) == 5647.005);

		CHECK(a4.at(0) == 8989.01);

		CHECK(a5.at(0) == 8989.01);
		CHECK(a5.at(1) == 0);
		CHECK(a5.at(2) == -1);

		CHECK(a6.at(0) == 0);
		CHECK(a6.at(1) == 0);
		CHECK(a6.at(2) == 0);
	}
}
