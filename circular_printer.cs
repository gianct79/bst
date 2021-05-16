using System;
using System.Collections.Generic;
					
public class Program
{
	public static int GetTime(string s)
	{
		if (string.IsNullOrWhiteSpace(s))
			return 0;

		int sum = 0;

		List<char> a = new List<char>(s.ToUpperInvariant().ToCharArray());
		a.Insert(0, 'A');

		for (int i = 1; i < a.Count; ++i)
		{
			int diff = Math.Abs(a[i - 1] - a[i]);
			
			if (diff > 13)
				diff = 26 - diff;
			
			sum += diff;
		}
		
		return sum;
	}
	
	public static void Main()
	{
		Console.WriteLine(GetTime("XMNP"));
	}
}
