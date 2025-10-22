#ifndef ALICESTYLE_H_
#define ALICESTYLE_H_

#include <RtypesCore.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TColor.h>
#include <TCanvas.h>
#include <TFrame.h>
#include <TF1.h>
#include <TH1F.h>
#include "TH1D.h"
#include <TH2F.h>
#include "TH2D.h"
#include "TGraph.h"
#include <TLegend.h>
#include <TLatex.h>
#include <TTree.h>
#include <TFile.h>
#include <TError.h>
#include "TString.h"
#include <TPaletteAxis.h>
#include <TMath.h>
#include <math.h>

#include <cmath>

namespace alicestyle
{

static TStyle* aliceStyle{nullptr};
Double_t aliceTextSize = 0.03;
Double_t aliceTextOffsetX = 0;
Double_t aliceTextSizeAxis = 0.06;
Double_t aliceTextSizeLeg = 0.06;

Font_t aliceTextFont = 63; // default is helvetic-bold
Font_t extraTextFont = 53; // default is helvetica-italics
Font_t additionalInfoFont = 42;

// Markers
static const int kALICECircle = kFullCircle;
static const int kALICESquare = kFullSquare;
static const int kALICETriangle = kFullTriangleUp;
static const int kALICETriangleDown = kFullTriangleDown;
static const int kALICECross = kFullCross;
// Linestyles

/// Colors
// This is the Petroff color scheme with 6 colors.
struct P6 {
#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 34, 0)
  inline static const Int_t kBlue = kP6Blue;
  inline static const Int_t kYellow = kP6Yellow;
  inline static const Int_t kRed = kP6Red;
  inline static const Int_t kGrape = kP6Grape;
  inline static const Int_t kGray = kP6Gray;
  inline static const Int_t kViolet = kP6Violet;
#else
  inline static const Int_t kBlue = TColor::GetColor("#5790fc");
  inline static const Int_t kYellow = TColor::GetColor("#f89c20");
  inline static const Int_t kRed = TColor::GetColor("#e42536");
  inline static const Int_t kGrape = TColor::GetColor("#964a8b");
  inline static const Int_t kGray = TColor::GetColor("#9c9ca1");
  inline static const Int_t kViolet = TColor::GetColor("#7a21dd");
#endif
};
// This is the Petroff color scheme with 8 colors.
struct P8 {
#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 34, 0)
  inline static const Int_t kBlue = kP8Blue;
  inline static const Int_t kOrange = kP8Orange;
  inline static const Int_t kRed = kP8Red;
  inline static const Int_t kPink = kP8Pink;
  inline static const Int_t kGreen = kP8Green;
  inline static const Int_t kCyan = kP8Cyan;
  inline static const Int_t kAzure = kP8Azure;
  inline static const Int_t kGray = kP8Gray;
#else
  inline static const Int_t kBlue = TColor::GetColor("#1845fb");
  inline static const Int_t kOrange = TColor::GetColor("#ff5e02");
  inline static const Int_t kRed = TColor::GetColor("#c91f16");
  inline static const Int_t kPink = TColor::GetColor("#c849a9");
  inline static const Int_t kGreen = TColor::GetColor("#adad7d");
  inline static const Int_t kCyan = TColor::GetColor("#86c8dd");
  inline static const Int_t kAzure = TColor::GetColor("#578dff");
  inline static const Int_t kGray = TColor::GetColor("#656364");
#endif
};
// This is the Petroff color scheme with 10 colors.
struct P10 {
#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 34, 0)
  inline static const Int_t kBlue = kP10Blue;
  inline static const Int_t kYellow = kP10Yellow;
  inline static const Int_t kRed = kP10Red;
  inline static const Int_t kGray = kP10Gray;
  inline static const Int_t kViolet = kP10Violet;
  inline static const Int_t kBrown = kP10Brown;
  inline static const Int_t kOrange = kP10Orange;
  inline static const Int_t kGreen = kP10Green;
  inline static const Int_t kAsh = kP10Ash;
  inline static const Int_t kCyan = kP10Cyan;
#else
  inline static const Int_t kBlue = TColor::GetColor("#3f90da");
  inline static const Int_t kYellow = TColor::GetColor("#ffa90e");
  inline static const Int_t kRed = TColor::GetColor("#bd1f01");
  inline static const Int_t kGray = TColor::GetColor("#94a4a2");
  inline static const Int_t kViolet = TColor::GetColor("#832db6");
  inline static const Int_t kBrown = TColor::GetColor("#a96b59");
  inline static const Int_t kOrange = TColor::GetColor("#e76300");
  inline static const Int_t kGreen = TColor::GetColor("#b9ac70");
  inline static const Int_t kAsh = TColor::GetColor("#717581");
  inline static const Int_t kCyan = TColor::GetColor("#92dadd");
#endif
};
std::vector<Int_t> getPettroffColorSet(Int_t ncolors)
{
  if (ncolors < 7) {
    return {P6::kBlue, P6::kYellow, P6::kRed, P6::kGrape, P6::kGray, P6::kViolet};
  } else if (ncolors < 9) {
    return {P8::kBlue, P8::kOrange, P8::kRed, P8::kPink, P8::kGreen, P8::kCyan, P8::kAzure, P8::kGray};
  } else {
    std::vector<Int_t> c{P10::kBlue, P10::kYellow, P10::kRed, P10::kGray, P10::kViolet, P10::kBrown, P10::kOrange, P10::kGreen, P10::kAsh, P10::kCyan};
    for (int i{10}; i < ncolors; ++i) {
      c.push_back(c[i % 10]);
    }
    return c;
  }
}

// FWD
void aliceDrawHist(TH1* h, int color, int marker = -1, const char* opt = "hist e same", Bool_t clamp = kTRUE);
void aliceDrawGraph(TGraph* g, int color, int linestyle = -1, int marker = -1, const char* opt = "l");
void aliceDrawTF1(TF1* f, int color, int linestyle = -1, const char* opt = "same");
TLegend* aliceLeg(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t columns = 0, Bool_t whiteBg = kFALSE, Bool_t withBorder = kTRUE, Double_t textSize = aliceTextSizeLeg, Style_t textFont = aliceTextFont, Color_t textColor = kBlack);
void drawText(const char* text, Double_t posX, Double_t posY, Font_t font = additionalInfoFont, Short_t align = 0, Double_t size = aliceTextSize);
void drawThisThesis(Double_t offsetX = 0.01, Double_t offsetY = 0.03);

class ALICECanvas : public TCanvas
{
 public:
  using TCanvas::TCanvas;

