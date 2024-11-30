#pragma once

#include <string>
#include <vector>

namespace FIX {
using FieldsVector = std::vector<std::pair<int, std::string>>;

using Length = int;
using TagNum = int;
using SeqNum = int;
using NumInGroup = int;
using DayOfMonth = int;

using Quantity = int;
using Price = float;
using PriceOffset = float;
using Amount = float;
using Percentage = float;

using Country = std::string;
using Language = std::string;
using Currency = std::string;
using Exchange = std::string;
using MonthYear = std::string;
using UTCTimestamp = std::string;
using UTCTimeOnly = std::string;
using UTCDateOnly = std::string;
using LocalMktDate = std::string;
using LocalMktTime = std::string;
using TZTimeOnly = std::string;
using TZTimestamp = std::string;
using ID = std::string;
using IDRef = std::string;
using OrderType = std::string;
using OrderSide = std::string;
using Boolean = std::string;
using MsgType = std::string;
}  // namespace FIX
