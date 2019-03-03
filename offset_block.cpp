////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////	offset_block.cxx
////
////	Make an offset block figure for the thesis
////    use run 2818, real event 102 (10% iterator 10)
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
#include "FFTtools.h"
#include "AraGeomTool.h"

//ROOT Includes
#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"

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
	TGraph *waveform = realAtriEvPtr->getGraphFromRFChan(0);
	TGraph *interpolated_waveform = FFTtools::getInterpolatedGraph(waveform, 0.5); //get an interpolated waveform with 0.5 ns interpolation
	TGraph *padded_waveform = FFTtools::padWaveToLength(interpolated_waveform,2048);
	TGraph *spectrum = FFTtools::makePowerSpectrumMilliVoltsNanoSecondsdB(padded_waveform); //now make a spectrum

	configure(waveform);
	configure(spectrum);

	vector<double> times;
	vector<double> volts;
	for(double i=-45.; i<405.; i+=1.){
		times.push_back(i);
		volts.push_back(0);
	}
	TGraph *w2 = new TGraph(times.size(),&times[0],&volts[0]);
	configure(w2);

	TCanvas *c = new TCanvas("","",2*1100,850);
	c->Divide(2,1);
	c->cd(1);
		gPad->SetTopMargin(0.05);
		gPad->SetRightMargin(0.05);
		gPad->SetLeftMargin(0.1);
		gPad->SetBottomMargin(0.1);
		w2->Draw("AL");
		w2->SetTitle("");
		w2->SetLineWidth(2);
		w2->SetLineColor(kWhite);
		w2->GetXaxis()->SetTitle("Time (ns)");
		w2->GetYaxis()->SetTitle("Voltage (mV)");
		w2->GetYaxis()->SetRangeUser(-100.,100.);
		w2->GetXaxis()->SetRangeUser(-45,405.);
		waveform->Draw("same");
		waveform->SetLineWidth(2);
	c->cd(2);
		gPad->SetTopMargin(0.05);
		gPad->SetRightMargin(0.05);
		gPad->SetLeftMargin(0.1);
		gPad->SetBottomMargin(0.1);
		spectrum->Draw("ALP");
		spectrum->SetTitle("");
		spectrum->SetLineWidth(2);
		spectrum->GetYaxis()->SetTitle("Power (dB)");
		spectrum->GetXaxis()->SetTitle("Frequency (MHz)");
		spectrum->GetYaxis()->SetRangeUser(0.,40.);
		spectrum->GetXaxis()->SetRangeUser(0,1000.);
	char save_title[300];
	sprintf(save_title,"station%d_run%d_event%d.png",stationId,runNum,realAtriEvPtr->eventNumber);
	c->SaveAs(save_title);

	delete spectrum;
	delete interpolated_waveform;
	delete padded_waveform;
	delete waveform;
	delete realAtriEvPtr;
	
}//close the main program

void configure(TGraph *gr){
	gr->GetXaxis()->SetLabelSize(0.05);
	// gr->GetXaxis()->SetLabelOffset(0.02);

	gr->GetXaxis()->SetTitleSize(0.05);
	// gr->GetXaxis()->SetTitleOffset(1.1);

	gr->GetYaxis()->SetLabelSize(0.05);
	// gr->GetYaxis()->SetLabelOffset(0.02);

	gr->GetYaxis()->SetTitleSize(0.05);
	// gr->GetYaxis()->SetTitleOffset(1.1);
}
