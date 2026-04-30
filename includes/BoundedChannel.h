//
// Created by aaronpo on 29/04/2026.
//

#ifndef CONCURRENCY_INTRO_CPP_INCLUDES_BOUNDEDCHANNEL_H_
#define CONCURRENCY_INTRO_CPP_INCLUDES_BOUNDEDCHANNEL_H_

#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>
#include <cstddef>

/**
 * @file BoundedChannel.h
 * @brief A thread-safe, bounded multi-producer/multi-consumer channel.
 */

// ---------------------------------------------------------------------------
// BoundedChannel<T>
//
// Models a synchronous channel with a fixed-capacity internal buffer.
// Producers block when the buffer is full (backpressure).
// Consumers block when the buffer be empty.
// Calling close() unblocks all waiting threads and signals exhaustion.
// ---------------------------------------------------------------------------
template <typename T>
class BoundedChannel {

  // -------------------------------------------------------------------------
  // Internal state — all access must be guarded by mutex_.
  // -------------------------------------------------------------------------

  std::queue<T> queue_;

  std::mutex mutex_;

  std::condition_variable not_full_;

  std::condition_variable not_empty_;

  std::size_t capacity_;

  bool closed_ = false;

 public:

  /**
   * @brief Construct a bounded channel with the given capacity.
   * @param capacity Maximum number of items the channel may hold.
   */
  explicit BoundedChannel(std::size_t capacity) : capacity_(capacity) {}

  /**
   * @brief Send an item into the channel. Blocks when the channel is full.
   * @param item Move-only item to enqueue.
   */
  void Send(T item);

  /**
   * @brief Receive an item from the channel. Blocks when the channel is
   * empty.
   * @return std::optional<T> containing the item, or std::nullopt when the
   * channel is closed and drained.
   */
  std::optional<T> Receive();

  /**
   * @brief Close the channel and unblock all waiting threads. Idempotent.
   */
  void close();
};

// Include the template implementation
#include "BoundedChannel.tcc"

#endif  // CONCURRENCY_INTRO_CPP_INCLUDES_BOUNDEDCHANNEL_H_
