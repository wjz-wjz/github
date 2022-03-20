#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"

#include "g4root.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoManager
{
  public:
    HistoManager();
   ~HistoManager();

    void Book();
    void Save();
    
    void FillHisto(G4int id, G4double e, G4double weight = 1.0);
   
    void FillNtuple(G4double engery);
  private:
    G4bool fFactoryOn;    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

