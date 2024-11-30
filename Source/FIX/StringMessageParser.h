#pragma once

#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

#include "FIX/DataTypes.h"

namespace FIX {

class StringMessageParser {
 public:
  void parser(const std::string& message, const char delimiter);

  [[nodiscard]] FIX::FieldsVector getVector() const noexcept;

 private:
  void parseGroupFields(std::istringstream& stream, char delimiter, int groups);

  [[nodiscard]] int calculateCheckSum(std::string_view message, char delimiter) const noexcept;
  [[nodiscard]] int calculateLength(std::string_view message) const noexcept;

  [[nodiscard]] bool isGroup(int tag) const;

  [[nodiscard]] std::pair<int, std::string> parseKeyValueField(const std::string& field);

  FIX::FieldsVector m_fieldsVector{};
};

}  // namespace FIX