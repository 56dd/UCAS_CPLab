#ifndef COMPILER_IRTYPE_H
#define COMPILER_IRTYPE_H


#include "IRValue.h"

class IRType : public IRValue {
public:
    enum PrimitiveID {
        VoidTyID = 0,
        BoolTyID,//  0, 1: Basics...
        IntTyID, //  2: 32 bit types...
        FloatTyID,
        DoubleTyID,// 3, 4: Floating point types...

        TypeTyID, // 5   : Type definitions
        LabelTyID,// 6   : Labels...

        // Derived types... see DerivedTypes.h file...
        FunctionTyID,
        ArrayTyID,
        PointerTyID,

        NumPrimitiveIDs,// Must remain as last defined ID
        FirstDerivedTyID = FunctionTyID,
    };

private:
    PrimitiveID ID;

protected:
    IRType(const std::string &Name, IRType::PrimitiveID id);

    ~IRType() override = default;

public:
    void print(std::ostream &OS) const override;

    inline PrimitiveID getPrimitiveID() const { return ID; }

    /******判断是不是整型或者浮点类型******/
    virtual bool isInteger() const { return 0; }
    bool isIntegral() const { return isInteger() || ID == BoolTyID; }
    bool isFloatingPoint() const { return ID == FloatTyID || ID == DoubleTyID; }

    /******判断是不是函数derived指针等其他类型******/
    inline bool isPrimitiveType() const { return ID < FirstDerivedTyID; }
    inline bool isDerivedType() const { return ID >= FirstDerivedTyID; }

    /**
     * Return true if the value is holdable in a register
     * @return bool
     */
    inline bool isFirstClassType() const {
        return isPrimitiveType() || ID == PointerTyID;
    }

    /**
     *
     * @return true if it makes sense to take the size of this type.
     */
    bool isSized() const {
        return ID != VoidTyID &&
               ID != FunctionTyID && ID != LabelTyID;
    }

    /**
     *
     * @return basic size of this type if it is a primitive type, zero if the type
     * dose not have a size or is not a primitive type
     */
    unsigned getPrimitiveSize() const;

    static const IRType *getPrimitiveType(PrimitiveID IDNumber);

    static IRType *VoidTy, *BoolTy;
    static IRType *IntTy;
    static IRType *FloatTy, *DoubleTy;

    static IRType *TypeTy, *LabelTy;

    static inline bool classof(const IRType *T) { return true; }
    static inline bool classof(const IRValue *V) {
        return V->getValueType() == IRValue::TypeVal;
    }
};


#endif//COMPILER_IRTYPE_H
