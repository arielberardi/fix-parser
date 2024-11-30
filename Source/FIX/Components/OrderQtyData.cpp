#include "FIX/Components/OrderQtyData.h"

#include "FIX/DataTypes.h"
#include "FIX/TagsNum.h"

FIX::OrderQtyData::OrderQtyData(const FIX::FieldsVector& message) noexcept {
  for (auto& [tag, value] : message) {
    switch (tag) {
      case FIX::TagsNum::OrderQty: m_orderQty = std::stoi(value); break;
    }
  }
}

[[nodiscard]] FIX::FieldsVector FIX::OrderQtyData::toVector() const noexcept {
  FIX::FieldsVector vector;

  vector.emplace_back(FIX::TagsNum::OrderQty, std::to_string(m_orderQty));

  return vector;
}

[[nodiscard]] FIX::Quantity FIX::OrderQtyData::getOrderQty() const noexcept { return m_orderQty; }
void FIX::OrderQtyData::setOrderQty(FIX::Quantity qty) noexcept { m_orderQty = qty; }