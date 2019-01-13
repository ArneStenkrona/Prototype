#include "CppUnitTest.h"
#include "..\..\Prototype\src\math\polygon.h"
#include <vector>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace polygonTest {

    TEST_CLASS(polygonTest) {
        public:
            TEST_METHOD(test_vector_constructor) {

                Point a = Point(1, 2);
                Point b = Point(3, 4);
                Point c = Point(5, 6);
                std::vector<Point> v;
                v.push_back(a);
                v.push_back(b);
                v.push_back(c);
                Polyshape p = Polyshape(v);
                Assert::AreEqual((int)p.numberOfVertices, 3);
            }
    };
}