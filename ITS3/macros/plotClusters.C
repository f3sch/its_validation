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

void plotClusters(const char* fName = "CheckClusters.root")
{
  setALICEStyle();

  std::unique_ptr<TFile> inFile(TFile::Open(fName));
  auto tree = inFile->Get<TTree>("ntc");

  float id; // chipID
  tree->SetBranchAddress("id", &id);
  float dz; // delta of digit z and hit z
  tree->SetBranchAddress("dz", &dz);
  float dx; // delta of digit x and hit x
  tree->SetBranchAddress("dx", &dx);
  float eta; // eta of cluster
  tree->SetBranchAddress("eta", &eta);

  const double etaMax{3.0}, etaDiv{0.5};
  auto hDzIB = new TH2F("hDzIB", "", 30, 0, etaMax, 200, -25, 25);
  hDzIB->GetXaxis()->SetNdivisions(6, 4, 0, false);
  auto hDxIB = new TH2F("hDxIB", "", 30, 0, etaMax, 200, -25, 25);
  hDxIB->GetXaxis()->SetNdivisions(6, 4, 0, false);
  auto hDzOB = new TH2F("hDzOB", "", 30, 0, etaMax, 200, -25, 25);
  hDzOB->GetXaxis()->SetNdivisions(6, 4, 0, false);
  auto hDxOB = new TH2F("hDxOB", "", 30, 0, etaMax, 200, -25, 25);
  hDxOB->GetXaxis()->SetNdivisions(6, 4, 0, false);

  for (int iEntry = 0; tree->LoadTree(iEntry) >= 0; ++iEntry) {
    tree->GetEntry(iEntry);
    if (id < 3456) {
      hDzIB->Fill(std::abs(eta), dz * 1e4);
      hDxIB->Fill(std::abs(eta), dx * 1e4);
    } else {
      hDzOB->Fill(std::abs(eta), dz * 1e4);
      hDxOB->Fill(std::abs(eta), dx * 1e4);
    }
  }

  { // IB
    aliceCanvas("InnerBarrel Cluster dZ", 0, etaMax, -25, 25, "|eta_{Hit}|", "#Delta(z_{Hit} - z_{Cluster COG}) (#mum)", false, false, false, true, 0, true, -999, hDzIB);
    aliceNormalize(hDzIB);
    aliceDrawTH2(hDzIB, true);
    adjustPaletteWidth(hDzIB);
    drawZTitle(hDzIB);
    drawThisThesis();
    saveCurrentCanvas("clusterIBDeltaZ.pdf");
  }
  { // OB
    aliceCanvas("OuterBarrel Cluster dZ", 0, etaMax, -25, 25, "|eta_{Hit}|", "#Delta(z_{Hit} - z_{Cluster COG}) (#mum)", false, false, false, true, 0, true, -999, hDzOB);
    aliceNormalize(hDzOB);
    aliceDrawTH2(hDzOB, true);
    adjustPaletteWidth(hDzOB);
    drawZTitle(hDzOB);
    drawThisThesis();
    saveCurrentCanvas("clusterOBDeltaZ.pdf");
  }
  { // IB
    aliceCanvas("InnerBarrel Cluster dX", 0, etaMax, -25, 25, "|eta_{Hit}|", "#Delta(x_{Hit} - x_{Cluster COG}) (#mum)", false, false, false, true, 0, true, -999, hDxIB);
    aliceNormalize(hDxIB);
    aliceDrawTH2(hDxIB, true);
    adjustPaletteWidth(hDxIB);
    drawZTitle(hDxIB);
    drawThisThesis();
    saveCurrentCanvas("clusterIBDeltaX.pdf");
  }
  { // OB
    aliceCanvas("OuterBarrel Cluster dX", 0, etaMax, -25, 25, "|eta_{Hit}|", "#Delta(x_{Hit} - x_{Cluster COG}) (#mum)", false, false, false, true, 0, true, -999, hDxOB);
    aliceNormalize(hDxOB);
    aliceDrawTH2(hDxOB, true);
    adjustPaletteWidth(hDxOB);
    drawZTitle(hDxOB);
    drawThisThesis();
    saveCurrentCanvas("clusterOBDeltaX.pdf");
  }
}
