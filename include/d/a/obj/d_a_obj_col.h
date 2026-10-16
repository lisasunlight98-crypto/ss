#ifndef D_A_OBJ_COL_H
#define D_A_OBJ_COL_H

#include "d/a/obj/d_a_obj_base.h"
#include "d/col/cc/d_cc_d.h"
#include "m/m_vec.h"

class dAcOCol_c : public dAcObjBase_c {
public:
    dAcOCol_c() {}
    virtual ~dAcOCol_c();

    virtual int create() override;
    virtual int doDelete() override;
    virtual int actorExecute() override;
    virtual int draw() override;

private:
    bool checkActive();

    static dCcD_SrcCyl sCylSrc;
    static dCcD_SrcUnk sUnkSrc;

    /* 0x330 */ dCcD_Cyl mCyl;
    /* 0x480 */ dCcD_Unk mUnk;
    /* 0x688 */ mVec3_c mUnkMin;
    /* 0x694 */ mVec3_c mUnkMax;
    /* 0x6A0 */ u8 mType;
    /* 0x6A1 */ u8 mUnkParam;
    /* 0x6A2 */ u8 field_0x6A2;
    /* 0x6A3 */ u8 mFlag;
};

#endif
