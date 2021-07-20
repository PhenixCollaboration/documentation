#include <TLegend.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TGraphErrors.h>
#include <TText.h>
#include <TText.h>
#include <TH1D.h>
#include <TFile.h>
#include <TStyle.h>
#include <TColor.h>

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>


const char input_rootfile_AuAu[256] = {"../v2pt_h_auau200_62_semifinal.root"};
const char input_rootfile_CuCu[256] = {"../v2pt_h_cucu200_62_final02.root"};
static const int ncentral = 6;
void reset();
void SetPanelStyle();
int read_file_AuAu_e2();
int read_file_CuCu_e2();
int read_file_CuAu_e2();

int read_file_AuAu_Npart();
int read_file_CuCu_Npart();
int read_file_CuAu_Npart();

int read_file_AuAu();
int read_file_CuCu();
int read_file_CuAu();

int draw_v2_CuAu_cent();
int draw_v2_CuCu_CuAu_AuAu_cent();
int draw_v2_CuCu_CuAu_AuAu_Npart();
int draw_v2_CuCu_CuAu_AuAu_e2();
int draw_scaled_v2_CuCu_CuAu_AuAu_cent(int Scale_Flag);

TGraphErrors* gr_cucu200[    ncentral];
TGraphErrors* gr_cucu200_sys[ncentral];
TGraphErrors* gr_auau200[    ncentral];
TGraphErrors* gr_auau200_sys[ncentral];
TGraphErrors* gr_cuau200[    ncentral];
TGraphErrors* gr_cuau200_sys[ncentral];

TGraphErrors* gr_cucu200_scaled[    ncentral];
TGraphErrors* gr_cucu200_scaled_sys[ncentral];
TGraphErrors* gr_auau200_scaled[    ncentral];
TGraphErrors* gr_auau200_scaled_sys[ncentral];
TGraphErrors* gr_cuau200_scaled[    ncentral];
TGraphErrors* gr_cuau200_scaled_sys[ncentral];

char name[256];
TText* cent[10];
float auau_e2[9];
float cucu_e2[9];
float cuau_e2[9];
float auau_e2_er[9];
float cucu_e2_er[9];
float cuau_e2_er[9];

float auau_Npart[8];
float cucu_Npart[8];
float cuau_Npart[8];
float auau_Npart_er[8];
float cucu_Npart_er[8];
float cuau_Npart_er[8];

int wsys=12;

void reset()
{

  for(int i=0;i<9;i++)
    {
      auau_e2[i]   =1.;
      cucu_e2[i]   =1.;
      cuau_e2[i]   =1.;
      auau_e2_er[i]=0.;
      cucu_e2_er[i]=0.;
      cuau_e2_er[i]=0.;
    }
  for(int i=0;i<8;i++)
    {
      auau_Npart[i]   =1.; 
      cucu_Npart[i]   =1.;
      cuau_Npart[i]   =1.;
      auau_Npart_er[i]=0.;
      cucu_Npart_er[i]=0.;
      cuau_Npart_er[i]=0.;
    }

}

void plotAuAuCuCuCuAu_v2(){
  SetPanelStyle();
  
  reset();
  
  read_file_AuAu_e2();
  read_file_CuCu_e2();
  read_file_CuAu_e2();
  
  int Scale_Flag=0;//0:W Npart 1:W/O Npart
  if(Scale_Flag==0)  
    {
      read_file_AuAu_Npart();
      read_file_CuCu_Npart();
      read_file_CuAu_Npart();
    }
  read_file_AuAu();
  read_file_CuCu();
  read_file_CuAu();

  cout<<"star drawing"<<endl;
  for(int ic=0;ic<7;ic++)
    {
      sprintf(name,"%d-%d%%",(ic)*10,(ic+1)*10);
      cent[ic] = new TText(3.,0.02,name);
      cent[ic] -> SetTextSize(20.);
    }
  
  ////////draw_v2_CuAu_cent();
  //draw_v2_CuCu_CuAu_AuAu_cent();
  //////////draw_v2_CuCu_CuAu_AuAu_Npart();
  ///////////draw_v2_CuCu_CuAu_AuAu_e2();
  draw_scaled_v2_CuCu_CuAu_AuAu_cent(Scale_Flag);
  ////////////draw_v2_e2_same_maya_ppg();
  
  Make_txt(Scale_Flag);

  return ; 
}

void   Make_txt(int Scale_Flag)
{
  double *x_cucu[6], *y_cucu[6], *sta_cucu[6], *sys_cucu[6];
  double *x_auau[6], *y_auau[6], *sta_auau[6], *sys_auau[6];
  double *x_cuau[6], *y_cuau[6], *sta_cuau[6], *sys_cuau[6];
  
  ofstream ofs;
  if(Scale_Flag==1) ofs.open("Fig11.txt");
  if(Scale_Flag==0) ofs.open("Fig12.txt");
  for(int ic=0;ic<6;ic++)
    {
      //CuCu
      if(ic<5) sys_cucu[ic] = gr_cucu200_scaled_sys[ic]->GetEY();
      if(ic<5) x_cucu[  ic] = gr_cucu200_scaled    [ic]->GetX();
      if(ic<5) y_cucu[  ic] = gr_cucu200_scaled    [ic]->GetY();
      if(ic<5) sta_cucu[ic] = gr_cucu200_scaled    [ic]->GetEY();
      //AuAu
      sys_auau[ic] = gr_auau200_scaled_sys[ic]->GetEY();
      x_auau[  ic] = gr_auau200_scaled    [ic]->GetX();
      y_auau[  ic] = gr_auau200_scaled    [ic]->GetY();
      sta_auau[ic] = gr_auau200_scaled    [ic]->GetEY();
      //CuAu
      sys_cuau[ic] = gr_cuau200_scaled_sys[ic]->GetEY();
      x_cuau[  ic] = gr_cuau200_scaled    [ic]->GetX();
      y_cuau[  ic] = gr_cuau200_scaled    [ic]->GetY();
      sta_cuau[ic] = gr_cuau200_scaled    [ic]->GetEY();  
      
      ofs << ic*10 << "-" << (ic+1)*10 << "%" << endl;      
      //CuCu
      if(ic<5)
	{
	  ofs << "Cu+Cu" << endl;
	  for(int ip=0;ip<9;ip++)
	    ofs << x_cucu[ic][ip] << " " << y_cucu[ic][ip] << " " << sta_cucu[ic][ip] << " " << sys_cucu[ic][ip] << endl;
	}
      
      //AuAu
      ofs << "Au+Au" << endl;
      int Npt;
      if(ic==5) Npt= 6;
      else      Npt=10;
      for(int ip=0;ip<Npt;ip++)
	ofs << x_auau[ic][ip] << " " << y_auau[ic][ip] << " " << sta_auau[ic][ip] << " " << sys_auau[ic][ip] << endl;

      ofs << "Cu+Au" << endl;      
      for(int ip=0;ip<15;ip++)
	ofs << x_cuau[ic][ip] << " " << y_cuau[ic][ip] << " " << sta_cuau[ic][ip] << " " << sys_cuau[ic][ip] << endl;
    }//ic  

  ofs.close();
}

