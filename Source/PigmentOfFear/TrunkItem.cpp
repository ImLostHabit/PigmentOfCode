


#include "TrunkItem.h"

void ATrunkItem::ItemReleased()
{
	CurrentKart->CheckForCollision(this);
}
