#include <benchmark/benchmark.h>

#include <iostream>
#include <unordered_map>
#include <vector>

#include "FIX/DataTypes.h"
#include "FIX/Messages/MessageActionsDispatcher.h"
#include "FIX/Messages/MessageFactory.h"
#include "FIX/Messages/NewOrderSingle.h"
#include "FIX/Messages/Types.h"
#include "FIX/StringMessageFormatter.h"
#include "FIX/StringMessageParser.h"

static constexpr char kNewSingleMessage[] =
    "8=FIXT.1.1|9=159|35=D|49=SenderCompID|56=TargetCompID|34=2|11="
    "123456|55=IBM|48=459200101|22=1|454=2|455=ALTID1|456=4|455=ALTID2|456=5|54=1|60=20231119-15:"
    "45:00.000|38=100|40=2|10=004|";

static constexpr char kDelimiter = '|';

static void BM_StringMessageProcess(benchmark::State& state) {
  uint64_t count = 0;

  MESSAGE_FACTORY_REGISTER(FIX::NewOrderSingle);
  MESSAGE_ACTION_REGISTER(
      FIX::NewOrderSingle,
      [](const std::shared_ptr<FIX::NewOrderSingle> message) { message->getType(); });

  for (auto _ : state) {
    FIX::StringMessageParser parser;
    parser.parser(kNewSingleMessage, kDelimiter);

    FIX::StandardHeader header{parser.getVector()};
    FIX::MsgType msgType = header.toVector()[2].second;

    auto message = FIX::MessageFactory::createMessage(msgType);
    message->parse(parser.getVector());

    FIX::MessageActionsDispatcher::executeAction(msgType, message);

    FIX::FieldsVector messageVector = header.toVector();
    FIX::FieldsVector newOrderSingleVector = message->toVector();
    for (auto&& pair : newOrderSingleVector) {
      messageVector.push_back(pair);
    }

    FIX::StringMessageFormatter formatter;
    formatter.format(messageVector, kDelimiter);
    ++count;
  }

  state.counters["ops/sec"] =
      benchmark::Counter(static_cast<double>(count), benchmark::Counter::kIsRate);
}

BENCHMARK(BM_StringMessageProcess)->Unit(benchmark::kSecond)->Repetitions(10);
BENCHMARK_MAIN();