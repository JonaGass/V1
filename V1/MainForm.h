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

	public ref class MainForm : public System::Windows::Forms::Form {
	public:
		MainForm(void) {

			// Start the splash screen in a separate thread
			Thread^ t = gcnew Thread(gcnew ThreadStart(this, &MainForm::StartForm));
			t->SetApartmentState(ApartmentState::STA);
			t->Start();
			t->Join(); // Wait for the SplashScreen thread to finish

			InitializeComponent();

			System::Reflection::Assembly^ assembly = System::Reflection::Assembly::GetExecutingAssembly();
			System::IO::Stream^ iconStream = assembly->GetManifestResourceStream("Icon.ico");

			this->Icon = gcnew System::Drawing::Icon(iconStream);

			sprache_aendern();
			this->StartPosition = FormStartPosition::CenterScreen;
			/*this->BringToFront();
			this->Activate();*/
			InitializeDataTypes();
			PopulateTypeDropdown();
			entries = gcnew List<DataArray^>();
			displayedEntryIndices = gcnew List<int>();
			HideAllFields();
			UpdateUIState(false);

			// Ensure MainForm is shown and brought to the foreground
			/*this->Shown += gcnew EventHandler(this, &MainForm::OnShown);*/

		}
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	public:
	private: System::Windows::Forms::ToolStripButton^  toolStripSplitButton1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton2;

	public:

	public:



	private:
		array<String^, 2>^ nachrichten; //meinis

	protected:
		~MainForm() {
			if (components) {
				delete components;
			}
		}


		/*private:
			void OnShown(System::Object^ sender, System::EventArgs^ e) {
				this->BringToFront();
				this->Activate();
			}*/
	public:
		void StartForm() {
			V1::SplashScreen^ form = gcnew V1::SplashScreen();
			form->ShowDialog();
		}

	private:
		List<int>^ displayedEntryIndices; // To store the indices of displayed entries after searching
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



		List<DataArray^>^ entries;
		DataArray^ currentEntry;
		array<DataTypeFields^>^ dataTypes;
	private: System::Windows::Forms::Button^  btnSaveHDD;
	private: System::Windows::Forms::Button^  btnClearAuthor;
	private: System::Windows::Forms::RadioButton^  rbtnAuthor;
	private: System::Windows::Forms::RadioButton^  rbtnEditor;
			 bool isEditMode;
	private: System::Windows::Forms::Button^  btnLanguage;
	private: System::Windows::Forms::Button^  btnPDF;
	private: System::Windows::Forms::Button^  btnDark;


			 //mein
	private: System::Windows::Forms::ListView^ listViewAuthors;
			 //mein

			 void InitializeDataTypes() {
				 dataTypes = GetDataTypes();
			 }


			 //Function to initialize the type dropdown with entry types
			 void PopulateTypeDropdown()
			 {
				 for each (DataTypeFields ^ type in dataTypes)
				 {
					 cmbType->Items->Add(type->TypeName);
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


				 //mein
				 listViewAuthors->Items->Clear();

				 if (entry->author != nullptr)
				 {
					 array<String^>^ authors = entry->author->Split(gcnew array<String^>{ " and " }, StringSplitOptions::None);
					 for each (String^ author in authors)
					 {
						 listViewAuthors->Items->Add(author->Trim());
					 }
				 }

				 if (entry->editor != nullptr)
				 {
					 array<String^>^ editors = entry->editor->Split(gcnew array<String^>{ " and " }, StringSplitOptions::None);
					 for each (String^ editor in editors)
					 {
						 listViewAuthors->Items->Add(editor->Trim());
					 }
				 }


				 //mein


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
				 rbtnAuthor->Visible = !readOnly;
				 rbtnEditor->Visible = !readOnly;
				 lblFirstName->Visible = !readOnly;
				 lblLastName->Visible = !readOnly;
				 txtFirstName->Visible = !readOnly;
				 txtLastName->Visible = !readOnly;
				 btnSetAuthor->Visible = !readOnly;
				 btnClearAuthor->Visible = !readOnly;
			 }

			 // Event handler for new entry button click
			 void btnNew_Click(System::Object^ sender, System::EventArgs^ e) {
				 listViewAuthors->Items->Clear();
				 ClearEntryDetails();
				 currentEntry = gcnew DataArray();
				 UpdateUIState(true);
			 }

			 // Event handler for edit button click
			 void btnEdit_Click(System::Object^ sender, System::EventArgs^ e) {
				 if (listViewEntries->SelectedIndices->Count > 0) {
					 listViewAuthors->Items->Clear();
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

					 // Clear existing entries to avoid overwriting
					 currentEntry->keyword = "";
					 currentEntry->author = "";
					 currentEntry->title = "";
					 currentEntry->year = "";
					 currentEntry->journal = "";
					 currentEntry->volume = "";
					 currentEntry->number = "";
					 currentEntry->pages = "";
					 currentEntry->month = "";
					 currentEntry->note = "";
					 currentEntry->publisher = "";
					 currentEntry->series = "";
					 currentEntry->address = "";
					 currentEntry->edition = "";
					 currentEntry->howpublished = "";
					 currentEntry->booktitle = "";
					 currentEntry->editor = "";
					 currentEntry->chapter = "";
					 currentEntry->school = "";
					 currentEntry->institution = "";
					 currentEntry->organization = "";

					 // Get the selected type
					 String^ selectedType = cmbType->SelectedItem->ToString();
					 DataTypeFields^ selectedTypeFields = nullptr;

					 // Find the selected type in the dataTypes array
					 for each (DataTypeFields^ type in dataTypes) {
						 if (type->TypeName == selectedType) {
							 selectedTypeFields = type;
							 break;
						 }
					 }

					 if (selectedTypeFields != nullptr) {
						 // Assign values for required fields
						 for each (String^ field in selectedTypeFields->RequiredFields) {
							 if (field == "keyword") currentEntry->keyword = txtKeyword->Text;
							 if (field == "author") currentEntry->author = txtAuthor->Text;
							 if (field == "title") currentEntry->title = txtTitle->Text;
							 if (field == "year") currentEntry->year = txtYear->Text;
							 if (field == "journal") currentEntry->journal = txtJournal->Text;
							 if (field == "volume") currentEntry->volume = txtVolume->Text;
							 if (field == "number") currentEntry->number = txtNumber->Text;
							 if (field == "pages") currentEntry->pages = txtPages->Text;
							 if (field == "month") currentEntry->month = txtMonth->Text;
							 if (field == "note") currentEntry->note = txtNote->Text;
							 if (field == "publisher") currentEntry->publisher = txtPublisher->Text;
							 if (field == "series") currentEntry->series = txtSeries->Text;
							 if (field == "address") currentEntry->address = txtAddress->Text;
							 if (field == "edition") currentEntry->edition = txtEdition->Text;
							 if (field == "howpublished") currentEntry->howpublished = txtHowpublished->Text;
							 if (field == "booktitle") currentEntry->booktitle = txtBooktitle->Text;
							 if (field == "editor") currentEntry->editor = txtEditor->Text;
							 if (field == "chapter") currentEntry->chapter = txtChapter->Text;
							 if (field == "school") currentEntry->school = txtSchool->Text;
							 if (field == "institution") currentEntry->institution = txtInstitution->Text;
							 if (field == "organization") currentEntry->organization = txtOrganization->Text;
						 }

						 // Assign values for optional fields
						 for each (String^ field in selectedTypeFields->OptionalFields) {
							 if (field == "keyword" && currentEntry->keyword->Trim() == String::Empty) currentEntry->keyword = txtKeyword->Text;
							 if (field == "author" && currentEntry->author->Trim() == String::Empty) currentEntry->author = txtAuthor->Text;
							 if (field == "title" && currentEntry->title->Trim() == String::Empty) currentEntry->title = txtTitle->Text;
							 if (field == "year" && currentEntry->year->Trim() == String::Empty) currentEntry->year = txtYear->Text;
							 if (field == "journal" && currentEntry->journal->Trim() == String::Empty) currentEntry->journal = txtJournal->Text;
							 if (field == "volume" && currentEntry->volume->Trim() == String::Empty) currentEntry->volume = txtVolume->Text;
							 if (field == "number" && currentEntry->number->Trim() == String::Empty) currentEntry->number = txtNumber->Text;
							 if (field == "pages" && currentEntry->pages->Trim() == String::Empty) currentEntry->pages = txtPages->Text;
							 if (field == "month" && currentEntry->month->Trim() == String::Empty) currentEntry->month = txtMonth->Text;
							 if (field == "note" && currentEntry->note->Trim() == String::Empty) currentEntry->note = txtNote->Text;
							 if (field == "publisher" && currentEntry->publisher->Trim() == String::Empty) currentEntry->publisher = txtPublisher->Text;
							 if (field == "series" && currentEntry->series->Trim() == String::Empty) currentEntry->series = txtSeries->Text;
							 if (field == "address" && currentEntry->address->Trim() == String::Empty) currentEntry->address = txtAddress->Text;
							 if (field == "edition" && currentEntry->edition->Trim() == String::Empty) currentEntry->edition = txtEdition->Text;
							 if (field == "howpublished" && currentEntry->howpublished->Trim() == String::Empty) currentEntry->howpublished = txtHowpublished->Text;
							 if (field == "booktitle" && currentEntry->booktitle->Trim() == String::Empty) currentEntry->booktitle = txtBooktitle->Text;
							 if (field == "editor" && currentEntry->editor->Trim() == String::Empty) currentEntry->editor = txtEditor->Text;
							 if (field == "chapter" && currentEntry->chapter->Trim() == String::Empty) currentEntry->chapter = txtChapter->Text;
							 if (field == "school" && currentEntry->school->Trim() == String::Empty) currentEntry->school = txtSchool->Text;
							 if (field == "institution" && currentEntry->institution->Trim() == String::Empty) currentEntry->institution = txtInstitution->Text;
							 if (field == "organization" && currentEntry->organization->Trim() == String::Empty) currentEntry->organization = txtOrganization->Text;
						 }

						 // Add or update the entry in the list
						 if (entries->IndexOf(currentEntry) == -1) {
							 entries->Add(currentEntry);
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
					 if (en_de == 0) {
						 MessageBox::Show(nachrichten[0, 0]);
					 }
					 else if (en_de == 1) {
						 MessageBox::Show(nachrichten[0, 1]);
					 }
					 //MessageBox::Show("Please select an entry type.");
					 stateMandatory = false;
				 }
				 else {
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
						 if (en_de == 0) {
							 MessageBox::Show(nachrichten[1, 0]);
						 }
						 else if (en_de == 1) {
							 MessageBox::Show(nachrichten[1, 1]);
						 }
						 //MessageBox::Show("Invalid entry type selected.");
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
							 if (en_de == 0) {
								 errorMessage += nachrichten[2, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[2, 1];
							 }
							 //errorMessage += "Please fill in the keyword field.\n";
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
							 if (en_de == 0) {
								 errorMessage += nachrichten[3, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[3, 1];
							 }
							 //errorMessage += "Please fill in the title field.\n";
							 stateMandatory = false;
						 }
						 int year;
						 if ((field == "year" && txtYear->Text->Trim() == String::Empty) || (field == "year" && !Int32::TryParse(txtYear->Text, year))) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[4, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[4, 1];
							 }
							 //errorMessage += "Please enter a number into the year field.\n";
							 stateMandatory = false;
						 }
						 if (field == "journal" && txtJournal->Text->Trim() == String::Empty) {
							 //errorMessage += "Please fill in the journal field.\n";
							 stateMandatory = false;
						 }
						 int volume;
						 if ((field == "volume" && txtVolume->Text->Trim() == String::Empty) || (field == "volume" && !Int32::TryParse(txtVolume->Text, volume))) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[5, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[5, 1];
							 }
							 //errorMessage += "Please enter a number into the volume field.\n";
							 stateMandatory = false;
						 }
						 int number;
						 if ((field == "number" && txtNumber->Text->Trim() == String::Empty) || (field == "number" && !Int32::TryParse(txtNumber->Text, number))) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[6, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[6, 1];
							 }
							 //errorMessage += "Please enter a number into the number field.\n";
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
								 if (en_de == 0) {
									 errorMessage += nachrichten[7, 0];
								 }
								 else if (en_de == 1) {
									 errorMessage += nachrichten[7, 1];
								 }
								 //errorMessage += "Please enter a number into the pages field.\n";
							 }
							 else {
								 hasPages = true; // Pages is present
							 }
						 }
						 if (field == "month" && txtMonth->Text->Trim() == String::Empty) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[8, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[8, 1];
							 }
							 //errorMessage += "Please fill in the month field.\n";
							 stateMandatory = false;
						 }
						 if (field == "note" && txtNote->Text->Trim() == String::Empty) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[9, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[9, 1];
							 }
							 //errorMessage += "Please fill in the note field.\n";
							 stateMandatory = false;
						 }
						 if (field == "publisher" && txtPublisher->Text->Trim() == String::Empty) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[10, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[10, 1];
							 }
							 //errorMessage += "Please fill in the publisher field.\n";
							 stateMandatory = false;
						 }
						 if (field == "series" && txtSeries->Text->Trim() == String::Empty) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[11, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[11, 1];
							 }
							 //errorMessage += "Please fill in the series field.\n";
							 stateMandatory = false;
						 }
						 if (field == "address" && txtAddress->Text->Trim() == String::Empty) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[12, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[12, 1];
							 }
							 //errorMessage += "Please fill in the address field.\n";
							 stateMandatory = false;
						 }
						 if (field == "edition" && txtEdition->Text->Trim() == String::Empty) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[13, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[13, 1];
							 }
							 //errorMessage += "Please fill in the edition field.\n";
							 stateMandatory = false;
						 }
						 if (field == "howpublished" && txtHowpublished->Text->Trim() == String::Empty) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[14, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[14, 1];
							 }
							 //errorMessage += "Please fill in the how published field.\n";
							 stateMandatory = false;
						 }
						 if (field == "booktitle" && txtBooktitle->Text->Trim() == String::Empty) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[15, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[15, 1];
							 }
							 //errorMessage += "Please fill in the book title field.\n";
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
							 if (en_de == 0) {
								 errorMessage += nachrichten[16, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[16, 1];
							 }
							 //errorMessage += "Please fill in the school field.\n";
							 stateMandatory = false;
						 }
						 if (field == "institution" && txtInstitution->Text->Trim() == String::Empty) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[17, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[17, 1];
							 }
							 //errorMessage += "Please fill in the institution field.\n";
							 stateMandatory = false;
						 }
						 if (field == "organization" && txtOrganization->Text->Trim() == String::Empty) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[18, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[18, 1];
							 }
							 //errorMessage += "Please fill in the organization field.\n";
							 stateMandatory = false;
						 }
					 }

					 // Check if either author or editor is filled if both are mandatory
					 if (AuthorMandatory && EditorMandatory)
					 {
						 if (!hasAuthor && !hasEditor) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[19, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[19, 1];
							 }
							 //errorMessage += "Please fill in either the author or the editor field.\n";
							 stateMandatory = false;
						 }
						 else if (hasAuthor && hasEditor) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[20, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[20, 1];
							 }
							 //errorMessage += "Cannot have both Author and Editor!\n";
							 stateMandatory = false;
						 }
					 }
					 else if (AuthorMandatory) {
						 if (!hasAuthor) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[21, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[21, 1];
							 }
							 //errorMessage += "Please fill in the author field.\n";
							 stateMandatory = false;
						 }
					 }
					 else if (EditorMandatory) {
						 if (!hasEditor) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[22, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[22, 1];
							 }
							 //errorMessage += "Please fill in the editor field.\n";
							 stateMandatory = false;
						 }
					 }

					 if (PagesMandatory && ChapterMandatory)
					 {
						 if (!hasPages && !hasChapter) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[23, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[23, 1];
							 }
							 //errorMessage += "Please fill in either the Pages or the Chapter field.\n";
							 stateMandatory = false;
						 }
					 }
					 else if (PagesMandatory) {
						 if (!hasPages) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[24, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[24, 1];
							 }
							 //errorMessage += "Please fill in the Pages field.\n";
							 stateMandatory = false;
						 }
					 }
					 else if (ChapterMandatory) {
						 if (!hasChapter) {
							 if (en_de == 0) {
								 errorMessage += nachrichten[25, 0];
							 }
							 else if (en_de == 1) {
								 errorMessage += nachrichten[25, 1];
							 }
							 //errorMessage += "Please fill in the Chapter field.\n";
							 stateMandatory = false;
						 }
					 }

					 if (!stateMandatory) {
						 MessageBox::Show(errorMessage, nachrichten[42, en_de], MessageBoxButtons::OK, MessageBoxIcon::Warning);
					 }
				 }
				 return stateMandatory;
			 }

			 bool ValidateOptional()
			 {
				 bool stateOptional = true;
				 // Check if an entry type is selected
				 if (cmbType->SelectedIndex == -1)
				 {
					 if (en_de == 0) {
						 MessageBox::Show(nachrichten[26, 0]);
					 }
					 else if (en_de == 1) {
						 MessageBox::Show(nachrichten[26, 1]);
					 }
					 //MessageBox::Show("Please select an entry type.");
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
					 if (en_de == 0) {
						 MessageBox::Show(nachrichten[27, 0]);
					 }
					 else if (en_de == 1) {
						 MessageBox::Show(nachrichten[27, 1]);
					 }
					 //MessageBox::Show("Invalid entry type selected.");
					 return false;
				 }
				 String^ errorMessageOptional = "";
				 // Check each optional field; leave conditions empty
				 for each (String^ field in selectedTypeFields->OptionalFields)
				 {
					 if (field == "keyword") {
						 // zu erg\u00e4nzen
					 }
					 if (field == "author") {
						 // zu erg\u00e4nzen
					 }
					 if (field == "title") {
						 // zu erg\u00e4nzen
					 }
					 int year;
					 if (field == "year" && !Int32::TryParse(txtYear->Text, year) && !(txtYear->Text->Trim() == String::Empty)) {
						 stateOptional = false;
						 if (en_de == 0) {
							 errorMessageOptional += nachrichten[28, 0];
						 }
						 else if (en_de == 1) {
							 errorMessageOptional += nachrichten[28, 1];
						 }
						 //errorMessageOptional += "Year must be a number.\n";
					 }
					 if (field == "journal") {
						 // zu erg\u00e4nzen
					 }
					 int volume;
					 if (field == "volume" && !Int32::TryParse(txtVolume->Text, volume) && !(txtVolume->Text->Trim() == String::Empty)) {
						 stateOptional = false;
						 if (en_de == 0) {
							 errorMessageOptional += nachrichten[29, 0];
						 }
						 else if (en_de == 1) {
							 errorMessageOptional += nachrichten[29, 1];
						 }
						 //errorMessageOptional += "Volume must be a number.\n";
					 }
					 int number;
					 if (field == "number" && !Int32::TryParse(txtNumber->Text, number) && !(txtNumber->Text->Trim() == String::Empty)) {
						 stateOptional = false;
						 if (en_de == 0) {
							 errorMessageOptional += nachrichten[30, 0];
						 }
						 else if (en_de == 1) {
							 errorMessageOptional += nachrichten[30, 1];
						 }
						 //errorMessageOptional += "Number must be a number.\n";
					 }
					 int pages;
					 if (field == "pages" && !Int32::TryParse(txtPages->Text, pages) && !(txtPages->Text->Trim() == String::Empty)) {
						 stateOptional = false;
						 if (en_de == 0) {
							 errorMessageOptional += nachrichten[31, 0];
						 }
						 else if (en_de == 1) {
							 errorMessageOptional += nachrichten[31, 1];
						 }
						 //errorMessageOptional += "Pages must be a number.\n";
					 }
					 if (field == "month") {
						 // zu erg\u00e4nzen
					 }
					 if (field == "note") {
						 // zu erg\u00e4nzen
					 }
					 if (field == "publisher") {
						 // zu erg\u00e4nzen
					 }
					 if (field == "series") {
						 // zu erg\u00e4nzen
					 }
					 if (field == "address") {
						 // zu erg\u00e4nzen
					 }
					 if (field == "edition") {
						 // zu erg\u00e4nzen
					 }
					 if (field == "howpublished") {
						 // zu erg\u00e4nzen
					 }
					 if (field == "booktitle") {
						 // zu erg\u00e4nzen
					 }
					 if (field == "editor") {
						 // zu erg\u00e4nzen
					 }
					 if (field == "chapter") {
						 // zu erg\u00e4nzen
					 }
					 if (field == "school") {
						 // zu erg\u00e4nzen
					 }
					 if (field == "institution") {
						 // zu erg\u00e4nzen
					 }
					 if (field == "organization") {
						 // zu erg\u00e4nzen
					 }
				 }
				 if (!stateOptional) {
					 MessageBox::Show(errorMessageOptional, nachrichten[42,en_de] , MessageBoxButtons::OK, MessageBoxIcon::Warning);
				 }
				 return stateOptional;
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
				 this->rbtnEditor = (gcnew System::Windows::Forms::RadioButton());
				 this->rbtnAuthor = (gcnew System::Windows::Forms::RadioButton());
				 this->btnClearAuthor = (gcnew System::Windows::Forms::Button());
				 this->lblLastName = (gcnew System::Windows::Forms::Label());
				 this->lblFirstName = (gcnew System::Windows::Forms::Label());
				 this->btnSave = (gcnew System::Windows::Forms::Button());
				 this->btnCancel = (gcnew System::Windows::Forms::Button());
				 this->btnSaveHDD = (gcnew System::Windows::Forms::Button());
				 this->txtSearch = (gcnew System::Windows::Forms::TextBox());
				 this->listViewAuthors = (gcnew System::Windows::Forms::ListView());
				 this->btnLanguage = (gcnew System::Windows::Forms::Button());
				 this->btnPDF = (gcnew System::Windows::Forms::Button());
				 this->btnDark = (gcnew System::Windows::Forms::Button());
				 this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
				 this->toolStripSplitButton1 = (gcnew System::Windows::Forms::ToolStripButton());
				 this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
				 this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
				 this->panelDetails->SuspendLayout();
				 this->toolStrip1->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // txtFirstName
				 // 
				 this->txtFirstName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->txtFirstName->Location = System::Drawing::Point(680, 702);
				 this->txtFirstName->Name = L"txtFirstName";
				 this->txtFirstName->Size = System::Drawing::Size(100, 21);
				 this->txtFirstName->TabIndex = 30;
				 // 
				 // txtLastName
				 // 
				 this->txtLastName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->txtLastName->Location = System::Drawing::Point(790, 702);
				 this->txtLastName->Name = L"txtLastName";
				 this->txtLastName->Size = System::Drawing::Size(100, 21);
				 this->txtLastName->TabIndex = 31;
				 // 
				 // btnSetAuthor
				 // 
				 this->btnSetAuthor->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->btnSetAuthor->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnSetAuthor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->btnSetAuthor->Location = System::Drawing::Point(900, 702);
				 this->btnSetAuthor->Name = L"btnSetAuthor";
				 this->btnSetAuthor->Size = System::Drawing::Size(75, 54);
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
				 this->listViewEntries->Size = System::Drawing::Size(300, 545);
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
				 this->btnExportToBib->Location = System::Drawing::Point(79, 682);
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
				 this->btnNew->Location = System::Drawing::Point(475, 43);
				 this->btnNew->Name = L"btnNew";
				 this->btnNew->Size = System::Drawing::Size(96, 28);
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
				 this->btnEdit->Location = System::Drawing::Point(576, 43);
				 this->btnEdit->Name = L"btnEdit";
				 this->btnEdit->Size = System::Drawing::Size(98, 28);
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
				 this->btnDelete->Location = System::Drawing::Point(680, 43);
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
				 this->panelDetails->Size = System::Drawing::Size(736, 545);
				 this->panelDetails->TabIndex = 13;
				 // 
				 // cmbType
				 // 
				 this->cmbType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				 this->cmbType->Location = System::Drawing::Point(200, 30);
				 this->cmbType->Name = L"cmbType";
				 this->cmbType->Size = System::Drawing::Size(200, 26);
				 this->cmbType->TabIndex = 5;
				 this->cmbType->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::cmbType_SelectedIndexChanged);
				 // 
				 // txtKeyword
				 // 
				 this->txtKeyword->Location = System::Drawing::Point(0, 0);
				 this->txtKeyword->Name = L"txtKeyword";
				 this->txtKeyword->Size = System::Drawing::Size(200, 24);
				 this->txtKeyword->TabIndex = 34;
				 this->txtKeyword->TabStop = false;
				 // 
				 // txtAuthor
				 // 
				 this->txtAuthor->Location = System::Drawing::Point(0, 0);
				 this->txtAuthor->Name = L"txtAuthor";
				 this->txtAuthor->Size = System::Drawing::Size(200, 24);
				 this->txtAuthor->TabIndex = 35;
				 // 
				 // txtTitle
				 // 
				 this->txtTitle->Location = System::Drawing::Point(0, 0);
				 this->txtTitle->Name = L"txtTitle";
				 this->txtTitle->Size = System::Drawing::Size(200, 24);
				 this->txtTitle->TabIndex = 37;
				 // 
				 // txtYear
				 // 
				 this->txtYear->Location = System::Drawing::Point(0, 0);
				 this->txtYear->Name = L"txtYear";
				 this->txtYear->Size = System::Drawing::Size(200, 24);
				 this->txtYear->TabIndex = 38;
				 // 
				 // txtJournal
				 // 
				 this->txtJournal->Location = System::Drawing::Point(0, 0);
				 this->txtJournal->Name = L"txtJournal";
				 this->txtJournal->Size = System::Drawing::Size(200, 24);
				 this->txtJournal->TabIndex = 39;
				 // 
				 // txtVolume
				 // 
				 this->txtVolume->Location = System::Drawing::Point(0, 0);
				 this->txtVolume->Name = L"txtVolume";
				 this->txtVolume->Size = System::Drawing::Size(200, 24);
				 this->txtVolume->TabIndex = 40;
				 // 
				 // txtNumber
				 // 
				 this->txtNumber->Location = System::Drawing::Point(0, 0);
				 this->txtNumber->Name = L"txtNumber";
				 this->txtNumber->Size = System::Drawing::Size(200, 24);
				 this->txtNumber->TabIndex = 41;
				 // 
				 // txtPages
				 // 
				 this->txtPages->Location = System::Drawing::Point(0, 0);
				 this->txtPages->Name = L"txtPages";
				 this->txtPages->Size = System::Drawing::Size(200, 24);
				 this->txtPages->TabIndex = 43;
				 // 
				 // txtMonth
				 // 
				 this->txtMonth->Location = System::Drawing::Point(0, 0);
				 this->txtMonth->Name = L"txtMonth";
				 this->txtMonth->Size = System::Drawing::Size(200, 24);
				 this->txtMonth->TabIndex = 44;
				 // 
				 // txtNote
				 // 
				 this->txtNote->Location = System::Drawing::Point(0, 0);
				 this->txtNote->Name = L"txtNote";
				 this->txtNote->Size = System::Drawing::Size(200, 24);
				 this->txtNote->TabIndex = 45;
				 // 
				 // txtPublisher
				 // 
				 this->txtPublisher->Location = System::Drawing::Point(0, 0);
				 this->txtPublisher->Name = L"txtPublisher";
				 this->txtPublisher->Size = System::Drawing::Size(200, 24);
				 this->txtPublisher->TabIndex = 46;
				 // 
				 // txtSeries
				 // 
				 this->txtSeries->Location = System::Drawing::Point(0, 0);
				 this->txtSeries->Name = L"txtSeries";
				 this->txtSeries->Size = System::Drawing::Size(200, 24);
				 this->txtSeries->TabIndex = 47;
				 // 
				 // txtAddress
				 // 
				 this->txtAddress->Location = System::Drawing::Point(0, 0);
				 this->txtAddress->Name = L"txtAddress";
				 this->txtAddress->Size = System::Drawing::Size(200, 24);
				 this->txtAddress->TabIndex = 48;
				 // 
				 // txtEdition
				 // 
				 this->txtEdition->Location = System::Drawing::Point(0, 0);
				 this->txtEdition->Name = L"txtEdition";
				 this->txtEdition->Size = System::Drawing::Size(200, 24);
				 this->txtEdition->TabIndex = 49;
				 // 
				 // txtHowpublished
				 // 
				 this->txtHowpublished->Location = System::Drawing::Point(0, 0);
				 this->txtHowpublished->Name = L"txtHowpublished";
				 this->txtHowpublished->Size = System::Drawing::Size(200, 24);
				 this->txtHowpublished->TabIndex = 50;
				 // 
				 // txtBooktitle
				 // 
				 this->txtBooktitle->Location = System::Drawing::Point(0, 0);
				 this->txtBooktitle->Name = L"txtBooktitle";
				 this->txtBooktitle->Size = System::Drawing::Size(200, 24);
				 this->txtBooktitle->TabIndex = 51;
				 // 
				 // txtEditor
				 // 
				 this->txtEditor->Location = System::Drawing::Point(0, 0);
				 this->txtEditor->Name = L"txtEditor";
				 this->txtEditor->Size = System::Drawing::Size(200, 24);
				 this->txtEditor->TabIndex = 52;
				 // 
				 // txtChapter
				 // 
				 this->txtChapter->Location = System::Drawing::Point(0, 0);
				 this->txtChapter->Name = L"txtChapter";
				 this->txtChapter->Size = System::Drawing::Size(200, 24);
				 this->txtChapter->TabIndex = 53;
				 // 
				 // txtSchool
				 // 
				 this->txtSchool->Location = System::Drawing::Point(0, 0);
				 this->txtSchool->Name = L"txtSchool";
				 this->txtSchool->Size = System::Drawing::Size(200, 24);
				 this->txtSchool->TabIndex = 54;
				 // 
				 // txtInstitution
				 // 
				 this->txtInstitution->Location = System::Drawing::Point(0, 0);
				 this->txtInstitution->Name = L"txtInstitution";
				 this->txtInstitution->Size = System::Drawing::Size(200, 24);
				 this->txtInstitution->TabIndex = 55;
				 // 
				 // txtOrganization
				 // 
				 this->txtOrganization->Location = System::Drawing::Point(0, 0);
				 this->txtOrganization->Name = L"txtOrganization";
				 this->txtOrganization->Size = System::Drawing::Size(200, 24);
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
				 // rbtnEditor
				 // 
				 this->rbtnEditor->AutoSize = true;
				 this->rbtnEditor->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->rbtnEditor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->rbtnEditor->Location = System::Drawing::Point(538, 710);
				 this->rbtnEditor->Name = L"rbtnEditor";
				 this->rbtnEditor->Size = System::Drawing::Size(14, 13);
				 this->rbtnEditor->TabIndex = 32;
				 this->rbtnEditor->UseVisualStyleBackColor = true;
				 this->rbtnEditor->CheckedChanged += gcnew System::EventHandler(this, &MainForm::rbtnEditor_CheckedChanged);
				 // 
				 // rbtnAuthor
				 // 
				 this->rbtnAuthor->AutoSize = true;
				 this->rbtnAuthor->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->rbtnAuthor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->rbtnAuthor->Location = System::Drawing::Point(538, 687);
				 this->rbtnAuthor->Name = L"rbtnAuthor";
				 this->rbtnAuthor->Size = System::Drawing::Size(14, 13);
				 this->rbtnAuthor->TabIndex = 33;
				 this->rbtnAuthor->UseVisualStyleBackColor = true;
				 this->rbtnAuthor->CheckedChanged += gcnew System::EventHandler(this, &MainForm::rbtnAuthor_CheckedChanged);
				 // 
				 // btnClearAuthor
				 // 
				 this->btnClearAuthor->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->btnClearAuthor->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnClearAuthor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->btnClearAuthor->Location = System::Drawing::Point(981, 702);
				 this->btnClearAuthor->Name = L"btnClearAuthor";
				 this->btnClearAuthor->Size = System::Drawing::Size(92, 54);
				 this->btnClearAuthor->TabIndex = 36;
				 this->btnClearAuthor->Click += gcnew System::EventHandler(this, &MainForm::btnClearAuthor_Click);
				 // 
				 // lblLastName
				 // 
				 this->lblLastName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->lblLastName->Location = System::Drawing::Point(790, 682);
				 this->lblLastName->Name = L"lblLastName";
				 this->lblLastName->Size = System::Drawing::Size(100, 23);
				 this->lblLastName->TabIndex = 78;
				 // 
				 // lblFirstName
				 // 
				 this->lblFirstName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.999999F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->lblFirstName->Location = System::Drawing::Point(680, 682);
				 this->lblFirstName->Name = L"lblFirstName";
				 this->lblFirstName->Size = System::Drawing::Size(100, 23);
				 this->lblFirstName->TabIndex = 79;
				 // 
				 // btnSave
				 // 
				 this->btnSave->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->btnSave->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnSave->Location = System::Drawing::Point(439, 773);
				 this->btnSave->Name = L"btnSave";
				 this->btnSave->Size = System::Drawing::Size(132, 28);
				 this->btnSave->TabIndex = 11;
				 this->btnSave->Click += gcnew System::EventHandler(this, &MainForm::btnSave_Click);
				 // 
				 // btnCancel
				 // 
				 this->btnCancel->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnCancel->Location = System::Drawing::Point(576, 773);
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
				 this->btnSaveHDD->Location = System::Drawing::Point(79, 642);
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
				 this->txtSearch->Size = System::Drawing::Size(300, 27);
				 this->txtSearch->TabIndex = 1;
				 this->txtSearch->TextChanged += gcnew System::EventHandler(this, &MainForm::txtSearch_TextChanged);
				 // 
				 // listViewAuthors
				 // 
				 this->listViewAuthors->FullRowSelect = true;
				 this->listViewAuthors->HideSelection = false;
				 this->listViewAuthors->LabelWrap = false;
				 this->listViewAuthors->Location = System::Drawing::Point(321, 656);
				 this->listViewAuthors->MultiSelect = false;
				 this->listViewAuthors->Name = L"listViewAuthors";
				 this->listViewAuthors->Size = System::Drawing::Size(200, 100);
				 this->listViewAuthors->TabIndex = 0;
				 this->listViewAuthors->TabStop = false;
				 this->listViewAuthors->UseCompatibleStateImageBehavior = false;
				 this->listViewAuthors->View = System::Windows::Forms::View::List;
				 this->listViewAuthors->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::listViewAuthors_SelectedIndexChanged);
				 // 
				 // btnLanguage
				 // 
				 this->btnLanguage->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->btnLanguage->Location = System::Drawing::Point(805, 41);
				 this->btnLanguage->Name = L"btnLanguage";
				 this->btnLanguage->Size = System::Drawing::Size(127, 28);
				 this->btnLanguage->TabIndex = 6;
				 this->btnLanguage->UseVisualStyleBackColor = true;
				 this->btnLanguage->Click += gcnew System::EventHandler(this, &MainForm::btnLanguage_Click);
				 // 
				 // btnPDF
				 // 
				 this->btnPDF->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->btnPDF->Location = System::Drawing::Point(938, 42);
				 this->btnPDF->Name = L"btnPDF";
				 this->btnPDF->Size = System::Drawing::Size(135, 27);
				 this->btnPDF->TabIndex = 7;
				 this->btnPDF->UseVisualStyleBackColor = true;
				 this->btnPDF->Click += gcnew System::EventHandler(this, &MainForm::btnPDF_Click);
				 // 
				 // btnDark
				 // 
				 this->btnDark->Cursor = System::Windows::Forms::Cursors::NoMove2D;
				 this->btnDark->Location = System::Drawing::Point(354, 48);
				 this->btnDark->Name = L"btnDark";
				 this->btnDark->Size = System::Drawing::Size(95, 23);
				 this->btnDark->TabIndex = 80;
				 this->btnDark->Text = L"Darkmode";
				 this->btnDark->UseVisualStyleBackColor = true;
				 this->btnDark->Click += gcnew System::EventHandler(this, &MainForm::btnDark_Click);
				 // 
				 // toolStrip1
				 // 
				 this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					 this->toolStripSplitButton1,
						 this->toolStripButton1, this->toolStripButton2
				 });
				 this->toolStrip1->Location = System::Drawing::Point(0, 0);
				 this->toolStrip1->Name = L"toolStrip1";
				 this->toolStrip1->Size = System::Drawing::Size(1088, 25);
				 this->toolStrip1->TabIndex = 81;
				 this->toolStrip1->Text = L"toolStrip1";
				 // 
				 // toolStripSplitButton1
				 // 
				 this->toolStripSplitButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				 this->toolStripSplitButton1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripSplitButton1.Image")));
				 this->toolStripSplitButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->toolStripSplitButton1->Name = L"toolStripSplitButton1";
				 this->toolStripSplitButton1->Size = System::Drawing::Size(66, 22);
				 this->toolStripSplitButton1->Text = L"Darkmode";
				 this->toolStripSplitButton1->ToolTipText = L"Darkmode";
				 this->toolStripSplitButton1->Click += gcnew System::EventHandler(this, &MainForm::toolStripSplitButton1_Click);
				 // 
				 // toolStripButton1
				 // 
				 this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				 this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton1.Image")));
				 this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->toolStripButton1->Name = L"toolStripButton1";
				 this->toolStripButton1->Size = System::Drawing::Size(63, 22);
				 this->toolStripButton1->Text = L"Language";
				 // 
				 // toolStripButton2
				 // 
				 this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				 this->toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton2.Image")));
				 this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->toolStripButton2->Name = L"toolStripButton2";
				 this->toolStripButton2->Size = System::Drawing::Size(51, 22);
				 this->toolStripButton2->Text = L"Manual";
				 // 
				 // MainForm
				 // 
				 this->ClientSize = System::Drawing::Size(1088, 854);
				 this->Controls->Add(this->toolStrip1);
				 this->Controls->Add(this->btnDark);
				 this->Controls->Add(this->txtFirstName);
				 this->Controls->Add(this->txtLastName);
				 this->Controls->Add(this->btnPDF);
				 this->Controls->Add(this->rbtnEditor);
				 this->Controls->Add(this->btnLanguage);
				 this->Controls->Add(this->listViewAuthors);
				 this->Controls->Add(this->rbtnAuthor);
				 this->Controls->Add(this->btnExportToBib);
				 this->Controls->Add(this->btnSaveHDD);
				 this->Controls->Add(this->txtSearch);
				 this->Controls->Add(this->btnClearAuthor);
				 this->Controls->Add(this->listViewEntries);
				 this->Controls->Add(this->btnNew);
				 this->Controls->Add(this->btnEdit);
				 this->Controls->Add(this->btnDelete);
				 this->Controls->Add(this->btnSave);
				 this->Controls->Add(this->btnCancel);
				 this->Controls->Add(this->btnSetAuthor);
				 this->Controls->Add(this->panelDetails);
				 this->Controls->Add(this->lblFirstName);
				 this->Controls->Add(this->lblLastName);
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
				 this->toolStrip1->ResumeLayout(false);
				 this->toolStrip1->PerformLayout();
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
				 txtEditor->ReadOnly = true;


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
				 String^ text;
				 try {
					 // Serialize the entries to the file stream
					 formatter->Serialize(fs, entries);
				 }
				 catch (Exception^ ex) {
					 if (en_de == 0) {
						 text = nachrichten[32, 0];
					 }
					 else if (en_de == 1) {
						 text = nachrichten[32, 1];
					 }
					 MessageBox::Show(text + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				 } //Fehlermeldung wenn speichern nicht erfolgreich
				 finally{
					 fs->Close();
				 }
			 }


			 bool LoadEntries(String^ filename) {
				 using namespace System::IO;
				 using namespace System::Runtime::Serialization::Formatters::Binary;
				 FileStream^ fs = nullptr;
				 bool success = false;
				 String^ text;

				 try {
					 if (File::Exists(filename)) {
						 fs = gcnew FileStream(filename, FileMode::Open, FileAccess::Read);
						 BinaryFormatter^ formatter = gcnew BinaryFormatter();
						 // Deserialize the file stream into the entries list
						 entries = (List<DataArray^>^)formatter->Deserialize(fs);
						 success = true; // Wenn das Einlesen erfolgreich ist
					 }
					 else {
						 if (en_de == 0) {
							 text = nachrichten[33, 0];
						 }
						 else if (en_de == 1) {
							 text = nachrichten[33, 1];
						 }
						 MessageBox::Show(text, "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
						 entries = gcnew List<DataArray^>(); // Initialisiere eine leere Liste, wenn die Datei nicht existiert
					 }
				 }
				 catch (Exception^ ex) {
					 if (en_de == 0) {
						 text = nachrichten[34, 0];
					 }
					 else if (en_de == 1) {
						 text = nachrichten[34, 1];
					 }
					 MessageBox::Show(text + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					 success = false; // Bei einer Ausnahme war das Einlesen nicht erfolgreich
				 }
				 finally{
					 if (fs != nullptr) {
						 fs->Close();
					 }
				 }

				 return success; // Gibt den Erfolg oder Misserfolg zur\u00fcck
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
					 /*if (txtAuthor->Text != "" || txtEditor->Text != "") {
						 TypeChanged = true;
					 }*/
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
				 // Author Namensblock ausblenden
				 lblFirstName->Visible = false;
				 lblLastName->Visible = false;
				 txtFirstName->Visible = false;
				 txtLastName->Visible = false;
				 btnSetAuthor->Visible = false;
				 btnClearAuthor->Visible = false;
				 rbtnAuthor->Visible = false;
				 rbtnEditor->Visible = false;
				 listViewAuthors->Visible = false;
				 // Author Namensblock ausblenden
			 }


			 // Function to show fields based on entry type
			 int ShowFieldsForType(DataTypeFields^ type)
			 {
				 // Hide all fields initially
				 HideAllFields();
				 int TabNumber = 10;
				 bool Author = false;
				 bool Editor = false;

				 // Show only the fields relevant to the selected type
				 for each (String^ mandatoryField in type -> RequiredFields)
				 {
					 if (mandatoryField == "keyword") {
						 txtKeyword->Visible = true;
						 lblKeyword->Visible = true;
						 txtKeyword->TabStop = true;
						 txtKeyword->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "author") {
						 Author = true;
						 txtAuthor->TabStop = true;
						 txtAuthor->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "title") {
						 txtTitle->Visible = true;
						 lblTitle->Visible = true;
						 txtTitle->TabStop = true;
						 txtTitle->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "year") {
						 txtYear->Visible = true;
						 lblYear->Visible = true;
						 txtYear->TabStop = true;
						 txtYear->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "journal") {
						 txtJournal->Visible = true;
						 lblJournal->Visible = true;
						 txtJournal->TabStop = true;
						 txtJournal->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "volume") {
						 txtVolume->Visible = true;
						 lblVolume->Visible = true;
						 txtVolume->TabStop = true;
						 txtVolume->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "number") {
						 txtNumber->Visible = true;
						 lblNumber->Visible = true;
						 txtNumber->TabStop = true;
						 txtNumber->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "pages") {
						 txtPages->Visible = true;
						 lblPages->Visible = true;
						 txtPages->TabStop = true;
						 txtPages->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "month") {
						 txtMonth->Visible = true;
						 lblMonth->Visible = true;
						 txtMonth->TabStop = true;
						 txtMonth->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "note") {
						 txtNote->Visible = true;
						 lblNote->Visible = true;
						 txtNote->TabStop = true;
						 txtNote->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "publisher") {
						 txtPublisher->Visible = true;
						 lblPublisher->Visible = true;
						 txtPublisher->TabStop = true;
						 txtPublisher->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "series") {
						 txtSeries->Visible = true;
						 lblSeries->Visible = true;
						 txtSeries->TabStop = true;
						 txtSeries->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "address") {
						 txtAddress->Visible = true;
						 lblAddress->Visible = true;
						 txtAddress->TabStop = true;
						 txtAddress->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "edition") {
						 txtEdition->Visible = true;
						 lblEdition->Visible = true;
						 txtEdition->TabStop = true;
						 txtEdition->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "howpublished") {
						 txtHowpublished->Visible = true;
						 lblHowpublished->Visible = true;
						 txtHowpublished->TabStop = true;
						 txtHowpublished->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "booktitle") {
						 txtBooktitle->Visible = true;
						 lblABooktitle->Visible = true;
						 txtBooktitle->TabStop = true;
						 txtBooktitle->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "editor") {
						 Editor = true;
						 txtEditor->TabStop = true;
						 txtEditor->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "chapter") {
						 txtChapter->Visible = true;
						 lblChapter->Visible = true;
						 txtChapter->TabStop = true;
						 txtChapter->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "school") {
						 txtSchool->Visible = true;
						 lblSchool->Visible = true;
						 txtSchool->TabStop = true;
						 txtSchool->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "institution") {
						 txtInstitution->Visible = true;
						 lblInstitution->Visible = true;
						 txtInstitution->TabStop = true;
						 txtInstitution->TabIndex = TabNumber++;
					 }
					 if (mandatoryField == "organization") {
						 txtOrganization->Visible = true;
						 lblOrganization->Visible = true;
						 txtOrganization->TabStop = true;
						 txtOrganization->TabIndex = TabNumber++;
					 }
				 }




				 for each (String^ optionalField in type -> OptionalFields)
				 {
					 if (optionalField == "keyword") {
						 txtKeyword->Visible = true;
						 lblKeyword->Visible = true;
						 txtKeyword->TabStop = true;
						 txtKeyword->TabIndex = TabNumber++;
					 }
					 if (optionalField == "author") {
						 Author = true;
						 txtAuthor->TabStop = true;
						 txtAuthor->TabIndex = TabNumber++;
					 }
					 if (optionalField == "title") {
						 txtTitle->Visible = true;
						 lblTitle->Visible = true;
						 txtTitle->TabStop = true;
						 txtTitle->TabIndex = TabNumber++;
					 }
					 if (optionalField == "year") {
						 txtYear->Visible = true;
						 lblYear->Visible = true;
						 txtYear->TabStop = true;
						 txtYear->TabIndex = TabNumber++;
					 }
					 if (optionalField == "journal") {
						 txtJournal->Visible = true;
						 lblJournal->Visible = true;
						 txtJournal->TabStop = true;
						 txtJournal->TabIndex = TabNumber++;
					 }
					 if (optionalField == "volume") {
						 txtVolume->Visible = true;
						 lblVolume->Visible = true;
						 txtVolume->TabStop = true;
						 txtVolume->TabIndex = TabNumber++;
					 }
					 if (optionalField == "number") {
						 txtNumber->Visible = true;
						 lblNumber->Visible = true;
						 txtNumber->TabStop = true;
						 txtNumber->TabIndex = TabNumber++;
					 }
					 if (optionalField == "pages") {
						 txtPages->Visible = true;
						 lblPages->Visible = true;
						 txtPages->TabStop = true;
						 txtPages->TabIndex = TabNumber++;
					 }
					 if (optionalField == "month") {
						 txtMonth->Visible = true;
						 lblMonth->Visible = true;
						 txtMonth->TabStop = true;
						 txtMonth->TabIndex = TabNumber++;
					 }
					 if (optionalField == "note") {
						 txtNote->Visible = true;
						 lblNote->Visible = true;
						 txtNote->TabStop = true;
						 txtNote->TabIndex = TabNumber++;
					 }
					 if (optionalField == "publisher") {
						 txtPublisher->Visible = true;
						 lblPublisher->Visible = true;
						 txtPublisher->TabStop = true;
						 txtPublisher->TabIndex = TabNumber++;
					 }
					 if (optionalField == "series") {
						 txtSeries->Visible = true;
						 lblSeries->Visible = true;
						 txtSeries->TabStop = true;
						 txtSeries->TabIndex = TabNumber++;
					 }
					 if (optionalField == "address") {
						 txtAddress->Visible = true;
						 lblAddress->Visible = true;
						 txtAddress->TabStop = true;
						 txtAddress->TabIndex = TabNumber++;
					 }
					 if (optionalField == "edition") {
						 txtEdition->Visible = true;
						 lblEdition->Visible = true;
						 txtEdition->TabStop = true;
						 txtEdition->TabIndex = TabNumber++;
					 }
					 if (optionalField == "howpublished") {
						 txtHowpublished->Visible = true;
						 lblHowpublished->Visible = true;
						 txtHowpublished->TabStop = true;
						 txtHowpublished->TabIndex = TabNumber++;
					 }
					 if (optionalField == "booktitle") {
						 txtBooktitle->Visible = true;
						 lblABooktitle->Visible = true;
						 txtBooktitle->TabStop = true;
						 txtBooktitle->TabIndex = TabNumber++;
					 }
					 if (optionalField == "editor") {
						 Editor = true;
						 txtEditor->TabStop = true;
						 txtEditor->TabIndex = TabNumber++;
					 }
					 if (optionalField == "chapter") {
						 txtChapter->Visible = true;
						 lblChapter->Visible = true;
						 txtChapter->TabStop = true;
						 txtChapter->TabIndex = TabNumber++;
					 }
					 if (optionalField == "school") {
						 txtSchool->Visible = true;
						 lblSchool->Visible = true;
						 txtSchool->TabStop = true;
						 txtSchool->TabIndex = TabNumber++;
					 }
					 if (optionalField == "institution") {
						 txtInstitution->Visible = true;
						 lblInstitution->Visible = true;
						 txtInstitution->TabStop = true;
						 txtInstitution->TabIndex = TabNumber++;
					 }
					 if (optionalField == "organization") {
						 txtOrganization->Visible = true;
						 lblOrganization->Visible = true;
						 txtOrganization->TabStop = true;
						 txtOrganization->TabIndex = TabNumber++;
					 }
				 }

				 if (Author && Editor) {
					 txtAuthor->Visible = true;
					 listViewAuthors->Visible = true;
					 lblAuthor->Visible = true;
					 txtEditor->Visible = true;
					 lblEditor->Visible = true;
					 lblFirstName->Visible = true;
					 lblLastName->Visible = true;
					 txtFirstName->Visible = true;
					 txtLastName->Visible = true;
					 btnSetAuthor->Visible = true;
					 btnClearAuthor->Visible = true;
					 rbtnEditor->Visible = true;
					 rbtnAuthor->Visible = true;
					 rbtnAuthor->Checked = false;
					 rbtnEditor->Checked = false;
				 }
				 else if (Author) {
					 txtAuthor->Visible = true;
					 listViewAuthors->Visible = true;
					 lblAuthor->Visible = true;
					 lblFirstName->Visible = true;
					 lblLastName->Visible = true;
					 txtFirstName->Visible = true;
					 txtLastName->Visible = true;
					 btnSetAuthor->Visible = true;
					 btnClearAuthor->Visible = true;
					 rbtnAuthor->Visible = true;
					 rbtnAuthor->Checked = true;
					 tc_no_edit = true;
				 }
				 else if (Editor) {
					 txtEditor->Visible = true;
					 listViewAuthors->Visible = true;
					 lblEditor->Visible = true;
					 lblFirstName->Visible = true;
					 lblLastName->Visible = true;
					 txtFirstName->Visible = true;
					 txtLastName->Visible = true;
					 btnSetAuthor->Visible = true;
					 btnClearAuthor->Visible = true;
					 rbtnEditor->Visible = true;
					 rbtnEditor->Checked = true;
					 tc_no_edit = true;
				 }

				 int mandatoryY = 75;
				 int optionalY = 75;
				 int xOffsetMandatory = 100;
				 int xOffsetOptional = 350;
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
				 return TabNumber;
			 }



			 void PositionFieldWithLabel(Label^ label, TextBox^ field, int% yOffset, int xOffset) {
				 if (field->Visible) {
					 label->Location = Point(xOffset, yOffset);
					 field->Location = Point(xOffset, yOffset + 20);
					 yOffset += 50;
				 }
			 }

	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void MainForm_Shown(System::Object^ sender, System::EventArgs^ e) {
		bool success = LoadEntries("entries.bin");
		this->BringToFront();
		this->Activate();
		String^ text;
		if (success) {
			RefreshListView(); // Aktualisiere die Anzeige der Eintr\u00e4ge, wenn das Laden erfolgreich war
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

		RefreshListView(); // Refresh the ListView to show loaded entries
	}

	private: System::Void btnSaveHDD_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ text;
		SaveEntries("entries.bin");
		if (en_de == 0) {
			text = nachrichten[37, 0];
		}
		else if (en_de == 1) {
			text = nachrichten[37, 1];
		}
		MessageBox::Show(text, "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	private: System::Void txtSearch_TextChanged(System::Object^  sender, System::EventArgs^  e) { //wird automatisch durchsucht wenn etwas eingegeben wird
		String^ searchTerm = txtSearch->Text->Trim();
		PerformSearch(searchTerm);

	}
	private: System::Void btnSetAuthor_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ firstName = txtFirstName->Text->Trim();
		String^ lastName = txtLastName->Text->Trim();
		String^ text;
		if (firstName->Length == 0 || lastName->Length == 0) {
			if (en_de == 0) {
				text = nachrichten[38, 0];
			}
			else if (en_de == 1) {
				text = nachrichten[38, 1];
			}
			MessageBox::Show(text, "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		String^ fullName = lastName + ", " + firstName;
		/*listViewAuthors->Items->Clear();*/
		if (rbtnAuthor->Checked) {
			if (listViewAuthors->SelectedItems->Count > 0) { //always falls into this if loop
				int selectedIndex = listViewAuthors->SelectedIndices[0];
				listViewAuthors->Items[selectedIndex]->Text = fullName;

				UpdateAuthorString(selectedIndex, fullName, txtAuthor);
				listViewAuthors->SelectedIndices->Clear();// reset the index here
			}
			else {
				listViewAuthors->Items->Add(fullName);// Neuen Eintrag hinzuf\u00fcgen
				txtAuthor->Text += (txtAuthor->Text->Length > 0 ? " and " : "") + fullName;
			}
		}
		else if (rbtnEditor->Checked) {
			if (listViewAuthors->SelectedItems->Count > 0) {
				int selectedIndex = listViewAuthors->SelectedIndices[0];
				listViewAuthors->Items[selectedIndex]->Text = fullName;

				UpdateAuthorString(selectedIndex, fullName, txtEditor);
			}
			else {
				listViewAuthors->Items->Add(fullName);// Neuen Eintrag hinzuf\u00fcgen
				txtEditor->Text += (txtEditor->Text->Length > 0 ? " and " : "") + fullName;
			}
		}

		else {
			if (en_de == 0) {
				text = nachrichten[39, 0];
			}
			else if (en_de == 1) {
				text = nachrichten[39, 1];
			}
			MessageBox::Show(text, "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}

		txtFirstName->Clear();
		txtLastName->Clear();
	}
	private: System::Void btnClearAuthor_Click(System::Object^  sender, System::EventArgs^  e) {
		listViewAuthors->Items->Clear();
		if (rbtnAuthor->Checked) {
			txtAuthor->Clear(); // Clears the author field
		}
		else if (rbtnEditor->Checked) {
			txtEditor->Clear(); // Clears the editor field
		}
		else {
			if (en_de == 0) {
				MessageBox::Show(nachrichten[40, 0]);
			}
			else if (en_de == 1) {
				MessageBox::Show(nachrichten[40, 1]);
			}
			//MessageBox::Show("Select Author or Editor!");
		}

	}
	private: System::Void btnExportToBib_Click(System::Object^  sender, System::EventArgs^  e) {

		int n;
		n = 0;
		int size = entries->Count;

		// MessageBox::Show("Die Gr\u00f6\u00dfe des Arrays betr\u00e4gt: " + size.ToString());

		//meins
		SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
		saveFileDialog->Filter = "Bib Dateien (*.bib)|*.bib";
		saveFileDialog->Title = "Speicher die Bib-Datei";
		if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			// Der ausgew\u00e4hlte Dateipfad
			String^ filePath = saveFileDialog->FileName;
			//meins

			FILE* Quelle;
			//Quelle = fopen("Quelle.bib", "w");
			Quelle = fopen((const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(filePath), "w");

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
	}

			 //mein
			 void listViewAuthors_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
			 {
				 if (listViewAuthors->SelectedItems->Count > 0 && rbtnAuthor->Checked)
				 {
					 String^ selectedAuthor = listViewAuthors->SelectedItems[0]->Text;
					 // Autor in das Textfeld f\u00fcr Vorname und Nachname aufteilen
					 array<String^>^ nameParts = selectedAuthor->Split(',');
					 txtLastName->Text = nameParts[0]; // Nachname
					 txtFirstName->Text = nameParts->Length > 1 ? nameParts[1] : ""; // Vorname
				 }
				 if (listViewAuthors->SelectedItems->Count > 0 && rbtnEditor->Checked)
				 {
					 String^ selectedAuthor = listViewAuthors->SelectedItems[0]->Text;

					 array<String^>^ nameParts = selectedAuthor->Split(',');
					 txtLastName->Text = nameParts[0]; // Nachname
					 txtFirstName->Text = nameParts->Length > 1 ? nameParts[1] : ""; // Vorname
				 }
			 }
			 void UpdateAuthorString(int index, String^ updatedEntry, TextBox^ storageTextBox) {
				 // Den Speicherstring ("txtAuthor") in Eintr\u00e4ge aufteilen
				 array<String^>^ authorEntries = storageTextBox->Text->Split(gcnew array<String^> { " and " }, StringSplitOptions::None);

				 // Den spezifischen Eintrag aktualisieren
				 if (index >= 0 && index < authorEntries->Length) {
					 authorEntries[index] = updatedEntry;
				 }

				 // Den Speicherstring neu zusammensetzen
				 storageTextBox->Text = String::Join(" and ", authorEntries);
			 }
			 //mein
			 bool TypeChanged = false;
			 bool tc_no_edit = false;
			 //String safe_edit_auth;
	private: System::Void rbtnAuthor_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (rbtnAuthor->Checked) {

			//if (!String::IsNullOrEmpty(txtEditor->Text)) {
			if (cmbType->SelectedItem != "conference" && cmbType->SelectedItem != "incollection" && cmbType->SelectedItem != "inproceedings") { //incollection, inbook
				if (!String::IsNullOrEmpty(txtEditor->Text)) {
					if (TypeChanged == true) {
						txtEditor->Text = "";
						TypeChanged = false;
					}
					else {
						//if (tc_no_edit == true) {
						txtAuthor->Text = txtEditor->Text;
						tc_no_edit = false;
						//}
					}
					//txtAuthor->Text = txtEditor->Text;
					txtEditor->Clear();
					listViewAuthors->Items->Clear();
					if (txtAuthor->Text != "")
					{
						array<String^>^ authors = txtAuthor->Text->Split(gcnew array<String^>{ " and " }, StringSplitOptions::None);
						for each (String^ author in authors)
						{
							listViewAuthors->Items->Add(author->Trim());
						}
					}
				}
			}
			else {
				TypeChanged = true;//----------------
				listViewAuthors->Items->Clear();
				if (txtAuthor->Text != "")
				{
					array<String^>^ authors = txtAuthor->Text->Split(gcnew array<String^>{ " and " }, StringSplitOptions::None);
					for each (String^ author in authors)
					{
						listViewAuthors->Items->Add(author->Trim());
					}
				}
				/*TypeChanged = false;*/
			}
			//}
		}
	}

	private: System::Void rbtnEditor_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (rbtnEditor->Checked) {
			//listViewAuthors->Items->Clear();
			//if (!String::IsNullOrEmpty(txtAuthor->Text)) { //Author gef\u00fcllt

			if (cmbType->SelectedItem != "conference" && cmbType->SelectedItem != "incollection" && cmbType->SelectedItem != "inproceedings") {
				if (!String::IsNullOrEmpty(txtAuthor->Text)/* && !TypeChanged*/) {
					if (TypeChanged == true) {
						txtAuthor->Text = "";
						TypeChanged = false;
					}
					else {
						//if (tc_no_edit == true) {
						txtEditor->Text = txtAuthor->Text;
						tc_no_edit = false;
						//}
					}
					//txtEditor->Text = txtAuthor->Text;
					txtAuthor->Clear();

					listViewAuthors->Items->Clear();
					if (txtEditor->Text != "")
					{
						array<String^>^ editors = txtEditor->Text->Split(gcnew array<String^>{ " and " }, StringSplitOptions::None);
						for each (String^ editor in editors)
						{
							listViewAuthors->Items->Add(editor->Trim());
						}
					}
				}
			}
			else {
				TypeChanged = true;//----------------
				listViewAuthors->Items->Clear();
				if (txtEditor->Text != "")
				{
					array<String^>^ editors = txtEditor->Text->Split(gcnew array<String^>{ " and " }, StringSplitOptions::None);
					for each (String^ editor in editors)
					{
						listViewAuthors->Items->Add(editor->Trim());
					}
				}
				/*TypeChanged = false;*/
			}
			//}
		}
	}

			 //mein
			 int en_de;
	private: System::Void btnLanguage_Click(System::Object^  sender, System::EventArgs^  e) {
		bool n;
		n = false;
		if (en_de == 0 && n == false) {
			en_de = 1;
			n = true;
		}
		if (en_de == 1 && n == false) {
			en_de = 0;
			n = true;
		}
		sprache_aendern();
	}
			 void sprache_aendern() {
				 if (en_de == 0) {
					 this->btnSetAuthor->Text = L"Set";
					 this->btnExportToBib->Text = L"Export to .bib";
					 this->btnNew->Text = L"New";
					 this->btnEdit->Text = L"Edit";
					 this->btnDelete->Text = L"Delete";
					 this->rbtnEditor->Text = L"Editor";
					 this->rbtnAuthor->Text = L"Author";
					 this->btnClearAuthor->Text = L"Clear";
					 this->lblKeyword->Text = L"Keyword:";
					 this->lblAuthor->Text = L"Author:";
					 this->lblTitle->Text = L"Title:";
					 this->lblYear->Text = L"Year:";
					 this->lblJournal->Text = L"Journal:";
					 this->lblVolume->Text = L"Volume:";
					 this->lblNumber->Text = L"Number:";
					 this->lblPages->Text = L"Pages:";
					 this->lblMonth->Text = L"Month:";
					 this->lblNote->Text = L"Note:";
					 this->lblPublisher->Text = L"Publisher:";
					 this->lblSeries->Text = L"Series:";
					 this->lblAddress->Text = L"Address:";
					 this->lblEdition->Text = L"Edition:";
					 this->lblHowpublished->Text = L"How published:";
					 this->lblABooktitle->Text = L"Booktitle:";
					 this->lblEditor->Text = L"Editor:";
					 this->lblChapter->Text = L"Chapter:";
					 this->lblSchool->Text = L"School:";
					 this->lblInstitution->Text = L"Institution:";
					 this->lblOrganization->Text = L"Organization:";
					 this->lblLastName->Text = L"Last Name:";
					 this->lblFirstName->Text = L"First Name:";
					 this->btnSave->Text = L"Save";
					 this->btnCancel->Text = L"Cancel";
					 this->btnSaveHDD->Text = L"Save HDD";
					 this->btnLanguage->Text = L"German";
					 this->btnSaveHDD->Text = L"Save to HDD";
					 this->btnPDF->Text = L"Manual";
				 }

				 if (en_de == 1) {
					 this->btnSetAuthor->Text = L"Setzen";
					 this->btnExportToBib->Text = L"Exportieren zu .bib";
					 this->btnNew->Text = L"Neu";
					 this->btnEdit->Text = L"Bearbeiten";
					 this->btnDelete->Text = L"L\u00f6schen";
					 this->rbtnEditor->Text = L"Herausgeber";
					 this->rbtnAuthor->Text = L"Autor";
					 this->btnClearAuthor->Text = "Autor L\u00f6schen";
					 this->lblKeyword->Text = L"Schlagwort:";
					 this->lblAuthor->Text = L"Autor:";
					 this->lblTitle->Text = L"Titel:";
					 this->lblYear->Text = L"Jahr:";
					 this->lblJournal->Text = L"Zeitschrift:";
					 this->lblVolume->Text = L"Band:";
					 this->lblNumber->Text = L"Nummer:";
					 this->lblPages->Text = L"Seiten:";
					 this->lblMonth->Text = L"Monat:";
					 this->lblNote->Text = L"Anmerkung:";
					 this->lblPublisher->Text = L"Verlag:";
					 this->lblSeries->Text = L"Serie:";
					 this->lblAddress->Text = L"Adresse:";
					 this->lblEdition->Text = L"Auflage:";
					 this->lblHowpublished->Text = "Ver\u00f6ffentlichungsart:";
					 this->lblABooktitle->Text = L"Buchtitel:";
					 this->lblEditor->Text = L"Herausgeber:";
					 this->lblChapter->Text = L"Kapitel:";
					 this->lblSchool->Text = L"Schule:";
					 this->lblInstitution->Text = L"Institution:";
					 this->lblOrganization->Text = L"Organisation:";
					 this->lblLastName->Text = L"Nachname:";
					 this->lblFirstName->Text = L"Vorname:";
					 this->btnSave->Text = L"Speichern";
					 this->btnCancel->Text = L"Abbrechen";
					 this->btnSaveHDD->Text = L"Speichern auf HDD";
					 this->btnLanguage->Text = L"Englisch";
					 this->btnSaveHDD->Text = L"Speichern auf HDD";
					 this->btnPDF->Text = L"Handbuch";
				 }
				 nachrichten = gcnew array<String^, 2>{
					 { "Please select an entry type.\n", "Bitte w\u00e4hlen Sie einen Eintragstyp aus.\n" },
					 { "Invalid entry type selected.\n","Ung\u00fcltiger Eintragstyp ausgew\u00e4hlt.\n" },
					 { "Please fill in the keyword field.\n","Bitte f\u00fcllen Sie das Stichwortfeld aus.\n" },
					 { "Please fill in the title field.\n", "Bitte f\u00fcllen Sie das Feld f\u00fcr den Titel aus.\n" },
					 { "Please enter a number into the year field.\n", "Bitte geben Sie eine Zahl in das Jahr-Feld ein.\n" },
					 { "Please enter a number into the volume field.\n","Bitte geben Sie eine Zahl in das Bandfeld ein.\n" },
					 { "Please enter a number into the number field.\n","Bitte geben Sie eine Nummer in das Nummernfeld ein.\n" },
					 { "Please enter a number into the pages field.\n","Bitte geben Sie eine Zahl in das Seitenfeld ein.\n" },
					 { "Please fill in the month field.\n","Bitte f\u00fcllen Sie das Monatsfeld aus.\n" },
					 { "Please fill in the note field.\n","Bitte f\u00fcllen Sie das Notizfeld aus.\n" },
					 { "Please fill in the publisher field.\n","Bitte f\u00fcllen Sie das Herausgeberfeld aus.\n" },
					 { "Please fill in the series field.\n","Bitte f\u00fcllen Sie das Serienfeld aus.\n" },
					 { "Please fill in the address field.\n","Bitte f\u00fcllen Sie das Adressfeld aus.\n" },
					 { "Please fill in the edition field.\n", "Bitte f\u00fcllen Sie das Editionsfeld aus.\n" },
					 { "Please fill in the how published field.\n", "Bitte f\u00fcllen Sie das Publisherfeld aus.\n" },
					 { "Please fill in the book title field.\n", "Bitte f\u00fcllen Sie das Buchtitelfeld aus.\n" },
					 { "Please fill in the school field.\n", "Bitte f\u00fcllen Sie das Schulfeld aus.\n" },
					 { "Please fill in the institution field.\n", "Bitte f\u00fcllen Sie das Instituionsfeld aus.\n" },
					 { "Please fill in the organization field.\n","Bitte f\u00fcllen Sie das Organisationsfeld aus.\n" },
					 { "Please fill in either the author or the editor field.\n","Bitte f\u00fcllen Sie entweder das Autor - oder Editorfeld aus.\n" },
					 { "Cannot have both Author and Editor!\n", "Es k\u00f6nnen nicht sowohl Autor als auch Editor vorhanden sein!\n" },
					 { "Please fill in the author field.\n", "Bitte f\u00fcllen Sie das Feld f\u00fcr den Autor aus.\n" },
					 { "Please fill in the editor field.\n", "Bitte f\u00fcllen Sie das Feld f\u00fcr den Herausgeber aus.\n" },
					 { "Please fill in either the Pages or the Chapter field.\n","Bitte f\u00fcllen Sie entweder das Feld Seiten oder das Feld Kapitel aus.\n" },
					 { "Please fill in the pages field.\n", "Bitte f\u00fcllen Sie das Feld f\u00fcr die Seiten aus.\n" },
					 { "Please fill in the chapter field.\n", "Bitte f\u00fcllen Sie das Feld f\u00fcr das Kapitel aus.\n" },
					 { "Please select an entry type.\n","Bitte w\u00e4hlen Sie einen Eintragstyp aus.\n" },
					 { "Invalid entry type selected.\n","Ung\u00fcltiger Eintragstyp ausgew\u00e4hlt.\n" },
					 { "Year must be a number.\n","Das Jahr muss eine Zahl sein.\n" },
					 { "Volume must be a number.\n","Das Band muss eine Zahl sein.\n" },
					 { "Number must be a number.\n","Zahl muss eine Zahl sein.\n" },
					 { "Pages must be a number.\n","Seiten m\u00fcssen eine Zahl sein.\n" },
					 { "Error saving entries : ","Fehler beim Speichern der Eintr\u00e4ge : " },
					 { "No entries file found.Starting with an empty list.\n","Keine Eintragsdatei gefunden.Beginnend mit einer leeren Liste.\n" },
					 { "Error loading entries: ","Fehler beim Laden der Eintr\u00e4ge : " },
					 { "Entries loaded successfully from HDD.\n", "Eintr\u00e4ge erfolgreich von der Festplatte geladen.\n" },
					 { "Failed to load entries from HDD.\n","Eintr\u00e4ge konnten nicht von der Festplatte geladen werden.\n" },
					 { "Entries saved successfully to HDD.\n","Eintr\u00e4ge erfolgreich auf der Festplatte gespeichert.\n" },
					 { "Please enter both first name and last name.\n","Bitte geben Sie sowohl den Vor - als auch den Nachnamen ein.\n" },
					 { "Please select Author or Editor.\n","Bitte w\u00e4hlen Sie Autor oder Editor aus.\n" },
					 { "Select Author or Editor!","W\u00e4hlen Sie Autor oder Herausgeber aus!" },
					 { "The PDF file was not found:","Die PDFDatei wurde nicht gefunden: " },
					 { "Missing Input!", "Fehlende Eingabe!"}
				 };
				 /*std::pair<std::string, std::string> errorMessages[] = {
				{"Bitte f\u00fcllen Sie das Feld f\u00fcr das Journal aus.", "Please fill in the journal field."},
				{"Bitte geben Sie eine Zahl in das Jahr-Feld ein.", "Please enter a number into the year field."},
				{"Es darf nicht sowohl Autor als auch Herausgeber angegeben werden!", "Cannot have both Author and Editor!"},
				{"Bitte f\u00fcllen Sie das Feld f\u00fcr den Autor aus.", "Please fill in the author field."},
				{"Bitte f\u00fcllen Sie das Feld f\u00fcr den Herausgeber aus.", "Please fill in the editor field."},
				{"Bitte f\u00fcllen Sie das Feld f\u00fcr das Kapitel aus.", "Please fill in the chapter field."},
				{"Bitte f\u00fcllen Sie das Feld f\u00fcr den Titel aus.", "Please fill in the title field."},
				{"Bitte f\u00fcllen Sie das Feld f\u00fcr die Seiten aus.", "Please fill in the pages field."},
				{"Missing Input","Fehlende Eingabe"}
				 };*/


			 }
	private: System::Void btnPDF_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ text;

		String^ exePfad = Application::StartupPath;

		String^ pdfName = "pi-314-inhalt.pdf";

		String^ pdfPfaduName = Path::Combine(exePfad, pdfName);

		if (System::IO::File::Exists(pdfPfaduName)) {
			System::Diagnostics::Process::Start(pdfPfaduName);
		}
		else {
			if (en_de == 0) {
				text = nachrichten[41, 0];
			}
			else if (en_de == 1) {
				text = nachrichten[41, 1];
			}
			MessageBox::Show(text + pdfPfaduName);
		}


	}
	private: System::Void btnDark_Click(System::Object^  sender, System::EventArgs^  e) {

		if (this->BackColor == System::Drawing::Color::FromArgb(19, 17, 28))
		{
			this->BackColor = System::Drawing::Color::White;
			panelDetails->BackColor = System::Drawing::Color::White;
			listViewEntries->BackColor = System::Drawing::Color::White;
			listViewAuthors->BackColor = System::Drawing::Color::White;
			rbtnAuthor->ForeColor = System::Drawing::Color::Black;
			rbtnEditor->ForeColor = System::Drawing::Color::Black;
			btnSetAuthor->ForeColor = System::Drawing::Color::Black;
			btnClearAuthor->ForeColor = System::Drawing::Color::Black;
			lblFirstName->ForeColor = System::Drawing::Color::Black;
			lblLastName->ForeColor = System::Drawing::Color::Black;
			lblKeyword->ForeColor = System::Drawing::Color::Black;
			lblAuthor->ForeColor = System::Drawing::Color::Black;
			lblTitle->ForeColor = System::Drawing::Color::Black;
			lblYear->ForeColor = System::Drawing::Color::Black;
			lblJournal->ForeColor = System::Drawing::Color::Black;
			lblVolume->ForeColor = System::Drawing::Color::Black;
			lblNumber->ForeColor = System::Drawing::Color::Black;
			lblPages->ForeColor = System::Drawing::Color::Black;
			lblMonth->ForeColor = System::Drawing::Color::Black;
			lblNote->ForeColor = System::Drawing::Color::Black;
			lblPublisher->ForeColor = System::Drawing::Color::Black;
			lblSeries->ForeColor = System::Drawing::Color::Black;
			lblAddress->ForeColor = System::Drawing::Color::Black;
			lblEdition->ForeColor = System::Drawing::Color::Black;
			lblHowpublished->ForeColor = System::Drawing::Color::Black;
			lblABooktitle->ForeColor = System::Drawing::Color::Black;
			lblEditor->ForeColor = System::Drawing::Color::Black;
			lblChapter->ForeColor = System::Drawing::Color::Black;
			lblSchool->ForeColor = System::Drawing::Color::Black;
			lblInstitution->ForeColor = System::Drawing::Color::Black;
			lblOrganization->ForeColor = System::Drawing::Color::Black;
			listViewEntries->ForeColor = System::Drawing::Color::Black;
			listViewAuthors->ForeColor = System::Drawing::Color::Black;
		}
		else
		{
			this->BackColor = System::Drawing::Color::FromArgb(19, 17, 28);
			panelDetails->BackColor = System::Drawing::Color::FromArgb(33, 33, 33);
			listViewEntries->BackColor = System::Drawing::Color::FromArgb(33, 33, 33);
			listViewAuthors->BackColor = System::Drawing::Color::FromArgb(33, 33, 33);
			btnSave->BackColor = System::Drawing::Color::White;
			btnCancel->BackColor = System::Drawing::Color::White;
			rbtnAuthor->ForeColor = System::Drawing::Color::White;
			rbtnEditor->ForeColor = System::Drawing::Color::White;
			btnSetAuthor->ForeColor = System::Drawing::Color::White;
			btnClearAuthor->ForeColor = System::Drawing::Color::White;
			lblFirstName->ForeColor = System::Drawing::Color::White;
			lblLastName->ForeColor = System::Drawing::Color::White;
			lblKeyword->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblAuthor->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblTitle->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblYear->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblJournal->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblVolume->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblNumber->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblPages->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblMonth->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblNote->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblPublisher->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblSeries->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblAddress->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblEdition->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblHowpublished->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblABooktitle->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblEditor->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblChapter->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblSchool->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblInstitution->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			lblOrganization->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			listViewEntries->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
			listViewAuthors->ForeColor = System::Drawing::Color::FromArgb(88, 110, 214);
		}

	}
	private: System::Void darkmodeLightmodeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void toolStripSplitButton1_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}
