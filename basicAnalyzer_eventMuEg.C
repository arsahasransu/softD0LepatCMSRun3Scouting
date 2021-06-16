
int basicAnalyzer_eventMuEg() {

  TFile infile("./data/ARTree_tuple4.root");
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

  TFile* outfile = new TFile("hists_ele.root","RECREATE");

  // Other GenMatched muons

  std::cout<<"Total event: "<<tree.GetEntries()<<std::endl;
  int Nmumu=0, Nmuel=0, Nmuelcheck=0, Nelel=0, N1tau=0, Noth=0;
  int mumchEvtCnt = 0, elmchEvtCnt=0, muelmchEvtCnt=0;
  int cut1mumchEvtCnt = 0, cut1elmchEvtCnt=0, cut1muelmchEvtCnt=0;
  int cut2mumchEvtCnt = 0, cut2elmchEvtCnt=0, cut2muelmchEvtCnt=0;
  
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

    if(cut1sct_mupos!=-1 && cut1sct_elpos!=-1) cut1muelmchEvtCnt++;

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

    if(cut2sct_mupos!=-1 && cut2sct_elpos!=-1) cut2muelmchEvtCnt++;

  } // End of event loop
  
  std::cout<<"MuMu topology: "<<Nmumu<<std::endl;
  std::cout<<"MuEl topology: "<<Nmuel<<std::endl;
  std::cout<<"ElEl topology: "<<Nelel<<std::endl;
  std::cout<<"1 Tau topology: "<<N1tau<<std::endl;
  std::cout<<"Oth topology: "<<Noth<<std::endl;

  std::cout<<"MuEl check topology: "<<Nmuelcheck<<std::endl;

  std::cout<<"MuEl topology: Mu Eff - "<<mumchEvtCnt<<std::endl;
  std::cout<<"MuEl topology: El Eff - "<<elmchEvtCnt<<std::endl;
  std::cout<<"MuEl topology: MuEl Eff - "<<muelmchEvtCnt<<std::endl;

  std::cout<<"cut1MuEl topology: Mu Eff - "<<cut1mumchEvtCnt<<std::endl;
  std::cout<<"cut1MuEl topology: El Eff - "<<cut1elmchEvtCnt<<std::endl;
  std::cout<<"cut1MuEl topology: MuEl Eff - "<<cut1muelmchEvtCnt<<std::endl;

  std::cout<<"cut2MuEl topology: Mu Eff - "<<cut2mumchEvtCnt<<std::endl;
  std::cout<<"cut2MuEl topology: El Eff - "<<cut2elmchEvtCnt<<std::endl;
  std::cout<<"cut2MuEl topology: MuEl Eff - "<<cut2muelmchEvtCnt<<std::endl;

  outfile->Write();
  outfile->Close();
  tree.Delete();
  return -1;
}
