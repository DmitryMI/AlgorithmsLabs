#pragma once

#include <stdlib.h>
#include "table.h"

namespace Lab_03
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ Form1
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  drawingCanvas;
	private: System::Windows::Forms::DataGridView^  pointDataGrid;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^  indexCol;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  weightCol;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  xCol;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  yCol;
	private: System::Windows::Forms::Button^  drawButton;
	private: System::Windows::Forms::Button^  genButton;
	private: System::Windows::Forms::TextBox^  numBox;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  argstepBox;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  initargBox;
	private: System::Windows::Forms::TextBox^  degreeBox;
	private: System::Windows::Forms::Label^  label4;







	protected:

	protected:

	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->drawingCanvas = (gcnew System::Windows::Forms::PictureBox());
			this->pointDataGrid = (gcnew System::Windows::Forms::DataGridView());
			this->indexCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->weightCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->xCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->yCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->drawButton = (gcnew System::Windows::Forms::Button());
			this->genButton = (gcnew System::Windows::Forms::Button());
			this->numBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->argstepBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->initargBox = (gcnew System::Windows::Forms::TextBox());
			this->degreeBox = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->drawingCanvas))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pointDataGrid))->BeginInit();
			this->SuspendLayout();
			// 
			// drawingCanvas
			// 
			this->drawingCanvas->BackColor = System::Drawing::Color::White;
			this->drawingCanvas->Location = System::Drawing::Point(651, 18);
			this->drawingCanvas->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->drawingCanvas->Name = L"drawingCanvas";
			this->drawingCanvas->Size = System::Drawing::Size(706, 689);
			this->drawingCanvas->TabIndex = 0;
			this->drawingCanvas->TabStop = false;
			// 
			// pointDataGrid
			// 
			this->pointDataGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->pointDataGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4)
			{
				this->indexCol,
					this->weightCol, this->xCol, this->yCol
			});
			this->pointDataGrid->Location = System::Drawing::Point(18, 18);
			this->pointDataGrid->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pointDataGrid->Name = L"pointDataGrid";
			this->pointDataGrid->Size = System::Drawing::Size(624, 542);
			this->pointDataGrid->TabIndex = 1;
			// 
			// indexCol
			// 
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->indexCol->DefaultCellStyle = dataGridViewCellStyle1;
			this->indexCol->HeaderText = L"#";
			this->indexCol->Name = L"indexCol";
			this->indexCol->ReadOnly = true;
			this->indexCol->Width = 70;
			// 
			// weightCol
			// 
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->weightCol->DefaultCellStyle = dataGridViewCellStyle2;
			this->weightCol->HeaderText = L"Weight";
			this->weightCol->Name = L"weightCol";
			// 
			// xCol
			// 
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->xCol->DefaultCellStyle = dataGridViewCellStyle3;
			this->xCol->HeaderText = L"X";
			this->xCol->Name = L"xCol";
			// 
			// yCol
			// 
			dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->yCol->DefaultCellStyle = dataGridViewCellStyle4;
			this->yCol->HeaderText = L"Y";
			this->yCol->Name = L"yCol";
			// 
			// drawButton
			// 
			this->drawButton->Location = System::Drawing::Point(18, 598);
			this->drawButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->drawButton->Name = L"drawButton";
			this->drawButton->Size = System::Drawing::Size(140, 35);
			this->drawButton->TabIndex = 2;
			this->drawButton->Text = L"Draw curve";
			this->drawButton->UseVisualStyleBackColor = true;
			this->drawButton->Click += gcnew System::EventHandler(this, &MainForm::ButtonListener);
			// 
			// genButton
			// 
			this->genButton->Location = System::Drawing::Point(18, 671);
			this->genButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->genButton->Name = L"genButton";
			this->genButton->Size = System::Drawing::Size(140, 35);
			this->genButton->TabIndex = 3;
			this->genButton->Text = L"Generate points";
			this->genButton->UseVisualStyleBackColor = true;
			this->genButton->Click += gcnew System::EventHandler(this, &MainForm::ButtonListener);
			// 
			// numBox
			// 
			this->numBox->Location = System::Drawing::Point(166, 674);
			this->numBox->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->numBox->Name = L"numBox";
			this->numBox->Size = System::Drawing::Size(100, 26);
			this->numBox->TabIndex = 4;
			this->numBox->Text = L"10";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(165, 652);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(103, 20);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Point number";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(276, 652);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(69, 20);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Arg step";
			// 
			// argstepBox
			// 
			this->argstepBox->Location = System::Drawing::Point(278, 674);
			this->argstepBox->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->argstepBox->Name = L"argstepBox";
			this->argstepBox->Size = System::Drawing::Size(100, 26);
			this->argstepBox->TabIndex = 6;
			this->argstepBox->Text = L"1";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(387, 652);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(58, 20);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Init arg";
			// 
			// initargBox
			// 
			this->initargBox->Location = System::Drawing::Point(388, 674);
			this->initargBox->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->initargBox->Name = L"initargBox";
			this->initargBox->Size = System::Drawing::Size(100, 26);
			this->initargBox->TabIndex = 8;
			this->initargBox->Text = L"-5";
			// 
			// degreeBox
			// 
			this->degreeBox->Location = System::Drawing::Point(170, 602);
			this->degreeBox->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->degreeBox->Name = L"degreeBox";
			this->degreeBox->Size = System::Drawing::Size(97, 26);
			this->degreeBox->TabIndex = 10;
			this->degreeBox->Text = L"1";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(165, 577);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(62, 20);
			this->label4->TabIndex = 11;
			this->label4->Text = L"Degree";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1376, 726);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->degreeBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->initargBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->argstepBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->numBox);
			this->Controls->Add(this->genButton);
			this->Controls->Add(this->drawButton);
			this->Controls->Add(this->pointDataGrid);
			this->Controls->Add(this->drawingCanvas);
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"MainForm";
			this->Text = L"OLS";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->drawingCanvas))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pointDataGrid))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		// NOT GENERATED CODE
	private:
		void ButtonListener(Object^ sender, EventArgs^ e);
		void GeneratePoints();
		void DrawTable(float *, float *);
		void ConstructTable();
		void draw_graphics(float , float);

	private:
		float x_scale, y_scale;
		Table *table = NULL;
		Random^ rnd = gcnew Random();

#pragma endregion

};
}

