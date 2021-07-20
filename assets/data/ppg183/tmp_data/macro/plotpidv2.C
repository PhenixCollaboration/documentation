void plotpidv2()
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
  
  
  for(int i=0; i<25; i++)
    {
      //ept_sys_wid[i]=0.05;
      ept_sys_wid[i]=0.0;
    }

  ifstream fin("v2bbc_pion_0_10.dat");
  float tmp;
  for(int i=0; i<13; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i];
      else ev1_sys[i]=0.05*v1[i];
    }
  fin.close();
  
  TGraphErrors *v2bbc        [6];
  TGraphErrors *v2bbc_sys    [6];
  TGraphErrors *v2bbckaon    [6];
  TGraphErrors *v2bbckaon_sys[6];
  TGraphErrors *v2bbcprot    [6];
  TGraphErrors *v2bbcprot_sys[6];
  
  v2bbc    [0] = new TGraphErrors(13, pt, v1, ept_wid, ev1_num);
  v2bbc_sys[0] = new TGraphErrors(13, pt, v1, ept_sys_wid, ev1_sys);
  
  ifstream fin("v2bbc_pion_10_20.dat");
  float tmp;
  for(int i=0; i<13; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.05*v1[i];
    }
  fin.close();

  v2bbc[1]     = new TGraphErrors(13, pt, v1, ept_wid, ev1_num);
  v2bbc_sys[1] = new TGraphErrors(13, pt, v1, ept_sys_wid, ev1_sys);
  
  ifstream fin("v2bbc_pion_20_30.dat");
  float tmp;
  for(int i=0; i<13; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.05*v1[i];
    }
  fin.close();
  
  v2bbc[2]     = new TGraphErrors(13, pt, v1, ept_wid, ev1_num);
  v2bbc_sys[2] = new TGraphErrors(13, pt, v1, ept_sys_wid, ev1_sys);
  
  ifstream fin("v2bbc_pion_30_40.dat");
  float tmp;
  for(int i=0; i<13; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.05*v1[i];
    }
  fin.close();
  
  v2bbc[3]     = new TGraphErrors(13, pt, v1, ept_wid, ev1_num);
  v2bbc_sys[3] = new TGraphErrors(13, pt, v1, ept_sys_wid, ev1_sys);
  
  ifstream fin("v2bbc_pion_40_50.dat");
  float tmp;
  for(int i=0; i<13; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.05*v1[i];
    }
  fin.close();
  
  v2bbc[4]     = new TGraphErrors(13, pt, v1, ept_wid, ev1_num);
  v2bbc_sys[4] = new TGraphErrors(13, pt, v1, ept_sys_wid, ev1_sys);

  ifstream fin("v2bbc_pion_50_60.dat");
  float tmp;
  for(int i=0; i<13; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.05*v1[i];
    }
  fin.close();
  
  //TGraphErrors *v2bbc5 = new TGraphErrors(13, pt, v1, ept_wid, ev1_num);
  //TGraphErrors *v2bbc5_sys = new TGraphErrors(13, pt, v1, ept_sys_wid, ev1_sys);
  v2bbc[5]     = new TGraphErrors(    12, pt, v1, ept_wid, ev1_num);
  v2bbc_sys[5] = new TGraphErrors(12, pt, v1, ept_sys_wid, ev1_sys);


  //kaon
  ifstream fin("v2bbc_kaon_0_10.dat");
  float tmp;
  for(int i=0; i<11; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.10*v1[i];
    }
  fin.close();
  
  v2bbckaon[0]     = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  v2bbckaon_sys[0] = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);
  
  ifstream fin("v2bbc_kaon_10_20.dat");
  float tmp;
  for(int i=0; i<11; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.10*v1[i];
    }
  fin.close();

  v2bbckaon[1]     = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  v2bbckaon_sys[1] = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);
  
  ifstream fin("v2bbc_kaon_20_30.dat");
  float tmp;
  for(int i=0; i<11; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.10*v1[i];
    }
  fin.close();
  
  v2bbckaon[2]     = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  v2bbckaon_sys[2] = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);
  
  ifstream fin("v2bbc_kaon_30_40.dat");
  float tmp;
  for(int i=0; i<11; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.10*v1[i];
    }
  fin.close();
  
  v2bbckaon[3]     = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  v2bbckaon_sys[3] = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);
  
  ifstream fin("v2bbc_kaon_40_50.dat");
  float tmp;
  for(int i=0; i<11; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.10*v1[i];
    }
  fin.close();
  
  v2bbckaon[4]     = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  v2bbckaon_sys[4] = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);

  ifstream fin("v2bbc_kaon_50_60.dat");
  float tmp;
  for(int i=0; i<11; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.10*v1[i];
    }
  fin.close();
  
  v2bbckaon[5]     = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  v2bbckaon_sys[5] = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);


  //proton
  ifstream fin("v2bbc_prot_0_10.dat");
  float tmp;
  for(int i=0; i<11; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.05*v1[i];
    }
  fin.close();
  
  v2bbcprot[0]     = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  v2bbcprot_sys[0] = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);
  
  ifstream fin("v2bbc_prot_10_20.dat");
  float tmp;
  for(int i=0; i<11; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.05*v1[i];
    }
  fin.close();

  v2bbcprot[1]     = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  v2bbcprot_sys[1] = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);
  
  ifstream fin("v2bbc_prot_20_30.dat");
  float tmp;
  for(int i=0; i<11; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.05*v1[i];
    }
  fin.close();
  
  v2bbcprot[2]     = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  v2bbcprot_sys[2] = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);
  
  ifstream fin("v2bbc_prot_30_40.dat");
  float tmp;
  for(int i=0; i<11; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.05*v1[i];
    }
  fin.close();
  
  v2bbcprot[3]     = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  v2bbcprot_sys[3] = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);
  
  ifstream fin("v2bbc_prot_40_50.dat");
  float tmp;
  for(int i=0; i<11; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.05*v1[i];
    }
  fin.close();
  
  v2bbcprot[4]     = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  v2bbcprot_sys[4] = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);

  ifstream fin("v2bbc_prot_50_60.dat");
  float tmp;
  for(int i=0; i<10; i++)
    {
      ept_wid[i]=0;
      fin>>pt[i]>>v1[i]>>ev1_num[i]>>ev1_sys[i];//>>tmp>>tmp>>tmp>>tmp>>tmp;
      if(pt[i]<2.0) ev1_sys[i]=0.03*v1[i]; else ev1_sys[i]=0.05*v1[i];
    }
  fin.close();
  
  //TGraphErrors *v2bbcprot5 = new TGraphErrors(11, pt, v1, ept_wid, ev1_num);
  //TGraphErrors *v2bbcprot5_sys = new TGraphErrors(11, pt, v1, ept_sys_wid, ev1_sys);
  v2bbcprot[5]     = new TGraphErrors(10, pt, v1, ept_wid, ev1_num);
  v2bbcprot_sys[5] = new TGraphErrors(10, pt, v1, ept_sys_wid, ev1_sys);
  
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

 const int nw=6;
 //this  makes it square  for 8 windows 
 TCanvas *can=new TCanvas("can","can",10,10,1050,600);
 can->Divide(3,2,0,0); //sticks the pads with no space inbetween     
 
 TH1D *h1[nw];
 for (int iw=0;iw<nw;iw++)
   {
    can->cd(iw+1);
    char ch1[8];
    sprintf(ch1,"h1_%d",iw);
    h1[iw] = new TH1D(ch1,"",1,hxmin[iw],hxmax[iw]);
    h1[iw]->SetMinimum(hymin[iw]); h1[iw]->SetMaximum(hymax[iw]);
    h1[iw]->SetXTitle(atit[iw][0]); h1[iw]->SetYTitle(atit[iw][1]);
    h1[iw]->GetXaxis()->CenterTitle(1);
    h1[iw]->GetYaxis()->CenterTitle(1);
    h1[iw]->SetBinContent(1,-1);

    // futz with the axes
    h1[iw]->GetYaxis()->SetNdivisions(606);
    h1[iw]->GetXaxis()->SetNdivisions(606);

    h1[iw]->GetYaxis()->SetTitleSize(textsize);
    h1[iw]->GetYaxis()->SetTitleOffset(3  );
    h1[iw]->GetYaxis()->SetLabelSize(textsize);
    h1[iw]->GetXaxis()->SetTitleSize(textsize);
    h1[iw]->GetXaxis()->SetTitleOffset(2.2);
    h1[iw]->GetXaxis()->SetLabelSize(textsize);
    
    h1[iw]->Draw();
  }
 
 //pion
 for(int ic=0;ic<6;ic++)
   {
     v2bbc_sys[ic]->SetMarkerStyle(20);
     v2bbc_sys[ic]->SetMarkerColor(2);
     v2bbc_sys[ic]->SetMarkerSize(0.1);
     v2bbc_sys[ic]->SetLineColor(kRed-10);
     v2bbc_sys[ic]->SetLineWidth(8);

     v2bbc[ic]    ->SetMarkerStyle(20);  // up triangle
     v2bbc[ic]    ->SetMarkerSize(1);
     v2bbc[ic]    ->SetMarkerColor(2);
     v2bbc[ic]    ->SetLineColor(2);

     //Kon
     v2bbckaon_sys[ic]->SetMarkerStyle(25);
     v2bbckaon_sys[ic]->SetMarkerColor(4);
     v2bbckaon_sys[ic]->SetMarkerSize(0.1);
     v2bbckaon_sys[ic]->SetLineColor(kBlue-10);
     v2bbckaon_sys[ic]->SetLineWidth(10);

     v2bbckaon[ic]    ->SetMarkerStyle(25);  // up triangle 
     v2bbckaon[ic]    ->SetMarkerColor(4);
     v2bbckaon[ic]    ->SetMarkerSize(1.5);
     v2bbckaon[ic]    ->SetFillColor(0);

     //proton
     v2bbcprot_sys[ic]->SetMarkerStyle(28);
     v2bbcprot_sys[ic]->SetMarkerColor(kGreen+2);
     v2bbcprot_sys[ic]->SetMarkerSize(0.1);
     v2bbcprot_sys[ic]->SetLineColor(kGreen-10);
     v2bbcprot_sys[ic]->SetLineWidth(11);
     
     v2bbcprot[ic]->SetMarkerStyle(28);  // up triangle
     v2bbcprot[ic]->SetMarkerSize(1.5);
     v2bbcprot[ic]->SetMarkerColor(kGreen+2);
     v2bbcprot[ic]->SetLineColor(kGreen+2);
     v2bbcprot[ic]->SetFillColor(0); 
   }
  
  for (int iw=0;iw<nw;iw++) // loop over windows
    {
      can->cd(iw+1);
      //
      if (iw==0)
      {
	tex=new TLatex(0.2,0.2,"PHENIX Cu+Au 200 GeV");
	tex->SetTextSize(textsize-2);
	tex->Draw();
	tex=new TLatex(3.4,0.2,"(a)");
	tex->SetTextSize(textsize-2);
	tex->Draw();
      }
      else if (iw==1){    
	tex=new TLatex(3.4,0.2,"(b)");
	tex->SetTextSize(textsize-2);
	tex->Draw();}
      else if (iw==2){    
	tex=new TLatex(3.4,0.2,"(c)");
	tex->SetTextSize(textsize-2);
	tex->Draw();}
      else if (iw==3){    
	tex=new TLatex(3.4,0.2,"(d)");
	tex->SetTextSize(textsize-2);
	tex->Draw();}
      else if (iw==4){    
	tex=new TLatex(3.4,0.2,"(e)");
	tex->SetTextSize(textsize-2);
	tex->Draw();}
      else if (iw==5){    
	tex=new TLatex(3.4,0.2,"(f)");
	tex->SetTextSize(textsize-2);
	tex->Draw();}
      else if (iw==6){    
	tex=new TLatex(3.4,0.2,"(g)");
	tex->SetTextSize(textsize-2);
	tex->Draw();}
      else if (iw==7){    
	tex=new TLatex(3.4,0.2,"(h)");
	tex->SetTextSize(textsize-2);
	tex->Draw();}
      
      if (iw < 8) tex=new TLatex(ptit[iw][0],ptit[iw][1],htit[iw]);
      if ( iw == 0)   tex->SetTextSize(textsize);
      else  tex->SetTextSize(textsize);
      tex->Draw();
      
      if(iw==0)
	{
	  
	  v2bbckaon_sys[0]->Draw("E");  
	  v2bbckaon    [0]->Draw("pE");
	  
	  v2bbcprot_sys[0]->Draw("E");  
	  v2bbcprot    [0]->Draw("PE");

	  v2bbc_sys    [0]->Draw("E");  
	  v2bbc        [0]->Draw("PE");

	  TLegend *leg3 = new TLegend(0.25, 0.45,0.60,0.8);
	  leg3->SetFillColor(10);
	  leg3->SetLineStyle(4000);
	  leg3->SetLineColor(10);
	  leg3->SetLineWidth(0.);
	  leg3->SetTextSize(20);
	  leg3->SetBorderSize(0);
	  leg3->AddEntry(v2bbc[0],"#pi^{+}+#pi^{-}","P");
	  leg3->AddEntry(v2bbckaon[0],"K^{+}+K^{-}","P");
	  leg3->AddEntry(v2bbcprot[0],"p+#bar{p}","P");
	  leg3->Draw();
	}
      else 
	{
	  
	  v2bbckaon_sys[iw]->Draw("E");  
	  v2bbckaon[iw]->Draw("PE");
	  
	  v2bbcprot_sys[iw]->Draw("E");  
	  v2bbcprot[iw]->Draw("PE");

	  v2bbc_sys[iw]->Draw("E");  
	  v2bbc[iw]->Draw("PE");
	}
    } //end loop over windows
  //can->cd();
  //  can->Print("../figures/v2_ptPID_6cent.pdf");
  //can->Print("../figures/v2_ptPID_6cent_tmp.pdf");
  
  //Get Systematics .txt
  double *x_pi[6], *y_pi[6], *sta_pi[6], *sys_pi[6];
  double *x_ka[6], *y_ka[6], *sta_ka[6], *sys_ka[6];
  double *x_pr[6], *y_pr[6], *sta_pr[6], *sys_pr[6];

  ofstream ofs;
  ofs.open("Fig7.txt");
  for(int ic=0;ic<6;ic++)
    {
      sys_pi[ic] = v2bbc_sys[ic]->GetEY();
      x_pi[  ic] = v2bbc    [ic]->GetX();
      y_pi[  ic] = v2bbc    [ic]->GetY();
      sta_pi[ic] = v2bbc    [ic]->GetEY();
      
      sys_ka[ic] = v2bbckaon_sys[ic]->GetEY();
      x_ka[  ic] = v2bbckaon    [ic]->GetX();
      y_ka[  ic] = v2bbckaon    [ic]->GetY();
      sta_ka[ic] = v2bbckaon    [ic]->GetEY();
      
      sys_pr[ic]   = v2bbcprot_sys[ic]->GetEY();
      x_pr[ic]   = v2bbcprot    [ic]->GetX();
      y_pr[ic] = v2bbcprot    [ic]->GetY();
      sta_pr[ic] = v2bbcprot    [ic]->GetEY();  
      ofs << ic*10 << "-" << (ic+1)*10 << "%" << endl;
      ofs << "pion" << endl;
      int NPT_PI=13;
      if(ic==5) NPT_PI=12;
      for(int ip=0;ip<NPT_PI;ip++)
	ofs << x_pi[ic][ip] << " " << y_pi[ic][ip] << " " << sta_pi[ic][ip] << " " << sys_pi[ic][ip] << endl;
      
      ofs << "kaon" << endl;
      for(int ip=0;ip<11;ip++)
	ofs << x_ka[ic][ip] << " " << y_ka[ic][ip] << " " << sta_ka[ic][ip] << " " << sys_ka[ic][ip] << endl;
      
      ofs << "proton" << endl;
      int NPT_PR=11;
      if(ic==5) NPT_PR=10;
      for(int ip=0;ip<NPT_PR;ip++)
	ofs << x_pr[ic][ip] << " " << y_pr[ic][ip] << " " << sta_pr[ic][ip] << " " << sys_pr[ic][ip] << endl;
    }
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
  gStyle->SetTitleSize(0.06,"xyz");
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
