void plotpidv3()
{
  
  gROOT->Reset();
  gROOT->SetStyle("MyStyle");
  gStyle->SetTextFont(43);
  gStyle->SetLabelFont(43,"x");
  gStyle->SetLabelFont(43,"y");
  gStyle->SetLabelFont(43,"z");
  gStyle->SetTitleFont(43,"x");
  gStyle->SetTitleFont(43,"y");
  gStyle->SetTitleFont(43,"z");
  gStyle->SetEndErrorSize(0);

  float pt[25], ept_wid[25];
  
  float v1[25], ev1_num[25], ev1_sys[25], ept_sys_wid[25];
  
  
  for(int i=0; i<6; i++)
    {
      //      ept_sys_wid[i]=0.05;
      ept_sys_wid[i]=0.0;
    }
  
//  ept_sys_wid[ 6] = 0.075;
//  ept_sys_wid[ 7] = 0.075;  
//  ept_sys_wid[ 8] = 0.075;
//  ept_sys_wid[ 9] = 0.075;
//  ept_sys_wid[10] = 0.100;
//  ept_sys_wid[11] = 0.100;
//  ept_sys_wid[12] = 0.100;
//  ept_sys_wid[13] = 0.125;
//  ept_sys_wid[14] = 0.125;
//  ept_sys_wid[15] = 0.250;
//  ept_sys_wid[16] = 0.250;
//  ept_sys_wid[17] = 0.250;
//  ept_sys_wid[18] = 0.250;
//  ept_sys_wid[19] = 0.250;
//  ept_sys_wid[20] = 0.500;
  
  
  ifstream fin("../v3bbc_pion_0_30.dat");
  float tmp;
  for(int i=0; i<13; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.05*v1[i];
    }
  fin.close();
  
  TGraphErrors *v2bbc0 = new TGraphErrors(13, pt, v1, ept_wid, ev1_num);
  TGraphErrors *v2bbc0_sys = new TGraphErrors(13, pt, v1, ept_sys_wid, ev1_sys);
  

  //kaon
  ifstream fin("../v3bbc_kaon_0_30.dat");
  float tmp;
  for(int i=0; i<11; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.10*v1[i];
    }
  fin.close();
  
  TGraphErrors *v2bbckaon0 = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  TGraphErrors *v2bbckaon0_sys = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);
  
  //proton
  ifstream fin("../v3bbc_prot_0_30.dat");
  float tmp;
  for(int i=0; i<11; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.05*v1[i];
    }
  fin.close();
  
  TGraphErrors *v2bbcprot0 = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  TGraphErrors *v2bbcprot0_sys = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);
  

  float ytop=0.97, ybot=0.07;
  float top_r = 0.042, bot_r = 0.102;
  float ny = 1.0/(1.0-top_r-0.02)+1.0/(1.0-bot_r-0.02);
  float ygap = (ytop - ybot)/ny;
  float ymiddle=ybot + ygap*1.0/(1.0-bot_r-0.02)-0.02;
  
  
  float xleft=0.05, xright=0.98; //xmiddle=1.0/(0.84/0.85+1.0)*(xright-xleft)+xleft;

  float left_r = 0.10, right_r = 0.021;
  float nx = 1.0/(1.0-left_r)+1.0/(1.0-right_r)+1.0;
  float xgap = (xright-xleft)/nx;
  //float xgap = (xright-xleft)/4.0;
  float xgap1 = xleft + 1.0/(1-left_r)*xgap;
  float xgap2 = xleft + 1.0/(1-left_r)*xgap + 1.0*xgap;
  //float xgap3 = xleft + 1.0/(1-left_r)*xgap + 2.0*xgap;

  c1=new TCanvas("c1","c1", 450,350);
  c1->SetFillColor(10);
  c1->SetFillColor(10);
  c1->SetFillColor(10);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->cd();
  TPad *c1_1 = new TPad("c1_1", "c1_1",xleft,ybot,xright,ytop);
  c1_1->SetFillColor(10);
  c1_1->SetFillColor(10);
  c1_1->SetBorderMode(0);
  c1_1->SetBorderSize(2);
  c1_1->SetFrameFillColor(0);
  c1_1->SetFrameBorderMode(0);
  c1_1->SetFrameBorderMode(0);
  c1_1->Draw();
  c1_1->cd();
  gPad->SetLeftMargin(left_r);
  gPad->SetRightMargin(right_r);
  gPad->SetBottomMargin(bot_r);
  gPad->SetTopMargin(top_r);
  gPad->SetTicks(1,1);

  float ymax0 =  0.169;
  float ymin0 =  0.0001;
  
  TH1F *h0 = new TH1F("h0","h0",64,0.00,3.8);
  h0->SetMinimum(ymin0);
  h0->SetMaximum(ymax0);
  
  h0->GetYaxis()->SetNdivisions(505);
  h0->GetXaxis()->SetNdivisions(505);

  h0->GetXaxis()->SetLabelSize(20);
  h0->GetYaxis()->SetLabelSize(20);
  h0->GetXaxis()->SetTitleSize(20);
  h0->GetYaxis()->SetTitleSize(20);
  h0->GetYaxis()->SetLabelOffset(0.01);
  h0->GetXaxis()->SetLabelOffset(0.02);
  h0->Draw();

 //pion
  v2bbc0_sys->SetMarkerStyle(20);
  v2bbc0_sys->SetMarkerColor(2);
  v2bbc0_sys->SetMarkerSize(1);
  //v2bbc0_sys->SetFillColor(kRed-10);
  v2bbc0_sys->SetLineColor(kRed-10);
  v2bbc0_sys->SetLineWidth(12);
  
  v2bbc0->SetMarkerStyle(20);  // up triangle
  v2bbc0->SetMarkerSize(1);
  v2bbc0->SetMarkerColor(2);
  v2bbc0->SetLineColor(2);
  
  //Kon
  v2bbckaon0_sys->SetMarkerStyle(25);
  v2bbckaon0_sys->SetMarkerColor(4);
  v2bbckaon0_sys->SetMarkerSize(0.1);
  v2bbckaon0_sys->SetLineColor(kBlue-10);
  v2bbckaon0_sys->SetLineWidth(16);
  //v2bbckaon0_sys->SetFillColor(kGray);
  
  v2bbckaon0->SetMarkerStyle(25);  // up triangle 
  v2bbckaon0->SetMarkerColor(4);
  v2bbckaon0->SetMarkerSize(1.5);
  v2bbckaon0->SetFillColor(0);
  
  v2bbcprot0_sys->SetMarkerStyle(28);
  v2bbcprot0_sys->SetMarkerColor(kGreen+2);
  v2bbcprot0_sys->SetMarkerSize(0.1);
  v2bbcprot0_sys->SetLineColor(kGreen-10);
  v2bbcprot0_sys->SetLineWidth(12);
  
  v2bbcprot0->SetMarkerStyle(28);  // up triangle
  v2bbcprot0->SetMarkerSize(1.5);
  v2bbcprot0->SetMarkerColor(kGreen+2);
  v2bbcprot0->SetLineColor(kGreen+2);
  v2bbcprot0->SetFillColor(0); 
  
  v2bbc0_sys->Draw("E");  
  v2bbc0->Draw("PE");
  
  v2bbckaon0_sys->Draw("E");  
  v2bbckaon0->Draw("pE");
  
  v2bbcprot0_sys->Draw("E");  
  v2bbcprot0->Draw("PE");
  
  TLegend *leg3 = new TLegend(0.12,0.65,0.60,0.92);
  leg3->SetFillColor(10);
  leg3->SetLineStyle(4000);
  leg3->SetLineColor(10);
  leg3->SetLineWidth(0.);
  leg3->SetTextSize(24);
  leg3->SetBorderSize(0);
  leg3->AddEntry(v2bbc0,"PHENIX Cu+Au 200 GeV","");
  leg3->AddEntry(v2bbc0,"#pi^{+}+#pi^{-}","P");
  leg3->AddEntry(v2bbckaon0,"K^{+}+K^{-}","P");
  leg3->AddEntry(v2bbcprot0,"p+#bar{p}","P");
  //leg3->AddEntry(ampt_0_10,"AMPT","L");
  leg3->Draw();
  
  TLatex *t12=new TLatex(3.3,0.88*(ymax0-ymin0)+ymin0, "(a)");
  t12->SetTextSize(20);
  //t12->Draw();
  
  TLatex *t11=new TLatex(2.4,0.08*(ymax0-ymin0)+ymin0, "0-30%");
  t11->SetTextSize(20);
  t11->Draw();

  
  c1->cd();
  TLatex *tx1=new TLatex(0.5,0.03, "p_{T} (GeV/c)");
  tx1->SetTextSize(20);
  tx1->Draw();

  /*
  TLatex *tx2=new TLatex(0.48,0.03, "p_{T} (GeV/c)");
  tx2->SetTextSize(0.04);
  tx2->Draw();

  TLatex *tx1=new TLatex(0.81,0.03, "p_{T} (GeV/c)");
  tx1->SetTextSize(0.04);
  tx1->Draw();

  
  TLatex *ty4 = new TLatex(0.032,0.29, "v_{2}");
  ty4->SetTextSize(0.05);
  ty4->SetTextAngle(90);
  ty4->Draw();
  */
  TLatex *ty5 = new TLatex(0.035,0.52, "v_{3}");
  ty5->SetTextSize(22.);
  ty5->SetTextAngle(90);
  ty5->Draw();

  //c1->cd();
  //  c1->Print("../figures/v3_ptPID_1cent.pdf");
  //v2bbc0     = new TGraphErrors(13, pt, v1, ept_wid, ev1_num);
  //v2bbc0_sys = new TGraphErrors(13, pt, v1, ept_sys_wid, ev1_sys);
  //v2bbckaon0 = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  //v2bbckaon0_sys = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);
  //v2bbcprot0 = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  //v2bbcprot0_sys = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);


  ofstream ofs;
  ofs.open("Fig8.txt");
  double* sys_pi = v2bbc0_sys->GetEY();
  double* x_pi   = v2bbc0    ->GetX();
  double* y_pi   = v2bbc0    ->GetY();
  double* sta_pi = v2bbc0    ->GetEY();
  
  double* sys_ka = v2bbckaon0_sys->GetEY();
  double* x_ka   = v2bbckaon0    ->GetX();
  double* y_ka   = v2bbckaon0    ->GetY();
  double* sta_ka = v2bbckaon0    ->GetEY();
  
  double* sys_pr  = v2bbcprot0_sys->GetEY();
  double* x_pr  = v2bbcprot0    ->GetX();
  double* y_pr= v2bbcprot0    ->GetY();
  double* sta_pr= v2bbcprot0    ->GetEY();  
  ofs << 10 << "-" << 30 << "%" << endl;
  ofs << "pion" << endl;
  for(int ip=0;ip<13;ip++)
    ofs << x_pi[ip] << " " << y_pi[ip] << " " << sta_pi[ip] << " " << sys_pi[ip] << endl;
  
  ofs << "kaon" << endl;
  for(int ip=0;ip<11;ip++)
    ofs << x_ka[ip] << " " << y_ka[ip] << " " << sta_ka[ip] << " " << sys_ka[ip] << endl;
  
  ofs << "proton" << endl;
  for(int ip=0;ip<11;ip++)
    ofs << x_pr[ip] << " " << y_pr[ip] << " " << sta_pr[ip] << " " << sys_pr[ip] << endl;

  ofs.close();



}


