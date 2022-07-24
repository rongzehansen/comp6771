#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <algorithm>
#include <iterator>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what)
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// Constructors
		// Default Constructor
		euclidean_vector() noexcept {
			dimension_ = 1;
			// NOLINTNEXTLINE(modernize-avoid-c-arrays)
			magnitude_ = std::make_unique<double[]>(1);
			magnitude_[0] = 0.0;
		};

		// Single-argument Constructor
		explicit euclidean_vector(int dimension) noexcept {
			dimension_ = static_cast<size_t>(dimension);
			// NOLINTNEXTLINE(modernize-avoid-c-arrays)
			magnitude_ = std::make_unique<double[]>(dimension_);
			std::fill_n(magnitude_.get(), dimension, 0.0);
		};

		// Constructor
		euclidean_vector(int dimension, double magnitude) noexcept {
			dimension_ = static_cast<size_t>(dimension);
			// NOLINTNEXTLINE(modernize-avoid-c-arrays)
			magnitude_ = std::make_unique<double[]>(dimension_);
			std::fill_n(magnitude_.get(), dimension, magnitude);
		};
		euclidean_vector(std::vector<double>::const_iterator first,
		                 std::vector<double>::const_iterator last) noexcept {
			dimension_ = static_cast<size_t>(std::distance(first, last));
			// NOLINTNEXTLINE(modernize-avoid-c-arrays)
			magnitude_ = std::make_unique<double[]>(dimension_);
			std::copy(first, last, magnitude_.get());
		};
		euclidean_vector(std::initializer_list<double> magnitudes) noexcept {
			dimension_ = magnitudes.size();
			// NOLINTNEXTLINE(modernize-avoid-c-arrays)
			magnitude_ = std::make_unique<double[]>(dimension_);
			std::copy(magnitudes.begin(), magnitudes.end(), magnitude_.get());
		};

		// Copy Constructor
		euclidean_vector(euclidean_vector const& src) noexcept {
			dimension_ = src.dimension_;
			// NOLINTNEXTLINE(modernize-avoid-c-arrays)
			magnitude_ = std::make_unique<double[]>(dimension_);
			std::copy(src.magnitude_.get(), src.magnitude_.get() + src.dimension_, magnitude_.get());
		};

		// Move Constructor
		euclidean_vector(euclidean_vector&& trg) noexcept {
			dimension_ = std::exchange(trg.dimension_, 0);
			magnitude_ = std::move(trg.magnitude_);
		};

		// Destructor
		~euclidean_vector() = default;

		// Operations
		// Copy Assignment
		auto operator=(euclidean_vector const& src) noexcept -> euclidean_vector&;
		// Move Assignment
		auto operator=(euclidean_vector&& trg) noexcept -> euclidean_vector&;
		// Subscript
		auto operator[](int idx) const noexcept -> double;
		auto operator[](int idx) noexcept -> double&;
		// Unary plus
		auto operator+() noexcept -> euclidean_vector;
		// Negation
		auto operator-() noexcept -> euclidean_vector;
		// Compound Addition
		auto operator+=(euclidean_vector const& other) -> euclidean_vector&;
		// Compound Subtraction
		auto operator-=(euclidean_vector const& other) -> euclidean_vector&;
		// Compound Multiplication
		auto operator*=(double scalar) noexcept -> euclidean_vector&;
		// Compound Division
		auto operator/=(double scalar) -> euclidean_vector&;
		// Vector Type Conversion
		explicit operator std::vector<double>() noexcept;
		// List Type Conversion
		explicit operator std::list<double>() noexcept;

		// Member Functions
		[[nodiscard]] auto at(int idx) const -> double;
		auto at(int idx) -> double&;
		[[nodiscard]] auto dimensions() const noexcept -> int;

		// Friends
		// Equal
		friend auto operator==(euclidean_vector const& a, euclidean_vector const& b) noexcept -> bool;
		// Not Equal
		friend auto operator!=(euclidean_vector const& a, euclidean_vector const& b) noexcept -> bool;
		// Addition
		friend auto operator+(euclidean_vector const& a, euclidean_vector const& b) -> euclidean_vector;
		// Subtraction
		friend auto operator-(euclidean_vector const& a, euclidean_vector const& b) -> euclidean_vector;
		// Multiply
		friend auto operator*(euclidean_vector const& a, double scalar) noexcept -> euclidean_vector;
		friend auto operator*(double scalar, euclidean_vector const& a) noexcept -> euclidean_vector;
		// Divide
		friend auto operator/(euclidean_vector const& a, double scalar) -> euclidean_vector;
		// Output Stream
		friend auto operator<<(std::ostream& out, euclidean_vector const& in) noexcept -> std::ostream&;

	private:
		size_t dimension_;
		// ass2 spec requires we use std::unique_ptr<double[]>
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitude_;
	};

	// Utility functions
	auto euclidean_norm(euclidean_vector const& v) noexcept -> double;
	auto unit(euclidean_vector const& v) -> euclidean_vector;
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;

} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
