#pragma once
#include <iostream>
#include <vector>

struct Vftable;
class ubiVector3;

enum EMovementComponent : uint32_t
{
    EDrvAnimation = 0x2800E489,
    EDrvSprinting = 0xDFD83971,
    EDrvWeapon = 0xA6F78616,
    EDrvMelee = 0xB1531297,
    EDrvShooting = 0xCE425D1A,
    EDrvDrone = 0x903F7852,
    EDrvGadget = 0x799B767A,
    EDrvLeaning = 0x2434CD8B,
    EDrvVaulting = 0xF6D74D80,
    Unknow1 = 0xE7BB7DA4
};

enum ESkeleton : uint32_t
{
    PELVIS = 0xDED10611,
    STOMACH = 0x530EC1CB,
    LUMBAR = 0x8F39FA4E,
    THORAX = 0x1630ABF4,
    SPINE = 0x8023796D,
    NECK = 0x7C159A2,

    LHIP = 0x176183F0,
    LKNEE = 0x60DF401,
    LFOOT = 0x58988870,
    LTOE = 0xB95094E1,

    LCLAVICLE = 0x2D4660A8,
    LSHOULDER = 0xEB830ADA,
    LELBOW = 0x89B93A80,
    LHAND = 0xB675F36C,

    RHIP = 0x757F1291,
    RKNEE = 0x863D09FC,
    RFOOT = 0x9B14362C,
    RTOE = 0x42BE0FCB,

    RCLAVICLE = 0xF60647E5,
    RSHOULDER = 0x6BB3F727,
    RELBOW = 0x7257A1AA,
    RHAND = 0x75F94D30,

    HEAD = 0xA9CEFD4A,
    ROOT = 0x22E53C03,
};

inline std::vector<std::pair<ESkeleton, ESkeleton>> BonesPair =
{
    { ESkeleton::RTOE, ESkeleton::RFOOT },
    { ESkeleton::RFOOT, ESkeleton::RKNEE },
    { ESkeleton::RKNEE, ESkeleton::RHIP },
    { ESkeleton::RHIP, ESkeleton::PELVIS },

    { ESkeleton::LTOE, ESkeleton::LFOOT },
    { ESkeleton::LFOOT, ESkeleton::LKNEE },
    { ESkeleton::LKNEE, ESkeleton::LHIP },
    { ESkeleton::LHIP, ESkeleton::PELVIS },

    { ESkeleton::PELVIS, ESkeleton::STOMACH },
    { ESkeleton::STOMACH, ESkeleton::LUMBAR },
    { ESkeleton::LUMBAR, ESkeleton::THORAX },
    { ESkeleton::THORAX, ESkeleton::SPINE },

    { ESkeleton::SPINE, ESkeleton::LSHOULDER },
    { ESkeleton::LSHOULDER, ESkeleton::LELBOW },
    { ESkeleton::LELBOW, ESkeleton::LHAND },

    { ESkeleton::SPINE, ESkeleton::RSHOULDER },
    { ESkeleton::RSHOULDER, ESkeleton::RELBOW },
    { ESkeleton::RELBOW, ESkeleton::RHAND },
};

class Actor
{
public:
	//Vftable* vtable;

	uintptr_t GetComponent(int id) noexcept;
	uintptr_t GetMovement(uint64_t Hash) noexcept;
	uint16_t GetID(uint32_t Hash);
};