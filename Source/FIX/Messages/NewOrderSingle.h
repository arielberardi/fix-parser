#pragma once

#include <iostream>

#include "FIX/Components/Instrument.h"
#include "FIX/Components/OrderQtyData.h"
#include "FIX/DataTypes.h"
#include "FIX/Messages/Message.h"
#include "FIX/Messages/MessageFactory.h"

namespace FIX {

class NewOrderSingle : public FIX::Message {
 public:
  static constexpr FIX::MsgType kMessageType{"D"};

  void parse(const FIX::FieldsVector& message) override;

  [[nodiscard]] FIX::FieldsVector toVector() const noexcept override;

  [[nodiscard]] FIX::MsgType getType() const noexcept override;

  [[nodiscard]] FIX::ID getCIOrderId() const noexcept;
  void setCIOrderId(FIX::ID ciOrdId) noexcept;

  [[nodiscard]] FIX::Instrument getInstrument() const noexcept;
  void setInstrument(const FIX::Instrument& instrument) noexcept;

  [[nodiscard]] FIX::OrderSide getOrderSide() const noexcept;
  void setOrderSide(FIX::OrderSide side) noexcept;

  [[nodiscard]] FIX::UTCTimestamp getTransactTime() const noexcept;
  void setTransactTime(const FIX::UTCTimestamp& transactTime) noexcept;

  [[nodiscard]] FIX::OrderQtyData getOrdQtyData() const noexcept;
  void setOrdQtyData(const FIX::OrderQtyData& ordQtyData) noexcept;

  [[nodiscard]] FIX::OrderType getOrderType() const noexcept;
  void setOrderType(FIX::OrderType orderType) noexcept;

 private:
  FIX::ID m_ciOrdId{};
  FIX::Instrument m_instrument;
  FIX::OrderSide m_side{};
  FIX::UTCTimestamp m_transactTime{};
  FIX::OrderQtyData m_ordQtyData;
  FIX::OrderType m_orderType{};
};

}  // namespace FIX