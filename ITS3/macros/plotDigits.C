#if !defined(__CLING__) || defined(__ROOTCLING__)
#include <memory>

#include <TROOT.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TPad.h>
#include <TTree.h>
#endif

#include "alicestyle.h"
using namespace alicestyle;

void plotDigits(const char* fName = "CheckDigits.root")
{
  setALICEStyle();

  std::unique_ptr<TFile> inFile(TFile::Open(fName));
  auto tree = inFile->Get<TTree>("ntd");

  float id; // chipID
  tree->SetBranchAddress("id", &id);
  float dz; // delta of digit z and hit z
  tree->SetBranchAddress("dz", &dz);
  float dx; // delta of digit x and hit x
  tree->SetBranchAddress("dx", &dx);
  float etaH; // eta of hit
  tree->SetBranchAddress("etaH", &etaH);

  const double etaMax{3.0}, etaDiv{0.5};
  auto hDzIB = new TH2F("hDzIB", "", 30, 0, etaMax, 200, -50, 50);
  hDzIB->GetXaxis()->SetNdivisions(6, 4, 0, false);
  auto hDxIB = new TH2F("hDxIB", "", 30, 0, etaMax, 200, -50, 50);
  hDxIB->GetXaxis()->SetNdivisions(6, 4, 0, false);
  auto hDzOB = new TH2F("hDzOB", "", 30, 0, etaMax, 200, -50, 50);
  hDzOB->GetXaxis()->SetNdivisions(6, 4, 0, false);
  auto hDxOB = new TH2F("hDxOB", "", 30, 0, etaMax, 200, -50, 50);
  hDxOB->GetXaxis()->SetNdivisions(6, 4, 0, false);

  for (int iEntry = 0; tree->LoadTree(iEntry) >= 0; ++iEntry) {
    tree->GetEntry(iEntry);
    if (id < 3456) {
      hDzIB->Fill(std::abs(etaH), dz * 1e4);
      hDxIB->Fill(std::abs(etaH), dx * 1e4);
    } else {
      hDzOB->Fill(std::abs(etaH), dz * 1e4);
      hDxOB->Fill(std::abs(etaH), dx * 1e4);
    }
  }

  { // IB
    aliceCanvas("InnerBarrel Digit dZ", 0, 1.5, -50, 50, "|eta_{Hit}|", "#Delta(z_{Hit} - z_{Digit}) (#mum)", false, false, false, true, 0, true, -999, hDzIB);
    aliceNormalize(hDzIB);
    aliceDrawTH2(hDzIB, true);
    adjustPaletteWidth(hDzIB);
    drawZTitle(hDzIB);
    drawThisThesis();
    saveCurrentCanvas("digitIBDeltaZ.pdf");
  }
  { // OB
    aliceCanvas("OuterBarrel Digit dZ", 0, 1.5, -50, 50, "|eta_{Hit}|", "#Delta(z_{Hit} - z_{Digit}) (#mum)", false, false, false, true, 0, true, -999, hDzOB);
    aliceNormalize(hDzOB);
    aliceDrawTH2(hDzOB, true);
    adjustPaletteWidth(hDzOB);
    drawZTitle(hDzOB);
    drawThisThesis();
    saveCurrentCanvas("digitOBDeltaZ.pdf");
  }
  { // IB
    aliceCanvas("InnerBarrel Digit dX", 0, 1.5, -50, 50, "|eta_{Hit}|", "#Delta(x_{Hit} - x_{Digit}) (#mum)", false, false, false, true, 0, true, -999, hDxIB);
    aliceNormalize(hDxIB);
    aliceDrawTH2(hDxIB, true);
    adjustPaletteWidth(hDxIB);
    drawZTitle(hDxIB);
    drawThisThesis();
    saveCurrentCanvas("digitIBDeltaX.pdf");
  }
  { // OB
    aliceCanvas("OuterBarrel Digit dX", 0, 1.5, -50, 50, "|eta_{Hit}|", "#Delta(x_{Hit} - x_{Digit}) (#mum)", false, false, false, true, 0, true, -999, hDxOB);
    aliceNormalize(hDxOB);
    aliceDrawTH2(hDxOB, true);
    adjustPaletteWidth(hDxOB);
    drawZTitle(hDxOB);
    drawThisThesis();
    saveCurrentCanvas("digitOBDeltaX.pdf");
  }
}
