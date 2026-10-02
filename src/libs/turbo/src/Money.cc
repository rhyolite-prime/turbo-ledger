#include "turbo/Money.h"

#include <cctype>
#include <cstdlib>
#include <limits>

namespace turbo {

namespace {
bool addOverflows(std::int64_t a, std::int64_t b, std::int64_t &out) {
    return __builtin_add_overflow(a, b, &out);
}
bool mulOverflows(std::int64_t a, std::int64_t b, std::int64_t &out) {
    return __builtin_mul_overflow(a, b, &out);
}
}  // namespace

Money Money::fromUnits(std::int64_t units) {
    std::int64_t micros;
    if (mulOverflows(units, kScale, micros)) throw MoneyError("money overflow in fromUnits");
    return Money(micros);
}

std::optional<Money> Money::parse(const std::string &text) {
    if (text.empty()) return std::nullopt;
    size_t i = 0;
    bool negative = false;
    if (text[i] == '+' || text[i] == '-') {
        negative = (text[i] == '-');
        ++i;
    }
    if (i >= text.size()) return std::nullopt;

    std::int64_t whole = 0;
    bool sawDigit = false;
    for (; i < text.size() && std::isdigit(static_cast<unsigned char>(text[i])); ++i) {
        sawDigit = true;
        if (whole > (std::numeric_limits<std::int64_t>::max() - 9) / 10) return std::nullopt;
        whole = whole * 10 + (text[i] - '0');
    }

    std::int64_t frac = 0;
    int fracDigits = 0;
    if (i < text.size() && text[i] == '.') {
        ++i;
        if (i >= text.size()) return std::nullopt;  // "12." is invalid
        for (; i < text.size() && std::isdigit(static_cast<unsigned char>(text[i])); ++i) {
            sawDigit = true;
            if (++fracDigits > kDecimals) return std::nullopt;  // too precise
            frac = frac * 10 + (text[i] - '0');
        }
    }
    if (i != text.size() || !sawDigit) return std::nullopt;

    for (int d = fracDigits; d < kDecimals; ++d) frac *= 10;

    std::int64_t micros;
    if (mulOverflows(whole, kScale, micros)) return std::nullopt;
    if (addOverflows(micros, frac, micros)) return std::nullopt;
    if (negative) micros = -micros;
    return Money(micros);
}

std::string Money::toString(bool trim) const {
    std::int64_t whole = micros_ / kScale;
    std::int64_t frac = micros_ % kScale;
    bool negative = micros_ < 0;
    if (negative) {
        whole = -whole;
        frac = -frac;
    }
    char fracBuf[8];
    std::snprintf(fracBuf, sizeof(fracBuf), "%06lld", static_cast<long long>(frac));
    std::string fracStr(fracBuf);
    if (trim) {
        while (fracStr.size() > 0 && fracStr.back() == '0') fracStr.pop_back();
    }
    std::string out = (negative ? "-" : "") + std::to_string(whole);
    if (!fracStr.empty()) out += "." + fracStr;
    return out;
}

Money Money::operator+(const Money &o) const {
    std::int64_t r;
    if (addOverflows(micros_, o.micros_, r)) throw MoneyError("money overflow in addition");
    return Money(r);
}

Money Money::operator-(const Money &o) const {
    std::int64_t r;
    if (addOverflows(micros_, -o.micros_, r)) throw MoneyError("money overflow in subtraction");
    return Money(r);
}

Money Money::operator-() const {
    if (micros_ == std::numeric_limits<std::int64_t>::min())
        throw MoneyError("money overflow in negation");
    return Money(-micros_);
}

Money Money::times(std::int64_t factor) const {
    std::int64_t r;
    if (mulOverflows(micros_, factor, r)) throw MoneyError("money overflow in times");
    return Money(r);
}

Money Money::timesRatio(std::int64_t numerator, std::int64_t denominator) const {
    if (denominator == 0) throw MoneyError("division by zero in timesRatio");
    // Use 128-bit intermediate to avoid overflow.
    __int128 wide = static_cast<__int128>(micros_) * numerator;
    __int128 q = wide / denominator;
    __int128 r = wide % denominator;
    // Half-even rounding on the remainder.
    __int128 twiceR = (r < 0 ? -r : r) * 2;
    __int128 absDen = denominator < 0 ? -static_cast<__int128>(denominator) : denominator;
    bool roundAway = twiceR > absDen || (twiceR == absDen && (q & 1) != 0);
    if (roundAway) q += ((wide < 0) != (denominator < 0)) ? -1 : 1;
    if (q > std::numeric_limits<std::int64_t>::max() || q < std::numeric_limits<std::int64_t>::min())
        throw MoneyError("money overflow in timesRatio");
    return Money(static_cast<std::int64_t>(q));
}

Money Money::roundTo(int decimals) const {
    if (decimals < 0 || decimals > kDecimals) throw MoneyError("invalid rounding scale");
    std::int64_t step = 1;
    for (int d = decimals; d < kDecimals; ++d) step *= 10;
    if (step == 1) return *this;
    std::int64_t q = micros_ / step;
    std::int64_t r = micros_ % step;
    std::int64_t twiceR = (r < 0 ? -r : r) * 2;
    bool roundAway = twiceR > step || (twiceR == step && (q & 1) != 0);
    if (roundAway) q += (micros_ < 0) ? -1 : 1;
    std::int64_t out;
    if (mulOverflows(q, step, out)) throw MoneyError("money overflow in roundTo");
    return Money(out);
}

std::vector<Money> Money::allocate(int parts) const {
    if (parts <= 0) throw MoneyError("allocate requires parts > 0");
    std::vector<Money> out;
    out.reserve(parts);
    std::int64_t base = micros_ / parts;
    std::int64_t remainder = micros_ % parts;
    std::int64_t sign = remainder < 0 ? -1 : 1;
    if (remainder < 0) remainder = -remainder;
    for (int i = 0; i < parts; ++i) {
        std::int64_t share = base + (i < remainder ? sign : 0);
        out.push_back(Money(share));
    }
    return out;
}

}  // namespace turbo
