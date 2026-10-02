#include "RateLimiter.h"

namespace gateway {

bool RateLimiter::allow(const std::string &key) {
    const auto now = std::chrono::steady_clock::now();
    std::lock_guard<std::mutex> lock(mutex_);

    if (buckets_.size() > kMaxBuckets) buckets_.clear();  // crude pressure valve

    auto [it, inserted] = buckets_.try_emplace(key, Bucket{burst_, now});
    auto &bucket = it->second;
    if (!inserted) {
        const double elapsed =
            std::chrono::duration<double>(now - bucket.last).count();
        bucket.tokens = std::min(burst_, bucket.tokens + elapsed * rate_);
        bucket.last = now;
    }
    if (bucket.tokens >= 1.0) {
        bucket.tokens -= 1.0;
        return true;
    }
    return false;
}

}  // namespace gateway
