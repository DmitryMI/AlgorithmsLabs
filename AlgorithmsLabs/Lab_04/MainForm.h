#pragma once

#include <stdlib.h>

namespace Lab_03
{

	typedef struct Table
	{
		float *x;
		float *y;
		float *weight;
	};	

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
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle9 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle10 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle11 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle12 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->drawingCanvas))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pointDataGrid))->BeginInit();
			this->SuspendLayout();
			// 
			// drawingCanvas
			// 
			this->drawingCanvas->BackColor = System::Drawing::Color::White;
			this->drawingCanvas->Location = System::Drawing::Point(434, 12);
			this->drawingCanvas->Name = L"drawingCanvas";
			this->drawingCanvas->Size = System::Drawing::Size(471, 448);
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
			this->pointDataGrid->Location = System::Drawing::Point(12, 12);
			this->pointDataGrid->Name = L"pointDataGrid";
			this->pointDataGrid->Size = System::Drawing::Size(416, 409);
			this->pointDataGrid->TabIndex = 1;
			// 
			// indexCol
			// 
			dataGridViewCellStyle9->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->indexCol->DefaultCellStyle = dataGridViewCellStyle9;
			this->indexCol->HeaderText = L"#";
			this->indexCol->Name = L"indexCol";
			this->indexCol->ReadOnly = true;
			this->indexCol->Width = 70;
			// 
			// weightCol
			// 
			dataGridViewCellStyle10->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->weightCol->DefaultCellStyle = dataGridViewCellStyle10;
			this->weightCol->HeaderText = L"Weight";
			this->weightCol->Name = L"weightCol";
			// 
			// xCol
			// 
			dataGridViewCellStyle11->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->xCol->DefaultCellStyle = dataGridViewCellStyle11;
			this->xCol->HeaderText = L"X";
			this->xCol->Name = L"xCol";
			// 
			// yCol
			// 
			dataGridViewCellStyle12->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->yCol->DefaultCellStyle = dataGridViewCellStyle12;
			this->yCol->HeaderText = L"Y";
			this->yCol->Name = L"yCol";
			// 
			// drawButton
			// 
			this->drawButton->Location = System::Drawing::Point(13, 436);
			this->drawButton->Name = L"drawButton";
			this->drawButton->Size = System::Drawing::Size(75, 23);
			this->drawButton->TabIndex = 2;
			this->drawButton->Text = L"Draw curve";
			this->drawButton->UseVisualStyleBackColor = true;
			this->drawButton->Click += gcnew System::EventHandler(this, &MainForm::ButtonListener);
			// 
			// genButton
			// 
			this->genButton->Location = System::Drawing::Point(94, 436);
			this->genButton->Name = L"genButton";
			this->genButton->Size = System::Drawing::Size(93, 23);
			this->genButton->TabIndex = 3;
			this->genButton->Text = L"Generate points";
			this->genButton->UseVisualStyleBackColor = true;
			this->genButton->Click += gcnew System::EventHandler(this, &MainForm::ButtonListener);
			// 
			// numBox
			// 
			this->numBox->Location = System::Drawing::Point(193, 438);
			this->numBox->Name = L"numBox";
			this->numBox->Size = System::Drawing::Size(68, 20);
			this->numBox->TabIndex = 4;
			this->numBox->Text = L"10";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(192, 424);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(69, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Point number";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(266, 424);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(46, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Arg step";
			// 
			// argstepBox
			// 
			this->argstepBox->Location = System::Drawing::Point(267, 438);
			this->argstepBox->Name = L"argstepBox";
			this->argstepBox->Size = System::Drawing::Size(68, 20);
			this->argstepBox->TabIndex = 6;
			this->argstepBox->Text = L"1";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(340, 424);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(39, 13);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Init arg";
			// 
			// initargBox
			// 
			this->initargBox->Location = System::Drawing::Point(341, 438);
			this->initargBox->Name = L"initargBox";
			this->initargBox->Size = System::Drawing::Size(68, 20);
			this->initargBox->TabIndex = 8;
			this->initargBox->Text = L"0";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(917, 472);
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
		void DrawTable();
		void ConstructTable();
		void free_table(Table *t);

	private:
		float x_scale, y_scale;
		Table *table;

#pragma endregion
	};
}

