#include "FIX/Groups/NoSecurityAltId.h"

#include <gtest/gtest.h>

#include "FIX/DataTypes.h"

TEST(NoSecurityAltId, converts_to_fields_vector) {
  FIX::NoSecurityAltId securityAltId{"123", 1};
  FIX::FieldsVector vector = securityAltId.toVector();

  EXPECT_FALSE(vector.empty());
  EXPECT_EQ(vector[0].second, "123");
  EXPECT_EQ(vector[1].second, "1");
}
