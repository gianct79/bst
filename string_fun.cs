/*
 * Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
 */

using System;
using System.Collections.Generic;
using System.IO;

namespace gtlib
{
    static class StringExtensions
    {
        public static string Sort(this string str)
        {
            char[] array = str.ToCharArray();
            Array.Sort(array);

            return new string(array);
        }

        public static int CountWords(this string str)
        {
            char[] array = str.ToCharArray();

            int cnt = 0;
            int s = 0;
            int r = 0;

            for (; r < array.Length; r++)
            {
                if (Char.IsWhiteSpace(array[r]))
                {
                    if (s < r)
                        cnt++;
                    s = r + 1;
                }
            }
            if (s < r)
                cnt++;

            return cnt;        
        }

        public static string Swap(this string str, int a, int b)
        {
            char[] array = str.ToCharArray();

            if (a >= array.Length || b >= array.Length)
                throw new ArgumentOutOfRangeException();

            char temp = array[a];
            array[a] = array[b];
            array[b] = temp;

            return new string(array);
        }
    }

    class StringFun
    {
        Dictionary<string, List<string>> dictionary = new Dictionary<string, List<string>>();

        public void Load()
        {
            int wordCount = 0;
            string word;

            using (TextReader reader = new StreamReader("dict.txt"))
            {
                while ((word = reader.ReadLine()) != null)
                {
                    string key = word.Sort();

                    if (!dictionary.ContainsKey(key))
                        dictionary.Add(key, new List<string>());

                    dictionary[key].Add(word);
                    wordCount++;
                }
            }

            dictionary.Add(string.Empty, new List<string>());
            Console.WriteLine(string.Format("{0} word(s) loaded, index size is {1}", wordCount, dictionary.Count));
        }

        public List<string> FindAnagrams(string word)
        {
            string key = word.Sort();

            if (dictionary.ContainsKey(key))
                return dictionary[key];

            return dictionary[string.Empty];
        }

        public void Permute(string word, int index)
        {
            if (word.Length == index)
            {
                Console.Write(word + ",");
            }
            else
            {
                for (int i = index; i < word.Length; ++i)
                {
                    word = word.Swap(i, index);
                    Permute(word, index + 1);
                    word = word.Swap(index, i);
                }
            }
        }

        public void Shuffle(string word)
        {
            Random rand = new Random();

            int n = word.Length;

            for (int i = 0; i < n; ++i)
            {
                int j = i + (rand.Next(n - i));
                Console.WriteLine(word.Swap(j, i));
            }
        }
    }

    class Program
    {
        public static void Main()
        {
            string menon = "menon";
            Console.WriteLine(string.Format("{0} rules", menon));

            Console.WriteLine("the quick brown fox jumps over the lazy dog!".CountWords());
            Console.WriteLine(string.Empty.CountWords());
            Console.WriteLine("  ".CountWords());
            Console.WriteLine(" a".CountWords());

            StringFun stringFun = new StringFun();
            stringFun.Load();

            string word;
            while (true)
            {
                Console.Write("Word [.quit]: ");
                word = Console.ReadLine();

                if (word.Equals(".quit"))
                    break;

                List<string> words = stringFun.FindAnagrams(word);
                Console.Write(string.Format("{0}: ", words.Count));

                foreach (var it in words)
                    Console.Write(string.Format("{0}, ", it));

                Console.WriteLine();

                stringFun.Permute(word, 0);
                Console.WriteLine();

                stringFun.Shuffle(word);
                Console.WriteLine();
            }
        }
    }
}