int draw_v2_CuAu_cent()
{
  
  TH1D* hist1 = new TH1D("hist1","",1,-0.2,5.3);
  hist1->SetMaximum(0.299);
  hist1->SetMinimum(-0.01);
  hist1->SetXTitle("p_{T} (GeV/c)");
  hist1->SetYTitle("v_{2}");
  hist1->SetLabelSize(0.06,"XY");
  hist1->SetTitleSize(0.07,"XY");
  hist1->SetBinContent(1,-1);
  hist1->GetXaxis()->CenterTitle();
  hist1->GetYaxis()->CenterTitle();
  
  TCanvas*c_v2pt = new TCanvas("v2pt_ce","v2pt_ce",1600,1000);
  c_v2pt->SetFillColor(10);
  c_v2pt->cd();
  
  TPad *c1[6];
  c1[0]= new TPad("c1_0", "c1_0",0.01,0.52,0.38,0.99);
  c1[0]->Draw();
  c_v2pt->cd();
  c1[1]= new TPad("c1_1", "c1_1",0.38,0.52,0.68,0.99);
  c1[1]->Draw();
  c_v2pt->cd();
  c1[2]= new TPad("c1_2", "c1_2",0.68,0.52,0.99,0.99);
  c1[2]->Draw();
  c_v2pt->cd();
  c1[3]= new TPad("c1_3", "c1_3",0.01,0.01,0.38,0.52);
  c1[3]->Draw();
  c_v2pt->cd();
  c1[4]= new TPad("c1_4", "c1_4",0.38,0.01,0.68,0.52);
  c1[4]->Draw();
  c_v2pt->cd();  
  c1[5]= new TPad("c1_5", "c1_5",0.68,0.01,0.99,0.52);
  c1[5]->Draw();
  for(int icc =0; icc<6; icc ++){
    int ic=icc; 
    c_v2pt->cd();
    c1[icc]->cd();
    c1[icc]->SetFillColor(10);
    c1[icc]->Draw();
    c1[icc]->cd();
    c1[icc]->SetFillColor(10);
    c1[icc]->SetBorderMode(0);
    c1[icc]->SetBorderSize(3);
    //c1[icc]->Range(-10,-1,10,1);
    if(icc==0 || icc==3){
      gPad->SetLeftMargin(0.22);
    }else{
      gPad->SetLeftMargin(1.1e-4);
    }
    if(icc==2 ||icc==5){
      gPad->SetRightMargin(0.05);
    }else{
      gPad->SetRightMargin(1.1e-4);
    }
    if(icc<3){
      gPad->SetBottomMargin(1.1e-4);
    }else{
      gPad->SetBottomMargin(0.18);
    }
    if(icc>=3){
      gPad->SetTopMargin(1.1e-4);
    }else{
      gPad->SetTopMargin(0.1);
    }
    //gPad->SetTicks(1,1);
    c1[icc]->SetFrameFillColor(0);
    //c1[icc]->SetFrameBorderMode(0);
    hist1->Draw();
    cent[icc]->Draw();
    
    gr_cuau200_sys[icc]->Draw("pz");
    gr_cuau200[icc]->Draw("pz");
  }//icc
  
  TText* phe = new TText(0.5,0.2,"PHENIX Cu+Au 200 GeV");
  phe->SetTextSize(0.06);
  
  TLegend* legend;
  legend= new TLegend(0.28,0.3,0.4,0.6);  
  legend->AddEntry(gr_cuau200[0],"h^{#pm}" ,"p");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.08);
  c1[0]->cd();
  phe->Draw();
  legend->Draw();
  
  //c_v2pt->Print("../figures/v2_CuCuCuAuAuAu_cent.pdf");
  c_v2pt->Print("../figures/v2_pt_6cent.pdf");
  return 0; 
}


