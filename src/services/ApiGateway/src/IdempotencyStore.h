//
// ApiGateway — idempotency-key replay store (in-memory, TTL-bounded).
//
// Money-moving POST/PUT requests carrying an Idempotency-Key header get
// exactly-once semantics at the edge:
//   * first request  -> marked in-flight, executed, response recorded
//   * concurrent dup -> 409 Conflict ("request in progress")
//   * later replay   -> stored response returned verbatim
//
#pragma once

#include <chrono>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>

namespace gateway {

struct StoredResponse {
    int statusCode{0};
    std::string contentType;
    std::string body;
};

class IdempotencyStore {
  public:
    explicit IdempotencyStore(std::chrono::seconds ttl = std::chrono::hours(24)) : ttl_(ttl) {}

    enum class BeginResult { kNew, kInFlight, kReplayed };

    /// Try to claim `key`. When kReplayed, `replay` holds the stored response.
    BeginResult begin(const std::string &key, StoredResponse &replay);

    /// Record the final upstream response for `key`.
    void complete(const std::string &key, StoredResponse response);

    /// Drop the in-flight claim (upstream failed hard; allow retry).
    void abandon(const std::string &key);

  private:
    struct Entry {
        bool inFlight{true};
        StoredResponse response;
        std::chrono::steady_clock::time_point storedAt;
    };

    void evictExpiredLocked();

    std::chrono::seconds ttl_;
    std::mutex mutex_;
    std::unordered_map<std::string, Entry> entries_;
    static constexpr size_t kMaxEntries = 200000;
};

}  // namespace gateway
