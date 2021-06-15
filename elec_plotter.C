std::map<TString, TString> varnametotitle{
  {"elept", "e p_{T} / GeV"},
  {"eleeta", "e #eta"},
    {"elephi", "e #phi"},
      {"elelog10d0","e log_{10} d_{0} / log_{10} cm"}
};

int plottersinglehist(TString cutname, TString histname, int binl=-1, int binh=-1, int rebin=1, bool logY=false) {

  histname = cutname+"_"+histname;
  TFile* file = TFile::Open("hists_ele.root","READ");
  TH1F* hist = (TH1F*) file->Get(histname);

  binl==-1?0:binl;
  binh==-1?hist->GetNbinsX():binh;

  hist->Rebin(rebin);
  hist->GetXaxis()->SetRange(binl/rebin, binh/rebin);

  double err;
  double val = hist->IntegralAndError(binh, hist->GetNbinsX()+1, err);
  hist->SetBinContent(binh, val);
  hist->SetBinError(binh, err);

  hist->SetTitle("");
  hist->SetLineWidth(2);
  hist->GetXaxis()->SetTitle(histname);
  hist->GetYaxis()->SetTitle("Events");

  TCanvas* c1 = new TCanvas();
  gStyle->SetOptStat(0);
  c1->SetLogy(logY);
  
  hist->Draw("hist");
  c1->SaveAs("./plots_ele/"+cutname+"/"+histname+".png");

  file->Close();
  
  return -1;
}

int comparehist(TString cutname1, TString cutname2, TString histname, int binl=-1, int binh=-1, int rebin=1, bool logY=false) {

  TString histname1 = cutname1+"_"+histname;
  TString histname2 = cutname2+"_"+histname;
  
  TFile* file = TFile::Open("hists_ele.root","READ");
  TH1F* hist1 = (TH1F*) file->Get(histname1);
  TH1F* hist2 = (TH1F*) file->Get(histname2);

  binl = binl==-1?0:binl;
  binh = binh==-1?hist1->GetNbinsX():binh;

  hist1->Rebin(rebin);
  hist1->GetXaxis()->SetRange(binl/rebin, binh/rebin);
  hist2->Rebin(rebin);
  hist2->GetXaxis()->SetRange(binl/rebin, binh/rebin);

  double err;
  double val = hist1->IntegralAndError(binh/rebin, hist1->GetNbinsX()+1, err);
  hist1->SetBinContent(binh/rebin, val);
  hist1->SetBinError(binh/rebin, err);

  val = hist2->IntegralAndError(binh/rebin, hist2->GetNbinsX()+1, err);
  hist2->SetBinContent(binh/rebin, val);
  hist2->SetBinError(binh/rebin, err);
  
  double min = hist1->GetMinimum()>hist2->GetMinimum()?hist1->GetMinimum():hist2->GetMinimum();
  double max = hist1->GetMaximum()>hist2->GetMaximum()?hist1->GetMaximum():hist2->GetMaximum();
  if(logY) {
    min = min==0?0.1:0.5*min;
    max = max==0?1:2*max;
  }
  else {
    min = 0.9*min;
    max = 1.1*max;
  }
  
  hist1->SetTitle("");
  hist1->SetLineWidth(2);
  hist1->SetLineColor(kBlue);
  hist1->GetXaxis()->SetTitle(histname1);
  hist1->GetYaxis()->SetTitle("Events");
  hist1->SetMinimum(min);
  hist1->SetMaximum(max);

  hist2->SetTitle("");
  hist2->SetLineWidth(2);
  hist2->SetLineColor(kRed);

  TCanvas* c1 = new TCanvas();
  gStyle->SetOptStat(0);
  c1->SetLogy(logY);
  
  hist1->Draw("hist");
  hist2->Draw("hist same");

  TLegend* leg = new TLegend();
  leg->AddEntry(hist1,histname1,"l");
  leg->AddEntry(hist2,histname2,"l");
  leg->Draw();
  
  c1->SaveAs("./plots_ele/"+cutname1+"_"+cutname2+"/"+histname+".png");

  TCanvas* c2 = new TCanvas();
  gStyle->SetOptStat(0);
  c2->SetLogy(logY);
  
  hist1->DrawNormalized("hist");
  hist2->DrawNormalized("hist same");

  TLegend* leg2 = new TLegend();
  leg2->AddEntry(hist1,histname1,"l");
  leg2->AddEntry(hist2,histname2,"l");
  leg2->Draw();
  
  c2->SaveAs("./plots_ele/"+cutname1+"_"+cutname2+"/normalized/"+histname+".png");

  file->Close();
  
  return -1;
}

