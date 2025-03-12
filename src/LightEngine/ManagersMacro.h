#pragma once
#include "Managers.h"

#define gameManager Managers::GetInstance()->GetGameManager()
#define resourceManager Managers::GetInstance()->GetResourceManager()
#define inputManager Managers::GetInstance()->GetInputManager()
