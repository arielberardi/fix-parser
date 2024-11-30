#include "FIX/StringMessageParser.h"

#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "FIX/DataTypes.h"
#include "FIX/TagsNum.h"

void FIX::StringMessageParser::parser(const std::string& message, const char delimiter) {
  // Assuming each fields is an average of 5 bytes we pre-reserve space for them
  m_fieldsVector.reserve(message.length() / 5);

  std::istringstream stream{message};
  std::string field{};

  while (std::getline(stream, field, delimiter)) {
    auto [key, value] = parseKeyValueField(field);

    if (value.empty()) {
      throw std::runtime_error("Invalid message: empty field");
    }

    if (key == 10 && calculateCheckSum(message, delimiter) != std::stoi(value)) {
      throw std::runtime_error("Invalid message: checksum has failed");
    }

    if (key == 9 && calculateLength(message) != std::stoi(value)) {
      throw std::runtime_error("Invalid message: length check failed");
    }

    m_fieldsVector.emplace_back(key, value);

    if (isGroup(key)) {
      parseGroupFields(stream, delimiter, std::stoi(value));
    }
  }
}

[[nodiscard]] FIX::FieldsVector FIX::StringMessageParser::getVector() const noexcept {
  return m_fieldsVector;
}

void FIX::StringMessageParser::parseGroupFields(std::istringstream& stream, char delimiter,
                                                int groups) {
  if (groups == 0) {
    return;
  }

  std::string field{};
  int groupCount = 0;
  int groupFirstKey = 0;
  int groupLastKey = 0;
  int lastKey = 0;

  while (std::getline(stream, field, delimiter)) {
    auto [key, value] = parseKeyValueField(field);

    if (groupFirstKey == 0) {
      groupFirstKey = key;
    } else if (groupLastKey == 0 && groupFirstKey == key) {
      groupLastKey = lastKey;
      ++groupCount;
    } else if (groupLastKey == key) {
      ++groupCount;
    }

    m_fieldsVector.emplace_back(key, value);
    lastKey = key;

    if (groupCount == groups) {
      break;
    }
  }
}

[[nodiscard]] int FIX::StringMessageParser::calculateCheckSum(std::string_view message,
                                                              char delimiter) const noexcept {
  int length = message.length() - 7;
  int checksum = 0;

  for (int i = 0; i < length; ++i) {
    if (message[i] == delimiter) {
      checksum += '\001';
      continue;
    }

    checksum += message[i];
  }

  return checksum & 0xFF;
}

[[nodiscard]] int FIX::StringMessageParser::calculateLength(
    std::string_view message) const noexcept {
  int start = message.find("35=") - 2;
  int end = message.rfind("10=") - 2;

  return end - start;
}

[[nodiscard]] bool FIX::StringMessageParser::isGroup(int tag) const {
  return FIX::TagsNum::GroupTagsMap.contains(tag);
}

[[nodiscard]] std::pair<int, std::string> FIX::StringMessageParser::parseKeyValueField(
    const std::string& field) {
  std::size_t equalPos = field.find('=');
  if (equalPos == std::string::npos) {
    throw std::runtime_error("Invalid field format: missing '=' in '" + field + "'");
  }

  return {std::stoi(field.substr(0, equalPos)), field.substr(equalPos + 1)};
}