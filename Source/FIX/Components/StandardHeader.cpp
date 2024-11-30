#include "FIX/Components/StandardHeader.h"

#include <string>

#include "FIX/DataTypes.h"
#include "FIX/TagsNum.h"

FIX::StandardHeader::StandardHeader(const FIX::FieldsVector& message) noexcept {
  for (auto& [tag, value] : message) {
    switch (tag) {
      case FIX::TagsNum::BeginString: m_beginString = value; break;
      case FIX::TagsNum::BodyLength: m_bodyLength = std::stoi(value); break;
      case FIX::TagsNum::MsgType: m_messageType = value; break;
      case FIX::TagsNum::SenderCompID: m_senderCompId = value; break;
      case FIX::TagsNum::TargetCompID: m_targetCompId = value; break;
      case FIX::TagsNum::MsgSeqNum: m_messageSeqNum = std::stoi(value); break;
      case FIX::TagsNum::SendingTime: m_sendingTime = value; break;
    }
  }
}

[[nodiscard]] FIX::FieldsVector FIX::StandardHeader::toVector() {
  FIX::FieldsVector vector;
  vector.reserve(6);

  vector.emplace_back(FIX::TagsNum::BeginString, m_beginString);
  vector.emplace_back(FIX::TagsNum::BodyLength, std::to_string(m_bodyLength));
  vector.emplace_back(FIX::TagsNum::MsgType, m_messageType);
  vector.emplace_back(FIX::TagsNum::SenderCompID, m_senderCompId);
  vector.emplace_back(FIX::TagsNum::TargetCompID, m_targetCompId);
  vector.emplace_back(FIX::TagsNum::MsgSeqNum, std::to_string(m_messageSeqNum));

  return vector;
}

[[nodiscard]] FIX::Length FIX::StandardHeader::getBodyLength() const noexcept {
  return m_bodyLength;
}
void FIX::StandardHeader::setBodyLength(FIX::Length bodyLength) noexcept {
  m_bodyLength = bodyLength;
}

[[nodiscard]] FIX::MsgType FIX::StandardHeader::getMessageType() const noexcept {
  return m_messageType;
}
void FIX::StandardHeader::setMessageType(FIX::MsgType messageType) noexcept {
  m_messageType = messageType;
}

[[nodiscard]] FIX::ID FIX::StandardHeader::getSenderCompId() const noexcept {
  return m_senderCompId;
}
void FIX::StandardHeader::setSenderCompId(FIX::ID senderCompId) noexcept {
  m_senderCompId = senderCompId;
}

[[nodiscard]] FIX::ID FIX::StandardHeader::getTargetCompId() const noexcept {
  return m_targetCompId;
}
void FIX::StandardHeader::setTargetCompId(FIX::ID targetCompId) noexcept {
  m_targetCompId = targetCompId;
}

[[nodiscard]] FIX::SeqNum FIX::StandardHeader::getMessageSeqNum() const noexcept {
  return m_messageSeqNum;
}
void FIX::StandardHeader::setMessageSeqNum(FIX::SeqNum messageSeqNum) noexcept {
  m_messageSeqNum = messageSeqNum;
}

[[nodiscard]] FIX::UTCTimestamp FIX::StandardHeader::getSendingTime() const noexcept {
  return m_sendingTime;
}
void FIX::StandardHeader::setSendingTime(const FIX::UTCTimestamp& sendingTime) noexcept {
  m_sendingTime = sendingTime;
}