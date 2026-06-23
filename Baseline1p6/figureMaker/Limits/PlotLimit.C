#include "/lustre/collider/chenjing/DarkSHINE/DSstyle/AtlasStyle.C"

bool doallbkg = false;
bool doDS = true;
bool dob15 = true;
string tag = "nominal";

//put text into figure
TPaveText* CreatePaveText(double x1,double y1,double x2,double y2,vector<TString> text,double textsize, int color = 1){
  TPaveText *tex=new TPaveText();
  tex->SetFillColor(0);tex->SetTextSize(0.05);
  tex->SetFillStyle(0);tex->SetBorderSize(0);
  int n=text.size();
  for(int i=0;i<n;i++) tex->AddText(text[i].Data());
  tex->SetX1NDC(x1);
  tex->SetY1NDC(y1);
  tex->SetX2NDC(x2);
  tex->SetY2NDC(y2);
  tex->SetTextSize(textsize);
  tex->SetTextColor(color);
  return tex;                                                                                            
}     

//coordinate information
void GetX1Y1X2Y2(TVirtualPad *c,double &x1,double &y1,double &x2,double &y2){  
  x1=c->GetFrame()->GetX1()+c->GetLeftMargin();
  y1=c->GetFrame()->GetY1()+c->GetBottomMargin();
  x2=c->GetFrame()->GetX2()-c->GetRightMargin();                                                         
  y2=c->GetFrame()->GetY2()-c->GetTopMargin();
}

