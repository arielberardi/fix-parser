#pragma once

#include <functional>
#include <memory>
#include <stdexcept>
#include <unordered_map>

#include "FIX/Messages/Message.h"

#define MESSAGE_ACTION_REGISTER(MessageObject, Action)                         \
  FIX::MessageActionsDispatcher::registerAction(                               \
      MessageObject::kMessageType, [](std::shared_ptr<FIX::Message> message) { \
        Action(std::static_pointer_cast<MessageObject>(message));              \
      });

namespace FIX {

class MessageActionsDispatcher {
 public:
  using Action = std::function<void(std::shared_ptr<Message>)>;

  static void registerAction(const FIX::MsgType& messageType, Action action) {
    getRegistry()[messageType] = std::move(action);
  }

  static void executeAction(const std::string& messageType, std::shared_ptr<Message> message) {
    RegistryMap& registry = getRegistry();

    auto it = registry.find(messageType);
    if (it == registry.end()) {
      throw std::runtime_error("Message type" + messageType + "is not registered");
    }

    it->second(message);
  }

 private:
  using RegistryMap = std::unordered_map<FIX::MsgType, Action>;

  static RegistryMap& getRegistry() {
    static RegistryMap registry;
    return registry;
  }
};

}  // namespace FIX