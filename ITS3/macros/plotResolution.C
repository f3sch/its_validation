#include "alicestyle.h"
using namespace alicestyle;
// Uses output from the PlotDCA macro to produce impact parameter & pt resolution for ITS & ITS-TPC tracks
void plotResolution()
{
  setALICEStyle();

  const std::string fName = "plotDCA.root";
  TFile* inFile = TFile::Open(fName.c_str(), "READ");
  TFile* tdrFile = TFile::Open("tdrITS3_ThreeLayers_default_allpt_pp_results_withfakes.root");
  auto hTDRDCAxy = tdrFile->Get<TH1F>("hDcaxyResPionsAllLayers");
  auto hTDRDCAz = tdrFile->Get<TH1F>("hDcazResPionsAllLayers");
  auto hTDRPtRes = tdrFile->Get<TH1F>("hPtResPionsAllLayers");
  hTDRPtRes->Scale(100); // to %
  // ITS3 FAT
  TFile* fatFile3 = TFile::Open("Fat_std_PiKP_ITSonlyITSTPC_eta05.root");
  auto gFATDCAxyITS3 = fatFile3->Get<TGraph>("gDcaxyPionsITS");
  auto gFATDCAxyITS3TPC = fatFile3->Get<TGraph>("gDcaxyPionsITSTPC");
  auto gFATDCAzITS3 = fatFile3->Get<TGraph>("gDcazPionsITS");
  auto gFATDCAzITS3TPC = fatFile3->Get<TGraph>("gDcazPionsITSTPC");
  // ITS2 FAT
  TFile* fatFile2 = TFile::Open("Fat_wernerpars_ITS2_PiKP_ITSonlyITSTPC_eta05.root");
  auto gFATDCAxyITS2 = fatFile2->Get<TGraph>("gDcaxyPionsITS");
  auto gFATDCAxyITS2TPC = fatFile2->Get<TGraph>("gDcaxyPionsITSTPC");
  auto gFATDCAzITS2 = fatFile2->Get<TGraph>("gDcazPionsITS");
  auto gFATDCAzITS2TPC = fatFile2->Get<TGraph>("gDcazPionsITSTPC");
  // ITS3 FAT Pt
  TFile* fatFile1 = TFile::Open("PtCurvResol_PionKaonProtITSonlyITSTPC_StdR19252315_thick66_resol5_foamYes.root");
  auto cFatPtCanvas = fatFile1->Get<TCanvas>("cCurvResol");
  auto cFatPtPad1 = (TPad*)cFatPtCanvas->GetListOfPrimitives()->FindObject("cCurvResol_1");
  auto gFATPtITS3 = (TGraph*)cFatPtPad1->GetListOfPrimitives()->FindObject("grPtResol0_Part0_itstpc1");
  auto gFATPtITS3TPC = (TGraph*)cFatPtPad1->GetListOfPrimitives()->FindObject("grPtResol0_Part0_itstpc0");

  { // DCAxy
    auto hITS = dynamic_cast<TH1F*>(inFile->Get("Pions/ITS/hResDCAxyVsPtAllLayers_Pions_ITS"));
    auto hITSTPC = dynamic_cast<TH1F*>(inFile->Get("Pions/ITSTPC/hResDCAxyVsPtAllLayers_Pions_ITSTPC"));
    aliceCanvas("Pion DCA_{xy} resolution", hITS->GetXaxis()->GetBinLowEdge(2), hITS->GetXaxis()->GetXmax(), 1, 1000, "#it{p}_{T}^{MC} (GeV/#it{c})", "#sigma(DCA_{xy}) (#mum)", true, true, true);
    auto colors = getPettroffColorSet(7);
    int icol{0};
    aliceDrawHist(hITS, colors[icol++], kALICECircle);
    aliceDrawHist(hITSTPC, colors[icol++], kALICESquare);
    aliceDrawHist(hTDRDCAxy, colors[icol++], kALICECross);
    aliceDrawGraph(gFATDCAxyITS3, colors[icol++]);
    aliceDrawGraph(gFATDCAxyITS3TPC, colors[icol++], kDashed);
    aliceDrawGraph(gFATDCAxyITS2, colors[icol++]);
    aliceDrawGraph(gFATDCAxyITS2TPC, colors[icol++], kDashed);
    auto leg = aliceLeg(0.5, 0.60, 0.88, 0.88, 2, true, true);
    leg->AddEntry(hITS, "ITS3", "p");
    leg->AddEntry(hITSTPC, "ITS3-TPC", "p");
    leg->AddEntry(hTDRDCAxy, "ITS3 TDR", "p");
    leg->AddEntry((TObject*)0, "", ""); // blank entry
    leg->AddEntry(gFATDCAxyITS3, "ITS3 FAT", "l");
    leg->AddEntry(gFATDCAxyITS3TPC, "ITS3-TPC FAT", "l");
    leg->AddEntry(gFATDCAxyITS2, "ITS2 FAT", "l");
    leg->AddEntry(gFATDCAxyITS2TPC, "ITS2-TPC FAT", "l");
    drawThisThesis();
    saveCurrentCanvas("dcaXYRes.pdf");
  }
  { // DCAz
    auto hITS = dynamic_cast<TH1F*>(inFile->Get("Pions/ITS/hResDCAzVsPtAllLayers_Pions_ITS"));
    auto hITSTPC = dynamic_cast<TH1F*>(inFile->Get("Pions/ITSTPC/hResDCAzVsPtAllLayers_Pions_ITSTPC"));
    aliceCanvas("Pion DCA_{z} resolution", hITS->GetXaxis()->GetBinLowEdge(2), hITS->GetXaxis()->GetXmax(), 1, 1000, "#it{p}_{T}^{MC} (GeV/#it{c})", "#sigma(DCA_{z}) (#mum)", true, true, true);
    auto colors = getPettroffColorSet(7);
    int icol{0};
    aliceDrawHist(hITS, colors[icol++], kALICECircle);
    aliceDrawHist(hITSTPC, colors[icol++], kALICESquare);
    aliceDrawHist(hTDRDCAz, colors[icol++], kALICECross);
    aliceDrawGraph(gFATDCAzITS3, colors[icol++]);
    aliceDrawGraph(gFATDCAzITS3TPC, colors[icol++], kDashed);
    aliceDrawGraph(gFATDCAzITS2, colors[icol++]);
    aliceDrawGraph(gFATDCAzITS2TPC, colors[icol++], kDashed);
    auto leg = aliceLeg(0.5, 0.60, 0.88, 0.88, 2, true, true);
    leg->AddEntry(hITS, "ITS3", "p");
    leg->AddEntry(hITSTPC, "ITS3-TPC", "p");
    leg->AddEntry(hTDRDCAz, "ITS3 TDR", "p");
    leg->AddEntry((TObject*)0, "", ""); // blank entry
    leg->AddEntry(gFATDCAzITS3, "ITS3 FAT", "l");
    leg->AddEntry(gFATDCAzITS3TPC, "ITS3-TPC FAT", "l");
    leg->AddEntry(gFATDCAzITS2, "ITS2 FAT", "l");
    leg->AddEntry(gFATDCAzITS2TPC, "ITS2-TPC FAT", "l");
    drawThisThesis();
    saveCurrentCanvas("dcaZRes.pdf");
  }
  { // Pt
    auto hITS = dynamic_cast<TH1F*>(inFile->Get("Pions/ITS/hResDeltaPtVsPtAllLayers_Pions_ITS"));
    hITS->Scale(100); // to %
    auto hITSTPC = dynamic_cast<TH1F*>(inFile->Get("Pions/ITSTPC/hResDeltaPtVsPtAllLayers_Pions_ITSTPC"));
    hITSTPC->Scale(100); // to %
    aliceCanvas("Pion #it{p}_{T} resolution", hITS->GetXaxis()->GetBinLowEdge(2), hITS->GetXaxis()->GetXmax(), 0.1, 100, "#it{p}_{T}^{MC} (GeV/#it{c})", "Momentum resolution (%)", true, true, true);
    auto colors = getPettroffColorSet(7); // more to have consistent coloring of the first three
    int icol{0};
    aliceDrawHist(hITS, colors[icol++], kALICECircle);
    aliceDrawHist(hITSTPC, colors[icol++], kALICESquare);
    aliceDrawHist(hTDRPtRes, colors[icol++], kALICECross);
    aliceDrawGraph(gFATPtITS3, colors[icol++]);
    aliceDrawGraph(gFATPtITS3TPC, colors[icol++], kDashed);
    auto leg = aliceLeg(0.25, 0.625, 0.585, 0.905, 2, true, true);
    leg->AddEntry(hITS, "ITS3", "p");
    leg->AddEntry(hITSTPC, "ITS3-TPC", "p");
    leg->AddEntry(hTDRPtRes, "ITS3 TDR", "p");
    leg->AddEntry((TObject*)0, "", ""); // blank entry
    leg->AddEntry(gFATPtITS3, "ITS3 FAT", "l");
    leg->AddEntry(gFATPtITS3TPC, "ITS3-TPC FAT", "l");
    drawThisThesis();
    saveCurrentCanvas("ptRes.pdf");
  }
}
