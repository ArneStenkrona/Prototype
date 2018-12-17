#include "CppUnitTest.h"
#include "../../Prototype/src/math/point.h"
#include "../../Prototype/src/math/point.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace pointTest {

    TEST_CLASS(point_test) {
        public:
            TEST_METHOD(test_addOperator) {
                double a = 234;
                double b = 325;
                double c = 657;
                double d = 768;
                Point p = Point(a, b);
                Point q = Point(c, d);

                Point pq = p + q;

                Assert::AreEqual(pq.x, a + c);
                Assert::AreEqual(pq.y, b + d);
            }
            TEST_METHOD(test_addAssignmentOperator) {
                double a = 234;
                double b = 325;
                double c = 657;
                double d = 768;
                Point p = Point(a, b);
                Point q = Point(c, d);

                Point pq = p + q;
                p += q;

                Assert::AreEqual(pq.x, p.x);
                Assert::AreEqual(pq.y, p.y);
            }
            TEST_METHOD(test_subtractOperator) {
                double a = 234;
                double b = 325;
                double c = 657;
                double d = 768;
                Point p = Point(a, b);
                Point q = Point(c, d);

                Point pq = p - q;

                Assert::AreEqual(pq.x, a - c);
                Assert::AreEqual(pq.y, b - d);
            }
            TEST_METHOD(test_subtractAssignmentOperator) {
                double a = 234;
                double b = 325;
                double c = 657;
                double d = 768;
                Point p = Point(a, b);
                Point q = Point(c, d);

                Point pq = p - q;
                p -= q;

                Assert::AreEqual(pq.x, p.x);
                Assert::AreEqual(pq.y, p.y);
            }

    };

}