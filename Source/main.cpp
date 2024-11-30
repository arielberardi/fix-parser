#include <iostream>
#include <unordered_map>
#include <vector>

#include "FIX/Components/StandardHeader.h"
#include "FIX/DataTypes.h"
#include "FIX/Messages/MessageActionsDispatcher.h"
#include "FIX/Messages/MessageFactory.h"
#include "FIX/Messages/NewOrderSingle.h"
#include "FIX/Messages/Types.h"
#include "FIX/StringMessageFormatter.h"
#include "FIX/StringMessageParser.h"

constexpr char delimiter = '|';
constexpr char kNewSingleMessage[] =
    "8=FIXT.1.1|9=159|35=D|49=SenderCompID|56=TargetCompID|34=2|11="
    "123456|55=IBM|48=459200101|22=1|454=2|455=ALTID1|456=4|455=ALTID2|456=5|54=1|60=20231119-15:"
    "45:00.000|38=100|40=2|10=004|";

void onNewOrderSingle(const std::shared_ptr<FIX::NewOrderSingle> message) {
  std::cout << &message << std::endl;
  std::cout << "Message type D: " << message->getType() << "\n";
}

int main() {
  // Code Smell, need to think how to improve this (can I find a way with templates?)
  MESSAGE_FACTORY_REGISTER(FIX::NewOrderSingle);
  MESSAGE_ACTION_REGISTER(FIX::NewOrderSingle, onNewOrderSingle);

  try {
    // Parser received FIX string message
    FIX::StringMessageParser parser;
    parser.parser(kNewSingleMessage, delimiter);

    // Create the header  (trailer just contains checksum so we don't need that)
    FIX::StandardHeader header{parser.getVector()};
    FIX::MsgType msgType = header.getMessageType();

    // Create the Message Type object from factory
    auto message = FIX::MessageFactory::createMessage(msgType);
    message->parse(parser.getVector());

    std::cout << &message << std::endl;

    // Execute action
    FIX::MessageActionsDispatcher::executeAction(msgType, message);

    // Format a FIX string message
    FIX::FieldsVector messageVector = header.toVector();
    FIX::FieldsVector newOrderSingleVector = message->toVector();
    for (auto&& pair : newOrderSingleVector) {
      messageVector.push_back(pair);
    }

    FIX::StringMessageFormatter formatter;
    formatter.format(messageVector, delimiter);

    std::cout << formatter.getMessage() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}