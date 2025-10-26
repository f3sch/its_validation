#include "ITSBase/GeometryTGeo.h"
#include "TFile.h"
#include "TString.h"

using Mat3D = o2::math_utils::Transform3D;

void compareTGeo(const char *ccdb1, const char *ccdb2) {
  std::vector<Mat3D> t2l1, t2l2, l2g1, l2g2;
  {
    TString path1(ccdb1);
    path1 += "/ITS/Config/Geometry/snapshot.root";
    auto f1 = TFile::Open(path1);
    auto geo = f1->Get<o2::its::GeometryTGeo>("ccdb_object");
    for (int i{0}; i < geo->getSize(); ++i) {
      t2l1.push_back(geo->getMatrixT2L(i));
      l2g1.push_back(geo->getMatrixL2G(i));
    }
    f1->Close();
  }

  {
    TString path2(ccdb2);
    path2 += "/ITS/Config/Geometry/snapshot.root";
    auto f2 = TFile::Open(path2);
    auto geo = f2->Get<o2::its::GeometryTGeo>("ccdb_object");
    for (int i{0}; i < geo->getSize(); ++i) {
      t2l2.push_back(geo->getMatrixT2L(i));
      l2g2.push_back(geo->getMatrixL2G(i));
    }
    f2->Close();
  }

  if (t2l1.size() != t2l2.size()) {
    Error("TGeo", "Unequal size? %zu %zu", t2l1.size(), t2l2.size());
    return;
  }

  for (int i{0}; i < t2l2.size(); ++i) {
    if (t2l1[i] != t2l2[i]) {
      Error("TGeo", "T2L %d is different!", i);
      return;
    }
    if (l2g1[i] != l2g2[i]) {
      Error("TGeo", "L2G %d is different!", i);
      return;
    }
  }
}

void compareCCDB(const char *ccdb1, const char *ccdb2) {
  compareTGeo(ccdb1, ccdb2);
}
