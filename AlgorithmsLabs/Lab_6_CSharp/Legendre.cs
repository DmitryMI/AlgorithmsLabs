using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Lab_6_CSharp
{
    class Legendre
    {
        public delegate double Function(double a, double b, List<double> t, List<double> w, FunctionPrimitive func);
        public delegate double FunctionPrimitive(double x);

        public const double RelativeAccuracy = 1e-6;
        private Function _func;
        private FunctionPrimitive _primitiveFunction;

        private static List<double> PoliLegendre(int n, double x)
        {
            var result = new List<double>();
            result.Add(1);
            result.Add(x);

            // Используем рекурсивную формулу для построения полинома Лежандра
            for (int i = 2; i < n + 1; i++)
            {
                double buff = (2.0f * i - 1) * x * result[i - 1] - (i - 1.0f) * result[i - 2];
                buff /= i;
                result.Add(buff);
            }
            return result;
        }

        private static double DerPoliLegendre(int n, List<double> poli, double x)
        {
            return (float)n / (1.0f - x * x) * (poli[n - 1] - x * poli[n]);
        }

        public static void GetRoots(List<double> x, List<double> poli, List<double> polider, int n)
        {
            // Исзодные приближения для каждого i-того корня
            for (int i = 0; i < n; i++)
            {
                x.Add(Math.Cos(Math.PI * (4 * i - 1) / (4 * n + 2)));
            }

            for (int i = 0; i < n; i++)
            {
                List<double> tmpPoli;
                double tmpDer;
                while (true)
                {
                    tmpPoli = PoliLegendre(n, x[i]);
                    tmpDer = DerPoliLegendre(n, tmpPoli, x[i]);
                    double dx = tmpPoli[n] / tmpDer;
                    x[i] -= dx;
                    if (Math.Abs(dx) < RelativeAccuracy * Math.Abs(dx) + RelativeAccuracy)
                        break;
                }
                poli.AddRange(tmpPoli);
                //polider.Add(tmpDer);
            }

            int len = x.Count;
            for (int i = 0; i < len; i++)
            {
                if (x[i] < 0)
                    x[i] = -x[i];
            }

            x.Sort();
            for (int i = 0; i < len - 1; i++)
            {
                if (Math.Abs(x[i] - x[i + 1]) < RelativeAccuracy)
                    x[i] = -x[i];
            }
            x.Sort();

            polider.Clear();
            for(int i = 0; i < n; i++)
            {
                var tmpPoli = PoliLegendre(n, x[i]);
                double tmpDer = DerPoliLegendre(n, tmpPoli, x[i]);
                polider.Add(tmpDer);
            }
        }

        public Legendre(Function func, FunctionPrimitive primitive)
        {
            _func = func;
            _primitiveFunction = primitive;
        }

        public double Integral(double down, double up, double alpha, List<double> t, List<double> w)
        {
            if (_func(down, up, t, w, _primitiveFunction) > 0)
            {
                double tmp = up;
                up = down;
                down = tmp;
            }

            if (_func(down, alpha, t, w, _primitiveFunction) > 0)
                throw new ArgumentException();

            double buffer = 0;
            int index = 0;

            while (index < 10)
            {
                buffer = (down + up) / 2;
                double forF = _func(buffer, alpha, t, w, _primitiveFunction);

                if (Math.Abs((up - buffer) / up) < RelativeAccuracy * Math.Abs(up) + RelativeAccuracy)
                    break;

                if (forF < 0)
                    down = buffer;
                else
                    up = buffer;

                //index++;
            }
            return buffer;
        }
    }
}
