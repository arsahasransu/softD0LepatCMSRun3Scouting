
std::vector<int> basicAnalyzer_eventMuEg_onefile(int fNum) {

  std::stringstream instream;
  instream<<"/pnfs/iihe/cms/store/user/asahasra/SingletTripletHDMToDisplacedL_M200deltaM20ctau3cm_TuneCP5_14TeV-madgraph-pythia8/STHDM_M200dM20ctau3cm_Run3Winter2021MC_crabRunSkim2_asahasra/210615_101538/0000/scoutingNTuple_"<<fNum<<".root";
  //instream<<"/pnfs/iihe/cms/store/user/asahasra/SingletTripletHDMToDisplacedL_M200deltaM20ctau30cm_TuneCP5_14TeV-madgraph-pythia8/STHDM_M200dM20ctau30cm_Run3Winter2021MC_crabRunSkim2_asahasra/210615_101821/0000/scoutingNTuple_"<<fNum<<".root";
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

  std::stringstream outstream;
  outstream<<"hists_mu_STHDM3cm_"<<fNum<<".root";
  //outstream<<"histsevent_mueg_STHDM30cm_"<<fNum<<".root";
  std::string outfilename = outstream.str();
  TFile* outfile = new TFile(outfilename.c_str(),"RECREATE");

  // Other GenMatched muons

  std::cout<<"Total event: "<<tree.GetEntries()<<std::endl;
  int Nmumu=0, Nmuel=0, Nmuelcheck=0, Nelel=0, N1tau=0, Noth=0;
  int mumchEvtCnt = 0, elmchEvtCnt=0, muelmchEvtCnt=0;
  int cut1mumchEvtCnt = 0, cut1elmchEvtCnt=0, cut1muelmchEvtCnt=0, cut1muelgenEvtCnt=0;
  int cut1muelmchEvtCntsr1=0, cut1muelgenEvtCntsr1=0;
  int cut1muelmchEvtCntsr2=0, cut1muelgenEvtCntsr2=0;
  int cut1muelmchEvtCntsr3=0, cut1muelgenEvtCntsr3=0;
  int cut1muelmchEvtCntcr=0, cut1muelgenEvtCntcr=0;
  int cut2mumchEvtCnt = 0, cut2elmchEvtCnt=0, cut2muelmchEvtCnt=0, cut2muelgenEvtCnt=0;
  int cut2muelmchEvtCntsr1=0, cut2muelgenEvtCntsr1=0;
  int cut2muelmchEvtCntsr2=0, cut2muelgenEvtCntsr2=0;
  int cut2muelmchEvtCntsr3=0, cut2muelgenEvtCntsr3=0;
  int cut2muelmchEvtCntcr=0, cut2muelgenEvtCntcr=0;
  
  bool isSR3 = false;
  bool isSR2 = false;
  bool isSR1 = false;
  bool isCR = false;


  int event=-1;
  while(tree.Next()) {
    
    event++;
    if(event%10000==0) std::cout<<event<<" done!"<<std::endl;
    
    int NgenHPmu=0, NgenHPele=0, NgenHPtau=0;
    int genctr_mupos = -1, genctr_elpos = -1;
    for(unsigned int genpart_ctr=0; genpart_ctr<(*n_genpart); genpart_ctr++) {
      if( genpart_isHP->at(genpart_ctr)==0) continue;

      if(TMath::Abs(genpart_pdg->at(genpart_ctr))==11) {
	NgenHPele++;
	genctr_elpos = genpart_ctr;
      }
      if(TMath::Abs(genpart_pdg->at(genpart_ctr))==13) {
	NgenHPmu++;
	genctr_mupos = genpart_ctr;
      }
      if(TMath::Abs(genpart_pdg->at(genpart_ctr))==15) NgenHPtau++;
      
    }

    if(NgenHPmu==2) Nmumu++;
    if(NgenHPmu==1 && NgenHPele==1) Nmuel++;
    if(NgenHPele==2) Nelel++;
    if(NgenHPtau>=1) N1tau++;
    if(NgenHPmu!=2 && NgenHPmu+NgenHPele!=2 && NgenHPele!=2 && NgenHPtau<1) Noth++;

    if(NgenHPmu!=1 || NgenHPele!=1) continue;
    if(genctr_elpos==-1 || genctr_mupos==-1) cout<<"Weird"<<endl; // Check to ensure that the correct gen particles are assigned
    Nmuelcheck++;

    isSR3 = false;
    isSR2 = false;
    isSR1 = false;
    isCR = false;

    TVector3 muP;
    muP.SetPtEtaPhi(genpart_pt->at(genctr_mupos),genpart_eta->at(genctr_mupos),genpart_phi->at(genctr_mupos));
    double mud0 = ((genpart_vx->at(genctr_mupos))*muP.Py())-((genpart_vy->at(genctr_mupos))*muP.Px());
    mud0 = mud0/genpart_pt->at(genctr_mupos);
    TVector3 elP;
    elP.SetPtEtaPhi(genpart_pt->at(genctr_elpos),genpart_eta->at(genctr_elpos),genpart_phi->at(genctr_elpos));
    double eld0 = ((genpart_vx->at(genctr_elpos))*elP.Py())-((genpart_vy->at(genctr_elpos))*elP.Px());
    eld0 = eld0/genpart_pt->at(genctr_elpos);
    if(abs(mud0)>0.1 && abs(mud0)<10 && abs(eld0)>0.1 && abs(eld0)<10) isSR3 = true;
    else if(abs(mud0)>0.05 && abs(mud0)<10 && abs(eld0)>0.05 && abs(eld0)<10) isSR2 = true;
    else if(abs(mud0)>0.02 && abs(mud0)<10 && abs(eld0)>0.02 && abs(eld0)<10) isSR1 = true;
    else isCR = true;

    if(genpart_pt->at(genctr_mupos)>42 && genpart_eta->at(genctr_mupos)<2.5 && genpart_pt->at(genctr_elpos)>40 && genpart_eta->at(genctr_elpos)<2.5) {
      cut1muelgenEvtCnt++;
      if(isSR3) cut1muelgenEvtCntsr3++;
      if(isSR2) cut1muelgenEvtCntsr2++;
      if(isSR1) cut1muelgenEvtCntsr1++;
      if(isCR) cut1muelgenEvtCntcr++;
    }
    if(genpart_pt->at(genctr_mupos)>20 && genpart_eta->at(genctr_mupos)<2.5 && genpart_pt->at(genctr_elpos)>20 && genpart_eta->at(genctr_elpos)<2.5) {
      cut2muelgenEvtCnt++;
      if(isSR3) cut2muelgenEvtCntsr3++;
      if(isSR2) cut2muelgenEvtCntsr2++;
      if(isSR1) cut2muelgenEvtCntsr1++;
      if(isCR) cut2muelgenEvtCntcr++;
    }

    // Loop for muons
    int sct_mupos = -1;
    for(unsigned int mu_ctr=0; mu_ctr<(*n_mu); mu_ctr++) {
      
      if(TMath::Abs(muon_eta->at(mu_ctr))>2.5) continue;

      TVector3 gen3vec;
      gen3vec.SetPtEtaPhi(genpart_pt->at(genctr_mupos),genpart_eta->at(genctr_mupos),genpart_phi->at(genctr_mupos));
      TVector3 sct3vec;
      sct3vec.SetPtEtaPhi(muon_pt->at(mu_ctr),muon_eta->at(mu_ctr),muon_phi->at(mu_ctr));
      double dR = gen3vec.DeltaR(sct3vec);

      if(dR<=0.7) {
	sct_mupos = mu_ctr;
	break;
      }
    }

    if(sct_mupos!=-1) mumchEvtCnt++;
    
    // Loop for electrons
    int sct_elpos = -1;
    for(unsigned int ele_ctr=0; ele_ctr<(*n_ele); ele_ctr++) {
      
      if(TMath::Abs(ele_eta->at(ele_ctr))>2.5) continue;

      TVector3 gen3vec;
      gen3vec.SetPtEtaPhi(genpart_pt->at(genctr_elpos),genpart_eta->at(genctr_elpos),genpart_phi->at(genctr_elpos));
      TVector3 sct3vec;
      sct3vec.SetPtEtaPhi(ele_pt->at(ele_ctr),ele_eta->at(ele_ctr),ele_phi->at(ele_ctr));
      double dR = gen3vec.DeltaR(sct3vec);
      
      if(dR<=0.4) {
	sct_elpos = ele_ctr;
	break;
      }
    }  

    if(sct_elpos!=-1) elmchEvtCnt++;

    if(sct_mupos!=-1 && sct_elpos!=-1) muelmchEvtCnt++;

    // cut1 - pt40 Gev
    // Loop for muons
    int cut1sct_mupos = -1;
    for(unsigned int mu_ctr=0; mu_ctr<(*n_mu); mu_ctr++) {
      
      if(TMath::Abs(muon_pt->at(mu_ctr))<40) continue;
      if(TMath::Abs(muon_eta->at(mu_ctr))>2.5) continue;

      TVector3 gen3vec;
      gen3vec.SetPtEtaPhi(genpart_pt->at(genctr_mupos),genpart_eta->at(genctr_mupos),genpart_phi->at(genctr_mupos));
      TVector3 sct3vec;
      sct3vec.SetPtEtaPhi(muon_pt->at(mu_ctr),muon_eta->at(mu_ctr),muon_phi->at(mu_ctr));
      double dR = gen3vec.DeltaR(sct3vec);

      if(dR<=0.7) {
	cut1sct_mupos = mu_ctr;
	break;
      }
    }

    if(cut1sct_mupos!=-1) cut1mumchEvtCnt++;
    
    // Loop for electrons
    int cut1sct_elpos = -1;
    for(unsigned int ele_ctr=0; ele_ctr<(*n_ele); ele_ctr++) {
      
      if(TMath::Abs(ele_pt->at(ele_ctr))<40) continue;
      if(TMath::Abs(ele_eta->at(ele_ctr))>2.5) continue;

      TVector3 gen3vec;
      gen3vec.SetPtEtaPhi(genpart_pt->at(genctr_elpos),genpart_eta->at(genctr_elpos),genpart_phi->at(genctr_elpos));
      TVector3 sct3vec;
      sct3vec.SetPtEtaPhi(ele_pt->at(ele_ctr),ele_eta->at(ele_ctr),ele_phi->at(ele_ctr));
      double dR = gen3vec.DeltaR(sct3vec);
      
      if(dR<=0.4) {
	cut1sct_elpos = ele_ctr;
	break;
      }
    }  

    if(cut1sct_elpos!=-1) cut1elmchEvtCnt++;

    if(cut1sct_mupos!=-1 && cut1sct_elpos!=-1) {
      cut1muelmchEvtCnt++;
      if(isSR3) cut1muelmchEvtCntsr3++;
      if(isSR2) cut1muelmchEvtCntsr2++;
      if(isSR1) cut1muelmchEvtCntsr1++;
      if(isCR) cut1muelmchEvtCntcr++;
    }
    
    // cut2 - pt20 Gev
    // Loop for muons
    int cut2sct_mupos = -1;
    for(unsigned int mu_ctr=0; mu_ctr<(*n_mu); mu_ctr++) {
      
      if(TMath::Abs(muon_pt->at(mu_ctr))<20) continue;
      if(TMath::Abs(muon_eta->at(mu_ctr))>2.5) continue;

      TVector3 gen3vec;
      gen3vec.SetPtEtaPhi(genpart_pt->at(genctr_mupos),genpart_eta->at(genctr_mupos),genpart_phi->at(genctr_mupos));
      TVector3 sct3vec;
      sct3vec.SetPtEtaPhi(muon_pt->at(mu_ctr),muon_eta->at(mu_ctr),muon_phi->at(mu_ctr));
      double dR = gen3vec.DeltaR(sct3vec);

      if(dR<=0.7) {
	cut2sct_mupos = mu_ctr;
	break;
      }
    }

    if(cut2sct_mupos!=-1) cut2mumchEvtCnt++;
    
    // Loop for electrons
    int cut2sct_elpos = -1;
    for(unsigned int ele_ctr=0; ele_ctr<(*n_ele); ele_ctr++) {
      
      if(TMath::Abs(ele_pt->at(ele_ctr))<20) continue;
      if(TMath::Abs(ele_eta->at(ele_ctr))>2.5) continue;

      TVector3 gen3vec;
      gen3vec.SetPtEtaPhi(genpart_pt->at(genctr_elpos),genpart_eta->at(genctr_elpos),genpart_phi->at(genctr_elpos));
      TVector3 sct3vec;
      sct3vec.SetPtEtaPhi(ele_pt->at(ele_ctr),ele_eta->at(ele_ctr),ele_phi->at(ele_ctr));
      double dR = gen3vec.DeltaR(sct3vec);
      
      if(dR<=0.4) {
	cut2sct_elpos = ele_ctr;
	break;
      }
    }  

    if(cut2sct_elpos!=-1) cut2elmchEvtCnt++;

    if(cut2sct_mupos!=-1 && cut2sct_elpos!=-1) {
      cut2muelmchEvtCnt++;
      if(isSR3) cut2muelmchEvtCntsr3++;
      if(isSR2) cut2muelmchEvtCntsr2++;
      if(isSR1) cut2muelmchEvtCntsr1++;
      if(isCR) cut2muelmchEvtCntcr++;
    }

  } // End of event loop
  
  // Pack the numbers
  std::vector<int> outNums;
  outNums.push_back(Nmumu);
  outNums.push_back(Nmuel);
  outNums.push_back(Nelel);
  outNums.push_back(N1tau);
  outNums.push_back(Noth);

  outNums.push_back(Nmuelcheck);

  outNums.push_back(mumchEvtCnt);
  outNums.push_back(elmchEvtCnt);
  outNums.push_back(muelmchEvtCnt);

  outNums.push_back(cut1mumchEvtCnt);
  outNums.push_back(cut1elmchEvtCnt);
  outNums.push_back(cut1muelmchEvtCnt);
  outNums.push_back(cut1muelgenEvtCnt);

  outNums.push_back(cut2mumchEvtCnt);
  outNums.push_back(cut2elmchEvtCnt);
  outNums.push_back(cut2muelmchEvtCnt);
  outNums.push_back(cut2muelgenEvtCnt);

  outNums.push_back(cut1muelmchEvtCntsr3);
  outNums.push_back(cut1muelgenEvtCntsr3);
  outNums.push_back(cut1muelmchEvtCntsr2);
  outNums.push_back(cut1muelgenEvtCntsr2);
  outNums.push_back(cut1muelmchEvtCntsr1);
  outNums.push_back(cut1muelgenEvtCntsr1);
  outNums.push_back(cut1muelmchEvtCntcr);
  outNums.push_back(cut1muelgenEvtCntcr);

  outNums.push_back(cut2muelmchEvtCntsr3);
  outNums.push_back(cut2muelgenEvtCntsr3);
  outNums.push_back(cut2muelmchEvtCntsr2);
  outNums.push_back(cut2muelgenEvtCntsr2);
  outNums.push_back(cut2muelmchEvtCntsr1);
  outNums.push_back(cut2muelgenEvtCntsr1);
  outNums.push_back(cut2muelmchEvtCntcr);
  outNums.push_back(cut2muelgenEvtCntcr);

  outfile->Write();
  outfile->Close();
  tree.Delete();

  return outNums;
}

