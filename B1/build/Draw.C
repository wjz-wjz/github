
#include <stdio.h>
#include <stdlib.h>
#include <Riostream.h>

#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include "TChain.h"
#include "TROOT.h"

//
const char Path[200] = "/share/003/users/zhangzy/BEGe_BNU/RootFile/AllRoot/";
const char SingleRootPath[200] = "/share/003/users/zhangzy/BEGe_BNU/RootFile/SingleRoot/";
const char SavePath[200] = "/home/zhangzy/DataAnalysis/BEGe_BNU/";

void DrawESpec(double min, double max,int bin_num)
{
	TFile *f1 = new TFile("/home/wjz/geant4/work/B1/build/B1out.root");
	TTree *t1 = (TTree *)f1->Get("B1");
	TCanvas *cESpec = new TCanvas("B1", "B1", 1280, 720);
	cESpec->SetLogy();
	TH1 *hESpec = new TH1D("hESpec","B1", bin_num, min,max);
	t1->Project("hESpec", "ESpec[0]");
	TAxis *axis = hESpec->GetXaxis();
	axis->SetLimits(min*1000,max*1000);
	axis->SetTitle("Energy/keV");
	TAxis *axis2 = hESpec->GetYaxis();
	axis2->SetTitle("Count");
	hESpec->Draw("hist");
	// hESpec->Scale(1 / (EEnd - EStart) / 1000 * BinNumber / DetMass * (Mass * ThActiviey / 1000000 * 3600 * 24 / t1->GetEntries()));
}
