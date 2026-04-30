//
// Created by aaronpo on 29/04/2026.
//

//
// Created by aaronpo on 29/04/2026.
//

#ifndef CONCURRENCY_INTRO_CPP_INCLUDES_TRIG_H_
#define CONCURRENCY_INTRO_CPP_INCLUDES_TRIG_H_

#include <cmath>
#include <format>
#include <string>
#include <vector>
#include <ostream>

#include "constants.h"



/**
 * @brief Convert degrees to radians.
 *
 * @param degrees Angle in degrees.
 * @return Angle in radians.
 */
static constexpr real_t DegreesToRadians(const real_t degrees) {
  return degrees * (std::numbers::pi_v<real_t>/ kHalfCircleDegrees);
}

/**
 * @brief Convert radians to degrees.
 *
 * @param radians Angle in radians.
 * @return Angle in degrees.
 */
static constexpr real_t RadiansToDegrees(const real_t radians) {
  return radians * (std::numbers::pi / kHalfCircleDegrees);
}

/**
 * @class TrigResult
 * @brief Container for a set of trigonometric values computed from an angle.
 */
class TrigResult {
  real_t degrees_;
  real_t radians_;
  real_t sin_;
  real_t cos_;
  real_t tan_;

 public:
  /**
   * @brief Lightweight wrapper to construct from degrees.
   */
  struct DegreesWrapper {
    real_t degrees_;

    /**
     * @brief Convert the wrapped degrees value to radians.
     * @return Angle in radians.
     */
    [[nodiscard]] real_t to_radians() const;
  };

  /**
   * @brief Lightweight wrapper to construct from radians.
   */
  struct RadiansWrapper {
    real_t radians_;
    /**
     * @brief Convert the wrapped radians value to degrees.
     * @return Angle in degrees.
     */
    [[nodiscard]] real_t to_degrees() const;
  };

  /**
   * @brief Construct from a DegreesWrapper.
   * @param degrees_wrapper Degrees wrapper containing the input angle.
   */
  explicit TrigResult(DegreesWrapper degrees_wrapper);

  /**
   * @brief Construct from a RadiansWrapper.
   * @param radians_wrapper Radians wrapper containing the input angle.
   */
  explicit TrigResult(RadiansWrapper radians_wrapper);

  /**
   * @brief Convert the stored values to a human-readable string.
   * @return std::string containing the formatted values.
   */
  [[nodiscard]] std::string ToString() const;

  /**
   * @brief Serialize the string representation to a byte vector.
   * @return std::vector<uint8_t> containing the serialized bytes.
   */
  [[nodiscard]] std::vector<uint8_t> Serialize() const;
};

/**
 * @brief Stream insertion operator for TrigResult.
 * @param os Output stream reference.
 * @param trig_result TrigResult to be formatted.
 * @return Reference to the output stream.
 */
std::ostream &operator<<(std::ostream &os, TrigResult const &trig_result);

#endif  // CONCURRENCY_INTRO_CPP_INCLUDES_TRIG_H_
