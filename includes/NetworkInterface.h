//
// Created by aaronpo on 29/04/2026.
//

#ifndef CONCURRENCY_INTRO_CPP_INCLUDES_NETWORKINTERFACE_H_
#define CONCURRENCY_INTRO_CPP_INCLUDES_NETWORKINTERFACE_H_

#include <chrono>
#include <cstdint>
#include <random>
#include <vector>

/**
 * @file NetworkInterface.h
 * @brief Abstract network interface and a small mock implementation used for
 * testing and demonstration.
 */

class NetworkInterface {
 public:
  virtual ~NetworkInterface() = default;
  /**
   * @brief Sends raw bytes over the network.
   * @param data Byte vector to transmit.
   */
  virtual void Send(std::vector<uint8_t> data) = 0;
};

/**
 * @class MockNetworkInterface
 * @brief A deterministic mock that simulates network latency.
 */
class MockNetworkInterface : public NetworkInterface {
  std::mt19937_64 rng_;

  static constexpr uint64_t kMinLatency{50};
  static constexpr uint64_t kMaxLatency{150};

  /**
   * @brief Returns a pseudo-random latency between min_latency_ and
   * max_latency_.
   * @return Duration representing the simulated latency.
   */
  std::chrono::milliseconds GetRandomLatency();

 public:
  /**
   * @brief Simulate sending bytes over the network by sleeping for a
   * random duration.
   * @param data Byte vector to "send". The contents are ignored by the
   * mock.
   */
  void Send(std::vector<uint8_t> data) override;
};

#endif  // CONCURRENCY_INTRO_CPP_INCLUDES_NETWORKINTERFACE_H_
