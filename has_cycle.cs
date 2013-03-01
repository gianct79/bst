/*
* Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
*/

using System;
using System.Text;

namespace runner
{
    class Queue<T>
    {
        public class Node
        {
            public T value;
            public Node next;
        }

        Node head, tail;

        public Node Push(T value)
        {
            Node n = new Node
            {
                value = value,
            };

            if (head == null)
                head = n;
            else
                tail.next = n;
            tail = n;

            return n;
        }

        public T Pop()
        {
            if (head == null)
                throw new Exception("Queue is empty.");

            T value = head.value;
            head = head.next;

            if (head == null)
                tail = null;

            return value;
        }

        public void Remove(Node node)
        {
            for (Node prev = null, it = head; it != null; prev = it, it = it.next)
            {
                if (it.Equals(node))
                {
                    if (it == head)
                        head = it.next;
                    else
                        prev.next = it.next;

                    if (it == tail)
                        tail = prev;
                }
            }
        }

        public bool IsEmpty()
        {
            return (head == null);
        }

        public bool HasCycle()
        {
            Node slow = head;
            Node fast = head;

            while (slow != null && fast != null)
            {
                fast = fast.next;
                //if (fast.Equals(slow))
                //    return true;

                if (fast != null)
                    fast = fast.next;

                if (slow.Equals(fast))
                    return true;

                slow = slow.next;
            }

            return false;
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            if (!HasCycle())
            {
                for (Node it = head; it != null; it = it.next)
                    sb.AppendFormat("{0} ", it.value);
            }
            return sb.ToString();
        }
    }

    class Runner
    {
        static void Main(string[] args)
        {
            Queue<char> queue = new Queue<char>();

            Queue<char>.Node a = queue.Push('a');
            //Queue<char>.Node b = queue.Push('b');
            //Queue<char>.Node c = queue.Push('c');
            //Queue<char>.Node d = queue.Push('d');

            Console.WriteLine(queue.IsEmpty());
            Console.WriteLine(queue.HasCycle());

            //d.next = b;
            a.next = a;
            Console.WriteLine(queue.HasCycle());
        }
    }
}