int draw_v2_CuCu_CuAu_AuAu_cent()
{
  TH1D* hist1 = new TH1D("hist1","",1,-0.2,5.3);
  hist1->SetMaximum(0.249);
  hist1->SetMinimum(-0.01);
  hist1->SetXTitle("p_{T} (GeV/c)");
  hist1->SetYTitle("v_{2}");
  hist1->SetLabelSize(20.,"XY");
  hist1->SetTitleSize(20.,"XY");
  hist1->SetBinContent(1,-1);
  hist1->GetYaxis()->SetNdivisions(606);
  hist1->GetXaxis()->SetNdivisions(606);
  hist1->GetXaxis()->CenterTitle();
  hist1->GetYaxis()->CenterTitle();
  hist1->GetXaxis()->SetTitleOffset(2.5);
  hist1->GetYaxis()->SetTitleOffset(2.5);

  // plot
  double textsize = 18;
  int   mcol[8]={kRed,kBlue,kGreen+1,kBlack,kOrange,kGray};
  int   mcol2[4]={6,2,4,8};
  int   msty[8][2]={{20,20},{21,24},{22,28},{23,29},{24,30},{25,27},{28,28},{30,24}};
  
  float msiz[8]={1.11,1.0,1.5,1.2,1.2,1.2,1.2,1.6};
  float msiz2[4]={1.5,1.5,1.5,1.5};
  //
  // arrays
  //
  const int Mfiles=50;
  int   ndp[Mfiles];
  char *cfn[Mfiles];
  char *cft[Mfiles];
  const int Mpoints=40;
  double xa[Mfiles][Mpoints],xe[Mfiles][Mpoints];
  double ya[Mfiles][Mpoints],ye[Mfiles][Mpoints],syse[Mfiles][Mpoints] ;
  
  double aexl[Mfiles][Mpoints],aexh[Mfiles][Mpoints];
  double aeyl[Mfiles][Mpoints],aeyh[Mfiles][Mpoints];
  
  double ra[Mfiles][Mpoints],re[Mfiles][Mpoints];
  
  const int Mpads=14;
  
  
  char  *htit[Mpads];
  char  *atit[Mpads][3];
  double ptit[Mpads][2];
  double hxmin[Mpads],hxmax[Mpads];
  double hymin[Mpads],hymax[Mpads];
  double lxmin[Mpads],lxmax[Mpads];
  double lymin[Mpads],lymax[Mpads];
 
  //
  // Data input
  //
  char *cjob="v2pt";
  int i=-1;
  
  // histogram parameter
  htit[0]="0-10%";
  htit[1]="10-20%";
  htit[2]="20-30%";
  htit[3]="30-40%";
  htit[4]="40-50%";
  htit[5]="50-60%";
// htit[8]="40-50%";
// htit[9]="50-60%";
// htit[10]="60-70%";
// htit[11]="70-80%";
for (int ip=0;ip<Mpads;ip++)
  {
    //  hxmin[ip]=0.0; hxmax[ip]=11.9;
    hxmin[ip]=-0.1; hxmax[ip]=3.8;
    //    hxmin[ip]=-0.08; hxmax[ip]=3.5;
    hymin[ip]=-0.01; hymax[ip]=0.249;
    // this is the legend
    //    lxmin[ip]=0.08; lxmax[ip]=0.35;
    lxmin[ip]=0.3; lxmax[ip]=0.7;
    lymin[ip]=0.6 ; lymax[ip]=0.9;
    ptit[ip][0]=2.0; ptit[ip][1]=0.01;// position centrality labels 
    atit[ip][0]="p_{T}(GeV/c)"; atit[ip][1]="v_{2}";
  }

/*
 const int nw=6;
 TCanvas *can=new TCanvas("can","can",10,10,1050,600);
 can->Divide(3,2,0,0); //sticks the pads with no space inbetween     
 
 TLatex* tex;
 for (int iw=0;iw<nw;iw++) // loop over windows
   {
     can->cd(iw+1);
     hist1->Draw();
     if (iw==0)
       {
	 tex=new TLatex(4.5,0.22,"(a)");
	 tex->SetTextSize(16);
	 tex->Draw();
       }
     else if (iw==1){    
       tex=new TLatex(4.5,0.22,"(b)");
       tex->SetTextSize(16);
       tex->Draw();}
     else if (iw==2){    
       tex=new TLatex(4.5,0.22,"(c)");
       tex->SetTextSize(16);
       tex->Draw();}
     else if (iw==3){    
       tex=new TLatex(4.5,0.22,"(d)");
       tex->SetTextSize(16);
       tex->Draw();}
     else if (iw==4){    
       tex=new TLatex(4.5,0.22,"(e)");
       tex->SetTextSize(16);
       tex->Draw();}
     else if (iw==5){    
       tex=new TLatex(4.5,0.22,"(f)");
       tex->SetTextSize(16);
       tex->Draw();}
     else if (iw==6){    
       tex=new TLatex(4.5,0.22,"(g)");
       tex->SetTextSize(16);
       tex->Draw();}
     else if (iw==7){    
       tex=new TLatex(4.5,0.22,"(h)");
       tex->SetTextSize(16);
       tex->Draw();}
     
     if (iw < 8) tex=new TLatex(ptit[iw][0],ptit[iw][1],htit[iw]);
     if ( iw == 0)   tex->SetTextSize(textsize);
     else  tex->SetTextSize(textsize);
     tex->Draw();
     if(iw<5) gr_cucu200_sys[iw]->Draw("e");    
     if(iw<5) gr_cucu200[iw]->Draw("pe");
     
     gr_auau200_sys[iw]->Draw("e");    
     gr_auau200[iw]->Draw("pe");
     
     gr_cuau200_sys[iw]->Draw("e");
     gr_cuau200[iw]->Draw("pe");
     
   } //end loop over windows
  */

 TCanvas*c_v2pt = new TCanvas("v2pt","v2pt",10,10,1050,600);
 c_v2pt->SetFillColor(10);
 c_v2pt->cd();
 
 TLatex* tex;
 
 TPad *c1[6];
 c1[0]= new TPad("c1_0", "c1_0",0.01,0.52,0.38,0.99);
 c1[0]->Draw();
 c_v2pt->cd();
 c1[1]= new TPad("c1_1", "c1_1",0.38,0.52,0.68,0.99);
 c1[1]->Draw();
 c_v2pt->cd();
 c1[2]= new TPad("c1_2", "c1_2",0.68,0.52,0.99,0.99);
 c1[2]->Draw();
 c_v2pt->cd();
 c1[3]= new TPad("c1_3", "c1_3",0.01,0.01,0.38,0.52);
 c1[3]->Draw();
 c_v2pt->cd();
 c1[4]= new TPad("c1_4", "c1_4",0.38,0.01,0.68,0.52);
 c1[4]->Draw();
 c_v2pt->cd();  
 c1[5]= new TPad("c1_5", "c1_5",0.68,0.01,0.99,0.52);
 c1[5]->Draw();
 for(int icc =0; icc<6; icc ++){
   int ic=icc; 
   c_v2pt->cd();
   c1[icc]->cd();
   c1[icc]->SetFillColor(10);
   c1[icc]->Draw();
   c1[icc]->cd();
   c1[icc]->SetFillColor(10);
   c1[icc]->SetBorderMode(0);
   c1[icc]->SetBorderSize(3);
   //c1[icc]->Range(-10,-1,10,1);
   if(icc==0 || icc==3){
     gPad->SetLeftMargin(0.22);
   }else{
     gPad->SetLeftMargin(1.1e-4);
   }
   if(icc==2 ||icc==5){
     gPad->SetRightMargin(0.05);
   }else{
     gPad->SetRightMargin(1.1e-4);
   }
   if(icc<3){
     gPad->SetBottomMargin(1.1e-4);
   }else{
     gPad->SetBottomMargin(0.18);
   }
   if(icc>=3){
     gPad->SetTopMargin(1.1e-4);
   }else{
      gPad->SetTopMargin(0.1);
   }
   //gPad->SetTicks(1,1);
   c1[icc]->SetFrameFillColor(0);
   //c1[icc]->SetFrameBorderMode(0);
   hist1->Draw();
   cent[icc]->Draw();
   if(icc==0)
     {
       tex=new TLatex(4.8,0.225,"(a)");
       tex->SetTextSize(18);
       tex->Draw();
     }
   else if (icc==1)
     {    
	tex=new TLatex(4.8,0.225,"(b)");
	tex->SetTextSize(18);
	tex->Draw();
     }
   else if (icc==2)
     {    
       tex=new TLatex(4.8,0.225,"(c)");
       tex->SetTextSize(18);
       tex->Draw();
      }
   else if (icc==3)
     {    
       tex=new TLatex(4.8,0.225,"(d)");
       tex->SetTextSize(18);
       tex->Draw();
     }
   else if (icc==4)
     {    
       tex=new TLatex(4.8,0.225,"(e)");
       tex->SetTextSize(18);
       tex->Draw();
     }
   else if (icc==5)
     {    
       tex=new TLatex(4.8,0.225,"(f)");
       tex->SetTextSize(18);
       tex->Draw();
     }
   
   if(ic<5) gr_cucu200_sys[icc]->Draw("e");    
   if(ic<5) gr_cucu200[icc]->Draw("pe");
   
   gr_auau200_sys[icc]->Draw("e");    
   gr_auau200[icc]->Draw("pe");
   
   gr_cuau200_sys[icc]->Draw("e");
    gr_cuau200[icc]->Draw("pe");
 }//icc
 
 
 TLegend* legend;
 legend= new TLegend(0.24,0.72,0.5,0.8);  
 legend->AddEntry(gr_cuau200[0],"Cu+Au 200 GeV" ,"p");
 legend->SetFillColor(0);
 legend->SetBorderSize(0);
 legend->SetTextSize(18.);
 c1[0]->cd();
 legend->Draw();
 
 TLegend* legend1= new TLegend(0.24,0.55,0.5,0.7);  
 legend1->AddEntry(gr_auau200[0],"Au+Au 200 GeV PRC92, 034913" ,"p");
 legend1->AddEntry(gr_cucu200[0],"Cu+Cu 200 GeV PRC92, 034913" ,"p");
 legend1->SetFillColor(0);
 legend1->SetBorderSize(0);
 legend1->SetTextSize(18.);
 c1[0]->cd();
 legend1->Draw();
 
 TLatex* tex=new TLatex(.5,0.13,"PHENIX");
 tex->SetTextSize(18);
 tex->Draw();
 // c_v2pt->cd();
 //c_v2pt->Print("../figures/v2_CuCuCuAuAuAu_cent.pdf");
 
  return 0; 
}

