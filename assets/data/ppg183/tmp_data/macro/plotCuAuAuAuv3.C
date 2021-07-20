#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <cmath>

#include "TFile.h"
#include "TH1.h"
#include "TGraphErrors.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TText.h"

//ppg132
TGraphErrors *g_vn[3][3][6];
TGraphErrors* gr_cuau200[    10];
TGraphErrors* gr_cuau200_sys[10];
TGraphErrors* gr_cuau200_cent_sys[2];
TGraphErrors* gr_cuau200_cent[    2];
TGraphErrors* gr_cuau200_v2[    10];
TGraphErrors* gr_cuau200_v2_sys[10];

// v3 AuAu scaled by e3, Npart
TGraphErrors* gr_auau200_scaled[      10];
TGraphErrors* gr_auau200_scaled_sys_1[10];
TGraphErrors* gr_auau200_scaled_sys_2[10];
			
// v3 CuAu scaled by e3, Npart	      
TGraphErrors* gr_cuau200_scaled[      10];
TGraphErrors* gr_cuau200_scaled_sys[  10];

float auau_e3[9];
float cuau_e3[9];
float auau_e3_er[9];
float cuau_e3_er[9];
float auau_Npart[9];
float cuau_Npart[9];
float auau_Npart_er[9];
float cuau_Npart_er[9];

char name[100];
int wsys=12;

void plotCuAuAuAuv3()
{
  SetPanelStyle();
  SetColor();
  
  int flag_Scale = 0;//0:e3 & Npart , 1:e3
  init_e3_Npart();

  read_file_AuAu_e3();
  read_file_CuAu_e3();
  
  if(flag_Scale==0)
    {
      read_file_AuAu_Npart();
      read_file_CuAu_Npart();
    }

  read_fileAuAu();
  read_fileCuAu();
  
  //  v2_v3_CuAu();
  //v3_AuAu_CuAu();
  //v3_CuAu();
  Scaled_v3_e3_Npart_AuAu_CuAu(flag_Scale);
  //v3_AuAu_CuAu_Npart();
  ////----------------------------------------

  Make_txt(flag_Scale);

}


void   Make_txt(int flag_Scale)
{
  double *x_auau[6], *y_auau[6], *sta_auau[6], *sys_auau_1[6], *sys_auau_2[6];
  double *x_cuau[6], *y_cuau[6], *sta_cuau[6], *sys_cuau[6]                  ;
  ofstream ofs;
  if(flag_Scale==1) ofs.open("Fig14.txt");
  if(flag_Scale==0) ofs.open("Fig15.txt");
  for(int ic=0;ic<2;ic++)
    {
      //AuAu
      sys_auau_1[ic] = gr_auau200_scaled_sys_1[ic]->GetY();
      sys_auau_2[ic] = gr_auau200_scaled_sys_2[ic]->GetY();
      x_auau[    ic] = gr_auau200_scaled      [ic]->GetX();
      y_auau[    ic] = gr_auau200_scaled      [ic]->GetY();
      sta_auau[  ic] = gr_auau200_scaled      [ic]->GetEY();
      //CuAu
      sys_cuau[ic] = gr_cuau200_scaled_sys[ic]->GetEY();
      x_cuau[  ic] = gr_cuau200_scaled    [ic]->GetX();
      y_cuau[  ic] = gr_cuau200_scaled    [ic]->GetY();
      sta_cuau[ic] = gr_cuau200_scaled    [ic]->GetEY();  
      
      ofs << ic*10 << "-" << (ic+1)*10 << "%" << endl;      
      //AuAu
      ofs << "Au+Au" << endl;
      for(int ip=0;ip<10;ip++)
	ofs << x_auau[ic][ip] << " " << y_auau[ic][ip] << " " << sta_auau[ic][ip] << " " << sys_auau_1[ic][ip]-y_auau[ic][ip] << endl;

      ofs << "Cu+Au" << endl;      
      for(int ip=0;ip<15;ip++)
	ofs << x_cuau[ic][ip] << " " << y_cuau[ic][ip] << " " << sta_cuau[ic][ip] << " " << sys_cuau[ic][ip] << endl;
    }//ic  

  ofs.close();
}


