#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>
#include <sstream>

TEST_CASE("Equal") {
	auto const v1 = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto const v2 = std::vector<double>{3.14, -2.189, 46.579, 0, 0};
	auto const v3 = std::vector<double>{3.14, -2.189, 46.579};

	auto const a1 = comp6771::euclidean_vector(v1.begin(), v1.end());
	auto const a2 = comp6771::euclidean_vector(v1.begin(), v1.end());
	auto const a3 = comp6771::euclidean_vector(v2.begin(), v2.end());
	auto const a4 = comp6771::euclidean_vector(v3.begin(), v3.end());
	auto const a5 = comp6771::euclidean_vector(0);

	CHECK(a1 == a2);
	CHECK(a2 == a1);
	CHECK_FALSE(a1 == a3);
	CHECK_FALSE(a1 == a4);
	CHECK_FALSE(a2 == a3);
	CHECK_FALSE(a2 == a4);

	CHECK_FALSE(a5 == a1);
	CHECK_FALSE(a5 == a3);

	CHECK(a1.dimensions() == 5);
	CHECK(a2.dimensions() == 5);

	for (int i = 0; i < static_cast<int>(v1.size()); i++) {
		CHECK(a1.at(i) == a2.at(i));
		CHECK(a1.at(i) == v1.at(static_cast<std::size_t>(i)));
		CHECK(a2.at(i) == v1.at(static_cast<std::size_t>(i)));
	}

	CHECK(a3.dimensions() == 5);
	for (int i = 0; i < static_cast<int>(v2.size()); i++) {
		CHECK(a3.at(i) == v2.at(static_cast<std::size_t>(i)));
	}

	CHECK(a4.dimensions() == 3);
	for (int i = 0; i < static_cast<int>(v3.size()); i++) {
		CHECK(a4.at(i) == v3.at(static_cast<std::size_t>(i)));
	}
}

TEST_CASE("Not Equal") {
	auto const v1 = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto const v2 = std::vector<double>{3.14, -2.189, 46.579, 0, 0};
	auto const v3 = std::vector<double>{3.14, -2.189, 46.579};

	auto const a1 = comp6771::euclidean_vector(v1.begin(), v1.end());
	auto const a2 = comp6771::euclidean_vector(v1.begin(), v1.end());
	auto const a3 = comp6771::euclidean_vector(v2.begin(), v2.end());
	auto const a4 = comp6771::euclidean_vector(v3.begin(), v3.end());
	auto const a5 = comp6771::euclidean_vector(0);

	CHECK_FALSE(a1 != a2);
	CHECK_FALSE(a2 != a1);
	CHECK(a1 != a3);
	CHECK(a1 != a4);
	CHECK(a2 != a3);
	CHECK(a2 != a4);

	CHECK(a5 != a1);
	CHECK(a5 != a3);

	CHECK(a1.dimensions() == 5);
	CHECK(a2.dimensions() == 5);

	for (int i = 0; i < static_cast<int>(v1.size()); i++) {
		CHECK(a1.at(i) == a2.at(i));
		CHECK(a1.at(i) == v1.at(static_cast<std::size_t>(i)));
		CHECK(a2.at(i) == v1.at(static_cast<std::size_t>(i)));
	}

	CHECK(a3.dimensions() == 5);
	for (int i = 0; i < static_cast<int>(v2.size()); i++) {
		CHECK(a3.at(i) == v2.at(static_cast<std::size_t>(i)));
	}

	CHECK(a4.dimensions() == 3);
	for (int i = 0; i < static_cast<int>(v3.size()); i++) {
		CHECK(a4.at(i) == v3.at(static_cast<std::size_t>(i)));
	}
}

TEST_CASE("Addition") {
	auto const a1 = comp6771::euclidean_vector{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto const a2 = comp6771::euclidean_vector{1, 2, 3, 4, 5};
	auto const a3 = comp6771::euclidean_vector(5);
	auto const a4 = comp6771::euclidean_vector(0);

	for (int i = 0; i < 5; i++) {
		CHECK(Approx((a1 + a2).at(i)) == (a1.at(i) + a2.at(i)));
	}

	for (int i = 0; i < 5; i++) {
		CHECK((a1 + a3).at(i) == a1.at(i));
	}

	for (int i = 0; i < 5; i++) {
		CHECK(Approx((a1 + a1).at(i)) == 2 * a1.at(i));
	}

	CHECK_THROWS_WITH(a1 + a4, "Dimensions of LHS(5) and RHS(0) do not match");

	CHECK((a4 + a4).dimensions() == 0);
}

TEST_CASE("Subtraction") {
	auto const a1 = comp6771::euclidean_vector{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto const a2 = comp6771::euclidean_vector{1, 2, 3, 4, 5};
	auto const a3 = comp6771::euclidean_vector(5);
	auto const a4 = comp6771::euclidean_vector(0);

	for (int i = 0; i < 5; i++) {
		CHECK(Approx((a1 - a2).at(i)) == (a1.at(i) - a2.at(i)));
	}

	for (int i = 0; i < 5; i++) {
		CHECK((a1 - a3).at(i) == a1.at(i));
	}

	for (int i = 0; i < 5; i++) {
		CHECK((a1 - a1).at(i) == 0);
	}

	CHECK_THROWS_WITH(a1 + a4, "Dimensions of LHS(5) and RHS(0) do not match");

	CHECK((a4 - a4).dimensions() == 0);
}

TEST_CASE("Multiply") {
	auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto const a1 = comp6771::euclidean_vector{v.begin(), v.end()};
	auto const a2 = comp6771::euclidean_vector(0);

	for (int i = 0; i < 5; i++) {
		CHECK(Approx((a1 * 3).at(i)) == 3 * v.at(static_cast<size_t>(i)));
	}

	for (int i = 0; i < 5; i++) {
		CHECK(Approx((12.3 * a1).at(i)) == 12.3 * v.at(static_cast<std::size_t>(i)));
	}

	CHECK((a2 * 64).dimensions() == 0);
}

TEST_CASE("Divide") {
	auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto const a1 = comp6771::euclidean_vector{v.begin(), v.end()};
	auto const a2 = comp6771::euclidean_vector(0);

	for (int i = 0; i < 5; i++) {
		CHECK(Approx((a1 / 3).at(i)) == v.at(static_cast<size_t>(i)) / 3);
	}

	CHECK((a2 / 64).dimensions() == 0);

	CHECK_THROWS_WITH(a1 / 0, "Invalid vector division by 0");
}

TEST_CASE("Output Stream") {
	auto sstream = std::stringstream();
	auto const a1 = comp6771::euclidean_vector{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto const a2 = comp6771::euclidean_vector(0);

	sstream << a2;
	CHECK(sstream.str() == "[]");
	sstream.str("");
	sstream << a1;
	CHECK(sstream.str() == "[3.140000 -2.189000 46.579000 1234.567800 0.000000]");
}
