/*
 * Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
 */

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace gtlib
{
    public class Deque<T> : IEnumerable
    {
        public class Node
        {
            public T value;
            public Node prev;
            public Node next;
        }

        class DequeEnum : IEnumerator<T>
        {
            Deque<T> deque;
            Node current;

            public DequeEnum(Deque<T> parent)
            {
                deque = parent;
            }

            public T Current
            {
                get { return current.value; }
            }

            public void Dispose()
            {
            }

            object IEnumerator.Current
            {
                get { return current.value; }
            }

            public bool MoveNext()
            {
                if (current == null)
                    current = deque.head;
                else
                    current = current.next;

                return (current != null);
            }

            public void Reset()
            {
                current = null;
            }
        }

        Node head, tail;

        public Node Add(T value)
        {
            Node n = new Node
            {
                value = value,
            };

            if (head == null)
                head = n;
            else
            {
                n.prev = tail;
                tail.next = n;
            }

            tail = n;

            return tail;
        }

        public void Remove(Node node)
        {
            Node next = node.next;
            Node prev = node.prev;

            if (prev == null)
                head = next;
            else
                prev.next = next;

            if (next == null)
                tail = prev;
            else
                next.prev = prev;
        }

        public bool Empty()
        {
            return (head == null);
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            for (var it = head; it != null; it = it.next)
                sb.AppendFormat("{0} ", it.value);
            return sb.ToString();
        }

        public IEnumerator GetEnumerator()
        {
            return new DequeEnum(this);
        }
    }

    class UnorderedSet<T> : IEnumerable
    {
        Dictionary<T, Deque<T>.Node> slots = new Dictionary<T, Deque<T>.Node>();
        Deque<T> values = new Deque<T>();

        public void Insert(T value)
        {
            if (!slots.ContainsKey(value))
                slots.Add(value, values.Add(value));
        }

        public void Remove(T value)
        {
            if (slots.ContainsKey(value))
            {
                Deque<T>.Node node = slots[value];
                values.Remove(node);
                slots.Remove(value);
            }
        }

        public override string ToString()
        {
            return values.ToString();
        }

        public IEnumerator GetEnumerator()
        {
            return values.GetEnumerator();
        }
    }

    class Program
    {
        public static void Main()
        {
            UnorderedSet<int> set = new UnorderedSet<int>();

            set.Insert(1);
            set.Insert(3);
            set.Insert(5);
            set.Insert(7);
            Console.WriteLine(set);

            set.Remove(7);
            set.Remove(5);
            Console.WriteLine(set);

            set.Insert(2);
            set.Insert(4);
            set.Insert(8);
            set.Remove(3);
            Console.WriteLine(set);

            set.Remove(1);
            Console.WriteLine(set);

            set.Remove(4);
            Console.WriteLine(set);
        }
    }
}
