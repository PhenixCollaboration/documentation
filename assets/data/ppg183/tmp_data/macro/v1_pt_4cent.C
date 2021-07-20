v1_pt_4cent()
{
  gROOT->Reset();
  gROOT->SetStyle("MyStyle");
  //  gROOT->LoadMacro("v2pt_12cen_MyDef.C");
  // gROOT->LoadMacro("MyDef.C");
  gStyle->SetTextFont(43);
  gStyle->SetLabelFont(43,"x");
  gStyle->SetLabelFont(43,"y");
  gStyle->SetLabelFont(43,"z");
  gStyle->SetTitleFont(43,"x");
  gStyle->SetTitleFont(43,"y");
  gStyle->SetTitleFont(43,"z");
  gStyle->SetEndErrorSize(0);

  //get correction factor 
  //Res{SmdS} BbcS -> BbcSN
  float Ratio[11];
  float Ratio_er[11];
  ifstream ifs;
  ifs.open("Run372_373_375_376_Ratio_SMDSResoPsi1_BBCS_BBCSN.dat");
  if(ifs)cout<< " find file"<< endl;
  float C1;
  for(int ic=0;ic<11;ic++){ Ratio[ic]=-1; Ratio_er[ic]=0;}
  for(int ic=0;ic<11;ic++)
    {
      ifs >> C1 >> Ratio[ic] >> Ratio_er[ic];//BbcS
      
      cout  <<"BbcSN:"<< C1 <<" " <<  Ratio[ic] << " " << Ratio_er[ic] << endl;
    }
  ifs.close();



  double textsize = 18;

  //int   mcol[8]={kRed,kMagenta,kBlue,kCyan,kGreen,kYellow,kOrange,kGray};
  int   mcol[8]={kRed,kOrange+1,kBlue,kGreen+1,kCyan,kYellow,kOrange,kGray};
  int   mcol2[4]={6,2,4,8};
  
  //int   msty[8][2]={{20,20},{25,24},{22,22},{28,26},{29,30},{33,27},{34,28},{20,24}};
  int   msty[8][2]={{20,20},{21,24},{22,29},{23,30},{24,30},{25,27},{28,28},{30,24}};
  
  
  //float msiz[8]={1.11,0.9,1.2,1.24,1.5,1,1,1};
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
  char *cjob="v1pt";
  int i=-1;

  // hadrons
  cfn[++i]="v1smd_hadr_10_20.dat" ;cft[i]="";
  cfn[++i]="v1smd_hadr_20_30.dat" ;cft[i]=""; 
  cfn[++i]="v1smd_hadr_30_40.dat" ;cft[i]="h^{#pm}"; 
  cfn[++i]="v1smd_hadr_40_50.dat" ;cft[i]=""; 

  // histogram parameter
  htit[0]="10-20%";
  htit[1]="20-30%";
  htit[2]="30-40%";
  htit[3]="40-50%";
  // htit[4]="20-25%";
  // htit[5]="25-30%";
  // htit[6]="30-35%";
  // htit[7]="35-40%";
  // htit[8]="40-50%";
  // htit[9]="50-60%";
  // htit[10]="60-70%";
  // htit[11]="70-80%";
  for (int ip=0;ip<Mpads;ip++)
  {
    //  hxmin[ip]=0.0; hxmax[ip]=11.9;
    hxmin[ip]=-0.1; hxmax[ip]=5.9;
    //  hymin[ip]=0.000; hymax[ip]=0.128;
    hymin[ip]=-0.056; hymax[ip]=0.023;
    //lxmin[ip]=0.08; lxmax[ip]=0.35;
    //lymin[ip]=0.8; lymax[ip]=0.9;
    lxmin[ip]=0.05; lxmax[ip]=0.7;
    lymin[ip]=0.88; lymax[ip]=0.93;
    ptit[ip][0]=1.; ptit[ip][1]=-0.05;// position legends 
    atit[ip][0]="p_{T} (GeV/c)"; atit[ip][1]="v_{1}";
  }
  //
  // Read data and create vector files
  //
  for (int ifile=0;ifile<Mfiles;ifile++)
  {
    //cout << ifile << "'th data" << endl;
    int np=0;
    ifstream infile;
    infile.open(cfn[ifile]);
    if (infile.is_open())
    {
      cout << "reading " << cfn[ifile] << endl;
      std::string line;
      while(std::getline(infile,line,'\n'))
      {
 
        double v1,v2,v3,v4;
        int res = sscanf(line.c_str(),"%lg %lg %lg %lg",&v1,&v2,&v3,&v4);
        if (res!=4) continue;
	cout <<"v1="<<v1<<" v2="<<v2<<" v3="<<v3 <<" v4="<<v4<<  endl;
//	if(v1>0.4){
        xa[ifile][np]=v1;
        xe[ifile][np]=0.0;
	syse[ifile][np]=v4;
        
	//ya[ifile][np]=v2;
        //ye[ifile][np]=v3;

	int ic = ifile+2;
	float new_vn  = v2*Ratio[ic];//v1
	float new_err = fabs(new_vn)*sqrt(pow(v3/v2,2)+pow(Ratio_er[ic]/Ratio[ic],2));//Ratio_er[11];
	
	cout << new_vn << " " << v2 << endl;
	cout << new_err << " " << v3 << endl;
	ya[ifile][np]= new_vn ;
	ye[ifile][np]= new_err;//v1 er



	// syse[ifile][np]=v2*0.1;
	// if(v1>3.4)	syse[ifile][np]=v2*0.15;
        np++;
//	}
      }
      infile.close();
    }
    else 
    {
      //cout << ifile << "'th data not exist!: " << cfn[ifile] << endl;
    }
    ndp[ifile]=np;
  }
  //
  //
  //
  //jv  const int nw=12;//number of windows
  const int nw=4;
  //jv try  make it square  TCanvas *can=new TCanvas("can","can",10,10,1050,800);   
  TCanvas *can=new TCanvas("can","can",10,10,1050,400);
  
  //jv  can->Divide(4,3,0,0); //sticks the pads with no space inbetween 
  can->Divide(4,1,0,0); //sticks the pads with no space inbetween 
  
  TH1D *h1[nw];
  for (int iw=0;iw<nw;iw++)
    {
      can->cd(iw+1);
      char ch1[8];
      sprintf(ch1,"h1_%d",iw);
      h1[iw] = new TH1D(ch1,"",500,hxmin[iw],hxmax[iw]);
      h1[iw]->SetMinimum(hymin[iw]); h1[iw]->SetMaximum(hymax[iw]);
      h1[iw]->SetXTitle(atit[iw][0]); h1[iw]->SetYTitle(atit[iw][1]);
      h1[iw]->GetXaxis()->CenterTitle(1);
      h1[iw]->GetYaxis()->CenterTitle(1);
      
      // futz with the axes
      h1[iw]->GetYaxis()->SetNdivisions(606);
      h1[iw]->GetXaxis()->SetNdivisions(606);
      
      h1[iw]->GetYaxis()->SetTitleSize(textsize);
      //      h1[iw]->GetYaxis()->SetTitleOffset(3.5);
      h1[iw]->GetYaxis()->SetTitleOffset(2.1);
      h1[iw]->GetYaxis()->SetLabelSize(textsize);
      h1[iw]->GetXaxis()->SetTitleSize(textsize);
      h1[iw]->GetXaxis()->SetTitleOffset(1.5);
      h1[iw]->GetXaxis()->SetLabelSize(textsize);
     // h1[iw]->GetXaxis()->SetLabelOffset(1.2);

    h1[iw]->Draw();
  }
  //
  // Draw! 
  //
  cout << "Now Draw!" << endl;
  TGraphErrors *ge;
  TGraphErrors* h_tmp_v1    [4];
  TGraphErrors* h_tmp_v1_sys[4];
  for (int iw=0;iw<nw;iw++)
  {
        can->cd(iw+1);
    //
    if (iw==0)
    {
      //  tex=new TLatex(0.5,0.11,"PHENIX Cu+Au #sqrt{s_{NN}}=200 GeV");
      tex=new TLatex(0.2,0.0115,"PHENIX Cu+Au 200 GeV");
      tex->SetTextSize(textsize-2);
      tex->Draw();
      tex=new TLatex(5.2,0.0115,"(a)");
      tex->SetTextSize(textsize-2);
      tex->Draw();
    }
    else if (iw==1){    
      tex=new TLatex(0.2,0.0115,"v1 w.r.t. Cu spect. neutrons");
      tex->SetTextSize(textsize-2);
      tex->Draw();
      tex=new TLatex(5.2,0.0115,"(b)");
      tex->SetTextSize(textsize-2);
      tex->Draw();}
    else if (iw==2){
    
      tex=new TLatex(5.2,0.0115,"(c)");
      tex->SetTextSize(textsize-2);
      tex->Draw();}
    else if (iw==3){    
      tex=new TLatex(5.2,0.0115,"(d)");
      tex->SetTextSize(textsize-2);
      tex->Draw();}
    if (iw < 4) tex=new TLatex(ptit[iw][0],ptit[iw][1],htit[iw]);
    //    else tex=new TLatex(ptit[iw][0],ptit[iw][1],htit[iw]);
    if ( iw == 0)   tex->SetTextSize(textsize);
    //  else if (iw == 8) tex->SetTextSize(textsize);
    else  tex->SetTextSize(textsize);
     tex->Draw();
    //
    // Legend
    //
    TLegend *leg = new TLegend(lxmin[iw],lymin[iw],lxmax[iw],lymax[iw]);
    leg->SetTextSize(textsize);
    //
    // Read data
    //
    for (int im=0;im<4;im++)
    {
      int j=im*12+iw;
      int col=mcol[im];
      if (ndp[j]==0) continue;
      ge=new TGraphErrors(ndp[j],&xa[j][0],&ya[j][0],&xe[j][0],&ye[j][0]);
      ge->SetMarkerStyle(msty[im][1]);
      // get the sys errors 
      ge1=new TGraphErrors(ndp[j],&xa[j][0],&ya[j][0],&xe[j][0],&syse[j][0]);
 
      ge->SetMarkerSize(msiz[im]);
      ge->SetMarkerColor(col);
      ge->SetLineWidth(1.2);
      ge->SetLineColor(col);
      // plot sys errors with a wide line
      ge1->SetLineColor(col-10);
      ge1->SetLineWidth(10);
      ge1->SetMarkerSize(0.1);

      h_tmp_v1    [iw] =(TGraphErrors*)ge->Clone();
      h_tmp_v1_sys[iw] =(TGraphErrors*)ge1->Clone();

      //ge1->Draw("e");
      //ge->Draw("pe");
      h_tmp_v1_sys[iw] ->Draw("e");
      h_tmp_v1    [iw] ->Draw("pe");
      leg->AddEntry(ge,cft[j],"p");
      // int np=0;
      // while (np < 30) {
      //     TBox *box = new TBox(xa[j][np]-0.5,ya[j][np]-syse[j][np],xa[j][np]+1.5,ya[j][np]+syse[j][np]);
      //     box->SetFillStyle(1);
      // 	  box->SetFillColor(1);
      //     box->Draw();
      // }    

    }
    if(iw==2) leg->Draw();
    //jv remove legend  if (iw==1) leg->Draw();
    //if (iw==1) leg->Draw();
  }
  cout << "end of process" << endl;
  //can->cd();
  //can->Print("../figures/v1_pt_4cent_tmp.pdf");


  ofstream ofs;
  ofs.open("Fig9.txt");
  double* sys_h[4];
  double* x_h[  4];
  double* y_h[  4];
  double* sta_h[4];
  for(int ic=0;ic<4;ic++)
    {
      sys_h[ic] = h_tmp_v1_sys[ic]->GetEY();
      x_h[  ic] = h_tmp_v1    [ic]->GetX();
      y_h[  ic] = h_tmp_v1    [ic]->GetY();
      sta_h[ic] = h_tmp_v1    [ic]->GetEY();
      ofs << (ic+1)*10 << "-" << (ic+2)*10 << "%" << endl;
      for(int ip=0;ip<ndp[ic];ip++)
	ofs << x_h[ic][ip] << " " << y_h[ic][ip] << " " << sta_h[ic][ip] << " " << sys_h[ic][ip] << endl;
    }
  ofs.close();
  
}
