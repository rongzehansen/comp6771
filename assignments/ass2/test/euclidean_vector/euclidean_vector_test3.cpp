#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Copy Assignment") {
	auto a1 = comp6771::euclidean_vector{1.0, 2.0, 3.0};
	auto a2 = comp6771::euclidean_vector{4.0, 5.0};

	REQUIRE(a1.dimensions() == 3);
	REQUIRE(a2.dimensions() == 2);

	a2 = a1;
	REQUIRE(a1.dimensions() == 3);
	REQUIRE(a2.dimensions() == 3);
	CHECK(a1 == a2);

	CHECK_THROWS_WITH(a1.at(3), "Index 3 is not valid for this euclidean_vector object");
	CHECK_THROWS_WITH(a2.at(3), "Index 3 is not valid for this euclidean_vector object");
}

TEST_CASE("Move Assignment") {
	auto a1 = comp6771::euclidean_vector{1.0, 2.0, 3.0};
	auto a2 = comp6771::euclidean_vector{4.0, 5.0};

	REQUIRE(a1.dimensions() == 3);
	REQUIRE(a2.dimensions() == 2);

	a1 = std::move(a2);
	REQUIRE(a1.dimensions() == 2);
	// NOLINTNEXTLINE(bugprone-use-after-move)
	REQUIRE(a2.dimensions() == 0);

	CHECK(a1 != a2);

	CHECK_THROWS_WITH(a2.at(0), "Index 0 is not valid for this euclidean_vector object");
	// NOLINTNEXTLINE(bugprone-use-after-move)
	CHECK_THROWS_WITH(a1.at(2), "Index 2 is not valid for this euclidean_vector object");
}

TEST_CASE("Subscript") {
	SECTION("double operator[](int idx) const noexcept") {
		auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
		auto a1 = comp6771::euclidean_vector(v.begin(), v.end());

		REQUIRE(a1.dimensions() == static_cast<int>(v.size()));

		for (int i = 0; i < a1.dimensions(); i++) {
			CHECK(a1[i] == v[static_cast<size_t>(i)]);
		}
	}

	SECTION("double& operator[](int idx) noexcept") {
		auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
		auto a1 = comp6771::euclidean_vector(v.begin(), v.end());

		REQUIRE(a1.dimensions() == static_cast<int>(v.size()));

		for (int i = 0; i < a1.dimensions(); i++) {
			CHECK(a1[i] == v[static_cast<size_t>(i)]);
			a1[i] = 0.0;
		}
		for (int i = 0; i < a1.dimensions(); i++) {
			CHECK(a1[i] == 0.0);
		}
	}
}

TEST_CASE("Unary plus") {
	auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto a1 = comp6771::euclidean_vector(v.begin(), v.end());

	REQUIRE(a1.dimensions() == static_cast<int>(v.size()));

	auto a2 = +a1;
	REQUIRE(a1 == a2);
	a1.at(0) = 0.0;
	REQUIRE(a1 != a2);
}

TEST_CASE("Negation") {
	auto a1 = comp6771::euclidean_vector{-6, 1, 0};
	auto a2 = comp6771::euclidean_vector{6, -1, 0};

	REQUIRE(a1.dimensions() == 3);

	CHECK(a1 == -a2);

	a1.at(0) = 0.0;
	a2.at(0) = 0.0;
	a1.at(1) = 0.0;
	a2.at(1) = 0.0;

	CHECK(a1 == -a2);
}

TEST_CASE("Compound Addition") {
	auto a1 = comp6771::euclidean_vector{1.0, 2.0, 3.0};
	auto a2 = comp6771::euclidean_vector{4.0, 5.0};
	auto a3 = comp6771::euclidean_vector{4.0, 5.0, -1.0};

	REQUIRE(a1.dimensions() != a2.dimensions());

	CHECK_THROWS_WITH(a1 += a2, "Dimensions of LHS(3) and RHS(2) do not match");
	a1 += a3;
	CHECK(a1.dimensions() == 3);
	CHECK(a1.at(0) == 5.0);
	CHECK(a1.at(1) == 7.0);
	CHECK(a1.at(2) == 2.0);
	CHECK(a3.at(0) == 4.0);
	CHECK(a3.at(1) == 5.0);
	CHECK(a3.at(2) == -1.0);
}

