#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../src/gcpqlParser/common/PODVariant.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace filterParserTest
{		
	TEST_CLASS(PODVariantTests)
	{
	public:
		
		TEST_METHOD(PODVariantIntegerTest)
		{
			PODVariant pv(1);
			Assert::IsTrue(pv.Valid());
			Assert::IsTrue(pv.Is<int>());
			Assert::IsFalse(pv.Is<bool>());
			Assert::IsFalse(pv.Is<double>());
			Assert::IsFalse(pv.Is<long>());
			Assert::AreEqual(1, pv.Get<int>());
			Assert::AreEqual(1L, pv.GetIntegralValue());
			Assert::IsTrue(pv.IsTrue());

			pv.Set<int>(0);

			Assert::AreEqual(0, pv.Get<int>());
			Assert::AreEqual(0L, pv.GetIntegralValue());
			bool res = pv.IsTrue();
			Assert::IsFalse(pv.IsTrue());
		}
		
		TEST_METHOD(PODVariantLongTest)
		{
			PODVariant pv(1L);
			Assert::IsTrue(pv.Valid());
			Assert::IsTrue(pv.Is<long>());
			Assert::IsFalse(pv.Is<bool>());
			Assert::IsFalse(pv.Is<double>());
			Assert::IsFalse(pv.Is<int>());
			Assert::AreEqual(1L, pv.Get<long>());
			Assert::AreEqual(1L, pv.GetIntegralValue());
			Assert::IsTrue(pv.IsTrue());

			pv.Set<long>(0L);

			Assert::IsFalse(pv.IsTrue());
			Assert::AreEqual(0L, pv.Get<long>());
			Assert::AreEqual(0L, pv.GetIntegralValue());
		}
		TEST_METHOD(PODVariantDoubleTest)
		{
			PODVariant pv(1.0);
			Assert::IsTrue(pv.Valid());
			Assert::IsTrue(pv.Is<double>());
			Assert::IsFalse(pv.Is<bool>());
			Assert::IsFalse(pv.Is<int>());
			Assert::IsFalse(pv.Is<long>());
			Assert::IsTrue( fabs(1.0 - pv.Get<double>()) <= 0.00001);
			Assert::AreEqual(1L, pv.GetIntegralValue());
			Assert::IsTrue(pv.IsTrue());

			pv.Set<double>(0.0);

			Assert::IsFalse(pv.IsTrue());
			Assert::IsTrue(fabs(pv.Get<double>()) <= 0.00001);
			Assert::AreEqual(0L, pv.GetIntegralValue());
		}

		TEST_METHOD(PODVariantBoolTest)
		{
			PODVariant pv(true);
			Assert::IsTrue(pv.Valid());
			Assert::IsTrue(pv.Is<bool>());
			Assert::IsFalse(pv.Is<int>());
			Assert::IsFalse(pv.Is<double>());
			Assert::IsFalse(pv.Is<long>());
			Assert::AreEqual(true, pv.Get<bool>());
			Assert::AreEqual(1L, pv.GetIntegralValue());
			Assert::IsTrue(pv.IsTrue());

			pv.Set<bool>(false);

			Assert::IsFalse(pv.IsTrue());
			Assert::AreEqual(false, pv.Get<bool>());
			Assert::AreEqual(0L, pv.GetIntegralValue());
		}
	};
}