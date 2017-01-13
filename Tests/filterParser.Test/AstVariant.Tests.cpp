#include "stdafx.h"
#include "CppUnitTest.h"

#include "src/gcpqlParser/common/AstVariant.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace filterParserTest
{		
	TEST_CLASS(AstVariantTests)
	{
	public:
		
		TEST_METHOD(AstVariantIntegerTest)
		{
			AstVariant pv(1);
			Assert::IsTrue(pv.Valid());
			Assert::IsTrue(pv.Is<int>());
			Assert::IsFalse(pv.Is<bool>());
			Assert::IsFalse(pv.Is<double>());
			Assert::IsFalse(pv.Is<long>());
			Assert::AreEqual(1, pv.Get<int>());
			Assert::AreEqual(1L, pv.AsLong());
			Assert::IsTrue(pv.IsTrue());

			pv.Set<int>(0);

			Assert::AreEqual(0, pv.Get<int>());
			Assert::AreEqual(0L, pv.AsLong());
			bool res = pv.IsTrue();
			Assert::IsFalse(pv.IsTrue());
		}
		
		TEST_METHOD(AstVariantLongTest)
		{
			AstVariant pv(1L);
			Assert::IsTrue(pv.Valid());
			Assert::IsTrue(pv.Is<long>());
			Assert::IsFalse(pv.Is<bool>());
			Assert::IsFalse(pv.Is<double>());
			Assert::IsFalse(pv.Is<int>());
			Assert::AreEqual(1L, pv.Get<long>());
			Assert::AreEqual(1L, pv.AsLong());
			Assert::IsTrue(pv.IsTrue());

			pv.Set<long>(0L);

			Assert::IsFalse(pv.IsTrue());
			Assert::AreEqual(0L, pv.Get<long>());
			Assert::AreEqual(0L, pv.AsLong());
		}
		TEST_METHOD(AstVariantDoubleTest)
		{
			AstVariant pv(1.0);
			Assert::IsTrue(pv.Valid());
			Assert::IsTrue(pv.Is<double>());
			Assert::IsFalse(pv.Is<bool>());
			Assert::IsFalse(pv.Is<int>());
			Assert::IsFalse(pv.Is<long>());
			Assert::IsTrue( fabs(1.0 - pv.Get<double>()) <= 0.00001);
			Assert::AreEqual(1L, pv.AsLong());
			Assert::IsTrue(pv.IsTrue());

			pv.Set<double>(0.0);

			Assert::IsFalse(pv.IsTrue());
			Assert::IsTrue(fabs(pv.Get<double>()) <= 0.00001);
			Assert::AreEqual(0L, pv.AsLong());
		}

		TEST_METHOD(AstVariantBoolTest)
		{
			AstVariant pv(true);
			Assert::IsTrue(pv.Valid());
			Assert::IsTrue(pv.Is<bool>());
			Assert::IsFalse(pv.Is<int>());
			Assert::IsFalse(pv.Is<double>());
			Assert::IsFalse(pv.Is<long>());
			Assert::AreEqual(true, pv.Get<bool>());
			Assert::AreEqual(1L, pv.AsLong());
			Assert::IsTrue(pv.IsTrue());

			pv.Set<bool>(false);

			Assert::IsFalse(pv.IsTrue());
			Assert::AreEqual(false, pv.Get<bool>());
			Assert::AreEqual(0L, pv.AsLong());
		}

		TEST_METHOD(AstVariantStringTest)
		{
			std::string str("string");
			AstVariant pv(&str);
			Assert::IsTrue(pv.Valid());
			Assert::IsTrue(pv.Is<std::string*>());
			Assert::IsFalse(pv.Is<int>());
			Assert::IsFalse(pv.Is<char*>());
		}

		TEST_METHOD(AstVariantCharTest)
		{
			std::string str("string");
			AstVariant pv(const_cast<char*>(str.c_str()));
			Assert::IsTrue(pv.Valid());
			Assert::IsTrue(pv.Is<char*>());
			Assert::IsFalse(pv.Is<int>());
			Assert::IsFalse(pv.Is<std::string*>());
		}
		
		TEST_METHOD(AstVariantStringCompareTest)
		{
			std::string str1("string");
			AstVariant pv1(const_cast<char*>(str1.c_str()));
			const char* str2 = "string";
			AstVariant pv2(const_cast<char*>(str2));
			Assert::IsTrue(pv1.Equal(pv2));
		}
	};
}