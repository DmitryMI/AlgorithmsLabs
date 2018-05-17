using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_5_CSharp
{
    class MatrixDouble
    {
        private double[][] _data;
        public MatrixDouble(int rows, int cols)
        {
            _data = new double[rows][];
            for (int i = 0; i < rows; i++)
            {
                _data[i] = new double[cols];
                for (int j = 0; j < cols; j++)
                    _data[i][j] = 0;
            }
        }

        public MatrixDouble(double[][] data)
        {
            _data = new double[data.Length][];
            for (int i = 0; i < data.Length; i++)
            {
                _data[i] = new double[data[0].Length];
                for (int j = 0; j < data[0].Length; j++)
                    _data[i][j] = data[i][j];
            }
        }

        public MatrixDouble(double[,]data)
        {
            int rows = data.GetLength(0);
            int cols = data.GetLength(1);
            _data = new double[rows][];
            for (int i = 0; i < rows; i++)
            {
                _data[i] = new double[cols];
                for (int j = 0; j < cols; j++)
                    _data[i][j] = data[i,j];
            }
        }

        public int Rows
        {
            get { return _data.Length; }
        }

        public int Cols
        {
            get { return _data[0].Length; }
        }

        public double this[int i, int j]
        {
            get { return _data[i][j]; }
            set { _data[i][j] = value; }
        }

        public double[] this[int i]
        {
            get { return _data[i]; }
            set { _data[i] = value; }
        }

    }
}
