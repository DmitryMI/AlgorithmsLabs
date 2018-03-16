#include "stdafx.h"
#include "MainForm.h"
#include <stdlib.h>
#include <time.h>

#define RND_01 ((float)rand() / (float)RAND_MAX)
#define RND_RANGE(min, max) ((RND_01) * (max - min) + min)
#define POINT_SIZE 4
#define POINT_COLOR Color::Red
#define Y_INTERFERENCE 10.0f

namespace Lab_03
{	

	float genFunc(float x)
	{
		return x * x;
	}
	
	void MainForm::free_table(Table *t)
	{
		if (t == NULL)
			return;
		free(t->x);
		free(t->y);
		free(t->weight);
		free(t);
	}

	void MainForm::ConstructTable()
	{
		free_table(table);
		table = NULL;
		if (pointDataGrid->RowCount <= 0)
			return;
		table = (Table*)malloc(sizeof(Table));
		table->x = (float*)malloc(sizeof(float)* pointDataGrid->RowCount);
		table->y = (float*)malloc(sizeof(float)* pointDataGrid->RowCount);;
		table->weight = (float*)malloc(sizeof(float)* pointDataGrid->RowCount);
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
		float x_max = table->x[0];
		for (int i = 0; i < pointDataGrid->RowCount - 1; i++)
		{
			float x = table->x[i];
			if (x > x_max)
				x_max = x;
		}
		x_scale = drawingCanvas->Width / 2 / x_max;

		// Calculating y_scale
		float y_max = table->y[0];
		for (int i = 0; i < pointDataGrid->RowCount - 1; i++)
		{
			float y = table->y[i];
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
				float pnt = RND_RANGE(y - Y_INTERFERENCE, y + Y_INTERFERENCE);
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
		}
		else
		if (sendingButton == genButton)
		{
			GeneratePoints();
		}
	}
}