int stackPlotter(std::vector<TString> cutnames, TString histname, int binl=-1, int binh=-1, int rebin=1, bool logY=false) {


  TFile* file = TFile::Open("hists_ele.root","READ");

  TString histnamewithcut = cutnames[0]+"_"+histname;
  TString filename = cutnames[0];
  TH1F* data = (TH1F*) file->Get(histnamewithcut);

  binl = binl==-1?0:binl;
  binh = binh==-1?data->GetNbinsX()+1:binh;

  data->Rebin(rebin);
  binl = binl/rebin;
  binh = binh/rebin;

  double err;
  double val = data->IntegralAndError(binh, data->GetNbinsX()+1, err);
  data->SetBinContent(binh, val);
  data->SetBinError(binh, err);
  val = data->IntegralAndError(0, binl, err);
  data->SetBinContent(binl, val);
  data->SetBinError(binl, err);

  data->GetXaxis()->SetRange(binl, binh);

  //double maxy = 0;
  //THStack* stack = new THStack("","",data->GetNbinsX()+2,data->GetBinLowEdge(0),data->GetBinCenter(data->GetNbinsX()+1)+0.5*data->GetBinWidth(data->GetNbinsX()+1));

  THStack* stack = new THStack("hs","");
  TH1F* bkgsum = new TH1F();
  std::vector<TH1F*> histvec;
  for(unsigned int ctr=1; ctr<cutnames.size(); ctr++) {
    filename += "_"+cutnames[ctr];
    histnamewithcut = cutnames[ctr]+"_"+histname;
    histvec.push_back(new TH1F());
    histvec[ctr-1] = (TH1F*) file->Get(histnamewithcut);
    histvec[ctr-1]->Rebin(rebin);

    val = histvec[ctr-1]->IntegralAndError(binh, histvec[ctr-1]->GetNbinsX()+1, err);
    histvec[ctr-1]->SetBinContent(binh, val);
    histvec[ctr-1]->SetBinError(binh, err);
    val = histvec[ctr-1]->IntegralAndError(0, binl, err);
    histvec[ctr-1]->SetBinContent(binl, val);
    histvec[ctr-1]->SetBinError(binl, err);
    
    histvec[ctr-1]->GetXaxis()->SetRange(binl, binh);

    histvec[ctr-1]->SetFillColor(ctr+1);
    histvec[ctr-1]->SetLineColor(ctr+1);

    //maxy = histvec[ctr-1]->GetMaximum()>maxy?histvec[ctr-1]->GetMaximum():maxy;
    stack->Add(histvec[ctr-1]);
    if(ctr==1) bkgsum = (TH1F*) histvec[ctr-1]->Clone();
    else bkgsum->Add(histvec[ctr-1]);
  }
  //stack->GetXaxis()->SetRange(binl, binh);

  double maxy = bkgsum->GetMaximum();
  maxy = logY? 10*maxy:1.1*maxy;
  stack->SetMaximum(maxy);

  data->SetLineWidth(3);

  gStyle->SetOptStat(0);
  auto c1 = new TCanvas("","",800,800);
  auto pad1 = new TPad("","",0,0.3,1,1);
  pad1->Draw();
  pad1->cd();
  pad1->SetLogy(logY);
  data->Draw("hist same");
  stack->Draw("hist same");
  data->Draw("hist same");
  //c1->Draw();
  c1->cd();
  auto pad2 = new TPad("","",0,0,1,0.3);
  pad2->Draw();
  pad2->cd();
  TH1F* datasum = (TH1F*) data->Clone();
  datasum->Divide(bkgsum);
  datasum->Draw("ep");
  TLine *line = new TLine(datasum->GetBinLowEdge(binl),1,datasum->GetBinLowEdge(binh+1),1);
  line->SetLineWidth(2);
  line->SetLineStyle(9);
  line->Draw();
  c1->SaveAs("./plots_ele/"+filename+"/"+histname+".png");
  c1->Close();

  file->Close();
  
  return -1;
}

