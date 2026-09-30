//
// Turbo Ledger platform library — exact decimal money type.
//
// Stored as int64 micro-units (6 decimal places), mirroring NUMERIC(19,6)
// in the database. Floating point is never used for amounts.
//
#pragma once

#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace turbo {

class MoneyError : public std::runtime_error {
  public:
    explicit MoneyError(const std::string &what) : std::runtime_error(what) {}
};

class Money {
  public:
    static constexpr std::int64_t kScale = 1000000;  // 6 decimal places
    static constexpr int kDecimals = 6;

    Money() = default;

    /// From micro-units (exact).
    static Money fromMicros(std::int64_t micros) { return Money(micros); }

    /// From whole units (e.g. 150 -> 150.000000).
    static Money fromUnits(std::int64_t units);

    /// Parse "123", "-123.45", "0.000001". Rejects >6 decimals, floats-style
    /// exponents and garbage. Returns nullopt on invalid input.
    static std::optional<Money> parse(const std::string &text);

    [[nodiscard]] std::int64_t micros() const { return micros_; }
    [[nodiscard]] bool isZero() const { return micros_ == 0; }
    [[nodiscard]] bool isNegative() const { return micros_ < 0; }

    /// Canonical string, always with all 6 decimals stripped to minimal form
    /// when `trim` is true (e.g. "12.5"), or fixed 6 decimals otherwise.
    [[nodiscard]] std::string toString(bool trim = true) const;

    // ---- checked arithmetic (throws MoneyError on overflow) ---------------
    Money operator+(const Money &o) const;
    Money operator-(const Money &o) const;
    Money operator-() const;
    Money &operator+=(const Money &o) { *this = *this + o; return *this; }
    Money &operator-=(const Money &o) { *this = *this - o; return *this; }

    /// Multiply by an integer quantity (checked).
    Money times(std::int64_t factor) const;

    /// Multiply by a ratio (num/den) rounding half-even at micro precision.
    Money timesRatio(std::int64_t numerator, std::int64_t denominator) const;

    /// Round to `decimals` (0..6) using banker's rounding (half-even).
    Money roundTo(int decimals) const;

    /// Split into `parts` shares that sum exactly to this amount.
    /// Remainder micro-units are distributed to the first shares.
    std::vector<Money> allocate(int parts) const;

    auto operator<=>(const Money &) const = default;

  private:
    explicit Money(std::int64_t micros) : micros_(micros) {}
    std::int64_t micros_{0};
};

}  // namespace turbo
