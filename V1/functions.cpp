#include "functions.h"
#include "Data.h"
using namespace System::Windows::Forms;

//typedef void(*SetFieldsReadOnlyPtr)(bool);

void V1::ClearEntryDetails(DataArray^ currentEntry, ComboBox^ cmbType, TextBox^ txtKeyword,
	TextBox^ txtAuthor, TextBox^ txtTitle, TextBox^ txtYear,
	TextBox^ txtJournal, TextBox^ txtVolume, TextBox^ txtNumber,
	TextBox^ txtPages, TextBox^ txtMonth, TextBox^ txtNote,
	TextBox^ txtPublisher, TextBox^ txtSeries, TextBox^ txtAddress,
	TextBox^ txtEdition, TextBox^ txtHowpublished, TextBox^ txtBooktitle,
	TextBox^ txtEditor, TextBox^ txtChapter, TextBox^ txtSchool,
	TextBox^ txtInstitution, TextBox^ txtOrganization/*,*/
	/*SetFieldsReadOnlyPtr setFieldsReadOnly*/)
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
	/*setFieldsReadOnly(false);*/

}
