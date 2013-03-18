/*
* Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
*/

using System;
using System.Threading;

namespace gtlib
{
    class Buffer<T>
    {
        class Node
        {
            public T value;
            public Node next;
        }

        Node curr;

        public Buffer(int size)
        {
            Node first = curr = new Node();
            for (int i = 1; i < size; i++)
            {
                curr.next = new Node();
                curr = curr.next;
            }
            curr.next = first;
            curr = first;
        }

        public void Push(T value)
        {
            curr.value = value;
            curr = curr.next;
        }

        public T Get()
        {
            return curr.value;
        }
    }

    class Throttle
    {
        Buffer<int> slots;

        public Throttle(int n)
        {
            slots = new Buffer<int>(5);
        }

        public bool Serve(long ticks)
        {
            int epoch = (int)((ticks - 621355968000000000) / 10000);

            if ((epoch - slots.Get()) > 1000)
            {
                slots.Push(epoch);
                return true;
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