int  draw_v2_CuCu_CuAu_AuAu_Npart()
{
  TH1D* hist = new TH1D("hist","",1,-0.2,5.3);
  hist->SetMaximum(0.3222);
  hist->SetMinimum(-0.01);
  hist->SetXTitle("p_{T} (GeV/c)");
  hist->SetYTitle("v_{2}");
  hist->SetLabelSize(24.,"XY");
  hist->SetTitleSize(24.,"XY");
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->SetBinContent(1,-1);
  hist->GetYaxis()->SetNdivisions(606);
  hist->GetXaxis()->SetNdivisions(606);
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitleOffset(1.5);
  hist->GetYaxis()->SetTitleOffset(1.5);
  
  TLatex* tex;
  //30   40      114.675        95.0(40-50)      99.7199(0-10)
  //TCanvas*c_v2pt = new TCanvas("c_v2pt_1","c1 v2 vs pT",1600,600);
  TCanvas*c_v2pt = new TCanvas("c_v2pt_1","c1 v2 vs pT",10,10,1050,550);
  c_v2pt->Divide(2,1,0.00,0.00);
  c_v2pt->cd(1);
  c_v2pt->SetFillColor(10);
  gPad->SetBottomMargin(0.18);
  hist->Draw();
  gr_cuau200_sys[4]->Draw("e");
  gr_cuau200[    4]->Draw("pe");
  gr_auau200_sys[3]->Draw("e");
  gr_auau200[    3]->Draw("pe");
  gr_cucu200_sys[0]->Draw("e");
  gr_cucu200[    0]->Draw("pe");

  tex=new TLatex(4.8,0.29,"(a)");
  tex->SetTextSize(20);
  tex->Draw();
  
  //40   50      75.5469        65.68(50-60)     73.1764(10-20)  
  c_v2pt->cd(2);
  c_v2pt->SetFillColor(10);
  gPad->SetBottomMargin(0.18);
  gPad->SetRightMargin(0.005);
  hist->Draw();
  gr_cuau200_sys[5]->Draw("e");
  gr_cuau200[    5]->Draw("pe");
  gr_auau200_sys[4]->Draw("e");
  gr_auau200[    4]->Draw("pe");
  gr_cucu200_sys[1]->Draw("e");
  gr_cucu200[    1]->Draw("pe");

  tex=new TLatex(4.8,0.29,"(b)");
  tex->SetTextSize(20);
  tex->Draw();
  
  TLegend* legend2;
  legend2= new TLegend(0.24,0.77,0.6,0.95);  
  legend2->AddEntry(gr_cuau200[4],"Cu+Au 200 GeV(40-50% #LTN_{part}#GT= 95  )" ,"p");
  legend2->AddEntry(gr_auau200[3],"Au+Au 200 GeV(30-40% #LTN_{part}#GT=114.7)" ,"p");
  legend2->AddEntry(gr_cucu200[0],"Cu+Cu 200 GeV( 0-10% #LTN_{part}#GT= 99.7)" ,"p");
  legend2->SetFillColor(0);
  legend2->SetBorderSize(0);
  legend2->SetTextSize(20.);
  c_v2pt->cd(1);
  legend2->Draw();

  TLatex* ttex=new TLatex(3.,0.0215,"PHENIX");
  ttex->SetTextSize(24);
  ttex->Draw();


  TLegend* legend3;
  legend2= new TLegend(0.24,0.77,0.6,0.95);  
  legend3= new TLegend(0.02,0.77,0.6,0.95);  
  legend3->AddEntry(gr_cuau200[5],"Cu+Au 200 GeV(50-60% #LTN_{part}#GT=65.7)" ,"p");
  legend3->AddEntry(gr_auau200[4],"Au+Au 200 GeV(40-50% #LTN_{part}#GT=75.5)" ,"p");
  legend3->AddEntry(gr_cucu200[1],"Cu+Cu 200 GeV(10-20% #LTN_{part}#GT=73.2)" ,"p");
  legend3->SetFillColor(0);
  legend3->SetBorderSize(0);
  legend3->SetTextSize(20.0);
  c_v2pt->cd(2);
  legend3->Draw();
  
  c_v2pt->Print("../figures/v2_CuCuCuAuAuAu_Npart.pdf");
  
  return 0;
}


