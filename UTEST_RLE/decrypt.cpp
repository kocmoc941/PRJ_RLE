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
      Assert::IsTrue(decrypt(dest, "\xFE\x31\x41", 3),
        L"Function \"decrypt\" return false, size buffer must be more 1 and"
        " no one buffer no must be zero point");
    }

    TEST_METHOD(Check_Decrypt)
    {
      wchar_t expected[1024]{ L"[p,mojugggnhdbssvgf" };
      char output[1024]{};
      char input[1024]{ "\xF9[p,moju\3g\xFCnhdb\2s\xFDvgf" };
      decrypt(output, input, 21);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(expected, unicode.str().c_str(), L"wrong decrypt");
    }

    TEST_METHOD(Check_Decrypt_OnlySome)
    {
      wchar_t expected[1024]{ L"gggggggggg" };
      char output[1024]{};
      char input[1024]{ "\x0Ag" };
      decrypt(output, input, 2);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(expected, unicode.str().c_str(), L"wrong decrypt");
    }

    TEST_METHOD(Check_Decrypt_OnlyDifferent)
    {
      wchar_t expected[1024]{ L"[p,mojugnhdbsvgf" };
      char output[1024]{};
      char input[1024]{ "\xF0[p,mojugnhdbsvgf" };
      decrypt(output, input, 17);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(expected, unicode.str().c_str(), L"wrong decrypt");
    }

    TEST_METHOD(Check_Decrypt_BinaryData)
    {
      wchar_t expected[1024]{ L"\x1\x0\x2\x2" };
      char output[1024]{};
      char input[1024]{ "\xFE\x1\x0\x02\x2" };
      decrypt(output, input, 5);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(expected, unicode.str().c_str(), L"wrong decrypt");
    }

    TEST_METHOD(Check_Decrypt_BinarySome)
    {
      wchar_t expected[1024]{ L"\xF\xF\xF\xF\xF\xF\xF\xF\xF\xF" };
      char output[1024]{};
      char input[1024]{ "\x0A\x0F" };
      decrypt(output, input, 2);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(expected, unicode.str().c_str(), L"wrong decrypt");
    }

    TEST_METHOD(Check_Decrypt_BinaryDifferent)
    {
      wchar_t expected[1024]{ L"\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\x0A\x0B\x0C\x0D\x0E\x0F" };
      char output[1024]{};
      char input[1024]{ "\xF0\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\x0A\x0B\x0C\x0D\x0E\x0F" };
      decrypt(output, input, 16);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(expected, unicode.str().c_str(), L"wrong decrypt");
    }
  };
}
