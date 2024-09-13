#pragma once
#include <string>
#include <vcclr.h>


namespace V1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Reflection;
	using namespace System::IO;
	using namespace System::Media; // Benötigt um Sound abzuspielen
	/// <summary>
	/// Zusammenfassung für SplashScreen
	/// </summary>

	public ref class SplashScreen : public System::Windows::Forms::Form
	{
	public:
		SplashScreen(void)
		{
			InitializeComponent();

			// Splashscreen zentral auf Bildschirm anzeigen
			this->StartPosition = FormStartPosition::CenterScreen;

			// Eingebettete HTML Animation laden
			Assembly^ assemblyHTML = Assembly::GetExecutingAssembly();
			Stream^ streamHTML = assemblyHTML->GetManifestResourceStream("SplashAnimation.html");
			StreamReader^ reader = gcnew StreamReader(streamHTML);
			String^ htmlContent = reader->ReadToEnd();

			// HTML Code in Browser laden
			webBrowser1->DocumentText = htmlContent;

			// Eingebettete Sounddatei laden
			Assembly^ assemblySound = Assembly::GetExecutingAssembly();
			Stream^ streamSound = assemblySound->GetManifestResourceStream("Startup.wav");

			// Startup Sound abspielen
			SoundPlayer^ player = gcnew SoundPlayer(streamSound);
			player->Play();
		

			// 5 Sekunden Timer starten
			System::Windows::Forms::Timer^ timer = gcnew System::Windows::Forms::Timer();
			timer->Interval = 5000; // 5 Sekunden
			timer->Tick += gcnew EventHandler(this, &SplashScreen::OnTimerTick);
			timer->Start();
		}

	private:
		void OnTimerTick(System::Object^ sender, System::EventArgs^ e) {
			// Splashscreen schließen wenn Timer abgelaufen ist
			((System::Windows::Forms::Timer^)sender)->Stop();
			this->Close();
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~SplashScreen()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::WebBrowser^  webBrowser1;
	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
			this->SuspendLayout();
			// 
			// webBrowser1
			// 
			this->webBrowser1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->webBrowser1->Location = System::Drawing::Point(0, 0);
			this->webBrowser1->MinimumSize = System::Drawing::Size(20, 20);
			this->webBrowser1->Name = L"webBrowser1";
			this->webBrowser1->Size = System::Drawing::Size(972, 495);
			this->webBrowser1->TabIndex = 0;
			this->webBrowser1->DocumentCompleted += gcnew System::Windows::Forms::WebBrowserDocumentCompletedEventHandler(this, &SplashScreen::webBrowser1_DocumentCompleted);
			// 
			// SplashScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(972, 495);
			this->Controls->Add(this->webBrowser1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"SplashScreen";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"SplashScreen";
			this->TopMost = true;
			this->UseWaitCursor = true;
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void webBrowser1_DocumentCompleted(System::Object^  sender, System::Windows::Forms::WebBrowserDocumentCompletedEventArgs^  e) {
	}
	};
}