int v2_v3_CuAu()
{
  TText* cent[10];
  for(int ic=0;ic<7;ic++)
    {
      if(ic<2) sprintf(name,"%d-%d%%",(ic)*5,(ic+1)*5);
      else     sprintf(name,"%d-%d%%",(ic-1)*10,(ic)*10);
      cent[ic] = new TText(3.,0.02,name);
      cent[ic] -> SetTextSize(0.08);
    }

  TH1D* hist = new TH1D("hist","",1,0,5);
  hist->SetMaximum(0.27);
  hist->SetMinimum(-0.01);
  hist->SetXTitle("p_{T} [GeV/c]");
  hist->SetYTitle("v_{n}");
  hist->SetLabelSize(0.06,"XY");
  hist->SetTitleSize(0.07,"XY");
  hist->SetBinContent(1,-1);
  TCanvas*c_v2pt_attached = new TCanvas("c_v2pt_attached","v2 vs pT",1800,500);
  c_v2pt_attached->SetFillColor(10);
  c_v2pt_attached->Divide(7,1,0.0000,0.00000);
  for(int ic=0;ic<7;ic++)
    {
      c_v2pt_attached->cd(ic+1);
      gPad->SetBottomMargin(0.18);
      hist->Draw();
      cent[ic]->Draw();
      if(ic<2)
	{
	  gr_cuau200_cent_sys[ic]->Draw("pe");
	  gr_cuau200_cent[    ic]->Draw("pe");
	}
      else if(ic<4)
	{
	  gr_cuau200[       ic-1]->Draw("pe");
	  gr_cuau200_sys[   ic-1]->Draw("pe");
	}
      
      gr_cuau200_v2[    ic]->Draw("pe");
      gr_cuau200_v2_sys[ic]->Draw("pe");
    }
  
  TLegend* legend;
  legend= new TLegend(0.3,0.6,0.5,0.8);  
  legend->AddEntry(gr_cuau200_v2_sys[0]," v{2} CuAu" ,"p");
  legend->AddEntry(gr_cuau200_sys[   0]," v{3} CuAu" ,"p");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.07);
  c_v2pt_attached->cd(1);
  legend->Draw();
  
  return 0; 
}

int  v3_AuAu_CuAu_Npart()
{

  TH1D* hist = new TH1D("hist","",1,-0.2,5.3);
  hist->SetMaximum(0.17);
  hist->SetMinimum(-0.01);
  hist->SetXTitle("p_{T} (GeV/c)");
  hist->SetYTitle("v_{3}");
  hist->SetLabelSize(0.06,"XY");
  hist->SetTitleSize(0.07,"XY");
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->SetBinContent(1,-1);

  TCanvas* cc = new TCanvas("ccc","",600,400);
  cc->SetFillColor(10);
  cc->cd(1);
  gPad->SetBottomMargin(0.18);
  hist->Draw();
  // AuAu 20-30% CuAu 5-10%
  gr_cuau200_cent_sys[1]->Draw("pe");		
  gr_cuau200_cent[    1]->Draw("pe");

  g_vn[1][0][2]->Draw("pe same");
  g_vn[1][1][2]->Draw("l same");
  g_vn[1][2][2]->Draw("l same");
  
  TLegend* legend;
  legend= new TLegend(0.25,0.6,0.4,0.8);  
  legend->AddEntry(gr_cuau200_cent[1],"PHENIX Cu+Au 200 GeV  5-10% N_{part}=165" ,"p");
  legend->AddEntry(g_vn[1][0][2]     ,"PHENIX Au+Au 200 GeV 20-30% N_{part}=167" ,"p");
  legend->AddEntry(g_vn[1][0][2]     ,"PRL 107. 252301" ,"");
  legend->SetFillColor(0); 
  legend->SetBorderSize(0);
  legend->SetTextSize(0.045);
  cc->cd(1);
  legend->Draw();

  cc->Print("../figures/v3_CuAu_AuAu_Npart.pdf");

  return 0;
}

