#include "../../include/alicestyle.h"

void plotMatBudTree() {
  alicestyle::setALICEStyle();
  TFile *_file0 = TFile::Open("matbudTree.root");
  auto cell = _file0->Get<TTree>("cell");
  cell->SetMarkerStyle(20);
  auto c1 = new TCanvas();
  c1->Divide(2, 3);
  c1->cd(1);
  gPad->SetRightMargin(0.1);
  cell->Draw("phi : z : meanRho", "ilr==2", "colz");
  c1->cd(2);
  gPad->SetRightMargin(0.1);
  cell->Draw("phi : z : meanRho", "ilr==3", "colz");
  c1->cd(3);
  gPad->SetRightMargin(0.1);
  cell->Draw("phi : z : meanRho", "ilr==4", "colz");
  c1->cd(4);
  gPad->SetRightMargin(0.1);
  cell->Draw("phi : z : meanRho", "ilr==5", "colz");
  c1->cd(5);
  gPad->SetRightMargin(0.1);
  cell->Draw("phi : z : meanRho", "ilr==6", "colz");
  c1->cd(6);
  gPad->SetRightMargin(0.1);
  cell->Draw("phi : z : meanRho", "ilr==7", "colz");
}