int effPlotter(std::vector<TString> cutnames, TString histname, int nbins=0, double *rebin=0) {

  TFile* file = TFile::Open("hists_ele.root","READ");

  TString histnamewithcut = cutnames[0]+"_"+histname;
  TString filename = "_"+cutnames[0];
  TH1F* data = (TH1F*) file->Get(histnamewithcut);
  TH1F* pass = 0;
  if(nbins==0)
    pass = (TH1F*) data->Clone();
  else
    pass = (TH1F*) data->Rebin(nbins,"",rebin);

  TH1F* bkgsum = new TH1F();
  for(unsigned int ctr=1; ctr<cutnames.size(); ctr++) {
    filename += "_"+cutnames[ctr];
    histnamewithcut = cutnames[ctr]+"_"+histname;
    TH1F* temphist = (TH1F*) file->Get(histnamewithcut);
    TH1F* temphist2 = 0;
    if(nbins==0)
      temphist2 = (TH1F*) temphist->Clone();
    else
      temphist2 = (TH1F*) temphist->Rebin(nbins,"",rebin);

    if(ctr==1) bkgsum = (TH1F*) temphist2->Clone();
    else bkgsum->Add(temphist2);
  }
  pass->SetLineWidth(3);

  TEfficiency* pEff = 0;
  //if(TEfficiency::CheckConsistency((*pass),(*bkgsum))) {
    pEff = new TEfficiency((*pass),(*bkgsum));
    //}
  bkgsum->SetLineColor(kRed);
  gStyle->SetOptStat(0);
  auto c1 = new TCanvas("","",800,800);
  //c1->SetFillStyle(1001);
  //c1->SetFillColor(kWhite);
  TH1D* demo = new TH1D("","",nbins,rebin);
  demo->SetMaximum(1.0);
  demo->SetMinimum(0);
  demo->GetYaxis()->SetTitle("ID eff.");
  demo->GetYaxis()->SetTitleFont(62);
  demo->GetYaxis()->SetTitleOffset(1.3);
  demo->GetXaxis()->SetTitle(varnametotitle[histname]);
  demo->GetXaxis()->SetTitleFont(62);
  //pass->GetYaxis()->SetTitle("#gen #mu/#scouting #mu");
  demo->Draw();
  pEff->SetLineWidth(3);
  pEff->Draw("same");
  //TLine *line = new TLine(data->GetBinLowEdge(binl),1,data->GetBinLowEdge(binh+1),1);
  //line->SetLineWidth(2);
  //line->SetLineColor(kBlack);
  //line->SetLineStyle(9);
  //line->Draw();
  c1->SaveAs("./plots_ele/"+filename+"/eff_"+histname+".png");
  c1->Close();

  auto c2 = new TCanvas("","",800,800);
  pass->Divide(bkgsum);
  pass->Draw("hist");
  c2->SaveAs("./plots_ele/"+filename+"/div_"+histname+".png");
  c2->Close();

  file->Close();
  
  return -1;
}