int  draw_v2_CuCu_CuAu_AuAu_e2()
{
  
  TH1D* hist = new TH1D("hist","",1,-0.2,5.3);
  hist->SetMaximum(0.299);
  hist->SetMinimum(-0.01);
  hist->SetXTitle("p_{T} (GeV/c)");
  hist->SetYTitle("v_{2}");
  hist->SetLabelSize(24.,"XY");
  hist->SetTitleSize(24.,"XY");
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->SetBinContent(1,-1);
  hist->GetYaxis()->SetNdivisions(606);
  hist->GetXaxis()->SetNdivisions(606);
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetTitleOffset(1.5);
  hist->GetYaxis()->SetTitleOffset(1.5);
  //--------------------------------------------
  //- 10-20 AuAu CuAu, 0-10 CuCu
  //- 30-40 AuAu, CuAu, 20-30 CuCu
  //40  50    0.431338     0.4366	 0.410351(30  40)
  //--------------------------------------------
  TCanvas*c_e2 = new TCanvas("c_e2","e2",10,10,1050,600);
  c_e2->SetFillColor(10);
  //  c_e2->Divide(2,1,0.0001,0.0001);
  c_e2->Divide(2,1,0.000,0.000);
  c_e2->cd(1);
  gPad->SetBottomMargin(0.18);
  hist->Draw();
  gr_cuau200_sys[1]->Draw("e");
  gr_cuau200[    1]->Draw("pe");
  gr_auau200_sys[1]->Draw("e");
  gr_auau200[    1]->Draw("pe");
  //gr_cucu200_sys[0]->Draw("pz");
  //gr_cucu200[    0]->Draw("pz");
  gr_cucu200_sys[1]->Draw("e");
  gr_cucu200[    1]->Draw("pe");

  TLatex* tex;
  tex=new TLatex(4.8,0.27,"(a)");
  tex->SetTextSize(20);
  tex->Draw();

  //10  20    0.202074     0.20	 0.170363( 0  10)
  TLegend* legend3;
  legend3= new TLegend(0.25,0.8,0.55,0.95);  
  legend3->AddEntry(gr_cuau200[1],"Cu+Au 200 GeV(10-20% #varepsilon_{2}=0.2 )" ,"p");
  legend3->AddEntry(gr_auau200[1],"Au+Au 200 GeV(10-20% #varepsilon_{2}=0.2 )" ,"p");
  legend3->AddEntry(gr_cucu200[1],"Cu+Cu 200 GeV(10-20% #varepsilon_{2}=0.24)" ,"p");
  //legend3->AddEntry(gr_cucu200_sys[0]," CuCu( 0-10% #varepsilon_{2}=0.16)" ,"pl");
  legend3->SetFillColor(0);
  legend3->SetBorderSize(0);
  legend3->SetTextSize(20.0);
  c_e2->cd(1);
  legend3->Draw();
  
  //30-40 AuAu, CuAu, 20-30 CuCu
  c_e2->cd(2);
  gPad->SetBottomMargin(0.18);
  hist->Draw();
  gr_cuau200_sys[3]->Draw("e");
  gr_cuau200[    3]->Draw("pe");
  gr_auau200_sys[3]->Draw("e");
  gr_auau200[    3]->Draw("pe");
  //gr_cucu200_sys[2]->Draw("pz");
  //gr_cucu200[    2]->Draw("pz");
  gr_cucu200_sys[3]->Draw("e");
  gr_cucu200[    3]->Draw("pe");
  TLegend* legend4;
  legend4= new TLegend(0.05,0.8,0.4,0.95);  
  legend4->AddEntry(gr_cuau200[3],"Cu+Au 200 GeV(30-40% #varepsilon_{2}=0.36)" ,"p");
  legend4->AddEntry(gr_auau200[3],"Au+Au 200 GeV(30-40% #varepsilon_{2}=0.36)" ,"p");
  //legend4->AddEntry(gr_cucu200_sys[2]," Cu 200GeV PHENIX Cu(20-30% #varepsilon_{2}=0.32)" ,"pl");
  legend4->AddEntry(gr_cucu200[3],"Cu+Cu 200 GeV(30-40% #varepsilon_{2}=0.40)" ,"p");
  legend4->SetFillColor(0);
  legend4->SetBorderSize(0);
  legend4->SetTextSize(20.0);
  c_e2->cd(2);
  legend4->Draw();
  
  tex=new TLatex(4.8,0.27,"(b)");
  tex->SetTextSize(20);
  tex->Draw();

  c_e2->cd(1);
  TLatex* ttex=new TLatex(3.,0.0215,"PHENIX");
  ttex->SetTextSize(26);
  ttex->Draw();
  
  c_e2->Print("../figures/v2_CuCuCuAuAuAu_e2.pdf");
  
  //40  50    0.431338     0.4366	 0.410351(30  40)
//  c_e2->cd(3);
//  gPad->SetBottomMargin(0.18);
//  hist->Draw();
//  gr_cuau200_sys[4]->Draw("pz");
//  gr_cuau200[    4]->Draw("pz");
//  gr_auau200_sys[4]->Draw("pz");
//  gr_auau200[    4]->Draw("pz");
//  //gr_cucu200_sys[3]->Draw("pz");
//  //gr_cucu200[    3]->Draw("pz");
//  gr_cucu200_sys[4]->Draw("pz");
//  gr_cucu200[    4]->Draw("pz");
//
//  TLegend* legend5;
//  legend5= new TLegend(0.46,0.18,0.73,0.38);  
//  legend5->AddEntry(gr_cuau200_sys[4]," CuAu(40-50% #varepsilon_{2}=0.42)" ,"pl");
//  legend5->AddEntry(gr_auau200_sys[4]," AuAu(40-50% #varepsilon_{2}=0.44)" ,"pl");
//  legend5->AddEntry(gr_cucu200_sys[3]," CuCu(30-40% #varepsilon_{2}=0.4)" ,"pl");
//  legend5->SetFillColor(0);
//  legend5->SetBorderSize(0);
//  legend5->SetTextSize(0.05);
//  c_e2->cd(3);
//  legend5->Draw();

  return 1;
}

