#include "FIX/Components/OrderQtyData.h"

#include <gtest/gtest.h>

#include "FIX/DataTypes.h"

static FIX::FieldsVector message{{8, "FIXT.1.1"},
                                 {9, "159"},
                                 {35, "D"},
                                 {49, "SenderCompID"},
                                 {56, "TargetCompID"},
                                 {34, "2"},
                                 {11, "123456"},
                                 {55, "IBM"},
                                 {48, "459200101"},
                                 {22, "1"},
                                 {454, "2"},
                                 {455, "ALTID1"},
                                 {456, "4"},
                                 {455, "ALTID2"},
                                 {456, "5"},
                                 {54, "1"},
                                 {60, "20231119-15:45:00.000"},
                                 {38, "100"},
                                 {40, "2"},
                                 {10, "004"}};

TEST(OrderQtyData, construct_from_fields_vector) {
  FIX::OrderQtyData order{message};
  FIX::FieldsVector vector = order.toVector();

  EXPECT_FALSE(vector.empty());
  EXPECT_EQ(vector.front().second, "100");
}
