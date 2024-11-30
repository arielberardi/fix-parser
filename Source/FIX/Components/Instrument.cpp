#include "FIX/Components/Instrument.h"

#include <stdexcept>
#include <string>
#include <vector>

#include "FIX/DataTypes.h"
#include "FIX/Groups/NoSecurityAltId.h"
#include "FIX/TagsNum.h"

FIX::Instrument::Instrument(const FIX::FieldsVector& message) {
  std::string tempSecAltId{};

  for (auto& [tag, value] : message) {
    switch (tag) {
      case FIX::TagsNum::Symbol: m_symbol = value; break;
      case FIX::TagsNum::SymbolSfx: m_symbolSfx = value; break;
      case FIX::TagsNum::SecurityID: m_securityId = value; break;
      case FIX::TagsNum::SecurityIDSource: m_securityIdSource = value; break;
      case FIX::TagsNum::NoSecurityAltID: m_noSecAltIdGrp = std::stoi(value); break;
      case FIX::TagsNum::SecurityAltID:
        if (m_noSecAltIdGrp == 0) {
          throw std::runtime_error("Invalid message: repeat group not in order");
        }

        tempSecAltId = value;
        break;
      case FIX::TagsNum::SecurityAltIDSource:
        if (tempSecAltId.empty() || m_noSecAltIdGrp == 0) {
          throw std::runtime_error("Invalid message: repeat group not in order");
        }

        m_secAltIdGrp.emplace_back(tempSecAltId, std::stoi(value));
        tempSecAltId = "";
        break;
    }
  }
}

[[nodiscard]] FIX::FieldsVector FIX::Instrument::toVector() const noexcept {
  FIX::FieldsVector vector;
  vector.reserve(1 + m_noSecAltIdGrp * 2);

  vector.emplace_back(FIX::TagsNum::Symbol, m_symbol);

  if (m_symbolSfx.length() > 0) {
    vector.emplace_back(FIX::TagsNum::SymbolSfx, m_symbolSfx);
  }

  if (m_securityId.length() > 0) {
    vector.emplace_back(FIX::TagsNum::SecurityID, m_securityId);
  }

  if (m_securityIdSource.length() > 0) {
    vector.emplace_back(FIX::TagsNum::SecurityIDSource, m_securityIdSource);
  }

  if (m_noSecAltIdGrp) {
    vector.emplace_back(FIX::TagsNum::NoSecurityAltID, std::to_string(m_noSecAltIdGrp));

    for (NoSecurityAltId group : m_secAltIdGrp) {
      for (auto&& pair : group.toVector()) {
        vector.emplace_back(std::move(pair));
      }
    }
  }

  return vector;
}

[[nodiscard]] std::string FIX::Instrument::getSymbol() const noexcept { return m_symbol; }
void FIX::Instrument::setSymbol(const std::string& symbol) noexcept { m_symbol = symbol; }

[[nodiscard]] std::string FIX::Instrument::getSymbolSfx() const noexcept { return m_symbolSfx; }
void FIX::Instrument::setSymbolSfx(const std::string& symbolSfx) noexcept {
  m_symbolSfx = symbolSfx;
}

[[nodiscard]] FIX::ID FIX::Instrument::getSecurityId() const noexcept { return m_securityId; }
void FIX::Instrument::setSecurityId(FIX::ID securityId) noexcept { m_securityId = securityId; }

[[nodiscard]] std::string FIX::Instrument::getSecurityIdSource() const noexcept {
  return m_securityIdSource;
}
void FIX::Instrument::setSecurityIdSource(const std::string& securityIdSource) noexcept {
  m_securityIdSource = securityIdSource;
}

[[nodiscard]] int FIX::Instrument::getNoSecAltIdGrp() const noexcept { return m_noSecAltIdGrp; }
void FIX::Instrument::setNoSecAltIdGrp(int noSecAltIdGrp) noexcept {
  m_noSecAltIdGrp = noSecAltIdGrp;
}

[[nodiscard]] std::vector<FIX::NoSecurityAltId> FIX::Instrument::getSecAltIdGrp() const noexcept {
  return m_secAltIdGrp;
}
void FIX::Instrument::setSecAltIdGrp(
    const std::vector<FIX::NoSecurityAltId>& secAltIdGrp) noexcept {
  m_secAltIdGrp = secAltIdGrp;
}