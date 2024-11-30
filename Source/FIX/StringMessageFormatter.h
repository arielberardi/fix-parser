#pragma once

#include <string>
#include <string_view>

#include "FIX/Components/StandardHeader.h"
#include "FIX/DataTypes.h"

namespace FIX {

class StringMessageFormatter {
 public:
  void format(const FIX::FieldsVector& messageVector, const char delimiter);

  [[nodiscard]] std::string getMessage() const noexcept;

 private:
  [[nodiscard]] std::string calculateChecksum(std::string_view message,
                                              const char delimiter) noexcept;

  std::string m_message{""};
  FIX::StandardHeader m_header{};
};

}  // namespace FIX