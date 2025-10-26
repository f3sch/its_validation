#include "alicestyle.h"
using namespace alicestyle;
void plotEff()
{
  setALICEStyle();
  const std::string fName = "CheckTracksCA.root";
  TFile* inFile = TFile::Open(fName.c_str(), "READ");
  auto hDen = inFile->Get<TH1D>("den");
  auto hFake = inFile->Get<TH1D>("fak");
  auto hNum = inFile->Get<TH1D>("num");
  auto hSum = (TH1D*)hNum->Clone("sum");
  hSum->Add(hFake);
  hNum->Divide(hNum, hDen, 1., 1., "B");
  hFake->Divide(hFake, hDen, 1., 1., "B");
  hSum->Divide(hSum, hDen, 1., 1., "B");
  for (int iBin{1}; iBin <= hSum->GetXaxis()->GetNbins(); ++iBin) {
    if (hSum->GetBinContent(iBin) > 1.0) {
      hSum->SetBinContent(iBin, 1.0);
    }
  }
  aliceCanvas("ITS2 efficiency", 0.01, 10, 0.01, 1.05, "#it{p}_{T}^{MC} (GeV/c)", "Efficiency (fake-track rate)", true, true, true);
  auto colors = getPettroffColorSet(3);
  aliceDrawHist(hNum, colors[0], -1, -1);
  aliceDrawHist(hFake, colors[1], -1, 3005);
  aliceDrawHist(hSum, colors[2]);
  drawSimulationInfo("Pb-Pb", "5.36", "0.5", "50 kHz", true, 0.68, 0.9);
  auto leg = aliceLeg(0.7, 0.3, 0.92, 0.5, 0, true, true);
  leg->AddEntry(hNum, "Good tracks", "l");
  leg->AddEntry(hFake, "Fake tracks", "l");
  leg->AddEntry(hSum, "Sum of tracks", "l");
  saveCurrentCanvas("eff.pdf");
}