TEST_CASE("Compound Subtraction") {
	auto a1 = comp6771::euclidean_vector{1.0, 2.0, 3.0};
	auto a2 = comp6771::euclidean_vector{4.0, 5.0};
	auto a3 = comp6771::euclidean_vector{4.0, 5.0, -1.0};

	REQUIRE(a1.dimensions() != a2.dimensions());

	CHECK_THROWS_WITH(a1 += a2, "Dimensions of LHS(3) and RHS(2) do not match");
	a1 -= a3;
	CHECK(a1.dimensions() == 3);
	CHECK(a1.at(0) == -3.0);
	CHECK(a1.at(1) == -3.0);
	CHECK(a1.at(2) == 4.0);
	CHECK(a3.at(0) == 4.0);
	CHECK(a3.at(1) == 5.0);
	CHECK(a3.at(2) == -1.0);
}

TEST_CASE("Compound Multiplication") {
	auto a1 = comp6771::euclidean_vector{1.0, 2.0, 3.0};

	REQUIRE(a1.dimensions() == 3);

	a1 *= 3;
	CHECK(a1.dimensions() == 3);
	CHECK(a1.at(0) == 3.0);
	CHECK(a1.at(1) == 6.0);
	CHECK(a1.at(2) == 9.0);
	a1 *= -1;
	CHECK(a1.dimensions() == 3);
	CHECK(a1.at(0) == -3.0);
	CHECK(a1.at(1) == -6.0);
	CHECK(a1.at(2) == -9.0);
	a1 *= 0;
	CHECK(a1.dimensions() == 3);
	CHECK(a1.at(0) == 0.0);
	CHECK(a1.at(1) == 0.0);
	CHECK(a1.at(2) == 0.0);
}

TEST_CASE("Compound Division") {
	auto a1 = comp6771::euclidean_vector{1.0, 2.0, 3.0};

	REQUIRE(a1.dimensions() == 3);

	a1 /= 3;
	CHECK(a1.dimensions() == 3);
	CHECK(a1.at(0) == 1.0 / 3);
	CHECK(a1.at(1) == 2.0 / 3);
	CHECK(a1.at(2) == 3.0 / 3);
	a1 /= -1;
	CHECK(a1.dimensions() == 3);
	CHECK(a1.at(0) == -1.0 / 3);
	CHECK(a1.at(1) == -2.0 / 3);
	CHECK(a1.at(2) == -3.0 / 3);

	CHECK_THROWS_WITH(a1 /= 0, "Invalid vector division by 0");
}

TEST_CASE("Vector Type Conversion") {
	auto const v1 = std::vector<double>{0.0, 1.0, 2.0};
	auto const v2 = std::vector<double>{0.0, 1.0, 2.0, 3.0};
	auto a1 = comp6771::euclidean_vector{0.0, 1.0, 2.0};
	auto const vf = static_cast<std::vector<double>>(a1);

	REQUIRE(vf == v1);
	REQUIRE(vf != v2);
	for (int i = 0; i < a1.dimensions(); i++) {
		CHECK(a1.at(i) == v1[static_cast<size_t>(i)]);
	}
}

TEST_CASE("List Type Conversion") {
	auto const v1 = std::list<double>{0.0, 1.0, 2.0};
	auto const v2 = std::list<double>{0.0, 1.0, 2.0, 3.0};
	auto a1 = comp6771::euclidean_vector{0.0, 1.0, 2.0};
	auto lf = static_cast<std::list<double>>(a1);

	REQUIRE(lf == v1);
	REQUIRE(lf != v2);
	for (int i = 0; i < a1.dimensions(); i++) {
		CHECK(a1.at(i) == lf.front());
		lf.pop_front();
	}
}
