#include <chrono>
#include <format>
#include <print>
#include <thread>

#include "../includes/BoundedChannel.h"
#include "../includes/NetworkInterface.h"
#include "../includes/TrigResult.h"
#include "spdlog/spdlog.h"

static constexpr size_t kMaxChannels = 512;

class Timer {
  std::chrono::time_point<std::chrono::steady_clock> start =
      std::chrono::steady_clock::now();
public:
  [[nodiscard]] std::chrono::nanoseconds elapsed() const {
    return std::chrono::steady_clock::now() - start;
  }
  void reset() {
    start = std::chrono::steady_clock::now();
  }
};

int main() {
  std::unique_ptr<NetworkInterface> network =
      std::make_unique<MockNetworkInterface>();

  BoundedChannel<std::vector<uint8_t>> trigChannel(kMaxChannels);
  BoundedChannel<std::string>          messageChannel(kMaxChannels);

  // Phase 1 — compute and enqueue trigonometric results
  std::jthread trigProducer([&] {
      for (int step = 0; step <= 3600; ++step) {
          const real_t i = step / real_t{10};
          TrigResult result(TrigResult::DegreesWrapper{i});
          trigChannel.Send(result.Serialize());
      }
      trigChannel.close();
  });

  // Phase 2 — drain trigChannel, send over network, enqueue log messages
  std::jthread networkProducer([&] {
      Timer timer;
      while (auto payload = trigChannel.Receive()) {
          network->Send(std::move(*payload));
          auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                        timer.elapsed()).count();
          messageChannel.Send(std::format("Sent data. Took {} ms", ms));
          timer.reset();
      }
      messageChannel.close();
  });

  // Phase 3 — drain messageChannel and log each entry
  std::jthread loggerConsumer([&] {
      while (auto msg = messageChannel.Receive()) {
          spdlog::info("{}", *msg);
      }
  });

  return 0;
}