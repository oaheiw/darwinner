

class systeminfo {
public:
	systeminfo() {}
	~systeminfo() {}
	unsigned char* getCPUID();
	char* getDiskID();
private:
	void ToHex(const unsigned char * szOrigin, int nSize, char * szHex);
	
};