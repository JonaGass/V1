#pragma once
#include "Data.h"
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

	public ref class MainForm : public System::Windows::Forms::Form {
	public:
		MainForm(void) {
			InitializeComponent();
			InitializeDataTypes();
			PopulateTypeDropdown();
			entries = gcnew List<DataArray^>();
			displayedEntryIndices = gcnew List<int>();
			HideAllFields();
			UpdateUIState(false);
		}

	protected:
		~MainForm() {
			if (components) {
				delete components;
			}
		}


	private:
	private:
		List<int>^ displayedEntryIndices; // To store the indices of displayed entries after searching
	private:
		System::Windows::Forms::TextBox^ txtFirstName;
		System::Windows::Forms::TextBox^ txtLastName;
		System::Windows::Forms::Button^ button1;
		System::Windows::Forms::Button^ btnSetAuthor;
		System::Windows::Forms::TextBox^ txtSearch;
		System::ComponentModel::Container^ components;
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

		List<DataArray^>^ entries;
		DataArray^ currentEntry;
		array<DataTypeFields^>^ dataTypes;
	private: System::Windows::Forms::Button^  btnSaveHDD;
	private: System::Windows::Forms::Button^  btnClearAuthor;
			 bool isEditMode;


		void InitializeDataTypes() {
			dataTypes = GetDataTypes();
		}


		 //Function to initialize the type dropdown with entry types
		void PopulateTypeDropdown()
		{
			for each (DataTypeFields ^ type in dataTypes)
			{
				cmbType->Items->Add(type -> TypeName);
			}
		}

		// Function to display entry details in the panel
		void DisplayEntryDetails(DataArray^ entry)
		{
			cmbType->SelectedItem = entry->type;
			txtKeyword->Text = entry->keyword;
			txtAuthor->Text = entry->author;
			txtTitle->Text = entry->title;
			txtYear->Text = entry->year;
			txtJournal->Text = entry->journal;
			txtVolume->Text = entry->volume;
			txtNumber->Text = entry->number;
			txtPages->Text = entry->pages;
			txtMonth->Text = entry->month;
			txtNote->Text = entry->note;
			txtPublisher->Text = entry->publisher;
			txtSeries->Text = entry->series;
			txtAddress->Text = entry->address;
			txtEdition->Text = entry->edition;
			txtHowpublished->Text = entry->howpublished;
			txtBooktitle->Text = entry->booktitle;
			txtEditor->Text = entry->editor;
			txtChapter->Text = entry->chapter;
			txtSchool->Text = entry->school;
			txtInstitution->Text = entry->institution;
			txtOrganization->Text = entry->organization;
			SetFieldsReadOnly(true);
		}

		// Function to clear entry details from the panel
		void ClearEntryDetails()
		{
			currentEntry = nullptr;
			cmbType->SelectedIndex = -1;
			txtKeyword->Clear();
			txtAuthor->Clear();
			txtTitle->Clear();
			txtYear->Clear();
			txtJournal->Clear();
			txtVolume->Clear();
			txtNumber->Clear();
			txtPages->Clear();
			txtMonth->Clear();
			txtNote->Clear();
			txtPublisher->Clear();
			txtSeries->Clear();
			txtAddress->Clear();
			txtEdition->Clear();
			txtHowpublished->Clear();
			txtBooktitle->Clear();
			txtEditor->Clear();
			txtChapter->Clear();
			txtSchool->Clear();
			txtInstitution->Clear();
			txtOrganization->Clear();
			SetFieldsReadOnly(false);
		}

		// Function to toggle read-only state of fields
		void SetFieldsReadOnly(bool readOnly)
		{
			txtKeyword->ReadOnly = readOnly;
			// txtAuthor->ReadOnly = readOnly;
			txtTitle->ReadOnly = readOnly;
			txtYear->ReadOnly = readOnly;
			txtJournal->ReadOnly = readOnly;
			txtVolume->ReadOnly = readOnly;
			txtNumber->ReadOnly = readOnly;
			txtPages->ReadOnly = readOnly;
			txtMonth->ReadOnly = readOnly;
			txtNote->ReadOnly = readOnly;
			txtPublisher->ReadOnly = readOnly;
			txtSeries->ReadOnly = readOnly;
			txtAddress->ReadOnly = readOnly;
			txtEdition->ReadOnly = readOnly;
			txtHowpublished->ReadOnly = readOnly;
			txtBooktitle->ReadOnly = readOnly;
			txtEditor->ReadOnly = readOnly;
			txtChapter->ReadOnly = readOnly;
			txtSchool->ReadOnly = readOnly;
			txtInstitution->ReadOnly = readOnly;
			txtOrganization->ReadOnly = readOnly;
		}

		// Event handler for new entry button click
		void btnNew_Click(System::Object^ sender, System::EventArgs^ e) {
			ClearEntryDetails();
			currentEntry = gcnew DataArray();
			UpdateUIState(true);
		}

		// Event handler for edit button click
		void btnEdit_Click(System::Object^ sender, System::EventArgs^ e) {
			if (listViewEntries->SelectedIndices->Count > 0) {
				int index = listViewEntries->SelectedIndices[0];
				currentEntry = entries[index];
				DisplayEntryDetails(currentEntry);
				UpdateUIState(true);
			}
		}

		// Event handler for save button click
		void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
			if (ValidateEntry() && ValidateOptional()) {

				currentEntry->type = cmbType->SelectedItem->ToString();
				currentEntry->keyword = txtKeyword->Text;
				currentEntry->author = txtAuthor->Text;
				currentEntry->title = txtTitle->Text;
				currentEntry->year = txtYear->Text;
				currentEntry->journal = txtJournal->Text;
				currentEntry->volume = txtVolume->Text;
				currentEntry->number = txtNumber->Text;
				currentEntry->pages = txtPages->Text;
				currentEntry->month = txtMonth->Text;
				currentEntry->note = txtNote->Text;
				currentEntry->publisher = txtPublisher->Text;
				currentEntry->series = txtSeries->Text;
				currentEntry->address = txtAddress->Text;
				currentEntry->edition = txtEdition->Text;
				currentEntry->howpublished = txtHowpublished->Text;
				currentEntry->booktitle = txtBooktitle->Text;
				currentEntry->editor = txtEditor->Text;
				currentEntry->chapter = txtChapter->Text;
				currentEntry->school = txtSchool->Text;
				currentEntry->institution = txtInstitution->Text;
				currentEntry->organization = txtOrganization->Text;

				if (entries->IndexOf(currentEntry) == -1) {
					entries->Add(currentEntry);
					//Console::WriteLine("currentEntry: {0}", currentEntry);
				}
				else {
					int index = entries->IndexOf(currentEntry);
					entries[index] = currentEntry;

				}

				RefreshListView();
				UpdateUIState(false);
				ClearEntryDetails();
			}
		}


		// Event handler for cancel button click
		void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
			ClearEntryDetails();
			UpdateUIState(false);
		}



		bool ValidateEntry()
		{
			bool stateMandatory = true;
			if (cmbType->SelectedIndex == -1)
			{
				MessageBox::Show("Please select an entry type.");
				stateMandatory = false;
			}

			String^ selectedType = cmbType->SelectedItem->ToString();
			DataTypeFields^ selectedTypeFields = nullptr;

			// Find the selected type in the dataTypes array
			for each (DataTypeFields^ type in dataTypes)
			{
				if (type->TypeName == selectedType)
				{
					selectedTypeFields = type;
					break;
				}
			}

			if (selectedTypeFields == nullptr)
			{
				MessageBox::Show("Invalid entry type selected.");
				stateMandatory = false;
			}

			String^ errorMessage = "";
			bool hasAuthor = false;
			bool hasEditor = false;
			bool AuthorMandatory = false;
			bool EditorMandatory = false;
			bool hasChapter = false;
			bool hasPages = false;
			bool ChapterMandatory = false;
			bool PagesMandatory = false;

			// Check each required field
			for each (String^ field in selectedTypeFields->RequiredFields)
			{
				if (field == "keyword" && txtKeyword->Text->Trim() == String::Empty) {
					errorMessage += "Please fill in the keyword field.\n";
					stateMandatory = false;
				}
				if (field == "author") {
					AuthorMandatory = true;
					if (txtAuthor->Text->Trim() == String::Empty) {
						//errorMessage += "Please fill in the author field.\n";
						//stateMandatory = false;
					}
					else {
						hasAuthor = true; // Author is present
					}
				}
				if (field == "title" && txtTitle->Text->Trim() == String::Empty) {
					errorMessage += "Please fill in the title field.\n";
					stateMandatory = false;
				}
				int year;
				if ((field == "year" && txtYear->Text->Trim() == String::Empty) || (field == "year" && !Int32::TryParse(txtYear->Text, year))) {
					errorMessage += "Please enter a number into the year field.\n";
					stateMandatory = false;
				}
				if (field == "journal" && txtJournal->Text->Trim() == String::Empty) {
					errorMessage += "Please fill in the journal field.\n";
					stateMandatory = false;
				}
				int volume;
				if ((field == "volume" && txtVolume->Text->Trim() == String::Empty) || (field == "volume" && !Int32::TryParse(txtVolume->Text, volume))) {
					errorMessage += "Please enter a number into the volume field.\n";
					stateMandatory = false;
				}
				int number;
				if ((field == "number" && txtNumber->Text->Trim() == String::Empty) || (field == "number" && !Int32::TryParse(txtNumber->Text, number))) {
					errorMessage += "Please enter a number into the number field.\n";
					stateMandatory = false;
				}
				int pages;
				/*if ((field == "pages" && txtPages->Text->Trim() == String::Empty) || (field == "pages" && !Int32::TryParse(txtPages->Text, pages))) {
					errorMessage += "Please enter a number into the pages field.\n";
					stateMandatory = false;
				}*/
				if (field == "pages") {
					PagesMandatory = true;
					if (txtPages->Text->Trim() == String::Empty) {
						//errorMessage += "Please enter a number into the pages field.\n";
						//stateMandatory = false;
					}
					else if (!Int32::TryParse(txtPages->Text, pages)) {
						errorMessage += "Please enter a number into the pages field.\n";
					}
					else {
						hasPages = true; // Pages is present
					}
				}
				if (field == "month" && txtMonth->Text->Trim() == String::Empty) {
					errorMessage += "Please fill in the month field.\n";
					stateMandatory = false;
				}
				if (field == "note" && txtNote->Text->Trim() == String::Empty) {
					errorMessage += "Please fill in the note field.\n";
					stateMandatory = false;
				}
				if (field == "publisher" && txtPublisher->Text->Trim() == String::Empty) {
					errorMessage += "Please fill in the publisher field.\n";
					stateMandatory = false;
				}
				if (field == "series" && txtSeries->Text->Trim() == String::Empty) {
					errorMessage += "Please fill in the series field.\n";
					stateMandatory = false;
				}
				if (field == "address" && txtAddress->Text->Trim() == String::Empty) {
					errorMessage += "Please fill in the address field.\n";
					stateMandatory = false;
				}
				if (field == "edition" && txtEdition->Text->Trim() == String::Empty) {
					errorMessage += "Please fill in the edition field.\n";
					stateMandatory = false;
				}
				if (field == "howpublished" && txtHowpublished->Text->Trim() == String::Empty) {
					errorMessage += "Please fill in the how published field.\n";
					stateMandatory = false;
				}
				if (field == "booktitle" && txtBooktitle->Text->Trim() == String::Empty) {
					errorMessage += "Please fill in the book title field.\n";
					stateMandatory = false;
				}
				if (field == "editor") {
					EditorMandatory = true;
					if (txtEditor->Text->Trim() == String::Empty) {
						//errorMessage += "Please fill in the editor field.\n";
						//stateMandatory = false;
					}
					else {
						hasEditor = true; // Editor is present
					}
				}
				/*if (field == "chapter" && txtChapter->Text->Trim() == String::Empty) {
					errorMessage += "Please fill in the chapter field.\n";
					stateMandatory = false;
				}*/
				if (field == "chapter") {
					ChapterMandatory = true;
					if (txtChapter->Text->Trim() == String::Empty) {
						//errorMessage += "Please fill in the Chapter field.\n";
						//stateMandatory = false;
					}
					else {
						hasChapter = true; // Chapter is present
					}
				}

				if (field == "school" && txtSchool->Text->Trim() == String::Empty) {
					errorMessage += "Please fill in the school field.\n";
					stateMandatory = false;
				}
				if (field == "institution" && txtInstitution->Text->Trim() == String::Empty) {
					errorMessage += "Please fill in the institution field.\n";
					stateMandatory = false;
				}
				if (field == "organization" && txtOrganization->Text->Trim() == String::Empty) {
					errorMessage += "Please fill in the organization field.\n";
					stateMandatory = false;
				}
			}

			// Check if either author or editor is filled if both are mandatory
			if (AuthorMandatory && EditorMandatory)
			{
				if (!hasAuthor && !hasEditor) {
					errorMessage += "Please fill in either the author or the editor field.\n";
					stateMandatory = false;
				}
				else if (hasAuthor && hasEditor) {
					errorMessage += "Cannot have both Author and Editor!\n";
					stateMandatory = false;
				}
			}
			else if (AuthorMandatory){
				if (!hasAuthor) {
					errorMessage += "Please fill in the author field.\n";
					stateMandatory = false;
				}
			}
			else {
				if (!hasEditor) {
					errorMessage += "Please fill in the editor field.\n";
					stateMandatory = false;
				}
			}

			if (PagesMandatory && ChapterMandatory)
			{
				if (!hasPages && !hasChapter) {
					errorMessage += "Please fill in either the Pages or the Chapter field.\n";
					stateMandatory = false;
				}
			}
			else if (PagesMandatory) {
				if (!hasPages) {
					errorMessage += "Please fill in the Pages field.\n";
					stateMandatory = false;
				}
			}
			else if (ChapterMandatory) {
				if (!hasChapter) {
					errorMessage += "Please fill in the Chapter field.\n";
					stateMandatory = false;
				}
			}

			if (!stateMandatory) {
				MessageBox::Show(errorMessage, "Missing Input", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
			return stateMandatory;
		}

		bool ValidateOptional()
		{
			bool stateOptional = true;
			// Check if an entry type is selected
			if (cmbType->SelectedIndex == -1)
			{
				MessageBox::Show("Please select an entry type.");
				return false;
			}

			String^ selectedType = cmbType->SelectedItem->ToString();
			DataTypeFields^ selectedTypeFields = nullptr;

			// Find the selected type in the dataTypes array
			for each (DataTypeFields^ type in dataTypes)
			{
				if (type->TypeName == selectedType)
				{
					selectedTypeFields = type;
					break;
				}
			}

			if (selectedTypeFields == nullptr)
			{
				MessageBox::Show("Invalid entry type selected.");
				return false;
			}
			String^ errorMessageOptional = "";
			// Check each optional field; leave conditions empty
			for each (String^ field in selectedTypeFields->OptionalFields)
			{
				if (field == "keyword") {
					// zu ergänzen
				}
				if (field == "author") {
					// zu ergänzen
				}
				if (field == "title") {
					// zu ergänzen
				}
				int year;
				if (field == "year" && !Int32::TryParse(txtYear->Text, year) && !(txtYear->Text->Trim() == String::Empty)) {
					stateOptional = false;
					errorMessageOptional += "Year must be a number.\n";
				}
				if (field == "journal") {
					// zu ergänzen
				}
				int volume;
				if (field == "volume" && !Int32::TryParse(txtVolume->Text, volume) && !(txtVolume->Text->Trim() == String::Empty)) {
					stateOptional = false;
					errorMessageOptional += "Volume must be a number.\n";
				}
				int number;
				if (field == "number" && !Int32::TryParse(txtNumber->Text, number) && !(txtNumber->Text->Trim() == String::Empty)) {
					stateOptional = false;
					errorMessageOptional += "Number must be a number.\n";
				}
				int pages;
				if (field == "pages" && !Int32::TryParse(txtPages->Text, pages) && !(txtPages->Text->Trim() == String::Empty)) {
					stateOptional = false;
					errorMessageOptional += "Pages must be a number.\n";
				}
				if (field == "month") {
					// zu ergänzen
				}
				if (field == "note") {
					// zu ergänzen
				}
				if (field == "publisher") {
					// zu ergänzen
				}
				if (field == "series") {
					// zu ergänzen
				}
				if (field == "address") {
					// zu ergänzen
				}
				if (field == "edition") {
					// zu ergänzen
				}
				if (field == "howpublished") {
					// zu ergänzen
				}
				if (field == "booktitle") {
					// zu ergänzen
				}
				if (field == "editor") {
					// zu ergänzen
				}
				if (field == "chapter") {
					// zu ergänzen
				}
				if (field == "school") {
					// zu ergänzen
				}
				if (field == "institution") {
					// zu ergänzen
				}
				if (field == "organization") {
					// zu ergänzen
				}
			}
			if (!stateOptional) {
				MessageBox::Show(errorMessageOptional, "Missing Input", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
			return stateOptional;
		}
		void InitializeComponent(void)
		{
			this->txtFirstName = (gcnew System::Windows::Forms::TextBox());
			this->txtLastName = (gcnew System::Windows::Forms::TextBox());
			this->btnSetAuthor = (gcnew System::Windows::Forms::Button());
			this->listViewEntries = (gcnew System::Windows::Forms::ListView());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->btnNew = (gcnew System::Windows::Forms::Button());
			this->btnEdit = (gcnew System::Windows::Forms::Button());
			this->btnDelete = (gcnew System::Windows::Forms::Button());
			this->panelDetails = (gcnew System::Windows::Forms::Panel());
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
			this->lblFirstName = (gcnew System::Windows::Forms::Label());
			this->lblLastName = (gcnew System::Windows::Forms::Label());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->btnSaveHDD = (gcnew System::Windows::Forms::Button());
			this->txtSearch = (gcnew System::Windows::Forms::TextBox());
			this->btnClearAuthor = (gcnew System::Windows::Forms::Button());
			this->panelDetails->SuspendLayout();
			this->SuspendLayout();
			// 
			// txtFirstName
			// 
			this->txtFirstName->Location = System::Drawing::Point(322, 500);
			this->txtFirstName->Name = L"txtFirstName";
			this->txtFirstName->Size = System::Drawing::Size(100, 20);
			this->txtFirstName->TabIndex = 0;
			// 
			// txtLastName
			// 
			this->txtLastName->Location = System::Drawing::Point(432, 500);
			this->txtLastName->Name = L"txtLastName";
			this->txtLastName->Size = System::Drawing::Size(100, 20);
			this->txtLastName->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(611, 10);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Export to bib";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// btnSetAuthor
			// 
			this->btnSetAuthor->Location = System::Drawing::Point(542, 500);
			this->btnSetAuthor->Name = L"btnSetAuthor";
			this->btnSetAuthor->Size = System::Drawing::Size(75, 23);
			this->btnSetAuthor->TabIndex = 1;
			this->btnSetAuthor->Text = L"Set";
			this->btnSetAuthor->Click += gcnew System::EventHandler(this, &MainForm::btnSetAuthor_Click);
			// 
			// listViewEntries
			// 
			this->listViewEntries->HideSelection = false;
			this->listViewEntries->Location = System::Drawing::Point(10, 10);
			this->listViewEntries->Name = L"listViewEntries";
			this->listViewEntries->Size = System::Drawing::Size(300, 500);
			this->listViewEntries->TabIndex = 0;
			this->listViewEntries->UseCompatibleStateImageBehavior = false;
			this->listViewEntries->View = System::Windows::Forms::View::List;
			this->listViewEntries->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::listViewEntries_SelectedIndexChanged);
			// 
			// btnNew
			// 
			this->btnNew->Location = System::Drawing::Point(320, 10);
			this->btnNew->Name = L"btnNew";
			this->btnNew->Size = System::Drawing::Size(75, 23);
			this->btnNew->TabIndex = 1;
			this->btnNew->Text = L"New";
			this->btnNew->Click += gcnew System::EventHandler(this, &MainForm::btnNew_Click);
			// 
			// btnEdit
			// 
			this->btnEdit->Location = System::Drawing::Point(400, 10);
			this->btnEdit->Name = L"btnEdit";
			this->btnEdit->Size = System::Drawing::Size(75, 23);
			this->btnEdit->TabIndex = 2;
			this->btnEdit->Text = L"Edit";
			this->btnEdit->Click += gcnew System::EventHandler(this, &MainForm::btnEdit_Click);
			// 
			// btnDelete
			// 
			this->btnDelete->Location = System::Drawing::Point(480, 10);
			this->btnDelete->Name = L"btnDelete";
			this->btnDelete->Size = System::Drawing::Size(75, 23);
			this->btnDelete->TabIndex = 3;
			this->btnDelete->Text = L"Delete";
			this->btnDelete->Click += gcnew System::EventHandler(this, &MainForm::btnDelete_Click);
			// 
			// panelDetails
			// 
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
			this->panelDetails->Location = System::Drawing::Point(320, 50);
			this->panelDetails->Name = L"panelDetails";
			this->panelDetails->Size = System::Drawing::Size(450, 400);
			this->panelDetails->TabIndex = 6;
			// 
			// cmbType
			// 
			this->cmbType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbType->Location = System::Drawing::Point(10, 10);
			this->cmbType->Name = L"cmbType";
			this->cmbType->Size = System::Drawing::Size(121, 21);
			this->cmbType->TabIndex = 0;
			this->cmbType->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::cmbType_SelectedIndexChanged);
			// 
			// txtKeyword
			// 
			this->txtKeyword->Location = System::Drawing::Point(0, 0);
			this->txtKeyword->Name = L"txtKeyword";
			this->txtKeyword->Size = System::Drawing::Size(100, 20);
			this->txtKeyword->TabIndex = 1;
			// 
			// txtAuthor
			// 
			this->txtAuthor->Location = System::Drawing::Point(0, 0);
			this->txtAuthor->Name = L"txtAuthor";
			this->txtAuthor->Size = System::Drawing::Size(100, 20);
			this->txtAuthor->TabIndex = 0;
			// 
			// txtTitle
			// 
			this->txtTitle->Location = System::Drawing::Point(0, 0);
			this->txtTitle->Name = L"txtTitle";
			this->txtTitle->Size = System::Drawing::Size(100, 20);
			this->txtTitle->TabIndex = 0;
			// 
			// txtYear
			// 
			this->txtYear->Location = System::Drawing::Point(0, 0);
			this->txtYear->Name = L"txtYear";
			this->txtYear->Size = System::Drawing::Size(100, 20);
			this->txtYear->TabIndex = 0;
			// 
			// txtJournal
			// 
			this->txtJournal->Location = System::Drawing::Point(0, 0);
			this->txtJournal->Name = L"txtJournal";
			this->txtJournal->Size = System::Drawing::Size(100, 20);
			this->txtJournal->TabIndex = 0;
			// 
			// txtVolume
			// 
			this->txtVolume->Location = System::Drawing::Point(0, 0);
			this->txtVolume->Name = L"txtVolume";
			this->txtVolume->Size = System::Drawing::Size(100, 20);
			this->txtVolume->TabIndex = 0;
			// 
			// txtNumber
			// 
			this->txtNumber->Location = System::Drawing::Point(0, 0);
			this->txtNumber->Name = L"txtNumber";
			this->txtNumber->Size = System::Drawing::Size(100, 20);
			this->txtNumber->TabIndex = 0;
			// 
			// txtPages
			// 
			this->txtPages->Location = System::Drawing::Point(0, 0);
			this->txtPages->Name = L"txtPages";
			this->txtPages->Size = System::Drawing::Size(100, 20);
			this->txtPages->TabIndex = 0;
			// 
			// txtMonth
			// 
			this->txtMonth->Location = System::Drawing::Point(0, 0);
			this->txtMonth->Name = L"txtMonth";
			this->txtMonth->Size = System::Drawing::Size(100, 20);
			this->txtMonth->TabIndex = 0;
			// 
			// txtNote
			// 
			this->txtNote->Location = System::Drawing::Point(0, 0);
			this->txtNote->Name = L"txtNote";
			this->txtNote->Size = System::Drawing::Size(100, 20);
			this->txtNote->TabIndex = 0;
			// 
			// txtPublisher
			// 
			this->txtPublisher->Location = System::Drawing::Point(0, 0);
			this->txtPublisher->Name = L"txtPublisher";
			this->txtPublisher->Size = System::Drawing::Size(100, 20);
			this->txtPublisher->TabIndex = 0;
			// 
			// txtSeries
			// 
			this->txtSeries->Location = System::Drawing::Point(0, 0);
			this->txtSeries->Name = L"txtSeries";
			this->txtSeries->Size = System::Drawing::Size(100, 20);
			this->txtSeries->TabIndex = 0;
			// 
			// txtAddress
			// 
			this->txtAddress->Location = System::Drawing::Point(0, 0);
			this->txtAddress->Name = L"txtAddress";
			this->txtAddress->Size = System::Drawing::Size(100, 20);
			this->txtAddress->TabIndex = 0;
			// 
			// txtEdition
			// 
			this->txtEdition->Location = System::Drawing::Point(0, 0);
			this->txtEdition->Name = L"txtEdition";
			this->txtEdition->Size = System::Drawing::Size(100, 20);
			this->txtEdition->TabIndex = 0;
			// 
			// txtHowpublished
			// 
			this->txtHowpublished->Location = System::Drawing::Point(0, 0);
			this->txtHowpublished->Name = L"txtHowpublished";
			this->txtHowpublished->Size = System::Drawing::Size(100, 20);
			this->txtHowpublished->TabIndex = 0;
			// 
			// txtBooktitle
			// 
			this->txtBooktitle->Location = System::Drawing::Point(0, 0);
			this->txtBooktitle->Name = L"txtBooktitle";
			this->txtBooktitle->Size = System::Drawing::Size(100, 20);
			this->txtBooktitle->TabIndex = 0;
			// 
			// txtEditor
			// 
			this->txtEditor->Location = System::Drawing::Point(0, 0);
			this->txtEditor->Name = L"txtEditor";
			this->txtEditor->Size = System::Drawing::Size(100, 20);
			this->txtEditor->TabIndex = 0;
			// 
			// txtChapter
			// 
			this->txtChapter->Location = System::Drawing::Point(0, 0);
			this->txtChapter->Name = L"txtChapter";
			this->txtChapter->Size = System::Drawing::Size(100, 20);
			this->txtChapter->TabIndex = 0;
			// 
			// txtSchool
			// 
			this->txtSchool->Location = System::Drawing::Point(0, 0);
			this->txtSchool->Name = L"txtSchool";
			this->txtSchool->Size = System::Drawing::Size(100, 20);
			this->txtSchool->TabIndex = 0;
			// 
			// txtInstitution
			// 
			this->txtInstitution->Location = System::Drawing::Point(0, 0);
			this->txtInstitution->Name = L"txtInstitution";
			this->txtInstitution->Size = System::Drawing::Size(100, 20);
			this->txtInstitution->TabIndex = 0;
			// 
			// txtOrganization
			// 
			this->txtOrganization->Location = System::Drawing::Point(0, 0);
			this->txtOrganization->Name = L"txtOrganization";
			this->txtOrganization->Size = System::Drawing::Size(100, 20);
			this->txtOrganization->TabIndex = 0;
			// 
			// lblKeyword
			// 
			this->lblKeyword->AutoSize = true;
			this->lblKeyword->Location = System::Drawing::Point(10, 10);
			this->lblKeyword->Name = L"lblKeyword";
			this->lblKeyword->Size = System::Drawing::Size(51, 13);
			this->lblKeyword->TabIndex = 1;
			this->lblKeyword->Text = L"Keyword:";
			// 
			// lblAuthor
			// 
			this->lblAuthor->AutoSize = true;
			this->lblAuthor->Location = System::Drawing::Point(10, 40);
			this->lblAuthor->Name = L"lblAuthor";
			this->lblAuthor->Size = System::Drawing::Size(41, 13);
			this->lblAuthor->TabIndex = 2;
			this->lblAuthor->Text = L"Author:";
			// 
			// lblTitle
			// 
			this->lblTitle->AutoSize = true;
			this->lblTitle->Location = System::Drawing::Point(10, 70);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(30, 13);
			this->lblTitle->TabIndex = 3;
			this->lblTitle->Text = L"Title:";
			// 
			// lblYear
			// 
			this->lblYear->AutoSize = true;
			this->lblYear->Location = System::Drawing::Point(10, 100);
			this->lblYear->Name = L"lblYear";
			this->lblYear->Size = System::Drawing::Size(32, 13);
			this->lblYear->TabIndex = 4;
			this->lblYear->Text = L"Year:";
			// 
			// lblJournal
			// 
			this->lblJournal->AutoSize = true;
			this->lblJournal->Location = System::Drawing::Point(10, 130);
			this->lblJournal->Name = L"lblJournal";
			this->lblJournal->Size = System::Drawing::Size(44, 13);
			this->lblJournal->TabIndex = 5;
			this->lblJournal->Text = L"Journal:";
			// 
			// lblVolume
			// 
			this->lblVolume->AutoSize = true;
			this->lblVolume->Location = System::Drawing::Point(10, 160);
			this->lblVolume->Name = L"lblVolume";
			this->lblVolume->Size = System::Drawing::Size(45, 13);
			this->lblVolume->TabIndex = 6;
			this->lblVolume->Text = L"Volume:";
			// 
			// lblNumber
			// 
			this->lblNumber->AutoSize = true;
			this->lblNumber->Location = System::Drawing::Point(10, 190);
			this->lblNumber->Name = L"lblNumber";
			this->lblNumber->Size = System::Drawing::Size(47, 13);
			this->lblNumber->TabIndex = 7;
			this->lblNumber->Text = L"Number:";
			// 
			// lblPages
			// 
			this->lblPages->AutoSize = true;
			this->lblPages->Location = System::Drawing::Point(10, 220);
			this->lblPages->Name = L"lblPages";
			this->lblPages->Size = System::Drawing::Size(40, 13);
			this->lblPages->TabIndex = 8;
			this->lblPages->Text = L"Pages:";
			// 
			// lblMonth
			// 
			this->lblMonth->AutoSize = true;
			this->lblMonth->Location = System::Drawing::Point(10, 250);
			this->lblMonth->Name = L"lblMonth";
			this->lblMonth->Size = System::Drawing::Size(40, 13);
			this->lblMonth->TabIndex = 9;
			this->lblMonth->Text = L"Month:";
			// 
			// lblNote
			// 
			this->lblNote->AutoSize = true;
			this->lblNote->Location = System::Drawing::Point(10, 280);
			this->lblNote->Name = L"lblNote";
			this->lblNote->Size = System::Drawing::Size(33, 13);
			this->lblNote->TabIndex = 10;
			this->lblNote->Text = L"Note:";
			// 
			// lblPublisher
			// 
			this->lblPublisher->AutoSize = true;
			this->lblPublisher->Location = System::Drawing::Point(10, 310);
			this->lblPublisher->Name = L"lblPublisher";
			this->lblPublisher->Size = System::Drawing::Size(53, 13);
			this->lblPublisher->TabIndex = 11;
			this->lblPublisher->Text = L"Publisher:";
			// 
			// lblSeries
			// 
			this->lblSeries->AutoSize = true;
			this->lblSeries->Location = System::Drawing::Point(10, 340);
			this->lblSeries->Name = L"lblSeries";
			this->lblSeries->Size = System::Drawing::Size(39, 13);
			this->lblSeries->TabIndex = 12;
			this->lblSeries->Text = L"Series:";
			// 
			// lblAddress
			// 
			this->lblAddress->AutoSize = true;
			this->lblAddress->Location = System::Drawing::Point(10, 370);
			this->lblAddress->Name = L"lblAddress";
			this->lblAddress->Size = System::Drawing::Size(48, 13);
			this->lblAddress->TabIndex = 13;
			this->lblAddress->Text = L"Address:";
			// 
			// lblEdition
			// 
			this->lblEdition->AutoSize = true;
			this->lblEdition->Location = System::Drawing::Point(10, 400);
			this->lblEdition->Name = L"lblEdition";
			this->lblEdition->Size = System::Drawing::Size(42, 13);
			this->lblEdition->TabIndex = 14;
			this->lblEdition->Text = L"Edition:";
			// 
			// lblHowpublished
			// 
			this->lblHowpublished->AutoSize = true;
			this->lblHowpublished->Location = System::Drawing::Point(10, 430);
			this->lblHowpublished->Name = L"lblHowpublished";
			this->lblHowpublished->Size = System::Drawing::Size(80, 13);
			this->lblHowpublished->TabIndex = 15;
			this->lblHowpublished->Text = L"How published:";
			// 
			// lblABooktitle
			// 
			this->lblABooktitle->AutoSize = true;
			this->lblABooktitle->Location = System::Drawing::Point(10, 460);
			this->lblABooktitle->Name = L"lblABooktitle";
			this->lblABooktitle->Size = System::Drawing::Size(51, 13);
			this->lblABooktitle->TabIndex = 16;
			this->lblABooktitle->Text = L"Booktitle:";
			// 
			// lblEditor
			// 
			this->lblEditor->AutoSize = true;
			this->lblEditor->Location = System::Drawing::Point(10, 490);
			this->lblEditor->Name = L"lblEditor";
			this->lblEditor->Size = System::Drawing::Size(37, 13);
			this->lblEditor->TabIndex = 17;
			this->lblEditor->Text = L"Editor:";
			// 
			// lblChapter
			// 
			this->lblChapter->AutoSize = true;
			this->lblChapter->Location = System::Drawing::Point(10, 520);
			this->lblChapter->Name = L"lblChapter";
			this->lblChapter->Size = System::Drawing::Size(47, 13);
			this->lblChapter->TabIndex = 18;
			this->lblChapter->Text = L"Chapter:";
			// 
			// lblSchool
			// 
			this->lblSchool->AutoSize = true;
			this->lblSchool->Location = System::Drawing::Point(10, 550);
			this->lblSchool->Name = L"lblSchool";
			this->lblSchool->Size = System::Drawing::Size(43, 13);
			this->lblSchool->TabIndex = 19;
			this->lblSchool->Text = L"School:";
			// 
			// lblInstitution
			// 
			this->lblInstitution->AutoSize = true;
			this->lblInstitution->Location = System::Drawing::Point(10, 580);
			this->lblInstitution->Name = L"lblInstitution";
			this->lblInstitution->Size = System::Drawing::Size(55, 13);
			this->lblInstitution->TabIndex = 20;
			this->lblInstitution->Text = L"Institution:";
			// 
			// lblOrganization
			// 
			this->lblOrganization->AutoSize = true;
			this->lblOrganization->Location = System::Drawing::Point(10, 610);
			this->lblOrganization->Name = L"lblOrganization";
			this->lblOrganization->Size = System::Drawing::Size(69, 13);
			this->lblOrganization->TabIndex = 21;
			this->lblOrganization->Text = L"Organization:";
			// 
			// lblFirstName
			// 
			this->lblFirstName->Location = System::Drawing::Point(322, 480);
			this->lblFirstName->Name = L"lblFirstName";
			this->lblFirstName->Size = System::Drawing::Size(100, 23);
			this->lblFirstName->TabIndex = 2;
			this->lblFirstName->Text = L"First Name:";
			// 
			// lblLastName
			// 
			this->lblLastName->Location = System::Drawing::Point(432, 480);
			this->lblLastName->Name = L"lblLastName";
			this->lblLastName->Size = System::Drawing::Size(100, 23);
			this->lblLastName->TabIndex = 3;
			this->lblLastName->Text = L"Last Name:";
			// 
			// btnSave
			// 
			this->btnSave->Location = System::Drawing::Point(320, 586);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(75, 23);
			this->btnSave->TabIndex = 4;
			this->btnSave->Text = L"Save";
			this->btnSave->Click += gcnew System::EventHandler(this, &MainForm::btnSave_Click);
			// 
			// btnCancel
			// 
			this->btnCancel->Location = System::Drawing::Point(400, 586);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(75, 23);
			this->btnCancel->TabIndex = 5;
			this->btnCancel->Text = L"Cancel";
			this->btnCancel->Click += gcnew System::EventHandler(this, &MainForm::btnCancel_Click);
			// 
			// btnSaveHDD
			// 
			this->btnSaveHDD->Location = System::Drawing::Point(558, 611);
			this->btnSaveHDD->Name = L"btnSaveHDD";
			this->btnSaveHDD->Size = System::Drawing::Size(75, 23);
			this->btnSaveHDD->TabIndex = 7;
			this->btnSaveHDD->Text = L"Save HDD";
			this->btnSaveHDD->UseVisualStyleBackColor = true;
			this->btnSaveHDD->Click += gcnew System::EventHandler(this, &MainForm::btnSaveHDD_Click);
			// 
			// txtSearch
			// 
			this->txtSearch->Location = System::Drawing::Point(400, 643);
			this->txtSearch->Name = L"txtSearch";
			this->txtSearch->Size = System::Drawing::Size(200, 20);
			this->txtSearch->TabIndex = 5;
			this->txtSearch->TextChanged += gcnew System::EventHandler(this, &MainForm::txtSearch_TextChanged);
			// 
			// btnClearAuthor
			// 
			this->btnClearAuthor->Location = System::Drawing::Point(623, 500);
			this->btnClearAuthor->Name = L"btnClearAuthor";
			this->btnClearAuthor->Size = System::Drawing::Size(75, 23);
			this->btnClearAuthor->TabIndex = 8;
			this->btnClearAuthor->Text = L"Clear";
			this->btnClearAuthor->Click += gcnew System::EventHandler(this, &MainForm::btnClearAuthor_Click);
			// 
			// MainForm
			// 
			this->ClientSize = System::Drawing::Size(920, 693);

			this->Controls->Add(this->button1);
			this->Controls->Add(this->btnClearAuthor);
			this->Controls->Add(this->txtFirstName);
			this->Controls->Add(this->btnSaveHDD);
			this->Controls->Add(this->txtLastName);
			this->Controls->Add(this->txtSearch);
			this->Controls->Add(this->btnSetAuthor);
			this->Controls->Add(this->listViewEntries);
			this->Controls->Add(this->btnNew);
			this->Controls->Add(this->btnEdit);
			this->Controls->Add(this->btnDelete);
			this->Controls->Add(this->btnSave);
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->panelDetails);
			this->Controls->Add(this->lblLastName);
			this->Controls->Add(this->lblFirstName);
			this->Name = L"MainForm";
			this->Text = L"BibTexPro";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->panelDetails->ResumeLayout(false);
			this->panelDetails->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		void UpdateUIState(bool inEditMode) {
			isEditMode = inEditMode;
			cmbType->Enabled = inEditMode;
			btnSave->Visible = inEditMode;
			btnCancel->Visible = inEditMode;
			btnNew->Enabled = !inEditMode;
			btnEdit->Enabled = !inEditMode && listViewEntries->SelectedItems->Count > 0;
			btnDelete->Enabled = !inEditMode && listViewEntries->SelectedItems->Count > 0;

			SetFieldsReadOnly(!inEditMode);
			txtAuthor->ReadOnly = true;


		}

		void RefreshListView() {
			listViewEntries->Items->Clear();
			for each (DataArray^ entry in entries) {
				String^ itemText = entry->keyword;
				listViewEntries->Items->Add(gcnew ListViewItem(itemText));
				//Console::WriteLine("Added: {0}", itemText);
			}
		}

		void SaveEntries(String^ filename) {
			using namespace System::IO;
			using namespace System::Runtime::Serialization::Formatters::Binary;
			FileStream^ fs = gcnew FileStream(filename, FileMode::Create, FileAccess::Write);
			BinaryFormatter^ formatter = gcnew BinaryFormatter();

			try {
				// Serialize the entries to the file stream
				formatter->Serialize(fs, entries);
			}
			catch (Exception^ ex) {
				MessageBox::Show("Error saving entries: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			} //Fehlermeldung wenn speichern nicht erfolgreich
			finally{
				fs->Close();
			}
		}


		void LoadEntries(String^ filename) {
			using namespace System::IO;
			using namespace System::Runtime::Serialization::Formatters::Binary;
			if (File::Exists(filename)) {
				FileStream^ fs = gcnew FileStream(filename, FileMode::Open, FileAccess::Read);
				BinaryFormatter^ formatter = gcnew BinaryFormatter();

				try {
					// Deserialize the file stream into the entries list
					entries = (List<DataArray^>^)formatter->Deserialize(fs);
				}
				catch (Exception^ ex) {
					MessageBox::Show("Error loading entries: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				finally{
					fs->Close();
				}
			}
			else {
				MessageBox::Show("No entries file found. Starting with an empty list.", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
				entries = gcnew List<DataArray^>(); // Initialize if file does not exist
			}
		}

		// Event handler for ListView selection change
		void listViewEntries_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
			if (listViewEntries->SelectedIndices->Count > 0 && !isEditMode) {
				int index = listViewEntries->SelectedIndices[0];
				currentEntry = entries[index];
				DisplayEntryDetails(currentEntry);
				btnEdit->Enabled = true;
				btnDelete->Enabled = true;
			}
			else {
				btnEdit->Enabled = false;
				btnDelete->Enabled = false;
			}
		}

		
		
		// Event handler for Delete button click
		void btnDelete_Click(System::Object^ sender, System::EventArgs^ e) {
			if (listViewEntries->SelectedIndices->Count > 0) {
				int index = listViewEntries->SelectedIndices[0];
				entries->RemoveAt(index);
				RefreshListView();
				ClearEntryDetails();
			}
		}

		void PerformSearch(String^ searchTerm) {
			listViewEntries->Items->Clear(); // Clear existing entries
			displayedEntryIndices->Clear(); // Clear previous indices

			for (int i = 0; i < entries->Count; i++) {
				DataArray^ entry = entries[i];
				if ((entry->keyword->IndexOf(searchTerm, StringComparison::CurrentCultureIgnoreCase) >= 0) ||
					(entry->title->IndexOf(searchTerm, StringComparison::CurrentCultureIgnoreCase) >= 0) ||
					(entry->author->IndexOf(searchTerm, StringComparison::CurrentCultureIgnoreCase) >= 0)) {

					// If a match is found, add to the ListView
					String^ itemText = entry->keyword;
					listViewEntries->Items->Add(gcnew ListViewItem(itemText));

					// Store the original index for the displayed entry
					displayedEntryIndices->Add(i);
				}
			}
		}

		// Event handler for ComboBox Type selection change
		void cmbType_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (cmbType->SelectedItem != nullptr)
			{
				String^ selectedType = cmbType->SelectedItem->ToString();
				for each (DataTypeFields^ type in dataTypes)
				{
					if (type->TypeName == selectedType)
					{
						ShowFieldsForType(type);
						break;
					}
				}
			}
			else
			{
				HideAllFields();
			}
		}

		// hide all fields
		void HideAllFields()
		{
			txtKeyword->Visible = false;
			txtAuthor->Visible = false;
			txtTitle->Visible = false;
			txtYear->Visible = false;
			txtJournal->Visible = false;
			txtVolume->Visible = false;
			txtNumber->Visible = false;
			txtPages->Visible = false;
			txtMonth->Visible = false;
			txtNote->Visible = false;
			txtPublisher->Visible = false;
			txtSeries->Visible = false;
			txtAddress->Visible = false;
			txtEdition->Visible = false;
			txtHowpublished->Visible = false;
			txtBooktitle->Visible = false;
			txtEditor->Visible = false;
			txtChapter->Visible = false;
			txtSchool->Visible = false;
			txtInstitution->Visible = false;
			txtOrganization->Visible = false;

			lblKeyword->Visible = false;
			lblAuthor->Visible = false;
			lblTitle->Visible = false;
			lblYear->Visible = false;
			lblJournal->Visible = false;
			lblVolume->Visible = false;
			lblNumber->Visible = false;
			lblPages->Visible = false;
			lblMonth->Visible = false;
			lblNote->Visible = false;
			lblPublisher->Visible = false;
			lblSeries->Visible = false;
			lblAddress->Visible = false;
			lblEdition->Visible = false;
			lblHowpublished->Visible = false;
			lblABooktitle->Visible = false;
			lblEditor->Visible = false;
			lblChapter->Visible = false;
			lblSchool->Visible = false;
			lblInstitution->Visible = false;
			lblOrganization->Visible = false;
			//TEST
			lblFirstName->Visible = false;
			lblLastName->Visible = false;
			txtFirstName->Visible = false;
			txtLastName->Visible = false;
			btnSetAuthor->Visible = false;
			btnClearAuthor->Visible = false;
			//TEST
		}


		// Function to show fields based on entry type
		void ShowFieldsForType(DataTypeFields^ type)
		{
			// Hide all fields initially
			HideAllFields();



			// Show only the fields relevant to the selected type
			for each (String^ mandatoryField in type -> RequiredFields)
			{
				if (mandatoryField == "keyword") {
					txtKeyword->Visible = true;
					lblKeyword->Visible = true;
				}
				if (mandatoryField == "author") {
					txtAuthor->Visible = true;
					lblAuthor->Visible = true;
					lblFirstName->Visible = true;
					lblLastName->Visible = true;
					txtFirstName->Visible = true;
					txtLastName->Visible = true;
					btnSetAuthor->Visible = true;
					btnClearAuthor->Visible = true;
				}
				if (mandatoryField == "title") {
					txtTitle->Visible = true;
					lblTitle->Visible = true;
				}
				if (mandatoryField == "year") {
					txtYear->Visible = true;
					lblYear->Visible = true;
				}
				if (mandatoryField == "journal") {
					txtJournal->Visible = true;
					lblJournal->Visible = true;
				}
				if (mandatoryField == "volume") {
					txtVolume->Visible = true;
					lblVolume->Visible = true;
				}
				if (mandatoryField == "number") {
					txtNumber->Visible = true;
					lblNumber->Visible = true;
				}
				if (mandatoryField == "pages") {
					txtPages->Visible = true;
					lblPages->Visible = true;
				}
				if (mandatoryField == "month") {
					txtMonth->Visible = true;
					lblMonth->Visible = true;
				}
				if (mandatoryField == "note") {
					txtNote->Visible = true;
					lblNote->Visible = true;
				}
				if (mandatoryField == "publisher") {
					txtPublisher->Visible = true;
					lblPublisher->Visible = true;
				}
				if (mandatoryField == "series") {
					txtSeries->Visible = true;
					lblSeries->Visible = true;
				}
				if (mandatoryField == "address") {
					txtAddress->Visible = true;
					lblAddress->Visible = true;
				}
				if (mandatoryField == "edition") {
					txtEdition->Visible = true;
					lblEdition->Visible = true;
				}
				if (mandatoryField == "howpublished") {
					txtHowpublished->Visible = true;
					lblHowpublished->Visible = true;
				}
				if (mandatoryField == "booktitle") {
					txtBooktitle->Visible = true;
					lblABooktitle->Visible = true;
				}
				if (mandatoryField == "editor") {
					txtEditor->Visible = true;
					lblEditor->Visible = true;
				}
				if (mandatoryField == "chapter") {
					txtChapter->Visible = true;
					lblChapter->Visible = true;
				}
				if (mandatoryField == "school") {
					txtSchool->Visible = true;
					lblSchool->Visible = true;
				}
				if (mandatoryField == "institution") {
					txtInstitution->Visible = true;
					lblInstitution->Visible = true;
				}
				if (mandatoryField == "organization") {
					txtOrganization->Visible = true;
					lblOrganization->Visible = true;
				}

			}

			for each (String^ optionalField in type -> OptionalFields)
			{
				if (optionalField == "keyword") {
					txtKeyword->Visible = true;
					lblKeyword->Visible = true;
				}
				if (optionalField == "author") {
					txtAuthor->Visible = true;
					lblAuthor->Visible = true;
				}
				if (optionalField == "title") {
					txtTitle->Visible = true;
					lblTitle->Visible = true;
				}
				if (optionalField == "year") {
					txtYear->Visible = true;
					lblYear->Visible = true;
				}
				if (optionalField == "journal") {
					txtJournal->Visible = true;
					lblJournal->Visible = true;
				}
				if (optionalField == "volume") {
					txtVolume->Visible = true;
					lblVolume->Visible = true;
				}
				if (optionalField == "number") {
					txtNumber->Visible = true;
					lblNumber->Visible = true;
				}
				if (optionalField == "pages") {
					txtPages->Visible = true;
					lblPages->Visible = true;
				}
				if (optionalField == "month") {
					txtMonth->Visible = true;
					lblMonth->Visible = true;
				}
				if (optionalField == "note") {
					txtNote->Visible = true;
					lblNote->Visible = true;
				}
				if (optionalField == "publisher") {
					txtPublisher->Visible = true;
					lblPublisher->Visible = true;
				}
				if (optionalField == "series") {
					txtSeries->Visible = true;
					lblSeries->Visible = true;
				}
				if (optionalField == "address") {
					txtAddress->Visible = true;
					lblAddress->Visible = true;
				}
				if (optionalField == "edition") {
					txtEdition->Visible = true;
					lblEdition->Visible = true;
				}
				if (optionalField == "howpublished") {
					txtHowpublished->Visible = true;
					lblHowpublished->Visible = true;
				}
				if (optionalField == "booktitle") {
					txtBooktitle->Visible = true;
					lblABooktitle->Visible = true;
				}
				if (optionalField == "editor") {
					txtEditor->Visible = true;
					lblEditor->Visible = true;
				}
				if (optionalField == "chapter") {
					txtChapter->Visible = true;
					lblChapter->Visible = true;
				}
				if (optionalField == "school") {
					txtSchool->Visible = true;
					lblSchool->Visible = true;
				}
				if (optionalField == "institution") {
					txtInstitution->Visible = true;
					lblInstitution->Visible = true;
				}
				if (optionalField == "organization") {
					txtOrganization->Visible = true;
					lblOrganization->Visible = true;
				}
			}

			int mandatoryY = 50;
			int optionalY = 50;
			int xOffsetMandatory = 50;
			int xOffsetOptional = 250;
			int verticalSpacing = 30;

			for each (String^ field in type->RequiredFields) {
				if (field == "keyword") PositionFieldWithLabel(lblKeyword, txtKeyword, mandatoryY, xOffsetMandatory);
				if (field == "author") PositionFieldWithLabel(lblAuthor, txtAuthor, mandatoryY, xOffsetMandatory);
				if (field == "title") PositionFieldWithLabel(lblTitle, txtTitle, mandatoryY, xOffsetMandatory);
				if (field == "year") PositionFieldWithLabel(lblYear, txtYear, mandatoryY, xOffsetMandatory);
				if (field == "journal") PositionFieldWithLabel(lblJournal, txtJournal, mandatoryY, xOffsetMandatory);
				if (field == "volume") PositionFieldWithLabel(lblVolume, txtVolume, mandatoryY, xOffsetMandatory);
				if (field == "number") PositionFieldWithLabel(lblNumber, txtNumber, mandatoryY, xOffsetMandatory);
				if (field == "pages") PositionFieldWithLabel(lblPages, txtPages, mandatoryY, xOffsetMandatory);
				if (field == "month") PositionFieldWithLabel(lblMonth, txtMonth, mandatoryY, xOffsetMandatory);
				if (field == "note") PositionFieldWithLabel(lblNote, txtNote, mandatoryY, xOffsetMandatory);
				if (field == "publisher") PositionFieldWithLabel(lblPublisher, txtPublisher, mandatoryY, xOffsetMandatory);
				if (field == "series") PositionFieldWithLabel(lblSeries, txtSeries, mandatoryY, xOffsetMandatory);
				if (field == "address") PositionFieldWithLabel(lblAddress, txtAddress, mandatoryY, xOffsetMandatory);
				if (field == "edition") PositionFieldWithLabel(lblEdition, txtEdition, mandatoryY, xOffsetMandatory);
				if (field == "howpublished") PositionFieldWithLabel(lblHowpublished, txtHowpublished, mandatoryY, xOffsetMandatory);
				if (field == "booktitle") PositionFieldWithLabel(lblABooktitle, txtBooktitle, mandatoryY, xOffsetMandatory);
				if (field == "editor") PositionFieldWithLabel(lblEditor, txtEditor, mandatoryY, xOffsetMandatory);
				if (field == "chapter") PositionFieldWithLabel(lblChapter, txtChapter, mandatoryY, xOffsetMandatory);
				if (field == "school") PositionFieldWithLabel(lblSchool, txtSchool, mandatoryY, xOffsetMandatory);
				if (field == "institution") PositionFieldWithLabel(lblInstitution, txtInstitution, mandatoryY, xOffsetMandatory);
				if (field == "organization") PositionFieldWithLabel(lblOrganization, txtOrganization, mandatoryY, xOffsetMandatory);
			}

			for each (String^ field in type->OptionalFields) {
				if (field == "keyword") PositionFieldWithLabel(lblKeyword, txtKeyword, optionalY, xOffsetOptional);
				if (field == "author") PositionFieldWithLabel(lblAuthor, txtAuthor, optionalY, xOffsetOptional);
				if (field == "title") PositionFieldWithLabel(lblTitle, txtTitle, optionalY, xOffsetOptional);
				if (field == "year")PositionFieldWithLabel(lblYear, txtYear, optionalY, xOffsetOptional);
				if (field == "journal") PositionFieldWithLabel(lblJournal, txtJournal, optionalY, xOffsetOptional);
				if (field == "volume") PositionFieldWithLabel(lblVolume, txtVolume, optionalY, xOffsetOptional);
				if (field == "number") PositionFieldWithLabel(lblNumber, txtNumber, optionalY, xOffsetOptional);
				if (field == "pages") PositionFieldWithLabel(lblPages, txtPages, optionalY, xOffsetOptional);
				if (field == "month") PositionFieldWithLabel(lblMonth, txtMonth, optionalY, xOffsetOptional);
				if (field == "note") PositionFieldWithLabel(lblNote, txtNote, optionalY, xOffsetOptional);
				if (field == "publisher") PositionFieldWithLabel(lblPublisher, txtPublisher, optionalY, xOffsetOptional);
				if (field == "series") PositionFieldWithLabel(lblSeries, txtSeries, optionalY, xOffsetOptional);
				if (field == "address") PositionFieldWithLabel(lblAddress, txtAddress, optionalY, xOffsetOptional);
				if (field == "edition") PositionFieldWithLabel(lblEdition, txtEdition, optionalY, xOffsetOptional);
				if (field == "howpublished") PositionFieldWithLabel(lblHowpublished, txtHowpublished, optionalY, xOffsetOptional);
				if (field == "booktitle") PositionFieldWithLabel(lblABooktitle, txtBooktitle, optionalY, xOffsetOptional);
				if (field == "editor") PositionFieldWithLabel(lblEditor, txtEditor, optionalY, xOffsetOptional);
				if (field == "chapter") PositionFieldWithLabel(lblChapter, txtChapter, optionalY, xOffsetOptional);
				if (field == "school") PositionFieldWithLabel(lblSchool, txtSchool, optionalY, xOffsetOptional);
				if (field == "institution") PositionFieldWithLabel(lblInstitution, txtInstitution, optionalY, xOffsetOptional);
				if (field == "organization") PositionFieldWithLabel(lblOrganization, txtOrganization, optionalY, xOffsetOptional);
			}
			
		}



		void PositionFieldWithLabel(Label^ label, TextBox^ field, int% yOffset, int xOffset) {
			if (field->Visible) {
				label->Location = Point(xOffset, yOffset);
				field->Location = Point(xOffset, yOffset + 20);
				yOffset += 50;
			}
		}

	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {

		LoadEntries("entries.bin"); // Load entries from a specified file
		RefreshListView(); // Refresh the ListView to show loaded entries
	}

	private: System::Void btnSaveHDD_Click(System::Object^  sender, System::EventArgs^  e) {
		SaveEntries("entries.bin");
		MessageBox::Show("Entries saved successfully to HDD.", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	private: System::Void txtSearch_TextChanged(System::Object^  sender, System::EventArgs^  e) { //wird automatisch durchsucht wenn etwas eingegeben wird
		String^ searchTerm = txtSearch->Text->Trim();
		PerformSearch(searchTerm);
	
	}
	private: System::Void btnSetAuthor_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ firstName = txtFirstName->Text->Trim();
		String^ lastName = txtLastName->Text->Trim();

		if (firstName->Length > 0 && lastName->Length > 0) {
			// Combine last name and first name
			txtAuthor->Text += (txtAuthor->Text->Length > 0 ? " and " : "") + lastName + ", " + firstName;
			txtFirstName->Clear();
			txtLastName->Clear();
		}
		else {
			MessageBox::Show("Please enter both first name and last name.", "Input Error",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
	private: System::Void btnClearAuthor_Click(System::Object^  sender, System::EventArgs^  e) {
		txtAuthor->Clear(); // Clears the author field
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		int n;
		n = 0;
		int size = entries->Count;

		MessageBox::Show("Die Größe des Arrays beträgt: " + size.ToString());

		FILE* Quelle;
		Quelle = fopen("Quelle.bib", "w");

		while (n < size)
		{

			fprintf(Quelle, "@%s{%s", entries[n]->type, entries[n]->keyword);
			if (entries[n]->title != "") { fprintf(Quelle, ",\ntitle = {{%s}}", entries[n]->title); }
			if (entries[n]->journal != "") { fprintf(Quelle, ",\njournal = {%s}", entries[n]->journal); }
			if (entries[n]->year != "") { fprintf(Quelle, ",\nyear = {%s}", entries[n]->year); }
			if (entries[n]->author != "") { fprintf(Quelle, ",\nauthor = {%s}", entries[n]->author); }
			if (entries[n]->volume != "") { fprintf(Quelle, ",\nvolume = {%s}", entries[n]->volume); }
			if (entries[n]->number != "") { fprintf(Quelle, ",\nnumber = {%s}", entries[n]->number); }
			if (entries[n]->pages != "") { fprintf(Quelle, ",\npages = {%s}", entries[n]->pages); }
			if (entries[n]->month != "") { fprintf(Quelle, ",\nmonth = {%s}", entries[n]->month); }
			if (entries[n]->note != "") { fprintf(Quelle, ",\nnote = {%s}", entries[n]->note); }
			if (entries[n]->publisher != "") { fprintf(Quelle, ",\npublisher = {%s}", entries[n]->publisher); }
			if (entries[n]->series != "") { fprintf(Quelle, ",\nseries = {%s}", entries[n]->series); }
			if (entries[n]->address != "") { fprintf(Quelle, ",\naddress = {%s}", entries[n]->address); }
			if (entries[n]->edition != "") { fprintf(Quelle, ",\nedition = {%s}", entries[n]->edition); }
			if (entries[n]->howpublished != "") { fprintf(Quelle, ",\nhowpublished = {%s}", entries[n]->howpublished); }
			if (entries[n]->booktitle != "") { fprintf(Quelle, ",\nbooktitle = {%s}", entries[n]->booktitle); }
			if (entries[n]->editor != "") { fprintf(Quelle, ",\neditor = {%s}", entries[n]->editor); }
			if (entries[n]->chapter != "") { fprintf(Quelle, ",\nchapter = {%s}", entries[n]->chapter); }
			if (entries[n]->school != "") { fprintf(Quelle, ",\nschool = {%s}", entries[n]->school); }
			if (entries[n]->institution != "") { fprintf(Quelle, ",\ninstitution = {%s}", entries[n]->institution); }
			if (entries[n]->organization != "") { fprintf(Quelle, ",\norganization = {%s}", entries[n]->organization); }

			fprintf(Quelle, "\n}\n\n");

			n++;

		}
		fclose(Quelle);

	}
};
}
