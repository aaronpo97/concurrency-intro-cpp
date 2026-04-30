#ifndef CONCURRENCY_INTRO_CPP_INCLUDES_CONSTANTS_H_
#define CONCURRENCY_INTRO_CPP_INCLUDES_CONSTANTS_H_

#include <cstdint>
#include <numbers>

/**
 * @file constants.h
 * @brief Global constants used across the small demo project.
 */
using real_t = float;
using int_t = std::int32_t;

static constexpr real_t kHalfCircleDegrees = 180.0;
static constexpr int_t kCount = 1'000'000;
static constexpr real_t kStep = (2.0 * std::numbers::pi) / kCount;

#endif  // CONCURRENCY_INTRO_CPP_INCLUDES_CONSTANTS_H_
