#include "stdafx.h"
#include "AssessRectangle.h"
#include "AssessDataProvider.h"
//////////////////////////////////////////////////////////////////////////
// JSON code taken from
// https://github.com/DaveGamble/cJSON
// and included in solution under JSON folder
#include "JSON/cJSON.h"
#include "AssessDataProviderJSON.h"
#include "AssessDataProviderFactory.h"
#include "AssessRectsContainer.h"

#include "easyunit\test.h"

using namespace easyunit;

TEST(Rectangle, InitRectangles)
{
	AssessRectangle rc1(10, 10, 20, 20);
	ASSERT_TRUE( rc1.isValid() );

	AssessRectangle rc2(10, 10, -20, 20);
	ASSERT_TRUE( !rc2.isValid() );

	rc2.set(INT_MAX, INT_MAX, INT_MAX, INT_MAX);
	ASSERT_TRUE( rc2.isValid() );

	rc2.set(INT_MAX, INT_MAX+1, INT_MAX, INT_MAX);
	ASSERT_TRUE( !rc2.isValid() );

	rc2.set(INT_MAX, INT_MAX, INT_MAX+1, INT_MAX);
	ASSERT_TRUE(!rc2.isValid());
}

TEST(Rectangle, Intersections)
{
	AssessRectangle rc1(10, 10, 20, 20);
	ASSERT_TRUE(rc1.isValid());

	AssessRectangle rc2(15, 15, 20, 20);
	ASSERT_TRUE(rc2.isValid());

	AssessRectangle rc3;
	ASSERT_TRUE( rc1.intersect(rc2, rc3) );
	ASSERT_TRUE( rc3.isValid());

	ASSERT_TRUE( rc3 == AssessRectangle(15,15,15,15) );


	AssessRectangle rc4(20, 20, 20, 20);
	ASSERT_TRUE(rc4.isValid());

	AssessRectangle rc5;
	ASSERT_TRUE(rc3.intersect(rc4, rc5));
	ASSERT_TRUE(rc5.isValid());

	ASSERT_TRUE(rc5 == AssessRectangle(20, 20, 10, 10));

}
