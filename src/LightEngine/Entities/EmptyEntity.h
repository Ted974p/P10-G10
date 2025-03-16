#include "../Entity.h"

class EmptyEntity : public Entity
{

public:
	void onInitialize() override;
	void set(int x, int y);
};

