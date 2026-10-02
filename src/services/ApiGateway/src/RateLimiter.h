//
// ApiGateway — per-key token bucket rate limiter (in-memory).
//
// Keys are "tenant|ip". The store is bounded; when Redis is configured this
// component can be swapped for a Redis-backed implementation with the same
// interface (Phase 8 hardening).
//
#pragma once

#include <chrono>
#include <mutex>
#include <string>
#include <unordered_map>

namespace gateway {

class RateLimiter {
  public:
    RateLimiter(double tokensPerSecond, double burst)
        : rate_(tokensPerSecond), burst_(burst) {}

    /// Returns true when the request is allowed.
    bool allow(const std::string &key);

  private:
    struct Bucket {
        double tokens;
        std::chrono::steady_clock::time_point last;
    };

    double rate_;
    double burst_;
    std::mutex mutex_;
    std::unordered_map<std::string, Bucket> buckets_;

    static constexpr size_t kMaxBuckets = 100000;
};

}  // namespace gateway
