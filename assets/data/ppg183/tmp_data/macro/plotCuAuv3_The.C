//ppg132
TH1D* h_v3_the[2][2];
TGraphErrors* gr_cuau200_v3[    10];
TGraphErrors* gr_cuau200_v3_sys[10];

char name[100];
int wsys=12;

void plotCuAuv3_The()
{
  SetPanelStyle();
  
  float r,g,b;
  //Green
  TColor* color = gROOT->GetColor(kGreen+2);
  color->GetRGB(r,g,b);
  color =  gROOT->GetColor(3);
  color ->SetRGB(r,g,b);

  //Yellow
  color =  gROOT->GetColor(kYellow+1);
  color->GetRGB(r,g,b);
  color =  gROOT->GetColor(5);
  color ->SetRGB(r,g,b);
  
  read_fileCuAu();
  read_the_v3CuAu();
  
  v3_CuAu();
}



int v3_CuAu()
{
  TText* cent[10];
  for(int ic=0;ic<7;ic++)
    {
      if(ic<2) sprintf(name,"%d-%d%%",(ic)*5,(ic+1)*5);
      else     sprintf(name,"%d-%d%%",(ic-1)*10,(ic)*10);
      cent[ic] = new TText(3.,0.01,name);
      cent[ic] -> SetTextSize(26.0);
    }

  TH1D* hist = new TH1D("hist","",1,-0.2,5.3);
  hist->SetMaximum(0.17);
  hist->SetMinimum(-0.01);
  hist->SetXTitle("p_{T} (GeV/c)");
  hist->SetYTitle("v_{3}");
  hist->SetLabelSize(24.0,"XY");
  hist->SetTitleSize(24.0,"XY");
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetNdivisions(606);
  hist->GetYaxis()->SetNdivisions(606);
  hist->SetBinContent(1,-1);
  hist->GetYaxis()->SetTitleOffset(1.3);
  hist->GetXaxis()->SetTitleOffset(1.3);


  TCanvas* cc = new TCanvas("cc","",800,400);
  cc->SetFillColor(10);
  cc->Divide(2,1,0.00,0.00);
  
  //0-5%
  cc->cd(1);
  gPad->SetBottomMargin(0.18);
  hist->Draw();
  cent[0]->Draw();
  gr_cuau200_v3_sys[0]->Draw("pz");
  gr_cuau200_v3[    0]->Draw("pz");
  h_v3_the[0][0]->Draw("lsame");
  h_v3_the[0][1]->Draw("lsame");
  TLatex* tex;
  tex=new TLatex(4.5,0.15,"(a)");
  tex->SetTextSize(20);
  tex->Draw();
  
  //20-30%
  cc->cd(2);
  gPad->SetBottomMargin(0.18);
  hist->Draw();
  cent[3]->Draw();  
  gr_cuau200_v3_sys[3]->Draw("pz");
  gr_cuau200_v3[    3]->Draw("pz");
  h_v3_the[1][0]->Draw("lsame");
  h_v3_the[1][1]->Draw("lsame");
  
  tex=new TLatex(4.5,0.15,"(b)");
  tex->SetTextSize(20);
  tex->Draw();


 TLegend* legend;
 legend= new TLegend(0.25,0.7,0.6,0.9);
 legend->AddEntry(gr_cuau200_v3[0], "PHENIX Cu+Au 200 GeV" ,"p");
 legend->AddEntry(h_v3_the[0][0]  , "Bozek(#eta/s=0.08)","l");
 legend->AddEntry(h_v3_the[0][1]  , "Bozek(#eta/s=0.16)","l");
 //legend->AddEntry(h_v3_the[0][0]  , "#eta/s=0.08 PLB 717 287 290","l");
 //legend->AddEntry(h_v3_the[0][1]  , "#eta/s=0.16 PLB 717 287 290","l");
 legend->SetFillColor(0);
 legend->SetBorderSize(0);
 legend->SetTextSize(20.0);
 cc->cd(1);
 legend->Draw();

 cc->Print("../figures/v3_data_the.pdf");
  
  return 0; 
}

int  read_the_v3CuAu()
{

  sprintf(name,"Eve_by_Evev3.root");
  TFile* f_v3 = new TFile(name);
  // 20-30  eta/s=0.08   v3{2}
  sprintf(name,"C0_5_eta_s_008");
  h_v3_the[0][0]=(TH1D*)f_v3->Get(name);  

  sprintf(name,"C0_5_eta_s_016");
  h_v3_the[0][1]=(TH1D*)f_v3->Get(name);  

  sprintf(name,"C20_30_eta_s_008");
  h_v3_the[1][0]=(TH1D*)f_v3->Get(name);  
  
  sprintf(name,"C20_30_eta_s_016");
  h_v3_the[1][1]=(TH1D*)f_v3->Get(name);  
  //008
  h_v3_the[0][0]->SetLineWidth(4);
  h_v3_the[1][0]->SetLineWidth(4);
  		
  //016		
  h_v3_the[0][1]->SetLineWidth(4);
  h_v3_the[1][1]->SetLineWidth(4);
  h_v3_the[0][1]->SetLineStyle(7);
  h_v3_the[1][1]->SetLineStyle(7);



  return 0;
}

