/*
 * Copyleft Giancarlo Tomazelli. All rights reversed.
 */

using System;
using System.Text;

namespace fillMatrix
{
    class Matrix
    {
        bool [,] values;
        Random rand = new Random();

        public Matrix(byte x, byte y)
        {
            values = new bool[x,y];
        }

        public byte GetX()
        {
            return (byte)values.GetLength(0);
        }

        public byte GetY()
        {
            return (byte)values.GetLength(1);
        }

        public void Fill(byte n)
        {
            if (n > GetX() * GetY())
                throw new ArgumentException("sin loi");

            while (n > 0)
            {
                int x = rand.Next(GetX());
                int y = rand.Next(GetY());

                while (values[x, y])
                {
                    x = rand.Next(GetX());
                    y = rand.Next(GetY());
                }
                values[x, y] = true;
                n--;
            }
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();

            for (byte x = 0; x < GetX(); x++)
            {
                for (byte y = 0; y < GetY(); y++)
                {
                    sb.AppendFormat("{0} ", values[x, y] ? 1 : 0);
                }
                sb.AppendLine();
            }

            return sb.ToString();
        }
    }

    class FillMatrix
    {
        static void Main(string[] args)
        {
            Matrix m = new Matrix(25, 25);
            Console.WriteLine(m);

            m.Fill(20);
            Console.WriteLine(m);

            m = new Matrix(0, 0);
            Console.WriteLine(m);

            m.Fill(0);
        }
    }
}