  void Add(TObject* o)
  {
    if (!o) {
      return;
    }
    if (!mObjs) {
      mObjs = new TList;
    }
    mObjs->Add(o);
  }

  void Add(TObject* o, Int_t color, Int_t marker = -1, Int_t linestyle = -1)
  {
    if (!o) {
      return;
    }
    TClass* cls = o->IsA();
    if (cls->InheritsFrom(TH1::Class())) {
      aliceDrawHist(static_cast<TH1*>(o), color, marker);
    } else if (cls->InheritsFrom(TGraph::Class())) {
      aliceDrawGraph(static_cast<TGraph*>(o), color, linestyle, marker);
    } else {
      Warning("ALICECanvas::Add", "Unsupported object type: %s", cls->GetName());
    }
  }

  void Draw()
  {
    const auto c = getPettroffColorSet(mObjs->GetEntries());
    int i{0};
    auto leg = aliceLeg(0.5, 0.60, 0.88, 0.88, 2, true, true);
    for (TObject* obj : *mObjs) {
      Add(obj, c[i]);
      leg->AddEntry(obj, obj->GetName(), "p");
      ++i;
    }
    TCanvas::Draw();
  }

  void setFrame(TH1* frame) { mFrame = frame; }
  auto getFrame() { return mFrame; }

