// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
 
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
 
class MyFrame : public wxFrame
{
public:
    MyFrame();
 
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnButton(wxCommandEvent& event);
    wxButton* sendButton;
    wxTextCtrl* userInput; 
    wxTextCtrl* outputArea;
};
 
enum
{
    ID_Hello = 1
};
 
wxIMPLEMENT_APP(MyApp);
 
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
 
MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Trabalho de Redes", wxDefaultPosition, wxSize(400,300))
{
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    userInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    userInput->SetMaxLength(4096); 

    wxButton* sendButton = new wxButton(panel, wxID_ANY, "Send");

    inputSizer->Add(userInput, 1, wxEXPAND | wxALL, 10); 
    inputSizer->Add(sendButton, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10); 

    mainSizer->Add(inputSizer, 0, wxEXPAND | wxALL, 10); 

    outputArea = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
    outputArea->SetBackgroundColour(*wxWHITE); 

    mainSizer->Add(outputArea, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10); 

    panel->SetSizer(mainSizer);
    
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    menuHelp->AppendSeparator();
    menuHelp->Append(wxID_EXIT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    //menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
 
    CreateStatusBar();
    SetStatusText("Um trabalho de Eduardo, Gabriel, Guilherme e Vitor");
 
    sendButton->Bind(wxEVT_BUTTON, &MyFrame::OnButton, this);
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}
 
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("Trabalho de Redes da Professora Kalinka",
                 "Sobre", wxOK | wxICON_INFORMATION);
}
 
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

void MyFrame::OnButton(wxCommandEvent& event){
    wxString userText = userInput->GetValue(); 
    
    outputArea->AppendText("You entered: " + userText + "\n");

    outputArea->SetDefaultStyle(wxTextAttr(*wxBLUE, *wxWHITE)); // Set the text style for the system's response
    outputArea->AppendText("System: Message Received\n");

    userInput->Clear(); 
}