int read_fileCuAu()
{
  for(int icent=0;icent<7;icent++)
    {      
      gr_cuau200_v3[    icent] = new TGraphErrors();
      gr_cuau200_v3_sys[icent] = new TGraphErrors();
      ifstream ifs;
      if(icent<2) sprintf(name,"../data/v3bbc_hadr_%d_%d.dat",(icent)*5,(icent+1)*5   );
      else        sprintf(name,"../data/v3bbc_hadr_%d_%d.dat",(icent-1)*10,(icent)*10   );
      cout << name << endl;
      ifs.open(name);
      
      float pt_bin  ;
      float v3      ;
      float v3_e    ;
      float v3_sys  ;
      for(int ipt=0;ipt<15;ipt++)
	{
	  float tmp;
	  
	  ifs >> pt_bin >>v3 >> v3_e >>v3_sys;
	  gr_cuau200_v3[icent]->SetPoint(     ipt, pt_bin, v3  );
	  gr_cuau200_v3[icent]->SetPointError(ipt,      0, v3_e);
	  
	  gr_cuau200_v3_sys[icent]->SetPoint(     ipt, pt_bin, v3    );
	  gr_cuau200_v3_sys[icent]->SetPointError(ipt,      0, v3_sys);
	}//ipt
      ifs.close();

      gr_cuau200_v3[icent]->SetMarkerStyle(20);
      gr_cuau200_v3[icent]->SetMarkerSize(1.5);
      gr_cuau200_v3[icent]->SetMarkerColor(2);
      gr_cuau200_v3[icent]->SetLineColor(2);

      gr_cuau200_v3_sys[icent]->SetLineColor(kRed-10);
      gr_cuau200_v3_sys[icent]->SetLineWidth(wsys);
      
    }//icent

    
  return 0;
}



void SetPanelStyle()
{
  gStyle->Reset();
  gROOT->SetStyle("MyStyle");
  gROOT->SetStyle("Plain");
  gStyle->SetTextFont(43);
  gStyle->SetLabelFont(43,"x");
  gStyle->SetLabelFont(43,"y");
  gStyle->SetLabelFont(43,"z");
  gStyle->SetTitleFont(43,"x");
  gStyle->SetTitleFont(43,"y");
  gStyle->SetTitleFont(43,"z");
  gStyle->SetEndErrorSize(0);
  

  // Set style which will affect all plots.
//  gStyle->Reset();
//  
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
//  
//  //gStyle->SetOptDate(1);
//  // gStyle->SetPalette(8,0);  // (1,0)
  gStyle->SetPalette(1);  // (1,0)
//  gStyle->SetDrawBorder(0);
//  // gStyle->SetFillColor(0);  // kills palete ???
//  gStyle->SetCanvasColor(0);
//  gStyle->SetPadColor(0);
//  // gStyle->SetFillColor(0); // otherwize it affects Fill colors later
//  gStyle->SetFrameFillColor(0);
  gStyle->SetCanvasBorderMode(0);
  //  gStyle->SetFrameLineWidth(2);
  // gStyle->SetFrameFillStyle(4000);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.2);
  //gStyle->SetHistLineWidth(2);
  //gStyle->SetFuncWidth(2);
//  gStyle->SetLabelSize(0.05,"xyz");
//  gStyle->SetLabelOffset(0.01,"y");
//  gStyle->SetLabelColor(kBlack,"xyz");
//  gStyle->SetTitleSize(0.06,"xyz");
//  gStyle->SetTitleOffset(1.3,"y");
//  gStyle->SetTitleFillColor(0);
//  gStyle->SetLineWidth(2);  
//  gStyle->SetHistLineColor(1);
//  gStyle->SetTextColor(1);
//  gStyle->SetTitleTextColor(1);
  //TGaxis::SetMaxDigits(4);
  //gROOT->ForceStyle();
  
  //gROOT->SetStyle("MyStyle");
//  
//  gStyle->SetLabelFont(62,"x");
//  gStyle->SetLabelFont(62,"y");
//  gStyle->SetLabelFont(62,"z");
//  gStyle->SetTitleFont(62,"x");
//  gStyle->SetTitleFont(62,"y");
//  gStyle->SetTitleFont(62,"z");
//  gStyle->SetEndErrorSize(0);
} // end of void SetPanelStyle()
