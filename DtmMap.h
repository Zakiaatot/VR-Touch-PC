#ifndef _DTM_MAP_H_
#define _DTM_MAP_H_

#include <vector>

class DtmMap
{
public:
	const bool* operator[](int name);
	void Push(bool* dtm);
	DtmMap(bool* dtms);
	~DtmMap();
private:
	std::vector<bool*> dtms_;
};


#endif // !_DTM_MAP_H_

