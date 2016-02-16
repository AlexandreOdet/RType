#ifndef __NABIBI_H__
#define __NABIBI_H__

#include "Object.hh"
#include <vector>
#include "Eshoot.hh"

class Nabibi :
	public Object
{
public:
	Nabibi(sf::Vector2f, int, int);
	~Nabibi();

	void						changeStand();
	std::vector<Object *>		Waveshoot() const;
	virtual	void				update();

private:
	bool						_def;
};

#endif
