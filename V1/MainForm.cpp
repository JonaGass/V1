#include "MainForm.h"

namespace V1 {


	// Funktion zum Bereinigen der Textfelder
	void MainForm::ClearEntryDetails()
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
		listViewAuthors->Items->Clear();
		SetFieldsReadOnly(false);
	}

	// Funktion zum Ändern des ReadOnly Status
	void MainForm::SetFieldsReadOnly(bool readOnly)
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

	//Funktion um Dropdown mit auswählbaren Referenztypen zu füllen
	void MainForm::PopulateTypeDropdown()
	{
		for each (DataTypeFields ^ type in dataTypes)
		{
			cmbType->Items->Add(type->TypeName);
		}
	}

	// Funktion zum Anzeigen der EntryDetails
	void MainForm::DisplayEntryDetails(DataArray^ entry)
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


		listViewAuthors->Items->Clear();

		if (entry->author != nullptr) // Überprüft ob ein Autor vorhanden ist
		{
			array<String^>^ authors = entry->author->Split(gcnew array<String^>{ " and " }, StringSplitOptions::None); // Teilt die Autornamen am Wort "and"
			for each (String^ author in authors) // Läuft einmal durch jeden Autor durch
			{
				listViewAuthors->Items->Add(author->Trim()); // Fügt jeden Autor der ListView hinzu
			}
		}

		if (entry->editor != nullptr) // Überprüft ob ein Editor vorhanden ist
		{
			array<String^>^ editors = entry->editor->Split(gcnew array<String^>{ " and " }, StringSplitOptions::None); // Teilt die Editornamen am Wort "and"
			for each (String^ editor in editors) // Läuft einmal durch jeden Editor durch
			{
				listViewAuthors->Items->Add(editor->Trim()); // Fügt jeden Editor der ListView hinzu
			}
		}



	}

	bool MainForm::ValidateEntry()
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
					stateMandatory = false;
				}
				if (field == "author") {
					AuthorMandatory = true;
					if (txtAuthor->Text->Trim() == String::Empty) {
					}
					else {
						hasAuthor = true; // Author ist da
					}
				}
				if (field == "title" && txtTitle->Text->Trim() == String::Empty) {
					if (en_de == 0) {
						errorMessage += nachrichten[3, 0];
					}
					else if (en_de == 1) {
						errorMessage += nachrichten[3, 1];
					}
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
					stateMandatory = false;
				}
				if (field == "journal" && txtJournal->Text->Trim() == String::Empty) {
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
					stateMandatory = false;
				}
				int pages;
				if (field == "pages") {
					PagesMandatory = true;
					if (txtPages->Text->Trim() == String::Empty) {
					}
					else if (!Int32::TryParse(txtPages->Text, pages)) {
						if (en_de == 0) {
							errorMessage += nachrichten[7, 0];
						}
						else if (en_de == 1) {
							errorMessage += nachrichten[7, 1];
						}
					}
					else {
						hasPages = true; // Pages ist da
					}
				}
				if (field == "month" && txtMonth->Text->Trim() == String::Empty) {
					if (en_de == 0) {
						errorMessage += nachrichten[8, 0];
					}
					else if (en_de == 1) {
						errorMessage += nachrichten[8, 1];
					}
					stateMandatory = false;
				}
				if (field == "note" && txtNote->Text->Trim() == String::Empty) {
					if (en_de == 0) {
						errorMessage += nachrichten[9, 0];
					}
					else if (en_de == 1) {
						errorMessage += nachrichten[9, 1];
					}
					stateMandatory = false;
				}
				if (field == "publisher" && txtPublisher->Text->Trim() == String::Empty) {
					if (en_de == 0) {
						errorMessage += nachrichten[10, 0];
					}
					else if (en_de == 1) {
						errorMessage += nachrichten[10, 1];
					}
					stateMandatory = false;
				}
				if (field == "series" && txtSeries->Text->Trim() == String::Empty) {
					if (en_de == 0) {
						errorMessage += nachrichten[11, 0];
					}
					else if (en_de == 1) {
						errorMessage += nachrichten[11, 1];
					}
					stateMandatory = false;
				}
				if (field == "address" && txtAddress->Text->Trim() == String::Empty) {
					if (en_de == 0) {
						errorMessage += nachrichten[12, 0];
					}
					else if (en_de == 1) {
						errorMessage += nachrichten[12, 1];
					}
					stateMandatory = false;
				}
				if (field == "edition" && txtEdition->Text->Trim() == String::Empty) {
					if (en_de == 0) {
						errorMessage += nachrichten[13, 0];
					}
					else if (en_de == 1) {
						errorMessage += nachrichten[13, 1];
					}
					stateMandatory = false;
				}
				if (field == "howpublished" && txtHowpublished->Text->Trim() == String::Empty) {
					if (en_de == 0) {
						errorMessage += nachrichten[14, 0];
					}
					else if (en_de == 1) {
						errorMessage += nachrichten[14, 1];
					}
					stateMandatory = false;
				}
				if (field == "booktitle" && txtBooktitle->Text->Trim() == String::Empty) {
					if (en_de == 0) {
						errorMessage += nachrichten[15, 0];
					}
					else if (en_de == 1) {
						errorMessage += nachrichten[15, 1];
					}
					stateMandatory = false;
				}
				if (field == "editor") {
					EditorMandatory = true;
					if (txtEditor->Text->Trim() == String::Empty) {
					}
					else {
						hasEditor = true; // Editor ist da
					}
				}
				if (field == "chapter") {
					ChapterMandatory = true;
					if (txtChapter->Text->Trim() == String::Empty) {
					}
					else {
						hasChapter = true; // Chapter ist da
					}
				}

				if (field == "school" && txtSchool->Text->Trim() == String::Empty) {
					if (en_de == 0) {
						errorMessage += nachrichten[16, 0];
					}
					else if (en_de == 1) {
						errorMessage += nachrichten[16, 1];
					}
					stateMandatory = false;
				}
				if (field == "institution" && txtInstitution->Text->Trim() == String::Empty) {
					if (en_de == 0) {
						errorMessage += nachrichten[17, 0];
					}
					else if (en_de == 1) {
						errorMessage += nachrichten[17, 1];
					}
					stateMandatory = false;
				}
				if (field == "organization" && txtOrganization->Text->Trim() == String::Empty) {
					if (en_de == 0) {
						errorMessage += nachrichten[18, 0];
					}
					else if (en_de == 1) {
						errorMessage += nachrichten[18, 1];
					}
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
					stateMandatory = false;
				}
				else if (hasAuthor && hasEditor) {
					if (en_de == 0) {
						errorMessage += nachrichten[20, 0];
					}
					else if (en_de == 1) {
						errorMessage += nachrichten[20, 1];
					}
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
					stateMandatory = false;
				}
			}

			if (!stateMandatory) {
				MessageBox::Show(errorMessage, nachrichten[42, en_de], MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
		}
		return stateMandatory;
	}

	bool MainForm::ValidateOptional()
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
			return false;
		}
		String^ errorMessageOptional = "";
		// Check each optional field; leave conditions empty
		for each (String^ field in selectedTypeFields->OptionalFields)
		{
			int year;
			if (field == "year" && !Int32::TryParse(txtYear->Text, year) && !(txtYear->Text->Trim() == String::Empty)) {
				stateOptional = false;
				if (en_de == 0) {
					errorMessageOptional += nachrichten[28, 0];
				}
				else if (en_de == 1) {
					errorMessageOptional += nachrichten[28, 1];
				}
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
			}
		}
		if (!stateOptional) {
			MessageBox::Show(errorMessageOptional, nachrichten[42, en_de], MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		return stateOptional;
	}

	void MainForm::UpdateUIState(bool inEditMode)
	{
		// Toggelt die UI-Elemente für EditMode bzw. nicht-EditMode
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

	void MainForm::RefreshListView()
	{
		// Alle Einträge aus "entries" in Liste anzeigen
		listViewEntries->Items->Clear();
		for each (DataArray^ entry in entries) {
			String^ itemText = entry->keyword;
			listViewEntries->Items->Add(gcnew ListViewItem(itemText));
		}
	}

	// Alle Textfelder ausblenden
	void MainForm::HideAllFields()
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
	}

	void MainForm::SaveEntries(String^ filename)
	{
		using namespace System::IO;
		using namespace System::Runtime::Serialization::Formatters::Binary;
		FileStream^ fs = gcnew FileStream(filename, FileMode::Create, FileAccess::Write);
		BinaryFormatter^ formatter = gcnew BinaryFormatter();
		String^ text;
		try {
			// Für Speichern in Binärdatei Serialize der Daten
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
		} //Fehlermeldung wenn Speichern nicht erfolgreich
		finally{
			fs->Close();
		}
	}

	bool MainForm::LoadEntries(String^ filename)
	{
		using namespace System::IO;
		using namespace System::Runtime::Serialization::Formatters::Binary;
		FileStream^ fs = nullptr;
		bool success = false;
		String^ text;

		try {
			if (File::Exists(filename)) {
				fs = gcnew FileStream(filename, FileMode::Open, FileAccess::Read);
				BinaryFormatter^ formatter = gcnew BinaryFormatter();
				// Deserialisieren des Dateistream in die Eintragsliste
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

		return success; // Gibt den Erfolg oder Misserfolg zurück
	}

	void MainForm::PerformSearch(String^ searchTerm) {
		listViewEntries->Items->Clear(); // Zurücksetzen der angezeigten Listenelemente
		displayedEntryIndices->Clear();

		for (int i = 0; i < entries->Count; i++) {
			DataArray^ entry = entries[i];
			if ((entry->keyword->IndexOf(searchTerm, StringComparison::CurrentCultureIgnoreCase) >= 0) ||
				(entry->title->IndexOf(searchTerm, StringComparison::CurrentCultureIgnoreCase) >= 0) ||
				(entry->author->IndexOf(searchTerm, StringComparison::CurrentCultureIgnoreCase) >= 0)) { // Vergleich des SearchTerm mit den Feldern keyword, title, author; theoretisch erweiterbar

				// Wenn übereinstimmung gefunden wird der entsprechedne Eintrag in die anzuzeigende Liste aufgenommen
				String^ itemText = entry->keyword;
				listViewEntries->Items->Add(gcnew ListViewItem(itemText));

				// Ursprünglicher Index wird gespeichert
				displayedEntryIndices->Add(i);
			}
		}
	}

	// Funktion Anzeigen der Textfelder nach ausgewähltem Referenztypen
	int MainForm::ShowFieldsForType(DataTypeFields^ type)	// Rückgabewert =  TabIndex des letzten Feldes
	{
		// Alle Felder erstmal ausblenden
		HideAllFields();
		int TabNumber = 10;	//	TabIndex des ersten Feldes wird vergeben, danach werden die TabIndizes dynamisch vergeben
		bool Author = false;	//	Author und Editor müssen gesondert behandelt werden
		bool Editor = false;

		// Nur relevante Felder werden eingeblendet
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

		if (Author && Editor) {					// Spezialfall Author && Editor mit EingabeUI Vor- und Nachname
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
		else if (Author) {							// Spezialfall Author mit EingabeUI Vor- und Nachname
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
		else if (Editor) {							// Spezialfall Editor mit EingabeUI Vor- und Nachname
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
		int xOffsetMandatory = 98;
		int xOffsetOptional = 368;

		// Zwingende Felder auf der linken Seite einblenden
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
		// Optionale Felder auf der rechten Seite einblenden
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
		return TabNumber; // erreichter TabIndex wird zurückgegeben
	}

	// UI-Elemente dynamisch positionieren
	void MainForm::PositionFieldWithLabel(Label^ label, TextBox^ field, int% yOffset, int xOffset)
	{
		if (field->Visible) {
			label->Location = Point(xOffset, yOffset);
			field->Location = Point(xOffset, yOffset + 20);
			yOffset += 50;
		}
	}

	void MainForm::sprache_aendern()
	{
		if (en_de == 0) {// Wenn die Sprache auf Englisch eingestellt ist
					 // Ändere die Texte der UI-Elemente auf Englisch
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

		if (en_de == 1) {// Wenn die Sprache auf Deutsch eingestellt ist
					 // Ändere die Texte der UI-Elemente auf Deutsch
			this->btnSetAuthor->Text = L"Setzen";
			this->btnExportToBib->Text = L"Exportieren zu .bib";
			this->btnNew->Text = L"Neu";
			this->btnEdit->Text = L"Bearbeiten";
			this->btnDelete->Text = L"L\u00f6schen";
			this->rbtnEditor->Text = L"Herausgeber";
			this->rbtnAuthor->Text = L"Autor";
			this->btnClearAuthor->Text = "Löschen";
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
		nachrichten = gcnew array<String^, 2>{ //füllt den Array für die Nachrichten mit einem deutschen und einem englischen Text 
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
			{ "The PDF file was not found:","Die PDF Datei wurde nicht gefunden: " },
			{ "Missing Input!", "Fehlende Eingabe!" }
		};
	}

	void MainForm::DarkMode()
	{
		// Array aller Textboxen
		array<System::Windows::Forms::TextBox^>^ textBoxes = {
			this->txtKeyword, this->txtAuthor, this->txtTitle, this->txtYear,
			this->txtJournal, this->txtVolume, this->txtNumber, this->txtPages,
			this->txtMonth, this->txtNote, this->txtPublisher, this->txtSeries,
			this->txtAddress, this->txtEdition, this->txtHowpublished, this->txtBooktitle,
			this->txtEditor, this->txtChapter, this->txtSchool, this->txtInstitution,
			this->txtOrganization, this->txtSearch, this->txtFirstName, this->txtLastName
		};

		if (this->BackColor == System::Drawing::Color::FromArgb(30, 30, 30)) { // Wenn Dark Mode Farben
			// Setze auf Lightmode

			Assembly^ assemblyHTML = Assembly::GetExecutingAssembly();
			Stream^ streamHTML = assemblyHTML->GetManifestResourceStream("lightmode.html");
			StreamReader^ reader = gcnew StreamReader(streamHTML);
			String^ htmlContent = reader->ReadToEnd();
			webBrowser1->DocumentText = htmlContent;

			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->btnDarkmode->Text = L"Darkmode";
			panelDetails->BackColor = System::Drawing::Color::WhiteSmoke;
			listViewEntries->BackColor = System::Drawing::Color::WhiteSmoke;
			listViewAuthors->BackColor = System::Drawing::Color::WhiteSmoke;


			for each (System::Windows::Forms::TextBox^ textBox in textBoxes) {
				textBox->BackColor = System::Drawing::Color::White;
				textBox->ForeColor = System::Drawing::Color::Black;
			}

			// Setze Farben für Labels und Buttons
			array<System::Windows::Forms::Control^>^ controls = {
				rbtnAuthor, rbtnEditor, btnSetAuthor, btnClearAuthor,
				lblFirstName, lblLastName, lblKeyword, lblAuthor, lblTitle, lblYear,
				lblJournal, lblVolume, lblNumber, lblPages, lblMonth, lblNote,
				lblPublisher, lblSeries, lblAddress, lblEdition, lblHowpublished,
				lblABooktitle, lblEditor, lblChapter, lblSchool, lblInstitution, lblOrganization,
				listViewEntries, listViewAuthors, btnCancel, btnSave
			};

			for each (System::Windows::Forms::Control^ control in controls) {
				control->ForeColor = System::Drawing::Color::Black;
			}

		}
		else { // Light Mode Farben
		 // Setze auf Darkmode
			Assembly^ assemblyHTML = Assembly::GetExecutingAssembly();
			Stream^ streamHTML = assemblyHTML->GetManifestResourceStream("darkmode.html");
			StreamReader^ reader = gcnew StreamReader(streamHTML);
			String^ htmlContent = reader->ReadToEnd();
			webBrowser1->DocumentText = htmlContent;

			this->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
			this->btnDarkmode->Text = L"Lightmode";
			panelDetails->BackColor = System::Drawing::Color::FromArgb(45, 45, 45);
			listViewEntries->BackColor = System::Drawing::Color::FromArgb(45, 45, 45);
			listViewAuthors->BackColor = System::Drawing::Color::FromArgb(45, 45, 45);


			for each (System::Windows::Forms::TextBox^ textBox in textBoxes) {
				textBox->BackColor = System::Drawing::Color::FromArgb(45, 45, 45);
				textBox->ForeColor = System::Drawing::Color::White;
			}

			// Setze Farben für Labels und Buttons
			array<System::Windows::Forms::Control^>^ controls = {
				rbtnAuthor, rbtnEditor, btnSetAuthor, btnClearAuthor,
				lblFirstName, lblLastName, lblKeyword, lblAuthor, lblTitle, lblYear,
				lblJournal, lblVolume, lblNumber, lblPages, lblMonth, lblNote,
				lblPublisher, lblSeries, lblAddress, lblEdition, lblHowpublished,
				lblABooktitle, lblEditor, lblChapter, lblSchool, lblInstitution, lblOrganization,
				listViewEntries, listViewAuthors, btnCancel, btnSave
			};

			for each (System::Windows::Forms::Control^ control in controls) {
				control->ForeColor = System::Drawing::Color::White;
			}
		}
	}

	void MainForm::OpenPDF()
	{
		Assembly^ assembly = Assembly::GetExecutingAssembly();

		// Lese die eingebettete PDF-Ressource als Stream
		Stream^ pdfStream = assembly->GetManifestResourceStream("PDF_file.pdf");

		if (pdfStream != nullptr)
		{
			// Temporäre Datei erstellen
			String^ tempFilePath = Path::GetTempFileName() + ".pdf";

			// PDF-Daten in die temporäre Datei schreiben
			FileStream^ fileStream = gcnew FileStream(tempFilePath, FileMode::Create, FileAccess::Write);
			pdfStream->CopyTo(fileStream);
			fileStream->Close();

			// PDF öffnen
			Process::Start(tempFilePath);

		}
		else
		{
			if (en_de == 0) {
				MessageBox::Show(nachrichten[41, 0]);
			}
			else if (en_de == 1) {
				MessageBox::Show(nachrichten[41, 1]);
			}

		}
	}

	void MainForm::ExportToBib() 
	{
		int n;  // Zähler für Einträge 
		n = 0; // Setze den Zähler auf 0
		int size = entries->Count; // Anzahl der Einträge (Größe des Arrays)

		//meins
		SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
		saveFileDialog->Filter = "Bib Dateien (*.bib)|*.bib"; //nur.bib-Dateien können gespeichert werden
		saveFileDialog->Title = "Speicher die Bib-Datei";  // Titel des Speicherdialogs
		if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) { // Wenn der Benutzer im Dialog auf OK klickt

			String^ filePath = saveFileDialog->FileName; // Der ausgewählte Dateipfad wird gespeichert


			FILE* Quelle; // Datei zum Schreiben öffnen
			Quelle = fopen((const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(filePath), "w"); // Konvertiere den Dateipfad von einem managed String zu einem C-String

			while (n < size) // Schleife die durch alle Einträge in der Liste läuft
			{

				fprintf(Quelle, "@%s{%s", entries[n]->type, entries[n]->keyword); // Beginne mit dem Schreiben eines Bib-Eintrags

				// Überprüft, ob die Felder gefüllt sind und wenn ja schreibe dann in die Datei
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

				fprintf(Quelle, "\n}\n\n"); // Schließt den Bib-Eintrag ab

				n++; // Erhöht den Zähler für den nächsten Eintrag

			}
			fclose(Quelle); // Schließt die Datei nach dem Schreiben
		}
	}

	void MainForm::UpdateAuthorString(int index, String^ updatedEntry, TextBox^ storageTextBox) {
		// Den Speicherstring in Einträge aufteilen
		array<String^>^ authorEntries = storageTextBox->Text->Split(gcnew array<String^> { " and " }, StringSplitOptions::None);

		if (index >= 0 && index < authorEntries->Length) {
			authorEntries[index] = updatedEntry; // Den spezifischen Eintrag aktualisieren
		}

		storageTextBox->Text = String::Join(" and ", authorEntries);// Den Speicherstring neu zusammensetzen
	}

	void MainForm::SetAuthor() 
	{
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
		if (rbtnAuthor->Checked) {
			if (listViewAuthors->SelectedItems->Count > 0) { //geht immer in diese if Abfrage
				int selectedIndex = listViewAuthors->SelectedIndices[0];
				listViewAuthors->Items[selectedIndex]->Text = fullName;

				UpdateAuthorString(selectedIndex, fullName, txtAuthor);
				listViewAuthors->SelectedIndices->Clear();// Index wird zurückgesetzt
			}
			else {
				listViewAuthors->Items->Add(fullName);// Neuen Eintrag hinzufügen
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
				listViewAuthors->Items->Add(fullName);// Neuen Eintrag hinzufügen
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

	void MainForm::ValidateSave() 
	{
		if (ValidateEntry() && ValidateOptional()) {
			currentEntry->type = cmbType->SelectedItem->ToString();

			// Existierende Einträge bereinigen
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

			// Ausgewählten Typen holen
			String^ selectedType = cmbType->SelectedItem->ToString();
			DataTypeFields^ selectedTypeFields = nullptr;

			// Find ausgewählten Typen in dataTypes finden
			for each (DataTypeFields^ type in dataTypes) {
				if (type->TypeName == selectedType) {
					selectedTypeFields = type;
					break;
				}
			}

			if (selectedTypeFields != nullptr) {
				// Werte für erforderliche Felder zuweisen
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

				// Werte für optionale Felder zuweisen
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

				// Hinzufügen oder updaten des Eintrags
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

}