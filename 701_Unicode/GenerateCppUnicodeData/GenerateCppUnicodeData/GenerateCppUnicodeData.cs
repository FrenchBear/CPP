// Generates a table of codepoint -> codepoint lowercase no accent for C++
// Only for chars in following blocks:
// 0020..007F;Basic Latin(ASCII); Latin;European Scripts; Scripts
// 0080..009F;ASCII Controls C1;;Specials;Symbols and Punctuation
// 00A0..00FF;Latin-1 Supplement;Latin;European Scripts; Scripts
// 0100..017F;Latin Extended-A;Latin;European Scripts; Scripts
// 0180..024F;Latin Extended-B;Latin;European Scripts; Scripts
//
// 2019-11-07   PV

using System;
using System.Diagnostics;
using System.Text;
using static System.Console;

namespace GenerateCppUnicodeData
{
    class GenerateCppUnicodeData
    {
        static void Main()
        {
            OutputEncoding = System.Text.Encoding.UTF8;
            for (int i = 32; i < 0x24f; i++)
            {
                string s = new string((char)i, 1);
                string t = s.Normalize(NormalizationForm.FormD).ToLowerInvariant();
                string u = "";
                foreach (char c in t)
                    if (char.IsLetter(c))
                        u += new string(c, 1);

                if (s != u && u.Length>=1 && (int)u[0]<=0x24f)
                {
                    if (u.Length != 1) Debugger.Break();
                    WriteLine($"{{0x{i:x}, 0x{(int)u[0]:x}}},\t// {(char)i}");
                }
            }
        }
    }
}
