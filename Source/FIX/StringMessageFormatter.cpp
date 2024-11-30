#include "FIX/StringMessageFormatter.h"

#include <stdexcept>
#include <vector>

#include "Components/StandardHeader.h"
#include "FIX/DataTypes.h"
#include "FIX/TagsNum.h"

void FIX::StringMessageFormatter::format(const FIX::FieldsVector& messageVector,
                                         const char delimiter) {
  std::string version{};
  std::string body{""};

  for (auto& pair : messageVector) {
    if (pair.first == 8) {
      version = pair.second;
      continue;
    }

    if (pair.first == 9 || pair.first == 10) {
      continue;
    }

    body += std::to_string(pair.first) + "=" + pair.second + delimiter;
  }

  if (version.empty()) {
    throw std::runtime_error("Invalid message: missing version");
  }

  m_message = "8=" + version + delimiter;
  m_message += "9=" + std::to_string(body.length()) + delimiter;
  m_message += body;

  std::string checksum = calculateChecksum(m_message, delimiter);
  m_message += "10=" + checksum + delimiter;
}

[[nodiscard]] std::string FIX::StringMessageFormatter::getMessage() const noexcept {
  return m_message;
}

[[nodiscard]] std::string FIX::StringMessageFormatter::calculateChecksum(
    std::string_view message, const char delimiter) noexcept {
  int checksum = 0;
  for (auto c : message) {
    if (c == delimiter) {
      checksum += '\001';
      continue;
    }

    checksum += c;
  }

  checksum = checksum & 0xFF;

  // Checksum must be a 3 digit value
  auto result = std::to_string(checksum);
  while (result.length() < 3) {
    result.insert(result.begin(), '0');
  }

  return result;
}