 private:
  TList* mObjs{nullptr};
  TH1* mFrame{nullptr};
};

void setALICEStyle(bool force = true)
{
  delete aliceStyle; // Starting from scratch!
  aliceStyle = new TStyle("aliceStyle", "Style for ALICE");

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
  aliceStyle->SetMarkerSize(1);
  aliceStyle->SetLineStyleString(2, "[12 12]"); // postscript dashes

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

  // legends
  aliceStyle->SetLegendFillStyle(kWhite);
  aliceStyle->SetLegendBorderSize(0);
  aliceStyle->SetLegendFont(additionalInfoFont);

  TColor::DefinedColors(1);

  // Using the Style.
  gROOT->SetStyle(aliceStyle->GetName());
  gROOT->ForceStyle(force);
  aliceStyle->cd();
}

void aliceStyleHist(TH1* h, int color, int marker = -1)
{
  h->SetLineColor(color);
  h->SetMarkerColor(color);
  if (marker >= 0) {
    h->SetMarkerStyle(marker);
  }
}

void aliceDrawHist(TH1* h, int color, int marker, const char* opt, Bool_t clamp)
{
  aliceStyleHist(h, color, marker);
  if (gPad && clamp) {              // clamp to frame dimensions
    if (h->GetXaxis() != nullptr) { // x-axis
      Double_t uxmin = gPad->GetUxmin();
      Double_t uxmax = gPad->GetUxmax();
      Double_t xmin = NAN, xmax = NAN;
      if (gPad->GetLogx()) {
        xmin = TMath::Power(10., uxmin);
        xmax = TMath::Power(10., uxmax);
      } else {
        xmin = uxmin;
        xmax = uxmax;
      }
      h->GetXaxis()->SetRangeUser(xmin, xmax);
    }
    if (h->GetYaxis() != nullptr) { // y-axis
      Double_t uymin = gPad->GetUymin();
      Double_t uymax = gPad->GetUymax();
      Double_t ymin = NAN, ymax = NAN;
      if (gPad->GetLogy()) {
        ymin = TMath::Power(10., uymin);
        ymax = TMath::Power(10., uymax);
      } else {
        ymin = uymin;
        ymax = uymax;
      }
      h->GetYaxis()->SetRangeUser(ymin, ymax);
    }
  }
  h->Draw(opt);
}

void aliceStyleGraph(TGraph* g, int color, int linestyle, int marker)
{
  g->SetLineColor(color);
  g->SetLineWidth(3);
  g->SetMarkerColor(color);
  if (linestyle >= 0) {
    g->SetLineStyle(linestyle);
  }
  if (marker >= 0) {
    g->SetMarkerStyle(marker);
  }
}

void aliceDrawGraph(TGraph* g, int color, int linestyle, int marker, const char* opt)
{
  aliceStyleGraph(g, color, linestyle, marker);
  g->Draw(opt);
}

void aliceStyleTF1(TF1* f, int color, int linestyle)
{
  f->SetLineColor(color);
  f->SetLineWidth(3);
  f->SetMarkerColor(color);
  if (linestyle >= 0) {
    f->SetLineStyle(linestyle);
  }
}
void aliceDrawTF1(TF1* f, int color, int linestyle, const char* opt)
{
  aliceStyleTF1(f, color, linestyle);
  f->Draw(opt);
}

TLegend* aliceLeg(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t columns, Bool_t whiteBg, Bool_t withBorder, Double_t textSize, Style_t textFont, Color_t textColor)
{
  TLegend* leg = new TLegend(x1, y1, x2, y2, "", "brNDC");
  if (withBorder) {
    leg->SetBorderSize(1);
  }
  if (whiteBg) {
    leg->SetFillStyle(1001); // solid fill
    leg->SetFillColor(kWhite);
  } else {
    leg->SetFillStyle(0); // transparent
    leg->SetFillColor(0);
  }

  if (columns != 0) {
    leg->SetNColumns(columns);
  }
  leg->Draw();
  return leg;
}

void drawText(const char* text, Double_t posX, Double_t posY, Font_t font, Short_t align, Double_t size)
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

void drawFitInfo(TF1* f, Double_t x = 0.55, Double_t y = 0.85, Double_t dy = 0.05)
{
  if (!f) {
    return;
  }

  // Retrieve fit quality info
  double chi2 = f->GetChisquare();
  int ndf = f->GetNDF();

  // Print function name
  TString txt = "Fit parameters";
  drawText(txt.Data(), x, y);
  y -= dy;

  // Loop over parameters
  for (int i = 0; i < f->GetNpar(); ++i) {
    txt = Form("%s = %.3g #pm %.2g", f->GetParName(i), f->GetParameter(i), f->GetParError(i));
    drawText(txt.Data(), x, y);
    y -= dy;
  }

  // Fit quality
  txt = Form("#chi^{2}/NDF = %.2f/%d = %.2f", chi2, ndf, ndf > 0 ? chi2 / ndf : 0.);
  drawText(txt.Data(), x, y);
  y -= dy;
  // double prob = f->GetProb();
  // if (prob > 0) {
  //   txt = Form("Prob = %.3f", prob);
  //   drawText(txt.Data(), x, y);
  // }
}

void drawThisThesis(Double_t offsetX, Double_t offsetY)
{
  if (!gPad) {
    Error("drawThisThesis", "No current pad (gPad == nullptr)");
    return;
  }

  // Compute the upper-left corner inside the pad margins
  Double_t x = gPad->GetLeftMargin() + offsetX;
  Double_t y = 1.0 - gPad->GetTopMargin() + offsetY;

  // Align = 13: left-aligned horizontally, top-aligned vertically (upper-left corner)
  drawText("THIS THESIS", x, y, additionalInfoFont, 13, aliceTextSize);
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

ALICECanvas* aliceCanvas(const char* canvName,
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
                         Double_t yTitOffset = -999,
                         TH1* h = nullptr)
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
  ALICECanvas* canv = new ALICECanvas(canvName, canvName, 50, 50, (Int_t)W, H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);

  canv->SetLeftMargin(leftN);
  canv->SetRightMargin(rightN);
  if (with_z_axis) {
    canv->SetRightMargin(rightN + 0.105);
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
  auto hProv = h != nullptr;
  if (!hProv) {
    h = canv->DrawFrame(x_min, y_min, x_max, y_max);
  }
  h->GetYaxis()->SetTitleOffset(y_offset);
  h->GetXaxis()->SetTitleOffset(1.2);
  h->GetXaxis()->SetTitle(nameXaxis);
  h->GetYaxis()->SetTitle(nameYaxis);
  if (!hProv) {
    h->Draw("AXIS");
  }
  canv->setFrame(h);

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
  if (gridon) {
    gPad->RedrawAxis("g");
  }

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

TH1D* getSlicesAlongX(const TH2* h2, Bool_t mean)
{
  if (!h2) {
    Error("CreateRMSvsX", "Input histogram is null!");
    return nullptr;
  }

  // Create output histogram
  TString name, title;
  if (mean) {
    name = TString(h2->GetName()) + "_meanY";
    title = TString("Mean of Y slices;") + h2->GetXaxis()->GetTitle() + ";Mean(Y)";
  } else {
    name = TString(h2->GetName()) + "_rmsY";
    title = TString("RMS of Y slices;") + h2->GetXaxis()->GetTitle() + ";RMS(Y)";
  }

  Int_t nbinsX = h2->GetNbinsX();
  Double_t xlow = h2->GetXaxis()->GetXmin();
  Double_t xup = h2->GetXaxis()->GetXmax();

  TH1D* h = new TH1D(name, title, nbinsX, xlow, xup);

  // Loop over x bins
  for (Int_t i = 1; i <= nbinsX; ++i) {
    // Project Y for each X-bin
    std::unique_ptr<TH1D> projY(static_cast<TH1D*>(h2->ProjectionY("_py", i, i, "e")));

    if (projY->GetEntries() > 0) {
      if (mean) {
        Double_t mean = projY->GetMean();
        Double_t meanErr = projY->GetMeanError();
        h->SetBinContent(i, mean);
        h->SetBinError(i, meanErr);
      } else {
        Double_t rms = projY->GetRMS();
        Double_t rmsErr = projY->GetRMSError();
        h->SetBinContent(i, rms);
        h->SetBinError(i, rmsErr);
      }
    } else {
      h->SetBinContent(i, 0);
      h->SetBinError(i, 0);
    }
  }

  return h;
}

void aliceDrawTH2(TH2* h, Bool_t withZAxis = false, Bool_t withExtra = true, Bool_t doRMS = false, float x1 = 0.66, float x2 = -999, float y1 = -999, float y2 = 0.42)
{
  h->Draw((withZAxis) ? "COLZ" : "COL");
  if (withExtra) {
    TH1D *h1 = nullptr, *h2 = nullptr;
    if (doRMS) {
      h2 = getSlicesAlongX(h, false);
      h1 = getSlicesAlongX(h, true);
    } else {
      h->FitSlicesY();
      h2 = gDirectory->Get<TH1D>(Form("%s_2", h->GetName()));
      h1 = gDirectory->Get<TH1D>(Form("%s_1", h->GetName()));
    }
    aliceDrawHist(h2, P6::kBlue, kALICESquare, "hist e same", false);
    aliceDrawHist(h1, P6::kRed, kALICECircle, "hist e same", false);
    TLegend* leg = nullptr;
    if (x2 == -999 || y1 == -999) {
      x2 = 1.0 - gPad->GetRightMargin(); // right edge of plot area
      y1 = gPad->GetBottomMargin();
    }
    leg = aliceLeg(x1, y1, x2, y2, 0, true);
    leg->AddEntry(h1, "#mu", "p");
    leg->AddEntry(h2, (doRMS) ? "RMS" : "#sigma", "p");
  }
}

void aliceNormalize(TH1* h)
{
  h->Scale(1. / h->Integral("width"));
  h->GetYaxis()->SetTitle("n. entries");
}

void aliceNormalize(TH2* h)
{
  h->Scale(1. / h->Integral("width"));
  h->GetZaxis()->SetTitle("n. entries");
}

void adjustPaletteWidth(TH2* h2, Double_t scale = 0.5)
{
  gPad->Update();
  auto* palette = (TPaletteAxis*)h2->GetListOfFunctions()->FindObject("palette");
  if (palette) {
    Double_t x1 = palette->GetX1NDC();
    Double_t x2 = palette->GetX2NDC();
    // Make it thinner and move it slightly closer to the plot
    Double_t width = x2 - x1;
    x1 = 1.0 - gPad->GetRightMargin(); // right edge of plot area
    palette->SetX1NDC(x1);
    // optionally adjust position
    palette->SetX2NDC(x2 - scale * width);
    gPad->Modified();
    gPad->Update();
  } else {
    Error("", "no palette available");
  }
}

/// Draw h2 with COLZ and place the Z title neatly next to the palette.
/// optional xPadGap is the extra gap (in NDC) between palette left edge and title.
void drawZTitle(TH2* h2, Double_t extraGap = 0.03)
{
  if (!h2) {
    return;
  }

  gPad->Update(); // palette is created only after Update()

  // Get palette
  auto* palette = (TPaletteAxis*)h2->GetListOfFunctions()->FindObject("palette");

  // Palette NDC coordinates (0..1 relative to pad)
  Double_t palX1 = palette->GetX1NDC();
  Double_t palX2 = palette->GetX2NDC();
  Double_t palY1 = palette->GetY1NDC();
  Double_t palY2 = palette->GetY2NDC();

  TAxis* zaxis = h2->GetZaxis();
  if (!zaxis) {
    return;
  }

  TString ztitle = zaxis->GetTitle();
  Float_t titleSize = zaxis->GetTitleSize(); // typically in NDC (fraction of pad height)
  Float_t labelSize = zaxis->GetLabelSize(); // typically in NDC
  Int_t labelFont = zaxis->GetLabelFont();

  // Desired title position: centered horizontally over palette, just above palY2
  Double_t titleX = 0.5 * (palX1 + palX2);
  Double_t titleY = palY2 + extraGap;

  palette->SetTitle(""); // avoid duplicate titles

  // Draw title using TLatex in NDC coordinates, rotated 90 degrees
  TLatex latex;
  latex.SetNDC();
  latex.SetTextFont(labelFont);
  latex.SetTextSize(titleSize);
  latex.SetTextAlign(22); // center horiz & vert
  latex.SetTextAngle(0);  // horizontal text
  latex.DrawLatex(titleX, titleY, ztitle.Data());

  gPad->Modified();
  gPad->Update();
}

} // namespace alicestyle

#endif