int v3_CuAu()
{
  TText* cent[10];
  for(int ic=0;ic<7;ic++)
    {
      sprintf(name,"%d-%d%%",(ic)*10,(ic+1)*10);
      cent[ic] = new TText(3.,0.02,name);
      cent[ic] -> SetTextSize(0.08);
    }

  TH1D* hist = new TH1D("v3_CuAu_AuAu","",1,-0.2,5.3);
  hist->SetMaximum( 0.17);
  hist->SetMinimum(-0.01);
  hist->SetXTitle("p_{T} (GeV/c)");
  hist->SetYTitle("v_{3}");
  hist->SetLabelSize(0.06,"XY");
  hist->SetTitleSize(0.07,"XY");
  hist->GetYaxis()->SetNdivisions(606);
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->SetBinContent(1,-1);

  TCanvas* cc = new TCanvas("v3_cent","",1400,400);
  cc->SetFillColor(10);
  cc->Divide(3,1,0.,0);
  int Ncent=3;
  for(int icent=0;icent<Ncent;icent++)
    {
      cc->cd(icent+1);
      gPad->SetBottomMargin(0.19);
      hist->Draw();
      cent[icent]->Draw();
     
      gr_cuau200_sys[icent]->Draw("pe");
      gr_cuau200[    icent]->Draw("pe");
    }
  
  TLegend* legend;
  legend= new TLegend(0.3,0.7,0.5,0.88);  
  legend->AddEntry(gr_cuau200_sys[0],"PHENIX Cu+Au 200 GeV" ,"");
  legend->AddEntry(gr_cuau200[    0],"h^{#pm}" ,"p");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.08);
  cc->cd(1);
  legend->Draw();
  
  cc->Print("../figures/v3_pt_3cent.pdf");

  return 0;
}

int v3_AuAu_CuAu()
{
  TText* cent[10];
  for(int ic=0;ic<7;ic++)
    {
      sprintf(name,"%d-%d%%",(ic)*10,(ic+1)*10);
      cent[ic] = new TText(3.,0.01,name);
      cent[ic] -> SetTextSize(20.0);
    }

  TH1D* hist = new TH1D("v3_CuAu_AuAu","",1,-0.2,5.3);
  hist->SetMaximum( 0.148);
  hist->SetMinimum(-0.0);
  hist->SetXTitle("p_{T}(GeV/c)");
  hist->SetYTitle("v_{3}");
  hist->SetLabelSize(20.0,"XY");
  hist->SetTitleSize(20.0,"XY");
  hist->GetYaxis()->SetNdivisions(606);
  hist->GetXaxis()->SetNdivisions(606);
  hist->GetXaxis()->SetTitleOffset(1.5);
  hist->GetYaxis()->SetTitleOffset(2.);
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->SetBinContent(1,-1);
  
  TLatex* tex;
  TCanvas* cc = new TCanvas("v3_Cent","v3_Cent",10,10,950,400);
  cc->SetFillColor(10);
  //cc->Divide(3,1,0.001,0.001);
  cc->Divide(3,1,0.,0);
  int Ncent=3;
  for(int icent=0;icent<Ncent;icent++)
    {
      cc->cd(icent+1);
      gPad->SetBottomMargin(0.19);
      hist->Draw();
      cent[icent]->Draw();
      
      if(icent==0)
      {
	tex=new TLatex(4.6,0.13,"(a)");
	tex->SetTextSize(20);
	tex->Draw();
      }
    else if (icent==1)
      {    
	tex=new TLatex(4.6,0.13,"(b)");
	tex->SetTextSize(20);
	tex->Draw();
      }
    else if (icent==2)
      {    
	tex=new TLatex(4.6,0.125,"(c)");
	tex->SetTextSize(20);
	tex->Draw();
      }

      gr_cuau200_sys[icent]->Draw("e");
      gr_cuau200[    icent]->Draw("pe");

      g_vn[1][0][icent]->Draw("pe same");
      g_vn[1][1][icent]->Draw("l same");
      g_vn[1][2][icent]->Draw("l same");
    }
  
  TLegend* legend;
  legend= new TLegend(0.25,0.8,0.4,0.95);  
  legend->AddEntry(gr_cuau200[0],"Cu+Au 200 GeV" ,"p");
  legend->AddEntry(g_vn[1][0][0],"Au+Au 200 GeV PRL 107. 252301" ,"p");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(17.0);
  cc->cd(1);
  legend->Draw();

  TLatex* tex=new TLatex(.5,0.1,"PHENIX");
  tex->SetTextSize(17);
  tex->Draw();

  cc->Print("../figures/v3_CuAu_AuAu_cent.pdf");

  return 0;
}

