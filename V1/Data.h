#pragma once

using namespace System;
using namespace System::Collections::Generic; // For List<T>

namespace DataNamespace {
	[Serializable]
	// Define DataArray as a managed type
	public ref class DataArray {
	public:
		String^ keyword;
		String^ title;
		String^ journal;
		String^ year;
		String^ author;
		String^ volume;
		String^ number;
		String^ pages;
		String^ month;
		String^ note;
		String^ publisher;
		String^ series;
		String^ address;
		String^ edition;
		String^ howpublished;
		String^ booktitle;
		String^ editor;
		String^ chapter;
		String^ school;
		String^ institution;
		String^ organization;
		String^ type; // To store the entry type (e.g., article, book, etc.)

		DataArray() {
			keyword = "";
			title = "";
			journal = "";
			year = "";
			author = "";
			volume = "";
			number = "";
			pages = "";
			month = "";
			note = "";
			publisher = "";
			series = "";
			address = "";
			edition = "";
			howpublished = "";
			booktitle = "";
			editor = "";
			chapter = "";
			school = "";
			institution = "";
			organization = "";
			type = "";
		}
	};

	// Define DataTypeFields as a managed type with a constructor
	public ref struct DataTypeFields {
		String^ TypeName;
		array<String^>^ RequiredFields;
		array<String^>^ OptionalFields;

		// Constructor to initialize the fields
		DataTypeFields(String^ typeName, array<String^>^ requiredFields, array<String^>^ optionalFields) {
			TypeName = typeName;
			RequiredFields = requiredFields;
			OptionalFields = optionalFields;
		}
	};

	// Function to initialize and return the data types
	inline array<DataTypeFields^>^ GetDataTypes() {
		return gcnew array<DataTypeFields^> {
			gcnew DataTypeFields("article",
				gcnew array<String^>{"keyword", "title", "journal", "year", "author"}, // Mandatory fields
				gcnew array<String^>{"volume", "number", "pages", "month", "note"}     // Optional fields
			),
				gcnew DataTypeFields("book",
					gcnew array<String^>{"keyword", "title", "publisher", "year", "author", "editor"},
					gcnew array<String^>{"volume", "series", "address", "edition", "month", "note"}
			),
				gcnew DataTypeFields("booklet",
					gcnew array<String^>{"keyword", "title"},
					gcnew array<String^>{"howpublished", "address", "month", "year", "note"}
			),
				gcnew DataTypeFields("conference",
					gcnew array<String^>{"keyword", "title", "booktitle", "year", "author"},
					gcnew array<String^>{"editor", "pages", "organization", "publisher", "address", "month", "note"}
			),
				gcnew DataTypeFields("inbook",
					gcnew array<String^>{"keyword", "title", "chapter/pages", "publisher", "year", "author", "editor"},
					gcnew array<String^>{"volume", "series", "address", "edition", "month", "note"}
			),
				gcnew DataTypeFields("incollection",
					gcnew array<String^>{"keyword", "title", "booktitle", "publisher", "year", "author"},
					gcnew array<String^>{"editor", "chapter", "pages", "address", "month", "note"}
			),
				gcnew DataTypeFields("inproceedings",
					gcnew array<String^>{"keyword", "title", "booktitle", "year", "author"},
					gcnew array<String^>{"editor", "pages", "organization", "publisher", "address", "month", "note"}
			),
				gcnew DataTypeFields("manual",
					gcnew array<String^>{"keyword", "title"},
					gcnew array<String^>{"organization", "address", "edition", "month", "year", "note"}
			),
				gcnew DataTypeFields("mastersthesis",
					gcnew array<String^>{"keyword", "title", "school", "year", "author"},
					gcnew array<String^>{"address", "month", "note"}
			),
				gcnew DataTypeFields("misc",
					gcnew array<String^>{"keyword"},
					gcnew array<String^>{"title", "howpublished", "month", "year", "note"}
			),
				gcnew DataTypeFields("phdthesis",
					gcnew array<String^>{"keyword", "title", "school", "year", "author"},
					gcnew array<String^>{"address", "month", "note"}
			),
				gcnew DataTypeFields("proceedings",
					gcnew array<String^>{"keyword", "title", "year"},
					gcnew array<String^>{"editor", "publisher", "organization", "address", "month", "note"}
			),
				gcnew DataTypeFields("techreport",
					gcnew array<String^>{"keyword", "title", "institution", "year", "author"},
					gcnew array<String^>{"type", "number", "address", "month", "note"}
			),
				gcnew DataTypeFields("unpublished",
					gcnew array<String^>{"keyword", "title", "note", "author"},
					gcnew array<String^>{"month", "year"}
			)
		};
	}
}
