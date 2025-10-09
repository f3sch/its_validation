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

  auto hDzIB = new TH2F("hDzIB", "", 100, 0, 1.5, 400, -25, 25);
  auto hDxIB = new TH2F("hDxIB", "", 100, 0, 1.5, 400, -25, 25);
  auto hDzOB = new TH2F("hDzOB", "", 100, 0, 1.5, 400, -25, 25);
  auto hDxOB = new TH2F("hDxOB", "", 100, 0, 1.5, 400, -25, 25);

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
    aliceCanvas("InnerBarrel Cluster dZ", 0, 1.5, -25, 25, "|eta_{Cluster}|", "#Delta(z_{Hit} - z_{Cluster}) (#mum)", false, false, false, true, 0, true, -999, hDzIB);
    aliceNormalize(hDzIB);
    aliceDrawTH2(hDzIB, true);
    adjustPaletteWidth(hDzIB);
    drawZTitle(hDzIB);
    drawThisThesis();
    saveCurrentCanvas("clusterIBDeltaZ.pdf");
  }
  { // OB
    aliceCanvas("OuterBarrel Cluster dZ", 0, 1.5, -25, 25, "|eta_{Cluster}|", "#Delta(z_{Hit} - z_{Cluster}) (#mum)", false, false, false, true, 0, true, -999, hDzOB);
    aliceNormalize(hDzOB);
    aliceDrawTH2(hDzOB, true);
    adjustPaletteWidth(hDzOB);
    drawZTitle(hDzOB);
    drawThisThesis();
    saveCurrentCanvas("clusterOBDeltaZ.pdf");
  }
  { // IB
    aliceCanvas("InnerBarrel Cluster dX", 0, 1.5, -25, 25, "|eta_{Cluster}|", "#Delta(x_{Hit} - x_{Cluster}) (#mum)", false, false, false, true, 0, true, -999, hDxIB);
    aliceNormalize(hDxIB);
    aliceDrawTH2(hDxIB, true);
    adjustPaletteWidth(hDxIB);
    drawZTitle(hDxIB);
    drawThisThesis();
    saveCurrentCanvas("clusterIBDeltaX.pdf");
  }
  { // OB
    aliceCanvas("OuterBarrel Cluster dX", 0, 1.5, -25, 25, "|eta_{Cluster}|", "#Delta(x_{Hit} - x_{Cluster }) (#mum)", false, false, false, true, 0, true, -999, hDxOB);
    aliceNormalize(hDxOB);
    aliceDrawTH2(hDxOB, true);
    adjustPaletteWidth(hDxOB);
    drawZTitle(hDxOB);
    drawThisThesis();
    saveCurrentCanvas("clusterOBDeltaX.pdf");
  }
}
