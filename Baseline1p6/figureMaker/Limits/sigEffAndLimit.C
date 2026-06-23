//---------------------------------------------------------------------------
// useage:
// 1. plot signal efficiency (25 points) through cutflow.
// 2. compute 90% C.L. limit using signal efficiency & estimated bkg yield.
// !! change [EOT] [Nb1year] and re-run this macro if needed.
//---------------------------------------------------------------------------
#include <vector>
#include "/lustre/collider/chenjing/DarkSHINE/SJTUstyle/HStyle.C"

bool checkXsection = true; // plot an ugly xsection curve - just to have a look
int nP = 10; // baseline1.6: 10 dark photon mass point
bool isbaseline1 = false;

void sigEffAndLimit(){
    SetAtlasStyle();

    // define dark photon mass points
    string iCHANNEL;
    //string CHANNEL[25] = {"1MeV","2MeV","3MeV","4MeV","5MeV","6MeV","7MeV","8MeV","9MeV",
    //             "10MeV","20MeV","30MeV","40MeV","50MeV","60MeV","70MeV","80MeV","90MeV",
    //                   "100MeV","200MeV","500MeV","700MeV","1000MeV","1500MeV","2000MeV"};//Baseline1p0                                     
    //string CHANNEL[8] = {"1MeV","10MeV","20MeV","50MeV","100MeV","500MeV","1000MeV","2000MeV"};//Baseline1p5 
    string CHANNEL[10] = {"0001MeV", "0010MeV", "0020MeV", "0050MeV", "0100MeV", "0200MeV", "0500MeV","1000MeV", "1500MeV", "2000MeV"};
    char filename[256];
    map<string,TFile*> map_TFile;
    map<string,TH1D*> map_TH1D;

    double_t y_All[nP], y_1track[nP], y_MissingP[nP], y_HCal[nP], y_MaxCell[nP], y_ECal[nP];

    int i=1;
    for(auto iCHANNEL:CHANNEL){
        const char* ichannel = iCHANNEL.c_str();
        // input signal sample containing "cutflow" (baseline 1.0) 
        // or "fullcutflow" (baseline1.5) -- need to alter some order
        //sprintf(filename,"baseline1.0/ana_signal_%s_fullout.root",ichannel);
        sprintf(filename,"/lustre/collider/chenjing/DarkSHINE/Analysis/Baseline1p6/sampleMaker/outputFiles/ana_signal_%s_fullout.root",ichannel);
        map_TFile[string("file_")+iCHANNEL] = new TFile(filename);
        //map_TH1D[string("cutflow_")+iCHANNEL] = (TH1D*)map_TFile[string("file_")+iCHANNEL]->Get("cutflow");
        map_TH1D[string("cutflow_")+iCHANNEL] = (TH1D*)map_TFile[string("file_")+iCHANNEL]->Get("fullcutflow");
        // convert cutflow into fraction
        y_All[i-1] = 1.;
        //y_1track[i-1]   = map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(2)/map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(1);
        //y_MissingP[i-1] = map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(3)/map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(1);
        //y_HCal[i-1]     = map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(4)/map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(1);
        //y_MaxCell[i-1]  = map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(5)/map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(1);
        //y_ECal[i-1]     = map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(6)/map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(1);
        //y_1track[i-1]   = map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(3)/map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(1);
        //y_MissingP[i-1] = map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(4)/map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(1);
        //y_HCal[i-1]     = map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(5)/map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(1);
        //y_MaxCell[i-1]  = map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(7)/map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(1);
        //y_ECal[i-1]     = map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(8)/map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(1);
        y_1track[i-1]   = map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(2)/map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(1);
        y_MissingP[i-1] = map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(3)/map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(1);
        y_HCal[i-1]     = map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(4)/map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(1);
        y_MaxCell[i-1]  = map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(6)/map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(1);
        y_ECal[i-1]     = map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(7)/map_TH1D[string("cutflow_")+iCHANNEL]->GetBinContent(1);
     i++;
    }
//---------------------------------------------------------------------------    
// plot signal efficiency
    TCanvas *ccutflow = new TCanvas("ccutflow","ccutflow",1000,600);
    gPad->SetLogx();

    //Double_t x[25] = {0.001, 0.002, 0.003, 0.004, 0.005, 0.006, 0.007, 0.008, 0.009,
    //                           0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
    //                                                0.1, 0.2, 0.5, 0.7, 1., 1.5, 2.};
    //Double_t x[8] = {0.001, 0.01, 0.02, 0.05, 0.1, 0.5, 1., 2.};//Baseline1p5
    Double_t x[10] = {0.001, 0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1., 1.5, 2.};//Baseline1p6
    TGraph *gr_All      = new TGraph(nP, x, y_All);
    TGraph *gr_1track   = new TGraph(nP, x, y_1track);
    TGraph *gr_MissingP = new TGraph(nP, x, y_MissingP);    
    TGraph *gr_HCal     = new TGraph(nP, x, y_HCal);
    TGraph *gr_MaxCell  = new TGraph(nP, x, y_MaxCell);
    TGraph *gr_ECal     = new TGraph(nP, x, y_ECal);
    // plotting style
    gr_All     ->SetLineColor(1);
    gr_1track  ->SetLineColor(kSpring+4);
    gr_MissingP->SetLineColor(kOrange+7);
    gr_HCal    ->SetLineColor(kAzure+7);
    gr_MaxCell ->SetLineColor(kViolet+6);
    gr_ECal    ->SetLineColor(kRed+2);  

    gr_All     ->SetMarkerColor(1);
    gr_1track  ->SetMarkerColor(kSpring+4);
    gr_MissingP->SetMarkerColor(kOrange+7);
    gr_HCal    ->SetMarkerColor(kAzure+7);
    gr_MaxCell ->SetMarkerColor(kViolet+6);
    gr_ECal    ->SetMarkerColor(kRed+2);    
    
    gr_All->SetMarkerSize(1.2);
    gr_All->GetXaxis()->SetTitle("m_{A'} [GeV]");
    gr_All->GetYaxis()->SetTitle("signal efficiency");
    gr_All->GetHistogram()->SetMaximum(2.);
    gr_All->GetHistogram()->SetMinimum(0.2);
    gr_All->Draw("AP");
    for(auto &gr : {gr_1track,gr_MissingP,gr_HCal,gr_MaxCell,gr_ECal}){
        gr->SetMarkerSize(1.2);
        gr->Draw("P");
    }    
    // legend
    TLegend *leg = makeLeg(0.6,0.6,0.9,0.93);
    leg->AddEntry(gr_All,     "all events","lp");
    leg->AddEntry(gr_1track,  "only 1 tag. track & 1 rec. track","lp");
    leg->AddEntry(gr_MissingP,"p_{inci.}-p_{reco.} > 4 GeV","lp");
    leg->AddEntry(gr_HCal,    "E_{HCAL}^{total} < 30 MeV","lp");
    leg->AddEntry(gr_MaxCell, "E_{HCAL}^{Max cell} < 0.1 MeV","lp");
    leg->AddEntry(gr_ECal,    "E_{ECAL}^{total} < 25 GeV","lp");
    leg->Draw();
    allLabels(3e14, "sig. efficiency at all mass point",0.2,0.85);
    ccutflow->Print("sigcutflow_1.6_3001.png");
    ccutflow->Print("sigcutflow_1.6_3001.pdf");
//---------------------------------------------------------------------------
/*
// compute limits
    // set EOT and Nb
    double Nb1year = 0.528434; // estimated bkg yield per year (3e14). baseline1.0: 0.015
    double EOT = 3e14; // compute limit correspond to [?] EOTs: 3E14, 9E14, 1.5E15, 1E16
    cout<<" >>> estimated bkg yield /year: "<<Nb1year<<endl;
    cout<<" >>> computing limits for "<<EOT<<" EOTs"<<endl;
      char EOTlabel[256];
      sprintf(EOTlabel,""); 
      if(EOT==3e14)sprintf(EOTlabel,"_3e14");
      else if(EOT==9e14)sprintf(EOTlabel,"_9e14");
      else if(EOT==1.5e15)sprintf(EOTlabel,"_15e14");
      else if(EOT==1e16)sprintf(EOTlabel,"_1e16");
    double Nb = Nb1year*(EOT/3e14); // estimated bkg yield
    cout<<"Nb (estimated bkg yield for "<<EOT<<" EOTs): "<<Nb<<endl;
    // Possion: 0.95 - 90% CL
    double Ups = 0.5*TMath::ChisquareQuantile(0.95,2*(Nb+1))-Nb;
    cout<<"Ups (should be a constant once Nb is fixed): "<<Ups<<endl;
cout<<"---------------------------------------------------------------------------"<<endl;
    // limit on exp. number of signal for each mass point 
    double_t y[nP],Nexp[nP];
    for(int i=0;i<nP;i++){
        y[i] = y_ECal[i];
        cout<<"sig eff. of No."<<i<<" mA' point: "<<y[i]<<endl;
        Nexp[i] = Ups/y[i];
        cout<<"limit on exp. N: "<<Nexp[i]<<endl;
    }
//---------------------------------------------------------------------------
// convert limit on N to ep2 and y (y as a function of mX, not mA)
// assumption for alpha and fA:
   double alpha = 0.5;
   double fA = 1/3.;

// inclusive cross-section of dark photon bremsstrahlung from e interacting with tungsten target.
// produced by Calchep, normalised to epsilon = 1, beam energy @ 8 GeV.
// value updated @ 2021.12.29 by XiangChen.
   //double Xsection[25] = {1.447E+13,7.27E+12,4.024E+12,2.612E+12,1.8988E+12,1.4066E+12,1.1300E+12,8.7699E+11,7.0202e+11,
   //                                  5.8246E+11,1.52E+11,6.46E+10,3.27E+10,1.95E+10,1.19E+10,8.52E+9,5.94E+09,4.352E+09,
   //                                                       3.164E+09,4.29E+08,1.17E+07,1.72E+06,1.1914E+05,2628.1,125.89};
   double Xsection[8] = {1.447E+13,5.8246E+11,1.52E+11,1.95E+10,3.164E+09,1.17E+07,1.1914E+05,125.89};
   double Ep2[nP], Ep2_model[nP];
   double cns[nP];
   for(int i=0;i<nP;i++){
        Ep2[i] = 0.;
        // couputing limit. meaning of each number:
        // 0.676   - (g/cm2) thickness of tungsten target (0.1 X0)
        // 6.02e23 - Avogadro constant
        // 184     - atomic mass of tungsten
        if(Xsection[i]!=0) Ep2[i] = Nexp[i]/(Xsection[i]*0.1*6.76*EOT*6.02E23/184*1E-36);
        //if(Xsection[i]!=0) cns[i] = Xsection[i]*0.1*6.76*EOT*6.02E23/184*1E-36;
	//cout<<"sig eff. of No."<<i<<" cross-section: "<<Xsection[i]<<" , Nsig: "<<cns[i]<<endl;
        // dimensionless interaction strength y = ep^2 * alpha * (mX/mA')^4
        Ep2_model[i] = Ep2[i]*alpha*pow(fA,4);
   }
//---------------------------------------------------------------------------
cout<<"---------------------------------------------------------------------------"<<endl;
// print output for PlotLimit.C and PlotModelmX.C
cout<<" Now paste these into PlotLimit.C:"<<endl;
cout<<" =========== current Nb: "<<Nb<<" | current EOT: "<<EOT<<" =========== "<<endl;
cout<<"double Limit_MAprime"<<EOTlabel<<"["<<nP<<"] = {";
 for(int i=0;i<nP;i++){
    cout<<Ep2[i];
    if(i<nP-1)cout<<",";
 }
cout<<"};"<<endl;

cout<<" and these into PlotModelmX.C:"<<endl;
cout<<" =========== current Nb: "<<Nb<<" | current EOT: "<<EOT<<" =========== "<<endl;
cout<<"double Limit_model"<<EOTlabel<<"["<<nP<<"] = {";
 for(int i=0;i<nP;i++){
    cout<<Ep2_model[i];
    if(i<nP-1)cout<<",";
 }
cout<<"};"<<endl;
//---------------------------------------------------------------------------
//plot cross-section curve if you want to see the shape
if(checkXsection){
    cout<<">> plotting dark photon cross-section:"<<endl;
    TCanvas *c_limitEp2 = new TCanvas("c_limitEp2","c_limitEp2",800,600);
    c_limitEp2->SetLogx();
    c_limitEp2->SetLogy();
    TGraph *g_limitEp2 = new TGraph(nP,x,Xsection);
    g_limitEp2->SetMarkerSize(1.);
    g_limitEp2->GetXaxis()->SetTitle("m_{A'} [GeV]");
    g_limitEp2->GetYaxis()->SetTitle("pb/#varepsilon^{2}");
    g_limitEp2->Draw("AP");
    c_limitEp2->Print("Xsection.png");    
}
*/
}