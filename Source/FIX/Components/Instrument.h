#pragma once

#include <string>
#include <vector>

#include "FIX/DataTypes.h"
#include "FIX/Groups/NoSecurityAltId.h"

namespace FIX {

class Instrument {
 public:
  Instrument() = default;
  Instrument(const FIX::FieldsVector& message);

  [[nodiscard]] FIX::FieldsVector toVector() const noexcept;

  [[nodiscard]] std::string getSymbol() const noexcept;
  void setSymbol(const std::string& symbol) noexcept;

  [[nodiscard]] std::string getSymbolSfx() const noexcept;
  void setSymbolSfx(const std::string& symbolSfx) noexcept;

  [[nodiscard]] FIX::ID getSecurityId() const noexcept;
  void setSecurityId(FIX::ID securityId) noexcept;

  [[nodiscard]] std::string getSecurityIdSource() const noexcept;
  void setSecurityIdSource(const std::string& securityIdSource) noexcept;

  [[nodiscard]] int getNoSecAltIdGrp() const noexcept;
  void setNoSecAltIdGrp(int noSecAltIdGrp) noexcept;

  [[nodiscard]] std::vector<FIX::NoSecurityAltId> getSecAltIdGrp() const noexcept;
  void setSecAltIdGrp(const std::vector<FIX::NoSecurityAltId>& secAltIdGrp) noexcept;

 private:
  std::string m_symbol{};
  std::string m_symbolSfx{};
  FIX::ID m_securityId{};
  std::string m_securityIdSource{};
  int m_noSecAltIdGrp{};
  std::vector<FIX::NoSecurityAltId> m_secAltIdGrp{};
};

}  // namespace FIX