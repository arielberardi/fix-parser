#include "FIX/Groups/NoSecurityAltId.h"

#include "FIX/DataTypes.h"
#include "FIX/TagsNum.h"

FIX::NoSecurityAltId::NoSecurityAltId(FIX::ID securityAltId, int securityAltIdSource) noexcept
    : m_securityAltId{securityAltId}, m_securityAltIdSource{securityAltIdSource} {}

[[nodiscard]] FIX::FieldsVector FIX::NoSecurityAltId::toVector() {
  FIX::FieldsVector vector;
  vector.reserve(2);

  vector.emplace_back(FIX::TagsNum::SecurityAltID, m_securityAltId);
  vector.emplace_back(FIX::TagsNum::SecurityAltIDSource, std::to_string(m_securityAltIdSource));

  return vector;
}

[[nodiscard]] FIX::ID FIX::NoSecurityAltId::getSecurityAltId() const noexcept {
  return m_securityAltId;
}
void FIX::NoSecurityAltId::setSecurityAltId(FIX::ID securityAltId) noexcept {
  m_securityAltId = securityAltId;
}

[[nodiscard]] int FIX::NoSecurityAltId::getSecurityAltIdSource() const noexcept {
  return m_securityAltIdSource;
}
void FIX::NoSecurityAltId::setSecurityAltIdSource(int securityAltIdSource) noexcept {
  m_securityAltIdSource = securityAltIdSource;
}