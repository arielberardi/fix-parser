#pragma once

#include "FIX/DataTypes.h"

namespace FIX {

class NoSecurityAltId {
 public:
  NoSecurityAltId() = default;

  NoSecurityAltId(FIX::ID securityAltId, int securityAltIdSource) noexcept;

  [[nodiscard]] FIX::FieldsVector toVector();

  [[nodiscard]] FIX::ID getSecurityAltId() const noexcept;
  void setSecurityAltId(FIX::ID securityAltId) noexcept;

  [[nodiscard]] int getSecurityAltIdSource() const noexcept;
  void setSecurityAltIdSource(int securityAltIdSource) noexcept;

 private:
  FIX::ID m_securityAltId;
  int m_securityAltIdSource;
};

}  // namespace FIX