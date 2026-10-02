#include "IdempotencyStore.h"

namespace gateway {

IdempotencyStore::BeginResult IdempotencyStore::begin(const std::string &key,
                                                      StoredResponse &replay) {
    const auto now = std::chrono::steady_clock::now();
    std::lock_guard<std::mutex> lock(mutex_);
    evictExpiredLocked();

    auto it = entries_.find(key);
    if (it == entries_.end()) {
        if (entries_.size() >= kMaxEntries) evictExpiredLocked();
        entries_[key] = Entry{true, {}, now};
        return BeginResult::kNew;
    }
    if (it->second.inFlight) return BeginResult::kInFlight;
    replay = it->second.response;
    return BeginResult::kReplayed;
}

void IdempotencyStore::complete(const std::string &key, StoredResponse response) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = entries_.find(key);
    if (it != entries_.end()) {
        it->second.inFlight = false;
        it->second.response = std::move(response);
        it->second.storedAt = std::chrono::steady_clock::now();
    }
}

void IdempotencyStore::abandon(const std::string &key) {
    std::lock_guard<std::mutex> lock(mutex_);
    entries_.erase(key);
}

void IdempotencyStore::evictExpiredLocked() {
    const auto now = std::chrono::steady_clock::now();
    for (auto it = entries_.begin(); it != entries_.end();) {
        if (!it->second.inFlight && now - it->second.storedAt > ttl_) {
            it = entries_.erase(it);
        } else {
            ++it;
        }
    }
}

}  // namespace gateway
