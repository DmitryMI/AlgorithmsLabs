#include "stdafx.h"
#include "MainForm.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "OlsInterpolator.h"

#define POINT_SIZE 4
#define POINT_COLOR Color::Red
#define Y_INTERFERENCE 3.0

namespace Lab_03
{	

	double fi(double x, int k)
	{
		double res = 1;
		for (int i = 0; i < k; i++)
			res *= x;
		return res;
	}

	float genFunc(float x)
	{
		return x;
	}
	
	void MainForm::ConstructTable()
	{
		free_table(table);
		table = NULL;
		if (pointDataGrid->RowCount <= 0)
			return;
		table = (Table*)malloc(sizeof(Table));
		table->x = (float*)malloc(sizeof(float)* (pointDataGrid->RowCount - 1));
		table->y = (float*)malloc(sizeof(float)* (pointDataGrid->RowCount - 1));
		table->weight = (float*)malloc(sizeof(float)* (pointDataGrid->RowCount - 1));
		table->size = (pointDataGrid->RowCount - 1);
		try
		{
			for (int i = 0; i < pointDataGrid->RowCount - 1; i++)
			{
				float w = Double::Parse(pointDataGrid->Rows[i]->Cells[1]->Value->ToString());
				float x = Double::Parse(pointDataGrid->Rows[i]->Cells[2]->Value->ToString());
				float y = Double::Parse(pointDataGrid->Rows[i]->Cells[3]->Value->ToString());
				table->x[i] = x;
				table->y[i] = y;
				table->weight[i] = w;
			}
		}
		catch (FormatException^ ex)
		{
			MessageBox::Show("Incorrect format of table value");
		}
		
	}

	void MainForm::DrawTable()
	{
		// Calculating x_scale
		float x_max = fabs(table->x[0]);
		for (int i = 0; i < pointDataGrid->RowCount - 1; i++)
		{
			float x = fabs(table->x[i]);
			if (x > x_max)
				x_max = x;
		}
		x_scale = drawingCanvas->Width / 2 / x_max;

		// Calculating y_scale
		float y_max = fabs(table->y[0]);
		for (int i = 0; i < pointDataGrid->RowCount - 1; i++)
		{
			float y = fabs(table->y[i]);
			if (y > y_max)
				y_max = y;
		}
		y_scale = drawingCanvas->Height / 2 / y_max;

		Graphics^ gr = drawingCanvas->CreateGraphics();
		gr->TranslateTransform(drawingCanvas->Width / 2, drawingCanvas->Height / 2);

		Brush^ pointBrush = gcnew SolidBrush(POINT_COLOR);

		for (int i = 0; i < pointDataGrid->RowCount - 1; i++)
		{
			float x = (table->x[i] * x_scale);
			float y = (table->y[i] * y_scale);
			gr->FillEllipse(pointBrush, x - POINT_SIZE / 2, -y - POINT_SIZE / 2, (float)POINT_SIZE, (float)POINT_SIZE);
		}
	}

	void MainForm::draw_graphics()
	{

		int degree = Int32::Parse(degreeBox->Text);
		OlsInterpolator *ols = new OlsInterpolator(table, fi, degree);
		Graphics^ gr = drawingCanvas->CreateGraphics();
		gr->TranslateTransform(drawingCanvas->Width / 2, drawingCanvas->Height / 2);
		int x_prev = - drawingCanvas->Width / 2;
		int y_prev = ols->calculate(x_prev);

		Brush^ pointBrush = gcnew SolidBrush(Color::Black);
		Pen^ pen = gcnew Pen(pointBrush);

		
		for (int x = -drawingCanvas->Width / 2 + 10; x < drawingCanvas->Width / 2; x += 10)
		{
			int y = ols->calculate(x);
			gr->DrawLine(pen, x_prev, y_prev, x, y);
		}
	}

	void MainForm::GeneratePoints()
	{
		srand(time(NULL));
		int N;
		float arg_step;
		float init_arg;
		try
		{
			String^ text = numBox->Text;
			N = Int32::Parse(text);
			arg_step = Double::Parse(argstepBox->Text);
			init_arg = Double::Parse(initargBox->Text);
			pointDataGrid->Rows->Clear();
			for (int i = 0; i < N; i++)
			{
				float x = (init_arg + (i * arg_step));
				float y = genFunc(x);
				float pnt = y + rnd->NextDouble() * (2 * Y_INTERFERENCE) - Y_INTERFERENCE;
				array<String^>^row1 = gcnew array<String^>
				{
					i.ToString(), "1",  x.ToString(), pnt.ToString()
				};
				pointDataGrid->Rows->Add(row1);
			}
		}
		catch (FormatException^ ex)
		{
			MessageBox::Show("Incorrect format.");
		}
	}

	void MainForm::ButtonListener(Object^ sender, EventArgs^ e)
	{
		Button^ sendingButton = (Button^)sender;
		if (sendingButton == drawButton)
		{
			ConstructTable();
			DrawTable();
			draw_graphics();
		}
		else
		if (sendingButton == genButton)
		{
			GeneratePoints();
		}
	}
}