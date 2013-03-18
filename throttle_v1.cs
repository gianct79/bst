/*
* Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
*/

using System;
using System.Threading;

namespace gtlib
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
            int epoch = (int)((ticks - 621355968000000000) / 10000);
            for (int t = 0; t < slots.Length; t++)
            {
                if ((epoch - slots[t]) > 1000)
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
            Throttle throttle = new Throttle(3);

            int request = 0;
            while (request++ < 50)
            {
                DateTime time = DateTime.Now;
                Console.WriteLine(string.Format("{0}: {1}", time.ToString("hh:mm:ss.FFF"), throttle.Serve(time.Ticks)));
                Thread.Sleep(rand.Next(500));
            }
        }
    }
}
