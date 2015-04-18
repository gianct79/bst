/*
* Copyleft 1979-2013 GTO Inc. All rights reversed.
*/

using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace gtlib
{
    public class BinaryTree<T>
    {
        public class Node
        {
            public T value;
            public Node left;
            public Node right;
        }

        private Node root = null;

        private Node Search(T value, Node node)
        {
            if (node != null)
            {
                Comparer<T> cmp = Comparer<T>.Default;
                if (cmp.Compare(value, node.value) < 0)
                    return Search(value, node.left);
                else if (cmp.Compare(value, node.value) > 0)
                    return Search(value, node.right);
            }
            return node;
        }

        public Node Search(T value)
        {
            return Search(value, root);
        }

        private Node Add(T value, Node node)
        {
            Comparer<T> cmp = Comparer<T>.Default;
            if (node == null)
                node = new Node { value = value };
            else if (cmp.Compare(value, node.value) < 0)
                node.left = Add(value, node.left);
            else if (cmp.Compare(value, node.value) > 0)
                node.right = Add(value, node.right);
            return node;
        }

        public void Add(T value)
        {
            root = Add(value, root);
        }

        private Node Ancestor(Node q, Node r)
        {
            if (r.right != null)
                r.right = Ancestor(q, r.right);
            else
            {
                q.value = r.value;
                r = r.left;
            }
            return r;
        }

        private Node Remove(T value, Node node)
        {
            if (node != null)
            {
                Comparer<T> cmp = Comparer<T>.Default;
                if (cmp.Compare(value, node.value) < 0)
                    node.left = Remove(value, node.left);
                else if (cmp.Compare(value, node.value) > 0)
                    node.right = Remove(value, node.right);
                else
                {
                    if (node.right == null)
                        node = node.left;
                    else if (node.left == null)
                        node = node.right;
                    else
                        node.left = Ancestor(node, node.left);
                }
            }
            return node;
        }

        public void Remove(T value)
        {
            root = Remove(value, root);
        }

        private void Print(StringBuilder sb, Node node, int depth, char connector)
        {
            if (node == null)
                return;

            Print(sb, node.right, depth + 1, '/');

            for (int i = depth; i-- > 0; )
                sb.Append('\t');

            sb.AppendFormat(" {0} -- {1}\n", connector, node.value);

            Print(sb, node.left, depth + 1, '\\');
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            Print(sb, root, 0, '+');
            return sb.ToString();
        }
    }
}
