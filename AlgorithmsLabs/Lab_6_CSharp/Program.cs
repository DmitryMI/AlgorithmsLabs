using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_6_CSharp
{
    class Program
    {
        static double function(double t)
        {
            return Math.Exp(-t * t / 2);
        }
        static double F(double x, double alpha, List<double> t, List<double> weights, Legendre.FunctionPrimitive func)
        {
            double result = 0;
            int amount = t.Count;

            for (int i = 0; i < amount; i++)
            {
                result += weights[i] * func((x / 2.0f) * (t[i] + 1));
            }
            result *= x / 2.0f;
            return result - alpha;
        }

        static void PrintList(List<double> list)
        {
            foreach (var e in list)
            {
                Console.Write("{0} ", e);
            }
            Console.WriteLine();
        }
        static void Main(string[] args)
        {
            // Входные параметры
            double alpha;
            int degree;

            Console.Write("State the alpha parameter: ");
            //cin >> alpha;
            alpha = Double.Parse(Console.ReadLine());
            Console.Write("State the degree of Legendre polinom: ");
            degree = Int32.Parse(Console.ReadLine());

            alpha *= Math.Sqrt(2 * Math.PI);

            List<double> x = new List<double>();
            List<double> polinom = new List<double>();
            List<double> polinomDerivative = new List<double>();
            Legendre.GetRoots(x, polinom, polinomDerivative, degree);

            Console.WriteLine("Roots of polynomial: ");
            PrintList(x);

            List<double> coefs = Gauss.Formulae(degree, polinomDerivative, x);

            Console.WriteLine("Weight coefficients: ");
            PrintList(coefs);

            Legendre intLegendre = new Legendre(F, function);
            double result = intLegendre.Integral(0, 5, alpha, x, coefs);

            Console.WriteLine("Result is: " + result);
            Console.ReadKey();
        }
    }
}