int elec_plotter() {

  //comparehist("cut1sctecgenHPmch","sctecgenHPmch","elen", 0, 10, 1, true);
  //comparehist("cut1sctecgenHPmch","sctecgenHPmch","elept", 0, 100, 1, true);
  //comparehist("cut1sctecgenHPmch","sctecgenHPmch","eleeta",-1,-1,2,false);
  //comparehist("cut1sctecgenHPmch","sctecgenHPmch","elephi",-1,-1,2,false);
  //comparehist("cut1sctecgenHPmch","sctecgenHPmch","elecharge");
  //comparehist("cut1sctecgenHPmch","sctecgenHPmch","elem",400,600,10,true);
  //comparehist("cut1sctecgenHPmch","sctecgenHPmch","eletkiso",0,50,2,true);
  //comparehist("cut1sctecgenHPmch","sctecgenHPmch","elehoe",0,400,4,true);
  //comparehist("cut1sctecgenHPmch","sctecgenHPmch","elesigmaietaieta",0,800,8,true);
  //comparehist("cut1sctecgenHPmch","sctecgenHPmch","eledphiin",0,100,1,true);
  //comparehist("cut1sctecgenHPmch","sctecgenHPmch","eledetain",0,20,1,true);
  //comparehist("cut1sctecgenHPmch","sctecgenHPmch","elemhits",0,4,1,true);
  //comparehist("cut1sctecgenHPmch","sctecgenHPmch","eleooEMOop",0,40,1,true);

  //comparehist("cut1sctbargenHPmch","sctbargenHPmch","elen", 0, 10, 1, true);
  //comparehist("cut1sctbargenHPmch","sctbargenHPmch","elept", 0, 100, 1, true);
  //comparehist("cut1sctbargenHPmch","sctbargenHPmch","eleeta",-1,-1,2,false);
  //comparehist("cut1sctbargenHPmch","sctbargenHPmch","elephi",-1,-1,2,false);
  //comparehist("cut1sctbargenHPmch","sctbargenHPmch","elecharge");
  //comparehist("cut1sctbargenHPmch","sctbargenHPmch","elem",400,600,10,true);
  //comparehist("cut1sctbargenHPmch","sctbargenHPmch","eletkiso",0,50,2,true);
  //comparehist("cut1sctbargenHPmch","sctbargenHPmch","elehoe",0,400,4,true);
  //comparehist("cut1sctbargenHPmch","sctbargenHPmch","elesigmaietaieta",0,800,8,true);
  //comparehist("cut1sctbargenHPmch","sctbargenHPmch","eledphiin",0,100,1,true);
  //comparehist("cut1sctbargenHPmch","sctbargenHPmch","eledetain",0,20,1,true);
  //comparehist("cut1sctbargenHPmch","sctbargenHPmch","elemhits",0,4,1,true);
  //comparehist("cut1sctbargenHPmch","sctbargenHPmch","eleooEMOop",0,40,1,true);

  //plottersinglehist("sct","gendRmin",1,1400,10,true);
  //plottersinglehist("sct","gendR",-1,-1,10,true);
  //plottersinglehist("sctbar","gendRmin",1,1400,10,true);
  //plottersinglehist("sctbar","gendR",-1,-1,10,true);
  //plottersinglehist("sctec","gendRmin",1,1400,10,true);
  //plottersinglehist("sctec","gendR",-1,-1,10,true);

  //comparehist("cut1genHPsctmch","genHPsctmch","elen",0,6,1,true);
  //comparehist("cut1genHPsctmch","genHPsctmch","elept",0,100,1,true);
  //comparehist("cut1genHPsctmch","genHPsctmch","elepdg");
  //comparehist("cut1genHPsctmch","genHPsctmch","eleeta");
  //comparehist("cut1genHPsctmch","genHPsctmch","elephi");

  //comparehist("genHPsctmch","sctgenHPmch","elept",0,100,1,true);
  //comparehist("genHPsctmch","sctgenHPmch","eleeta");
  //comparehist("genHPsctmch","sctgenHPmch","elephi");

  //comparehist("sct","sctgenHPmch","elept",0,100,1,true);
  //comparehist("sct","sctgenHPmch","eleeta");
  //comparehist("sct","sctgenHPmch","elephi");

  std::vector<TString> cuts;
  cuts.push_back("genHPsctmch");
  cuts.push_back("genHP");
  double bins[] = {0,1,2,3,4,5,6,7,8,9,10,12,14,16,18,20,24,28,32,36,40,50,60,80,100};
  effPlotter(cuts,"elept",24,bins);
  double binseta[] = {-2.45,-2.4,-2.2,-2.0,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.45};
  effPlotter(cuts,"eleeta",26,binseta);
  double binsphi[] = {-3.3,-3.2,-3.0,-2.5,-2.0,-1.5,-1.0,-0.5,0,0.5,1.0,1.5,2.0,2.5,3.0,3.2,3.3};
  effPlotter(cuts,"elephi",16,binsphi);
  double binslog10dxy[] = {-3,-2.9,-2.8,-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.6,-0.5,-0.4,-0.3,-0.2,-0.1,0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.75,2};
  effPlotter(cuts,"elelog10d0",36,binslog10dxy);
  //effPlotter(cuts,"elelog10d0");
  //effPlotter(cuts,"chi2_ndf");
  //effPlotter(cuts,"trklaywmsr");

  //std::vector<TString> cuts;
  //cuts.push_back("sctbar");
  //cuts.push_back("sctbargenHPmch");
  //cuts.push_back("sctbargenothmch");
  //stackPlotter(cuts,"elept",0,100,1,true);
  //stackPlotter(cuts,"elehoe",0,400,4,true);
  //stackPlotter(cuts,"elesigmaietaieta",0,800,8,true);
  //stackPlotter(cuts,"eledphiin",0,100,1,true);
  //stackPlotter(cuts,"elelog10d0",-1,-1,10,false);
  //stackPlotter(cuts,"eleooEMOop",0,40,1,true);
  //stackPlotter(cuts,"ecaliso",50,-1,5,true);
  //stackPlotter(cuts,"hcaliso",150,-1,10,true);
  //stackPlotter(cuts,"trkiso",-1,-1,20,true);

  //std::vector<TString> cuts;
  //cuts.push_back("genHPmch");
  //cuts.push_back("sct");
  //effPlotter(cuts,"mun",0,6,1);
  //effPlotter(cuts,"ecaliso",50,-1,5);

  return -1;
}
