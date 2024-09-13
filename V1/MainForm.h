#pragma once
#include "Data.h"
#include "SplashScreen.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace DataNamespace;

namespace V1 {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Diagnostics;
	using namespace System::IO;
	using namespace System::Reflection;
	using namespace System::Windows::Forms;

	public ref class MainForm : public System::Windows::Forms::Form
	{

	public:
		MainForm(void) {

			// Neuen Thread definieren, welcher "StartForm" in einem separaten Thread ausführt
			Thread^ t = gcnew Thread(gcnew ThreadStart(this, &MainForm::StartForm));
			t->SetApartmentState(ApartmentState::STA);

			// Thread starten
			t->Start();

			// Warten bis Splashscreen beendet wird
			t->Join(); 

			// Programmfenster mittig zentriert öffnen
			this->StartPosition = FormStartPosition::CenterScreen;

			InitializeComponent();

			// Eingebettetes Programmicon laden
			System::Reflection::Assembly^ assembly = System::Reflection::Assembly::GetExecutingAssembly();
			System::IO::Stream^ iconStream = assembly->GetManifestResourceStream("Icon.ico");

			// Programmicon setzen
			this->Icon = gcnew System::Drawing::Icon(iconStream);

			// Hintergrund "Lightmode" laden und via Browser anzeigen
			Assembly^ assemblyHTML = Assembly::GetExecutingAssembly();
			Stream^ streamHTML = assemblyHTML->GetManifestResourceStream("lightmode.html");
			StreamReader^ reader = gcnew StreamReader(streamHTML);
			String^ htmlContent = reader->ReadToEnd();
			webBrowser1->DocumentText = htmlContent;

			// UI-ELemente beschriften bzw. in Englisch laden
			sprache_aendern();
			
			// Datentypen initialisieren
			InitializeDataTypes();

			// Dropdown mit den verschiedenen Quellentypen füllen
			PopulateTypeDropdown();

			// Alle Textfelder ausblenden
			HideAllFields();

			// UI-Elemente dem Status "Nicht im Edit-Mode" anpassen
			UpdateUIState(false);

		}

	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  btnDarkmode;
	private: System::Windows::Forms::ToolStripButton^  btnLanguage;
	private: System::Windows::Forms::ToolStripButton^  btnPDF;
	private: System::Windows::Forms::WebBrowser^  webBrowser1;
	private: System::Windows::Forms::Panel^  pnlNameEdit;


	private:
		array<String^, 2>^ nachrichten; //Zweidimensionales Array für sämmtliche Messageboxen

	protected:

		~MainForm() {
			if (components) {
				delete components;
			}
		}
	public:
		void StartForm() {
			//Splashscreen laden
			V1::SplashScreen^ form = gcnew V1::SplashScreen();
			form->ShowDialog();
		}

	private:
		List<int>^ displayedEntryIndices = gcnew List<int>(); // Um Indizes nach Suche zu speichern
	private:
		System::Windows::Forms::TextBox^ txtFirstName;
		System::Windows::Forms::TextBox^ txtLastName;
		System::Windows::Forms::Button^ btnExportToBib;
		System::Windows::Forms::Button^ btnSetAuthor;
		System::Windows::Forms::TextBox^ txtSearch;
	private: System::ComponentModel::IContainer^  components;

			 System::Windows::Forms::ListView^ listViewEntries;
			 System::Windows::Forms::Button^ btnNew;
			 System::Windows::Forms::Button^ btnEdit;
			 System::Windows::Forms::Button^ btnDelete;
			 System::Windows::Forms::Panel^ panelDetails;
			 System::Windows::Forms::ComboBox^ cmbType;
			 System::Windows::Forms::TextBox^ txtKeyword;
			 System::Windows::Forms::TextBox^ txtAuthor;
			 System::Windows::Forms::TextBox^ txtTitle;
			 System::Windows::Forms::TextBox^ txtYear;
			 System::Windows::Forms::TextBox^ txtJournal;
			 System::Windows::Forms::TextBox^ txtVolume;
			 System::Windows::Forms::TextBox^ txtNumber;
			 System::Windows::Forms::TextBox^ txtPages;
			 System::Windows::Forms::TextBox^ txtMonth;
			 System::Windows::Forms::TextBox^ txtNote;
			 System::Windows::Forms::TextBox^ txtPublisher;
			 System::Windows::Forms::TextBox^ txtSeries;
			 System::Windows::Forms::TextBox^ txtAddress;
			 System::Windows::Forms::TextBox^ txtEdition;
			 System::Windows::Forms::TextBox^ txtHowpublished;
			 System::Windows::Forms::TextBox^ txtBooktitle;
			 System::Windows::Forms::TextBox^ txtEditor;
			 System::Windows::Forms::TextBox^ txtChapter;
			 System::Windows::Forms::TextBox^ txtSchool;
			 System::Windows::Forms::TextBox^ txtInstitution;
			 System::Windows::Forms::TextBox^ txtOrganization;
			 System::Windows::Forms::Button^ btnSave;
			 System::Windows::Forms::Button^ btnCancel;
			 System::Windows::Forms::Label^ lblLastName;
			 System::Windows::Forms::Label^ lblFirstName;
			 System::Windows::Forms::Label^ lblKeyword;
			 System::Windows::Forms::Label^ lblAuthor;
			 System::Windows::Forms::Label^ lblTitle;
			 System::Windows::Forms::Label^ lblYear;
			 System::Windows::Forms::Label^ lblJournal;
			 System::Windows::Forms::Label^ lblVolume;
			 System::Windows::Forms::Label^ lblNumber;
			 System::Windows::Forms::Label^ lblPages;
			 System::Windows::Forms::Label^ lblMonth;
			 System::Windows::Forms::Label^ lblNote;
			 System::Windows::Forms::Label^ lblPublisher;
			 System::Windows::Forms::Label^ lblSeries;
			 System::Windows::Forms::Label^ lblAddress;
			 System::Windows::Forms::Label^ lblEdition;
			 System::Windows::Forms::Label^ lblHowpublished;
			 System::Windows::Forms::Label^ lblABooktitle;
			 System::Windows::Forms::Label^ lblEditor;
			 System::Windows::Forms::Label^ lblChapter;
			 System::Windows::Forms::Label^ lblSchool;
			 System::Windows::Forms::Label^ lblInstitution;
			 System::Windows::Forms::Label^ lblOrganization;


			 // Liste zum Speichern aller Einträge
			 List<DataArray^>^ entries = gcnew List<DataArray^>();

			 // Objekt zum Speichern des aktuell angezeigten Eintrags
			 DataArray^ currentEntry;

			 // Array für Quellentypen
			 array<DataTypeFields^>^ dataTypes;

	private: System::Windows::Forms::Button^  btnSaveHDD;
	private: System::Windows::Forms::Button^  btnClearAuthor;
	private: System::Windows::Forms::RadioButton^  rbtnAuthor;
	private: System::Windows::Forms::RadioButton^  rbtnEditor;

			 bool isEditMode;

	private: System::Windows::Forms::ListView^ listViewAuthors; // Listview zum Anzeigen der Autoren oder Editoren
			 //FunktionenDeklaration
			 void ClearEntryDetails();
			 void SetFieldsReadOnly(bool readOnly);
			 void PopulateTypeDropdown();
			 void DisplayEntryDetails(DataArray^ entry);
			 bool ValidateEntry();
			 bool ValidateOptional();
			 void UpdateUIState(bool inEditMode);
			 void RefreshListView();
			 void HideAllFields();
			 void SaveEntries(String^ filename);
			 bool MainForm::LoadEntries(String^ filename);
			 void PerformSearch(String^ searchTerm);
			 int ShowFieldsForType(DataTypeFields^ type);
			 void PositionFieldWithLabel(Label^ label, TextBox^ field, int% yOffset, int xOffset);
			 void DarkMode();
			 void sprache_aendern();
			 void OpenPDF();
			 void ExportToBib();
			 void UpdateAuthorString(int index, String^ updatedEntry, TextBox^ storageTextBox);
			 void SetAuthor();
			 void ValidateSave();
			 //FunktionenDeklaration
			 //mein

			 void InitializeDataTypes() {
				 dataTypes = GetDataTypes();
			 }

			 // Event für "Neuer Eintrag"
			 void btnNew_Click(System::Object^ sender, System::EventArgs^ e) {
				 //Textfelder leeren
				 ClearEntryDetails();
				 //Leeres Objekt für neuen Eintrag initialisieren
				 currentEntry = gcnew DataArray();
				 // Oberfläche in Edit-Mode schalten
				 UpdateUIState(true);
			 }

			 // Event für "Bearbeiten"
			 void btnEdit_Click(System::Object^ sender, System::EventArgs^ e) {
				 if (listViewEntries->SelectedIndices->Count > 0) {
					 // Autorenliste leeren
					 listViewAuthors->Items->Clear();
					 // Aktuell ausgewählten Eintrag anzeigen
					 int index = listViewEntries->SelectedIndices[0];
					 currentEntry = entries[index];
					 DisplayEntryDetails(currentEntry);
					 // Oberfläche in Edit-Mode schalten
					 UpdateUIState(true);
				 }
			 }

			 // Event für "Speichern"
			 void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
				 ValidateSave();
			 }


