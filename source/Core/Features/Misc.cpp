#include "Misc.h"

#include "../../Engine/Scimitar/Main/World.h"
#include "../../Engine/Scimitar/Main/Entity.h"
#include "../../Engine/Scimitar/Main/Pawn.h"
#include "../../Engine/Scimitar/Main/Replication.h"
#include "../../Engine/Scimitar/Main/Actor.h"

#include "../../Config.h"
#include "../../Engine/Engine.h"
#include "../Utils/SafeCall/SafeCall.h"

void Misc::Movement() noexcept
{
    static const auto world = std::make_unique<World>();

    const auto Local = world->GetLocal();
    if (!Local)
        return;

    const auto LocalPawn = Local->GetPawn();
    if (!LocalPawn)
        return;

    const auto LocalActor = LocalPawn->GetActor();
    if (!LocalActor)
        return;

    if (config->misc.NoPullOut)
    {
        const auto getMovement = LocalActor->GetMovement(EMovementComponent::EDrvWeapon);
        if (!getMovement)
            return;

        *reinterpret_cast<float*>(getMovement + 0x11C) = 10.f;
    };

    if (config->misc.NoAnimation)
    {
        const auto getMovement = LocalActor->GetMovement(EMovementComponent::Unknow1);
        if (!getMovement)
            return;

        *reinterpret_cast<bool*>(getMovement + 0x2B7) = true;
    };

    if (config->misc.JumpingSettings.first)
    {
        using Prototype = uintptr_t(*)(uintptr_t, int);
        const Prototype function = reinterpret_cast<Prototype>(client + 0x1A02B0);
        uintptr_t fn = FUNCTION(
            function,
            LocalActor->GetComponent(Update::JumpingComponent),
            0xB
        );
        if (!fn)
            return;

        if (config->misc.JumpingSettings.second.IsActive())
            *reinterpret_cast<float*>(fn + 0x330) = 3.f;
    }

};

void Misc::Physics() noexcept
{
    const auto Manager = *reinterpret_cast<uintptr_t*>(client + Update::Physics);
    if (!Manager)
        return;

    const auto Chain1 = *reinterpret_cast<uintptr_t*>(Manager + 0x98);
    if (!Chain1)
        return;

    const auto Chain2 = *reinterpret_cast<uintptr_t*>(Chain1 + 0x10) + 0x530;
    if (!Chain2)
        return;

    if (config->misc.Speed.first)
    {
        *reinterpret_cast<float*>(Chain2 + 0x130) = config->misc.Speed.second;
        *reinterpret_cast<float*>(Chain2 + 0x134) = config->misc.Speed.second;
        *reinterpret_cast<float*>(Chain2 + 0x138) = config->misc.Speed.second;
    }

    constexpr auto defaultValue = 0.0003051850945f;

    if (config->misc.noClipSettings.first && config->misc.noClipSettings.second.IsActive())
        *reinterpret_cast<float*>(Chain2 + 0xA0) = -1.f;
    else
        *reinterpret_cast<float*>(Chain2 + 0xA0) = defaultValue;
};

void Misc::ChatInteraction() noexcept
{
};