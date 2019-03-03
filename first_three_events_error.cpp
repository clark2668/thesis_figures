////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////	first_three_events_error.cxx
////
////	Make a corrup event figure for the thesis
////    use run 6570, real event 3 (100% iterator 3)
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
#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"

using namespace std;

void configure(TGraph *gr);

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
	UsefulAtriStationEvent *realAtriEvPtr = new UsefulAtriStationEvent(rawAtriEvPtr, AraCalType::kLatestCalib);

	vector<TGraph*> graphs;
	for(int chan=0; chan<16; chan++){
		graphs.push_back(realAtriEvPtr->getGraphFromRFChan(chan));
		configure(graphs[chan]);
	}

	stringstream ss1;
	string xLabel, yLabel;
	xLabel = "Time (ns)"; yLabel = "Voltage (mV)";
	vector<string> titlesForGraphs;
	for (int i = 0; i < 16; i++){
		ss1.str("");
		ss1 << "Channel " << i;
		titlesForGraphs.push_back(ss1.str());
	}

	TCanvas *c = new TCanvas("","",1100,850);
	c->Divide(4,4);
	for(int chan=0; chan<16; chan++){
		c->cd(chan+1);

		gPad->SetTopMargin(0.1);
		gPad->SetRightMargin(0.03);
		gPad->SetLeftMargin(0.12);
		gPad->SetBottomMargin(0.11);

		graphs[chan]->Draw("AL");

		graphs[chan]->SetTitle(titlesForGraphs[chan].c_str());
		graphs[chan]->GetXaxis()->SetTitle(xLabel.c_str());
		graphs[chan]->GetYaxis()->SetTitle(yLabel.c_str());
		graphs[chan]->SetLineWidth(2);
	}
	char save_title[300];
	sprintf(save_title,"first3_station%d_run%d_event%d.png",stationId,runNum,realAtriEvPtr->eventNumber);
	c->SaveAs(save_title);
	
}//close the main program

void configure(TGraph *gr){
	gr->GetXaxis()->SetLabelSize(0.07);
	gr->GetXaxis()->SetTitleSize(0.07);
	gr->GetYaxis()->SetLabelSize(0.07);
	gr->GetYaxis()->SetTitleSize(0.07);
	gr->GetYaxis()->SetTitleOffset(1.1);
	gStyle->SetTitleFontSize(0.07);
}
