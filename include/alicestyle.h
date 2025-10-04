#ifndef ALICESTYLE_H_
#define ALICESTYLE_H_

#include <RtypesCore.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TColor.h>
#include <TCanvas.h>
#include <TFrame.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TTree.h>
#include <TFile.h>

#include <cmath>

namespace alicestyle
{

TStyle* aliceStyle{nullptr};
Double_t aliceTextSize = 0.75;
Double_t aliceTextOffsetX = 0;
Double_t aliceTextSizeAxis = 0.06;
Double_t aliceTextSizeLeg = 0.06;

Font_t aliceTextFont = 61; // default is helvetic-bold
Font_t extraTextFont = 52; // default is helvetica-italics
Font_t additionalInfoFont = 42;

Double_t extraOverALICETextSize = 0.76; // ratio of 'ALICE' and extra text size

// Colour
static const int kALICEBlue = TColor::GetColor("#3f90da");
static const int kALICEYellow = TColor::GetColor("#ffa90e");
static const int kALICERed = TColor::GetColor("#bd1f01");
static const int kALICEGray = TColor::GetColor("#94a4a2");
static const int kALICEViolet = TColor::GetColor("#832db6");
static const int kALICEBrown = TColor::GetColor("#a96b59");
static const int kALICEOrange = TColor::GetColor("#e76300");
static const int kALICEGreen = TColor::GetColor("#b9ac70");
static const int kALICEAsh = TColor::GetColor("#717581");
static const int kALICECyan = TColor::GetColor("#92dadd");
// Markers
static const int kALICECircle = kFullCircle;
static const int kALICESquare = kFullSquare;
static const int kALICETriangle = kFullTriangleUp;
static const int kALICECross = kFullCross;

void setALICEStyle(bool force = true)
{
  delete aliceStyle; // Starting from scratch!
  aliceStyle = new TStyle("aliceStyle", "Style for ALICE");

  gROOT->SetStyle(aliceStyle->GetName());
  gROOT->ForceStyle(force);

  // For the canvas:
  aliceStyle->SetCanvasBorderMode(0);
  aliceStyle->SetCanvasColor(kWhite);
  aliceStyle->SetCanvasDefH(600); // Height of canvas
  aliceStyle->SetCanvasDefW(600); // Width of canvas
  aliceStyle->SetCanvasDefX(0);   // Position on screen
  aliceStyle->SetCanvasDefY(0);
  aliceStyle->SetPadBorderMode(0);
  aliceStyle->SetPadGridX(kFALSE);
  aliceStyle->SetPadGridY(kFALSE);
  aliceStyle->SetPadColor(kWhite);
  aliceStyle->SetGridColor(kBlack);
  aliceStyle->SetGridStyle(3);
  aliceStyle->SetGridWidth(1);

  // For the frame:
  aliceStyle->SetFrameBorderMode(0);
  aliceStyle->SetFrameBorderSize(1);
  aliceStyle->SetFrameFillColor(0);
  aliceStyle->SetFrameFillStyle(0);
  aliceStyle->SetFrameLineColor(1);
  aliceStyle->SetFrameLineStyle(1);
  aliceStyle->SetFrameLineWidth(1);

  // For the histo:
  aliceStyle->SetHistLineColor(1);
  aliceStyle->SetHistLineStyle(0);
  aliceStyle->SetHistLineWidth(1);
  aliceStyle->SetEndErrorSize(2);
  aliceStyle->SetMarkerStyle(20);

  // For the fit/function:
  aliceStyle->SetOptFit(1);
  aliceStyle->SetFitFormat("5.4g");
  aliceStyle->SetFuncColor(2);
  aliceStyle->SetFuncStyle(1);
  aliceStyle->SetFuncWidth(1);

  // For the date:
  aliceStyle->SetOptDate(0);

  // For the statistics box:
  aliceStyle->SetOptFile(0);
  aliceStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat('mr')
  aliceStyle->SetStatColor(kWhite);
  aliceStyle->SetStatFont(additionalInfoFont);
  aliceStyle->SetStatFontSize(0.025);
  aliceStyle->SetStatTextColor(1);
  aliceStyle->SetStatFormat("6.4g");
  aliceStyle->SetStatBorderSize(1);
  aliceStyle->SetStatH(0.1);
  aliceStyle->SetStatW(0.15);

  // Margins:
  aliceStyle->SetPadTopMargin(0.02);
  aliceStyle->SetPadBottomMargin(0.19);
  aliceStyle->SetPadLeftMargin(0.19);
  aliceStyle->SetPadRightMargin(0.02);

  // For the Global title:
  aliceStyle->SetOptTitle(0);
  aliceStyle->SetTitleFont(additionalInfoFont);

  aliceStyle->SetTitleColor(1);
  aliceStyle->SetTitleTextColor(1);
  aliceStyle->SetTitleFillColor(10);
  aliceStyle->SetTitleFontSize(0.05);

  // For the axis titles:
  aliceStyle->SetTitleColor(1, "XYZ");
  aliceStyle->SetTitleFont(additionalInfoFont, "XYZ");
  aliceStyle->SetTitleSize(aliceTextSizeAxis, "XYZ");
  aliceStyle->SetTitleXOffset(1.1);
  aliceStyle->SetTitleYOffset(1.35);

  // For the axis labels:
  aliceStyle->SetLabelColor(1, "XYZ");
  aliceStyle->SetLabelFont(additionalInfoFont, "XYZ");
  aliceStyle->SetLabelOffset(0.012, "XYZ");
  aliceStyle->SetLabelSize(0.05, "XYZ");

  // For the axis:
  aliceStyle->SetAxisColor(1, "XYZ");
  aliceStyle->SetStripDecimals(kTRUE);
  aliceStyle->SetTickLength(0.03, "XYZ");
  aliceStyle->SetNdivisions(510, "XYZ");
  aliceStyle->SetPadTickX(1); // To get tick marks on the opposite side of the frame
  aliceStyle->SetPadTickY(1);

  // Change for log plots:
  aliceStyle->SetOptLogx(0);
  aliceStyle->SetOptLogy(0);
  aliceStyle->SetOptLogz(0);

  // Postscript options:
  aliceStyle->SetPaperSize(20.0, 20.0);
  aliceStyle->SetHatchesLineWidth(2);
  aliceStyle->SetHatchesSpacing(1.3);

  // Some additional parameters we need to set as "style"
  aliceStyle->SetPalette("batlow.txt");
  aliceStyle->SetNumberContours(256);

  TColor::DefinedColors(1);

  // Using the Style.
  aliceStyle->cd();
}

void aliceStyleHist(TH1* h, int color, int marker)
{
  h->SetLineColor(color);
  h->SetMarkerColor(color);
  h->SetMarkerStyle(marker);
}

void aliceDrawHist(TH1* h, int color, int marker, const char* opt = "hist e same")
{
  aliceStyleHist(h, color, marker);
  h->Draw(opt);
}

TLegend* aliceLeg(Double_t x1, Double_t y1, Double_t x2, Double_t y2,
                  Double_t textSize = aliceTextSizeLeg,
                  Style_t textFont = aliceTextFont,
                  Color_t textColor = kBlack,
                  Int_t columns = 0)
{
  TLegend* leg = new TLegend(x1, y1, x2, y2, "", "brNDC");

  leg->SetTextSize(textSize);
  leg->SetTextFont(textFont);
  leg->SetTextColor(textColor);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetFillColor(0);

  if (columns != 0) {
    leg->SetNColumns(columns);
  }
  leg->Draw();

  return leg;
}

void drawText(const char* text, Double_t posX, Double_t posY,
              Font_t font = additionalInfoFont, Short_t align = 0, Double_t size = aliceTextSize)
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(font);
  latex.SetTextAlign(align);
  latex.SetTextSize(size);

