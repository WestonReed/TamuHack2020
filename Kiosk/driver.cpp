#include <iostream>
#include "nfc.h"
#include <curl/curl.h>
#include <unistd.h>
#include <sstream>
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}



int main(int argc, char** argv){
	NFC *reader = new NFC();
	
	while(true){
		std::cout << "\033[2J\033[1;1H";
		std::cout << "Please tap your baggage claim card" << std::endl;
		std::string uid = reader->getID();
		CURL *curl;
		std::string readBuffer, readBuffer2;

		curl = curl_easy_init();
		if(curl) {
			std::string url = "https://claimmybag.online/getname.php?rfid="+uid;
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
			curl_easy_perform(curl);
			curl_easy_cleanup(curl);

			std::stringstream ss;
			ss << "Welcome " << readBuffer;
			std::cout << "Welcome " << readBuffer << std::endl;
		}
		int bags, bagnum;
		std::cout << "How many bags do you have? ";

		std::cin >> bags;
		for(int i=0; i<bags; i++){
			std::cout << "Enter bag number: ";
			std::cin >> bagnum;
			curl = curl_easy_init();
			if(curl){
				readBuffer="";
				std::string url = "https://claimmybag.online/checkoutbag.php?bagID="+std::to_string(bagnum)+"&userID="+uid;
				curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
				curl_easy_perform(curl);
				curl_easy_cleanup(curl);

				std::stringstream ss;
				ss << readBuffer;
				if(ss.str() == "INVALID_USER"){
					std::cout << "Error: This bag is not registered to your account. Are you sure you typed the number correctly?" << std::endl;
					i--;
				}
			}
		}

		std::cout << "Thank you, enjoy your trip!" << std::endl;

		sleep(2);		
	}		
	exit(0);
}
