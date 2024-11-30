#include "FIX/StringMessageFormatter.h"

#include <gtest/gtest.h>

#include <string>

#include "FIX/DataTypes.h"

static FIX::FieldsVector messageVector{{8, "FIXT.1.1"},
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
                                       {40, "2"}};

static std::string fixMessage =
    "8=FIXT.1.1|9=159|35=D|49=SenderCompID|56=TargetCompID|34=2|11="
    "123456|55=IBM|48=459200101|22=1|454=2|455=ALTID1|456=4|455=ALTID2|456=5|54=1|60=20231119-15:"
    "45:00.000|38=100|40=2|10=004|";

static std::string fixMessage2 =
    "8=FIXT.1.1;9=159;35=D;49=SenderCompID;56=TargetCompID;34=2;11="
    "123456;55=IBM;48=459200101;22=1;454=2;455=ALTID1;456=4;455=ALTID2;456=5;54=1;60=20231119-15:"
    "45:00.000;38=100;40=2;10=004;";

TEST(StringMessageFormatter, returns_valid_string_fix_message) {
  FIX::StringMessageFormatter formatter;
  formatter.format(messageVector, '|');

  EXPECT_EQ(formatter.getMessage(), fixMessage);
}

TEST(StringMessageFormatter, receives_different_delimiter) {
  FIX::StringMessageFormatter formatter;
  formatter.format(messageVector, ';');

  EXPECT_EQ(formatter.getMessage(), fixMessage2);
}
