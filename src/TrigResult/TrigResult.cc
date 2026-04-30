#include "../includes/TrigResult.h"

TrigResult::TrigResult(DegreesWrapper const degrees_wrapper)
    : degrees_(degrees_wrapper.degrees_),
      radians_(degrees_wrapper.to_radians()),
      sin_(std::sin(radians_)),
      cos_(std::cos(radians_)),
      tan_(std::tan(radians_)) {}


TrigResult::TrigResult(RadiansWrapper const radians_wrapper)
    : degrees_(radians_wrapper.to_degrees()),
      radians_(radians_wrapper.radians_),
      sin_(std::sin(radians_)),
      cos_(std::cos(radians_)),
      tan_(std::tan(radians_)) {}


[[nodiscard]] real_t TrigResult::DegreesWrapper::to_radians() const {
  return DegreesToRadians(degrees_);
}

[[nodiscard]] real_t TrigResult::RadiansWrapper::to_degrees() const {
  return RadiansToDegrees(radians_);
}


std::string TrigResult::ToString() const {
  return std::format("Degrees: {}, Radians: {}, Sin: {}, Cos: {}, Tan: {}",
                     degrees_, radians_, sin_, cos_, tan_);
}

std::ostream &operator<<(std::ostream &os, TrigResult const &trig_result) {
  return os << trig_result.ToString();
}

std::vector<uint8_t> TrigResult::Serialize() const {
  std::string stringified = ToString();
  return {stringified.begin(), stringified.end()};
}