
int basicAnalyzer_gamma(int argc, char** argv) {

  TFile infile(argv[1]);
  TTreeReader tree("mmtree/tree",&infile);
  TTreeReaderValue<UInt_t> n_genpart(tree,"n_genpart");
  TTreeReaderValue<std::vector<int>> genpart_pdg(tree,"genpart_pdg");
  TTreeReaderValue<std::vector<float>> genpart_pt(tree,"genpart_pt");
  TTreeReaderValue<std::vector<float>> genpart_eta(tree,"genpart_eta");
  TTreeReaderValue<std::vector<float>> genpart_phi(tree,"genpart_phi");
  TTreeReaderValue<std::vector<float>> genpart_vx(tree,"genpart_vx");
  TTreeReaderValue<std::vector<float>> genpart_vy(tree,"genpart_vy");
  TTreeReaderValue<std::vector<float>> genpart_vz(tree,"genpart_vz");
  TTreeReaderValue<std::vector<float>> genpart_m(tree,"genpart_m");
  TTreeReaderValue<std::vector<float>> genpart_isHP(tree,"genpart_isHP");
  TTreeReaderValue<UInt_t> n_ele(tree,"n_ele");
  TTreeReaderValue<std::vector<float>> ele_pt(tree,"Electron_pt");
  TTreeReaderValue<std::vector<float>> ele_eta(tree,"Electron_eta");
  TTreeReaderValue<std::vector<float>> ele_phi(tree,"Electron_phi");
  TTreeReaderValue<std::vector<float>> ele_charge(tree,"Electron_charge");
  TTreeReaderValue<std::vector<float>> ele_m(tree,"Electron_m");
  TTreeReaderValue<std::vector<float>> ele_tkiso(tree,"Electron_tkiso");
  TTreeReaderValue<std::vector<float>> ele_hoe(tree,"Electron_HoE");
  TTreeReaderValue<std::vector<float>> ele_sigmaietaieta(tree,"Electron_sigmaietaieta");
  TTreeReaderValue<std::vector<float>> ele_dphiin(tree,"Electron_dphiin");
  TTreeReaderValue<std::vector<float>> ele_detain(tree,"Electron_detain");
  TTreeReaderValue<std::vector<float>> ele_mhits(tree,"Electron_mHits");
  TTreeReaderValue<std::vector<float>> ele_ooEMOop(tree,"Electron_ooEMOop");

  TFile* outfile = new TFile("hists_ele.root","RECREATE");
  TH1F* gen_elen = new TH1F("gen_elen","gen_elen",10,0,10);
  TH1F* gen_elept = new TH1F("gen_elept","gen_elept",1000,0,1000);
  TH1F* gen_eleeta = new TH1F("gen_eleeta","gen_eleeta",108,-2.7,2.7);
  TH1F* gen_elephi = new TH1F("gen_elephi","gen_elephi",66,-3.3,3.3);
  TH1F* gen_elelog10d0 = new TH1F("gen_elelog10d0","gen_elelog10d0",700,-3,4);
  TH1F* genHP_elen = new TH1F("genHP_elen","genHP_elen",10,0,10);
  TH1F* genHP_elept = new TH1F("genHP_elept","genHP_elept",1000,0,1000);
  TH1F* genHP_elepdg = new TH1F("genHP_elepdg","genHP_elepdg",40,-20,20);
  TH1F* genHP_eleeta = new TH1F("genHP_eleeta","genHP_eleeta",108,-2.7,2.7);
  TH1F* genHP_elephi = new TH1F("genHP_elephi","genHP_elephi",66,-3.3,3.3);
  TH1F* genHP_elelog10d0 = new TH1F("genHP_elelog10d0","genHP_elelog10d0",700,-3,4);
  TH1F* genHPbar_elen = new TH1F("genHPbar_elen","genHPbar_elen",10,0,10);
  TH1F* genHPbar_elept = new TH1F("genHPbar_elept","genHPbar_elept",1000,0,1000);
  TH1F* genHPbar_elepdg = new TH1F("genHPbar_elepdg","genHPbar_elepdg",40,-20,20);
  TH1F* genHPbar_eleeta = new TH1F("genHPbar_eleeta","genHPbar_eleeta",108,-2.7,2.7);
  TH1F* genHPbar_elephi = new TH1F("genHPbar_elephi","genHPbar_elephi",66,-3.3,3.3);
  TH1F* genHPbar_elelog10d0 = new TH1F("genHPbar_elelog10d0","genHPbar_elelog10d0",700,-3,4);
  TH1F* genHPec_elen = new TH1F("genHPec_elen","genHPec_elen",10,0,10);
  TH1F* genHPec_elept = new TH1F("genHPec_elept","genHPec_elept",1000,0,1000);
  TH1F* genHPec_elepdg = new TH1F("genHPec_elepdg","genHPec_elepdg",40,-20,20);
  TH1F* genHPec_eleeta = new TH1F("genHPec_eleeta","genHPec_eleeta",108,-2.7,2.7);
  TH1F* genHPec_elephi = new TH1F("genHPec_elephi","genHPec_elephi",66,-3.3,3.3);
  TH1F* genHPec_elelog10d0 = new TH1F("genHPec_elelog10d0","genHPec_elelog10d0",700,-3,4);
  TH1F* genoth_elen = new TH1F("genoth_elen","genoth_elen",10,0,10);
  TH1F* genoth_elept = new TH1F("genoth_elept","genoth_elept",1000,0,1000);
  TH1F* genoth_eleeta = new TH1F("genoth_eleeta","genoth_eleeta",108,-2.7,2.7);
  TH1F* genoth_elephi = new TH1F("genoth_elephi","genoth_elephi",66,-3.3,3.3);
  TH1F* genoth_elelog10d0 = new TH1F("genoth_elelog10d0","genoth_elelog10d0",700,-3,4);
  TH1F* sct_elen = new TH1F("sct_elen","sct_elen",10,0,10);
  TH1F* sct_elept = new TH1F("sct_elept","sct_elept",1000,0,1000);
  TH1F* sct_eleeta = new TH1F("sct_eleeta","sct_eleeta",108,-2.7,2.7);
  TH1F* sct_elephi = new TH1F("sct_elephi","sct_elephi",66,-3.3,3.3);
  TH1F* sct_elecharge = new TH1F("sct_elecharge","sct_elecharge",5,-2,3);
  TH1F* sct_elem = new TH1F("sct_elem","sct_elem",1000,-1e-5,1e-5);
  TH1F* sct_eletkiso = new TH1F("sct_eletkiso","sct_eletkiso",1000,0,250);
  TH1F* sct_elehoe = new TH1F("sct_elehoe","sct_elehoe",1000,0,0.5);
  TH1F* sct_elesigmaietaieta = new TH1F("sct_elesigmaietaieta","sct_elesigmaietaieta",1000,0,0.1);
  TH1F* sct_eledphiin = new TH1F("sct_eledphiin","sct_eledphiin",1000,0,5);
  TH1F* sct_eledetain = new TH1F("sct_eledetain","sct_eledetain",1000,0,5);
  TH1F* sct_elemhits = new TH1F("sct_elemhits","sct_elemhits",10,0,10);
  TH1F* sct_eleooEMOop = new TH1F("sct_eleooEMOop","sct_eleooEMOop",1000,0,20);
  TH1F* sct_gendR = new TH1F("sct_gendR","sct_gendR",1400,0,7);
  TH1F* sct_gendRmin = new TH1F("sct_gendRmin","sct_gendRmin",1400,0,7);
  TH1F* sctbar_elen = new TH1F("sctbar_elen","sctbar_elen",10,0,10);
  TH1F* sctbar_elept = new TH1F("sctbar_elept","sctbar_elept",1000,0,1000);
  TH1F* sctbar_eleeta = new TH1F("sctbar_eleeta","sctbar_eleeta",108,-2.7,2.7);
  TH1F* sctbar_elephi = new TH1F("sctbar_elephi","sctbar_elephi",66,-3.3,3.3);
  TH1F* sctbar_elecharge = new TH1F("sctbar_elecharge","sctbar_elecharge",5,-2,3);
  TH1F* sctbar_elem = new TH1F("sctbar_elem","sctbar_elem",1000,-1e-5,1e-5);
  TH1F* sctbar_eletkiso = new TH1F("sctbar_eletkiso","sctbar_eletkiso",1000,0,250);
  TH1F* sctbar_elehoe = new TH1F("sctbar_elehoe","sctbar_elehoe",1000,0,0.5);
  TH1F* sctbar_elesigmaietaieta = new TH1F("sctbar_elesigmaietaieta","sctbar_elesigmaietaieta",1000,0,0.1);
  TH1F* sctbar_eledphiin = new TH1F("sctbar_eledphiin","sctbar_eledphiin",1000,0,5);
  TH1F* sctbar_eledetain = new TH1F("sctbar_eledetain","sctbar_eledetain",1000,0,5);
  TH1F* sctbar_elemhits = new TH1F("sctbar_elemhits","sctbar_elemhits",10,0,10);
  TH1F* sctbar_eleooEMOop = new TH1F("sctbar_eleooEMOop","sctbar_eleooEMOop",1000,0,20);
  TH1F* sctbar_gendR = new TH1F("sctbar_gendR","sctbar_gendR",1400,0,7);
  TH1F* sctbar_gendRmin = new TH1F("sctbar_gendRmin","sctbar_gendRmin",1400,0,7);
  TH1F* sctec_elen = new TH1F("sctec_elen","sctec_elen",10,0,10);
  TH1F* sctec_elept = new TH1F("sctec_elept","sctec_elept",1000,0,1000);
  TH1F* sctec_eleeta = new TH1F("sctec_eleeta","sctec_eleeta",108,-2.7,2.7);
  TH1F* sctec_elephi = new TH1F("sctec_elephi","sctec_elephi",66,-3.3,3.3);
  TH1F* sctec_elecharge = new TH1F("sctec_elecharge","sctec_elecharge",5,-2,3);
  TH1F* sctec_elem = new TH1F("sctec_elem","sctec_elem",1000,-1e-5,1e-5);
  TH1F* sctec_eletkiso = new TH1F("sctec_eletkiso","sctec_eletkiso",1000,0,250);
  TH1F* sctec_elehoe = new TH1F("sctec_elehoe","sctec_elehoe",1000,0,0.5);
  TH1F* sctec_elesigmaietaieta = new TH1F("sctec_elesigmaietaieta","sctec_elesigmaietaieta",1000,0,0.1);
  TH1F* sctec_eledphiin = new TH1F("sctec_eledphiin","sctec_eledphiin",1000,0,5);
  TH1F* sctec_eledetain = new TH1F("sctec_eledetain","sctec_eledetain",1000,0,5);
  TH1F* sctec_elemhits = new TH1F("sctec_elemhits","sctec_elemhits",10,0,10);
  TH1F* sctec_eleooEMOop = new TH1F("sctec_eleooEMOop","sctec_eleooEMOop",1000,0,20);
  TH1F* sctec_gendR = new TH1F("sctec_gendR","sctec_gendR",1400,0,7);
  TH1F* sctec_gendRmin = new TH1F("sctec_gendRmin","sctec_gendRmin",1400,0,7);

  TH1F* sctgenmch_elen = new TH1F("sctgenmch_elen","sctgenmch_elen",10,0,10);
  TH1F* sctgenmch_elept = new TH1F("sctgenmch_elept","sctgenmch_elept",1000,0,1000);
  TH1F* sctgenmch_eleeta = new TH1F("sctgenmch_eleeta","sctgenmch_eleeta",108,-2.7,2.7);
  TH1F* sctgenmch_elephi = new TH1F("sctgenmch_elephi","sctgenmch_elephi",66,-3.3,3.3);
  TH1F* sctgenmch_elecharge = new TH1F("sctgenmch_elecharge","sctgenmch_elecharge",5,-2,3);
  TH1F* sctgenmch_elem = new TH1F("sctgenmch_elem","sctgenmch_elem",1000,-1e-5,1e-5);
  TH1F* sctgenmch_eletkiso = new TH1F("sctgenmch_eletkiso","sctgenmch_eletkiso",1000,0,250);
  TH1F* sctgenmch_elehoe = new TH1F("sctgenmch_elehoe","sctgenmch_elehoe",1000,0,0.5);
  TH1F* sctgenmch_elesigmaietaieta = new TH1F("sctgenmch_elesigmaietaieta","sctgenmch_elesigmaietaieta",1000,0,0.1);
  TH1F* sctgenmch_eledphiin = new TH1F("sctgenmch_eledphiin","sctgenmch_eledphiin",1000,0,5);
  TH1F* sctgenmch_eledetain = new TH1F("sctgenmch_eledetain","sctgenmch_eledetain",1000,0,5);
  TH1F* sctgenmch_elemhits = new TH1F("sctgenmch_elemhits","sctgenmch_elemhits",10,0,10);
  TH1F* sctgenmch_eleooEMOop = new TH1F("sctgenmch_eleooEMOop","sctgenmch_eleooEMOop",1000,0,20);
  TH1F* sctbargenmch_elen = new TH1F("sctbargenmch_elen","sctbargenmch_elen",10,0,10);
  TH1F* sctbargenmch_elept = new TH1F("sctbargenmch_elept","sctbargenmch_elept",1000,0,1000);
  TH1F* sctbargenmch_eleeta = new TH1F("sctbargenmch_eleeta","sctbargenmch_eleeta",108,-2.7,2.7);
  TH1F* sctbargenmch_elephi = new TH1F("sctbargenmch_elephi","sctbargenmch_elephi",66,-3.3,3.3);
  TH1F* sctbargenmch_elecharge = new TH1F("sctbargenmch_elecharge","sctbargenmch_elecharge",5,-2,3);
  TH1F* sctbargenmch_elem = new TH1F("sctbargenmch_elem","sctbargenmch_elem",1000,-1e-5,1e-5);
  TH1F* sctbargenmch_eletkiso = new TH1F("sctbargenmch_eletkiso","sctbargenmch_eletkiso",1000,0,250);
  TH1F* sctbargenmch_elehoe = new TH1F("sctbargenmch_elehoe","sctbargenmch_elehoe",1000,0,0.5);
  TH1F* sctbargenmch_elesigmaietaieta = new TH1F("sctbargenmch_elesigmaietaieta","sctbargenmch_elesigmaietaieta",1000,0,0.1);
  TH1F* sctbargenmch_eledphiin = new TH1F("sctbargenmch_eledphiin","sctbargenmch_eledphiin",1000,0,5);
  TH1F* sctbargenmch_eledetain = new TH1F("sctbargenmch_eledetain","sctbargenmch_eledetain",1000,0,5);
  TH1F* sctbargenmch_elemhits = new TH1F("sctbargenmch_elemhits","sctbargenmch_elemhits",10,0,10);
  TH1F* sctbargenmch_eleooEMOop = new TH1F("sctbargenmch_eleooEMOop","sctbargenmch_eleooEMOop",1000,0,20);
  TH1F* sctecgenmch_elen = new TH1F("sctecgenmch_elen","sctecgenmch_elen",10,0,10);
  TH1F* sctecgenmch_elept = new TH1F("sctecgenmch_elept","sctecgenmch_elept",1000,0,1000);
  TH1F* sctecgenmch_eleeta = new TH1F("sctecgenmch_eleeta","sctecgenmch_eleeta",108,-2.7,2.7);
  TH1F* sctecgenmch_elephi = new TH1F("sctecgenmch_elephi","sctecgenmch_elephi",66,-3.3,3.3);
  TH1F* sctecgenmch_elecharge = new TH1F("sctecgenmch_elecharge","sctecgenmch_elecharge",5,-2,3);
  TH1F* sctecgenmch_elem = new TH1F("sctecgenmch_elem","sctecgenmch_elem",1000,-1e-5,1e-5);
  TH1F* sctecgenmch_eletkiso = new TH1F("sctecgenmch_eletkiso","sctecgenmch_eletkiso",1000,0,250);
  TH1F* sctecgenmch_elehoe = new TH1F("sctecgenmch_elehoe","sctecgenmch_elehoe",1000,0,0.5);
  TH1F* sctecgenmch_elesigmaietaieta = new TH1F("sctecgenmch_elesigmaietaieta","sctecgenmch_elesigmaietaieta",1000,0,0.1);
  TH1F* sctecgenmch_eledphiin = new TH1F("sctecgenmch_eledphiin","sctecgenmch_eledphiin",1000,0,5);
  TH1F* sctecgenmch_eledetain = new TH1F("sctecgenmch_eledetain","sctecgenmch_eledetain",1000,0,5);
  TH1F* sctecgenmch_elemhits = new TH1F("sctecgenmch_elemhits","sctecgenmch_elemhits",10,0,10);
  TH1F* sctecgenmch_eleooEMOop = new TH1F("sctecgenmch_eleooEMOop","sctecgenmch_eleooEMOop",1000,0,20);

  // HP GenMatched muons
  TH1F* genHPsctmch_elen = new TH1F("genHPsctmch_elen","genHPsctmch_elen",10,0,10);
  TH1F* genHPsctmch_elept = new TH1F("genHPsctmch_elept","genHPsctmch_elept",1000,0,1000);
  TH1F* genHPsctmch_elepdg = new TH1F("genHPsctmch_elepdg","genHPsctmch_elepdg",40,-20,20);
  TH1F* genHPsctmch_eleeta = new TH1F("genHPsctmch_eleeta","genHPsctmch_eleeta",108,-2.7,2.7);
  TH1F* genHPsctmch_elephi = new TH1F("genHPsctmch_elephi","genHPsctmch_elephi",66,-3.3,3.3);
  TH1F* genHPsctmch_elelog10d0 = new TH1F("genHPsctmch_elelog10d0","genHPsctmch_elelog10d0",700,-3,4);
  TH1F* genHPsctbarmch_elen = new TH1F("genHPsctbarmch_elen","genHPsctbarmch_elen",10,0,10);
  TH1F* genHPsctbarmch_elept = new TH1F("genHPsctbarmch_elept","genHPsctbarmch_elept",1000,0,1000);
  TH1F* genHPsctbarmch_elepdg = new TH1F("genHPsctbarmch_elepdg","genHPsctbarmch_elepdg",40,-20,20);
  TH1F* genHPsctbarmch_eleeta = new TH1F("genHPsctbarmch_eleeta","genHPsctbarmch_eleeta",108,-2.7,2.7);
  TH1F* genHPsctbarmch_elephi = new TH1F("genHPsctbarmch_elephi","genHPsctbarmch_elephi",66,-3.3,3.3);
  TH1F* genHPsctbarmch_elelog10d0 = new TH1F("genHPsctbarmch_elelog10d0","genHPsctbarmch_elelog10d0",700,-3,4);
  TH1F* genHPsctecmch_elen = new TH1F("genHPsctecmch_elen","genHPsctecmch_elen",10,0,10);
  TH1F* genHPsctecmch_elept = new TH1F("genHPsctecmch_elept","genHPsctecmch_elept",1000,0,1000);
  TH1F* genHPsctecmch_elepdg = new TH1F("genHPsctecmch_elepdg","genHPsctecmch_elepdg",40,-20,20);
  TH1F* genHPsctecmch_eleeta = new TH1F("genHPsctecmch_eleeta","genHPsctecmch_eleeta",108,-2.7,2.7);
  TH1F* genHPsctecmch_elephi = new TH1F("genHPsctecmch_elephi","genHPsctecmch_elephi",66,-3.3,3.3);
  TH1F* genHPsctecmch_elelog10d0 = new TH1F("genHPsctecmch_elelog10d0","genHPsctecmch_elelog10d0",700,-3,4);
  TH1F* sctgenHPmch_elen = new TH1F("sctgenHPmch_elen","sctgenHPmch_elen",10,0,10);
  TH1F* sctgenHPmch_elept = new TH1F("sctgenHPmch_elept","sctgenHPmch_elept",1000,0,1000);
  TH1F* sctgenHPmch_eleeta = new TH1F("sctgenHPmch_eleeta","sctgenHPmch_eleeta",108,-2.7,2.7);
  TH1F* sctgenHPmch_elephi = new TH1F("sctgenHPmch_elephi","sctgenHPmch_elephi",66,-3.3,3.3);
  TH1F* sctgenHPmch_elecharge = new TH1F("sctgenHPmch_elecharge","sctgenHPmch_elecharge",5,-2,3);
  TH1F* sctgenHPmch_elem = new TH1F("sctgenHPmch_elem","sctgenHPmch_elem",1000,-1e-5,1e-5);
  TH1F* sctgenHPmch_eletkiso = new TH1F("sctgenHPmch_eletkiso","sctgenHPmch_eletkiso",1000,0,250);
  TH1F* sctgenHPmch_elehoe = new TH1F("sctgenHPmch_elehoe","sctgenHPmch_elehoe",1000,0,0.5);
  TH1F* sctgenHPmch_elesigmaietaieta = new TH1F("sctgenHPmch_elesigmaietaieta","sctgenHPmch_elesigmaietaieta",1000,0,0.1);
  TH1F* sctgenHPmch_eledphiin = new TH1F("sctgenHPmch_eledphiin","sctgenHPmch_eledphiin",1000,0,5);
  TH1F* sctgenHPmch_eledetain = new TH1F("sctgenHPmch_eledetain","sctgenHPmch_eledetain",1000,0,5);
  TH1F* sctgenHPmch_elemhits = new TH1F("sctgenHPmch_elemhits","sctgenHPmch_elemhits",10,0,10);
  TH1F* sctgenHPmch_eleooEMOop = new TH1F("sctgenHPmch_eleooEMOop","sctgenHPmch_eleooEMOop",1000,0,20);
  TH1F* sctbargenHPmch_elen = new TH1F("sctbargenHPmch_elen","sctbargenHPmch_elen",10,0,10);
  TH1F* sctbargenHPmch_elept = new TH1F("sctbargenHPmch_elept","sctbargenHPmch_elept",1000,0,1000);
  TH1F* sctbargenHPmch_eleeta = new TH1F("sctbargenHPmch_eleeta","sctbargenHPmch_eleeta",108,-2.7,2.7);
  TH1F* sctbargenHPmch_elephi = new TH1F("sctbargenHPmch_elephi","sctbargenHPmch_elephi",66,-3.3,3.3);
  TH1F* sctbargenHPmch_elecharge = new TH1F("sctbargenHPmch_elecharge","sctbargenHPmch_elecharge",5,-2,3);
  TH1F* sctbargenHPmch_elem = new TH1F("sctbargenHPmch_elem","sctbargenHPmch_elem",1000,-1e-5,1e-5);
  TH1F* sctbargenHPmch_eletkiso = new TH1F("sctbargenHPmch_eletkiso","sctbargenHPmch_eletkiso",1000,0,250);
  TH1F* sctbargenHPmch_elehoe = new TH1F("sctbargenHPmch_elehoe","sctbargenHPmch_elehoe",1000,0,0.5);
  TH1F* sctbargenHPmch_elesigmaietaieta = new TH1F("sctbargenHPmch_elesigmaietaieta","sctbargenHPmch_elesigmaietaieta",1000,0,0.1);
  TH1F* sctbargenHPmch_eledphiin = new TH1F("sctbargenHPmch_eledphiin","sctbargenHPmch_eledphiin",1000,0,5);
  TH1F* sctbargenHPmch_eledetain = new TH1F("sctbargenHPmch_eledetain","sctbargenHPmch_eledetain",1000,0,5);
  TH1F* sctbargenHPmch_elemhits = new TH1F("sctbargenHPmch_elemhits","sctbargenHPmch_elemhits",10,0,10);
  TH1F* sctbargenHPmch_eleooEMOop = new TH1F("sctbargenHPmch_eleooEMOop","sctbargenHPmch_eleooEMOop",1000,0,20);
  TH1F* sctecgenHPmch_elen = new TH1F("sctecgenHPmch_elen","sctecgenHPmch_elen",10,0,10);
  TH1F* sctecgenHPmch_elept = new TH1F("sctecgenHPmch_elept","sctecgenHPmch_elept",1000,0,1000);
  TH1F* sctecgenHPmch_eleeta = new TH1F("sctecgenHPmch_eleeta","sctecgenHPmch_eleeta",108,-2.7,2.7);
  TH1F* sctecgenHPmch_elephi = new TH1F("sctecgenHPmch_elephi","sctecgenHPmch_elephi",66,-3.3,3.3);
  TH1F* sctecgenHPmch_elecharge = new TH1F("sctecgenHPmch_elecharge","sctecgenHPmch_elecharge",5,-2,3);
  TH1F* sctecgenHPmch_elem = new TH1F("sctecgenHPmch_elem","sctecgenHPmch_elem",1000,-1e-5,1e-5);
  TH1F* sctecgenHPmch_eletkiso = new TH1F("sctecgenHPmch_eletkiso","sctecgenHPmch_eletkiso",1000,0,250);
  TH1F* sctecgenHPmch_elehoe = new TH1F("sctecgenHPmch_elehoe","sctecgenHPmch_elehoe",1000,0,0.5);
  TH1F* sctecgenHPmch_elesigmaietaieta = new TH1F("sctecgenHPmch_elesigmaietaieta","sctecgenHPmch_elesigmaietaieta",1000,0,0.1);
  TH1F* sctecgenHPmch_eledphiin = new TH1F("sctecgenHPmch_eledphiin","sctecgenHPmch_eledphiin",1000,0,5);
  TH1F* sctecgenHPmch_eledetain = new TH1F("sctecgenHPmch_eledetain","sctecgenHPmch_eledetain",1000,0,5);
  TH1F* sctecgenHPmch_elemhits = new TH1F("sctecgenHPmch_elemhits","sctecgenHPmch_elemhits",10,0,10);
  TH1F* sctecgenHPmch_eleooEMOop = new TH1F("sctecgenHPmch_eleooEMOop","sctecgenHPmch_eleooEMOop",1000,0,20);

  // Other GenMatched muons

  std::cout<<"Total event: "<<tree.GetEntries()<<std::endl;

  int event=-1;
  while(tree.Next()) {
    
    event++;
    if(event%10000==0) std::cout<<event<<" done!"<<std::endl;
    //if(event>=100) break;
    
    int ngenele = 0;
    int ngenHPele = 0;
    int ngenothele = 0;
    for(unsigned int genpart_ctr=0; genpart_ctr<(*n_genpart); genpart_ctr++) {
      if(TMath::Abs(genpart_eta->at(genpart_ctr))>2.5) continue;
      if(TMath::Abs(genpart_pdg->at(genpart_ctr))!=11) continue;
      
      ngenele++;
      gen_elept->Fill(genpart_pt->at(genpart_ctr));
      gen_eleeta->Fill(genpart_eta->at(genpart_ctr));
      gen_elephi->Fill(genpart_phi->at(genpart_ctr));
      TVector3 elP;
      elP.SetPtEtaPhi(genpart_pt->at(genpart_ctr),genpart_eta->at(genpart_ctr),genpart_phi->at(genpart_ctr));
      double d0 = ((genpart_vx->at(genpart_ctr))*elP.Py())-((genpart_vy->at(genpart_ctr))*elP.Px());
      d0 = d0/genpart_pt->at(genpart_ctr);
      gen_elelog10d0->Fill(TMath::Log10(TMath::Abs(d0)));

      if( genpart_isHP->at(genpart_ctr)>0) {
	ngenHPele++;
	genHP_elept->Fill(genpart_pt->at(genpart_ctr));
	genHP_elepdg->Fill(genpart_pdg->at(genpart_ctr));
	genHP_eleeta->Fill(genpart_eta->at(genpart_ctr));
	genHP_elephi->Fill(genpart_phi->at(genpart_ctr));
	genHP_elelog10d0->Fill(TMath::Log10(TMath::Abs(d0)));
	if(TMath::Abs(genpart_eta->at(genpart_ctr))<1.479) {
	  genHPbar_elept->Fill(genpart_pt->at(genpart_ctr));
	  genHPbar_elepdg->Fill(genpart_pdg->at(genpart_ctr));
	  genHPbar_eleeta->Fill(genpart_eta->at(genpart_ctr));
	  genHPbar_elephi->Fill(genpart_phi->at(genpart_ctr));
	  genHPbar_elelog10d0->Fill(TMath::Log10(TMath::Abs(d0)));
	}
	else {
	  genHPec_elept->Fill(genpart_pt->at(genpart_ctr));
	  genHPec_elepdg->Fill(genpart_pdg->at(genpart_ctr));
	  genHPec_eleeta->Fill(genpart_eta->at(genpart_ctr));
	  genHPec_elephi->Fill(genpart_phi->at(genpart_ctr));
	  genHPec_elelog10d0->Fill(TMath::Log10(TMath::Abs(d0)));
	}
      }
      else {
	ngenothele++;
	genoth_elept->Fill(genpart_pt->at(genpart_ctr));
	genoth_eleeta->Fill(genpart_eta->at(genpart_ctr));
	genoth_elephi->Fill(genpart_phi->at(genpart_ctr));
	genoth_elelog10d0->Fill(TMath::Log10(TMath::Abs(d0)));
      }
    }
    gen_elen->Fill(ngenele);
    genHP_elen->Fill(ngenHPele);
    genoth_elen->Fill(ngenothele);
    //std::cout<<"|| \t";
    
    std::vector<unsigned> genHPmcheles;
    std::vector<unsigned> genothmcheles;
    std::vector<unsigned> genmchgens;
    std::vector<unsigned> genHPmchgens;
    std::vector<unsigned> genothmchgens;
    bool foundgenmch = false;

    sct_elen->Fill(*n_ele);
    int nsctbar = 0;
    int nsctec = 0;
    for(unsigned int ele_ctr=0; ele_ctr<(*n_ele); ele_ctr++) {
      
      if(TMath::Abs(ele_eta->at(ele_ctr))>2.5) continue;
      
      sct_elept->Fill(ele_pt->at(ele_ctr));
      sct_eleeta->Fill(ele_eta->at(ele_ctr));
      sct_elephi->Fill(ele_phi->at(ele_ctr));
      sct_elecharge->Fill(ele_charge->at(ele_ctr));
      sct_eletkiso->Fill(ele_tkiso->at(ele_ctr));
      sct_elehoe->Fill(ele_hoe->at(ele_ctr));
      sct_elem->Fill(ele_m->at(ele_ctr));
      sct_elesigmaietaieta->Fill(ele_sigmaietaieta->at(ele_ctr));
      sct_eledphiin->Fill(ele_dphiin->at(ele_ctr));
      sct_eledetain->Fill(ele_detain->at(ele_ctr));
      sct_elemhits->Fill(ele_mhits->at(ele_ctr));
      sct_eleooEMOop->Fill(ele_ooEMOop->at(ele_ctr));
      if(TMath::Abs(ele_eta->at(ele_ctr))<=1.479) {
	nsctbar++;
	sctbar_elept->Fill(ele_pt->at(ele_ctr));
	sctbar_eleeta->Fill(ele_eta->at(ele_ctr));
	sctbar_elephi->Fill(ele_phi->at(ele_ctr));
	sctbar_elecharge->Fill(ele_charge->at(ele_ctr));
	sctbar_eletkiso->Fill(ele_tkiso->at(ele_ctr));
	sctbar_elehoe->Fill(ele_hoe->at(ele_ctr));
	sctbar_elem->Fill(ele_m->at(ele_ctr));
	sctbar_elesigmaietaieta->Fill(ele_sigmaietaieta->at(ele_ctr));
	sctbar_eledphiin->Fill(ele_dphiin->at(ele_ctr));
	sctbar_eledetain->Fill(ele_detain->at(ele_ctr));
	sctbar_elemhits->Fill(ele_mhits->at(ele_ctr));
	sctbar_eleooEMOop->Fill(ele_ooEMOop->at(ele_ctr));
      }
      else {
	nsctec++;
	sctec_elept->Fill(ele_pt->at(ele_ctr));
	sctec_eleeta->Fill(ele_eta->at(ele_ctr));
	sctec_elephi->Fill(ele_phi->at(ele_ctr));
	sctec_elecharge->Fill(ele_charge->at(ele_ctr));
	sctec_eletkiso->Fill(ele_tkiso->at(ele_ctr));
	sctec_elehoe->Fill(ele_hoe->at(ele_ctr));
	sctec_elem->Fill(ele_m->at(ele_ctr));
	sctec_elesigmaietaieta->Fill(ele_sigmaietaieta->at(ele_ctr));
	sctec_eledphiin->Fill(ele_dphiin->at(ele_ctr));
	sctec_eledetain->Fill(ele_detain->at(ele_ctr));
	sctec_elemhits->Fill(ele_mhits->at(ele_ctr));
	sctec_eleooEMOop->Fill(ele_ooEMOop->at(ele_ctr));
      }
  
      // Loop to find gen matched electron
      int nsctelegenmch = 0;
      for(unsigned int gen_ctr=0; gen_ctr<(*n_genpart); gen_ctr++) {
	if(TMath::Abs(genpart_pdg->at(gen_ctr))!=11) continue;
	
	TVector3 gen3vec;
	gen3vec.SetPtEtaPhi(genpart_pt->at(gen_ctr),genpart_eta->at(gen_ctr),genpart_phi->at(gen_ctr));
	TVector3 sct3vec;
	sct3vec.SetPtEtaPhi(ele_pt->at(ele_ctr),ele_eta->at(ele_ctr),ele_phi->at(ele_ctr));
	double dR = gen3vec.DeltaR(sct3vec);
	if(dR<=0.4 && (std::find(genmchgens.begin(), genmchgens.end(), gen_ctr) == genmchgens.end())) {
	  genmchgens.push_back(gen_ctr);
	  if(genpart_isHP->at(gen_ctr)>0) {
	    genHPmcheles.push_back(ele_ctr);
	    genHPmchgens.push_back(gen_ctr);
	  }
	  else {
	    genothmcheles.push_back(ele_ctr);
	    genothmchgens.push_back(gen_ctr);
	  }
	}
	if(foundgenmch) break;
      }  
	  
      
      double dRmin = 10;
      for(unsigned int gen_ctr=0; gen_ctr<(*n_genpart); gen_ctr++) {
	if(TMath::Abs(genpart_pdg->at(gen_ctr))!=11) continue;

	TVector3 gen3vec;
	gen3vec.SetPtEtaPhi(genpart_pt->at(gen_ctr),genpart_eta->at(gen_ctr),genpart_phi->at(gen_ctr));
	TVector3 sct3vec;
	sct3vec.SetPtEtaPhi(ele_pt->at(ele_ctr),ele_eta->at(ele_ctr),ele_phi->at(ele_ctr));
	double dR = gen3vec.DeltaR(sct3vec);
	sct_gendR->Fill(dR);
	if(TMath::Abs(ele_eta->at(ele_ctr))<=1.479) {
	  sctbar_gendR->Fill(dR);
	}
	else {
	  sctec_gendR->Fill(dR);
	}
	if(dR<dRmin) dRmin = dR;
      }
      sct_gendRmin->Fill(dRmin);
      if(TMath::Abs(ele_eta->at(ele_ctr))<=1.479) {
	sctbar_gendRmin->Fill(dRmin);
      }
      else {
	sctec_gendRmin->Fill(dRmin);
      }
      
    }
    sctbar_elen->Fill(nsctbar);
    sctec_elen->Fill(nsctec);

    // Fill histograms
    int ngenHPbarmchgens = 0;
    int ngenHPecmchgens = 0;
    for(unsigned int genctr=0; genctr<genHPmchgens.size(); genctr++) {
      
      genHPsctmch_elept->Fill(genpart_pt->at(genHPmchgens[genctr]));
      genHPsctmch_elepdg->Fill(genpart_pdg->at(genHPmchgens[genctr]));
      genHPsctmch_eleeta->Fill(genpart_eta->at(genHPmchgens[genctr]));
      genHPsctmch_elephi->Fill(genpart_phi->at(genHPmchgens[genctr]));
      TVector3 elP;
      elP.SetPtEtaPhi(genpart_pt->at(genHPmchgens[genctr]),genpart_eta->at(genHPmchgens[genctr]),genpart_phi->at(genHPmchgens[genctr]));
      double d0 = ((genpart_vx->at(genHPmchgens[genctr]))*elP.Py())-((genpart_vy->at(genHPmchgens[genctr]))*elP.Px());
      d0 = d0/genpart_pt->at(genHPmchgens[genctr]);
      genHPsctmch_elelog10d0->Fill(TMath::Log10(TMath::Abs(d0)));
      if(TMath::Abs(genpart_eta->at(genHPmchgens[genctr]))<=1.479) {
	genHPsctbarmch_elept->Fill(genpart_pt->at(genHPmchgens[genctr]));
	genHPsctbarmch_elepdg->Fill(genpart_pdg->at(genHPmchgens[genctr]));
	genHPsctbarmch_eleeta->Fill(genpart_eta->at(genHPmchgens[genctr]));
	genHPsctbarmch_elephi->Fill(genpart_phi->at(genHPmchgens[genctr]));
	genHPsctbarmch_elelog10d0->Fill(TMath::Log10(TMath::Abs(d0)));
	ngenHPbarmchgens++;
      }
      else {
	genHPsctecmch_elept->Fill(genpart_pt->at(genHPmchgens[genctr]));
	genHPsctecmch_elepdg->Fill(genpart_pdg->at(genHPmchgens[genctr]));
	genHPsctecmch_eleeta->Fill(genpart_eta->at(genHPmchgens[genctr]));
	genHPsctecmch_elephi->Fill(genpart_phi->at(genHPmchgens[genctr]));
	genHPsctecmch_elelog10d0->Fill(TMath::Log10(TMath::Abs(d0)));
	ngenHPecmchgens++;
      }	
    }
    genHPsctmch_elen->Fill(genHPmchgens.size());
    genHPsctbarmch_elen->Fill(ngenHPbarmchgens);
    genHPsctecmch_elen->Fill(ngenHPecmchgens);
    
    int nsctbargenHPmch = 0;
    int nsctecgenHPmch = 0;
    for(unsigned int electr=0; electr<genHPmcheles.size(); electr++) {
      
      sctgenHPmch_elept->Fill(ele_pt->at(genHPmcheles[electr]));
      sctgenHPmch_eleeta->Fill(ele_eta->at(genHPmcheles[electr]));
      sctgenHPmch_elephi->Fill(ele_phi->at(genHPmcheles[electr]));
      sctgenHPmch_elecharge->Fill(ele_charge->at(genHPmcheles[electr]));
      sctgenHPmch_eletkiso->Fill(ele_tkiso->at(genHPmcheles[electr]));
      sctgenHPmch_elehoe->Fill(ele_hoe->at(genHPmcheles[electr]));
      sctgenHPmch_elem->Fill(ele_m->at(genHPmcheles[electr]));
      sctgenHPmch_elesigmaietaieta->Fill(ele_sigmaietaieta->at(genHPmcheles[electr]));
      sctgenHPmch_eledphiin->Fill(ele_dphiin->at(genHPmcheles[electr]));
      sctgenHPmch_eledetain->Fill(ele_detain->at(genHPmcheles[electr]));
      sctgenHPmch_elemhits->Fill(ele_mhits->at(genHPmcheles[electr]));
      sctgenHPmch_eleooEMOop->Fill(ele_ooEMOop->at(genHPmcheles[electr]));
      if(TMath::Abs(ele_eta->at(genHPmcheles[electr]))<=1.479) {
	nsctbargenHPmch++;
	sctbargenHPmch_elept->Fill(ele_pt->at(genHPmcheles[electr]));
	sctbargenHPmch_eleeta->Fill(ele_eta->at(genHPmcheles[electr]));
	sctbargenHPmch_elephi->Fill(ele_phi->at(genHPmcheles[electr]));
	sctbargenHPmch_elecharge->Fill(ele_charge->at(genHPmcheles[electr]));
	sctbargenHPmch_eletkiso->Fill(ele_tkiso->at(genHPmcheles[electr]));
	sctbargenHPmch_elehoe->Fill(ele_hoe->at(genHPmcheles[electr]));
	sctbargenHPmch_elem->Fill(ele_m->at(genHPmcheles[electr]));
	sctbargenHPmch_elesigmaietaieta->Fill(ele_sigmaietaieta->at(genHPmcheles[electr]));
	sctbargenHPmch_eledphiin->Fill(ele_dphiin->at(genHPmcheles[electr]));
	sctbargenHPmch_eledetain->Fill(ele_detain->at(genHPmcheles[electr]));
	sctbargenHPmch_elemhits->Fill(ele_mhits->at(genHPmcheles[electr]));
	sctbargenHPmch_eleooEMOop->Fill(ele_ooEMOop->at(genHPmcheles[electr]));
      }
      else {
	nsctecgenHPmch++;
	sctecgenHPmch_elept->Fill(ele_pt->at(genHPmcheles[electr]));
	sctecgenHPmch_eleeta->Fill(ele_eta->at(genHPmcheles[electr]));
	sctecgenHPmch_elephi->Fill(ele_phi->at(genHPmcheles[electr]));
	sctecgenHPmch_elecharge->Fill(ele_charge->at(genHPmcheles[electr]));
	sctecgenHPmch_eletkiso->Fill(ele_tkiso->at(genHPmcheles[electr]));
	sctecgenHPmch_elehoe->Fill(ele_hoe->at(genHPmcheles[electr]));
	sctecgenHPmch_elem->Fill(ele_m->at(genHPmcheles[electr]));
	sctecgenHPmch_elesigmaietaieta->Fill(ele_sigmaietaieta->at(genHPmcheles[electr]));
	sctecgenHPmch_eledphiin->Fill(ele_dphiin->at(genHPmcheles[electr]));
	sctecgenHPmch_eledetain->Fill(ele_detain->at(genHPmcheles[electr]));
	sctecgenHPmch_elemhits->Fill(ele_mhits->at(genHPmcheles[electr]));
	sctecgenHPmch_eleooEMOop->Fill(ele_ooEMOop->at(genHPmcheles[electr]));
      }      
    }
    sctgenHPmch_elen->Fill(genHPmcheles.size());
    sctbargenHPmch_elen->Fill(nsctbargenHPmch);
    sctecgenHPmch_elen->Fill(nsctecgenHPmch);
    
    genHPmcheles.clear();
    genothmcheles.clear();
    genmchgens.clear();
    genHPmchgens.clear();
    genothmchgens.clear();
    
  } // End of event loop
  
  outfile->Write();
  outfile->Close();
  tree.Delete();
  return -1;
}
