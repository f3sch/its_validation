#include "alicestyle.h"
using namespace alicestyle;
// Uses output from the PlotDCA macro to produce impact parameter & pt resolution for ITS & ITS-TPC tracks
void plotPulls()
{
  setALICEStyle();

  const std::string fName = "plotPulls.root";
  TFile* inFile = TFile::Open(fName.c_str(), "READ");

  { // Pulls
    const char* pNames[5] = {"Y", "Z", "Snp", "Tgl", "Q2Pt"};
    for (int i{0}; i < 5; ++i) {
      auto mean = inFile->Get<TH1F>(Form("hPull%sMean", pNames[i]));
      auto sigma = inFile->Get<TH1F>(Form("hPull%sSigma", pNames[i]));
      aliceCanvas(Form("Pion Pull %s distribution", pNames[i]), mean->GetXaxis()->GetBinLowEdge(2), mean->GetXaxis()->GetXmax(), -3, 3, "#it{p}_{T}^{MC} (GeV/#it{c})", "", true, true, false);
      aliceDrawHist(mean, P6::kBlue, kALICESquare);
      aliceDrawHist(sigma, P6::kRed, kALICECircle);
      auto leg = aliceLeg(0.23, 0.18, 0.33, 0.4, 0, true, true);
      leg->AddEntry(mean, "#mu", "p");
      leg->AddEntry(sigma, "#sigma", "p");
      drawThisThesis();
      saveCurrentCanvas(Form("pull%s.pdf", pNames[i]));
    }
  }
  { // Mahalanobis distance
    auto h = inFile->Get<TH1F>("hMahDist2");
    auto fit = inFile->Get<TF1>("fchi2_fit");
    auto c = aliceCanvas("Mahalanobis distance", h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetXmax(), 0, 0.3, "Mahalanobis distance", "n. entries", false, false, false);
    c->getFrame()->GetYaxis()->SetTitleOffset(1.35);
    aliceDrawHist(h, P6::kBlue, 0);
    aliceDrawTF1(fit, P6::kRed, kDashed);
    drawFitInfo(fit, 0.60, 0.65);
    auto leg = aliceLeg(0.49, 0.70, 0.88, 0.88, 0, true, true);
    leg->AddEntry(h, "Mahalanobis distance", "le");
    leg->AddEntry(fit, "#chi^{2} fit", "l");
    drawThisThesis();
    saveCurrentCanvas("pullMahalanobis.pdf");
  }
}
