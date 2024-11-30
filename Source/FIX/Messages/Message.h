#pragma once

#include "FIX/DataTypes.h"

namespace FIX {

class Message {
 public:
  virtual void parse(const FIX::FieldsVector& message) = 0;
  virtual FIX::FieldsVector toVector() const = 0;
  virtual FIX::MsgType getType() const = 0;
};

}  // namespace FIX