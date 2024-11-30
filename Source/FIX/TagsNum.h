#pragma once

#include <unordered_map>

#include "FIX/DataTypes.h"

namespace FIX {
namespace TagsNum {
constexpr int BeginString{8};
constexpr int BodyLength{9};
constexpr int CheckSum{10};
constexpr int CIOrderID{11};
constexpr int SecurityIDSource{22};
constexpr int MsgSeqNum{34};
constexpr int MsgType{35};
constexpr int OrderQty{38};
constexpr int OrdType{40};
constexpr int SecurityID{48};
constexpr int SenderCompID{49};
constexpr int SendingTime{52};
constexpr int Side{54};
constexpr int Symbol{55};
constexpr int TargetCompID{56};
constexpr int TimeInForce{59};
constexpr int TransactTime{60};
constexpr int SymbolSfx{65};
constexpr int CashOrderQty{152};
constexpr int NoSecurityAltID{454};
constexpr int SecurityAltID{455};
constexpr int SecurityAltIDSource{456};
constexpr int Product{460};
constexpr int RoundingDirection{468};
constexpr int RoundingModulus{469};
constexpr int OrderPercent{516};
constexpr int ProductComplex{1227};
constexpr int SymbolPositionNumber{2957};

const std::unordered_map<int, bool> GroupTagsMap{{FIX::TagsNum::NoSecurityAltID, true}};
}  // namespace TagsNum
}  // namespace FIX