int Scaled_v3_e3_Npart_AuAu_CuAu(int flag_Scale)
{
  char y_name[100];
  float YMax,YMin,hPhenix,lmax;  
  if(flag_Scale==0)
    {
      sprintf(y_name,"v_{3}/(#varepsilon_{3}N_{part}^{1/3})");
      YMax = 0.186;
      YMin = -0.0;
      hPhenix=0.12;
      lmax = 0.16;
    }
  if(flag_Scale==1)
    {
      sprintf(y_name,"v_{3}/#varepsilon_{3}");
      YMax =  1.42;
      YMin = -0.0;
      hPhenix = 0.9;
      lmax = 1.2;
    }

  TText* cent[10];
  for(int ic=0;ic<7;ic++)
    {
      sprintf(name,"%d-%d%%",(ic)*10,(ic+1)*10);
      if(flag_Scale==0) cent[ic] = new TText(3.,0.02,name);
      if(flag_Scale==1) cent[ic] = new TText(3.,0.1,name);
      cent[ic] -> SetTextSize(24.0);
    }

  TH1D* hist = new TH1D("hist_scale","",1,-0.2,5.3);
  hist->SetMaximum(YMax);
  hist->SetMinimum(YMin);
  hist->SetXTitle("p_{T}(GeV/c)");
  hist->SetYTitle(y_name);
  hist->SetTitleOffset(1.1,"x");
  hist->SetLabelSize(20.0,"XY");
  hist->SetTitleSize(20.0,"XY");
  hist->GetYaxis()->SetNdivisions(606);
  hist->GetXaxis()->SetNdivisions(606);
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitleOffset(1.5);
  hist->GetYaxis()->SetTitleOffset(1.5);
  hist->SetBinContent(1,-1);  

  TCanvas* cc = new TCanvas("cc","",10,10,1050,500);
  cc->SetFillColor(10);
  //cc->Divide(3,1,0.001,0.001);
  cc->Divide(2,1,0.,0);
  int Ncent=2;
  for(int icent=0;icent<Ncent;icent++)
    {
      cc->cd(icent+1);
      gPad->SetBottomMargin(0.18);
      hist->Draw();
      cent[icent]->Draw();

      if(icent==0)
      {
	tex=new TLatex(4.6,lmax,"(a)");
	tex->SetTextSize(20);
	tex->Draw();
      }
    else if (icent==1)
      {    
	tex=new TLatex(4.6,lmax,"(b)");
	tex->SetTextSize(20);
	tex->Draw();
      }
    else if (icent==2)
      {    
	tex=new TLatex(4.6,lmax,"(c)");
	tex->SetTextSize(20);
	tex->Draw();
      }
      
      gr_cuau200_scaled_sys[icent]->Draw("pe");
      gr_cuau200_scaled[    icent]->Draw("pe");
      
      gr_auau200_scaled[      icent]->Draw("pe same");
      gr_auau200_scaled_sys_1[icent]->Draw("l same");//top
      gr_auau200_scaled_sys_2[icent]->Draw("l same");//bottom
    }
  
  TLegend* legend;
  legend= new TLegend(0.25,0.8,0.6,0.95);  
  legend->AddEntry(gr_cuau200[0],"Cu+Au 200 GeV " ,"p");
  legend->AddEntry(g_vn[1][0][0],"Au+Au 200 GeV PRL 107. 252301" ,"p");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(22.);
  cc->cd(1);
  legend->Draw();
  
  TLatex* tex=new TLatex(.5,hPhenix,"PHENIX");
  tex->SetTextSize(22);
  tex->Draw();

//  if(flag_Scale==0)
//    cc->Print("../figures/Scaledv3_e3_Npart.pdf");
//  if(flag_Scale==1)
//    cc->Print("../figures/Scaledv3_e3.pdf");

  return 0;
  }