//start the main function
void plot(){
  TCanvas *c = new TCanvas("c","c",1000,800);

  SetAtlasStyle();
  gPad->SetLogy();gPad->SetLogx();    
  gPad->SetBottomMargin(0.2);
  gPad->SetLeftMargin(0.2);
  gPad->SetTicks(1);
  gPad->SetGrid(0,1);
  TLine *line1 = new TLine(10.,1e-14,10.,1e-4);
  line1->SetLineStyle(3);
  TLine *line2 = new TLine(100.,1e-14,100.,1e-4);
  line2->SetLineStyle(3);
  TLine *line3 = new TLine(1000.,1e-14,1000.,1e-4);
  line3->SetLineStyle(3);

  //BaBar limits
  Double_t mass_s4[16] = {1,5,10,50,100,200,500,700,900,1000,1100,1500,1800,1900,1920, 2000};
  Double_t limit_Babar[16] = {9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,8.5E-7,8E-7,6E-7};
  Double_t shade_Babar[16] = {1E-3,1E-3,1E-3,1E-3,1E-3,1E-3,1E-3,1E-3,1E-3,1E-3,1E-3,1E-3,1E-3,1E-3,1E-3,1E-3};

  TGraph *gr_Babar = new TGraph(16, mass_s4, limit_Babar);
  gr_Babar->Draw("ac"); 
  gr_Babar->GetXaxis()->SetLimits(1,2000); 
  gr_Babar->GetHistogram()->SetMaximum(1E-4); 
  gr_Babar->GetHistogram()->SetMinimum(1E-14); 
  gr_Babar->GetXaxis()->SetTitle("#it{m_{A'}}[MeV]");
  //gr_Babar->GetXaxis()->SetTitleFont(13);
  gr_Babar->GetYaxis()->SetTitle("#it{#varepsilon^{2}}");
  gr_Babar->GetYaxis()->SetTitleFont(152);
  gr_Babar->GetYaxis()->SetTitleOffset(1.30);
  gr_Babar->GetXaxis()->SetTitleOffset(1.50);
  gr_Babar->SetLineWidth(2);
  gr_Babar->SetLineStyle(1);
  gr_Babar->SetLineColor(607);


  TGraph *grshade_BaBar = new TGraph(28);
  for (int i=0;i<16;i++) {
    grshade_BaBar->SetPoint(i,mass_s4[i],limit_Babar[i]);
    grshade_BaBar->SetPoint(16+i,mass_s4[16-i-1],shade_Babar[16-i-1]);
  }
  grshade_BaBar->SetFillStyle(3001);
  grshade_BaBar->SetFillColor(607);
  grshade_BaBar->SetFillColorAlpha(607, 0.65);
  grshade_BaBar->Draw("f");
  
  // BESIII 2012-2018 14 /fb
  //Double_t limit_BESIII[16] = {1.4E-8,1.4E-8,1.4E-8,1.4E-8,1.4E-8,1.4E-8,1.4E-8,1.4E-8,1.35E-8,1.35E-8,1.30E-8,1.25E-8,1.20E-8,1.15E-8,1.10E-8,1.05E-8};
  //Double_t shade_BESIII[16] = {9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7};
  // BESIII 2011-2018 17 /fb
  
  Double_t mass_BESIII[12] = {1,5,10,50,100,200,500,778,996.7,1326,1796,2223};
  Double_t limit_BESIII[12] = {1.4E-8,1.4E-8,1.4E-8,1.4E-8,1.4E-8,1.4E-8,1.4E-8,1.3E-8,1.2E-8,1.14E-8,1.06E-8,1.13E-8};
  Double_t shade_BESIII[12] = {9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7,9E-7};
//  TGraph *gr_BESIII = new TGraph(16, mass_s4, limit_BESIII);
  TGraph *gr_BESIII = new TGraph(12, mass_BESIII, limit_BESIII);
  gr_BESIII->Draw("c");
  gr_BESIII->SetLineWidth(2);
  gr_BESIII->SetLineStyle(2);
  gr_BESIII->SetLineColor(433);
  
  TGraph *grshade_BESIII = new TGraph(8);
  for (int i=0;i<12;i++) {
    grshade_BESIII->SetPoint(i,mass_BESIII[i],shade_BESIII[i]);
    grshade_BESIII->SetPoint(12+i,mass_BESIII[12-i-1],limit_BESIII[12-i-1]);
  }
  grshade_BESIII->SetFillStyle(3001);
  grshade_BESIII->SetFillColor(433);
  grshade_BESIII->SetFillColorAlpha(433, 0.65);
  grshade_BESIII->Draw("f");
  
  //fake grid-X
  line1->Draw();
  line2->Draw();
  line3->Draw();

  //NA64 limit
  Double_t mass_s3[5] = {1,2,5,30,39.5};
  Double_t limit_NA64_2017[5] = {7.2E-11,1E-10,4E-10,8E-9,1.4E-8};
  //Double_t shade_NA64[5] = {1.4E-8,1.4E-8,1.4E-8,1.4E-8,1.4E-8};
  Double_t shade_NA64[6] = {1.4E-8,1.4E-8,1.4E-8,1.4E-8,1.4E-8,1.4E-8};
//------------new NA64-------------
  Double_t mass_s3_2019[6] = {1.01,1.38,2.553,5.671,29.48752,37.32};
  Double_t limit_NA64_2019[6] = {5.91E-11,6.7E-11,1.332E-10,4.2E-10,8.191E-9,1.33E-8};
//---------------------------------
  //TGraph *gr_NA64 = new TGraph(5, mass_s3, limit_NA64);
  TGraph *gr_NA64 = new TGraph(6, mass_s3_2019, limit_NA64_2019);
  gr_NA64->Draw("c"); 
  gr_NA64->SetLineWidth(2);
  gr_NA64->SetLineStyle(1);
  gr_NA64->SetLineColor(8);
  
  TGraph *grshade_NA64 = new TGraph(8);
/*  for (int i=0;i<5;i++) {
    grshade_NA64->SetPoint(i,mass_s3[i],shade_NA64[i]);
    grshade_NA64->SetPoint(5+i,mass_s3[5-i-1],limit_NA64[5-i-1]);
  }*/
  for (int i=0;i<6;i++) {
    grshade_NA64->SetPoint(i,mass_s3_2019[i],shade_NA64[i]);
    grshade_NA64->SetPoint(6+i,mass_s3_2019[6-i-1],limit_NA64_2019[6-i-1]);
  }
  grshade_NA64->SetFillStyle(3001);
  grshade_NA64->SetFillColor(8);
  grshade_NA64->SetFillColorAlpha(8, 0.65);
  grshade_NA64->Draw("f");
  
  //NA64e2
  Double_t mass_NA64e2[10] = {1,2,5,10,50,100,300,500,700,900};
  Double_t limit_NA64e2[10] = {3.2E-12,5.8E-12,2.4E-11,7.2E-11,1.6E-9,8E-9,1.7E-7,1.0E-6,4E-6,1.6E-5};

  TGraph *gr_NA64e2 = new TGraph(10, mass_NA64e2, limit_NA64e2);
  gr_NA64e2->Draw("c"); 
  gr_NA64e2->SetLineWidth(2);
  gr_NA64e2->SetLineStyle(9);
  gr_NA64e2->SetLineColor(46);

  //NA64mu1
  Double_t mass_NA64mu1[8] = {1,30,50,100,140,500,1000,2000};
  Double_t limit_NA64mu1[8] = {1.6E-9,1.6E-9,1.6E-9,2.5E-9,3.6E-9,3.2E-8,1.6E-7,1.0E-6};

  TGraph *gr_NA64mu1 = new TGraph(8, mass_NA64mu1, limit_NA64mu1);
  gr_NA64mu1->Draw("c"); 
  gr_NA64mu1->SetLineWidth(2);
  gr_NA64mu1->SetLineStyle(9);
  gr_NA64mu1->SetLineColor(28);

  //NA64mu2
  Double_t mass_NA64mu2[8] = {1,30,50,100,160,500,1000,2000};
  Double_t limit_NA64mu2[8] = {1.6E-10,1.6E-10,1.6E-10,2.6E-10,4E-10,3.E-9,1.6E-8,9.6E-8};

  TGraph *gr_NA64mu2 = new TGraph(8, mass_NA64mu2, limit_NA64mu2);
  gr_NA64mu2->Draw("c"); 
  gr_NA64mu2->SetLineWidth(2);
  gr_NA64mu2->SetLineStyle(9);
  gr_NA64mu2->SetLineColor(48);
  
  // STCF 2 GeV 30 /ab
  Double_t mass_10[14] = {1,5,10,50,100,200,500,700,900,1000,1100,1490,1500,1510};
  Double_t limit_STCF2[14]= {3.3E-11,3.3E-11,3.3E-11,3.3E-11,3.3E-11,3.3E-11,3.3E-11,3.3E-11,3.0E-11,2.8E-11,2.8E-11,2.7E-11,2.7E-11,1};
  TGraph *gr_STCF2 = new TGraph(14, mass_10, limit_STCF2);
  gr_STCF2->Draw("c");
  gr_STCF2->SetLineWidth(2);
  gr_STCF2->SetLineStyle(9);
  gr_STCF2->SetLineColor(9);

  //LDMX limit
  Double_t mass_s5[11] = {1,5,10,20,30,40,100,200,300,400,650};
  //Double_t limit_LDMX[9] = {1.2E-11,5E-11,1.6E-10,2.9E-10,3E-9,2.2E-8,1.3E-7,5E-7,1E-5};
  Double_t limit_LDMX[11] = {6.5E-13,3.5E-12,1.2E-11,5E-11,1.6E-10,2.9E-10,3E-9,2.2E-8,1.3E-7,5E-7,1E-5};

  TGraph *gr_LDMX = new TGraph(11, mass_s5, limit_LDMX);
  if(doallbkg==false && doDS==false)gr_LDMX->Draw("c"); 
  gr_LDMX->SetLineWidth(2);
  gr_LDMX->SetLineStyle(1);
  gr_LDMX->SetLineColor(kBlack);
  
  // STCF 7 GeV 30 /ab
  Double_t limit_STCF7[16]= {1.7E-9,1.7E-9,1.7E-9,1.7E-9,1.7E-9,1.7E-9,1.7E-9,1.7E-9,1.7E-9,1.7E-9,1.7E-9,1.5E-9,1.5E-9,1.5E-9,1.45E-9,1.45E-9};
  TGraph *gr_STCF7 = new TGraph(16, mass_s4, limit_STCF7);
  gr_STCF7->Draw("c");
  gr_STCF7->SetLineWidth(2);
  gr_STCF7->SetLineStyle(9);
  gr_STCF7->SetLineColor(9);
  // STCF 4 GeV 30 /ab
  Double_t limit_STCF4[16]= {3.25E-10,3.25E-10,3.25E-10,3.25E-10,3.25E-10,3.25E-10,3.25E-10,3.25E-10,3.25E-10,3.25E-10,3.25E-10,3.25E-10,3.0E-10,3.0E-10,2.8E-10,2.6E-10};
  TGraph *gr_STCF4 = new TGraph(16, mass_s4, limit_STCF4);
  gr_STCF4->Draw("c");
  gr_STCF4->SetLineWidth(2);
  gr_STCF4->SetLineStyle(9);
  gr_STCF4->SetLineColor(9);

  //dark shine 4G/8G limit

  Double_t mass_s1[26] = {1,3,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,1200,1400,1600,1800,2000};
  Double_t limit_SJTU4G[26] = {0.9/0.41*2.5E-13,0.9/0.65*1.05E-12,0.9/0.65*5.522E-12,0.9/0.65*1.945E-11,0.9/0.65*5.073E-11,0.9/0.65*1.095E-10,0.9/0.65*1.977E-10,0.9/0.65*3.122E-10,0.9/0.65*4.786E-10,0.9/0.65*6.796E-10,0.9/0.65*9.127E-10,0.9/0.60*1.22E-09,0.9/0.6*1.088E-08,0.9/0.6*6.219E-08,0.9/0.7*2.5E-07,0.9/0.7*9.599E-07,0.9/0.8*3.528E-06,0.9/0.8*1.238E-05,0.9/0.9*4.065E-05,0.9/0.9*1.259E-04,3.655E-04,2.530E-03,1.412E-02,6.660E-02,2.762E-01,1.042E+00};
  Double_t limit_SJTU8G[26] = {0.9/0.49*2.5E-13,0.9/0.7*1.0E-12,0.9/0.7*4.894E-12,0.9/0.65*1.472E-11,0.9/0.65*3.814E-11,0.9/0.65*7E-11,0.9/0.65*1.25E-10,0.9/0.65*2.E-10,0.9/0.65*3.25E-10,0.9/0.65*4.501E-10,0.9/0.65*6.3E-10,0.9/0.60*7.9E-10,0.9/0.6*5.862E-09,0.9/0.6*2.645E-08,0.9/0.7*8E-08,0.9/0.7*2.201E-07,0.9/0.8*5.816E-07,0.9/0.8*1.481E-06,3.722E-06,8.988E-06,2.152E-05,1.088E-04,4.859E-04,1.863E-03,6.500E-03,2.004E-02};

//-----------------------------------------------
double Limit_MAprime_nominal[23] = {4.70115e-13,9.00974e-13,1.49388e-12,2.25203e-12,2.90548e-12,4.2171e-12,5.37249e-12,6.79106e-12,8.43867e-12,1.04524e-11,2.45881e-11,6.78399e-11,1.52002e-10,2.28254e-10,3.70123e-10,5.79451e-10,8.58349e-10,1.10076e-09,1.49223e-09,1.06672e-08,3.78599e-07,2.52263e-06,3.66685e-05};

double Limit_MAprime_inclusive[23] = {4.4461e-13,8.52094e-13,1.41283e-12,2.12985e-12,2.74785e-12,3.98831e-12,5.08102e-12,6.42262e-12,7.98085e-12,9.8853e-12,2.32541e-11,6.41594e-11,1.43755e-10,2.15871e-10,3.50042e-10,5.48014e-10,8.11781e-10,1.04104e-09,1.41128e-09,1.00884e-08,3.58059e-07,2.38577e-06,3.46792e-05};

//double Limit_MAprime_e16[23] = {3.23999e-14,6.20942e-14,1.02957e-13,1.55208e-13,2.00243e-13,2.90638e-13,3.70267e-13,4.68033e-13,5.81585e-13,7.20367e-13,1.69459e-12,4.67546e-12,1.04758e-11,1.57311e-11,2.55085e-11,3.99352e-11,5.91566e-11,7.58635e-11,1.02843e-10,7.3517e-10,2.60927e-08,1.73857e-07,2.52716e-06};

//double Limit_MAprime_e16[23] = {3.69452e-14,6.01298e-14,1.02957e-13,1.53128e-13,2.0965e-13,2.79357e-13,3.50607e-13,4.54163e-13,5.66656e-13,6.80964e-13,2.64222e-12,6.2822e-12,1.2398e-11,2.08134e-11,3.40828e-11,4.7341e-11,6.80201e-11,9.2389e-11,1.26441e-10,9.04825e-10,3.1445e-08,2.11257e-07,3.05215e-06};

double Limit_MAprime_05bkg[23] = {5.05695e-13,9.69162e-13,1.60694e-12,2.42247e-12,3.12538e-12,4.53626e-12,5.77909e-12,7.30502e-12,9.07733e-12,1.12434e-11,2.6449e-11,7.29742e-11,1.63505e-10,2.45529e-10,3.98135e-10,6.23305e-10,9.23311e-10,1.18407e-09,1.60517e-09,1.14745e-08,4.07252e-07,2.71355e-06,3.94437e-05};

double Limit_MAprime_1bkg[23] = {5.55635e-13,1.06487e-12,1.76564e-12,2.66171e-12,3.43403e-12,4.98425e-12,6.34982e-12,8.02644e-12,9.97378e-12,1.23538e-11,2.9061e-11,8.01809e-11,1.79653e-10,2.69777e-10,4.37453e-10,6.84861e-10,1.01449e-09,1.30101e-09,1.76369e-09,1.26077e-08,4.47471e-07,2.98153e-06,4.33391e-05};

double Limit_MAprime_2bkg[23] = {6.37548e-13,1.22186e-12,2.02593e-12,3.0541e-12,3.94028e-12,5.71904e-12,7.28592e-12,9.20972e-12,1.14441e-11,1.4175e-11,3.33453e-11,9.20014e-11,2.06138e-10,3.09548e-10,5.01943e-10,7.85825e-10,1.16405e-09,1.4928e-09,2.0237e-09,1.44663e-08,5.13439e-07,3.42108e-06,4.97282e-05};

double Limit_MAprime_5bkg[23] = {8.18202e-13,1.56808e-12,2.59999e-12,3.9195e-12,5.05679e-12,7.33956e-12,9.35044e-12,1.18194e-11,1.46869e-11,1.81916e-11,4.27939e-11,1.18071e-10,2.64548e-10,3.97261e-10,6.44172e-10,1.00849e-09,1.4939e-09,1.9158e-09,2.59713e-09,1.85654e-08,6.58925e-07,4.39046e-06,6.3819e-05};

double Limit_MAprime_10bkg[23] = {1.03328e-12,1.98028e-12,3.28344e-12,4.9498e-12,6.38604e-12,9.26888e-12,1.18083e-11,1.49263e-11,1.85476e-11,2.29736e-11,5.40429e-11,1.49107e-10,3.34088e-10,5.01686e-10,8.13503e-10,1.27359e-09,1.88659e-09,2.4194e-09,3.27982e-09,2.34456e-08,8.32133e-07,5.54456e-06,8.05948e-05};

double Limit_MAprime_100bkg[23] = {2.68319e-12,5.14232e-12,8.52634e-12,1.28535e-11,1.65831e-11,2.40691e-11,3.06635e-11,3.876e-11,4.81638e-11,5.9657e-11,1.40337e-10,3.87197e-10,8.6755e-10,1.30276e-09,2.11248e-09,3.30722e-09,4.89903e-09,6.28262e-09,8.51694e-09,6.08829e-08,2.16086e-06,1.43979e-05,0.000209286};

///for DarkSHINE, 1st xsection
/*
double Limit_MAprime_3e14[23] = {6.18602e-13,1.18555e-12,1.96573e-12,2.96334e-12,3.82319e-12,5.54908e-12,7.06941e-12,8.93603e-12,1.1104e-11,1.37538e-11,3.23543e-11,8.92673e-11,2.00012e-10,3.00349e-10,4.87027e-10,7.62472e-10,1.12946e-09,1.44844e-09,1.96356e-09,1.40364e-08,4.98181e-07,3.31941e-06,4.82504e-05};

double Limit_MAprime_9e14[23] = {2.21597e-13,4.2469e-13,7.04166e-13,1.06153e-12,1.36955e-12,1.9878e-12,2.53241e-12,3.20108e-12,3.97771e-12,4.92691e-12,1.159e-11,3.19775e-11,7.16486e-11,1.07592e-10,1.74464e-10,2.73134e-10,4.04597e-10,5.18864e-10,7.0339e-10,5.02815e-09,1.78459e-07,1.18909e-06,1.72843e-05};

double Limit_MAprime_15e14[23] = {1.41146e-13,2.70506e-13,4.48518e-13,6.76143e-13,8.72334e-13,1.26613e-12,1.61302e-12,2.03893e-12,2.5336e-12,3.13819e-12,7.38226e-12,2.03681e-11,4.56365e-11,6.85304e-11,1.11125e-10,1.73973e-10,2.57708e-10,3.3049e-10,4.48024e-10,3.20268e-09,1.13669e-07,7.57387e-07,1.10093e-05};
*/

///// with 0.194bkg
/*
double Limit_MAprime_3e14[23] = {7.05386e-13,1.14804e-12,1.96573e-12,2.92363e-12,4.00279e-12,5.33368e-12,6.69404e-12,8.67121e-12,1.0819e-11,1.30015e-11,5.04472e-11,1.19944e-10,2.36711e-10,3.97385e-10,6.50734e-10,9.0387e-10,1.29869e-09,1.76396e-09,2.41411e-09,1.72756e-08,6.00372e-07,4.03347e-06,5.82739e-05};

double Limit_MAprime_9e14[23] = {2.52685e-13,4.11254e-13,7.04166e-13,1.04731e-12,1.43389e-12,1.91064e-12,2.39795e-12,3.10622e-12,3.87561e-12,4.65741e-12,1.80713e-11,4.29667e-11,8.47951e-11,1.42352e-10,2.33107e-10,3.23786e-10,4.65219e-10,6.31888e-10,8.64787e-10,6.18849e-09,2.15066e-07,1.44488e-06,2.0875e-05};

double Limit_MAprime_15e14[23] = {1.60947e-13,2.61948e-13,4.48518e-13,6.67083e-13,9.13314e-13,1.21698e-12,1.52737e-12,1.9785e-12,2.46857e-12,2.96653e-12,1.15105e-11,2.73676e-11,5.40102e-11,9.0671e-11,1.48477e-10,2.06235e-10,2.96321e-10,4.02481e-10,5.50826e-10,3.94176e-09,1.36986e-07,9.20314e-07,1.32963e-05};
*/

//new xsection, 0.026bkg
/*
double Limit_MAprime_3e14[23] = {6.81421e-13,1.10904e-12,1.89894e-12,2.82431e-12,3.8668e-12,5.15248e-12,6.46662e-12,8.37662e-12,1.04515e-11,1.25598e-11,4.87333e-11,1.15869e-10,2.28669e-10,3.83884e-10,6.28626e-10,8.73162e-10,1.25457e-09,1.70403e-09,2.3321e-09,1.66887e-08,5.79975e-07,3.89644e-06,5.62941e-05};

double Limit_MAprime_9e14[23] = {2.30692e-13,3.75459e-13,6.42878e-13,9.56154e-13,1.30909e-12,1.74434e-12,2.18924e-12,2.83586e-12,3.53829e-12,4.25204e-12,1.64984e-11,3.9227e-11,7.74148e-11,1.29962e-10,2.12818e-10,2.95604e-10,4.24728e-10,5.76891e-10,7.89519e-10,5.64986e-09,1.96347e-07,1.31912e-06,1.90581e-05};

double Limit_MAprime_15e14[23] = {1.40484e-13,2.28642e-13,3.91491e-13,5.82266e-13,7.9719e-13,1.06225e-12,1.33317e-12,1.72694e-12,2.1547e-12,2.58935e-12,1.0047e-11,2.38879e-11,4.7143e-11,7.91426e-11,1.29599e-10,1.80013e-10,2.58645e-10,3.51307e-10,4.80791e-10,3.44058e-09,1.19569e-07,8.033e-07,1.16057e-05};

double Limit_MAprime_e16[23] = {2.47714e-14,4.03165e-14,6.90316e-14,1.02671e-13,1.40568e-13,1.87306e-13,2.35078e-13,3.04512e-13,3.79938e-13,4.5658e-13,1.77158e-12,4.21215e-12,8.31272e-12,1.39552e-11,2.28522e-11,3.17417e-11,4.56068e-11,6.19459e-11,8.47777e-11,6.06677e-10,2.10836e-08,1.41646e-07,2.04644e-06};
*/

/*
//updated xsection,0.015bkg
double Limit_MAprime_3e14[23] = {6.79125e-13,1.1053e-12,1.89255e-12,2.81479e-12,3.85377e-12,5.13512e-12,6.44483e-12,8.34839e-12,1.04162e-11,1.25174e-11,4.85691e-11,1.15479e-10,2.27899e-10,3.82591e-10,6.26507e-10,8.7022e-10,1.25034e-09,1.69829e-09,2.32424e-09,1.66324e-08,5.7802e-07,3.88331e-06,5.61044e-05};
double Limit_MAprime_9e14[23] = {2.28451e-13,3.71812e-13,6.36633e-13,9.46866e-13,1.29637e-12,1.7274e-12,2.16797e-12,2.80831e-12,3.50391e-12,4.21074e-12,1.63381e-11,3.88459e-11,7.66627e-11,1.287e-10,2.10751e-10,2.92733e-10,4.20602e-10,5.71286e-10,7.81849e-10,5.59498e-09,1.9444e-07,1.3063e-06,1.88729e-05};
double Limit_MAprime_15e14[23] = {1.38294e-13,2.25078e-13,3.85389e-13,5.7319e-13,7.84764e-13,1.04569e-12,1.31239e-12,1.70003e-12,2.12111e-12,2.54899e-12,9.89039e-12,2.35156e-11,4.64082e-11,7.7909e-11,1.27579e-10,1.77207e-10,2.54613e-10,3.45831e-10,4.73297e-10,3.38695e-09,1.17705e-07,7.90779e-07,1.14248e-05};
double Limit_MAprime_e16[23] = {2.30655e-14,3.754e-14,6.42777e-14,9.56004e-14,1.30888e-13,1.74407e-13,2.1889e-13,2.83541e-13,3.53773e-13,4.25137e-13,1.64958e-12,3.92208e-12,7.74026e-12,1.29942e-11,2.12785e-11,2.95558e-11,4.24661e-11,5.768e-11,7.89395e-11,5.64897e-10,1.96317e-08,1.31891e-07,1.90551e-06};
*/
//updated xsection, 0.015bkg, 25 points
double Limit_MAprime_3e14[25] = {6.79125e-13,1.1053e-12,1.89255e-12,2.81479e-12,3.85377e-12,5.13512e-12,6.44483e-12,8.34839e-12,1.04162e-11,1.25174e-11,4.85691e-11,1.15479e-10,2.27899e-10,3.82591e-10,6.26507e-10,8.7022e-10,1.25034e-09,1.69829e-09,2.32424e-09,1.66324e-08,5.7802e-07,3.88331e-06,5.61044e-05,0.00271947,0.0638142};
double Limit_MAprime_9e14[25] = {2.28451e-13,3.71812e-13,6.36633e-13,9.46866e-13,1.29637e-12,1.7274e-12,2.16797e-12,2.80831e-12,3.50391e-12,4.21074e-12,1.63381e-11,3.88459e-11,7.66627e-11,1.287e-10,2.10751e-10,2.92733e-10,4.20602e-10,5.71286e-10,7.81849e-10,5.59498e-09,1.9444e-07,1.3063e-06,1.88729e-05,0.000914801,0.0214664};
double Limit_MAprime_15e14[25] = {1.38294e-13,2.25078e-13,3.85389e-13,5.7319e-13,7.84764e-13,1.04569e-12,1.31239e-12,1.70003e-12,2.12111e-12,2.54899e-12,9.89039e-12,2.35156e-11,4.64082e-11,7.7909e-11,1.27579e-10,1.77207e-10,2.54613e-10,3.45831e-10,4.73297e-10,3.38695e-09,1.17705e-07,7.90779e-07,1.14248e-05,0.00055378,0.0129948};
double Limit_MAprime_e16[25] = {2.30655e-14,3.754e-14,6.42777e-14,9.56004e-14,1.30888e-13,1.74407e-13,2.1889e-13,2.83541e-13,3.53773e-13,4.25137e-13,1.64958e-12,3.92208e-12,7.74026e-12,1.29942e-11,2.12785e-11,2.95558e-11,4.24661e-11,5.768e-11,7.89395e-11,5.64897e-10,1.96317e-08,1.31891e-07,1.90551e-06,9.23629e-05,0.00216736};

//baseline1.5 preliminary
double Limit_MAprime_new3e14[8] = {7.74613e-13,1.45239e-11,5.88177e-11,4.72477e-10,2.91634e-09,7.40176e-07,7.30691e-05,0.0810281};
//double Limit_MAprime_3e141[8] = {8.09611e-13,1.51801e-11,6.14752e-11,4.93825e-10,3.04811e-09,7.73619e-07,7.63705e-05,0.0846891};
//double Limit_MAprime_3e142[8] = {8.05903e-13,1.51106e-11,6.11936e-11,4.91563e-10,3.03415e-09,7.70075e-07,7.60207e-05,0.0843012};
//double Limit_MAprime_3e143[8] = {8.0385e-13,1.50721e-11,6.10377e-11,4.90311e-10,3.02642e-09,7.68113e-07,7.58271e-05,0.0840865};
//double Limit_MAprime_3e144[8] = {7.99209e-13,1.49851e-11,6.06853e-11,4.8748e-10,3.00894e-09,7.63679e-07,7.53893e-05,0.083601};
//double Limit_MAprime_3e145[8] = {7.9756e-13,1.49542e-11,6.05601e-11,4.86474e-10,3.00273e-09,7.62103e-07,7.52337e-05,0.0834285};
//double Limit_MAprime_3e146[8] = {7.96677e-13,1.49376e-11,6.0493e-11,4.85935e-10,2.99941e-09,7.61259e-07,7.51504e-05,0.0833362};
//double Limit_MAprime_3e147[8] = {7.91016e-13,1.48315e-11,6.00632e-11,4.82482e-10,2.9781e-09,7.5585e-07,7.46164e-05,0.082744};
//double Limit_MAprime_3e148[8] = {7.85462e-13,1.47273e-11,5.96415e-11,4.79095e-10,2.95719e-09,7.50543e-07,7.40926e-05,0.082163};
//double Limit_MAprime_3e149[8] = {7.57008e-13,1.41938e-11,5.74809e-11,4.61739e-10,2.85006e-09,7.23354e-07,7.14085e-05,0.0791866};
//double Limit_MAprime_3e1410[8] = {7.61428e-13,1.42767e-11,5.78166e-11,4.64436e-10,2.8667e-09,7.27578e-07,7.18255e-05,0.079649};
//double Limit_MAprime_3e1411[8] = {7.62495e-13,1.42967e-11,5.78975e-11,4.65086e-10,2.87072e-09,7.28597e-07,7.1926e-05,0.0797605};
//double Limit_MAprime_3e1412[8] = {7.66943e-13,1.43801e-11,5.82353e-11,4.67799e-10,2.88746e-09,7.32847e-07,7.23456e-05,0.0802258};
//double Limit_MAprime_3e1413[8] = {7.7006e-13,1.44385e-11,5.8472e-11,4.697e-10,2.8992e-09,7.35826e-07,7.26397e-05,0.0805519};
//double Limit_MAprime_3e1414[8] = {7.78607e-13,1.45988e-11,5.9121e-11,4.74914e-10,2.93138e-09,7.43993e-07,7.3446e-05,0.081446};
//double Limit_MAprime_3e1415[8] = {7.7381e-13,1.45088e-11,5.87567e-11,4.71988e-10,2.91332e-09,7.39409e-07,7.29934e-05,0.0809441};
//double Limit_MAprime_3e1416[8] = {7.74613e-13,1.45239e-11,5.88177e-11,4.72477e-10,2.91634e-09,7.40176e-07,7.30691e-05,0.0810281};
//double x_8p[8] = {1,10,20,50,100,500,1000,2000};

//double_t x[23] = {1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,500,700,1000};
double_t x[25] = {1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,500,700,1000,1500,2000};
//------------------------

//const char *grname = (string("Limit_MAprime_")+string(tag)).c_str();
/*
 TGraph *gr_nominal = new TGraph(23, x, Limit_MAprime_nominal);
 TGraph *gr_inclusive = new TGraph(23, x, Limit_MAprime_inclusive);  
 TGraph *gr_e16 = new TGraph(23, x, Limit_MAprime_e16);
 TGraph *gr_05bkg = new TGraph(23, x, Limit_MAprime_05bkg);
 TGraph *gr_1bkg = new TGraph(23, x, Limit_MAprime_1bkg);
 TGraph *gr_2bkg = new TGraph(23, x, Limit_MAprime_2bkg);
 TGraph *gr_5bkg = new TGraph(23, x, Limit_MAprime_5bkg);
 TGraph *gr_10bkg = new TGraph(23, x, Limit_MAprime_10bkg);
 TGraph *gr_100bkg = new TGraph(23, x, Limit_MAprime_100bkg);
 TGraph *gr_3e14 = new TGraph(23, x, Limit_MAprime_3e14);
 TGraph *gr_9e14 = new TGraph(23, x, Limit_MAprime_9e14);
 TGraph *gr_15e14 = new TGraph(23, x, Limit_MAprime_15e14); 
*/
 TGraph *gr_nominal = new TGraph(25, x, Limit_MAprime_nominal);
 TGraph *gr_inclusive = new TGraph(25, x, Limit_MAprime_inclusive);
 TGraph *gr_e16 = new TGraph(25, x, Limit_MAprime_e16);
 TGraph *gr_05bkg = new TGraph(25, x, Limit_MAprime_05bkg);
 TGraph *gr_1bkg = new TGraph(25, x, Limit_MAprime_1bkg);
 TGraph *gr_2bkg = new TGraph(25, x, Limit_MAprime_2bkg);
 TGraph *gr_5bkg = new TGraph(25, x, Limit_MAprime_5bkg);
 TGraph *gr_10bkg = new TGraph(25, x, Limit_MAprime_10bkg);
 TGraph *gr_100bkg = new TGraph(25, x, Limit_MAprime_100bkg);
 TGraph *gr_3e14 = new TGraph(25, x, Limit_MAprime_3e14);
 TGraph *gr_9e14 = new TGraph(25, x, Limit_MAprime_9e14);
 TGraph *gr_15e14 = new TGraph(25, x, Limit_MAprime_15e14);

TGraph *gr_new3e14 = new TGraph(8, x_8p, Limit_MAprime_new3e14);

// this line was the previous one by Kun!
  //TGraph *gr = new TGraph(26, mass_s1, limit_SJTU8G);

// it's the main red curve
  TGraph *gr = new TGraph();
if(doDS)tag="3e14";
if(tag=="nominal")gr = (TGraph*)gr_nominal->Clone();
if(tag=="inclusive")gr = (TGraph*)gr_inclusive->Clone();
if(tag=="e16")gr = (TGraph*)gr_e16->Clone();
if(tag=="05bkg")gr = (TGraph*)gr_05bkg->Clone();
if(tag=="1bkg")gr = (TGraph*)gr_1bkg->Clone();
if(tag=="2bkg")gr = (TGraph*)gr_2bkg->Clone();
if(tag=="5bkg")gr = (TGraph*)gr_5bkg->Clone();
if(tag=="10bkg")gr = (TGraph*)gr_10bkg->Clone();
if(tag=="100bkg")gr = (TGraph*)gr_100bkg->Clone();
if(tag=="3e14")gr = (TGraph*)gr_3e14->Clone();
if(tag=="9e14")gr = (TGraph*)gr_9e14->Clone();
if(tag=="15e14")gr = (TGraph*)gr_15e14->Clone();
  gr->Draw("c"); 

  gr->SetLineWidth(3);
  gr->SetLineStyle(10);  //1: solid line
  gr->SetMarkerStyle(8);
  gr->SetMarkerSize(1);
  gr->SetLineColor(kRed);

if(doallbkg){
for(auto &g:{gr_1bkg,gr_2bkg,gr_5bkg}){
  g->SetLineWidth(3);
  g->SetLineStyle(1);
  g->SetMarkerStyle(8);
  g->SetMarkerSize(1);
  g->Draw("c");
  }  
  gr_1bkg->SetLineColor(kAzure+2);
  gr_2bkg->SetLineColor(kOrange+7);
  gr_5bkg->SetLineColor(kTeal+3);
  //gr_10bkg->SetLineColor(kViolet-3); 
}

if(doDS){
for(auto &g:{gr_9e14,gr_15e14,gr_e16}){
  g->SetLineWidth(3);
  g->SetLineStyle(6);
  g->SetMarkerStyle(8);
  g->SetMarkerSize(1);
  g->Draw("c");
    }
  gr_9e14->SetLineColor(kAzure+2);
  gr_15e14->SetLineColor(kOrange+7);
  gr_e16->SetLineColor(kTeal+3);
 }

if(dob15){
  gr_new3e14->SetLineColor(60);
  gr_new3e14->SetLineWidth(3);
  gr_new3e14->SetMarkerStyle(8);
  gr_new3e14->SetMarkerSize(1);
  gr_new3e14->Draw("c");
}

  TGraph *gr_SJTU4G = new TGraph(26, mass_s1, limit_SJTU4G);
  //gr_SJTU4G->Draw("c"); 
  gr_SJTU4G->SetLineWidth(2);
  gr_SJTU4G->SetLineStyle(1);
  gr_SJTU4G->SetLineColor(kBlue);

  //dark shine 400M limit

  Double_t mass_s2[14] = {1, 3,10,20,30,40,50,60,70,80,90,100,200,300};
  Double_t limit_SJTU400M[14] = {2.45E-13,1.15E-12,9.431E-12,5.955E-11,1.931E-10,4.762E-10,1.011E-09,1.966E-09,3.625E-09,6.405E-09,1.102E-08,1.653E-08,2.473E-06,5.530E-04};

  TGraph *gr_SJTU400M = new TGraph(14, mass_s2, limit_SJTU400M);
  //gr_SJTU400M->Draw("c"); 
  gr_SJTU400M->SetLineWidth(3);
  gr_SJTU400M->SetLineStyle(1);
  gr_SJTU400M->SetLineColor(kRed);


  //start putting text
  double x1,y1,x2,y2;
  GetX1Y1X2Y2(c,x1,y1,x2,y2);
  cout<<x1<<", "<<x2<<", "<<y1<<", "<<y2<<endl;

  vector<TString> pavetext;
  pavetext.push_back("#bf{Invisibly Decaying Dark Photon}");
  TPaveText* text = CreatePaveText(x1+0.25,y1+0.02,x1+0.62,y1+0.05,pavetext,0.03);
  text->Draw("same");

  vector<TString>mu_SJTU4G;
  mu_SJTU4G.push_back("DARK SHINE, 4 #it{GeV}");
  TPaveText* pt_SJTU4G = CreatePaveText(x1+0.20,y1+0.13,x1+0.30,y1+0.175,mu_SJTU4G,0.03,kBlue);
  //pt_SJTU4G->Draw("same"); 

  vector<TString>mu_SJTU8G;
  TString tmp_SJTU8G = "DARK SHINE, 8 #it{GeV}, 4E14 EOT";
  if(string(tag)=="e16")tmp_SJTU8G = "DARK SHINE, 8 #it{GeV}, 1E16 EOT";
  if(doallbkg)tmp_SJTU8G = "DARK SHINE, 8 #it{GeV}, 4E14 EOT, 0.2 bkg";
  if(doDS)tmp_SJTU8G = "DARK SHINE, 8 #it{GeV}, 3E14 EOT"; 
  mu_SJTU8G.push_back(tmp_SJTU8G);
  TPaveText* pt_SJTU8G = CreatePaveText(x1+0.11,y1+0.09,x1+0.17,y1+0.13,mu_SJTU8G,0.025,kRed);
  pt_SJTU8G->Draw("same"); 

if(doallbkg){
  vector<TString>mu_SJTU8G_5bkg;
  mu_SJTU8G_5bkg.push_back("DARK SHINE, 4E14 EOT, 5. bkg");
  TPaveText* pt_SJTU8G_5bkg = CreatePaveText(x1+0.4,y1+0.19,x1+0.56,y1+0.23,mu_SJTU8G_5bkg,0.025,kTeal+3);
  pt_SJTU8G_5bkg->Draw("same");
  vector<TString>mu_SJTU8G_2bkg;
  mu_SJTU8G_2bkg.push_back("DARK SHINE, 4E14 EOT, 2. bkg");
  TPaveText* pt_SJTU8G_2bkg = CreatePaveText(x1+0.4,y1+0.16,x1+0.56,y1+0.20,mu_SJTU8G_2bkg,0.025,kOrange+7);
  pt_SJTU8G_2bkg->Draw("same");
  vector<TString>mu_SJTU8G_1bkg;
  mu_SJTU8G_1bkg.push_back("DARK SHINE, 4E14 EOT, 1. bkg");
  TPaveText* pt_SJTU8G_1bkg = CreatePaveText(x1+0.4,y1+0.13,x1+0.56,y1+0.17,mu_SJTU8G_1bkg,0.025,kAzure+2);
  pt_SJTU8G_1bkg->Draw("same");
}

if(doDS){
  vector<TString>mu_SJTU8G_9e14;
  mu_SJTU8G_9e14.push_back("DARK SHINE, 9E14 EOT");
  TPaveText* pt_SJTU8G_9e14 = CreatePaveText(x1+0.4,y1+0.19,x1+0.56,y1+0.23,mu_SJTU8G_9e14,0.025,kAzure+2);
  pt_SJTU8G_9e14->Draw("same");
  vector<TString>mu_SJTU8G_15e14;
  mu_SJTU8G_15e14.push_back("DARK SHINE, 1.5E15 EOT");
  TPaveText* pt_SJTU8G_15e14 = CreatePaveText(x1+0.4,y1+0.16,x1+0.56,y1+0.20,mu_SJTU8G_15e14,0.025,kOrange+7);
  pt_SJTU8G_15e14->Draw("same");
  vector<TString>mu_SJTU8G_e16;
  mu_SJTU8G_e16.push_back("DARK SHINE, 1E16 EOT");
  TPaveText* pt_SJTU8G_e16 = CreatePaveText(x1+0.4,y1+0.13,x1+0.56,y1+0.17,mu_SJTU8G_e16,0.025,kTeal+3);
  pt_SJTU8G_e16->Draw("same");
}


  vector<TString>mu_SJTU400M;
  mu_SJTU400M.push_back("DARK SHINE, 400 #it{MeV}");
  TPaveText* pt_SJTU400M = CreatePaveText(x1+0.04,y1+0.05,x1+0.10,y1+0.11,mu_SJTU400M,0.03,2);
  //pt_SJTU400M->Draw("same"); 


  vector<TString>mu_LDMX;
  mu_LDMX.push_back("LDMX, 4 #it{GeV}, 4E14 EOT");
  TPaveText* pt_LDMX = CreatePaveText(x1+0.27,y1+0.17,x1+0.40,y1+0.22,mu_LDMX,0.03,kBlack);
  if(doallbkg==false && doDS==false)pt_LDMX->Draw("same"); 


  vector<TString>mu_NA64;
  mu_NA64.push_back("NA64e,2.84E11 EOT");
  TPaveText* pt_NA64 = CreatePaveText(x1+0.085,y1+0.37,x1+0.135,y1+0.43,mu_NA64,0.025,418);
  pt_NA64->Draw("same"); 
  
  /*vector<TString>mu_combination;
  mu_combination.push_back("NA64 + BESIII exclusions");
  TPaveText* pt_combination = CreatePaveText(x1+0.085,y1+0.50,x1+0.135,y1+0.60,mu_combination,0.032,12);
  pt_combination->Draw("same");
  */

  vector<TString>mu_NA64e2;
  mu_NA64e2.push_back("NA64e,5E12 EOT");
  TPaveText* pt_NA64e2 = CreatePaveText(x1+0.01,y1+0.21,x1+0.09,y1+0.245,mu_NA64e2,0.02,46);
  pt_NA64e2->Draw("same");

  vector<TString>mu_NA64mu1;
  mu_NA64mu1.push_back("NA64#it{u},5E12 EOT");
  TPaveText* pt_NA64mu1 = CreatePaveText(x1+0.02,y1+0.355,x1+0.10,y1+0.395,mu_NA64mu1,0.02,28);
  pt_NA64mu1->Draw("same");

  vector<TString>mu_NA64mu2;
  mu_NA64mu2.push_back("NA64#it{u},5E13 EOT");
  TPaveText* pt_NA64mu2 = CreatePaveText(x1+0.02,y1+0.278,x1+0.10,y1+0.318,mu_NA64mu2,0.02,48);
  pt_NA64mu2->Draw("same");
  
  vector<TString>mu_BaBar;
  mu_BaBar.push_back("BaBar");
  TPaveText* pt_BaBar = CreatePaveText(x1+0.20,y1+0.55,x1+0.25,y1+0.65,mu_BaBar,0.03,616);
  pt_BaBar->Draw("same"); 

  vector<TString>mu_BESIII;
  //mu_BESIII.push_back("BESIII 2012-2018 14/fb");
  mu_BESIII.push_back("BESIII 2011-2018 17/fb");
  TPaveText* pt_BESIII = CreatePaveText(x1+0.10,y1+0.46,x1+0.15,y1+0.53,mu_BESIII,0.03,435);
  pt_BESIII->Draw("same"); 

  vector<TString>mu_STCF7;
  mu_STCF7.push_back("STCF 7 GeV 30/ab");
  TPaveText* pt_STCF7 = CreatePaveText(x1+0.515,y1+0.36,x1+0.525,y1+0.38,mu_STCF7,0.02,9);
  pt_STCF7->Draw("same"); 

  vector<TString>mu_STCF4;
  mu_STCF4.push_back("STCF 4 GeV 30/ab");
  TPaveText* pt_STCF4 = CreatePaveText(x1+0.515,y1+0.31,x1+0.525,y1+0.34,mu_STCF4,0.02,9);
  pt_STCF4->Draw("same"); 
  
  vector<TString>mu_STCF2;
  mu_STCF2.push_back("STCF 2 GeV 30/ab");
  TPaveText* pt_STCF2 = CreatePaveText(x1+0.515,y1+0.235,x1+0.525,y1+0.265,mu_STCF2,0.02,9);
  pt_STCF2->Draw("same"); 
  
  TLegend *leg = new TLegend(x1+0.02,y2-0.24,x1+0.60,y2-0.18, NULL, "brNDC");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.03);
  leg->SetTextFont(42);
  //leg->AddEntry(fa1, "SM Higgs boson", "l");//->SetLineWidth(15.);
  leg->Draw("same");

  const char* output_pdf = (string("figure/plot/DarkShine_")+string(tag)+string(".pdf")).c_str();
  c->SaveAs(output_pdf);
  const char* output_root = (string("figure/plot/DarkShine_")+string(tag)+string(".root")).c_str();
  c->SaveAs(output_root);
  const char* output_eps = (string("figure/plot/DarkShine_")+string(tag)+string(".eps")).c_str();
  c->SaveAs(output_eps);
  const char* output_C = (string("figure/plot/DarkShine_")+string(tag)+string(".C")).c_str();
  c->SaveAs(output_C);  
  const char* output_png = (string("figure/plot/DarkShine_")+string(tag)+string(".png")).c_str();
  c->SaveAs(output_png);  
  const char* output_bkg_pdf = (string("figure/plot/DarkShine_doallbkg_")+string(tag)+string(".pdf")).c_str();
  if(doallbkg)c->SaveAs(output_bkg_pdf);

}