int basicAnalyzer_eventMuEg() {

  std::vector<int> outNums;
  for(int i = 1; i<=21; i++) {
    if(i==16) continue;
    std::vector<int> outNumsOneFile;
    outNumsOneFile = basicAnalyzer_eventMuEg_onefile(i);

    for(int j=0; j<outNumsOneFile.size(); j++) {
      if(i==1) {
	outNums.push_back(outNumsOneFile[j]);
      }
      else {
	outNums[j] += outNumsOneFile[j];
      }
    }

  }

  std::cout<<"MuMu topology: "<<outNums[0]<<std::endl;
  std::cout<<"MuEl topology: "<<outNums[1]<<std::endl;
  std::cout<<"ElEl topology: "<<outNums[2]<<std::endl;
  std::cout<<"1 Tau topology: "<<outNums[3]<<std::endl;
  std::cout<<"Oth topology: "<<outNums[4]<<std::endl;

  std::cout<<"MuEl check topology: "<<outNums[5]<<std::endl;

  std::cout<<"MuEl topology: Mu Eff - "<<outNums[6]<<std::endl;
  std::cout<<"MuEl topology: El Eff - "<<outNums[7]<<std::endl;
  std::cout<<"MuEl topology: MuEl Eff - "<<outNums[8]<<std::endl;

  std::cout<<"cut1MuEl topology: Mu Eff - "<<outNums[9]<<std::endl;
  std::cout<<"cut1MuEl topology: El Eff - "<<outNums[10]<<std::endl;
  std::cout<<"cut1MuEl topology: MuEl Eff - "<<outNums[11]<<std::endl;
  std::cout<<"cut1MuEl topology: MuEl Gen - "<<outNums[12]<<std::endl;

  std::cout<<"cut2MuEl topology: Mu Eff - "<<outNums[13]<<std::endl;
  std::cout<<"cut2MuEl topology: El Eff - "<<outNums[14]<<std::endl;
  std::cout<<"cut2MuEl topology: MuEl Eff - "<<outNums[15]<<std::endl;
  std::cout<<"cut2MuEl topology: MuEl Gen - "<<outNums[16]<<std::endl;

  std::cout<<"cut1MuEl topology: SR3 - "<<outNums[17]<<std::endl;
  std::cout<<"cut1MuEl topology: SR3 - "<<outNums[18]<<std::endl;
  std::cout<<"cut1MuEl topology: SR2 - "<<outNums[19]<<std::endl;
  std::cout<<"cut1MuEl topology: SR2 - "<<outNums[20]<<std::endl;
  std::cout<<"cut1MuEl topology: SR1 - "<<outNums[21]<<std::endl;
  std::cout<<"cut1MuEl topology: SR1 - "<<outNums[22]<<std::endl;
  std::cout<<"cut1MuEl topology: CR - "<<outNums[23]<<std::endl;
  std::cout<<"cut1MuEl topology: CR - "<<outNums[24]<<std::endl;

  std::cout<<"cut2MuEl topology: SR3 - "<<outNums[25]<<std::endl;
  std::cout<<"cut2MuEl topology: SR3 - "<<outNums[26]<<std::endl;
  std::cout<<"cut2MuEl topology: SR2 - "<<outNums[27]<<std::endl;
  std::cout<<"cut2MuEl topology: SR2 - "<<outNums[28]<<std::endl;
  std::cout<<"cut2MuEl topology: SR1 - "<<outNums[29]<<std::endl;
  std::cout<<"cut2MuEl topology: SR1 - "<<outNums[30]<<std::endl;
  std::cout<<"cut2MuEl topology: CR - "<<outNums[31]<<std::endl;
  std::cout<<"cut2MuEl topology: CR - "<<outNums[32]<<std::endl;

  return -1;
}
