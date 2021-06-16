// With the following cuts
// Cut 1 - chi2/ndf < 3
// Cut 2 - n trk layer with measurement > 5
// Cut 3 - Cut 1 and cut 2

int basicAnalyzer_mu_onefile(int fNum) {

  std::stringstream instream;
  //instream<<"/pnfs/iihe/cms/store/user/asahasra/SingletTripletHDMToDisplacedL_M200deltaM20ctau3cm_TuneCP5_14TeV-madgraph-pythia8/STHDM_M200dM20ctau3cm_Run3Winter2021MC_crabRunSkim2_asahasra/210615_101538/0000/scoutingNTuple_"<<fNum<<".root";
  instream<<"/pnfs/iihe/cms/store/user/asahasra/SingletTripletHDMToDisplacedL_M200deltaM20ctau30cm_TuneCP5_14TeV-madgraph-pythia8/STHDM_M200dM20ctau30cm_Run3Winter2021MC_crabRunSkim2_asahasra/210615_101821/0000/scoutingNTuple_"<<fNum<<".root";
  std::string filename = instream.str();
  TFile infile(filename.c_str());
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
  TTreeReaderValue<UInt_t> n_mu(tree,"n_mu");
  TTreeReaderValue<std::vector<float>> muon_pt(tree,"Muon_pt");
  TTreeReaderValue<std::vector<float>> muon_eta(tree,"Muon_eta");
  TTreeReaderValue<std::vector<float>> muon_phi(tree,"Muon_phi");
  TTreeReaderValue<std::vector<float>> muon_m(tree,"Muon_m");
  TTreeReaderValue<std::vector<float>> muon_ecaliso(tree,"Muon_ecaliso");
  TTreeReaderValue<std::vector<float>> muon_hcaliso(tree,"Muon_hcaliso");
  TTreeReaderValue<std::vector<float>> muon_trkiso(tree,"Muon_trkiso");
  TTreeReaderValue<std::vector<float>> muon_chi2(tree,"Muon_trkiso");
  TTreeReaderValue<std::vector<float>> muon_ndof(tree,"Muon_chi2");
  TTreeReaderValue<std::vector<float>> muon_charge(tree,"Muon_ndof");
  TTreeReaderValue<std::vector<float>> muon_dxy(tree,"Muon_charge");
  TTreeReaderValue<std::vector<float>> muon_dz(tree,"Muon_dxy");
  TTreeReaderValue<std::vector<float>> muon_nvalidmuon_hits(tree,"Muon_dz");
  TTreeReaderValue<std::vector<float>> muon_validpixelhits(tree,"Muon_nvalidmuon_hits");
  TTreeReaderValue<std::vector<float>> muon_nmatchedstations(tree,"Muon_validpixelhits");
  TTreeReaderValue<std::vector<float>> muon_trklaywmsr(tree,"Muon_nmatchedstations");
  TTreeReaderValue<std::vector<float>> muon_type(tree,"Muon_type");
  TTreeReaderValue<std::vector<float>> muon_nvalidstriphits(tree,"Muon_nvalidstriphits");
  TTreeReaderValue<std::vector<float>> muon_trkqoverp(tree,"Muon_trkqoverp");
  TTreeReaderValue<std::vector<float>> muon_trklambda(tree,"Muon_trklambda");
  TTreeReaderValue<std::vector<float>> muon_trkpt(tree,"Muon_trkpt");
  TTreeReaderValue<std::vector<float>> muon_trkphi(tree,"Muon_trkphi");
  TTreeReaderValue<std::vector<float>> muon_trketa(tree,"Muon_trketa");
  TTreeReaderValue<std::vector<float>> muon_trkqoverperror(tree,"Muon_trkqoverperror");
  TTreeReaderValue<std::vector<float>> muon_trklambdaerror(tree,"Muon_trklambdaerror");
  TTreeReaderValue<std::vector<float>> muon_trkpterror(tree,"Muon_trkpterror");
  TTreeReaderValue<std::vector<float>> muon_trkphierror(tree,"Muon_trkphierror");
  TTreeReaderValue<std::vector<float>> muon_trketaerror(tree,"Muon_trketaerror");
  TTreeReaderValue<std::vector<float>> muon_trkdszerror(tree,"Muon_trkdszerror");
  TTreeReaderValue<std::vector<float>> muon_trkdsz(tree,"Muon_trkdsz");
  TTreeReaderValue<UInt_t> n_jet(tree,"n_jet");
  TTreeReaderValue<std::vector<float>> jet_pt(tree,"Jet_pt");
  TTreeReaderValue<std::vector<float>> jet_eta(tree,"Jet_eta");
  TTreeReaderValue<std::vector<float>> jet_phi(tree,"Jet_phi");

  std::stringstream outstream;
  //outstream<<"hists_mu_STHDM3cm_"<<fNum<<".root";
  outstream<<"hists_mu_STHDM30cm_"<<fNum<<".root";
  std::string outfilename = outstream.str();
  TFile* outfile = new TFile(outfilename.c_str(),"RECREATE");
  TH1F* gen_mun = new TH1F("gen_mun","gen_mun",10,0,10);
  TH1F* gen_mupt = new TH1F("gen_mupt","gen_mupt",1000,0,1000);
  TH1F* gen_mueta = new TH1F("gen_mueta","gen_mueta",100,-2.5,2.5);
  TH1F* gen_muphi = new TH1F("gen_muphi","gen_muphi",66,-3.3,3.3);
  TH1F* gen_mulog10d0 = new TH1F("gen_mulog10d0","gen_mulog10d0",700,-3,4);
  TH1F* genHP_mun = new TH1F("genHP_mun","genHP_mun",10,0,10);
  TH1F* genHP_mupt = new TH1F("genHP_mupt","genHP_mupt",1000,0,1000);
  TH1F* genHP_mueta = new TH1F("genHP_mueta","genHP_mueta",100,-2.5,2.5);
  TH1F* genHP_muphi = new TH1F("genHP_muphi","genHP_muphi",66,-3.3,3.3);
  TH1F* genHP_mulog10d0 = new TH1F("genHP_mulog10d0","genHP_mulog10d0",700,-3,4);
  TH1F* genoth_mun = new TH1F("genoth_mun","genoth_mun",10,0,10);
  TH1F* genoth_mupt = new TH1F("genoth_mupt","genoth_mupt",1000,0,1000);
  TH1F* genoth_mueta = new TH1F("genoth_mueta","genoth_mueta",100,-2.5,2.5);
  TH1F* genoth_muphi = new TH1F("genoth_muphi","genoth_muphi",66,-3.3,3.3);
  TH1F* genoth_mulog10d0 = new TH1F("genoth_mulog10d0","genoth_mulog10d0",700,-3,4);
  TH1F* sct_mun = new TH1F("sct_mun","sct_mun",10,0,10);
  TH1F* sct_mupt = new TH1F("sct_mupt","sct_mupt",1000,0,1000);
  TH1F* sct_mueta = new TH1F("sct_mueta","sct_mueta",100,-2.5,2.5);
  TH1F* sct_muphi = new TH1F("sct_muphi","sct_muphi",66,-3.3,3.3);
  TH1F* sct_mudxy = new TH1F("sct_mudxy","sct_mudxy",2000,-10,10);
  TH1F* sct_mulog10dxy = new TH1F("sct_mulog10dxy","sct_mulog10dxy",140,-3,4);
  TH1F* sct_ecaliso = new TH1F("sct_ecaliso","sct_ecaliso",200,-10,10);
  TH1F* sct_hcaliso = new TH1F("sct_hcaliso","sct_hcaliso",600,-30,30);
  TH1F* sct_trkiso = new TH1F("sct_trkiso","sct_trkiso",1000,0,100);
  TH1F* sct_chi2 = new TH1F("sct_chi2","sct_chi2",1000,0,100);
  TH1F* sct_chi2_ndf = new TH1F("sct_chi2_ndf","sct_chi2_ndf",50,0,5);
  TH1F* sct_charge = new TH1F("sct_charge","sct_charge",5,-2,3);
  TH1F* sct_dz = new TH1F("sct_dz","sct_dz",1000,-50,50);
  TH1F* sct_nvalidmuon_hits = new TH1F("sct_nvalidmuon_hits","sct_nvalidmuon_hits",100,0,100);
  TH1F* sct_validpixelhits = new TH1F("sct_validpixelhits","sct_validpixelhits",60,0,60);
  TH1F* sct_nmatchedstations = new TH1F("sct_nmatchedstations","sct_nmatchedstations",10,0,10);
  TH1F* sct_trklaywmsr = new TH1F("sct_trklaywmsr","sct_trklaywmsr",20,0,20);
  TH1F* sct_type = new TH1F("sct_type","sct_type",20,0,20);
  TH1F* sct_nvalidstriphits = new TH1F("sct_nvalidstriphits","sct_nvalidstriphits",30,0,30);
  TH1F* sct_trkqoverp = new TH1F("sct_trkqoverp","sct_trkqoverp",600,-0.3,0.3);
  TH1F* sct_trklambda = new TH1F("sct_trklambda","sct_trklambda",300,-1.5,1.5);
  TH1F* sct_trkpt = new TH1F("sct_trkpt","sct_trkpt",10000,0,100);
  TH1F* sct_trkptsig = new TH1F("sct_trkptsig","sct_trkptsig",50000,0,5000);
  TH1F* sct_trkphi = new TH1F("sct_trkphi","sct_trkphi",66,-3.3,3.3);
  TH1F* sct_trketa = new TH1F("sct_trketa","sct_trketa",100,-2.5,2.5);
  TH1F* sct_trkqoverperror = new TH1F("sct_trkqoverperror","sct_trkqoverperror",10000,0,0.1);
  TH1F* sct_trklambdaerror = new TH1F("sct_trklambdaerror","sct_trklambdaerror",1000,0,1);
  TH1F* sct_trkpterror = new TH1F("sct_trkpterror","sct_trkpterror",100,0,0.01);
  TH1F* sct_trkphierror = new TH1F("sct_trkphierror","sct_trkphierror",100,0,0.01);
  TH1F* sct_trketaerror = new TH1F("sct_trketaerror","sct_trketaerror",100,0,0.01);
  TH1F* sct_trkdszerror = new TH1F("sct_trkdszerror","sct_trkdszerror",1000,-50,50);
  TH1F* sct_trkdsz = new TH1F("sct_trkdsz","sct_trkdsz",200,0,0.2);
  TH1F* sct_gendR = new TH1F("sct_gendR","sct_gendR",1400,0,7);
  TH1F* sct_gendRmin = new TH1F("sct_gendRmin","sct_gendRmin",1400,0,7);
  
  // HP genmatched gen muons
  TH1F* genHPsctmch_mun = new TH1F("genHPsctmch_mun","genHPsctmch_mun",10,0,10);
  TH1F* genHPsctmch_mupt = new TH1F("genHPsctmch_mupt","genHPsctmch_mupt",1000,0,1000);
  TH1F* genHPsctmch_mupdg = new TH1F("genHPsctmch_mupdg","genHPsctmch_mupdg",40,-20,20);
  TH1F* genHPsctmch_mueta = new TH1F("genHPsctmch_mueta","genHPsctmch_mueta",100,-2.5,2.5);
  TH1F* genHPsctmch_muphi = new TH1F("genHPsctmch_muphi","genHPsctmch_muphi",66,-3.3,3.3);
  TH1F* genHPsctmch_mulog10d0 = new TH1F("genHPsctmch_mulog10d0","genHPsctmch_mulog10d0",700,-3,4);

  // HP GenMatched scouting muons
  TH1F* genHPmch_mun = new TH1F("genHPmch_mun","genHPmch_mun",10,0,10);
  TH1F* genHPmch_mupt = new TH1F("genHPmch_mupt","genHPmch_mupt",1000,0,1000);
  TH1F* genHPmch_mueta = new TH1F("genHPmch_mueta","genHPmch_mueta",100,-2.5,2.5);
  TH1F* genHPmch_muphi = new TH1F("genHPmch_muphi","genHPmch_muphi",66,-3.3,3.3);
  TH1F* genHPmch_ecaliso = new TH1F("genHPmch_ecaliso","genHPmch_ecaliso",200,-10,10);
  TH1F* genHPmch_hcaliso = new TH1F("genHPmch_hcaliso","genHPmch_hcaliso",600,-30,30);
  TH1F* genHPmch_trkiso = new TH1F("genHPmch_trkiso","genHPmch_trkiso",1000,0,100);
  TH1F* genHPmch_chi2 = new TH1F("genHPmch_chi2","genHPmch_chi2",1000,0,100);
  TH1F* genHPmch_chi2_ndf = new TH1F("genHPmch_chi2_ndf","genHPmch_chi2_ndf",50,0,5);
  TH1F* genHPmch_charge = new TH1F("genHPmch_charge","genHPmch_charge",5,-2,3);
  TH1F* genHPmch_mudxy = new TH1F("genHPmch_mudxy","genHPmch_dxy",2000,-10,10);
  TH1F* genHPmch_mulog10dxy = new TH1F("genHPmch_mulog10dxy","genHPmch_mulog10dxy",140,-3,4);
  TH1F* genHPmch_dz = new TH1F("genHPmch_dz","genHPmch_dz",1000,-50,50);
  TH1F* genHPmch_nvalidmuon_hits = new TH1F("genHPmch_nvalidmuon_hits","genHPmch_nvalidmuon_hits",100,0,100);
  TH1F* genHPmch_validpixelhits = new TH1F("genHPmch_validpixelhits","genHPmch_validpixelhits",60,0,60);
  TH1F* genHPmch_nmatchedstations = new TH1F("genHPmch_nmatchedstations","genHPmch_nmatchedstations",10,0,10);
  TH1F* genHPmch_trklaywmsr = new TH1F("genHPmch_trklaywmsr","genHPmch_trklaywmsr",20,0,20);
  TH1F* genHPmch_type = new TH1F("genHPmch_type","genHPmch_type",20,0,20);
  TH1F* genHPmch_nvalidstriphits = new TH1F("genHPmch_nvalidstriphits","genHPmch_nvalidstriphits",30,0,30);
  TH1F* genHPmch_trkqoverp = new TH1F("genHPmch_trkqoverp","genHPmch_trkqoverp",600,-0.3,0.3);
  TH1F* genHPmch_trklambda = new TH1F("genHPmch_trklambda","genHPmch_trklambda",300,-1.5,1.5);
  TH1F* genHPmch_trkpt = new TH1F("genHPmch_trkpt","genHPmch_trkpt",10000,0,100);
  TH1F* genHPmch_trkptsig = new TH1F("genHPmch_trkptsig","genHPmch_trkptsig",50000,0,5000);
  TH1F* genHPmch_trkphi = new TH1F("genHPmch_trkphi","genHPmch_trkphi",66,-3.3,3.3);
  TH1F* genHPmch_trketa = new TH1F("genHPmch_trketa","genHPmch_trketa",100,-2.5,2.5);
  TH1F* genHPmch_trkqoverperror = new TH1F("genHPmch_trkqoverperror","genHPmch_trkqoverperror",10000,0,0.1);
  TH1F* genHPmch_trklambdaerror = new TH1F("genHPmch_trklambdaerror","genHPmch_trklambdaerror",1000,0,1);
  TH1F* genHPmch_trkpterror = new TH1F("genHPmch_trkpterror","genHPmch_trkpterror",100,0,0.01);
  TH1F* genHPmch_trkphierror = new TH1F("genHPmch_trkphierror","genHPmch_trkphierror",100,0,0.01);
  TH1F* genHPmch_trketaerror = new TH1F("genHPmch_trketaerror","genHPmch_trketaerror",100,0,0.01);
  TH1F* genHPmch_trkdszerror = new TH1F("genHPmch_trkdszerror","genHPmch_trkdszerror",1000,-50,50);
  TH1F* genHPmch_trkdsz = new TH1F("genHPmch_trkdsz","genHPmch_trkdsz",200,0,0.2);

  // Other GenMatched scouting muons
  TH1F* genothmch_mun = new TH1F("genothmch_mun","genothmch_mun",10,0,10);
  TH1F* genothmch_mupt = new TH1F("genothmch_mupt","genothmch_mupt",1000,0,1000);
  TH1F* genothmch_mueta = new TH1F("genothmch_mueta","genothmch_mueta",100,-2.5,2.5);
  TH1F* genothmch_muphi = new TH1F("genothmch_muphi","genothmch_muphi",66,-3.3,3.3);
  TH1F* genothmch_ecaliso = new TH1F("genothmch_ecaliso","genothmch_ecaliso",200,-10,10);
  TH1F* genothmch_hcaliso = new TH1F("genothmch_hcaliso","genothmch_hcaliso",600,-30,30);
  TH1F* genothmch_trkiso = new TH1F("genothmch_trkiso","genothmch_trkiso",1000,0,100);
  TH1F* genothmch_chi2 = new TH1F("genothmch_chi2","genothmch_chi2",1000,0,100);
  TH1F* genothmch_chi2_ndf = new TH1F("genothmch_chi2_ndf","genothmch_chi2_ndf",50,0,5);
  TH1F* genothmch_charge = new TH1F("genothmch_charge","genothmch_charge",5,-2,3);
  TH1F* genothmch_mudxy = new TH1F("genothmch_mudxy","genothmch_dxy",2000,-10,10);
  TH1F* genothmch_mulog10dxy = new TH1F("genothmch_mulog10dxy","genothmch_mulog10dxy",140,-3,4);
  TH1F* genothmch_dz = new TH1F("genothmch_dz","genothmch_dz",1000,-50,50);
  TH1F* genothmch_nvalidmuon_hits = new TH1F("genothmch_nvalidmuon_hits","genothmch_nvalidmuon_hits",100,0,100);
  TH1F* genothmch_validpixelhits = new TH1F("genothmch_validpixelhits","genothmch_validpixelhits",60,0,60);
  TH1F* genothmch_nmatchedstations = new TH1F("genothmch_nmatchedstations","genothmch_nmatchedstations",10,0,10);
  TH1F* genothmch_trklaywmsr = new TH1F("genothmch_trklaywmsr","genothmch_trklaywmsr",20,0,20);
  TH1F* genothmch_type = new TH1F("genothmch_type","genothmch_type",20,0,20);
  TH1F* genothmch_nvalidstriphits = new TH1F("genothmch_nvalidstriphits","genothmch_nvalidstriphits",30,0,30);
  TH1F* genothmch_trkqoverp = new TH1F("genothmch_trkqoverp","genothmch_trkqoverp",600,-0.3,0.3);
  TH1F* genothmch_trklambda = new TH1F("genothmch_trklambda","genothmch_trklambda",300,-1.5,1.5);
  TH1F* genothmch_trkpt = new TH1F("genothmch_trkpt","genothmch_trkpt",10000,0,100);
  TH1F* genothmch_trkptsig = new TH1F("genothmch_trkptsig","genothmch_trkptsig",50000,0,5000);
  TH1F* genothmch_trkphi = new TH1F("genothmch_trkphi","genothmch_trkphi",66,-3.3,3.3);
  TH1F* genothmch_trketa = new TH1F("genothmch_trketa","genothmch_trketa",100,-2.5,2.5);
  TH1F* genothmch_trkqoverperror = new TH1F("genothmch_trkqoverperror","genothmch_trkqoverperror",10000,0,0.1);
  TH1F* genothmch_trklambdaerror = new TH1F("genothmch_trklambdaerror","genothmch_trklambdaerror",1000,0,1);
  TH1F* genothmch_trkpterror = new TH1F("genothmch_trkpterror","genothmch_trkpterror",100,0,0.01);
  TH1F* genothmch_trkphierror = new TH1F("genothmch_trkphierror","genothmch_trkphierror",100,0,0.01);
  TH1F* genothmch_trketaerror = new TH1F("genothmch_trketaerror","genothmch_trketaerror",100,0,0.01);
  TH1F* genothmch_trkdszerror = new TH1F("genothmch_trkdszerror","genothmch_trkdszerror",1000,-50,50);
  TH1F* genothmch_trkdsz = new TH1F("genothmch_trkdsz","genothmch_trkdsz",200,0,0.2);

  // Cut 1 - HP genmatched gen muons
  TH1F* cut1genHPsctmch_mun = new TH1F("cut1genHPsctmch_mun","cut1genHPsctmch_mun",10,0,10);
  TH1F* cut1genHPsctmch_mupt = new TH1F("cut1genHPsctmch_mupt","cut1genHPsctmch_mupt",1000,0,1000);
  TH1F* cut1genHPsctmch_mupdg = new TH1F("cut1genHPsctmch_mupdg","cut1genHPsctmch_mupdg",40,-20,20);
  TH1F* cut1genHPsctmch_mueta = new TH1F("cut1genHPsctmch_mueta","cut1genHPsctmch_mueta",100,-2.5,2.5);
  TH1F* cut1genHPsctmch_muphi = new TH1F("cut1genHPsctmch_muphi","cut1genHPsctmch_muphi",66,-3.3,3.3);

  // Cut 1 - HP GenMatched scouting muons
  TH1F* cut1genHPmch_mun = new TH1F("cut1genHPmch_mun","cut1genHPmch_mun",10,0,10);
  TH1F* cut1genHPmch_mupt = new TH1F("cut1genHPmch_mupt","cut1genHPmch_mupt",1000,0,1000);
  TH1F* cut1genHPmch_mueta = new TH1F("cut1genHPmch_mueta","cut1genHPmch_mueta",100,-2.5,2.5);
  TH1F* cut1genHPmch_muphi = new TH1F("cut1genHPmch_muphi","cut1genHPmch_muphi",66,-3.3,3.3);
  TH1F* cut1genHPmch_ecaliso = new TH1F("cut1genHPmch_ecaliso","cut1genHPmch_ecaliso",200,-10,10);
  TH1F* cut1genHPmch_hcaliso = new TH1F("cut1genHPmch_hcaliso","cut1genHPmch_hcaliso",600,-30,30);
  TH1F* cut1genHPmch_trkiso = new TH1F("cut1genHPmch_trkiso","cut1genHPmch_trkiso",1000,0,100);
  TH1F* cut1genHPmch_chi2 = new TH1F("cut1genHPmch_chi2","cut1genHPmch_chi2",1000,0,100);
  TH1F* cut1genHPmch_chi2_ndf = new TH1F("cut1genHPmch_chi2_ndf","cut1genHPmch_chi2_ndf",50,0,5);
  TH1F* cut1genHPmch_charge = new TH1F("cut1genHPmch_charge","cut1genHPmch_charge",5,-2,3);
  TH1F* cut1genHPmch_mudxy = new TH1F("cut1genHPmch_mudxy","cut1genHPmch_dxy",2000,-10,10);
  TH1F* cut1genHPmch_mulog10dxy = new TH1F("cut1genHPmch_mulog10dxy","cut1genHPmch_mulog10dxy",140,-3,4);
  TH1F* cut1genHPmch_dz = new TH1F("cut1genHPmch_dz","cut1genHPmch_dz",1000,-50,50);
  TH1F* cut1genHPmch_nvalidmuon_hits = new TH1F("cut1genHPmch_nvalidmuon_hits","cut1genHPmch_nvalidmuon_hits",100,0,100);
  TH1F* cut1genHPmch_validpixelhits = new TH1F("cut1genHPmch_validpixelhits","cut1genHPmch_validpixelhits",60,0,60);
  TH1F* cut1genHPmch_nmatchedstations = new TH1F("cut1genHPmch_nmatchedstations","cut1genHPmch_nmatchedstations",10,0,10);
  TH1F* cut1genHPmch_trklaywmsr = new TH1F("cut1genHPmch_trklaywmsr","cut1genHPmch_trklaywmsr",20,0,20);
  TH1F* cut1genHPmch_type = new TH1F("cut1genHPmch_type","cut1genHPmch_type",20,0,20);
  TH1F* cut1genHPmch_nvalidstriphits = new TH1F("cut1genHPmch_nvalidstriphits","cut1genHPmch_nvalidstriphits",30,0,30);
  TH1F* cut1genHPmch_trkqoverp = new TH1F("cut1genHPmch_trkqoverp","cut1genHPmch_trkqoverp",600,-0.3,0.3);
  TH1F* cut1genHPmch_trklambda = new TH1F("cut1genHPmch_trklambda","cut1genHPmch_trklambda",300,-1.5,1.5);
  TH1F* cut1genHPmch_trkpt = new TH1F("cut1genHPmch_trkpt","cut1genHPmch_trkpt",10000,0,100);
  TH1F* cut1genHPmch_trkptsig = new TH1F("cut1genHPmch_trkptsig","cut1genHPmch_trkptsig",50000,0,5000);
  TH1F* cut1genHPmch_trkphi = new TH1F("cut1genHPmch_trkphi","cut1genHPmch_trkphi",66,-3.3,3.3);
  TH1F* cut1genHPmch_trketa = new TH1F("cut1genHPmch_trketa","cut1genHPmch_trketa",100,-2.5,2.5);
  TH1F* cut1genHPmch_trkqoverperror = new TH1F("cut1genHPmch_trkqoverperror","cut1genHPmch_trkqoverperror",10000,0,0.1);
  TH1F* cut1genHPmch_trklambdaerror = new TH1F("cut1genHPmch_trklambdaerror","cut1genHPmch_trklambdaerror",1000,0,1);
  TH1F* cut1genHPmch_trkpterror = new TH1F("cut1genHPmch_trkpterror","cut1genHPmch_trkpterror",100,0,0.01);
  TH1F* cut1genHPmch_trkphierror = new TH1F("cut1genHPmch_trkphierror","cut1genHPmch_trkphierror",100,0,0.01);
  TH1F* cut1genHPmch_trketaerror = new TH1F("cut1genHPmch_trketaerror","cut1genHPmch_trketaerror",100,0,0.01);
  TH1F* cut1genHPmch_trkdszerror = new TH1F("cut1genHPmch_trkdszerror","cut1genHPmch_trkdszerror",1000,-50,50);
  TH1F* cut1genHPmch_trkdsz = new TH1F("cut1genHPmch_trkdsz","cut1genHPmch_trkdsz",200,0,0.2);

  // Cut 2 - HP genmatched gen muons
  TH1F* cut2genHPsctmch_mun = new TH1F("cut2genHPsctmch_mun","cut2genHPsctmch_mun",10,0,10);
  TH1F* cut2genHPsctmch_mupt = new TH1F("cut2genHPsctmch_mupt","cut2genHPsctmch_mupt",1000,0,1000);
  TH1F* cut2genHPsctmch_mupdg = new TH1F("cut2genHPsctmch_mupdg","cut2genHPsctmch_mupdg",40,-20,20);
  TH1F* cut2genHPsctmch_mueta = new TH1F("cut2genHPsctmch_mueta","cut2genHPsctmch_mueta",100,-2.5,2.5);
  TH1F* cut2genHPsctmch_muphi = new TH1F("cut2genHPsctmch_muphi","cut2genHPsctmch_muphi",66,-3.3,3.3);

  // Cut 2 - HP GenMatched scouting muons
  TH1F* cut2genHPmch_mun = new TH1F("cut2genHPmch_mun","cut2genHPmch_mun",10,0,10);
  TH1F* cut2genHPmch_mupt = new TH1F("cut2genHPmch_mupt","cut2genHPmch_mupt",1000,0,1000);
  TH1F* cut2genHPmch_mueta = new TH1F("cut2genHPmch_mueta","cut2genHPmch_mueta",100,-2.5,2.5);
  TH1F* cut2genHPmch_muphi = new TH1F("cut2genHPmch_muphi","cut2genHPmch_muphi",66,-3.3,3.3);
  TH1F* cut2genHPmch_ecaliso = new TH1F("cut2genHPmch_ecaliso","cut2genHPmch_ecaliso",200,-10,10);
  TH1F* cut2genHPmch_hcaliso = new TH1F("cut2genHPmch_hcaliso","cut2genHPmch_hcaliso",600,-30,30);
  TH1F* cut2genHPmch_trkiso = new TH1F("cut2genHPmch_trkiso","cut2genHPmch_trkiso",1000,0,100);
  TH1F* cut2genHPmch_chi2 = new TH1F("cut2genHPmch_chi2","cut2genHPmch_chi2",1000,0,100);
  TH1F* cut2genHPmch_chi2_ndf = new TH1F("cut2genHPmch_chi2_ndf","cut2genHPmch_chi2_ndf",50,0,5);
  TH1F* cut2genHPmch_charge = new TH1F("cut2genHPmch_charge","cut2genHPmch_charge",5,-2,3);
  TH1F* cut2genHPmch_mudxy = new TH1F("cut2genHPmch_mudxy","cut2genHPmch_dxy",2000,-10,10);
  TH1F* cut2genHPmch_mulog10dxy = new TH1F("cut2genHPmch_mulog10dxy","cut2genHPmch_mulog10dxy",140,-3,4);
  TH1F* cut2genHPmch_dz = new TH1F("cut2genHPmch_dz","cut2genHPmch_dz",1000,-50,50);
  TH1F* cut2genHPmch_nvalidmuon_hits = new TH1F("cut2genHPmch_nvalidmuon_hits","cut2genHPmch_nvalidmuon_hits",100,0,100);
  TH1F* cut2genHPmch_validpixelhits = new TH1F("cut2genHPmch_validpixelhits","cut2genHPmch_validpixelhits",60,0,60);
  TH1F* cut2genHPmch_nmatchedstations = new TH1F("cut2genHPmch_nmatchedstations","cut2genHPmch_nmatchedstations",10,0,10);
  TH1F* cut2genHPmch_trklaywmsr = new TH1F("cut2genHPmch_trklaywmsr","cut2genHPmch_trklaywmsr",20,0,20);
  TH1F* cut2genHPmch_type = new TH1F("cut2genHPmch_type","cut2genHPmch_type",20,0,20);
  TH1F* cut2genHPmch_nvalidstriphits = new TH1F("cut2genHPmch_nvalidstriphits","cut2genHPmch_nvalidstriphits",30,0,30);
  TH1F* cut2genHPmch_trkqoverp = new TH1F("cut2genHPmch_trkqoverp","cut2genHPmch_trkqoverp",600,-0.3,0.3);
  TH1F* cut2genHPmch_trklambda = new TH1F("cut2genHPmch_trklambda","cut2genHPmch_trklambda",300,-1.5,1.5);
  TH1F* cut2genHPmch_trkpt = new TH1F("cut2genHPmch_trkpt","cut2genHPmch_trkpt",10000,0,100);
  TH1F* cut2genHPmch_trkptsig = new TH1F("cut2genHPmch_trkptsig","cut2genHPmch_trkptsig",50000,0,5000);
  TH1F* cut2genHPmch_trkphi = new TH1F("cut2genHPmch_trkphi","cut2genHPmch_trkphi",66,-3.3,3.3);
  TH1F* cut2genHPmch_trketa = new TH1F("cut2genHPmch_trketa","cut2genHPmch_trketa",100,-2.5,2.5);
  TH1F* cut2genHPmch_trkqoverperror = new TH1F("cut2genHPmch_trkqoverperror","cut2genHPmch_trkqoverperror",10000,0,0.1);
  TH1F* cut2genHPmch_trklambdaerror = new TH1F("cut2genHPmch_trklambdaerror","cut2genHPmch_trklambdaerror",1000,0,1);
  TH1F* cut2genHPmch_trkpterror = new TH1F("cut2genHPmch_trkpterror","cut2genHPmch_trkpterror",100,0,0.01);
  TH1F* cut2genHPmch_trkphierror = new TH1F("cut2genHPmch_trkphierror","cut2genHPmch_trkphierror",100,0,0.01);
  TH1F* cut2genHPmch_trketaerror = new TH1F("cut2genHPmch_trketaerror","cut2genHPmch_trketaerror",100,0,0.01);
  TH1F* cut2genHPmch_trkdszerror = new TH1F("cut2genHPmch_trkdszerror","cut2genHPmch_trkdszerror",1000,-50,50);
  TH1F* cut2genHPmch_trkdsz = new TH1F("cut2genHPmch_trkdsz","cut2genHPmch_trkdsz",200,0,0.2);

  // Cut 3 - HP genmatched gen muons
  TH1F* cut3genHPsctmch_mun = new TH1F("cut3genHPsctmch_mun","cut3genHPsctmch_mun",10,0,10);
  TH1F* cut3genHPsctmch_mupt = new TH1F("cut3genHPsctmch_mupt","cut3genHPsctmch_mupt",1000,0,1000);
  TH1F* cut3genHPsctmch_mupdg = new TH1F("cut3genHPsctmch_mupdg","cut3genHPsctmch_mupdg",40,-20,20);
  TH1F* cut3genHPsctmch_mueta = new TH1F("cut3genHPsctmch_mueta","cut3genHPsctmch_mueta",100,-2.5,2.5);
  TH1F* cut3genHPsctmch_muphi = new TH1F("cut3genHPsctmch_muphi","cut3genHPsctmch_muphi",66,-3.3,3.3);

  // Cut 3 - HP GenMatched scouting muons
  TH1F* cut3genHPmch_mun = new TH1F("cut3genHPmch_mun","cut3genHPmch_mun",10,0,10);
  TH1F* cut3genHPmch_mupt = new TH1F("cut3genHPmch_mupt","cut3genHPmch_mupt",1000,0,1000);
  TH1F* cut3genHPmch_mueta = new TH1F("cut3genHPmch_mueta","cut3genHPmch_mueta",100,-2.5,2.5);
  TH1F* cut3genHPmch_muphi = new TH1F("cut3genHPmch_muphi","cut3genHPmch_muphi",66,-3.3,3.3);
  TH1F* cut3genHPmch_ecaliso = new TH1F("cut3genHPmch_ecaliso","cut3genHPmch_ecaliso",200,-10,10);
  TH1F* cut3genHPmch_hcaliso = new TH1F("cut3genHPmch_hcaliso","cut3genHPmch_hcaliso",600,-30,30);
  TH1F* cut3genHPmch_trkiso = new TH1F("cut3genHPmch_trkiso","cut3genHPmch_trkiso",1000,0,100);
  TH1F* cut3genHPmch_chi2 = new TH1F("cut3genHPmch_chi2","cut3genHPmch_chi2",1000,0,100);
  TH1F* cut3genHPmch_chi2_ndf = new TH1F("cut3genHPmch_chi2_ndf","cut3genHPmch_chi2_ndf",50,0,5);
  TH1F* cut3genHPmch_charge = new TH1F("cut3genHPmch_charge","cut3genHPmch_charge",5,-2,3);
  TH1F* cut3genHPmch_mudxy = new TH1F("cut3genHPmch_mudxy","cut3genHPmch_dxy",2000,-10,10);
  TH1F* cut3genHPmch_mulog10dxy = new TH1F("cut3genHPmch_mulog10dxy","cut3genHPmch_mulog10dxy",140,-3,4);
  TH1F* cut3genHPmch_dz = new TH1F("cut3genHPmch_dz","cut3genHPmch_dz",1000,-50,50);
  TH1F* cut3genHPmch_nvalidmuon_hits = new TH1F("cut3genHPmch_nvalidmuon_hits","cut3genHPmch_nvalidmuon_hits",100,0,100);
  TH1F* cut3genHPmch_validpixelhits = new TH1F("cut3genHPmch_validpixelhits","cut3genHPmch_validpixelhits",60,0,60);
  TH1F* cut3genHPmch_nmatchedstations = new TH1F("cut3genHPmch_nmatchedstations","cut3genHPmch_nmatchedstations",10,0,10);
  TH1F* cut3genHPmch_trklaywmsr = new TH1F("cut3genHPmch_trklaywmsr","cut3genHPmch_trklaywmsr",20,0,20);
  TH1F* cut3genHPmch_type = new TH1F("cut3genHPmch_type","cut3genHPmch_type",20,0,20);
  TH1F* cut3genHPmch_nvalidstriphits = new TH1F("cut3genHPmch_nvalidstriphits","cut3genHPmch_nvalidstriphits",30,0,30);
  TH1F* cut3genHPmch_trkqoverp = new TH1F("cut3genHPmch_trkqoverp","cut3genHPmch_trkqoverp",600,-0.3,0.3);
  TH1F* cut3genHPmch_trklambda = new TH1F("cut3genHPmch_trklambda","cut3genHPmch_trklambda",300,-1.5,1.5);
  TH1F* cut3genHPmch_trkpt = new TH1F("cut3genHPmch_trkpt","cut3genHPmch_trkpt",10000,0,100);
  TH1F* cut3genHPmch_trkptsig = new TH1F("cut3genHPmch_trkptsig","cut3genHPmch_trkptsig",50000,0,5000);
  TH1F* cut3genHPmch_trkphi = new TH1F("cut3genHPmch_trkphi","cut3genHPmch_trkphi",66,-3.3,3.3);
  TH1F* cut3genHPmch_trketa = new TH1F("cut3genHPmch_trketa","cut3genHPmch_trketa",100,-2.5,2.5);
  TH1F* cut3genHPmch_trkqoverperror = new TH1F("cut3genHPmch_trkqoverperror","cut3genHPmch_trkqoverperror",10000,0,0.1);
  TH1F* cut3genHPmch_trklambdaerror = new TH1F("cut3genHPmch_trklambdaerror","cut3genHPmch_trklambdaerror",1000,0,1);
  TH1F* cut3genHPmch_trkpterror = new TH1F("cut3genHPmch_trkpterror","cut3genHPmch_trkpterror",100,0,0.01);
  TH1F* cut3genHPmch_trkphierror = new TH1F("cut3genHPmch_trkphierror","cut3genHPmch_trkphierror",100,0,0.01);
  TH1F* cut3genHPmch_trketaerror = new TH1F("cut3genHPmch_trketaerror","cut3genHPmch_trketaerror",100,0,0.01);
  TH1F* cut3genHPmch_trkdszerror = new TH1F("cut3genHPmch_trkdszerror","cut3genHPmch_trkdszerror",1000,-50,50);
  TH1F* cut3genHPmch_trkdsz = new TH1F("cut3genHPmch_trkdsz","cut3genHPmch_trkdsz",200,0,0.2);
  
  // Cut 3 - Scouting muons
  TH1F* cut3sct_mun = new TH1F("cut3sct_mun","cut3sct_mun",10,0,10);
  TH1F* cut3sct_mupt = new TH1F("cut3sct_mupt","cut3sct_mupt",1000,0,1000);
  TH1F* cut3sct_mueta = new TH1F("cut3sct_mueta","cut3sct_mueta",100,-2.5,2.5);
  TH1F* cut3sct_muphi = new TH1F("cut3sct_muphi","cut3sct_muphi",66,-3.3,3.3);
  TH1F* cut3sct_mudxy = new TH1F("cut3sct_mudxy","cut3sct_mudxy",2000,-10,10);
  TH1F* cut3sct_mulog10dxy = new TH1F("cut3sct_mulog10dxy","cut3sct_mulog10dxy",140,-3,4);
  TH1F* cut3sct_ecaliso = new TH1F("cut3sct_ecaliso","cut3sct_ecaliso",200,-10,10);
  TH1F* cut3sct_hcaliso = new TH1F("cut3sct_hcaliso","cut3sct_hcaliso",600,-30,30);
  TH1F* cut3sct_trkiso = new TH1F("cut3sct_trkiso","cut3sct_trkiso",1000,0,100);
  TH1F* cut3sct_chi2 = new TH1F("cut3sct_chi2","cut3sct_chi2",1000,0,100);
  TH1F* cut3sct_chi2_ndf = new TH1F("cut3sct_chi2_ndf","cut3sct_chi2_ndf",50,0,5);
  TH1F* cut3sct_charge = new TH1F("cut3sct_charge","cut3sct_charge",5,-2,3);
  TH1F* cut3sct_dz = new TH1F("cut3sct_dz","cut3sct_dz",1000,-50,50);
  TH1F* cut3sct_nvalidmuon_hits = new TH1F("cut3sct_nvalidmuon_hits","cut3sct_nvalidmuon_hits",100,0,100);
  TH1F* cut3sct_validpixelhits = new TH1F("cut3sct_validpixelhits","cut3sct_validpixelhits",60,0,60);
  TH1F* cut3sct_nmatchedstations = new TH1F("cut3sct_nmatchedstations","cut3sct_nmatchedstations",10,0,10);
  TH1F* cut3sct_trklaywmsr = new TH1F("cut3sct_trklaywmsr","cut3sct_trklaywmsr",20,0,20);
  TH1F* cut3sct_type = new TH1F("cut3sct_type","cut3sct_type",20,0,20);
  TH1F* cut3sct_nvalidstriphits = new TH1F("cut3sct_nvalidstriphits","cut3sct_nvalidstriphits",30,0,30);
  TH1F* cut3sct_trkqoverp = new TH1F("cut3sct_trkqoverp","cut3sct_trkqoverp",600,-0.3,0.3);
  TH1F* cut3sct_trklambda = new TH1F("cut3sct_trklambda","cut3sct_trklambda",300,-1.5,1.5);
  TH1F* cut3sct_trkpt = new TH1F("cut3sct_trkpt","cut3sct_trkpt",10000,0,100);
  TH1F* cut3sct_trkptsig = new TH1F("cut3sct_trkptsig","cut3sct_trkptsig",50000,0,5000);
  TH1F* cut3sct_trkphi = new TH1F("cut3sct_trkphi","cut3sct_trkphi",66,-3.3,3.3);
  TH1F* cut3sct_trketa = new TH1F("cut3sct_trketa","cut3sct_trketa",100,-2.5,2.5);
  TH1F* cut3sct_trkqoverperror = new TH1F("cut3sct_trkqoverperror","cut3sct_trkqoverperror",10000,0,0.1);
  TH1F* cut3sct_trklambdaerror = new TH1F("cut3sct_trklambdaerror","cut3sct_trklambdaerror",1000,0,1);
  TH1F* cut3sct_trkpterror = new TH1F("cut3sct_trkpterror","cut3sct_trkpterror",100,0,0.01);
  TH1F* cut3sct_trkphierror = new TH1F("cut3sct_trkphierror","cut3sct_trkphierror",100,0,0.01);
  TH1F* cut3sct_trketaerror = new TH1F("cut3sct_trketaerror","cut3sct_trketaerror",100,0,0.01);
  TH1F* cut3sct_trkdszerror = new TH1F("cut3sct_trkdszerror","cut3sct_trkdszerror",1000,-50,50);
  TH1F* cut3sct_trkdsz = new TH1F("cut3sct_trkdsz","cut3sct_trkdsz",200,0,0.2);

  std::cout<<"Total event: "<<tree.GetEntries()<<std::endl;

  int event=-1;
  while(tree.Next()) {
    
    event++;
    if(event%10000==0) std::cout<<event<<" done!"<<std::endl;
    //if(event>=100) break;
    
    int ngenmu = 0;
    int ngenHPmu = 0;
    int ngenothmu = 0;
    for(unsigned int genpart_ctr=0; genpart_ctr<(*n_genpart); genpart_ctr++) {
      if(TMath::Abs(genpart_eta->at(genpart_ctr))>2.5) continue;
      if(TMath::Abs(genpart_pdg->at(genpart_ctr))!=13) continue;
      
      ngenmu++;
      gen_mupt->Fill(genpart_pt->at(genpart_ctr));
      gen_mueta->Fill(genpart_eta->at(genpart_ctr));
      gen_muphi->Fill(genpart_phi->at(genpart_ctr));
      TVector3 muP;
      muP.SetPtEtaPhi(genpart_pt->at(genpart_ctr),genpart_eta->at(genpart_ctr),genpart_phi->at(genpart_ctr));
      double d0 = ((genpart_vx->at(genpart_ctr))*muP.Py())-((genpart_vy->at(genpart_ctr))*muP.Px());
      d0 = d0/genpart_pt->at(genpart_ctr);
      gen_mulog10d0->Fill(TMath::Log10(TMath::Abs(d0)));

      if( genpart_isHP->at(genpart_ctr)>0) {
	ngenHPmu++;
	genHP_mupt->Fill(genpart_pt->at(genpart_ctr));
	genHP_mueta->Fill(genpart_eta->at(genpart_ctr));
	genHP_muphi->Fill(genpart_phi->at(genpart_ctr));
	genHP_mulog10d0->Fill(TMath::Log10(TMath::Abs(d0)));
      }
      else {
	ngenothmu++;
	genoth_mupt->Fill(genpart_pt->at(genpart_ctr));
	genoth_mueta->Fill(genpart_eta->at(genpart_ctr));
	genoth_muphi->Fill(genpart_phi->at(genpart_ctr));
	genoth_mulog10d0->Fill(TMath::Log10(TMath::Abs(d0)));
      }
    }
    gen_mun->Fill(ngenmu);
    genHP_mun->Fill(ngenHPmu);
    genoth_mun->Fill(ngenothmu);
    //std::cout<<"|| \t";
    
    std::vector<unsigned> genHPmchmus;
    std::vector<unsigned> genothmchmus;
    std::vector<unsigned> genmchgens;
    std::vector<unsigned> genHPmchgens;
    std::vector<unsigned> genothmchgens;

    for(unsigned int mu_ctr=0; mu_ctr<(*n_mu); mu_ctr++) {
      
      if(TMath::Abs(muon_eta->at(mu_ctr))>2.5) continue;
      
      sct_mupt->Fill(muon_pt->at(mu_ctr));
      sct_mueta->Fill(muon_eta->at(mu_ctr));
      sct_muphi->Fill(muon_phi->at(mu_ctr));
      sct_mudxy->Fill(muon_dxy->at(mu_ctr));
      sct_mulog10dxy->Fill(TMath::Log10(TMath::Abs(muon_dxy->at(mu_ctr))));
      sct_ecaliso->Fill(muon_ecaliso->at(mu_ctr));
      sct_hcaliso->Fill(muon_hcaliso->at(mu_ctr));
      sct_trkiso->Fill(muon_trkiso->at(mu_ctr));
      sct_chi2->Fill(muon_chi2->at(mu_ctr));
      sct_chi2_ndf->Fill(muon_chi2->at(mu_ctr)/muon_ndof->at(mu_ctr));
      sct_charge->Fill(muon_charge->at(mu_ctr));
      sct_dz->Fill(muon_dz->at(mu_ctr));
      sct_nvalidmuon_hits->Fill(muon_nvalidmuon_hits->at(mu_ctr));
      sct_validpixelhits->Fill(muon_validpixelhits->at(mu_ctr));
      sct_nmatchedstations->Fill(muon_nmatchedstations->at(mu_ctr));
      sct_trklaywmsr->Fill(muon_trklaywmsr->at(mu_ctr));
      sct_type->Fill(muon_type->at(mu_ctr));
      sct_nvalidstriphits->Fill(muon_nvalidstriphits->at(mu_ctr));
      sct_trkqoverp->Fill(muon_trkqoverp->at(mu_ctr));
      sct_trklambda->Fill(muon_trklambda->at(mu_ctr));
      sct_trkpt->Fill(muon_trkpt->at(mu_ctr));
      sct_trkptsig->Fill(muon_trkpt->at(mu_ctr)/TMath::Sqrt(muon_trkpterror->at(mu_ctr)));
      sct_trkphi->Fill(muon_trkphi->at(mu_ctr));
      sct_trketa->Fill(muon_trketa->at(mu_ctr));
      sct_trkqoverperror->Fill(muon_trkqoverperror->at(mu_ctr));
      sct_trklambdaerror->Fill(muon_trklambdaerror->at(mu_ctr));
      sct_trkpterror->Fill(muon_trkpterror->at(mu_ctr));
      sct_trkphierror->Fill(muon_trkphierror->at(mu_ctr));
      sct_trketaerror->Fill(muon_trketaerror->at(mu_ctr));
      sct_trkdszerror->Fill(muon_trkdszerror->at(mu_ctr));
      sct_trkdsz->Fill(muon_trkdsz->at(mu_ctr));

      double dRmin = 10;
      for(unsigned int gen_ctr=0; gen_ctr<(*n_genpart); gen_ctr++) {
	
	if(TMath::Abs(genpart_pdg->at(gen_ctr))==13) {
	  TVector3 gen3vec;
	  gen3vec.SetPtEtaPhi(genpart_pt->at(gen_ctr),genpart_eta->at(gen_ctr),genpart_phi->at(gen_ctr));
	  TVector3 sct3vec;
	  sct3vec.SetPtEtaPhi(muon_pt->at(mu_ctr),muon_eta->at(mu_ctr),muon_phi->at(mu_ctr));
	  double dR = gen3vec.DeltaR(sct3vec);
	  sct_gendR->Fill(dR);
	  if(dR<dRmin) dRmin = dR;
	}
      }
      sct_gendRmin->Fill(dRmin);
      
      // Loop to find gen matched muon
      int i=0;
      for(unsigned int gen_ctr=0; gen_ctr<(*n_genpart); gen_ctr++) {
	
	bool found_mumatch = false;
	if(TMath::Abs(genpart_pdg->at(gen_ctr))==13) {
	  TVector3 gen3vec;
	  gen3vec.SetPtEtaPhi(genpart_pt->at(gen_ctr),genpart_eta->at(gen_ctr),genpart_phi->at(gen_ctr));
	  TVector3 sct3vec;
	  sct3vec.SetPtEtaPhi(muon_pt->at(mu_ctr),muon_eta->at(mu_ctr),muon_phi->at(mu_ctr));
	  double dR = gen3vec.DeltaR(sct3vec);
	  
	  //if(dR<0) cout<<dR<<endl;
	  // See if the muon has matched to another genparticle, should happen extremely rarely
	  if(dR<=0.7 && (std::find(genmchgens.begin(), genmchgens.end(), gen_ctr) == genmchgens.end())) {
	  //if(dR<=0.7) {	    
	    i++;
	    genmchgens.push_back(gen_ctr);
	    found_mumatch = true;
	    if(genpart_isHP->at(gen_ctr)>0) {
	      genHPmchgens.push_back(gen_ctr);
	      genHPmchmus.push_back(mu_ctr);
	    }
	    else {
	      genothmchgens.push_back(gen_ctr);
	      genothmchmus.push_back(mu_ctr);
	    }
	  }
	  if(found_mumatch) break;
	}
	
      }
      
    }// End of muon loop inside event loop
    sct_mun->Fill((*n_mu));
    
    for(unsigned int ctr=0; ctr<genHPmchgens.size(); ctr++) {
      genHPsctmch_mupdg->Fill(genpart_pdg->at(genHPmchgens[ctr]));
      genHPsctmch_mupt->Fill(genpart_pt->at(genHPmchgens[ctr]));
      genHPsctmch_mueta->Fill(genpart_eta->at(genHPmchgens[ctr]));
      genHPsctmch_muphi->Fill(genpart_phi->at(genHPmchgens[ctr]));
      TVector3 muP;
      muP.SetPtEtaPhi(genpart_pt->at(genHPmchgens[ctr]),genpart_eta->at(genHPmchgens[ctr]),genpart_phi->at(genHPmchgens[ctr]));
      double d0 = ((genpart_vx->at(genHPmchgens[ctr]))*muP.Py())-((genpart_vy->at(genHPmchgens[ctr]))*muP.Px());
      d0 = d0/genpart_pt->at(genHPmchgens[ctr]);
      genHPsctmch_mulog10d0->Fill(TMath::Log10(TMath::Abs(d0)));
    }
    genHPsctmch_mun->Fill(genHPmchgens.size());
    
    // Loop on genmatched mus
    for(unsigned int ctr=0; ctr<genHPmchmus.size(); ctr++) {
      
      genHPmch_mupt->Fill(muon_pt->at(genHPmchmus[ctr]));
      genHPmch_mueta->Fill(muon_eta->at(genHPmchmus[ctr]));
      genHPmch_muphi->Fill(muon_phi->at(genHPmchmus[ctr]));
      genHPmch_mulog10dxy->Fill(TMath::Log10(TMath::Abs(muon_dxy->at(genHPmchmus[ctr]))));
      genHPmch_ecaliso->Fill(muon_ecaliso->at(genHPmchmus[ctr]));
      genHPmch_hcaliso->Fill(muon_hcaliso->at(genHPmchmus[ctr]));
      genHPmch_trkiso->Fill(muon_trkiso->at(genHPmchmus[ctr]));
      genHPmch_chi2->Fill(muon_chi2->at(genHPmchmus[ctr]));
      genHPmch_chi2_ndf->Fill(muon_chi2->at(genHPmchmus[ctr])/muon_ndof->at(genHPmchmus[ctr]));
      genHPmch_charge->Fill(muon_charge->at(genHPmchmus[ctr]));
      genHPmch_mudxy->Fill(muon_dxy->at(genHPmchmus[ctr]));
      genHPmch_dz->Fill(muon_dz->at(genHPmchmus[ctr]));
      genHPmch_nvalidmuon_hits->Fill(muon_nvalidmuon_hits->at(genHPmchmus[ctr]));
      genHPmch_validpixelhits->Fill(muon_validpixelhits->at(genHPmchmus[ctr]));
      genHPmch_nmatchedstations->Fill(muon_nmatchedstations->at(genHPmchmus[ctr]));
      genHPmch_trklaywmsr->Fill(muon_trklaywmsr->at(genHPmchmus[ctr]));
      genHPmch_type->Fill(muon_type->at(genHPmchmus[ctr]));
      genHPmch_nvalidstriphits->Fill(muon_nvalidstriphits->at(genHPmchmus[ctr]));
      genHPmch_trkqoverp->Fill(muon_trkqoverp->at(genHPmchmus[ctr]));
      genHPmch_trklambda->Fill(muon_trklambda->at(genHPmchmus[ctr]));
      genHPmch_trkpt->Fill(muon_trkpt->at(genHPmchmus[ctr]));
      genHPmch_trkptsig->Fill(muon_trkpt->at(genHPmchmus[ctr])/TMath::Sqrt(muon_trkpterror->at(genHPmchmus[ctr])));
      genHPmch_trkphi->Fill(muon_trkphi->at(genHPmchmus[ctr]));
      genHPmch_trketa->Fill(muon_trketa->at(genHPmchmus[ctr]));
      genHPmch_trkqoverperror->Fill(muon_trkqoverperror->at(genHPmchmus[ctr]));
      genHPmch_trklambdaerror->Fill(muon_trklambdaerror->at(genHPmchmus[ctr]));
      genHPmch_trkpterror->Fill(muon_trkpterror->at(genHPmchmus[ctr]));
      genHPmch_trkphierror->Fill(muon_trkphierror->at(genHPmchmus[ctr]));
      genHPmch_trketaerror->Fill(muon_trketaerror->at(genHPmchmus[ctr]));
      genHPmch_trkdszerror->Fill(muon_trkdszerror->at(genHPmchmus[ctr]));
      genHPmch_trkdsz->Fill(muon_trkdsz->at(genHPmchmus[ctr]));      
    }
    genHPmch_mun->Fill(genHPmchmus.size());
    
    // Loop on genmatched mus
    for(unsigned int ctr=0; ctr<genothmchmus.size(); ctr++) {
      
      genothmch_mupt->Fill(muon_pt->at(genothmchmus[ctr]));
      genothmch_mueta->Fill(muon_eta->at(genothmchmus[ctr]));
      genothmch_muphi->Fill(muon_phi->at(genothmchmus[ctr]));
      genothmch_mulog10dxy->Fill(TMath::Log10(TMath::Abs(muon_dxy->at(genothmchmus[ctr]))));
      genothmch_ecaliso->Fill(muon_ecaliso->at(genothmchmus[ctr]));
      genothmch_hcaliso->Fill(muon_hcaliso->at(genothmchmus[ctr]));
      genothmch_trkiso->Fill(muon_trkiso->at(genothmchmus[ctr]));
      genothmch_chi2->Fill(muon_chi2->at(genothmchmus[ctr]));
      genothmch_chi2_ndf->Fill(muon_chi2->at(genothmchmus[ctr])/muon_ndof->at(genothmchmus[ctr]));
      genothmch_charge->Fill(muon_charge->at(genothmchmus[ctr]));
      genothmch_mudxy->Fill(muon_dxy->at(genothmchmus[ctr]));
      genothmch_dz->Fill(muon_dz->at(genothmchmus[ctr]));
      genothmch_nvalidmuon_hits->Fill(muon_nvalidmuon_hits->at(genothmchmus[ctr]));
      genothmch_validpixelhits->Fill(muon_validpixelhits->at(genothmchmus[ctr]));
      genothmch_nmatchedstations->Fill(muon_nmatchedstations->at(genothmchmus[ctr]));
      genothmch_trklaywmsr->Fill(muon_trklaywmsr->at(genothmchmus[ctr]));
      genothmch_type->Fill(muon_type->at(genothmchmus[ctr]));
      genothmch_nvalidstriphits->Fill(muon_nvalidstriphits->at(genothmchmus[ctr]));
      genothmch_trkqoverp->Fill(muon_trkqoverp->at(genothmchmus[ctr]));
      genothmch_trklambda->Fill(muon_trklambda->at(genothmchmus[ctr]));
      genothmch_trkpt->Fill(muon_trkpt->at(genothmchmus[ctr]));
      genothmch_trkptsig->Fill(muon_trkpt->at(genothmchmus[ctr])/TMath::Sqrt(muon_trkpterror->at(genothmchmus[ctr])));
      genothmch_trkphi->Fill(muon_trkphi->at(genothmchmus[ctr]));
      genothmch_trketa->Fill(muon_trketa->at(genothmchmus[ctr]));
      genothmch_trkqoverperror->Fill(muon_trkqoverperror->at(genothmchmus[ctr]));
      genothmch_trklambdaerror->Fill(muon_trklambdaerror->at(genothmchmus[ctr]));
      genothmch_trkpterror->Fill(muon_trkpterror->at(genothmchmus[ctr]));
      genothmch_trkphierror->Fill(muon_trkphierror->at(genothmchmus[ctr]));
      genothmch_trketaerror->Fill(muon_trketaerror->at(genothmchmus[ctr]));
      genothmch_trkdszerror->Fill(muon_trkdszerror->at(genothmchmus[ctr]));
      genothmch_trkdsz->Fill(muon_trkdsz->at(genothmchmus[ctr]));
      
    }
    genothmch_mun->Fill(genothmchmus.size());

    std::vector<unsigned> cut1genHPmchmus;
    std::vector<unsigned> cut1genothmchmus;
    std::vector<unsigned> cut1genmchgens;
    std::vector<unsigned> cut1genHPmchgens;
    std::vector<unsigned> cut1genothmchgens;

    // cut1 selection loop
    for(unsigned int mu_ctr=0; mu_ctr<(*n_mu); mu_ctr++) {
      
      if(TMath::Abs(muon_eta->at(mu_ctr))>2.5) continue;
      if((muon_chi2->at(mu_ctr)/muon_ndof->at(mu_ctr))>3) continue;
            
      // Loop to find gen matched muon
      for(unsigned int gen_ctr=0; gen_ctr<(*n_genpart); gen_ctr++) {
	
	bool found_mumatch = false;
	if(TMath::Abs(genpart_pdg->at(gen_ctr))==13) {
	  TVector3 gen3vec;
	  gen3vec.SetPtEtaPhi(genpart_pt->at(gen_ctr),genpart_eta->at(gen_ctr),genpart_phi->at(gen_ctr));
	  TVector3 sct3vec;
	  sct3vec.SetPtEtaPhi(muon_pt->at(mu_ctr),muon_eta->at(mu_ctr),muon_phi->at(mu_ctr));
	  double dR = gen3vec.DeltaR(sct3vec);
	  
	  if(dR<=0.7 && (std::find(cut1genmchgens.begin(), cut1genmchgens.end(), gen_ctr) == cut1genmchgens.end())) {
	    cut1genmchgens.push_back(gen_ctr);
	    found_mumatch = true;
	    if(genpart_isHP->at(gen_ctr)>0) {
	      cut1genHPmchgens.push_back(gen_ctr);
	      cut1genHPmchmus.push_back(mu_ctr);
	    }
	    else {
	      cut1genothmchgens.push_back(gen_ctr);
	      cut1genothmchmus.push_back(mu_ctr);
	    }
	  }
	  if(found_mumatch) break;
	}
	
      }
      
    }// End of cut1 muon loop inside event loop

    for(unsigned int ctr=0; ctr<cut1genHPmchgens.size(); ctr++) {
      cut1genHPsctmch_mupdg->Fill(genpart_pdg->at(cut1genHPmchgens[ctr]));
      cut1genHPsctmch_mupt->Fill(genpart_pt->at(cut1genHPmchgens[ctr]));
      cut1genHPsctmch_mueta->Fill(genpart_eta->at(cut1genHPmchgens[ctr]));
      cut1genHPsctmch_muphi->Fill(genpart_phi->at(cut1genHPmchgens[ctr]));
    }
    cut1genHPsctmch_mun->Fill(cut1genHPmchgens.size());
    
    // Loop on genmatched mus
    for(unsigned int ctr=0; ctr<cut1genHPmchmus.size(); ctr++) {
      
      cut1genHPmch_mupt->Fill(muon_pt->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_mueta->Fill(muon_eta->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_muphi->Fill(muon_phi->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_mulog10dxy->Fill(TMath::Log10(TMath::Abs(muon_dxy->at(cut1genHPmchmus[ctr]))));
      cut1genHPmch_ecaliso->Fill(muon_ecaliso->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_hcaliso->Fill(muon_hcaliso->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_trkiso->Fill(muon_trkiso->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_chi2->Fill(muon_chi2->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_chi2_ndf->Fill(muon_chi2->at(cut1genHPmchmus[ctr])/muon_ndof->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_charge->Fill(muon_charge->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_mudxy->Fill(muon_dxy->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_dz->Fill(muon_dz->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_nvalidmuon_hits->Fill(muon_nvalidmuon_hits->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_validpixelhits->Fill(muon_validpixelhits->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_nmatchedstations->Fill(muon_nmatchedstations->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_trklaywmsr->Fill(muon_trklaywmsr->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_type->Fill(muon_type->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_nvalidstriphits->Fill(muon_nvalidstriphits->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_trkqoverp->Fill(muon_trkqoverp->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_trklambda->Fill(muon_trklambda->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_trkpt->Fill(muon_trkpt->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_trkptsig->Fill(muon_trkpt->at(cut1genHPmchmus[ctr])/TMath::Sqrt(muon_trkpterror->at(cut1genHPmchmus[ctr])));
      cut1genHPmch_trkphi->Fill(muon_trkphi->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_trketa->Fill(muon_trketa->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_trkqoverperror->Fill(muon_trkqoverperror->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_trklambdaerror->Fill(muon_trklambdaerror->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_trkpterror->Fill(muon_trkpterror->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_trkphierror->Fill(muon_trkphierror->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_trketaerror->Fill(muon_trketaerror->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_trkdszerror->Fill(muon_trkdszerror->at(cut1genHPmchmus[ctr]));
      cut1genHPmch_trkdsz->Fill(muon_trkdsz->at(cut1genHPmchmus[ctr]));      
    }
    cut1genHPmch_mun->Fill(genHPmchmus.size());

    std::vector<unsigned> cut2genHPmchmus;
    std::vector<unsigned> cut2genothmchmus;
    std::vector<unsigned> cut2genmchgens;
    std::vector<unsigned> cut2genHPmchgens;
    std::vector<unsigned> cut2genothmchgens;

    // cut2 selection loop
    for(unsigned int mu_ctr=0; mu_ctr<(*n_mu); mu_ctr++) {
      
      if(TMath::Abs(muon_eta->at(mu_ctr))>2.5) continue;
      if(muon_trklaywmsr->at(mu_ctr)<6) continue;
                  
      // Loop to find gen matched muon
      for(unsigned int gen_ctr=0; gen_ctr<(*n_genpart); gen_ctr++) {
	
	bool found_mumatch = false;
	if(TMath::Abs(genpart_pdg->at(gen_ctr))==13) {
	  TVector3 gen3vec;
	  gen3vec.SetPtEtaPhi(genpart_pt->at(gen_ctr),genpart_eta->at(gen_ctr),genpart_phi->at(gen_ctr));
	  TVector3 sct3vec;
	  sct3vec.SetPtEtaPhi(muon_pt->at(mu_ctr),muon_eta->at(mu_ctr),muon_phi->at(mu_ctr));
	  double dR = gen3vec.DeltaR(sct3vec);
	  
	  if(dR<=0.7 && (std::find(cut2genmchgens.begin(), cut2genmchgens.end(), gen_ctr) == cut2genmchgens.end())) {
	    cut2genmchgens.push_back(gen_ctr);
	    found_mumatch = true;
	    if(genpart_isHP->at(gen_ctr)>0) {
	      cut2genHPmchgens.push_back(gen_ctr);
	      cut2genHPmchmus.push_back(mu_ctr);
	    }
	    else {
	      cut2genothmchgens.push_back(gen_ctr);
	      cut2genothmchmus.push_back(mu_ctr);
	    }
	  }
	  if(found_mumatch) break;
	}
	
      }
      
    }// End of cut2 muon loop inside event loop

    for(unsigned int ctr=0; ctr<cut2genHPmchgens.size(); ctr++) {
      cut2genHPsctmch_mupdg->Fill(genpart_pdg->at(cut2genHPmchgens[ctr]));
      cut2genHPsctmch_mupt->Fill(genpart_pt->at(cut2genHPmchgens[ctr]));
      cut2genHPsctmch_mueta->Fill(genpart_eta->at(cut2genHPmchgens[ctr]));
      cut2genHPsctmch_muphi->Fill(genpart_phi->at(cut2genHPmchgens[ctr]));
    }
    cut2genHPsctmch_mun->Fill(cut2genHPmchgens.size());
    
    // Loop on genmatched mus
    for(unsigned int ctr=0; ctr<cut2genHPmchmus.size(); ctr++) {
      
      cut2genHPmch_mupt->Fill(muon_pt->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_mueta->Fill(muon_eta->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_muphi->Fill(muon_phi->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_mulog10dxy->Fill(TMath::Log10(TMath::Abs(muon_dxy->at(cut2genHPmchmus[ctr]))));
      cut2genHPmch_ecaliso->Fill(muon_ecaliso->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_hcaliso->Fill(muon_hcaliso->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_trkiso->Fill(muon_trkiso->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_chi2->Fill(muon_chi2->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_chi2_ndf->Fill(muon_chi2->at(cut2genHPmchmus[ctr])/muon_ndof->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_charge->Fill(muon_charge->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_mudxy->Fill(muon_dxy->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_dz->Fill(muon_dz->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_nvalidmuon_hits->Fill(muon_nvalidmuon_hits->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_validpixelhits->Fill(muon_validpixelhits->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_nmatchedstations->Fill(muon_nmatchedstations->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_trklaywmsr->Fill(muon_trklaywmsr->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_type->Fill(muon_type->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_nvalidstriphits->Fill(muon_nvalidstriphits->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_trkqoverp->Fill(muon_trkqoverp->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_trklambda->Fill(muon_trklambda->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_trkpt->Fill(muon_trkpt->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_trkptsig->Fill(muon_trkpt->at(cut2genHPmchmus[ctr])/TMath::Sqrt(muon_trkpterror->at(cut2genHPmchmus[ctr])));
      cut2genHPmch_trkphi->Fill(muon_trkphi->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_trketa->Fill(muon_trketa->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_trkqoverperror->Fill(muon_trkqoverperror->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_trklambdaerror->Fill(muon_trklambdaerror->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_trkpterror->Fill(muon_trkpterror->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_trkphierror->Fill(muon_trkphierror->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_trketaerror->Fill(muon_trketaerror->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_trkdszerror->Fill(muon_trkdszerror->at(cut2genHPmchmus[ctr]));
      cut2genHPmch_trkdsz->Fill(muon_trkdsz->at(cut2genHPmchmus[ctr]));      
    }
    cut2genHPmch_mun->Fill(genHPmchmus.size());

    std::vector<unsigned> cut3genHPmchmus;
    std::vector<unsigned> cut3genothmchmus;
    std::vector<unsigned> cut3genmchgens;
    std::vector<unsigned> cut3genHPmchgens;
    std::vector<unsigned> cut3genothmchgens;

    // cut3 selection loop
    int cut3sctctr = 0;
    for(unsigned int mu_ctr=0; mu_ctr<(*n_mu); mu_ctr++) {
      
      if(TMath::Abs(muon_eta->at(mu_ctr))>2.5) continue;
      if((muon_chi2->at(mu_ctr)/muon_ndof->at(mu_ctr))>3) continue;
      if(muon_trklaywmsr->at(mu_ctr)<6) continue;

      cut3sctctr++;
      cut3sct_mupt->Fill(muon_pt->at(mu_ctr));
      cut3sct_mueta->Fill(muon_eta->at(mu_ctr));
      cut3sct_muphi->Fill(muon_phi->at(mu_ctr));
      cut3sct_mudxy->Fill(muon_dxy->at(mu_ctr));
      cut3sct_mulog10dxy->Fill(TMath::Log10(TMath::Abs(muon_dxy->at(mu_ctr))));
      cut3sct_ecaliso->Fill(muon_ecaliso->at(mu_ctr));
      cut3sct_hcaliso->Fill(muon_hcaliso->at(mu_ctr));
      cut3sct_trkiso->Fill(muon_trkiso->at(mu_ctr));
      cut3sct_chi2->Fill(muon_chi2->at(mu_ctr));
      cut3sct_chi2_ndf->Fill(muon_chi2->at(mu_ctr)/muon_ndof->at(mu_ctr));
      cut3sct_charge->Fill(muon_charge->at(mu_ctr));
      cut3sct_dz->Fill(muon_dz->at(mu_ctr));
      cut3sct_nvalidmuon_hits->Fill(muon_nvalidmuon_hits->at(mu_ctr));
      cut3sct_validpixelhits->Fill(muon_validpixelhits->at(mu_ctr));
      cut3sct_nmatchedstations->Fill(muon_nmatchedstations->at(mu_ctr));
      cut3sct_trklaywmsr->Fill(muon_trklaywmsr->at(mu_ctr));
      cut3sct_type->Fill(muon_type->at(mu_ctr));
      cut3sct_nvalidstriphits->Fill(muon_nvalidstriphits->at(mu_ctr));
      cut3sct_trkqoverp->Fill(muon_trkqoverp->at(mu_ctr));
      cut3sct_trklambda->Fill(muon_trklambda->at(mu_ctr));
      cut3sct_trkpt->Fill(muon_trkpt->at(mu_ctr));
      cut3sct_trkptsig->Fill(muon_trkpt->at(mu_ctr)/TMath::Sqrt(muon_trkpterror->at(mu_ctr)));
      cut3sct_trkphi->Fill(muon_trkphi->at(mu_ctr));
      cut3sct_trketa->Fill(muon_trketa->at(mu_ctr));
      cut3sct_trkqoverperror->Fill(muon_trkqoverperror->at(mu_ctr));
      cut3sct_trklambdaerror->Fill(muon_trklambdaerror->at(mu_ctr));
      cut3sct_trkpterror->Fill(muon_trkpterror->at(mu_ctr));
      cut3sct_trkphierror->Fill(muon_trkphierror->at(mu_ctr));
      cut3sct_trketaerror->Fill(muon_trketaerror->at(mu_ctr));
      cut3sct_trkdszerror->Fill(muon_trkdszerror->at(mu_ctr));
      cut3sct_trkdsz->Fill(muon_trkdsz->at(mu_ctr));

      // Loop to find gen matched muon
      for(unsigned int gen_ctr=0; gen_ctr<(*n_genpart); gen_ctr++) {
	
	bool found_mumatch = false;
	if(TMath::Abs(genpart_pdg->at(gen_ctr))==13) {
	  TVector3 gen3vec;
	  gen3vec.SetPtEtaPhi(genpart_pt->at(gen_ctr),genpart_eta->at(gen_ctr),genpart_phi->at(gen_ctr));
	  TVector3 sct3vec;
	  sct3vec.SetPtEtaPhi(muon_pt->at(mu_ctr),muon_eta->at(mu_ctr),muon_phi->at(mu_ctr));
	  double dR = gen3vec.DeltaR(sct3vec);
	  
	  if(dR<=0.7 && (std::find(cut3genmchgens.begin(), cut3genmchgens.end(), gen_ctr) == cut3genmchgens.end())) {
	    cut3genmchgens.push_back(gen_ctr);
	    found_mumatch = true;
	    if(genpart_isHP->at(gen_ctr)>0) {
	      cut3genHPmchgens.push_back(gen_ctr);
	      cut3genHPmchmus.push_back(mu_ctr);
	    }
	    else {
	      cut3genothmchgens.push_back(gen_ctr);
	      cut3genothmchmus.push_back(mu_ctr);
	    }
	  }
	  if(found_mumatch) break;
	}
	
      }
      
    }// End of cut3 muon loop inside event loop
    cut3sct_mun->Fill(cut3sctctr);

    for(unsigned int ctr=0; ctr<cut3genHPmchgens.size(); ctr++) {
      cut3genHPsctmch_mupdg->Fill(genpart_pdg->at(cut3genHPmchgens[ctr]));
      cut3genHPsctmch_mupt->Fill(genpart_pt->at(cut3genHPmchgens[ctr]));
      cut3genHPsctmch_mueta->Fill(genpart_eta->at(cut3genHPmchgens[ctr]));
      cut3genHPsctmch_muphi->Fill(genpart_phi->at(cut3genHPmchgens[ctr]));
    }
    cut3genHPsctmch_mun->Fill(cut3genHPmchgens.size());
    
    // Loop on genmatched mus
    for(unsigned int ctr=0; ctr<cut3genHPmchmus.size(); ctr++) {
      
      cut3genHPmch_mupt->Fill(muon_pt->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_mueta->Fill(muon_eta->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_muphi->Fill(muon_phi->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_mulog10dxy->Fill(TMath::Log10(TMath::Abs(muon_dxy->at(cut3genHPmchmus[ctr]))));
      cut3genHPmch_ecaliso->Fill(muon_ecaliso->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_hcaliso->Fill(muon_hcaliso->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_trkiso->Fill(muon_trkiso->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_chi2->Fill(muon_chi2->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_chi2_ndf->Fill(muon_chi2->at(cut3genHPmchmus[ctr])/muon_ndof->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_charge->Fill(muon_charge->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_mudxy->Fill(muon_dxy->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_dz->Fill(muon_dz->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_nvalidmuon_hits->Fill(muon_nvalidmuon_hits->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_validpixelhits->Fill(muon_validpixelhits->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_nmatchedstations->Fill(muon_nmatchedstations->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_trklaywmsr->Fill(muon_trklaywmsr->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_type->Fill(muon_type->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_nvalidstriphits->Fill(muon_nvalidstriphits->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_trkqoverp->Fill(muon_trkqoverp->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_trklambda->Fill(muon_trklambda->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_trkpt->Fill(muon_trkpt->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_trkptsig->Fill(muon_trkpt->at(cut3genHPmchmus[ctr])/TMath::Sqrt(muon_trkpterror->at(cut3genHPmchmus[ctr])));
      cut3genHPmch_trkphi->Fill(muon_trkphi->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_trketa->Fill(muon_trketa->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_trkqoverperror->Fill(muon_trkqoverperror->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_trklambdaerror->Fill(muon_trklambdaerror->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_trkpterror->Fill(muon_trkpterror->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_trkphierror->Fill(muon_trkphierror->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_trketaerror->Fill(muon_trketaerror->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_trkdszerror->Fill(muon_trkdszerror->at(cut3genHPmchmus[ctr]));
      cut3genHPmch_trkdsz->Fill(muon_trkdsz->at(cut3genHPmchmus[ctr]));      
    }
    cut3genHPmch_mun->Fill(genHPmchmus.size());

    genHPmchmus.clear();
    genothmchmus.clear();
    genmchgens.clear();
    genHPmchgens.clear();
    genothmchgens.clear();
    cut1genHPmchmus.clear();
    cut1genothmchmus.clear();
    cut1genmchgens.clear();
    cut1genHPmchgens.clear();
    cut1genothmchgens.clear();
    cut2genHPmchmus.clear();
    cut2genothmchmus.clear();
    cut2genmchgens.clear();
    cut2genHPmchgens.clear();
    cut2genothmchgens.clear();
    cut3genHPmchmus.clear();
    cut3genothmchmus.clear();
    cut3genmchgens.clear();
    cut3genHPmchgens.clear();
    cut3genothmchgens.clear();

  } // End of event loop
  
  outfile->Write();
  outfile->Close();
  tree.Delete();
  return -1;
}

int basicAnalyzer_mu() {

  for(int i = 1; i<=17; i++) {
    //if(i==16) continue;
    basicAnalyzer_mu_onefile(i);
  }

  return -1;
}
