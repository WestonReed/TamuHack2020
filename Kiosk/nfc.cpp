#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <nfc/nfc.h>
#include "nfc.h"

NFC::NFC(){
	// Initialize libnfc and set the nfc_context
	nfc_init(&context);
	if(!context) {
		printf("Unable to init libnfc (malloc)\n");
		exit(EXIT_FAILURE);
	}

	pnd = nfc_open(context, NULL);
  
	if(!pnd) {
		printf("ERROR: %s\n", "Unable to open NFC device.");
		exit(EXIT_FAILURE);
	}

	if(nfc_initiator_init(pnd) < 0) {
		nfc_perror(pnd, "nfc_initiator_init");
		exit(EXIT_FAILURE);
	}
}

std::string NFC::getID(){
	//wait for the next NFC tag
	while(nfc_initiator_select_passive_target(pnd, nmMifare, NULL, 0, &nt) <= 0)
		continue;

	std::stringstream ss;
	
	ss << std::hex << std::setfill('0');
	
	for(int i=0; i<(int)nt.nti.nai.szUidLen; i++)
		ss << std::hex << std::setw(2) << static_cast<int>(nt.nti.nai.abtUid[i]);
		
	return ss.str();
}
