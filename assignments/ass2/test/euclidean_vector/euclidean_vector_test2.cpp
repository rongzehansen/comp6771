#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Constructors") {
	SECTION("euclidean_vector()") {
		auto const a1 = comp6771::euclidean_vector();
		auto const a2 = comp6771::euclidean_vector();

		REQUIRE(a1.dimensions() == 1);
		CHECK(a1.at(0) == 0.0);
		REQUIRE(a2.dimensions() == 1);
		CHECK(a2.at(0) == 0.0);

		CHECK_THROWS_WITH(a1.at(1), "Index 1 is not valid for this euclidean_vector object");
		CHECK_THROWS_WITH(a2.at(1), "Index 1 is not valid for this euclidean_vector object");
	}

	SECTION("euclidean_vector(int)") {
		auto const a1 = comp6771::euclidean_vector(0);
		auto const a2 = comp6771::euclidean_vector(3);

		REQUIRE(a1.dimensions() == 0);
		REQUIRE(a2.dimensions() == 3);
		CHECK(a2.at(0) == 0.0);
		CHECK(a2.at(1) == 0.0);
		CHECK(a2.at(2) == 0.0);

		CHECK_THROWS_WITH(a1.at(0), "Index 0 is not valid for this euclidean_vector object");
		CHECK_THROWS_WITH(a2.at(3), "Index 3 is not valid for this euclidean_vector object");
	}

	SECTION("euclidean_vector(int, double)") {
		auto const a1 = comp6771::euclidean_vector(0, 1.1);
		auto const a2 = comp6771::euclidean_vector(3, 3.3);

		REQUIRE(a1.dimensions() == 0);
		REQUIRE(a2.dimensions() == 3);
		CHECK(a2.at(0) == 3.3);
		CHECK(a2.at(1) == 3.3);
		CHECK(a2.at(2) == 3.3);

		CHECK_THROWS_WITH(a1.at(0), "Index 0 is not valid for this euclidean_vector object");
		CHECK_THROWS_WITH(a2.at(3), "Index 3 is not valid for this euclidean_vector object");
	}

	SECTION("euclidean_vector(std::vector<double>::const_iterator, "
	        "std::vector<double>::const_iterator)") {
		auto const v1 = std::vector<double>{1.0, 2.0, 3.0};
		auto const v2 = std::vector<double>{};
		auto const a1 = comp6771::euclidean_vector(v1.begin(), v1.end());
		auto const a2 = comp6771::euclidean_vector(v2.begin(), v2.end());

		REQUIRE(a1.dimensions() == 3);
		CHECK(a1.at(0) == 1.0);
		CHECK(a1.at(1) == 2.0);
		CHECK(a1.at(2) == 3.0);
		REQUIRE(a2.dimensions() == 0);

		CHECK_THROWS_WITH(a1.at(3), "Index 3 is not valid for this euclidean_vector object");
		CHECK_THROWS_WITH(a2.at(0), "Index 0 is not valid for this euclidean_vector object");
	}

	SECTION("euclidean_vector(std::initializer_list<double>)") {
		auto const a1 = comp6771::euclidean_vector{1.0, 2.0, 3.0};
		auto const a2 = comp6771::euclidean_vector{};

		REQUIRE(a1.dimensions() == 3);
		CHECK(a1.at(0) == 1.0);
		CHECK(a1.at(1) == 2.0);
		CHECK(a1.at(2) == 3.0);
		REQUIRE(a2.dimensions() == 1);
		CHECK(a2.at(0) == 0.0);

		CHECK_THROWS_WITH(a1.at(3), "Index 3 is not valid for this euclidean_vector object");
		CHECK_THROWS_WITH(a2.at(1), "Index 1 is not valid for this euclidean_vector object");
	}
}

TEST_CASE("Copy Constructor") {
	auto a2 = comp6771::euclidean_vector{4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};

	REQUIRE(a2.dimensions() == 7);
	CHECK(a2.at(0) == 4.0);
	CHECK(a2.at(1) == 5.0);
	CHECK(a2.at(2) == 6.0);
	CHECK(a2.at(3) == 7.0);
	CHECK(a2.at(4) == 8.0);
	CHECK(a2.at(5) == 9.0);
	CHECK(a2.at(6) == 10.0);

	auto a1 = comp6771::euclidean_vector(a2);
	REQUIRE(a1.dimensions() == 7);
	CHECK(a1.at(0) == 4.0);
	CHECK(a1.at(1) == 5.0);
	CHECK(a1.at(2) == 6.0);
	CHECK(a1.at(3) == 7.0);
	CHECK(a1.at(4) == 8.0);
	CHECK(a1.at(5) == 9.0);
	CHECK(a1.at(6) == 10.0);
	CHECK(a1 == a2);

	CHECK_THROWS_WITH(a1.at(7), "Index 7 is not valid for this euclidean_vector object");
	CHECK_THROWS_WITH(a2.at(7), "Index 7 is not valid for this euclidean_vector object");
}

TEST_CASE("Move Constructor") {
	auto a1 = comp6771::euclidean_vector{1.0, 2.0, 3.0};

	REQUIRE(a1.dimensions() == 3);
	CHECK(a1.at(0) == 1.0);
	CHECK(a1.at(1) == 2.0);
	CHECK(a1.at(2) == 3.0);

	auto a2 = comp6771::euclidean_vector(std::move(a1));
	REQUIRE(a2.dimensions() == 3);
	CHECK(a2.at(0) == 1.0);
	CHECK(a2.at(1) == 2.0);
	CHECK(a2.at(2) == 3.0);
	// NOLINTNEXTLINE(bugprone-use-after-move)
	CHECK(a1.dimensions() == 0);
	// NOLINTNEXTLINE(bugprone-use-after-move)
	CHECK(a1 != a2);

	CHECK_THROWS_WITH(a2.at(4), "Index 4 is not valid for this euclidean_vector object");
	// NOLINTNEXTLINE(bugprone-use-after-move)
	CHECK_THROWS_WITH(a1.at(0), "Index 0 is not valid for this euclidean_vector object");
}