void SetPanelStyle()
{
  // Set style which will affect all plots.
  gStyle->Reset();
  
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  
  //gStyle->SetOptDate(1);
  // gStyle->SetPalette(8,0);  // (1,0)
  gStyle->SetPalette(1);  // (1,0)
  gStyle->SetDrawBorder(0);
  // gStyle->SetFillColor(0);  // kills palete ???
  gStyle->SetCanvasColor(0);
  gStyle->SetPadColor(0);
  // gStyle->SetFillColor(0); // otherwize it affects Fill colors later
  gStyle->SetFrameFillColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameLineWidth(2);
  // gStyle->SetFrameFillStyle(4000);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.2);
  gStyle->SetHistLineWidth(2);
  gStyle->SetFuncWidth(2);
  gStyle->SetLabelSize(0.05,"xyz");
  gStyle->SetLabelOffset(0.01,"y");
  gStyle->SetLabelColor(kBlack,"xyz");
  gStyle->SetTitleSize(0.08,"xyz");
  gStyle->SetTitleOffset(1.3,"y");
  gStyle->SetTitleFillColor(0);
  gStyle->SetLineWidth(2);  
  gStyle->SetHistLineColor(1);
  gStyle->SetTextColor(1);
  gStyle->SetTitleTextColor(1);
  //TGaxis::SetMaxDigits(4);
  //gROOT->ForceStyle();
  
  gStyle->SetLabelFont(62,"x");
  gStyle->SetLabelFont(62,"y");
  gStyle->SetLabelFont(62,"z");
  gStyle->SetTitleFont(62,"x");
  gStyle->SetTitleFont(62,"y");
  gStyle->SetTitleFont(62,"z");
  gStyle->SetEndErrorSize(0);
} // end of void SetPanelStyle()
