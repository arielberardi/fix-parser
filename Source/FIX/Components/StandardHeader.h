#pragma once

#include <string>

#include "FIX/DataTypes.h"

namespace FIX {

class StandardHeader {
 public:
  StandardHeader() = default;

  StandardHeader(const FIX::FieldsVector& message) noexcept;

  [[nodiscard]] FIX::FieldsVector toVector();

  [[nodiscard]] FIX::Length getBodyLength() const noexcept;
  void setBodyLength(FIX::Length bodyLength) noexcept;

  [[nodiscard]] FIX::MsgType getMessageType() const noexcept;
  void setMessageType(FIX::MsgType messageType) noexcept;

  [[nodiscard]] FIX::ID getSenderCompId() const noexcept;
  void setSenderCompId(FIX::ID senderCompId) noexcept;

  [[nodiscard]] FIX::ID getTargetCompId() const noexcept;
  void setTargetCompId(FIX::ID targetCompId) noexcept;

  [[nodiscard]] FIX::SeqNum getMessageSeqNum() const noexcept;
  void setMessageSeqNum(FIX::SeqNum messageSeqNum) noexcept;

  [[nodiscard]] FIX::UTCTimestamp getSendingTime() const noexcept;
  void setSendingTime(const FIX::UTCTimestamp& sendingTime) noexcept;

 private:
  std::string m_beginString;
  FIX::Length m_bodyLength;
  FIX::MsgType m_messageType;
  FIX::ID m_senderCompId;
  FIX::ID m_targetCompId;
  FIX::SeqNum m_messageSeqNum;
  FIX::UTCTimestamp m_sendingTime;
};

}  // namespace FIX