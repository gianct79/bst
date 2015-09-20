/*
 * Copyleft GTO Inc. All rights reversed.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace gtlib
{
    class Building
    {
        public int lx { get; set; }
        public int rx { get; set; }
        public int h { get; set; }

        public Building(int x, int h, int w)
        {
            this.lx = x;
            this.h = h;
            this.rx = x + w;
        }

        public static Building Parse(string values)
        {
            string[] v = values.Split(',');

            if (v.Length != 3)
                throw new ArgumentException("Sin loi man.");

            return new Building(
                int.Parse(v[0]), int.Parse(v[1]), int.Parse(v[2]));
        }
    }

    class Skyline
    {
        class Strip
        {
            public int lx { get; set; }
            public int h { get; set; }

            public Strip(int lx, int h)
            {
                this.lx = lx;
                this.h = h;
            }
        }

        Queue<Strip> strips = new Queue<Strip>();

        void PushTail(Strip strip)
        {
            strips.Enqueue(strip);
        }

        void PushTail(Skyline sk)
        {
            while (sk.Count > 0)
                strips.Enqueue(sk.PopHead());
        }

        public int Perimeter
        {
            get
            {
                int p = 0;
                Strip prev = new Strip(strips.Count > 0 ? Head.lx : 0, 0);
                foreach (Strip strip in strips)
                {
                    p += Math.Abs(strip.lx - prev.lx);
                    p += Math.Abs(strip.h - prev.h);

                    prev = strip;
                }
                return p;
            }
        }

        Strip Head { get { return strips.Peek(); } }

        Strip PopHead()
        {
            return strips.Dequeue();
        }

        int Count { get { return strips.Count; } }

        public static Skyline Create(ICollection<Building> buildings)
        {
            Building[] array = buildings.OrderBy(a => a.lx).ToArray();

            return Create(array, 0, array.Length - 1);
        }

        static Skyline Create(Building[] B, int lo, int hi)
        {
            Skyline sk;

            if (B.Length == 0) // die
                sk = new Skyline();
            else if (lo == hi)
            {
                // skyline from building
                sk = new Skyline();
                sk.PushTail(new Strip(B[lo].lx, B[lo].h));
                sk.PushTail(new Strip(B[lo].rx, 0));
            }
            else
            {
                int mid = (lo + hi) / 2;
                Skyline sk1 = Create(B, lo, mid);
                Skyline sk2 = Create(B, mid + 1, hi);
                // merge the two buildings to create a bigger building
                sk = Merge(sk1, sk2);
            }

            return sk;
        }

        static Skyline Merge(Skyline sk1, Skyline sk2)
        {
            Skyline sk = new Skyline();

            int curH1 = 0;
            int curH2 = 0;
            int prevH = 0;

            // create intersections
            while (sk1.Count > 0 && sk2.Count > 0)
            {
                int curX;
                if (sk1.Head.lx < sk2.Head.lx)
                {
                    curX = sk1.Head.lx;
                    curH1 = sk1.Head.h;
                    sk1.PopHead();
                }
                else
                {
                    curX = sk2.Head.lx;
                    curH2 = sk2.Head.h;
                    sk2.PopHead();
                }
                int maxH = Math.Max(curH1, curH2);
                if (maxH != prevH) // avoid intersections on same height
                {
                    sk.PushTail(new Strip(curX, maxH));
                    prevH = maxH;
                }
            }

            // append reminders (if exist)
            sk.PushTail(sk1);
            sk.PushTail(sk2);

            return sk;
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendFormat("Perimeter: {0} ", Perimeter);
            if (strips.Count > 0)
            {
                sb.Append("(");
                foreach (Strip strip in strips)
                    sb.AppendFormat("{0},{1},", strip.lx, strip.h);
                sb.Replace(',', ')', sb.Length - 1, 1);
            }
            return sb.ToString();
        }
    }

    class Runner
    {
        static void Main(string[] args)
        {
            IList<Building> buildings = new List<Building>();

            Console.WriteLine("Enter values x, h, w; one building per line...");

            string values;
            while ((values = Console.ReadLine()) != null)
                buildings.Add(Building.Parse(values));

            Skyline skyline = Skyline.Create(buildings);
            Console.WriteLine(skyline);
        }
    }
}
