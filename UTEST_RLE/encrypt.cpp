#include "stdafx.h"
#include "CppUnitTest.h"
#include "RLE.H"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTEST_RLE
{		
	TEST_CLASS(RLE_ENCRYPT)
	{
	public:
		
		TEST_METHOD(Check_EncryptSizeAndNullptrBuffers)
		{
      char dest[4]{};
      Assert::IsTrue( encrypt(dest, "234", 2), 
        L"Function \"encrypt\" return false, size buffer must be more 1 and"
        " no one buffer no must be zero point");
		}

    TEST_METHOD(Check_Encrypt)
    {
      char input[1024]{"[p,mojugggnhdbssvgf"};
      char output[1024]{};
      wchar_t expected[1024]{ L"\xF9[p,moju\3g\xFCnhdb\2s\xFDvgf" };
      encrypt(output, input, strlen(input));
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(expected, unicode.str().c_str(), L"wrong encrypt");
    }

    TEST_METHOD(Check_Encrypt_OnlySome)
    {
      char input[1024]{ "gggggggggg" };
      char output[1024]{};
      wchar_t expected[1024]{ L"\x0Ag" };
      encrypt(output, input, strlen(input));
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(expected, unicode.str().c_str(), L"wrong encrypt");
    }

    TEST_METHOD(Check_Encrypt_OnlyDifferent)
    {
      char input[1024]{ "[p,mojugnhdbsvgf" };
      char output[1024]{};
      wchar_t expected[1024]{ L"\xF0[p,mojugnhdbsvgf" };
      encrypt(output, input, strlen(input));
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(expected, unicode.str().c_str(), L"wrong encrypt");
    }

    TEST_METHOD(Check_Encrypt_BinaryData)
    {
      char input[1024]{ "\x1\x0\x2\x2" };
      char output[1024]{};
      wchar_t expected[1024]{ L"\xFE\x1\x0\x02\x2" };
      encrypt(output, input, 4);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(expected, unicode.str().c_str(), L"wrong encrypt");
    }

    TEST_METHOD(Check_Encrypt_BinarySome)
    {
      char input[1024]{ "\xF\xF\xF\xF\xF\xF\xF\xF\xF\xF" };
      char output[1024]{};
      wchar_t expected[1024]{ L"\x0A\x0F"  };
      encrypt(output, input, 10);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(expected, unicode.str().c_str(), L"wrong encrypt");
    }

    TEST_METHOD(Check_Encrypt_BinaryDifferent)
    {
      char input[1024]{ "\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\x0A\x0B\x0C\x0D\x0E\x0F" };
      char output[1024]{};
      wchar_t expected[1024]{ L"\xF0\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\x0A\x0B\x0C\x0D\x0E\x0F" };
      encrypt(output, input, 16);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(expected, unicode.str().c_str(), L"wrong encrypt");
    }

    TEST_METHOD(Check_Encrypt_512B_Some)
    {
      char input[1024]{};
      for (size_t i = 0; i < 512; ++i)
        input[i] = '\xFE';
      char output[1024]{};
      wchar_t expected[1024]{ L"\x7f\xFE\x7f\xFE\x7f\xFE\x7f\xFE" };
      encrypt(output, input, 512);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(expected, unicode.str().c_str(), L"wrong encrypt");
    }

    TEST_METHOD(Check_Encrypt_512B_Different)
    {
      char input[1024]{};
      for (size_t i = 0; i < 512; ++i)
        input[i] = (char)i;
      char output[1024]{};
      char expect[1024]{};

      for (size_t j = 0; j < 4; ++j) {
        expect[128 * j] = '\x80';
        for (size_t i = 1; i < 128; ++i)
          expect[i + 128 * j] = char(i + 128 * j);
      }

      std::wstringstream expected;
      expected << expect;

      encrypt(output, input, 512);
      std::wstringstream unicode;
      unicode << output;
      Assert::AreEqual(expected.str().c_str(), unicode.str().c_str(), L"wrong encrypt");
    }

	};
}
