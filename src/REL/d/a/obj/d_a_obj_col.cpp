#include "d/a/obj/d_a_obj_col.h"

#include "d/col/cc/d_cc_s.h"
#include "d/flag/sceneflag_manager.h"

SPECIAL_ACTOR_PROFILE(OBJ_COL, dAcOCol_c, fProfile::OBJ_COL, 0x257, 0, 3);

dCcD_SrcCyl dAcOCol_c::sCylSrc = {
    /* mObjInf */
    {/* mObjAt */ {0, 0, {0, 0, 0}, 0, 0, 0, 0, CUT_DIR_NONE, 0},
     /* mObjTg */ {0, 0, {0, 0, 0x407}, 0, CUT_DIR_NONE},
     /* mObjCo */ {0xE9}},
    /* mCylInf */
    {100.0f, 100.0f},
};

dCcD_SrcUnk dAcOCol_c::sUnkSrc = {
    /* mObjInf */
    {/* mObjAt */ {0, 0, {0, 0, 0}, 0, 0, 0, 0, CUT_DIR_NONE, 0},
     /* mObjTg */ {0, 0, {0, 0, 0x407}, 0, CUT_DIR_NONE},
     /* mObjCo */ {0xE5}},
    /* mUnkInf */
    {-50.0f, 0.0f, -50.0f, 50.0f, 100.0f, 50.0f},
};

int dAcOCol_c::create() {
    mType = getFromParams(0, 0xF);
    mStts.SetDefaultRank();
    mFlag = getFromParams(4, 0xFF);
    mUnkParam = getFromParams(12, 0xF);

    if (mType == 0 || mType == 2) {
        mCyl.Set(sCylSrc);
        mCyl.SetH(sCylSrc.mCylInf.mHeight * mScale.y);
        mCyl.SetR(sCylSrc.mCylInf.mRadius * mScale.x);
        mCyl.SetStts(mStts);
    } else if (mType == 1 || mType == 3) {
        mUnk.Set(sUnkSrc);
        mUnk.SetStts(mStts);
        mUnkMin.x = -50.0f * mScale.x;
        mUnkMin.y = 0.0f;
        mUnkMin.z = -50.0f * mScale.z;
        mUnkMax.x = 50.0f * mScale.x;
        mUnkMax.y = 100.0f * mScale.y;
        mUnkMax.z = 50.0f * mScale.z;
        mUnk.Set(mUnkMin, mUnkMax);
    }

    mAcceleration = 0.0f;
    mMaxSpeed = -40.0f;
    updateMatrix();

    mBoundingBox.Set(mVec3_c(-200.0f, -50.0f, -200.0f), mVec3_c(200.0f, 200.0f, 200.0f));
    return SUCCEEDED;
}

int dAcOCol_c::doDelete() {
    return SUCCEEDED;
}

int dAcOCol_c::actorExecute() {
    if (checkActive()) {
        if (mType == 0 || mType == 2) {
            mCyl.SetC(mPosition);
            dCcS::GetInstance()->Set(&mCyl);
        } else if (mType == 1 || mType == 3) {
            mUnk.Set(mPosition, mRotation.y);
            dCcS::GetInstance()->Set(&mUnk);
        }
    }
    return SUCCEEDED;
}

int dAcOCol_c::draw() {
    return SUCCEEDED;
}

bool dAcOCol_c::checkActive() {
    bool ret = true;
    bool cond1 = false;
    bool canCheck = mUnkParam == 0 && mFlag < 0xFF;
    if (canCheck) {
        if (SceneflagManager::sInstance->checkBoolFlag(mRoomID, mFlag)) {
            cond1 = true;
        }
    }

    if (!cond1) {
        bool cond2 = false;
        if (mUnkParam != 0) {
            bool flag = false;
            if (mFlag < 0xFF && SceneflagManager::sInstance->checkBoolFlag(mRoomID, mFlag)) {
                flag = true;
            }
            if (!flag) {
                cond2 = true;
            }
        }
        if (!cond2) {
            ret = false;
        }
    }
    return ret;
}

dAcOCol_c::~dAcOCol_c() {}
