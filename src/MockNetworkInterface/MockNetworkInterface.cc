#include <random>
#include <thread>

#include "../includes/NetworkInterface.h"

std::chrono::milliseconds MockNetworkInterface::GetRandomLatency() {
  std::uniform_int_distribution dist(kMinLatency, kMaxLatency);
  return std::chrono::milliseconds(dist(rng_));
}

void MockNetworkInterface::Send(std::vector<uint8_t> /* data */) {
  const std::chrono::milliseconds latency = GetRandomLatency();
  std::this_thread::sleep_for(latency);
}

