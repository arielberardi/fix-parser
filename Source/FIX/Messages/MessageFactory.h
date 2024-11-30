#pragma once

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "FIX/DataTypes.h"
#include "FIX/Messages/Message.h"

#define MESSAGE_FACTORY_REGISTER(MessageObject)                     \
  FIX::MessageFactory::registerMessage(MessageObject::kMessageType, \
                                       []() { return std::make_shared<MessageObject>(); });

namespace FIX {

class MessageFactory {
 public:
  using Creator = std::function<std::shared_ptr<Message>()>;

  static void registerMessage(const FIX::MsgType& messageType, Creator creator) noexcept {
    getRegistry()[messageType] = std::move(creator);
  }

  [[nodiscard]] static std::shared_ptr<Message> createMessage(const FIX::MsgType& messageType) {
    RegistryMap& registry = getRegistry();

    auto it = registry.find(messageType);
    if (it == registry.end()) {
      throw std::runtime_error("Message type" + messageType + "is not registered");
    }

    return it->second();
  }

 private:
  using RegistryMap = std::unordered_map<FIX::MsgType, Creator>;

  static RegistryMap& getRegistry() {
    static RegistryMap registry;
    return registry;
  }
};

}  // namespace FIX