int read_fileAuAu()
{  
  for(int nv=0; nv<2; nv++){
    for(int idata=0; idata<3; idata++){
      for(int ic=0; ic<6; ic++){
	g_vn[nv][idata][ic] = new TGraphErrors();
      }//for ic
    }//for idata
  }//for nv
  

  float dummy_value[5];//x,y,ey,sy_up,sy_low
  for(int ihar=0; ihar<2; ihar++){
    ifstream ifs;
    sprintf(name,"../AuAu_v%d.txt",ihar+2);
    ifs.open(name);
    
    for(int ic=0; ic<6; ic++){
      for(int n_bin=0; n_bin<10; n_bin++){
	for(int j=0; j<5; j++){
	  ifs >> dummy_value[j];
	}//for j
	
	//Main
	g_vn[ihar][0][ic]->SetPoint(n_bin,dummy_value[0],dummy_value[1]);
	g_vn[ihar][0][ic]->SetPointError(n_bin,0.,dummy_value[2]);
	//Sys
	g_vn[ihar][1][ic]->SetPoint(n_bin,dummy_value[0], dummy_value[3]);
	g_vn[ihar][2][ic]->SetPoint(n_bin,dummy_value[0], dummy_value[4]);
      }//for n_bin
    }//for ic
    ifs.close();
  }//for ihar
  
  for(int ihar=0; ihar<2; ihar++){
    for(int idata=0; idata<3; idata++){
      for(int ic=0; ic<6; ic++){
	//dummy_int=kcol[ihar];
	//	g_vn[ihar][idata][ic]->SetMarkerStyle(8);
	if(ihar==0) g_vn[ihar][idata][ic]->SetMarkerStyle(20);
	else        g_vn[ihar][idata][ic]->SetMarkerStyle(28);
	g_vn[ihar][idata][ic]->SetMarkerSize(1.5);
	g_vn[ihar][idata][ic]->SetLineWidth(1);
	g_vn[ihar][idata][ic]->SetMarkerColor(4);
	g_vn[ihar][idata][ic]->SetLineColor(4);
      }//for idata       
    }//for ic
  }//for ihar
  
  for(int ic=0;ic<6;ic++)
    {
      //Scaled by e2, Npart^(1/3)
      gr_auau200_scaled[      ic] = (TGraphErrors*)g_vn[1][0][ic]->Clone();
      gr_auau200_scaled_sys_1[ic] = (TGraphErrors*)g_vn[1][1][ic]->Clone();
      gr_auau200_scaled_sys_2[ic] = (TGraphErrors*)g_vn[1][2][ic]->Clone();
      double* y_sys_1 = g_vn[1][1][ic]->GetY();
      double* y_sys_2 = g_vn[1][2][ic]->GetY();
      double* x       = g_vn[1][0][ic]->GetX();
      double* y       = g_vn[1][0][ic]->GetY();
      double* y_sta   = g_vn[1][0][ic]->GetEY();
      for(int ipt=0;ipt<10;ipt++)
	{
	  float y_sys = fabs(y_sys_1[ipt]-y[ipt]);
	  float val   = y[    ipt]/(auau_e3[ic]*pow(auau_Npart[ic],1./3.));
	  float err1  = pow(y_sys     /y[ipt]               ,2);
	  float err2  = pow(auau_e3_er[   ic]/auau_e3[   ic],2);
	  //float err3  = pow(auau_Npart_er[ic]/auau_Npart[ic],2);
	  float err3  = pow(1./3.,2)*pow(auau_Npart_er[ic]/auau_Npart[ic],2);
	  float err   = val*sqrt(err1+err2+err3);
	  
	  cout <<" AuAu " <<  val << " " << err << " " << auau_e3[ic] << " " << auau_Npart[ic] << endl;
	  gr_auau200_scaled[      ic]->SetPoint(     ipt, x[ipt], val    );
	  gr_auau200_scaled[      ic]->SetPointError(ipt, 0     , y_sta[ipt]);
	  gr_auau200_scaled_sys_1[ic]->SetPoint(     ipt, x[ipt], val+err);
	  gr_auau200_scaled_sys_2[ic]->SetPoint(     ipt, x[ipt], val-err);
	}
    }//ic  
  
 return 0;
}


