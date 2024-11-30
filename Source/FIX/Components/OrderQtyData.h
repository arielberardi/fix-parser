#pragma once

#include "FIX/DataTypes.h"

namespace FIX {

class OrderQtyData {
 public:
  OrderQtyData() = default;
  OrderQtyData(const FIX::FieldsVector& message) noexcept;

  [[nodiscard]] FIX::FieldsVector toVector() const noexcept;

  [[nodiscard]] FIX::Quantity getOrderQty() const noexcept;
  void setOrderQty(FIX::Quantity qty) noexcept;

 private:
  FIX::Quantity m_orderQty;
};

}  // namespace FIX