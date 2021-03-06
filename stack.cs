/*
 * Copyleft GTO Inc. All rights reversed.
 */

using System;
using System.Text;

namespace gtlib
{
    public class Stack<T>
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
                throw new Exception("The stack is empty.");

            T value = top.value;
            top = top.prev;

            return value;
        }

        public bool Empty()
        {
            return (top == null);
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            for (Node it = top; it != null; it = it.prev)
                sb.AppendFormat("{0} ", it.value);
            return sb.ToString();
        }
    }
}