int read_fileCuAu(){

  for(int ic=0;ic<6;ic++)
    {      
      gr_cuau200[    ic] = new TGraphErrors();
      gr_cuau200_sys[ic] = new TGraphErrors();
      ifstream ifs;
      sprintf(name,"../v3bbc_hadr_%d_%d.dat",(ic)*10,(ic+1)*10   );
      cout << name << endl;
      ifs.open(name);
      
      float pt_bin  ;
      float v2      ;
      float v2_e    ;
      float v2_sys  ;
      for(int ipt=0;ipt<15;ipt++)
	{
	  float tmp;
	  
	  ifs >> pt_bin >>v2 >> v2_e >>v2_sys;
	  gr_cuau200[ic]->SetPoint(     ipt, pt_bin, v2  );
	  gr_cuau200[ic]->SetPointError(ipt,      0, v2_e);
	  
	  gr_cuau200_sys[ic]->SetPoint(     ipt, pt_bin, v2    );
	  gr_cuau200_sys[ic]->SetPointError(ipt,      0, v2_sys);
	}//ipt
      ifs.close();

      gr_cuau200[ic]->SetMarkerStyle(20);
      gr_cuau200[ic]->SetMarkerSize(1.5);
      gr_cuau200[ic]->SetMarkerColor(2);
      gr_cuau200[ic]->SetLineColor(2);
      
      gr_cuau200_sys[ic]->SetLineWidth(wsys);
      gr_cuau200_sys[ic]->SetLineColor(kRed-10);
    }//ic

  for(int ic=0;ic<2;ic++)
    {      
      gr_cuau200_cent[    ic] = new TGraphErrors();
      gr_cuau200_cent_sys[ic] = new TGraphErrors();
      ifstream ifs;
      sprintf(name,"../v3bbc_hadr_%d_%d.dat",(ic)*5,(ic+1)*5   );
      cout << name << endl;
      ifs.open(name);
      
      float pt_bin  ;
      float v2      ;
      float v2_e    ;
      float v2_sys  ;
      for(int ipt=0;ipt<15;ipt++)
	{
	  float tmp;
	  
	  ifs >> pt_bin >>v2 >> v2_e >>v2_sys;
	  gr_cuau200_cent[ic]->SetPoint(     ipt, pt_bin, v2  );
	  gr_cuau200_cent[ic]->SetPointError(ipt,      0, v2_e);
	  
	  gr_cuau200_cent_sys[ic]->SetPoint(     ipt, pt_bin, v2    );
	  gr_cuau200_cent_sys[ic]->SetPointError(ipt,      0, v2_sys);
	}//ipt
      ifs.close();

      gr_cuau200_cent[ic]->SetMarkerStyle(20);
      gr_cuau200_cent[ic]->SetMarkerSize(1.5);
      gr_cuau200_cent[ic]->SetMarkerColor(2);
      gr_cuau200_cent[ic]->SetLineColor(2);
      
      gr_cuau200_cent_sys[ic]->SetLineColor(kRed-10);
      gr_cuau200_cent_sys[ic]->SetLineWidth(wsys);
      
      //Scaled by e2, Npart^(1/3)
      gr_cuau200_scaled[    ic] = (TGraphErrors*)gr_cuau200[    ic]->Clone();
      gr_cuau200_scaled_sys[ic] = (TGraphErrors*)gr_cuau200_sys[ic]->Clone();
      double* y_sys = gr_cuau200_sys[ic] ->GetEY();
      double* x     = gr_cuau200_sys[ic] ->GetX();
      double* y     = gr_cuau200[    ic] ->GetY();
      double* y_sta = gr_cuau200[    ic] ->GetEY();
      for(int ipt=0;ipt<15;ipt++)
	{
	  float val = y[    ipt]/(cuau_e3[ic]*pow(cuau_Npart[ic],1./3.));
	  float err1 = pow(y_sys[ipt]/y[ipt]               ,2);
	  float err2 = pow(cuau_e3_er[   ic]/cuau_e3[   ic],2);
	  //float err3 = pow(cuau_Npart_er[ic]/cuau_Npart[ic],2);
	  float err3 = pow(1./3.,2)*pow(cuau_Npart_er[ic]/cuau_Npart[ic],2);
	  float err  = val*sqrt(err1+err2+err3);
	  
	  gr_cuau200_scaled[    ic]->SetPoint(     ipt, x[ipt],val       );
	  gr_cuau200_scaled[    ic]->SetPointError(ipt, 0     ,y_sta[ipt]);
	  gr_cuau200_scaled_sys[ic]->SetPoint(     ipt, x[ipt],val       );
	  gr_cuau200_scaled_sys[ic]->SetPointError(ipt,      0,err       );
	}
    }//ic  
  
  ///////////////////////////////////////////////////////////////////////////////////
  //v2
  for(int ic=0;ic<7;ic++)
    {      
      gr_cuau200_v2[    ic] = new TGraphErrors();
      gr_cuau200_v2_sys[ic] = new TGraphErrors();
      ifstream ifs;
      if(ic<2) sprintf(name,"../v2bbc_hadr_%d_%d.dat",(ic)*5,(ic+1)*5   );
      else     sprintf(name,"../v2bbc_hadr_%d_%d.dat",(ic-1)*10,(ic)*10   );
      cout << name << endl;
      ifs.open(name);
      
      float pt_bin  ;
      float v2      ;
      float v2_e    ;
      float v2_sys  ;
      for(int ipt=0;ipt<15;ipt++)
	{
	  float tmp;
	  
	  ifs >> pt_bin >>v2 >> v2_e >>v2_sys;
	  gr_cuau200_v2[ic]->SetPoint(     ipt, pt_bin, v2  );
	  gr_cuau200_v2[ic]->SetPointError(ipt,      0, v2_e);
	  
	  gr_cuau200_v2_sys[ic]->SetPoint(     ipt, pt_bin, v2    );
	  gr_cuau200_v2_sys[ic]->SetPointError(ipt,      0, v2_sys);
	}//ipt
      ifs.close();

      gr_cuau200_v2_sys[ic]->SetMarkerStyle(20);
      gr_cuau200_v2_sys[ic]->SetMarkerSize(1.5);
      gr_cuau200_v2_sys[ic]->SetMarkerColor(2);
      gr_cuau200_v2_sys[ic]->SetLineColor(kRed-10);
      gr_cuau200_v2_sys[ic]->SetLineWidth(wsys);
      
      gr_cuau200_v2[    ic]->SetLineColor(2);


    }//ic

    
  return 0;
}

  int init_e3_Npart()
  {
    for(int ic=0;ic<9;ic++)
      {
	auau_e3[      ic]=1;
	cuau_e3[      ic]=1;
	auau_e3_er[   ic]=0;
	cuau_e3_er[   ic]=0;
	auau_Npart[   ic]=1;
	cuau_Npart[   ic]=1;
	auau_Npart_er[ic]=0;
	cuau_Npart_er[ic]=0;
  }  
    return 1;
  }


