// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include <algorithm>
#include <cassert>
#include <cmath>
#include <comp6771/euclidean_vector.hpp>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>

namespace comp6771 {
	// Implement solution here
	auto euclidean_vector::operator=(euclidean_vector const& src) noexcept -> euclidean_vector& {
		auto a_copy = euclidean_vector(src);
		std::swap(a_copy.dimension_, this->dimension_);
		std::swap(a_copy.magnitude_, this->magnitude_);
		return *this;
	}

	auto euclidean_vector::operator=(euclidean_vector&& trg) noexcept -> euclidean_vector& {
		auto a_copy = euclidean_vector(std::move(trg));
		std::swap(a_copy.dimension_, this->dimension_);
		std::swap(a_copy.magnitude_, this->magnitude_);
		return *this;
	}

	auto euclidean_vector::operator[](int idx) const noexcept -> double {
		assert(static_cast<size_t>(idx) < this->dimension_ && idx >= 0);
		return this->magnitude_[static_cast<size_t>(idx)];
	}

	auto euclidean_vector::operator[](int idx) noexcept -> double& {
		assert(static_cast<size_t>(idx) < this->dimension_ && idx >= 0);
		return this->magnitude_[static_cast<size_t>(idx)];
	}

	auto euclidean_vector::operator+() noexcept -> euclidean_vector {
		auto a_copy = euclidean_vector(*this);
		return a_copy;
	}

	auto euclidean_vector::operator-() noexcept -> euclidean_vector {
		auto a_copy = euclidean_vector(*this);
		std::transform(a_copy.magnitude_.get(),
		               a_copy.magnitude_.get() + a_copy.dimension_,
		               a_copy.magnitude_.get(),
		               std::negate<>());
		return a_copy;
	}

	auto euclidean_vector::operator+=(euclidean_vector const& other) -> euclidean_vector& {
		if (this->dimension_ != other.dimension_) {
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(this->dimension_)
			                             + ") and RHS(" + std::to_string(other.dimension_)
			                             + ") do not match");
		}
		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + this->dimension_,
		               other.magnitude_.get(),
		               this->magnitude_.get(),
		               std::plus<>());
		return *this;
	}

	auto euclidean_vector::operator-=(euclidean_vector const& other) -> euclidean_vector& {
		if (this->dimension_ != other.dimension_) {
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(this->dimension_)
			                             + ") and RHS(" + std::to_string(other.dimension_)
			                             + ") do not match");
		}
		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + this->dimension_,
		               other.magnitude_.get(),
		               this->magnitude_.get(),
		               std::minus<>());
		return *this;
	}

	auto euclidean_vector::operator*=(double scalar) noexcept -> euclidean_vector& {
		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + this->dimension_,
		               this->magnitude_.get(),
		               [scalar](double& x) { return x * scalar; });
		return *this;
	}

	auto euclidean_vector::operator/=(double scalar) -> euclidean_vector& {
		if (scalar == 0) {
			throw euclidean_vector_error("Invalid vector division by 0");
		}
		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + this->dimension_,
		               this->magnitude_.get(),
		               [scalar](double& x) { return x / scalar; });
		return *this;
	}

	euclidean_vector::operator std::vector<double>() noexcept {
		std::vector<double> vector;
		std::copy(this->magnitude_.get(),
		          this->magnitude_.get() + this->dimension_,
		          std::back_inserter(vector));
		return vector;
	}

	euclidean_vector::operator std::list<double>() noexcept {
		std::list<double> list;
		std::copy(this->magnitude_.get(),
		          this->magnitude_.get() + this->dimension_,
		          std::back_inserter(list));
		return list;
	}

	[[nodiscard]] auto euclidean_vector::at(int idx) const -> double {
		if (idx < 0 || idx >= static_cast<int>(this->dimension_)) {
			throw euclidean_vector_error("Index " + std::to_string(idx)
			                             + " is not valid for this euclidean_vector object");
		}
		return this->magnitude_[static_cast<size_t>(idx)];
	}

	auto euclidean_vector::at(int idx) -> double& {
		if (idx < 0 || idx >= static_cast<int>(this->dimension_)) {
			throw euclidean_vector_error("Index " + std::to_string(idx)
			                             + " is not valid for this euclidean_vector object");
		}
		return this->magnitude_[static_cast<size_t>(idx)];
	}

	[[nodiscard]] auto euclidean_vector::dimensions() const noexcept -> int {
		return static_cast<int>(this->dimension_);
	}

	auto operator==(euclidean_vector const& a, euclidean_vector const& b) noexcept -> bool {
		if (a.dimensions() != b.dimensions()) {
			return false;
		}
		for (int i = 0; i < a.dimensions(); i++) {
			if (a.at(i) != b.at(i)) {
				return false;
			}
		}
		return true;
	}

	auto operator!=(euclidean_vector const& a, euclidean_vector const& b) noexcept -> bool {
		if (a.dimensions() != b.dimensions()) {
			return true;
		}
		for (int i = 0; i < a.dimensions(); i++) {
			if (a.at(i) != b.at(i)) {
				return true;
			}
		}
		return false;
	}

	auto operator+(euclidean_vector const& a, euclidean_vector const& b) -> euclidean_vector {
		auto a_copy = euclidean_vector(a);
		auto b_copy = euclidean_vector(b);
		return a_copy += b_copy;
	}

	auto operator-(euclidean_vector const& a, euclidean_vector const& b) -> euclidean_vector {
		auto a_copy = euclidean_vector(a);
		auto b_copy = euclidean_vector(b);
		return a_copy -= b_copy;
	}

	auto operator*(euclidean_vector const& a, double scalar) noexcept -> euclidean_vector {
		auto a_copy = euclidean_vector(a);
		return a_copy *= scalar;
	}

	auto operator*(double scalar, euclidean_vector const& a) noexcept -> euclidean_vector {
		auto a_copy = euclidean_vector(a);
		return a_copy *= scalar;
	}

	auto operator/(euclidean_vector const& a, double scalar) -> euclidean_vector {
		auto a_copy = euclidean_vector(a);
		return a_copy /= scalar;
	}

	auto operator<<(std::ostream& out, euclidean_vector const& in) noexcept -> std::ostream& {
		out << "[";
		for (int i = 0; i < in.dimensions(); i++) {
			if (i == in.dimensions() - 1) {
				out << std::to_string(in.at(i));
			}
			else {
				out << std::to_string(in.at(i)) << " ";
			}
		}
		out << "]";
		return out;
	}

	auto euclidean_norm(euclidean_vector const& v) noexcept -> double {
		if (v.dimensions() == 0) {
			return 0;
		}
		double norm = 0.0;
		for (int i = 0; i < v.dimensions(); i++) {
			norm += std::pow(v.at(i), 2);
		}
		return std::sqrt(norm);
	}

	auto unit(euclidean_vector const& v) -> euclidean_vector {
		if (v.dimensions() == 0) {
			throw euclidean_vector_error("euclidean_vector with no dimensions does not have a unit "
			                             "vector");
		}
		if (euclidean_norm(v) == 0) {
			throw euclidean_vector_error("euclidean_vector with zero euclidean normal does not have a "
			                             "unit vector");
		}
		double norm = euclidean_norm(v);
		return v / norm;
	}

	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
		if (x.dimensions() != y.dimensions()) {
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(x.dimensions())
			                             + ") and RHS(" + std::to_string(y.dimensions())
			                             + ") do not match");
		}
		double dot = 0.0;
		for (int i = 0; i < x.dimensions(); i++) {
			dot += x.at(i) * y.at(i);
		}
		return dot;
	}

} // namespace comp6771
