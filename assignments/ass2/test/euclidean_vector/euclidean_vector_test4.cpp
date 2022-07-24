#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Member Functions") {
	SECTION("double at(int) const") {
		auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
		auto a1 = comp6771::euclidean_vector(v.begin(), v.end());

		REQUIRE(a1.dimensions() == static_cast<int>(v.size()));

		for (int i = 0; i < a1.dimensions(); i++) {
			CHECK(a1.at(i) == v[static_cast<size_t>(i)]);
		}

		CHECK_THROWS_WITH(a1.at(5), "Index 5 is not valid for this euclidean_vector object");
	}

	SECTION("double& at(int)") {
		auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
		auto a1 = comp6771::euclidean_vector(v.begin(), v.end());

		REQUIRE(a1.dimensions() == static_cast<int>(v.size()));

		for (int i = 0; i < a1.dimensions(); i++) {
			CHECK(a1.at(i) == v[static_cast<size_t>(i)]);
			a1.at(i) = 0.0;
		}
		for (int i = 0; i < a1.dimensions(); i++) {
			CHECK(a1.at(i) == 0.0);
		}

		CHECK_THROWS_WITH(a1.at(5), "Index 5 is not valid for this euclidean_vector object");
	}

	SECTION("int dimensions()") {
		auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
		auto a1 = comp6771::euclidean_vector(v.begin(), v.end());
		auto a2 = comp6771::euclidean_vector(32);

		REQUIRE(a1.dimensions() == static_cast<int>(v.size()));
		REQUIRE(a2.dimensions() == 32);
	}
}
