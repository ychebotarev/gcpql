#include "stdafx.h"
#include "CppUnitTest.h"

#include "src/gcpqlParser/common/disjoint_hash_set.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace gcpqlParserTest
{
    TEST_CLASS(DisjointHashSetTests)
    {
    public:

        TEST_METHOD(DisjointHashSetSimpleTest)
        {
            disjoint_hash_set<std::string> ds;
            ds.Add("A1");
            ds.Add("A2");
            ds.Union("A1", "A2");
            Assert::IsTrue(ds.AreInSameSet("A1", "A2"), L"A1 and A2 are not in the same set");
        }
        
        TEST_METHOD(DisjointHashSetUnionTest)
        {
            disjoint_hash_set<std::string> ds;
            ds.Add("A1");
            ds.Add("A2");
            ds.Add("A3");
            ds.Add("A4");
            ds.Add("A5");
            ds.Add("A6");
            ds.Add("A7");
            ds.Add("A8");
            ds.Add("A9");

            ds.Union("A1", "A2");
            ds.Union("A3", "A4");
            ds.Union("A5", "A6");
            ds.Union("A7", "A8");
            ds.Union("A7", "A9");

            Assert::IsTrue(ds.AreInSameSet("A1", "A2"), L"A1 and A2 are not in the same set");
            Assert::IsTrue(ds.AreInSameSet("A3", "A4"), L"A3 and A4 are not in the same set");
            Assert::IsTrue(ds.AreInSameSet("A5", "A6"), L"A5 and A6 are not in the same set");
            Assert::IsTrue(ds.AreInSameSet("A7", "A8"), L"A6 and A8 are not in the same set");
            Assert::IsTrue(ds.AreInSameSet("A8", "A9"), L"A8 and A9 are not in the same set");
            
            Assert::IsFalse(ds.AreInSameSet("A1", "A3"), L"A1 and A3 are in the same set");
            Assert::IsFalse(ds.AreInSameSet("A1", "A4"), L"A1 and A4 are in the same set");
            Assert::IsFalse(ds.AreInSameSet("A1", "A5"), L"A1 and A5 are in the same set");
            Assert::IsFalse(ds.AreInSameSet("A1", "A6"), L"A1 and A6 are in the same set");
            Assert::IsFalse(ds.AreInSameSet("A1", "A7"), L"A1 and A7 are in the same set");
            Assert::IsFalse(ds.AreInSameSet("A1", "A8"), L"A1 and A8 are in the same set");
            Assert::IsFalse(ds.AreInSameSet("A1", "A9"), L"A1 and A9 are in the same set");

            Assert::IsFalse(ds.IsSinglePath());

            ds.Union("A1", "A4");
            ds.Union("A7", "A6");
            ds.Union("A4", "A6");

            Assert::IsTrue(ds.IsSinglePath());

            Assert::IsTrue(ds.AreInSameSet("A1", "A3"), L"A1 and A3 are not in the same set");
            Assert::IsTrue(ds.AreInSameSet("A1", "A4"), L"A1 and A4 are not in the same set");
            Assert::IsTrue(ds.AreInSameSet("A1", "A5"), L"A1 and A5 are not in the same set");
            Assert::IsTrue(ds.AreInSameSet("A1", "A6"), L"A1 and A6 are not in the same set");
            Assert::IsTrue(ds.AreInSameSet("A1", "A7"), L"A1 and A7 are not in the same set");
            Assert::IsTrue(ds.AreInSameSet("A1", "A8"), L"A1 and A8 are not in the same set");
            Assert::IsTrue(ds.AreInSameSet("A1", "A9"), L"A1 and A9 are not in the same set");
        }
    };
}