//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
  G4double env_sizeXY = 20*cm, env_sizeZ = 20*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Envelope
  //  
  G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
  //     
  // Shape 1_1   Ge Detector
  //  
  G4Material* shape1_1_mat = nist->FindOrBuildMaterial("G4_Ge");
  G4ThreeVector pos1_1 = G4ThreeVector(0, 0*cm, 2.7*cm);
        
  // Conical section shape       
  G4double shape1_1_rmina =  0*cm, shape1_1_rmaxa = 4.5*cm;
  G4double shape1_1_rminb =  0*cm, shape1_1_rmaxb = 4.5*cm;
  G4double shape1_1_hz = 1.5*cm;
  G4double shape1_1_phimin = 0.*deg, shape1_1_phimax = 360.*deg;
  G4Cons* solidShape1_1 =    
    new G4Cons("Shape1_1", 
    shape1_1_rmina, shape1_1_rmaxa, shape1_1_rminb, shape1_1_rmaxb, shape1_1_hz,
    shape1_1_phimin, shape1_1_phimax);
                      
  G4LogicalVolume* logicShape1_1 =                         
    new G4LogicalVolume(solidShape1_1,         //its solid
                        shape1_1_mat,          //its material
                        "Shape1_1");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos1_1,                    //at position
                    logicShape1_1,             //its logical volume
                    "Shape1_1",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  //     
  // Shape 1_1   Ge Detector passivation layer
  //  


  G4Material* shape1_2_mat = nist->FindOrBuildMaterial("G4_Ge");
  
        
  // Conical section shape       
  G4double shape1_2_rmina =  0*cm, shape1_2_rmaxa = 4.5*cm;
  G4double shape1_2_rminb =  0*cm, shape1_2_rmaxb = 4.5*cm;
  G4double shape1_2_hz = 0.00005*cm;
  G4double shape1_2_phimin = 0.*deg, shape1_2_phimax = 360.*deg;
  G4ThreeVector pos1_2 = G4ThreeVector(0, 0*cm, 1.2-shape1_2_hz*cm);
  G4Cons* solidShape1_2 =    
    new G4Cons("Shape1_2", 
    shape1_2_rmina, shape1_2_rmaxa, shape1_2_rminb, shape1_2_rmaxb, shape1_2_hz,
    shape1_2_phimin, shape1_2_phimax);
                      
  G4LogicalVolume* logicShape1_2 =                         
    new G4LogicalVolume(solidShape1_2,         //its solid
                        shape1_2_mat,          //its material
                        "Shape1_2");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos1_2,                    //at position
                    logicShape1_2,             //its logical volume
                    "Shape1_2",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  //     
  // Shape 2   Carbon window
  //
  G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_C");
  G4ThreeVector pos2 = G4ThreeVector(0*cm, 0*cm, 0*cm);

  // Trapezoid shape      
  G4double shape2_rmina =  0*cm, shape2_rmaxa = 4.6*cm;
  G4double shape2_rminb =  0*cm, shape2_rmaxb = 4.6*cm;
  G4double shape2_hz = 0.03*cm;
  G4double shape2_phimin = 0.*deg, shape2_phimax = 360.*deg;
   
  /*G4double shape2_dxa = 6*cm, shape2_dxb = 8*cm;
  G4double shape2_dya = 6*cm, shape2_dyb = 8*cm;
  G4double shape2_dz  = 12*cm;   */   
  G4Cons* solidShape2 =    
    new G4Cons("Shape2",                      //its name
              shape2_rmina, shape2_rmaxa, shape2_rminb, shape2_rmaxb, shape2_hz,
    shape2_phimin, shape2_phimax);
                
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
                        shape2_mat,          //its material
                        "Shape2");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Shape2",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  //     
  // Shape 3     Al frame
  //
  G4Material* shape3_mat = nist->FindOrBuildMaterial("G4_Al");
  G4ThreeVector pos3 = G4ThreeVector(0*cm, 0*cm, 1.*cm);
     
  G4double shape3_1rmina =  0.*cm, shape3_1rmaxa = 5.9*cm;
  G4double shape3_1rminb =  0.*cm, shape3_1rmaxb = 5.9*cm;
  G4double shape3_1hz = 0.05*cm;
  G4double shape3_1phimin = 0.*deg, shape3_1phimax = 360.*deg;
  
  G4Cons* solidShape3_1 =    
    new G4Cons("Shape3_1",                      //its name
              shape3_1rmina, shape3_1rmaxa, shape3_1rminb, shape3_1rmaxb, shape3_1hz,
    shape3_1phimin, shape3_1phimax);
  
  G4ThreeVector Transition(0.*cm, 0.*cm, 0.*cm);
  G4double shape3_2rmina =  0.*cm, shape3_2rmaxa = 4.505*cm;
  G4double shape3_2rminb =  0.*cm, shape3_2rmaxb = 4.505*cm;
  G4double shape3_2hz = 0.06*cm;
  G4double shape3_2phimin = 0.*deg, shape3_2phimax = 180.*deg;

  G4Cons* solidShape3_2 =    
    new G4Cons("Shape3_2",                      //its name
              shape3_2rmina, shape3_2rmaxa, shape3_2rminb, shape3_2rmaxb, shape3_2hz,
    shape3_2phimin, shape3_2phimax);


  G4SubtractionSolid*  solidShape3 =                         
    new G4SubtractionSolid("solidShape3",
                        solidShape3_1,         
                        solidShape3_2,
                        0,         
                        Transition);           

  G4LogicalVolume* logicShape3 =                         
  new G4LogicalVolume(solidShape3,         //its solid
                      shape3_mat,          //its material
                      "Shape3");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos3,                    //at position
                    logicShape3,             //its logical volume
                    "Shape3",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  /*//     
  // Shape 4     Pb
  //
  G4Material* shape4_mat = nist->FindOrBuildMaterial("G4_Pb");
  G4ThreeVector pos4 = G4ThreeVector(0*cm, 0*cm, -1.2*cm);

  // Trapezoid shape      
  G4double shape4_rmina =  0.1*cm, shape4_rmaxa = 4*cm;
  G4double shape4_rminb =  0.1*cm, shape4_rmaxb = 4*cm;
  G4double shape4_hz = 1*cm;
  G4double shape4_phimin = 0.*deg, shape4_phimax = 360.*deg;
   

  G4Cons* solidShape4 =    
    new G4Cons("Shape4",                      //its name
              shape4_rmina, shape4_rmaxa, shape4_rminb, shape4_rmaxb, shape4_hz,
    shape4_phimin, shape4_phimax);
                
  G4LogicalVolume* logicShape4 =                         
    new G4LogicalVolume(solidShape4,         //its solid
                        shape4_mat,          //its material
                        "Shape4");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos4,                    //at position
                    logicShape4,             //its logical volume
                    "Shape4",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //     
  // Shape 5     Pb
  //
  G4Material* shape5_mat = nist->FindOrBuildMaterial("G4_Pb");
  G4ThreeVector pos5 = G4ThreeVector(0*cm, 0*cm, -2.7*cm);

  // Trapezoid shape      
  G4double shape5_rmina =  0*cm, shape5_rmaxa = 4*cm;
  G4double shape5_rminb =  0*cm, shape5_rmaxb = 4*cm;
  G4double shape5_hz = 0.5*cm;
  G4double shape5_phimin = 0.*deg, shape5_phimax = 360.*deg;
   

  G4Cons* solidShape5 =    
    new G4Cons("Shape5",                      //its name
              shape5_rmina, shape5_rmaxa, shape5_rminb, shape5_rmaxb, shape5_hz,
    shape5_phimin, shape5_phimax);
                
  G4LogicalVolume* logicShape5 =                         
    new G4LogicalVolume(solidShape5,         //its solid
                        shape5_mat,          //its material
                        "Shape5");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos5,                    //at position
                    logicShape5,             //its logical volume
                    "Shape5",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
*/
  // Set Shape1 as scoring volume
  //

  //     
  // Shape 6   half round Al shield
  //
  G4Material* shape6_mat = nist->FindOrBuildMaterial("G4_Al");
  G4ThreeVector pos6 = G4ThreeVector(0*cm, 0*cm, 1.0*cm);
  
  G4double shape6_rmina =  0*cm, shape6_rmaxa = 4.505*cm;
  G4double shape6_rminb =  0*cm, shape6_rmaxb = 4.505*cm;
  G4double shape6_hz = 0.005*cm;
  G4double shape6_phimin = 0.*deg, shape6_phimax = 180.*deg;
   
  /*G4double shape2_dxa = 6*cm, shape2_dxb = 8*cm;
  G4double shape2_dya = 6*cm, shape2_dyb = 8*cm;
  G4double shape2_dz  = 12*cm;   */   
  G4Cons* solidShape6 =    
    new G4Cons("Shape6",                      //its name
              shape6_rmina, shape6_rmaxa, shape6_rminb, shape6_rmaxb, shape6_hz,
    shape6_phimin, shape6_phimax);
                
  G4LogicalVolume* logicShape6 =                         
    new G4LogicalVolume(solidShape6,         //its solid
                        shape6_mat,          //its material
                        "Shape6");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos6,                    //at position
                    logicShape6,             //its logical volume
                    "Shape6",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  fScoringVolume = logicShape1_1;  //set Ge detector as ScoringVolume

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
