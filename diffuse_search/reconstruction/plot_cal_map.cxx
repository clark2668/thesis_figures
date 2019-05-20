////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////	first_three_events_error.cxx
////
////	Make plot of calibration pulser event
////    use run 1449, real event 452 (100% iterator 54)
////////////////////////////////////////////////////////////////////////////////

// C/C++ Includes
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <algorithm>

//AraRoot Includes
#include "RawAtriStationEvent.h"
#include "UsefulAtriStationEvent.h"

//ROOT Includes
#include "TColor.h"
#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TStyle.h"

// AraRoot includes
#include "Settings.h"
#include "Detector.h"
#include "Report.h"
#include "RayTraceCorrelator.h"
AraAntPol::AraAntPol_t Vpol = AraAntPol::kVertical;
AraAntPol::AraAntPol_t Hpol = AraAntPol::kHorizontal;

using namespace std;

void beautify_TH2D()
{
	const Int_t NRGBs = 5;
	const Int_t NCont = 255;
	Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
	Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
	Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
	Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);
}

int main(int argc, char **argv)
{
	if(argc<2) {  // Check to make sure there are enough arguments to do something meaningful
		std::cout << "Usage: " << basename(argv[0]) << " <input data file> <event>" << std::endl;
		return -1;
	}
	int event = atoi(argv[2]);
	
	TFile *fpIn = new TFile(argv[1], "OLD"); //we're going to open the data file
	if(!fpIn){
		std::cerr<< "Can not open the old file: " <<argv[1]<<endl;
		return -1;
	} //throw a warning if you can't open it
	
	fpIn->cd(); //go into that file
	TTree *eventTree = (TTree*) fpIn->Get("eventTree"); //load in the event free for this file
	if(!eventTree){
		std::cerr<<"Can't find eventTree in file" <<argv[1]<<" with filename " <<argv[1]<<endl;
		return -1;
	} //throw a warning if you can't open it
	RawAtriStationEvent *rawAtriEvPtr=0;
	eventTree->SetBranchAddress("event",&rawAtriEvPtr);
	int runNum;
	eventTree->SetBranchAddress("run",&runNum);
	
	eventTree->GetEntry(event);
	int stationId = rawAtriEvPtr->stationId;
	while(!rawAtriEvPtr->isCalpulserEvent() && event<eventTree->GetEntries()){
		event++;
		eventTree->GetEntry(event);
	}
	UsefulAtriStationEvent *realAtriEvPtr = new UsefulAtriStationEvent(rawAtriEvPtr, AraCalType::kLatestCalib);

	//set up the ray tracer
	Settings *settings = new Settings();
	string setupfile = "setup.txt";
	settings->ReadFile(setupfile);
	settings->NOFZ=1;
	Detector *detector=0;
	RayTraceCorrelator *corr = new RayTraceCorrelator(stationId, 41., settings, 1, 4); //41 m, cal puser
	TH2D *map = corr->getInterferometricMap_RT(settings, detector, realAtriEvPtr, Vpol, 0, 0);

	beautify_TH2D();
	gStyle->SetOptStat(0);


	TCanvas *c = new TCanvas("","",4*1100,4*850);
		map->Draw("colz");
		map->GetYaxis()->SetTitle("Elevation Angle (degree)");
		map->GetXaxis()->SetTitle("Azimuthal Angle (degree)");
		map->GetZaxis()->SetTitle("Summed Correlation Value (#Sigma C_{i,j})");
		map->GetYaxis()->CenterTitle();
		map->GetXaxis()->CenterTitle();
		map->GetZaxis()->CenterTitle();
		map->GetXaxis()->SetTitleOffset(1.1);
		map->GetYaxis()->SetTitleOffset(1.1);
		map->GetZaxis()->SetTitleOffset(1.1);
		gPad->SetTopMargin(0.05);
		gPad->SetRightMargin(0.15);
		gPad->SetLeftMargin(0.10);
		gPad->SetBottomMargin(0.10);
		map->GetZaxis()->SetRangeUser(0,0.6);
	char save_title[300];
	sprintf(save_title,"/users/PAS0654/osu0673/GeomStuff/thesis_figures/diffuse_search/reconstruction/map_station%d_run%d_event%d.png",stationId,runNum,realAtriEvPtr->eventNumber);
	c->SaveAs(save_title);
	
}//close the main program
