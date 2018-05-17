using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_5_CSharp
{
    class Program
    {
        static void Exit(bool pause)
        {
            if(pause)
                Console.ReadKey();
            Environment.Exit(0);
        }

        static string ListToStr<T>(List<T> list)
        {
            string str = "";
            foreach (var el in list)
            {
                str += el.ToString() + "\n";
            }
            return str;
        }

        static void Main(string[] args)
        {
            // Source values
            int p = 1, t = 1;
            try
            {
                Console.Write("State Pressure: ");
                p = Int32.Parse(Console.ReadLine() ?? throw new ArgumentNullException());
                Console.Write("State Temperature: ");
                t = Int32.Parse(Console.ReadLine() ?? throw new ArgumentNullException());
            }
            catch (ArgumentNullException ex)
            {
                Console.WriteLine("ERROR: Line can not be empty");
                Exit(true);
            }

            double
                g = 0,
                k = 1.38e-23,
                ne = Math.Exp(-3.27),
                n1 = 7.242e+3 * p / t - 2 * ne,
                n2 = ne;
            List<double> listE = new List<double>() { 12.13, 20.96, 31.05, 42.2 };
            List<double> listZ = new List<double>() { 0, 1, 2, 3, 4 };
            List<double> listQ = new List<double>() { 1.0895, 4.65, 7.41, 11.0, 15.0 };
            List<double> values = new List<double>()
            {
                Math.Log(ne),
                Math.Log(n1),
                Math.Log(n2),
                -1,
                -1,
                -1
            };

            Console.WriteLine("Source values: \n");
            Console.WriteLine(ListToStr(values));

            // answer,gamma = refinement(values, listQ, listE, listZ, g, p, t);
            SolverResult result = Solver.Refinement(values, listQ, listE, listZ, g, p, t);

            Console.WriteLine("Result: " + ListToStr(result.A));
            Console.WriteLine("Gamma: " + result.G);

            Exit(true);
        }
    }
}
