//functions.h
#include "Data.h"

#pragma once
using namespace DataNamespace;
using namespace System::Windows::Forms;

namespace V1 {
	void ClearEntryDetails(DataArray^ currentEntry, ComboBox^ cmbType, TextBox^ txtKeyword,
		TextBox^ txtAuthor, TextBox^ txtTitle, TextBox^ txtYear,
		TextBox^ txtJournal, TextBox^ txtVolume, TextBox^ txtNumber,
		TextBox^ txtPages, TextBox^ txtMonth, TextBox^ txtNote,
		TextBox^ txtPublisher, TextBox^ txtSeries, TextBox^ txtAddress,
		TextBox^ txtEdition, TextBox^ txtHowpublished, TextBox^ txtBooktitle,
		TextBox^ txtEditor, TextBox^ txtChapter, TextBox^ txtSchool,
		TextBox^ txtInstitution, TextBox^ txtOrganization/*,*/
		/*SetFieldsReadOnlyPtr setFieldsReadOnly*/);
}