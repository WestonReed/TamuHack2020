#include <string>
#include <nfc/nfc.h>

#ifndef NFC_H
#define NFC_H

class NFC{
 private:
	nfc_device *pnd;
	nfc_target nt;
	nfc_context *context;
	const nfc_modulation nmMifare = {
								   .nmt = NMT_ISO14443A,
								   .nbr = NBR_106,
	};
	
 public:
	NFC();
	std::string getID();
};

#endif
