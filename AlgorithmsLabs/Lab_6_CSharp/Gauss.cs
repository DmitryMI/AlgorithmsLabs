using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_6_CSharp
{
    class Gauss
    {
        /*private static double GetCoefficients(int index, List<double> ders, List<double> x)
        {
            return 2 / (1 - x[index] * x[index]) / (ders[index] * ders[index]);
        }*/

        public static List<double> Formulae(int n, List<double> ders, List<double> x)
        {
            List<double> result = new List<double>();
            for (int i = 0; i < n; i++)
            {
                double tmp = 2.0f / (1.0f - x[i] * x[i]) / (ders[i] * ders[i]);
                result.Add(tmp);
            }
            return result;
        }


    }
}