  latex.DrawLatex(posX, posY, text);
}

void updatePad(TVirtualPad* ppad)
// This method updates the provided TPad or TCanvas.
{
  if (ppad == nullptr) {
    gPad->RedrawAxis();
    gPad->Modified();
    gPad->Update();
  } else {
    ppad->RedrawAxis();
    ppad->Modified();
    ppad->Update();
  }
}

TCanvas* aliceCanvas(const char* canvName,
                     Double_t x_min,
                     Double_t x_max,
                     Double_t y_min,
                     Double_t y_max,
                     const char* nameXaxis,
                     const char* nameYaxis,
                     Bool_t gridon = kTRUE,
                     Bool_t logx = kFALSE,
                     Bool_t logy = kFALSE,
                     Bool_t square = kTRUE,
                     Double_t extraSpace = 0,
                     Bool_t with_z_axis = kFALSE,
                     Double_t yTitOffset = -999)
{
  if (aliceStyle == nullptr) {
    setALICEStyle();
  }

  // Canvas geometry (pixels)
  Int_t H = 600;
  Double_t W = (square ? 600 : 800);

  // Default pad margins (NDC). These are sane defaults and easier to reason about.
  Double_t topN = 0.07;
  Double_t bottomN = 0.13; // increase bottom if X-title is large
  Double_t leftN = 0.16;   // base left margin
  Double_t rightN = 0.05;

  // Decide y-axis title offset if not provided
  Double_t y_offset = 0.78;
  if (yTitOffset < -998) {
    if (square)
      y_offset = 1.2;
    else
      y_offset = 0.78;
  } else {
    y_offset = yTitOffset;
  }

  // Slight automatic nudges depending on large offsets
  // if the title offset is large, increase the left margin a bit
  if (y_offset > 1.0) {
    leftN += 0.03 * (y_offset - 1.0); // small automatic increase
  }

  // Apply an extraSpace additive NDC margin if requested
  leftN += extraSpace;

  // Build the canvas and apply margins
  TCanvas* canv = new TCanvas(canvName, canvName, 50, 50, (Int_t)W, H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);

  canv->SetLeftMargin(leftN);
  canv->SetRightMargin(rightN);
  if (with_z_axis) {
    canv->SetRightMargin(rightN + 0.03);
  }
  canv->SetTopMargin(topN);
  canv->SetBottomMargin(bottomN);

  // set log axes before enabling grid so grid lines follow log scale
  if (gridon) {
    canv->SetGrid();
  }
  if (logx) {
    canv->SetLogx();
  }
  if (logy) {
    canv->SetLogy();
  }

  // Draw the frame for plotting things and set axis labels
  TH1* h = canv->DrawFrame(x_min, y_min, x_max, y_max);
  h->GetYaxis()->SetTitleOffset(y_offset);
  h->GetXaxis()->SetTitleOffset(1.2);
  h->GetXaxis()->SetTitle(nameXaxis);
  h->GetYaxis()->SetTitle(nameYaxis);
  h->Draw("AXIS");

  // Force an update so ROOT has computed the axis text extents
  canv->Update();

  // === Auto-adjust left margin so Y-title is not clipped ===
  // We use the product (title size * title offset) as a simple proxy for required space.
  // If required space exceeds a threshold, increase left margin.
  Double_t yTitleSize = h->GetYaxis()->GetTitleSize(); // NDC-ish
  Double_t yTitleOffset = h->GetYaxis()->GetTitleOffset();
  Double_t proxy = yTitleSize * yTitleOffset;

  // threshold and scale chosen conservatively; tweak if you want more/less margin
  Double_t threshold = 0.06; // if proxy is bigger than this we need more left margin
  if (proxy > threshold) {
    Double_t extraLeft = 0.03 * (proxy / threshold); // scale up a bit
    Double_t newLeft = std::max((double)canv->GetLeftMargin(), canv->GetLeftMargin() + extraLeft);
    canv->SetLeftMargin(newLeft);
  }

  // Auto-adjust bottom margin slightly if X title would clip
  Double_t xTitleSize = h->GetXaxis()->GetTitleSize();
  Double_t xTitleOffset = h->GetXaxis()->GetTitleOffset();
  Double_t xProxy = xTitleSize * xTitleOffset;
  Double_t bottomThreshold = 0.04;
  if (xProxy > bottomThreshold) {
    Double_t extraBot = 0.02 * (xProxy / bottomThreshold);
    canv->SetBottomMargin(std::max((double)canv->GetBottomMargin(), canv->GetBottomMargin() + extraBot));
  }

  // // redraw after adjusting margins / log / grid so ROOT renders grid lines
  canv->cd();
  canv->Modified();
  canv->Update();
  gPad->RedrawAxis("g");

  return canv;
}

void saveCanvas(TVirtualPad* pcanv, const std::string& path, bool close = false)
// This method allows to save the canvas with the proper update.
{
  updatePad(pcanv);
  pcanv->SaveAs(path.c_str());

  if (close) {
    pcanv->Close();
  }
}

void saveCurrentCanvas(const std::string& path, bool close = false)
{
  saveCanvas(gPad, path, close);
}

} // namespace alicestyle

#endif
