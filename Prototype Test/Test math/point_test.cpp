#include "CppUnitTest.h"
#include "../../Prototype/src/math/point.h"
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

                Assert::AreEqual(a + c, pq.x);
                Assert::AreEqual(b + d, pq.y);
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

                Assert::AreEqual(p.x, pq.x);
                Assert::AreEqual(p.y, pq.y);
            }
            TEST_METHOD(test_subtractOperator) {
                double a = 234;
                double b = 325;
                double c = 657;
                double d = 768;
                Point p = Point(a, b);
                Point q = Point(c, d);

                Point pq = p - q;

                Assert::AreEqual(a - c, pq.x);
                Assert::AreEqual(b - d, pq.y);
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

                Assert::AreEqual(p.x, pq.x);
                Assert::AreEqual(p.y, pq.y);
            }
            TEST_METHOD(test_crossProductOperator) {
                double a = 234;
                double b = 325;
                double c = 657;
                double d = 768;
                Point p = Point(a, b);
                Point q = Point(c, d);

                Point pq = p * q;

                Assert::AreEqual(a * c - b * d, pq.x);
                Assert::AreEqual(a * d + b * c, pq.y);
            }
            TEST_METHOD(test_crossProductAssignmentOperator) {
                double a = 234;
                double b = 325;
                double c = 657;
                double d = 768;
                Point p = Point(a, b);
                Point q = Point(c, d);

                Point pq = p * q;
                p *= q;

                Assert::AreEqual(p.x, pq.x);
               (p.y, pq.y);
            }
            TEST_METHOD(test_leftshiftOperator) {
                std::ostringstream oss;
                oss << Point(1,2);
                Assert::AreEqual("Point(1, 2)", oss.str().c_str());
            }
            TEST_METHOD(test_toString) {
                std::string s = Point(1, 2).toString();
                Assert::AreEqual("Point(1.000000, 2.000000)", s.c_str());
            }
            TEST_METHOD(test_maginutde) {
                Point p = Point(22, 120);
                Point q = Point(-34, 288);

                Assert::AreEqual(122.0, p.magnitude());
                Assert::AreEqual(290.0, q.magnitude());
            }
            TEST_METHOD(test_normalized){
                Point p = Point(100,200).normalized();
                Assert::AreEqual(0.4472, p.x, 0.0001);
                Assert::AreEqual(0.8944, p.y, 0.0001);
                Assert::AreEqual(1.0, p.magnitude(), 0.0001);
            }
            TEST_METHOD(test_rotate) {
                Point p = Point(3, 4);
                Point q = Point(5, 7);
                Point prq = p.rotate(33, q);
                Assert::AreEqual(4.96, prq.x, 0.01);
                Assert::AreEqual(3.39, prq.y, 0.01);
            }
            TEST_METHOD(test_distanceTo) {
                Point p = Point(521, 376);
                Point q = Point(-21, 877);
                double d = p.distanceTo(q);
                Assert::AreEqual(738, d, 0.1);
            }
            TEST_METHOD(test_dotProduct) {
                double a = 234;
                double b = 325;
                double c = 657;
                double d = 768;
                Point p = Point(a, b);
                Point q = Point(c, d);

                double dot = p.dot(q);

                Assert::AreEqual(a * c + b * d, dot);
            }
            TEST_METHOD(test_antidotProduct) {
                double a = 234;
                double b = 325;
                double c = 657;
                double d = 768;
                Point p = Point(a, b);
                Point q = Point(c, d);

                double antidot = p.antidot(q);

                Assert::AreEqual(a * d - b * c, antidot);
            }

            TEST_METHOD(test_toAngle) {
                Point p = Point(33, 2);
                Assert::AreEqual(3.46823, p.toAngle(), 0.0001);
            }
    };

}