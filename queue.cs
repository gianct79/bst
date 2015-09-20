/*
 * Copyleft GTO Inc. All rights reversed.
 */

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace gtlib
{
    public class Queue<T> : IEnumerable
    {
        class Node
        {
            public T value;
            public Node next;
        }

        class QueueEnum : IEnumerator<T>
        {
            Queue<T> queue;
            Node current;

            public QueueEnum(Queue<T> parent)
            {
                queue = parent;
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
                    current = queue.first;
                else
                    current = current.next;

                return (current != null);
            }

            public void Reset()
            {
                current = null;
            }
        }

        Node first, last;

        public void Push(T value)
        {
            Node n = new Node
            {
                value = value,
            };

            if (first == null)
                first = n;
            else
                last.next = n;

            last = n;
        }

        public T Pop()
        {
            if (first == null)
                throw new Exception("The queue is empty.");

            T value = first.value;
            first = first.next;

            if (first == null)
                last = null;

            return value;
        }

        public bool Empty()
        {
            return (first == null);
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            for (var it = first; it != null; it = it.next)
                sb.AppendFormat("{0} ", it.value);
            return sb.ToString();
        }

        public IEnumerator GetEnumerator()
        {
            return new QueueEnum(this);
        }
    }
}