int  read_file_AuAu_e3()
{
  ifstream ifs;
  ifs.open("../AuAu_e3.txt");
  for(int ic=0;ic<9;ic++)
    {
      int C;
      ifs >> C >>  auau_e3[ic] >> auau_e3_er[ic];
      auau_e3_er[ic] = auau_e3_er[ic]/100.*auau_e3[ic];
    }
  ifs.close();

  return 1;
}

int  read_file_CuAu_e3()
{
  ifstream ifs;
  ifs.open("../CuAu_e3.txt");
  for(int ic=0;ic<9;ic++)
    {
      int C;
      ifs >> C >> cuau_e3[ic] >> cuau_e3_er[ic];
    }

  return 1;
}


int  read_file_AuAu_Npart()
{
  ifstream ifs;
  ifs.open("../Npart_AuAu.txt");
  for(int ic=0;ic<8;ic++)
    {
      int C;
      ifs >> C >>  auau_Npart[ic] >> auau_Npart_er[ic];
      auau_Npart_er[ic]=auau_Npart_er[ic]/100.*auau_Npart[ic];
    }
  ifs.close();

  return 1;
}

int  read_file_CuAu_Npart()
{
  ifstream ifs;
  ifs.open("../Npart_CuAu.txt");
  for(int ic=0;ic<8;ic++)
    {
      int C;
      ifs >> C >> cuau_Npart[ic] >> cuau_Npart_er[ic];
    }

  return 1;
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
  gStyle->SetFrameLineWidth(0);

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
  gStyle->SetPadBorderSize(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.2);
  //gStyle->SetHistLineWidth(2);
  //gStyle->SetFuncWidth(2);
  //gStyle->SetLabelSize(0.01,"xyz");
//  gStyle->SetLabelOffset(0.01,"y");
//  gStyle->SetLabelColor(kBlack,"xyz");
//  gStyle->SetTitleSize(0.06,"xyz");
//  gStyle->SetTitleOffset(1.3,"y");
//  gStyle->SetTitleFillColor(0);
//  gStyle->SetLineWidth(0);  
//  gStyle->SetHistLineColor(1);
//  gStyle->SetTextColor(1);
//  gStyle->SetTitleTextColor(1);
  //TGaxis::SetMaxDigits(4);
  //gROOT->ForceStyle();
  
} // end of void SetPanelStyle()

void SetColor()
{
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
}