			 // Event für "Abbrechen"
			 void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
				 ClearEntryDetails();
				 // Edit-Mode deaktivieren
				 UpdateUIState(false);
			 }






			 void InitializeComponent(void)
			 {
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
				 this->txtFirstName = (gcnew System::Windows::Forms::TextBox());
				 this->txtLastName = (gcnew System::Windows::Forms::TextBox());
				 this->btnSetAuthor = (gcnew System::Windows::Forms::Button());
				 this->listViewEntries = (gcnew System::Windows::Forms::ListView());
				 this->btnExportToBib = (gcnew System::Windows::Forms::Button());
				 this->btnNew = (gcnew System::Windows::Forms::Button());
				 this->btnEdit = (gcnew System::Windows::Forms::Button());
				 this->btnDelete = (gcnew System::Windows::Forms::Button());
				 this->panelDetails = (gcnew System::Windows::Forms::Panel());
				 this->pnlNameEdit = (gcnew System::Windows::Forms::Panel());
				 this->lblFirstName = (gcnew System::Windows::Forms::Label());
				 this->lblLastName = (gcnew System::Windows::Forms::Label());
				 this->btnClearAuthor = (gcnew System::Windows::Forms::Button());
				 this->listViewAuthors = (gcnew System::Windows::Forms::ListView());
				 this->rbtnAuthor = (gcnew System::Windows::Forms::RadioButton());
				 this->rbtnEditor = (gcnew System::Windows::Forms::RadioButton());
				 this->cmbType = (gcnew System::Windows::Forms::ComboBox());
				 this->txtKeyword = (gcnew System::Windows::Forms::TextBox());
				 this->txtAuthor = (gcnew System::Windows::Forms::TextBox());
				 this->txtTitle = (gcnew System::Windows::Forms::TextBox());
				 this->txtYear = (gcnew System::Windows::Forms::TextBox());
				 this->txtJournal = (gcnew System::Windows::Forms::TextBox());
				 this->txtVolume = (gcnew System::Windows::Forms::TextBox());
				 this->txtNumber = (gcnew System::Windows::Forms::TextBox());
				 this->txtPages = (gcnew System::Windows::Forms::TextBox());
				 this->txtMonth = (gcnew System::Windows::Forms::TextBox());
				 this->txtNote = (gcnew System::Windows::Forms::TextBox());
				 this->txtPublisher = (gcnew System::Windows::Forms::TextBox());
				 this->txtSeries = (gcnew System::Windows::Forms::TextBox());
				 this->txtAddress = (gcnew System::Windows::Forms::TextBox());
				 this->txtEdition = (gcnew System::Windows::Forms::TextBox());
				 this->txtHowpublished = (gcnew System::Windows::Forms::TextBox());
				 this->txtBooktitle = (gcnew System::Windows::Forms::TextBox());
				 this->txtEditor = (gcnew System::Windows::Forms::TextBox());
				 this->txtChapter = (gcnew System::Windows::Forms::TextBox());
				 this->txtSchool = (gcnew System::Windows::Forms::TextBox());
				 this->txtInstitution = (gcnew System::Windows::Forms::TextBox());
				 this->txtOrganization = (gcnew System::Windows::Forms::TextBox());
				 this->lblKeyword = (gcnew System::Windows::Forms::Label());
				 this->lblAuthor = (gcnew System::Windows::Forms::Label());
				 this->lblTitle = (gcnew System::Windows::Forms::Label());
				 this->lblYear = (gcnew System::Windows::Forms::Label());
				 this->lblJournal = (gcnew System::Windows::Forms::Label());
				 this->lblVolume = (gcnew System::Windows::Forms::Label());
				 this->lblNumber = (gcnew System::Windows::Forms::Label());
				 this->lblPages = (gcnew System::Windows::Forms::Label());
				 this->lblMonth = (gcnew System::Windows::Forms::Label());
				 this->lblNote = (gcnew System::Windows::Forms::Label());
				 this->lblPublisher = (gcnew System::Windows::Forms::Label());
				 this->lblSeries = (gcnew System::Windows::Forms::Label());
				 this->lblAddress = (gcnew System::Windows::Forms::Label());
				 this->lblEdition = (gcnew System::Windows::Forms::Label());
				 this->lblHowpublished = (gcnew System::Windows::Forms::Label());
				 this->lblABooktitle = (gcnew System::Windows::Forms::Label());
				 this->lblEditor = (gcnew System::Windows::Forms::Label());
				 this->lblChapter = (gcnew System::Windows::Forms::Label());
				 this->lblSchool = (gcnew System::Windows::Forms::Label());
				 this->lblInstitution = (gcnew System::Windows::Forms::Label());
				 this->lblOrganization = (gcnew System::Windows::Forms::Label());
				 this->btnSave = (gcnew System::Windows::Forms::Button());
				 this->btnCancel = (gcnew System::Windows::Forms::Button());
				 this->btnSaveHDD = (gcnew System::Windows::Forms::Button());
				 this->txtSearch = (gcnew System::Windows::Forms::TextBox());
				 this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
				 this->btnDarkmode = (gcnew System::Windows::Forms::ToolStripButton());
				 this->btnLanguage = (gcnew System::Windows::Forms::ToolStripButton());
				 this->btnPDF = (gcnew System::Windows::Forms::ToolStripButton());
				 this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
				 this->panelDetails->SuspendLayout();
				 this->pnlNameEdit->SuspendLayout();
				 this->toolStrip1->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // txtFirstName
				 // 
				 this->txtFirstName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->txtFirstName->Location = System::Drawing::Point(331, 66);
				 this->txtFirstName->Name = L"txtFirstName";
				 this->txtFirstName->Size = System::Drawing::Size(123, 21);
				 this->txtFirstName->TabIndex = 30;
				 // 
				 // txtLastName
				 // 
				 this->txtLastName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->txtLastName->Location = System::Drawing::Point(470, 66);
				 this->txtLastName->Name = L"txtLastName";
				 this->txtLastName->Size = System::Drawing::Size(123, 21);
				 this->txtLastName->TabIndex = 31;
				 // 
				 // btnSetAuthor
				 // 
				 this->btnSetAuthor->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->btnSetAuthor->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnSetAuthor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->btnSetAuthor->Location = System::Drawing::Point(618, 21);
				 this->btnSetAuthor->Name = L"btnSetAuthor";
				 this->btnSetAuthor->Size = System::Drawing::Size(92, 37);
				 this->btnSetAuthor->TabIndex = 42;
				 this->btnSetAuthor->Click += gcnew System::EventHandler(this, &MainForm::btnSetAuthor_Click);
				 // 
				 // listViewEntries
				 // 
				 this->listViewEntries->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->listViewEntries->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.75F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->listViewEntries->HideSelection = false;
				 this->listViewEntries->Location = System::Drawing::Point(12, 84);
				 this->listViewEntries->Name = L"listViewEntries";
				 this->listViewEntries->Size = System::Drawing::Size(300, 628);
				 this->listViewEntries->TabIndex = 10;
				 this->listViewEntries->TabStop = false;
				 this->listViewEntries->UseCompatibleStateImageBehavior = false;
				 this->listViewEntries->View = System::Windows::Forms::View::List;
				 this->listViewEntries->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::listViewEntries_SelectedIndexChanged);
				 // 
				 // btnExportToBib
				 // 
				 this->btnExportToBib->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(22)), static_cast<System::Int32>(static_cast<System::Byte>(167)),
					 static_cast<System::Int32>(static_cast<System::Byte>(22)));
				 this->btnExportToBib->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->btnExportToBib->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnExportToBib->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->btnExportToBib->ForeColor = System::Drawing::Color::White;
				 this->btnExportToBib->Location = System::Drawing::Point(72, 763);
				 this->btnExportToBib->Name = L"btnExportToBib";
				 this->btnExportToBib->Size = System::Drawing::Size(160, 30);
				 this->btnExportToBib->TabIndex = 8;
				 this->btnExportToBib->UseVisualStyleBackColor = false;
				 this->btnExportToBib->Click += gcnew System::EventHandler(this, &MainForm::btnExportToBib_Click);
				 // 
				 // btnNew
				 // 
				 this->btnNew->BackColor = System::Drawing::SystemColors::MenuHighlight;
				 this->btnNew->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->btnNew->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnNew->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->btnNew->ForeColor = System::Drawing::Color::White;
				 this->btnNew->Location = System::Drawing::Point(536, 43);
				 this->btnNew->Name = L"btnNew";
				 this->btnNew->Size = System::Drawing::Size(100, 28);
				 this->btnNew->TabIndex = 2;
				 this->btnNew->UseVisualStyleBackColor = false;
				 this->btnNew->Click += gcnew System::EventHandler(this, &MainForm::btnNew_Click);
				 // 
				 // btnEdit
				 // 
				 this->btnEdit->BackColor = System::Drawing::SystemColors::MenuHighlight;
				 this->btnEdit->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->btnEdit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnEdit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->btnEdit->ForeColor = System::Drawing::Color::White;
				 this->btnEdit->Location = System::Drawing::Point(642, 43);
				 this->btnEdit->Name = L"btnEdit";
				 this->btnEdit->Size = System::Drawing::Size(100, 28);
				 this->btnEdit->TabIndex = 3;
				 this->btnEdit->UseVisualStyleBackColor = false;
				 this->btnEdit->Click += gcnew System::EventHandler(this, &MainForm::btnEdit_Click);
				 // 
				 // btnDelete
				 // 
				 this->btnDelete->BackColor = System::Drawing::SystemColors::MenuHighlight;
				 this->btnDelete->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->btnDelete->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnDelete->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->btnDelete->ForeColor = System::Drawing::Color::White;
				 this->btnDelete->Location = System::Drawing::Point(748, 43);
				 this->btnDelete->Name = L"btnDelete";
				 this->btnDelete->Size = System::Drawing::Size(100, 28);
				 this->btnDelete->TabIndex = 4;
				 this->btnDelete->UseVisualStyleBackColor = false;
				 this->btnDelete->Click += gcnew System::EventHandler(this, &MainForm::btnDelete_Click);
				 // 
				 // panelDetails
				 // 
				 this->panelDetails->BackColor = System::Drawing::Color::White;
				 this->panelDetails->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->panelDetails->Controls->Add(this->pnlNameEdit);
				 this->panelDetails->Controls->Add(this->cmbType);
				 this->panelDetails->Controls->Add(this->txtKeyword);
				 this->panelDetails->Controls->Add(this->txtAuthor);
				 this->panelDetails->Controls->Add(this->txtTitle);
				 this->panelDetails->Controls->Add(this->txtYear);
				 this->panelDetails->Controls->Add(this->txtJournal);
				 this->panelDetails->Controls->Add(this->txtVolume);
				 this->panelDetails->Controls->Add(this->txtNumber);
				 this->panelDetails->Controls->Add(this->txtPages);
				 this->panelDetails->Controls->Add(this->txtMonth);
				 this->panelDetails->Controls->Add(this->txtNote);
				 this->panelDetails->Controls->Add(this->txtPublisher);
				 this->panelDetails->Controls->Add(this->txtSeries);
				 this->panelDetails->Controls->Add(this->txtAddress);
				 this->panelDetails->Controls->Add(this->txtEdition);
				 this->panelDetails->Controls->Add(this->txtHowpublished);
				 this->panelDetails->Controls->Add(this->txtBooktitle);
				 this->panelDetails->Controls->Add(this->txtEditor);
				 this->panelDetails->Controls->Add(this->txtChapter);
				 this->panelDetails->Controls->Add(this->txtSchool);
				 this->panelDetails->Controls->Add(this->txtInstitution);
				 this->panelDetails->Controls->Add(this->txtOrganization);
				 this->panelDetails->Controls->Add(this->lblKeyword);
				 this->panelDetails->Controls->Add(this->lblAuthor);
				 this->panelDetails->Controls->Add(this->lblTitle);
				 this->panelDetails->Controls->Add(this->lblYear);
				 this->panelDetails->Controls->Add(this->lblJournal);
				 this->panelDetails->Controls->Add(this->lblVolume);
				 this->panelDetails->Controls->Add(this->lblNumber);
				 this->panelDetails->Controls->Add(this->lblPages);
				 this->panelDetails->Controls->Add(this->lblMonth);
				 this->panelDetails->Controls->Add(this->lblNote);
				 this->panelDetails->Controls->Add(this->lblPublisher);
				 this->panelDetails->Controls->Add(this->lblSeries);
				 this->panelDetails->Controls->Add(this->lblAddress);
				 this->panelDetails->Controls->Add(this->lblEdition);
				 this->panelDetails->Controls->Add(this->lblHowpublished);
				 this->panelDetails->Controls->Add(this->lblABooktitle);
				 this->panelDetails->Controls->Add(this->lblEditor);
				 this->panelDetails->Controls->Add(this->lblChapter);
				 this->panelDetails->Controls->Add(this->lblSchool);
				 this->panelDetails->Controls->Add(this->lblInstitution);
				 this->panelDetails->Controls->Add(this->lblOrganization);
				 this->panelDetails->Location = System::Drawing::Point(320, 84);
				 this->panelDetails->Name = L"panelDetails";
				 this->panelDetails->Size = System::Drawing::Size(736, 628);
				 this->panelDetails->TabIndex = 13;
				 // 
				 // pnlNameEdit
				 // 
				 this->pnlNameEdit->Controls->Add(this->lblFirstName);
				 this->pnlNameEdit->Controls->Add(this->txtLastName);
				 this->pnlNameEdit->Controls->Add(this->txtFirstName);
				 this->pnlNameEdit->Controls->Add(this->lblLastName);
				 this->pnlNameEdit->Controls->Add(this->btnClearAuthor);
				 this->pnlNameEdit->Controls->Add(this->listViewAuthors);
				 this->pnlNameEdit->Controls->Add(this->rbtnAuthor);
				 this->pnlNameEdit->Controls->Add(this->rbtnEditor);
				 this->pnlNameEdit->Controls->Add(this->btnSetAuthor);
				 this->pnlNameEdit->Location = System::Drawing::Point(3, 502);
				 this->pnlNameEdit->Name = L"pnlNameEdit";
				 this->pnlNameEdit->Size = System::Drawing::Size(728, 119);
				 this->pnlNameEdit->TabIndex = 78;
				 // 
				 // lblFirstName
				 // 
				 this->lblFirstName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->lblFirstName->Location = System::Drawing::Point(331, 40);
				 this->lblFirstName->Name = L"lblFirstName";
				 this->lblFirstName->Size = System::Drawing::Size(100, 23);
				 this->lblFirstName->TabIndex = 79;
				 // 
				 // lblLastName
				 // 
				 this->lblLastName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->lblLastName->Location = System::Drawing::Point(470, 40);
				 this->lblLastName->Name = L"lblLastName";
				 this->lblLastName->Size = System::Drawing::Size(100, 23);
				 this->lblLastName->TabIndex = 78;
				 // 
				 // btnClearAuthor
				 // 
				 this->btnClearAuthor->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->btnClearAuthor->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnClearAuthor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->btnClearAuthor->Location = System::Drawing::Point(618, 64);
				 this->btnClearAuthor->Name = L"btnClearAuthor";
				 this->btnClearAuthor->Size = System::Drawing::Size(92, 37);
				 this->btnClearAuthor->TabIndex = 36;
				 this->btnClearAuthor->Click += gcnew System::EventHandler(this, &MainForm::btnClearAuthor_Click);
				 // 
				 // listViewAuthors
				 // 
				 this->listViewAuthors->FullRowSelect = true;
				 this->listViewAuthors->HideSelection = false;
				 this->listViewAuthors->LabelWrap = false;
				 this->listViewAuthors->Location = System::Drawing::Point(10, 10);
				 this->listViewAuthors->MultiSelect = false;
				 this->listViewAuthors->Name = L"listViewAuthors";
				 this->listViewAuthors->Size = System::Drawing::Size(200, 100);
				 this->listViewAuthors->TabIndex = 0;
				 this->listViewAuthors->TabStop = false;
				 this->listViewAuthors->UseCompatibleStateImageBehavior = false;
				 this->listViewAuthors->View = System::Windows::Forms::View::List;
				 this->listViewAuthors->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::listViewAuthors_SelectedIndexChanged);
				 // 
				 // rbtnAuthor
				 // 
				 this->rbtnAuthor->AutoSize = true;
				 this->rbtnAuthor->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->rbtnAuthor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->rbtnAuthor->Location = System::Drawing::Point(227, 41);
				 this->rbtnAuthor->Name = L"rbtnAuthor";
				 this->rbtnAuthor->Size = System::Drawing::Size(14, 13);
				 this->rbtnAuthor->TabIndex = 33;
				 this->rbtnAuthor->UseVisualStyleBackColor = true;
				 this->rbtnAuthor->CheckedChanged += gcnew System::EventHandler(this, &MainForm::rbtnAuthor_CheckedChanged);
				 // 
				 // rbtnEditor
				 // 
				 this->rbtnEditor->AutoSize = true;
				 this->rbtnEditor->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->rbtnEditor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->rbtnEditor->Location = System::Drawing::Point(227, 64);
				 this->rbtnEditor->Name = L"rbtnEditor";
				 this->rbtnEditor->Size = System::Drawing::Size(14, 13);
				 this->rbtnEditor->TabIndex = 32;
				 this->rbtnEditor->UseVisualStyleBackColor = true;
				 this->rbtnEditor->CheckedChanged += gcnew System::EventHandler(this, &MainForm::rbtnEditor_CheckedChanged);
				 // 
				 // cmbType
				 // 
				 this->cmbType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				 this->cmbType->Location = System::Drawing::Point(268, 30);
				 this->cmbType->Name = L"cmbType";
				 this->cmbType->Size = System::Drawing::Size(200, 26);
				 this->cmbType->TabIndex = 5;
				 this->cmbType->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::cmbType_SelectedIndexChanged);


				 int txtBoxSize = 250;

				 // 
				 // txtKeyword
				 // 
				 this->txtKeyword->Location = System::Drawing::Point(0, 0);
				 this->txtKeyword->Name = L"txtKeyword";
				 this->txtKeyword->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtKeyword->TabIndex = 34;
				 this->txtKeyword->TabStop = false;
				 // 
				 // txtAuthor
				 // 
				 this->txtAuthor->Location = System::Drawing::Point(0, 0);
				 this->txtAuthor->Name = L"txtAuthor";
				 this->txtAuthor->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtAuthor->TabIndex = 35;
				 // 
				 // txtTitle
				 // 
				 this->txtTitle->Location = System::Drawing::Point(0, 0);
				 this->txtTitle->Name = L"txtTitle";
				 this->txtTitle->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtTitle->TabIndex = 37;
				 // 
				 // txtYear
				 // 
				 this->txtYear->Location = System::Drawing::Point(0, 0);
				 this->txtYear->Name = L"txtYear";
				 this->txtYear->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtYear->TabIndex = 38;
				 // 
				 // txtJournal
				 // 
				 this->txtJournal->Location = System::Drawing::Point(0, 0);
				 this->txtJournal->Name = L"txtJournal";
				 this->txtJournal->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtJournal->TabIndex = 39;
				 // 
				 // txtVolume
				 // 
				 this->txtVolume->Location = System::Drawing::Point(0, 0);
				 this->txtVolume->Name = L"txtVolume";
				 this->txtVolume->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtVolume->TabIndex = 40;
				 // 
				 // txtNumber
				 // 
				 this->txtNumber->Location = System::Drawing::Point(0, 0);
				 this->txtNumber->Name = L"txtNumber";
				 this->txtNumber->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtNumber->TabIndex = 41;
				 // 
				 // txtPages
				 // 
				 this->txtPages->Location = System::Drawing::Point(0, 0);
				 this->txtPages->Name = L"txtPages";
				 this->txtPages->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtPages->TabIndex = 43;
				 // 
				 // txtMonth
				 // 
				 this->txtMonth->Location = System::Drawing::Point(0, 0);
				 this->txtMonth->Name = L"txtMonth";
				 this->txtMonth->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtMonth->TabIndex = 44;
				 // 
				 // txtNote
				 // 
				 this->txtNote->Location = System::Drawing::Point(0, 0);
				 this->txtNote->Name = L"txtNote";
				 this->txtNote->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtNote->TabIndex = 45;
				 // 
				 // txtPublisher
				 // 
				 this->txtPublisher->Location = System::Drawing::Point(0, 0);
				 this->txtPublisher->Name = L"txtPublisher";
				 this->txtPublisher->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtPublisher->TabIndex = 46;
				 // 
				 // txtSeries
				 // 
				 this->txtSeries->Location = System::Drawing::Point(0, 0);
				 this->txtSeries->Name = L"txtSeries";
				 this->txtSeries->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtSeries->TabIndex = 47;
				 // 
				 // txtAddress
				 // 
				 this->txtAddress->Location = System::Drawing::Point(0, 0);
				 this->txtAddress->Name = L"txtAddress";
				 this->txtAddress->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtAddress->TabIndex = 48;
				 // 
				 // txtEdition
				 // 
				 this->txtEdition->Location = System::Drawing::Point(0, 0);
				 this->txtEdition->Name = L"txtEdition";
				 this->txtEdition->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtEdition->TabIndex = 49;
				 // 
				 // txtHowpublished
				 // 
				 this->txtHowpublished->Location = System::Drawing::Point(0, 0);
				 this->txtHowpublished->Name = L"txtHowpublished";
				 this->txtHowpublished->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtHowpublished->TabIndex = 50;
				 // 
				 // txtBooktitle
				 // 
				 this->txtBooktitle->Location = System::Drawing::Point(0, 0);
				 this->txtBooktitle->Name = L"txtBooktitle";
				 this->txtBooktitle->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtBooktitle->TabIndex = 51;
				 // 
				 // txtEditor
				 // 
				 this->txtEditor->Location = System::Drawing::Point(0, 0);
				 this->txtEditor->Name = L"txtEditor";
				 this->txtEditor->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtEditor->TabIndex = 52;
				 // 
				 // txtChapter
				 // 
				 this->txtChapter->Location = System::Drawing::Point(0, 0);
				 this->txtChapter->Name = L"txtChapter";
				 this->txtChapter->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtChapter->TabIndex = 53;
				 // 
				 // txtSchool
				 // 
				 this->txtSchool->Location = System::Drawing::Point(0, 0);
				 this->txtSchool->Name = L"txtSchool";
				 this->txtSchool->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtSchool->TabIndex = 54;
				 // 
				 // txtInstitution
				 // 
				 this->txtInstitution->Location = System::Drawing::Point(0, 0);
				 this->txtInstitution->Name = L"txtInstitution";
				 this->txtInstitution->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtInstitution->TabIndex = 55;
				 // 
				 // txtOrganization
				 // 
				 this->txtOrganization->Location = System::Drawing::Point(0, 0);
				 this->txtOrganization->Name = L"txtOrganization";
				 this->txtOrganization->Size = System::Drawing::Size(txtBoxSize, 24);
				 this->txtOrganization->TabIndex = 56;
				 // 
				 // lblKeyword
				 // 
				 this->lblKeyword->AutoSize = true;
				 this->lblKeyword->Location = System::Drawing::Point(10, 10);
				 this->lblKeyword->Name = L"lblKeyword";
				 this->lblKeyword->Size = System::Drawing::Size(0, 18);
				 this->lblKeyword->TabIndex = 57;
				 // 
				 // lblAuthor
				 // 
				 this->lblAuthor->AutoSize = true;
				 this->lblAuthor->Location = System::Drawing::Point(10, 40);
				 this->lblAuthor->Name = L"lblAuthor";
				 this->lblAuthor->Size = System::Drawing::Size(0, 18);
				 this->lblAuthor->TabIndex = 58;
				 // 
				 // lblTitle
				 // 
				 this->lblTitle->AutoSize = true;
				 this->lblTitle->Location = System::Drawing::Point(10, 70);
				 this->lblTitle->Name = L"lblTitle";
				 this->lblTitle->Size = System::Drawing::Size(0, 18);
				 this->lblTitle->TabIndex = 59;
				 // 
				 // lblYear
				 // 
				 this->lblYear->AutoSize = true;
				 this->lblYear->Location = System::Drawing::Point(10, 100);
				 this->lblYear->Name = L"lblYear";
				 this->lblYear->Size = System::Drawing::Size(0, 18);
				 this->lblYear->TabIndex = 60;
				 // 
				 // lblJournal
				 // 
				 this->lblJournal->AutoSize = true;
				 this->lblJournal->Location = System::Drawing::Point(10, 130);
				 this->lblJournal->Name = L"lblJournal";
				 this->lblJournal->Size = System::Drawing::Size(0, 18);
				 this->lblJournal->TabIndex = 61;
				 // 
				 // lblVolume
				 // 
				 this->lblVolume->AutoSize = true;
				 this->lblVolume->Location = System::Drawing::Point(10, 160);
				 this->lblVolume->Name = L"lblVolume";
				 this->lblVolume->Size = System::Drawing::Size(0, 18);
				 this->lblVolume->TabIndex = 62;
				 // 
				 // lblNumber
				 // 
				 this->lblNumber->AutoSize = true;
				 this->lblNumber->Location = System::Drawing::Point(10, 190);
				 this->lblNumber->Name = L"lblNumber";
				 this->lblNumber->Size = System::Drawing::Size(0, 18);
				 this->lblNumber->TabIndex = 63;
				 // 
				 // lblPages
				 // 
				 this->lblPages->AutoSize = true;
				 this->lblPages->Location = System::Drawing::Point(10, 220);
				 this->lblPages->Name = L"lblPages";
				 this->lblPages->Size = System::Drawing::Size(0, 18);
				 this->lblPages->TabIndex = 64;
				 // 
				 // lblMonth
				 // 
				 this->lblMonth->AutoSize = true;
				 this->lblMonth->Location = System::Drawing::Point(10, 250);
				 this->lblMonth->Name = L"lblMonth";
				 this->lblMonth->Size = System::Drawing::Size(0, 18);
				 this->lblMonth->TabIndex = 65;
				 // 
				 // lblNote
				 // 
				 this->lblNote->AutoSize = true;
				 this->lblNote->Location = System::Drawing::Point(10, 280);
				 this->lblNote->Name = L"lblNote";
				 this->lblNote->Size = System::Drawing::Size(0, 18);
				 this->lblNote->TabIndex = 66;
				 // 
				 // lblPublisher
				 // 
				 this->lblPublisher->AutoSize = true;
				 this->lblPublisher->Location = System::Drawing::Point(10, 310);
				 this->lblPublisher->Name = L"lblPublisher";
				 this->lblPublisher->Size = System::Drawing::Size(0, 18);
				 this->lblPublisher->TabIndex = 67;
				 // 
				 // lblSeries
				 // 
				 this->lblSeries->AutoSize = true;
				 this->lblSeries->Location = System::Drawing::Point(10, 340);
				 this->lblSeries->Name = L"lblSeries";
				 this->lblSeries->Size = System::Drawing::Size(0, 18);
				 this->lblSeries->TabIndex = 68;
				 // 
				 // lblAddress
				 // 
				 this->lblAddress->AutoSize = true;
				 this->lblAddress->Location = System::Drawing::Point(10, 370);
				 this->lblAddress->Name = L"lblAddress";
				 this->lblAddress->Size = System::Drawing::Size(0, 18);
				 this->lblAddress->TabIndex = 69;
				 // 
				 // lblEdition
				 // 
				 this->lblEdition->AutoSize = true;
				 this->lblEdition->Location = System::Drawing::Point(10, 400);
				 this->lblEdition->Name = L"lblEdition";
				 this->lblEdition->Size = System::Drawing::Size(0, 18);
				 this->lblEdition->TabIndex = 70;
				 // 
				 // lblHowpublished
				 // 
				 this->lblHowpublished->AutoSize = true;
				 this->lblHowpublished->Location = System::Drawing::Point(10, 430);
				 this->lblHowpublished->Name = L"lblHowpublished";
				 this->lblHowpublished->Size = System::Drawing::Size(0, 18);
				 this->lblHowpublished->TabIndex = 71;
				 // 
				 // lblABooktitle
				 // 
				 this->lblABooktitle->AutoSize = true;
				 this->lblABooktitle->Location = System::Drawing::Point(10, 460);
				 this->lblABooktitle->Name = L"lblABooktitle";
				 this->lblABooktitle->Size = System::Drawing::Size(0, 18);
				 this->lblABooktitle->TabIndex = 72;
				 // 
				 // lblEditor
				 // 
				 this->lblEditor->AutoSize = true;
				 this->lblEditor->Location = System::Drawing::Point(10, 490);
				 this->lblEditor->Name = L"lblEditor";
				 this->lblEditor->Size = System::Drawing::Size(0, 18);
				 this->lblEditor->TabIndex = 73;
				 // 
				 // lblChapter
				 // 
				 this->lblChapter->AutoSize = true;
				 this->lblChapter->Location = System::Drawing::Point(10, 520);
				 this->lblChapter->Name = L"lblChapter";
				 this->lblChapter->Size = System::Drawing::Size(0, 18);
				 this->lblChapter->TabIndex = 74;
				 // 
				 // lblSchool
				 // 
				 this->lblSchool->AutoSize = true;
				 this->lblSchool->Location = System::Drawing::Point(10, 550);
				 this->lblSchool->Name = L"lblSchool";
				 this->lblSchool->Size = System::Drawing::Size(0, 18);
				 this->lblSchool->TabIndex = 75;
				 // 
				 // lblInstitution
				 // 
				 this->lblInstitution->AutoSize = true;
				 this->lblInstitution->Location = System::Drawing::Point(10, 580);
				 this->lblInstitution->Name = L"lblInstitution";
				 this->lblInstitution->Size = System::Drawing::Size(0, 18);
				 this->lblInstitution->TabIndex = 76;
				 // 
				 // lblOrganization
				 // 
				 this->lblOrganization->AutoSize = true;
				 this->lblOrganization->Location = System::Drawing::Point(10, 610);
				 this->lblOrganization->Name = L"lblOrganization";
				 this->lblOrganization->Size = System::Drawing::Size(0, 18);
				 this->lblOrganization->TabIndex = 77;
				 // 
				 // btnSave
				 // 
				 this->btnSave->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->btnSave->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnSave->Location = System::Drawing::Point(542, 727);
				 this->btnSave->Name = L"btnSave";
				 this->btnSave->Size = System::Drawing::Size(132, 28);
				 this->btnSave->TabIndex = 11;
				 this->btnSave->Click += gcnew System::EventHandler(this, &MainForm::btnSave_Click);
				 // 
				 // btnCancel
				 // 
				 this->btnCancel->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnCancel->Location = System::Drawing::Point(679, 727);
				 this->btnCancel->Name = L"btnCancel";
				 this->btnCancel->Size = System::Drawing::Size(136, 28);
				 this->btnCancel->TabIndex = 12;
				 this->btnCancel->Click += gcnew System::EventHandler(this, &MainForm::btnCancel_Click);
				 // 
				 // btnSaveHDD
				 // 
				 this->btnSaveHDD->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(22)), static_cast<System::Int32>(static_cast<System::Byte>(167)),
					 static_cast<System::Int32>(static_cast<System::Byte>(22)));
				 this->btnSaveHDD->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->btnSaveHDD->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnSaveHDD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->btnSaveHDD->ForeColor = System::Drawing::Color::White;
				 this->btnSaveHDD->Location = System::Drawing::Point(72, 727);
				 this->btnSaveHDD->Name = L"btnSaveHDD";
				 this->btnSaveHDD->Size = System::Drawing::Size(160, 30);
				 this->btnSaveHDD->TabIndex = 9;
				 this->btnSaveHDD->UseVisualStyleBackColor = false;
				 this->btnSaveHDD->Click += gcnew System::EventHandler(this, &MainForm::btnSaveHDD_Click);
				 // 
				 // txtSearch
				 // 
				 this->txtSearch->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->txtSearch->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->txtSearch->Location = System::Drawing::Point(12, 43);
				 this->txtSearch->Name = L"txtSearch";
				 this->txtSearch->RightToLeft = System::Windows::Forms::RightToLeft::No;
				 this->txtSearch->Size = System::Drawing::Size(300, 27);
				 this->txtSearch->TabIndex = 1;
				 this->txtSearch->TextChanged += gcnew System::EventHandler(this, &MainForm::txtSearch_TextChanged);
				 // 
				 // toolStrip1
				 // 
				 this->toolStrip1->BackColor = System::Drawing::Color::White;
				 this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					 this->btnDarkmode, this->btnLanguage,
						 this->btnPDF
				 });
				 this->toolStrip1->Location = System::Drawing::Point(0, 0);
				 this->toolStrip1->Name = L"toolStrip1";
				 this->toolStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
				 this->toolStrip1->Size = System::Drawing::Size(1068, 25);
				 this->toolStrip1->TabIndex = 81;
				 this->toolStrip1->Text = L"toolStrip1";
				 // 
				 // btnDarkmode
				 // 
				 this->btnDarkmode->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				 this->btnDarkmode->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnDarkmode.Image")));
				 this->btnDarkmode->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->btnDarkmode->Name = L"btnDarkmode";
				 this->btnDarkmode->Size = System::Drawing::Size(66, 22);
				 this->btnDarkmode->Text = L"Darkmode";
				 this->btnDarkmode->ToolTipText = L"Darkmode";
				 this->btnDarkmode->Click += gcnew System::EventHandler(this, &MainForm::btnDarkmode_Click);
				 // 
				 // btnLanguage
				 // 
				 this->btnLanguage->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				 this->btnLanguage->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnLanguage.Image")));
				 this->btnLanguage->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->btnLanguage->Name = L"btnLanguage";
				 this->btnLanguage->Size = System::Drawing::Size(63, 22);
				 this->btnLanguage->Text = L"Language";
				 this->btnLanguage->Click += gcnew System::EventHandler(this, &MainForm::btnLanguage_Click);
				 // 
				 // btnPDF
				 // 
				 this->btnPDF->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				 this->btnPDF->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnPDF.Image")));
				 this->btnPDF->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->btnPDF->Name = L"btnPDF";
				 this->btnPDF->Size = System::Drawing::Size(51, 22);
				 this->btnPDF->Text = L"Manual";
				 this->btnPDF->Click += gcnew System::EventHandler(this, &MainForm::btnPDF_Click);
				 // 
				 // webBrowser1
				 // 
				 this->webBrowser1->Location = System::Drawing::Point(0, 0);
				 this->webBrowser1->MinimumSize = System::Drawing::Size(20, 20);
				 this->webBrowser1->Name = L"webBrowser1";
				 this->webBrowser1->ScrollBarsEnabled = false;
				 this->webBrowser1->Size = System::Drawing::Size(1073, 810);
				 this->webBrowser1->TabIndex = 82;
				 // 
				 // MainForm
				 // 
				 this->ClientSize = System::Drawing::Size(1068, 805);
				 this->Controls->Add(this->toolStrip1);
				 this->Controls->Add(this->btnExportToBib);
				 this->Controls->Add(this->btnSaveHDD);
				 this->Controls->Add(this->txtSearch);
				 this->Controls->Add(this->listViewEntries);
				 this->Controls->Add(this->btnNew);
				 this->Controls->Add(this->btnEdit);
				 this->Controls->Add(this->btnDelete);
				 this->Controls->Add(this->btnSave);
				 this->Controls->Add(this->btnCancel);
				 this->Controls->Add(this->panelDetails);
				 this->Controls->Add(this->webBrowser1);
				 this->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				 this->MaximizeBox = false;
				 this->Name = L"MainForm";
				 this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
				 this->Text = L"BibTexPro";
				 this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
				 this->Shown += gcnew System::EventHandler(this, &MainForm::MainForm_Shown);
				 this->panelDetails->ResumeLayout(false);
				 this->panelDetails->PerformLayout();
				 this->pnlNameEdit->ResumeLayout(false);
				 this->pnlNameEdit->PerformLayout();
				 this->toolStrip1->ResumeLayout(false);
				 this->toolStrip1->PerformLayout();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }


			 // Änderung der angezeigten Felder wenn der Referenztyp geändert wird
			 void listViewEntries_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
				 if (listViewEntries->SelectedIndices->Count > 0 && !isEditMode) { //Überprüfen ob mindestens ein Eintrag in der ListView ausgewählt ist und der Bearbeitungsmodus nicht aktiv ist
					 int index = listViewEntries->SelectedIndices[0]; // Zahl des ersten ausgewählten Eintrags
					 currentEntry = entries[index]; // Weist den aktuell ausgewählten Eintrag aus der viewlist anhand des Index zu
					 DisplayEntryDetails(currentEntry);
					 btnEdit->Enabled = true;
					 btnDelete->Enabled = true;
				 }
				 else {
					 btnEdit->Enabled = false;
					 btnDelete->Enabled = false;
				 }
			 }



			 // Event Löschen Button wird gedrückt
			 void btnDelete_Click(System::Object^ sender, System::EventArgs^ e) {
				 if (listViewEntries->SelectedIndices->Count > 0) {
					 int index = listViewEntries->SelectedIndices[0];
					 entries->RemoveAt(index); // Eintrag mit entsprechendem Index wird gelöscht
					 RefreshListView();	// Listenansicht wird aktualisiert	
					 ClearEntryDetails();	// Textfelder werden bereinigt
				 }
			 }


			 // Event Referenztyp Auswahl
			 void cmbType_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
			 {
				 if (cmbType->SelectedItem != nullptr)
				 {
					 String^ selectedType = cmbType->SelectedItem->ToString();

					 for each (DataTypeFields^ type in dataTypes)
					 {
						 if (type->TypeName == selectedType)
						 {
							 int TabNumberCurrent = ShowFieldsForType(type);
							 txtFirstName->TabIndex = TabNumberCurrent++;
							 txtLastName->TabIndex = TabNumberCurrent++;
							 btnSetAuthor->TabIndex = TabNumberCurrent++;
							 btnClearAuthor->TabIndex = TabNumberCurrent++;
							 btnSave->TabIndex = TabNumberCurrent++;
							 btnCancel->TabIndex = TabNumberCurrent++;
							 btnSaveHDD->TabIndex = TabNumberCurrent++;
							 btnExportToBib->TabIndex = TabNumberCurrent;
							 break;
						 }
					 }
				 }
				 else
				 {
					 HideAllFields();
				 }
			 }










	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void MainForm_Shown(System::Object^ sender, System::EventArgs^ e) {
		// bin Datei beim Start laden
		bool success = LoadEntries("entries.bin");
		this->BringToFront();
		this->Activate();
		String^ text;
		if (success) {
			RefreshListView(); // Aktualisiere die Anzeige der Einträge, wenn das Laden erfolgreich war
			if (en_de == 0) {
				text = nachrichten[35, 0];
			}
			else if (en_de == 1) {
				text = nachrichten[35, 1];
			}
			MessageBox::Show(text, "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else {
			if (en_de == 0) {
				text = nachrichten[36, 0];
			}
			else if (en_de == 1) {
				text = nachrichten[36, 1];
			}
			MessageBox::Show(text, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}

	}

	private: System::Void btnSaveHDD_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ text;
		// Einträge in Bin speichern
		SaveEntries("entries.bin");
		if (en_de == 0) {
			text = nachrichten[37, 0];
		}
		else if (en_de == 1) {
			text = nachrichten[37, 1];
		}
		MessageBox::Show(text, "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}


	private:	System::Void txtSearch_TextChanged(System::Object^  sender, System::EventArgs^  e) { //wird automatisch durchsucht wenn etwas eingegeben wird
		String^ searchTerm = txtSearch->Text->Trim();
		PerformSearch(searchTerm);

	}
	private:	System::Void btnSetAuthor_Click(System::Object^ sender, System::EventArgs^ e)
	{
		SetAuthor();
	}

	private: System::Void btnClearAuthor_Click(System::Object^  sender, System::EventArgs^  e) {
		listViewAuthors->Items->Clear();
		if (rbtnAuthor->Checked) {
			txtAuthor->Clear(); 
		}
		else if (rbtnEditor->Checked) {
			txtEditor->Clear(); 
		}
		else {
			if (en_de == 0) {
				MessageBox::Show(nachrichten[40, 0]);
			}
			else if (en_de == 1) {
				MessageBox::Show(nachrichten[40, 1]);
			}
		}

	}
	private: System::Void btnExportToBib_Click(System::Object^  sender, System::EventArgs^  e) {

		ExportToBib();
	}

			 //mein
			 void listViewAuthors_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
			 {
				 if (listViewAuthors->SelectedItems->Count > 0 && rbtnAuthor->Checked) // Überprüft ob ein Element in der Liste ausgewählt wurde und ob der Radiobutton für "Autor" aktiviert ist
				 {
					 String^ selectedAuthor = listViewAuthors->SelectedItems[0]->Text; // Holt den Text von dem ausgewählten Autors
					 array<String^>^ nameParts = selectedAuthor->Split(','); // Teilt den Namen in Teile auf basierend auf einem Komma (Nachname, Vorname)
					 txtLastName->Text = nameParts[0]; // Nachname
					 txtFirstName->Text = nameParts->Length > 1 ? nameParts[1] : ""; // Vorname
				 }
				 if (listViewAuthors->SelectedItems->Count > 0 && rbtnEditor->Checked) // Überprüft ob ein Element in der Liste ausgewählt wurde und ob der Radiobutton für "Editor" aktiviert ist
				 {
					 String^ selectedAuthor = listViewAuthors->SelectedItems[0]->Text; // Holt den Text von dem ausgewählten Editors

					 array<String^>^ nameParts = selectedAuthor->Split(',');// Teilt den Namen in Teile auf basierend auf einem Komma (Nachname, Vorname)
					 txtLastName->Text = nameParts[0]; // Nachname
					 txtFirstName->Text = nameParts->Length > 1 ? nameParts[1] : ""; // Vorname
				 }
			 }

			 bool TypeChanged = false;
			 bool tc_no_edit = false;

	private: System::Void rbtnAuthor_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (rbtnAuthor->Checked) {// Überprüfen, ob das Autor-Radiobutton ausgewählt wurde

			if (cmbType->SelectedItem != "conference" && cmbType->SelectedItem != "incollection" && cmbType->SelectedItem != "inproceedings") {   // Wenn der ausgewählte Typ nicht "conference", "incollection" oder "inproceedings" ist
				if (!String::IsNullOrEmpty(txtEditor->Text)) { // Überprüfen ob das Editor-Feld nicht leer ist
					if (TypeChanged == true) { // Wenn der Typ geändert wurde
						txtEditor->Text = ""; // Leere das Editor-Feld, da der Typ geändert wurde
						TypeChanged = false;// Setze den Typwechsel zurück
					}
					else {
						txtAuthor->Text = txtEditor->Text; // Kopiere den Text vom Editor-Feld ins Autor-Feld
						tc_no_edit = false;
					}
					txtEditor->Clear();// Leere das Editor-Feld
					listViewAuthors->Items->Clear(); // Lösche alle Einträge in der Autorenliste
					if (txtAuthor->Text != "") // Wenn das Autor-Feld nicht leer ist
					{
						array<String^>^ authors = txtAuthor->Text->Split(gcnew array<String^>{ " and " }, StringSplitOptions::None); // Teile den Text im Autor-Feld anhand des Wortes "and"
						for each (String^ author in authors)// Füge jeden Autor einzeln zur listview hinzu
						{
							listViewAuthors->Items->Add(author->Trim()); // Added den Author in die listview
						}
					}
				}
			}
			else { // Wenn der Typ einer der speziellen Typen ist (conference, incollection, inproceedings)
				TypeChanged = true; // Setzt das der Typ gewechselt wurde
				listViewAuthors->Items->Clear(); // Lösche alle Einträge in der listview
				if (txtAuthor->Text != "") // Wenn das Autor-Feld nicht leer ist
				{
					array<String^>^ authors = txtAuthor->Text->Split(gcnew array<String^>{ " and " }, StringSplitOptions::None); // Teile den Text im Autor-Feld anhand des Wortes "and"
					for each (String^ author in authors)// Füge jeden Autor einzeln zur Autorenliste hinzu
					{
						listViewAuthors->Items->Add(author->Trim()); // Added den Author in die listview
					}
				}
			}
		}
	}

	private: System::Void rbtnEditor_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (rbtnEditor->Checked) { // Überprüfen, ob das Editor-Radiobutton ausgewählt wurde



			if (cmbType->SelectedItem != "conference" && cmbType->SelectedItem != "incollection" && cmbType->SelectedItem != "inproceedings") {  // Überprüfen, ob der ausgewählte Typ nicht "conference", "incollection" oder "inproceedings" ist
				if (!String::IsNullOrEmpty(txtAuthor->Text)/* && !TypeChanged*/) {// Wenn das Author-Feld nicht leer ist und
					if (TypeChanged == true) {// Wenn der Typ geändert wurde
						txtAuthor->Text = ""; // Leere das Autor-Feld, wenn der Typ geändert wurde
						TypeChanged = false;// Setze den Typwechsel zurück
					}
					else { // Wenn der Typ nicht geändert wurde
						txtEditor->Text = txtAuthor->Text; // Kopiere den Text aus dem Autor-Feld ins Editor-Feld
						tc_no_edit = false;
					}
					txtAuthor->Clear(); // Löscht den Inhalt des Autor-Feldes

					listViewAuthors->Items->Clear(); // Löscht alle Einträge in der Autorenliste
					if (txtEditor->Text != "") // Wenn das Editor-Feld nicht leer ist
					{
						array<String^>^ editors = txtEditor->Text->Split(gcnew array<String^>{ " and " }, StringSplitOptions::None); //Teile den Text im Editor-Feld anhand des Wortes "and"
						for each (String^ editor in editors) // Läuft durch jeden Eintrag in editors  durch
						{
							listViewAuthors->Items->Add(editor->Trim()); // Added den Editor in die listview
						}
					}
				}
			}
			else {   // Wenn der Typ einer der speziellen Typen ist
				TypeChanged = true;// Setzt das der Typ gewechselt wurde
				listViewAuthors->Items->Clear(); // Leere die listview
				if (txtEditor->Text != "") // Wenn das Editor-Feld nicht leer ist
				{
					array<String^>^ editors = txtEditor->Text->Split(gcnew array<String^>{ " and " }, StringSplitOptions::None);//Teile den Text im Editor-Feld anhand des Wortes "and"
					for each (String^ editor in editors) // Läuft durch jeden Eintrag in editors  durchv
					{
						listViewAuthors->Items->Add(editor->Trim()); // Added den Editor in die listview
					}
				}
			}
		}
	}

			 int en_de; // Variable zur Einstellung der Sprache (0 = Englisch, 1 = Deutsch)




	private: System::Void darkmodeLightmodeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void btnDarkmode_Click(System::Object^  sender, System::EventArgs^  e) {

		DarkMode();
	}

	private: System::Void btnLanguage_Click(System::Object^  sender, System::EventArgs^  e) {
		bool n; //Variable zur Kontrolle, ob die Sprache bereits geändert wurde
		n = false; //setzt n auf false
		if (en_de == 0 && n == false) { // Wenn die Sprache Englisch ist  n false ist
			en_de = 1; // Setze die Sprache auf Deutsch 
			n = true; // Setze n auf true um zu verhindern dass die Sprache erneut geändert wird
		}

		if (en_de == 1 && n == false) { // Wenn die aktuelle Sprache Deutsch ist und n false ist
			en_de = 0; // Setze die Sprache auf Englisch 
			n = true; // Setze n auf true um zu verhindern dass die Sprache erneut geändert wird
		}
		sprache_aendern(); // Ruf die Funktion auf um die Sprache in der Benutzeroberfläche zu ändern
	}

		private: System::Void btnPDF_Click(System::Object^  sender, System::EventArgs^  e) {

			OpenPDF();
		}
	};
}
