/*
* Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
*/

using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace gtlib
{
    public class SBinaryTree<T>
    {
        public enum Bent
        {
            Hor,
            Ver,
        }

        public class Node
        {
            public T value;

            public Node left;
            public Node right;

            public Bent refL;
            public Bent refR;
        }

        private Node root = null;
        private bool sbb = true;

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

        private Node Ll(Node ap)
        {
            Node ap1 = ap.left;
            ap.left = ap1.right;
            ap1.right = ap;
            ap1.refL = Bent.Ver;
            ap.refL = Bent.Ver;
            ap = ap1;
            return ap;
        }

        private Node Lr(Node ap)
        {
            Node ap1 = ap.left;
            Node ap2 = ap1.right;
            ap1.refR = Bent.Ver;
            ap.refL = Bent.Ver;
            ap1.right = ap2.left;
            ap2.left = ap1;
            ap.left = ap2.right;
            ap2.right = ap;
            ap = ap2;
            return ap;
        }

        private Node Rr(Node ap)
        {
            Node ap1 = ap.right;
            ap.right = ap1.left;
            ap1.left = ap;
            ap1.refR = Bent.Ver;
            ap.refR = Bent.Ver;
            ap = ap1;
            return ap;
        }

        private Node Rl(Node ap)
        {
            Node ap1 = ap.right;
            Node ap2 = ap1.left;
            ap1.refL = Bent.Ver;
            ap.refR = Bent.Ver;
            ap1.left = ap2.right;
            ap2.right = ap1;
            ap.right = ap2.left;
            ap2.left = ap;
            ap = ap2;
            return ap;
        }

        private Node Add(T value, Node parent, Node child, bool left)
        {
            Comparer<T> cmp = Comparer<T>.Default;
            if (child == null)
            {
                child = new Node { value = value, refL = Bent.Ver, refR = Bent.Ver };
                if (parent != null)
                    if (left)
                        parent.refL = Bent.Hor;
                    else
                        parent.refR = Bent.Hor;
                sbb = false;
            }
            else if (cmp.Compare(value, child.value) < 0)
            {
                child.left = Add(value, child, child.left, true);
                if (!sbb)
                {
                    if (child.refL == Bent.Hor)
                    {
                        if (child.left.refL == Bent.Hor)
                            child = Ll(child);
                        else if (child.left.refR == Bent.Hor)
                            child = Lr(child);

                        if (parent != null)
                            if (left)
                                parent.refL = Bent.Hor;
                            else
                                parent.refR = Bent.Hor;
                    }
                    else
                        sbb = true;
                }
            }
            else if (cmp.Compare(value, child.value) > 0)
            {
                child.right = Add(value, child, child.right, false);
                if (!sbb)
                {
                    if (child.refR == Bent.Hor)
                    {
                        if (child.right.refR == Bent.Hor)
                            child = Rr(child);
                        else if (child.right.refL == Bent.Hor)
                            child = Rl(child);

                        if (parent != null)
                            if (left)
                                parent.refL = Bent.Hor;
                            else
                                parent.refR = Bent.Hor;
                    }
                    else
                        sbb = true;
                }
            }
            else
                sbb = true;
            return child;
        }

        public void Add(T value)
        {
            root = Add(value, null, root, true);
        }

        private Node shortL(Node ap)
        {
            if (ap.refL == Bent.Hor)
            {
                ap.refL = Bent.Ver;
                sbb = true;
            }
            else if (ap.refR == Bent.Hor)
            {
                Node ap1 = ap.right;
                ap.right = ap1.left;
                ap1.left = ap;
                ap = ap1;
                if (ap.left.right.refL == Bent.Hor)
                {
                    ap.left = Rl(ap.left);
                    ap.refL = Bent.Hor;
                }
                else if (ap.left.right.refR == Bent.Hor)
                {
                    ap.left = Rr(ap.left);
                    ap.refL = Bent.Hor;
                }
                sbb = true;
            }
            else
            {
                ap.refR = Bent.Hor;
                if (ap.right.refL == Bent.Hor)
                {
                    ap = Rl(ap);
                    sbb = true;
                }
                else if (ap.right.refR == Bent.Hor)
                {
                    ap = Rr(ap);
                    sbb = true;
                }
            }
            return ap;
        }

        private Node shortR(Node ap)
        {
            if (ap.refR == Bent.Hor)
            {
                ap.refR = Bent.Ver;
                sbb = true;
            }
            else if (ap.refL == Bent.Hor)
            {
                Node ap1 = ap.left;
                ap.left = ap1.right;
                ap1.right = ap;
                ap = ap1;
                if (ap.right.left.refR == Bent.Hor)
                {
                    ap.right = Lr(ap.right);
                    ap.refR = Bent.Hor;
                }
                else if (ap.right.left.refL == Bent.Hor)
                {
                    ap.right = Ll(ap.right);
                    ap.refR = Bent.Hor;
                }
                sbb = true;
            }
            else
            {
                ap.refL = Bent.Hor;
                if (ap.left.refR == Bent.Hor)
                {
                    ap = Lr(ap);
                    sbb = true;
                }
                else if (ap.left.refL == Bent.Hor)
                {
                    ap = Ll(ap);
                    sbb = true;
                }
            }
            return ap;
        }

        private Node Ancestor(Node q, Node r)
        {
            if (r.right != null)
            {
                r.right = Ancestor(q, r.right);
                if (!sbb)
                    r = shortR(r);
            }
            else
            {
                q.value = r.value;
                r = r.left;
                if (r != null)
                    sbb = true;
            }
            return r;
        }

        private Node Remove(T value, Node node)
        {
            Comparer<T> cmp = Comparer<T>.Default;

            if (node == null)
            {
                sbb = true;
            }
            else if (cmp.Compare(value, node.value) < 0)
            {
                node.left = Remove(value, node.left);
                if (!sbb)
                    node = shortL(node);
            }
            else if (cmp.Compare(value, node.value) > 0)
            {
                node.right = Remove(value, node.right);
                if (!sbb)
                    node = shortR(node);
            }
            else
            {
                sbb = false;
                if (node.left == null)
                {
                    node = node.right;
                    if (node != null)
                        sbb = true;
                }
                else if (node.right == null)
                {
                    node = node.left;
                    if (node != null)
                        sbb = true;
                }
                else
                {
                    node.left = Ancestor(node, node.left);
                    if (!sbb)
                        node = shortL(node);
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
