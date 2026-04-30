#include <cmath>
#include <cstdint>
#include <format>
#include <fstream>
#include <iostream>
#include <numbers>
#include <thread>
#include <vector>

int main() {
  constexpr uint64_t count = 1'000'000;
  constexpr double step = (2.0 * std::numbers::pi) / count;

  std::vector<double> sines(count);
  std::vector<double> cosines(count);
  std::vector<double> tangents(count);

  std::thread t_sin([&]() {
    for (uint64_t i = 0; i < count; ++i) sines[i] = std::sin(i * step);
  });

  std::thread t_cos([&]() {
    for (uint64_t i = 0; i < count; ++i) cosines[i] = std::cos(i * step);
  });

  std::thread t_tan([&]() {
    for (uint64_t i = 0; i < count; ++i) tangents[i] = std::tan(i * step);
  });

  t_sin.join();
  t_cos.join();
  t_tan.join();

  for (uint64_t i = 0; i < count; ++i) {
    std::cout << std::format("sin({:.2f}) = {:.10f}\ncos({:.2f}) = {:.10f}\ntan({:.2f}) = {:.10f}\n\n",
                             i * step, sines[i], i * step, cosines[i], i * step, tangents[i]);
  }
  return 0;
}