/*
int  draw_v2_e2_same_maya_ppg()
{
  TH1D* hist = new TH1D("hist","",1,0,3.999);
  hist->SetMaximum(0.39);
  hist->SetMinimum(0.);
  hist->SetXTitle("p_{T} [GeV/c]");
  hist->SetYTitle("v_{2}");
  hist->SetLabelSize(0.06,"XY");
  hist->SetTitleSize(0.07,"XY");

  //20-30 AuAu CuAu, 10-20 CuCu
  TCanvas*c_e2_2 = new TCanvas("c_e2_2","e2_2",900,300);
  c_e2_2->SetFillColor(10);
  c_e2_2->Divide(3,1,0.000,0.000);
  c_e2_2->cd(1);
  gPad->SetBottomMargin(0.18);
  hist->Draw();
  gr_cuau200_sys[2]->Draw("pz");
  gr_cuau200[    2]->Draw("pz");
  gr_auau200_sys[2]->Draw("pz");
  gr_auau200[    2]->Draw("pz");
  //gr_cucu200_sys[0]->Draw("pz");
  //gr_cucu200[    0]->Draw("pz");
  gr_cucu200_sys[1]->Draw("pz");
  gr_cucu200[    1]->Draw("pz");
  //10  20    0.202074     0.20	 0.170363( 0  10)
  TLegend* legend3;
  legend3= new TLegend(0.55,0.18,0.77,0.37);  
  legend3->AddEntry(gr_cuau200_sys[2]," CuAu(20-30% #varepsilon_{2}=0.28 )" ,"pl");
  legend3->AddEntry(gr_auau200_sys[2]," AuAu(20-30% #varepsilon_{2}=0.28 )" ,"pl");
  legend3->AddEntry(gr_cucu200_sys[1]," CuCu(10-20% #varepsilon_{2}=0.24)" ,"pl");
  //legend3->AddEntry(gr_cucu200_sys[0]," CuCu( 0-10% #varepsilon_{2}=0.16)" ,"pl");
  legend3->SetFillColor(0);
  legend3->SetBorderSize(0);
  legend3->SetTextSize(0.05);
  c_e2_2->cd(1);
  legend3->Draw();
  
  //30-40 AuAu, CuAu, 20-30 CuCu
  c_e2_2->cd(2);
  gPad->SetBottomMargin(0.18);
  hist->Draw();
  gr_cuau200_sys[3]->Draw("pz");
  gr_cuau200[    3]->Draw("pz");
  gr_auau200_sys[3]->Draw("pz");
  gr_auau200[    3]->Draw("pz");
  gr_cucu200_sys[2]->Draw("pz");
  gr_cucu200[    2]->Draw("pz");
  //gr_cucu200_sys[3]->Draw("pz");
  //gr_cucu200[    3]->Draw("pz");
  TLegend* legend4;
  legend4= new TLegend(0.46,0.18,0.73,0.38);  
  legend4->AddEntry(gr_cuau200_sys[3]," CuAu(30-40% #varepsilon_{2}=0.36)" ,"pl");
  legend4->AddEntry(gr_auau200_sys[3]," AuAu(30-40% #varepsilon_{2}=0.36)" ,"pl");
  legend4->AddEntry(gr_cucu200_sys[2]," CuCu(20-30% #varepsilon_{2}=0.32)" ,"pl");
  //legend4->AddEntry(gr_cucu200_sys[3]," CuCu(30-40% #varepsilon_{2}=0.40)" ,"pl");
  legend4->SetFillColor(0);
  legend4->SetBorderSize(0);
  legend4->SetTextSize(0.05);
  c_e2_2->cd(2);
  legend4->Draw();

  
  //40  50    0.431338     0.4366	 0.410351(30  40)
  c_e2_2->cd(3);
  gPad->SetBottomMargin(0.18);
  hist->Draw();
  gr_cuau200_sys[5]->Draw("pz");
  
  gr_cuau200[    5]->Draw("pz");
  gr_auau200_sys[5]->Draw("pz");
  gr_auau200[    5]->Draw("pz");
  //gr_cucu200_sys[3]->Draw("pz");
  //gr_cucu200[    3]->Draw("pz");
  gr_cucu200_sys[4]->Draw("pz");
  gr_cucu200[    4]->Draw("pz");

  TLegend* legend5;
  legend5= new TLegend(0.46,0.18,0.73,0.38);  
  legend5->AddEntry(gr_cuau200_sys[5]," CuAu(50-60% #varepsilon_{2}=0.49)" ,"pl");
  legend5->AddEntry(gr_auau200_sys[5]," AuAu(50-60% #varepsilon_{2}=0.52)" ,"pl");
  legend5->AddEntry(gr_cucu200_sys[4]," CuCu(40-50% #varepsilon_{2}=0.48)" ,"pl");
  legend5->SetFillColor(0);
  legend5->SetBorderSize(0);
  legend5->SetTextSize(0.05);
  c_e2_2->cd(3);
  legend5->Draw();


}
*/


int draw_scaled_v2_CuCu_CuAu_AuAu_cent(int Scale_Flag)
{
  //Scale_Flag 0:W Npart , 1:W/O Npart
  if(Scale_Flag==0) 
    {
      ymax=0.15;
      lmax=0.256;
    }
  if(Scale_Flag==1) 
    {
      ymax=0.75;
      lmax=1.16;
    }

  TLatex* tex;
  TH1D* hist1 = new TH1D("hist1","",1,-0.2,5.3);
  if(Scale_Flag==0) hist1->SetMaximum(0.299);
  if(Scale_Flag==1) hist1->SetMaximum(1.311);
  if(Scale_Flag==0) hist1->SetMinimum(-0.01);
  if(Scale_Flag==1) hist1->SetMinimum(-0.1);
  hist1->SetXTitle("p_{T} (GeV/c)");
  if(Scale_Flag==0) hist1->SetYTitle("v_{2}/(#varepsilon_{2}N^{1/3}_{part})");
  if(Scale_Flag==1) hist1->SetYTitle("v_{2}/#varepsilon_{2}");
  hist1->SetLabelSize(20.0,"XY");
  hist1->SetTitleSize(20.0,"XY");
  hist1->GetYaxis()->SetNdivisions(606);
  hist1->GetXaxis()->SetNdivisions(606);
  hist1->GetXaxis()->CenterTitle();
  hist1->GetYaxis()->CenterTitle();
  hist1->SetBinContent(1,-1);
  hist1->GetXaxis()->SetTitleOffset(2.5);
  hist1->GetYaxis()->SetTitleOffset(2.5);

  TCanvas*c_v2pt = new TCanvas("c_v2pt","c_v2pt",10,10,1050,600);
  c_v2pt->SetFillColor(10);
  c_v2pt->cd();
  
  TPad *c1[6];
  c1[0]= new TPad("c1_0", "c1_0",0.01,0.52,0.38,0.99);
  c1[0]->Draw();
  c_v2pt->cd();
  c1[1]= new TPad("c1_1", "c1_1",0.38,0.52,0.68,0.99);
  c1[1]->Draw();
  c_v2pt->cd();
  c1[2]= new TPad("c1_2", "c1_2",0.68,0.52,0.99,0.99);
  c1[2]->Draw();
  c_v2pt->cd();
  c1[3]= new TPad("c1_3", "c1_3",0.01,0.01,0.38,0.52);
  c1[3]->Draw();
  c_v2pt->cd();
  c1[4]= new TPad("c1_4", "c1_4",0.38,0.01,0.68,0.52);
  c1[4]->Draw();
  c_v2pt->cd();  
  c1[5]= new TPad("c1_5", "c1_5",0.68,0.01,0.99,0.52);
  c1[5]->Draw();
  for(int icc =0; icc<6; icc ++){
    int ic=icc; 
    if(icc==5)ic=9; //MB
    c_v2pt->cd();
    c1[icc]->cd();
    c1[icc]->SetFillColor(10);
    c1[icc]->Draw();
    c1[icc]->cd();
    c1[icc]->SetFillColor(10);
    c1[icc]->SetBorderMode(0);
    c1[icc]->SetBorderSize(3);
    //c1[icc]->Range(-10,-1,10,1);
    if(icc==0 || icc==3){
      gPad->SetLeftMargin(0.22);
    }else{
      gPad->SetLeftMargin(1.1e-4);
    }
    if(icc==2 ||icc==5){
      gPad->SetRightMargin(0.05);
    }else{
      gPad->SetRightMargin(1.1e-4);
    }
    if(icc<3){
      gPad->SetBottomMargin(1.1e-4);
    }else{
      gPad->SetBottomMargin(0.18);
    }
    if(icc>=3){
      gPad->SetTopMargin(1.1e-4);
    }else{
      gPad->SetTopMargin(0.1);
    }
    //gPad->SetTicks(1,1);
    c1[icc]->SetFrameFillColor(0);
    //c1[icc]->SetFrameBorderMode(0);
    hist1->Draw();
    cent[icc]->Draw();
    if(icc==0)
      {
	tex=new TLatex(4.7,lmax,"(a)");
	tex->SetTextSize(20);
	tex->Draw();
      }
    else if (icc==1)
      {    
	tex=new TLatex(4.7,lmax,"(b)");
	tex->SetTextSize(20);
	tex->Draw();
      }
    else if (icc==2)
      {    
	tex=new TLatex(4.7,lmax,"(c)");
	tex->SetTextSize(20);
	tex->Draw();
      }
    else if (icc==3)
      {    
	tex=new TLatex(4.7,lmax,"(d)");
	tex->SetTextSize(20);
	tex->Draw();
      }
    else if (icc==4)
      {    
	tex=new TLatex(4.7,lmax,"(e)");
	tex->SetTextSize(20);
	tex->Draw();
      }
    else if (icc==5)
      {    
	tex=new TLatex(4.7,lmax,"(f)");
	tex->SetTextSize(20);
	tex->Draw();
      }
    if(ic<5) gr_cucu200_scaled_sys[icc]->Draw("p");    
    if(ic<5) gr_cucu200_scaled[icc]->Draw("p");

    gr_auau200_scaled_sys[icc]->Draw("p");    
    gr_auau200_scaled[icc]->Draw("p");

    gr_cuau200_scaled_sys[icc]->Draw("p");
    gr_cuau200_scaled[icc]->Draw("p");
  }//icc

  TLegend* legend;
  if(Scale_Flag==0) legend= new TLegend(0.24,0.72, 0.6, 0.8);  
  if(Scale_Flag==1) legend= new TLegend(0.24,0.8,0.58,0.88);  
  legend->AddEntry(gr_cuau200[0],"Cu+Au 200 GeV" ,"p");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(18.);

  TLegend* legend2;
  if(Scale_Flag==0) legend2= new TLegend(0.24,0.55, 0.6, 0.7);  
  if(Scale_Flag==1) legend2= new TLegend(0.24,0.64,0.58,0.79);  
  legend2->AddEntry(gr_auau200[0],"Au+Au 200 GeV PRC92,034913" ,"p");
  legend2->AddEntry(gr_cucu200[0],"Cu+Cu 200 GeV PRC92,034913" ,"p");
  legend2->SetFillColor(0);
  legend2->SetBorderSize(0);
  legend2->SetTextSize(18.);

  c1[0]->cd();
  legend->Draw();
  legend2->Draw();
  
  TLatex* ttex=new TLatex(.5,ymax,"PHENIX");
  ttex->SetTextSize(20);
  ttex->Draw();

  if(Scale_Flag==0)
    c_v2pt->Print("../figures/Scaledv2_e2_Npart.pdf");
    if(Scale_Flag==1)
    c_v2pt->Print("../figures/Scaledv2_e2.pdf");

  
  return 0; 
}



