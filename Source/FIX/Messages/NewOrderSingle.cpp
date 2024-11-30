#include "FIX/Messages/NewOrderSingle.h"

#include "FIX/Components/Instrument.h"
#include "FIX/Components/OrderQtyData.h"
#include "FIX/DataTypes.h"
#include "FIX/Messages/Types.h"
#include "FIX/TagsNum.h"

void FIX::NewOrderSingle::parse(const FIX::FieldsVector& message) {
  m_instrument = FIX::Instrument(message);
  m_ordQtyData = FIX::OrderQtyData(message);

  for (auto& [tag, value] : message) {
    switch (tag) {
      case FIX::TagsNum::CIOrderID: m_ciOrdId = value; break;
      case FIX::TagsNum::OrdType: m_orderType = value; break;
      case FIX::TagsNum::Side: m_side = value; break;
      case FIX::TagsNum::TransactTime: m_transactTime = value; break;
    }
  }
}

[[nodiscard]] FIX::FieldsVector FIX::NewOrderSingle::toVector() const noexcept {
  auto instrumentVector = m_instrument.toVector();
  auto qtyDataVector = m_ordQtyData.toVector();

  FIX::FieldsVector vector;
  vector.reserve(5 + instrumentVector.size() + qtyDataVector.size());

  vector.emplace_back(FIX::TagsNum::CIOrderID, m_ciOrdId);
  vector.emplace_back(FIX::TagsNum::OrdType, m_orderType);
  vector.emplace_back(FIX::TagsNum::Side, m_side);
  vector.emplace_back(FIX::TagsNum::TransactTime, m_transactTime);

  for (auto&& pair : instrumentVector) {
    vector.emplace_back(std::move(pair));
  }

  for (auto&& pair : qtyDataVector) {
    vector.emplace_back(std::move(pair));
  }

  return vector;
}

[[nodiscard]] FIX::MsgType FIX::NewOrderSingle::getType() const noexcept {
  return FIX::MessageType::NewOrderSingle;
}

[[nodiscard]] FIX::ID FIX::NewOrderSingle::getCIOrderId() const noexcept { return m_ciOrdId; }
void FIX::NewOrderSingle::setCIOrderId(FIX::ID ciOrdId) noexcept { m_ciOrdId = ciOrdId; }

[[nodiscard]] FIX::Instrument FIX::NewOrderSingle::getInstrument() const noexcept {
  return m_instrument;
}
void FIX::NewOrderSingle::setInstrument(const FIX::Instrument& instrument) noexcept {
  m_instrument = instrument;
}

[[nodiscard]] FIX::OrderSide FIX::NewOrderSingle::getOrderSide() const noexcept { return m_side; }
void FIX::NewOrderSingle::setOrderSide(FIX::OrderSide side) noexcept { m_side = side; }

[[nodiscard]] FIX::UTCTimestamp FIX::NewOrderSingle::getTransactTime() const noexcept {
  return m_transactTime;
}
void FIX::NewOrderSingle::setTransactTime(const FIX::UTCTimestamp& transactTime) noexcept {
  m_transactTime = transactTime;
}

[[nodiscard]] FIX::OrderQtyData FIX::NewOrderSingle::getOrdQtyData() const noexcept {
  return m_ordQtyData;
}
void FIX::NewOrderSingle::setOrdQtyData(const FIX::OrderQtyData& ordQtyData) noexcept {
  m_ordQtyData = ordQtyData;
}

[[nodiscard]] FIX::OrderType FIX::NewOrderSingle::getOrderType() const noexcept {
  return m_orderType;
}
void FIX::NewOrderSingle::setOrderType(FIX::OrderType orderType) noexcept {
  m_orderType = orderType;
}
