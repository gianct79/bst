/*
* Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
*/

using System;
using System.Collections.Generic;
using System.Linq;

namespace gtlib
{
    class Appointment
    {
        public int start { get; set; }
        public int end { get; set; }

        public Appointment(int start, int end)
        {
            this.start = start;
            this.end = end;
        }

        public bool Conflicted(Appointment other)
        {
            if (this.start >= other.start && this.end <= other.end)
                return true;
            if (this.start <= other.start && this.end > other.start)
                return true;
            if (this.start >= other.start && other.end > this.start)
                return true;

            return false;
        }

        public static Appointment Parse(string values)
        {
            string[] v = values.Split(',');

            if (v.Length != 2)
                throw new ArgumentException("Sin loi man.");

            return new Appointment(
                int.Parse(v[0]), int.Parse(v[1]));
        }
    }

    class AppointmentList
    {
        IList<Appointment> appointments = new List<Appointment>();

        public void Add(Appointment item)
        {
            appointments.Add(item);
        }

        public void Remove(Appointment item)
        {
            appointments.Remove(item);
        }


        public int CountConflicts()
        {
            int count = 0;

            Queue<Appointment> queue = new Queue<Appointment>(appointments);
            for (int i = 0; i < queue.Count;)
            {
                Appointment a = queue.Dequeue();
                foreach (Appointment b in queue)
                    if (a.Conflicted(b))
                        count++;
            }

            return count;
        }
    }

    class Runner
    {
        static void Main(string[] args)
        {
            AppointmentList events = new AppointmentList();

            Console.WriteLine("Enter appointments (start, end); one appointment per line...");

            string values;
            while ((values = Console.ReadLine()) != null)
                events.Add(Appointment.Parse(values));

            Console.WriteLine(events.CountConflicts());
        }
    }
}
