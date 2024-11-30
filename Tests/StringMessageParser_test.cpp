#include "FIX/StringMessageParser.h"

#include <gtest/gtest.h>

#include <string>

#include "FIX/DataTypes.h"

static FIX::FieldsVector messageVector{{8, "FIXT.1.1"},
                                       {9, ""},
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
                                       {10, ""}};

static std::string fixMessage =
    "8=FIXT.1.1|9=159|35=D|49=SenderCompID|56=TargetCompID|34=2|11="
    "123456|55=IBM|48=459200101|22=1|454=2|455=ALTID1|456=4|455=ALTID2|456=5|54=1|60=20231119-15:"
    "45:00.000|38=100|40=2|10=004|";

static std::string fixMessageInvalidLength =
    "8=FIXT.1.1|9=15|35=D|49=SenderCompID|56=TargetCompID|34=2|11="
    "123456|55=IBM|48=459200101|22=1|454=2|455=ALTID1|456=4|455=ALTID2|456=5|54=1|60=20231119-15:"
    "45:00.000|38=100|40=2|10=004|";

static std::string fixMessageInvalidChecksum =
    "8=FIXT.1.1|9=15|35=D|49=SenderCompID|56=TargetCompID|34=2|11="
    "123456|55=IBM|48=459200101|22=1|454=2|455=ALTID1|456=4|455=ALTID2|456=5|54=1|60=20231119-15:"
    "45:00.000|38=100|40=2|10=004|";

static std::string fixMessageInvalidField =
    "8=FIXT.1.1|9=15|35=D|49=SenderCompID|56=TargetCompID|34=2|11="
    "123456|55=IBM|48=459200101|22=|454=2|455=ALTID1|456=4|455=ALTID2|456=5|54=1|60=20231119-15:"
    "45:00.000|38=100|40=2|10=004|";

TEST(StringMessageParser, parser_message_to_vector) {
  FIX::StringMessageParser parser;
  parser.parser(fixMessage, '|');

  FIX::FieldsVector vector = parser.getVector();

  EXPECT_FALSE(vector.empty());
  EXPECT_EQ(vector.size(), messageVector.size());

  EXPECT_EQ(vector[0].second, messageVector[0].second);
  EXPECT_EQ(vector[2].second, messageVector[2].second);
  EXPECT_EQ(vector[5].second, messageVector[5].second);
  EXPECT_EQ(vector[8].second, messageVector[8].second);
}

TEST(StringMessageParser, raise_exception_invalid_length) {
  FIX::StringMessageParser parser;
  EXPECT_THROW(parser.parser(fixMessageInvalidLength, '|'), std::runtime_error);
}

TEST(StringMessageParser, raise_exception_invalid_checksum) {
  FIX::StringMessageParser parser;
  EXPECT_THROW(parser.parser(fixMessageInvalidChecksum, '|'), std::runtime_error);
}

TEST(StringMessageParser, raise_exception_invalid_field) {
  FIX::StringMessageParser parser;
  EXPECT_THROW(parser.parser(fixMessageInvalidField, '|'), std::runtime_error);
}