int read_file_AuAu(){
  TDirectory*current_dir = gDirectory;
  TFile* file = TFile::Open(input_rootfile_AuAu);
  gDirectory = current_dir; 
  for(int ic=0; ic<6; ic ++){
    sprintf(name,"gr_auau200_ic%d",ic);
    gr_auau200[    ic] = (TGraphErrors*)file->Get(name)->Clone();
    sprintf(name,"gr_auau200_sys_ic%d",ic);
    gr_auau200_sys[ic] = (TGraphErrors*)file->Get(name)->Clone();
  
    gr_auau200[ic]->SetMarkerStyle(28);
    gr_auau200[ic]->SetMarkerSize(1.5);
    gr_auau200[ic]->SetMarkerColor(kBlue+1);
    gr_auau200[ic]->SetLineColor(kBlue+1);
    
    gr_auau200_sys[ic]->SetLineColor(kBlue-8);
    gr_auau200_sys[ic]->SetLineWidth(wsys);
    gr_auau200_sys[ic]->SetMarkerColor(kBlue+1);
    gr_auau200_sys[ic]->SetMarkerSize(0.1);
    
    gr_auau200_scaled[    ic] = (TGraphErrors*)gr_auau200[    ic]->Clone();
    gr_auau200_scaled_sys[ic] = (TGraphErrors*)gr_auau200_sys[ic]->Clone();

    //Scaled by e2, Npart^(1/3)
    double* y_sys = gr_auau200_sys[ic] ->GetEY();
    double* x     = gr_auau200_sys[ic] ->GetX();
    double* y     = gr_auau200[    ic] ->GetY();
    double* y_sta = gr_auau200[    ic] ->GetEY();
    int Npt;
    if(ic==5) Npt= 6;
    else      Npt=10;
    for(int ipt=0;ipt<Npt;ipt++)
      {
	float val  = y[    ipt]/(auau_e2[ic]*pow(auau_Npart[ic],1./3.));
	//float val  = y[    ipt]/(auau_e2[ic]*pow(auau_Npart[ic],1));
	float err1 = pow(y_sys[ipt]/y[ipt]               ,2);
	float err2 = pow(auau_e2_er[   ic]/auau_e2[   ic],2);
	//float err3 = pow(auau_Npart_er[ic]/auau_Npart[ic],2);
	float err3 = pow((1./3.)*auau_Npart_er[ic]/auau_Npart[ic],2);
	float err  = val*sqrt(err1+err2+err3);
	gr_auau200_scaled[    ic]->SetPoint(     ipt, x[ipt],val       );
	gr_auau200_scaled[    ic]->SetPointError(ipt,      0,y_sta[ipt]);
	gr_auau200_scaled_sys[ic]->SetPoint(     ipt, x[ipt],val       );
	gr_auau200_scaled_sys[ic]->SetPointError(ipt,      0,err       );
      }
  }
  file->Close();
  file->Delete();

//  TFile* fffff = new TFile("v2AuAu.root","recreate");
//  for(int ic=0; ic<6; ic ++)
//    {
//      sprintf(name,"v2AuAu_C%d",ic);
//      gr_auau200[           ic]->SetNameTitle(name,name);
//      sprintf(name,"v2AuAu_C%d_Sys",ic);
//      gr_auau200_sys[       ic]->SetNameTitle(name,name);
//      sprintf(name,"v2AuAu_C%d_SCal",ic);
//      gr_auau200_scaled[    ic]->SetNameTitle(name,name);
//      sprintf(name,"v2AuAu_C%d_SCal_Sys",ic);
//      gr_auau200_scaled_sys[ic]->SetNameTitle(name,name);
//
//      gr_auau200[           ic]->Write();
//      gr_auau200_sys[       ic]->Write();
//      gr_auau200_scaled[    ic]->Write();
//      gr_auau200_scaled_sys[ic]->Write();
//    }
//  fffff->Write();
//  fffff->Close();

  return 0;
}


