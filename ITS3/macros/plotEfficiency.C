#if !defined(__CLING__) || defined(__ROOTCLING__)
#include <cmath>

#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TF1.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <THStack.h>
#include <TLegend.h>
#include <TPad.h>
#include <TROOT.h>
#include <TStyle.h>
#endif

#include "alicestyle.h"
using namespace alicestyle;

struct ParticleInfo {
  int event;
  int pdg;
  float pt;
  float recpt;
  float eta;
  float phi;
  float pvx;
  float pvy;
  float pvz;
  float dcaxy;
  float dcaz;
  int mother;
  int first;
  unsigned short clusters = 0u;
  unsigned char isReco = 0u;
  unsigned char isFake = 0u;
  bool isPrimary = 0u;
  unsigned char storedStatus = 2; /// not stored = 2, fake = 1, good = 0
  o2::its::TrackITS track;
};

void plotEfficiency(const char* fName = "CheckTracksITS3.root")
{
  setALICEStyle();

  std::unique_ptr<TFile> inFile(TFile::Open(fName));
  auto tree = inFile->Get<TTree>("ParticleInfo");
  ParticleInfo* part = nullptr;
  tree->SetBranchAddress("particle", &part);

  const int nPtBinsEff = 39;
  double ptLimitsEff[nPtBinsEff] = {0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.6, 0.7, 0.8, 0.9, 1., 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2., 2.2, 2.5, 3., 4., 5., 6., 8., 10., 15., 20.};

  const int PDG = 211;

  auto hNum = new TH1F("hNum", ";#it{p}_{T} (GeV/#it{c});counts", nPtBinsEff - 1, ptLimitsEff);
  auto hFak = new TH1F("hFak", ";#it{p}_{T} (GeV/#it{c});counts", nPtBinsEff - 1, ptLimitsEff);
  auto hDen = new TH1F("hDen", ";#it{p}_{T} (GeV/#it{c});counts", nPtBinsEff - 1, ptLimitsEff);

  for (int iEntry = 0; tree->LoadTree(iEntry) >= 0; ++iEntry) {
    tree->GetEntry(iEntry);
    auto absEta = std::abs(part->eta);
    auto pdg = std::abs(part->pdg);
    if (!part->isPrimary || pdg != PDG || absEta > 1. || (part->clusters & 0x7f) != 0x7f) {
      continue;
    }
    hDen->Fill(part->pt);

    if (!part->isReco && !part->isFake) { // we also accept the fakes
      continue;
    }
    if (part->isReco) {
      hNum->Fill(part->pt);
    } else {
      hFak->Fill(part->pt);
    }
  }

  auto hEffGood = (TH1F*)hNum->Clone("hEffGood");
  auto hEffFake = (TH1F*)hFak->Clone("hEffFake");
  auto hEffSum = (TH1F*)hNum->Clone("hEffSum");
  hEffSum->Add(hFak);
  hEffGood->Divide(hEffGood, hDen, 1., 1., "B");
  hEffFake->Divide(hEffFake, hDen, 1., 1., "B");
  hEffSum->Divide(hEffSum, hDen, 1., 1., "B");

  aliceCanvas("Tracking Efficiency", ptLimitsEff[0], ptLimitsEff[nPtBinsEff - 1], .01, 1.1, "#it{p}_{T} (GeV/#it{c})", "Efficiency (Fake-rate)", true, true, true);
  auto colors = getPettroffColorSet(3);
  aliceDrawHist(hEffGood, colors[0], kAllMarkers[0]);
  aliceDrawHist(hEffFake, colors[1], kAllMarkers[1]);
  aliceDrawHist(hEffSum, colors[2], kAllMarkers[2]);
  drawThisThesis();
  auto leg = aliceLeg(0.5, 0.3, 0.8, 0.6, 0, true);
  leg->AddEntry(hEffSum, "Sum", "p");
  leg->AddEntry(hEffGood, "Good", "p");
  leg->AddEntry(hEffFake, "Fake", "p");
  saveCurrentCanvas("effPion.pdf");
}
