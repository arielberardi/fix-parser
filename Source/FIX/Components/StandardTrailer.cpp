#include "FIX/Components/StandardTrailer.h"

#include <string>

#include "FIX/DataTypes.h"
#include "FIX/TagsNum.h"

FIX::StandardTrailer::StandardTrailer(const FIX::FieldsVector& message) noexcept {
  for (auto& [tag, value] : message) {
    if (tag == FIX::TagsNum::CheckSum) {
      m_checkSum = value;
      break;
    }
  }
}

[[nodiscard]] FIX::FieldsVector FIX::StandardTrailer::toVector() {
  FIX::FieldsVector vector;

  vector.emplace_back(FIX::TagsNum::CheckSum, m_checkSum);

  return vector;
}

[[nodiscard]] std::string FIX::StandardTrailer::getChecksum() const noexcept { return m_checkSum; }
void FIX::StandardTrailer::setChecksum(const std::string& checksum) noexcept {
  m_checkSum = checksum;
}