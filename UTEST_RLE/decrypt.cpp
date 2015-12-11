#include "stdafx.h"
#include "CppUnitTest.h"
#include "RLE.H"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTEST_RLE
{
  TEST_CLASS(RLE_DECRYPT)
  {
  public:

    TEST_METHOD(Check_DecryptSizeAndNullptrBuffers)
    {
      char dest[4]{};
      Assert::IsTrue(decrypt(dest, "234", 2),
        L"Function \"decrypt\" return false, size buffer must be more 1 and"
        " no one buffer no must be zero point");
    }

    TEST_METHOD(Check_Decrypt)
    {
      char expected[1024]{ "[p,mojugggnhdbssvgf" };
      char output[1024]{};
      wchar_t input[1024]{ L"\xF9[p,moju\3g\xFCnhdb\2s\xFDvgf" };
      decrypt(output, expected, 23);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(input, unicode.str().c_str(), L"wrong decrypt");
    }

    TEST_METHOD(Check_Decrypt_OnlySome)
    {
      char expected[1024]{ "gggggggggg" };
      char output[1024]{};
      wchar_t input[1024]{ L"\x0Ag" };
      decrypt(output, expected, 2);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(input, unicode.str().c_str(), L"wrong decrypt");
    }

    TEST_METHOD(Check_Decrypt_OnlyDifferent)
    {
      char expected[1024]{ "[p,mojugnhdbsvgf" };
      char output[1024]{};
      wchar_t input[1024]{ L"\xF0[p,mojugnhdbsvgf" };
      decrypt(output, expected, 17);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(input, unicode.str().c_str(), L"wrong decrypt");
    }

    TEST_METHOD(Check_Decrypt_BinaryData)
    {
      char expected[1024]{ "\x1\x0\x2\x2" };
      char output[1024]{};
      wchar_t input[1024]{ L"\xFE\x1\x0\x02\x2" };
      decrypt(output, expected, 5);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(input, unicode.str().c_str(), L"wrong decrypt");
    }

    TEST_METHOD(Check_Decrypt_BinarySome)
    {
      char expected[1024]{ "\xF\xF\xF\xF\xF\xF\xF\xF\xF\xF" };
      char output[1024]{};
      wchar_t input[1024]{ L"\x0A\x0F" };
      decrypt(output, expected, 2);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(input, unicode.str().c_str(), L"wrong decrypt");
    }

    TEST_METHOD(Check_Decrypt_BinaryDifferent)
    {
      char expected[1024]{ "\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\x0A\x0B\x0C\x0D\x0E\x0F" };
      char output[1024]{};
      wchar_t input[1024]{ L"\xF0\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\x0A\x0B\x0C\x0D\x0E\x0F" };
      decrypt(output, expected, 16);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(input, unicode.str().c_str(), L"wrong decrypt");
    }
  };
}
