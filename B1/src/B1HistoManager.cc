#include "B1HistoManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
 : fFactoryOn(false)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  // Only merge in MT mode to avoid warning when running in Sequential mode
#ifdef G4MULTITHREADED
  analysisManager->SetNtupleMerging(true);
#endif

  // Create directories
  analysisManager->SetHistoDirectoryName("histo");

  // Open an output file
  //
  G4bool fileOpen = analysisManager->OpenFile("B1out");
  if (! fileOpen) {
    G4cerr << "\n---> HistoManager::Book(): cannot open "
           << analysisManager->GetFileName() << G4endl;
    return;
  }

  // Create histograms.
  // Histogram ids are generated automatically starting from 0.
  // The start value can be changed by:
  // analysisManager->SetFirstHistoId(1);

  // id = 0
  analysisManager->CreateH1("ESpec","Edep in Ge (keV)", 1000, 4.0*keV, 30.0*keV);
  
  analysisManager->CreateNtuple("B1", "Edep in Ge (keV)");
  analysisManager->CreateNtupleDColumn("ESpec");
  analysisManager->FinishNtuple();
  
  fFactoryOn = true;

  G4cout << "\n----> Output file is open in "
         << analysisManager->GetFileName() << "."
         << analysisManager->GetFileType() << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Save()
{
  if (! fFactoryOn) return;

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

  G4cout << "\n----> Histograms and ntuples are saved\n" << G4endl;

  delete G4AnalysisManager::Instance();
  fFactoryOn = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::FillHisto(G4int ih, G4double xbin, G4double weight)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(ih, xbin, weight);
}

void HistoManager::FillNtuple(G4double energy)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // Fill 1st ntuple ( id = 0)
  analysisManager->FillNtupleDColumn(0, 0, energy);
  analysisManager->AddNtupleRow(0);

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

