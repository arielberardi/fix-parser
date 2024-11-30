#pragma once

#include <string>

#include "FIX/DataTypes.h"

namespace FIX {

class StandardTrailer {
 public:
  StandardTrailer() = default;

  StandardTrailer(const FIX::FieldsVector& message) noexcept;

  [[nodiscard]] FIX::FieldsVector toVector();

  [[nodiscard]] std::string getChecksum() const noexcept;
  void setChecksum(const std::string& checksum) noexcept;

 private:
  std::string m_checkSum;
};

}  // namespace FIX