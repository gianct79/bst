/*
* Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
*/

using System;
using System.Text;

namespace gtlib
{
    class Stack<T>
    {
        class Node
        {
            public T value;
            public Node prev;
        }

        Node top;

        public void Push(T value)
        {
            Node n = new Node
            {
                value = value,
                prev = top,
            };

            top = n;
        }

        public T Pop()
        {
            if (top == null)
                throw new Exception("underflow");

            T value = top.value;
            top = top.prev;

            return value;
        }

        public bool IsEmpty()
        {
            return (top == null);
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            for (Node it = top; it != null; it = it.prev)
            {
                sb.AppendFormat("{0} ", it.value);
            }
            return sb.ToString();
        }
    }
}
