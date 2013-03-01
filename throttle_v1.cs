/*
* Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
*/

using System;
using System.Threading;

namespace runner
{
    class Throttle
    {
        int[] slots;

        public Throttle(int n)
        {
            slots = new int[n];
        }

        public bool Serve(long ticks)
        {
            int epoch = (int)((ticks - 621355968000000000) / 10000000);
            for (int t = 0; t < slots.Length; t++)
            {
                if ((epoch - slots[t]) > 1)
                {
                    slots[t] = epoch;
                    return true;
                }
            }
            return false;
        }
    }

    class Runner
    {
        static void Main(string[] args)
        {
            Random rand = new Random();
            Throttle throttle = new Throttle(5);

            int request = 0;
            while (request++ < 50)
            {
                Console.WriteLine(throttle.Serve(DateTime.Now.Ticks));
                Thread.Sleep(rand.Next(500));
            }
        }
    }
}
