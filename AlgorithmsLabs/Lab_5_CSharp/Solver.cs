using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Lab_5_CSharp
{
    struct SolverResult
    {
        private double _g;
        private List<double> _a;

        public SolverResult(List<double> a, double g)
        {
            this._a = a;
            this._g = g;
        }

        public List<double> A
        {
            get { return _a; }
        }

        public double G
        {
            get { return _g; }
        }
    }
    class Solver
    {

        private static double Max(params double[] param)
        {
            double max = param[0];
            foreach (var el in param)
            {
                if (el > max)
                    max = el;
            }
            return max;
        }

        private static double Func(double T, double ve, double g, double x2, double x3, double x4, double x5, double z2,
            double z3, double z4, double z5)
        {
            double summ = (Math.Exp(x2) * z2 * z2) / (1 + z2 * z2 * g / 2) +
                          (Math.Exp(x3) * z3 * z3) / (1 + z3 * z3 * g / 2) +
                          (Math.Exp(x4) * z4 * z4) / (1 + z4 * z4 * g / 2) +
                          (Math.Exp(x5) * z5 * z5) / (1 + z5 * z5 * g / 2);
            return g * g - 5.87e10 / (T * T * T) * (Math.Exp(ve) / (1 + g / 2) + summ);
        }

        private static double HalfDivision(int t, List<double> values, List<double> z)
        {
            double a = 0,
                b = 2,
                c = (a + b) / 2;

            while (Math.Abs((b - a) / c) > 1e-5)
            {
                c = (a + b) / 2;
                double d = Func(t, values[0], a, values[2], values[3], values[4], values[5], z[1], z[2], z[3], z[4]) *
                           Func(t, values[0], c, values[2], values[3], values[4], values[5], z[1], z[2], z[3], z[4]);
                if (d > 0)
                    a = c;
                if (d < 0)
                    b = c;
            }

            return c;
        }

        private static double Ki(double qi1, double qi, int T, double ei, double deltaEi)
        {
            return (2 * 2.415e-3 * qi1 / qi * Math.Pow(T, (3.0f / 2)) * Math.Exp(-(ei - deltaEi) * 11603 / T));
        }

        private static double DeltaEi(double T, double zi1, double zi, double g)
        {
            return (8.61 * Math.Pow(10, -5) * T *
                    Math.Log(((1 + zi1 * zi1 * g / 2) * (1 + g / 2)) / (1 + zi * zi * g / 2)));
        }

        private static List<double> Gauss(MatrixDouble a)
        {
            //найти размер матрицы
            int width = a.Cols;
            int height = a.Rows;
            //WriteEquation(a);

            double[] x = new double[height]; //массив решений уравнения
            //инициализация массива корней уравнения
            for (int i = 0; i < x.Length; i++)
            {
                x[i] = a[i, width - 1];
            }

            //приведение матрицы к треугольному виду
            double m;
            for (int i = 0; i < width - 1; i++)
            for (int j = i + 1; j < height; j++)
            {
                m = a[j, i] / a[i, i];
                if (double.IsNaN(m)) m = 0;
                for (int k = 0; k < height; k++)
                    a[j, k] -= m * a[i, k];
                x[j] -= m * x[i];
            }

            for (int i = 0; i < height; i++)
                a[i, width - 1] = x[i];

            for (int i = height - 1; i >= 0; i--)
            {
                for (int j = i + 1; j < width - 1; j++)
                {
                    x[i] -= i != j ? a[i, j] * x[j] : 0;
                }
                x[i] = x[i] / a[i, i];
            }
            return new List<double>(x);
        }

        private static MatrixDouble ToMatrix(List<double> values, List<double> listQ, double g, List<double> listE, int t, List<double> listZ, int p)
        {
            double
                ve = values[0],
                x1 = values[1],
                x2 = values[2],
                x3 = values[3],
                x4 = values[4],
                x5 = values[5],
                q1 = listQ[0],
                q2 = listQ[1],
                q3 = listQ[2],
                q4 = listQ[3],
                q5 = listQ[4],
                e1 = listE[0],
                e2 = listE[1],
                e3 = listE[2],
                e4 = listE[3],
                z1 = listZ[0],
                z2 = listZ[1],
                z3 = listZ[2],
                z4 = listZ[3],
                z5 = listZ[4],
                alpha = 0.285e-11 * Math.Pow(g * t, 3);

            double[,] mdata = new double[,]
            {
                {1, -1, 1, 0, 0, 0, -(ve + x2 - x1 - Math.Log(Ki(q2, q1, t, e1, DeltaEi(t, z2, z1, g))))},
                {1, 0, -1, 1, 0, 0, -(ve + x3 - x2 - Math.Log(Ki(q3, q2, t, e2, DeltaEi(t, z3, z2, g))))},
                {1, 0, 0, -1, 1, 0, -(ve + x4 - x3 - Math.Log(Ki(q4, q3, t, e3, DeltaEi(t, z4, z3, g))))},
                {1, 0, 0, 0, -1, 1, -(ve + x5 - x4 - Math.Log(Ki(q5, q4, t, e4, DeltaEi(t, z5, z4, g))))},
                {Math.Exp(ve), Math.Exp(x1), Math.Exp(x2), Math.Exp(x3), Math.Exp(x4), Math.Exp(x5), -(Math.Exp(ve) + Math.Exp(x1) + Math.Exp(x2) + Math.Exp(x3) + Math.Exp(x4) + Math.Exp(x5) - alpha - p*7.242*1000/t) },
                {Math.Exp(ve), 0, -z2 * Math.Exp(x2), -z3 * Math.Exp(x3), -z4 * Math.Exp(x4), -z5 * Math.Exp(x5), -(Math.Exp(ve) - (z2 * Math.Exp(x2) + z3 * Math.Exp(x3) + z4 * Math.Exp(x4) + z5 * Math.Exp(x5))) }
            };
            MatrixDouble m = new MatrixDouble(mdata);
            return m;
        }

        public static SolverResult Refinement(List<double> values, List<double> listQ, List<double> listE, List<double> listZ, double g, int p, int t)
        {
            // m = matrix(Values, Q, G, E, T, Z)
            MatrixDouble m = ToMatrix(values, listQ, g, listE, t, listZ, p);
            var dValues = Gauss(m);
            double nG = HalfDivision(t, values, listZ);

            while (
                Max(Math.Abs(dValues[0] / values[0]),
                    Math.Abs(dValues[1] / values[1]),
                    Math.Abs(dValues[2] / values[2]),
                    Math.Abs(dValues[3] / values[3]),
                    Math.Abs(dValues[4] / values[4]),
                    Math.Abs(dValues[5] / values[5]),
                    Math.Abs((g - nG) / nG))
                    > 1e-5)
            {
                values[0] += dValues[0];
                values[1] += dValues[1];
                values[2] += dValues[2];
                values[3] += dValues[3];
                values[4] += dValues[4];
                values[5] += dValues[5];

                g = nG;
                nG = HalfDivision(t, values, listZ);

                m = ToMatrix(values, listQ, g, listE, t, listZ, p);
                dValues = Gauss(m);
            }

            for (int i = 0; i < values.Count; i++)
            {
                values[i] = Math.Exp(values[i]);
            }
            return new SolverResult(values, nG);
        }
    }
}
