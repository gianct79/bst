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
        class Node
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

        public void PushHead(T value)
        {
            Node n = new Node
            {
                value = value,
            };

            if (tail == null)
                tail = n;
            else
            {
                n.next = head;
                head.prev = n;
            }

            head = n;
        }

        public void PushTail(T value)
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
        }

        public T PopHead()
        {
            if (head == null)
                throw new Exception("The deque is empty.");

            T value = head.value;
            head = head.next;

            if (head == null)
                tail = null;
            else
                head.prev = null;

            return value;
        }

        public T PopTail()
        {
            if (tail == null)
                throw new Exception("The deque is empty.");

            T value = tail.value;
            tail = tail.prev;

            if (tail == null)
                head = null;
            else
                tail.next = null;

            return value;
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
            return sb.ToString(0, sb.Length - 1);
        }

        public IEnumerator GetEnumerator()
        {
            return new DequeEnum(this);
        }
    }
}