int read_file_CuCu(){
  TDirectory*current_dir = gDirectory;
  TFile* file = TFile::Open(input_rootfile_CuCu);
  gDirectory = current_dir; 
  for(int ic=0; ic<5; ic ++){
    sprintf(name,"gr_cucu200_ic%d",ic);
    gr_cucu200[ic] = (TGraphErrors *)file->Get(name)->Clone();
    sprintf(name,"gr_cucu200_sys_ic%d",ic);
    gr_cucu200_sys[ic] = (TGraphErrors *)file->Get(name)->Clone();
    
    gr_cucu200[ic]->SetMarkerStyle(26);
    gr_cucu200[ic]->SetMarkerSize(1.5);
    gr_cucu200[ic]->SetMarkerColor(kGreen+3);
    gr_cucu200[ic]->SetLineColor(kGreen+3);

    gr_cucu200_sys[ic]->SetLineColor(kGreen-8);
    gr_cucu200_sys[ic]->SetLineWidth(wsys);
    
    //Scaled by e2, Npart^(1/3)
    gr_cucu200_scaled[    ic] = (TGraphErrors*)gr_cucu200[    ic]->Clone();
    gr_cucu200_scaled_sys[ic] = (TGraphErrors*)gr_cucu200_sys[ic]->Clone();
    double* y_sys = gr_cucu200_sys[ic] ->GetEY();
    double* x     = gr_cucu200_sys[ic] ->GetX();
    double* y     = gr_cucu200[    ic] ->GetY();
    double* y_sta = gr_cucu200[    ic] ->GetEY();
    for(int ipt=0;ipt<9;ipt++)
      {
	float val = y[    ipt]/(cucu_e2[ic]*pow(cucu_Npart[ic],1./3.));
	//float val = y[    ipt]/(cucu_e2[ic]*pow(cucu_Npart[ic],1));
	float err1 = pow(y_sys[ipt]/y[ipt]               ,2);
	float err2 = pow(cucu_e2_er[   ic]/cucu_e2[   ic],2);
	//float err3 = pow(cucu_Npart_er[ic]/cucu_Npart[ic],2);
	float err3 = pow((1./3.)*cucu_Npart_er[ic]/cucu_Npart[ic],2);
	float err  = val*sqrt(err1+err2+err3);
	gr_cucu200_scaled[    ic]->SetPoint(     ipt, x[ipt],val       );
	gr_cucu200_scaled[    ic]->SetPointError(ipt,      0,y_sta[ipt]);
	gr_cucu200_scaled_sys[ic]->SetPoint(     ipt, x[ipt],val       );
	gr_cucu200_scaled_sys[ic]->SetPointError(ipt,      0,err       );
      }

  }
  file->Close();
  file->Delete();
  return 0; 
}

int read_file_CuAu(){

  for(int ic=0;ic<6;ic++)
    {      
      gr_cuau200[    ic] = new TGraphErrors();
      gr_cuau200_sys[ic] = new TGraphErrors();
      ifstream ifs;
      sprintf(name,"../v2bbc_hadr_%d_%d.dat",(ic)*10,(ic+1)*10   );
      cout << name << endl;
      ifs.open(name);
      
      float pt_bin  ;
      float v2      ;
      float v2_e    ;
      float v2_sys  ;
      for(int ipt=0;ipt<15;ipt++)
	{
	  ifs >> pt_bin >>v2 >> v2_e >>v2_sys;
	  cout << ipt << " " << v2_e << endl;
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
      
      gr_cuau200_sys[ic]->SetLineColor(kRed-10);
      gr_cuau200_sys[ic]->SetLineWidth(wsys);
      
      //Scaled by e2, Npart^(1/3)
      gr_cuau200_scaled[    ic] = (TGraphErrors*)gr_cuau200[    ic]->Clone();
      gr_cuau200_scaled_sys[ic] = (TGraphErrors*)gr_cuau200_sys[ic]->Clone();
      double* y_sys = gr_cuau200_sys[ic] ->GetEY();
      double* x     = gr_cuau200_sys[ic] ->GetX();
      double* y     = gr_cuau200[    ic] ->GetY();
      double* y_sta = gr_cuau200[    ic] ->GetEY();
      for(int ipt=0;ipt<15;ipt++)
	{
	  float val = y[    ipt]/(cuau_e2[ic]*pow(cuau_Npart[ic],1./3.));
	  //float val = y[    ipt]/(cuau_e2[ic]*pow(cuau_Npart[ic],1));
	  float err1 = pow(y_sys[ipt]/y[ipt]               ,2);
	  float err2 = pow(cuau_e2_er[   ic]/cuau_e2[   ic],2);
	  //float err3 = pow(cuau_Npart_er[ic]/cuau_Npart[ic],2);
	  float err3 = pow((1./3.)*cuau_Npart_er[ic]/cuau_Npart[ic],2);
	  float err  = val*sqrt(err1+err2+err3);
	  
	  gr_cuau200_scaled[    ic]->SetPoint(     ipt, x[ipt],val       );
	  gr_cuau200_scaled[    ic]->SetPointError(ipt,      0,y_sta[ipt]);

	  gr_cuau200_scaled_sys[ic]->SetPoint(     ipt, x[ipt],val       );
	  gr_cuau200_scaled_sys[ic]->SetPointError(ipt, 0     ,err       );
	}
    }//ic
    
  return 0;
}

int  read_file_AuAu_e2()
{
  ifstream ifs;
  ifs.open("../AuAu_e2.txt");
  for(int ic=0;ic<9;ic++)
    {
      int C;
      ifs >> C >>  auau_e2[ic] >> auau_e2_er[ic];
      auau_e2_er[ic] = auau_e2_er[ic]/100.*auau_e2[ic];
      cout << auau_e2[ic] << " " << auau_e2_er[ic] << endl;
    }
  ifs.close();

  return 1;
}

int  read_file_CuCu_e2()
{
  ifstream ifs;
  ifs.open("../CuCu_e2.txt");
  for(int ic=0;ic<9;ic++)
    {
      int C;
      ifs >> C >> cucu_e2[ic] >> cucu_e2_er[ic];
      cucu_e2_er[ic] = cucu_e2_er[ic]/100.*cucu_e2[ic];
    }

  return 1;
}

int  read_file_CuAu_e2()
{
  ifstream ifs;
  ifs.open("../CuAu_e2.txt");
  for(int ic=0;ic<9;ic++)
    {
      int C;
      ifs >> C >> cuau_e2[ic] >> cuau_e2_er[ic];
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

int  read_file_CuCu_Npart()
{
  ifstream ifs;
  ifs.open("../Npart_CuCu.txt");
  for(int ic=0;ic<8;ic++)
    {
      int C;
      ifs >> C >> cucu_Npart[ic] >> cucu_Npart_er[ic];
      cucu_Npart_er[ic]=cucu_Npart_er[ic]/100.*cucu_Npart[ic];
    }

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
