#include "alicestyle.h"

using namespace alicestyle;

// Uses output from the PlotDCA macro to produce impact parameter & pt resolution for ITS & ITS-TPC tracks

void plotResolution()
{
  setALICEStyle();

  const std::string fName = "plotDCA.root";
  TFile* inFile = TFile::Open(fName.c_str(), "READ");

  { // DCAxy
    auto hITS = dynamic_cast<TH1F*>(inFile->Get("Pions/ITS/hResDCAxyVsPtAllLayers_Pions_ITS"));
    auto hITSTPC = dynamic_cast<TH1F*>(inFile->Get("Pions/ITSTPC/hResDCAxyVsPtAllLayers_Pions_ITSTPC"));
    aliceCanvas("Pion DCA_{xy} resolution", hITS->GetXaxis()->GetXmin(), hITS->GetXaxis()->GetXmax(), 1, 1000, "#it{p}_{T,MC} (GeV/#it{c})", "#sigma(DCA_{xy}) (#mum)", true, true, true);
    aliceDrawHist(hITS, kALICERed, kALICECircle);
    aliceDrawHist(hITSTPC, kALICEBlue, kALICESquare);
    auto leg = aliceLeg(0.65, 0.75, 0.88, 0.88);
    leg->AddEntry(hITS, "ITS", "pl");
    leg->AddEntry(hITSTPC, "ITS-TPC", "pl");
    saveCurrentCanvas("dcaXYRes.pdf");
  }
  { // DCAz
    auto hITS = dynamic_cast<TH1F*>(inFile->Get("Pions/ITS/hResDCAzVsPtAllLayers_Pions_ITS"));
    auto hITSTPC = dynamic_cast<TH1F*>(inFile->Get("Pions/ITSTPC/hResDCAzVsPtAllLayers_Pions_ITSTPC"));
    aliceCanvas("Pion DCA_{z} resolution", hITS->GetXaxis()->GetXmin(), hITS->GetXaxis()->GetXmax(), 1, 1000, "#it{p}_{T,MC} (GeV/#it{c})", "#sigma(DCA_{z}) (#mum)", true, true, true);
    aliceDrawHist(hITS, kALICERed, kALICECircle);
    aliceDrawHist(hITSTPC, kALICEBlue, kALICESquare);
    auto leg = aliceLeg(0.65, 0.75, 0.88, 0.88);
    leg->AddEntry(hITS, "ITS", "pl");
    leg->AddEntry(hITSTPC, "ITS-TPC", "pl");
    saveCurrentCanvas("dcaZRes.pdf");
  }
  { // Pt
    auto hITS = dynamic_cast<TH1F*>(inFile->Get("Pions/ITS/hResDeltaPtVsPtAllLayers_Pions_ITS"));
    auto hITSTPC = dynamic_cast<TH1F*>(inFile->Get("Pions/ITSTPC/hResDeltaPtVsPtAllLayers_Pions_ITSTPC"));
    aliceCanvas("Pion #it{p}_{T} resolution", hITS->GetXaxis()->GetXmin(), hITS->GetXaxis()->GetXmax(), 0.001, 1, "#it{p}_{T,MC} (GeV/#it{c})", "#sigma(#Delta#it{p}_{T}/#it{p}_{T})", true, true, true);
    aliceDrawHist(hITS, kALICERed, kALICECircle);
    aliceDrawHist(hITSTPC, kALICEBlue, kALICESquare);
    auto leg = aliceLeg(0.65, 0.75, 0.88, 0.88);
    leg->AddEntry(hITS, "ITS", "pl");
    leg->AddEntry(hITSTPC, "ITS-TPC", "pl");
    saveCurrentCanvas("ptRes.pdf");
  }
}
