//
// Generated file, do not edit! Created by nedtool 5.0 from wise/src/node/application/wiseCameraMTIC/WiseCameraMTIC_Msg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "WiseCameraMTIC_Msg_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("WiseICFMTICCPacketType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("WiseICFMTICCPacketType"));
    e->insert(MTIC_COLLABORATION_DATA1, "MTIC_COLLABORATION_DATA1");
    e->insert(MTIC_COLLABORATION_END, "MTIC_COLLABORATION_END");
);

Register_Class(WiseCameraMTIC_Msg);

WiseCameraMTIC_Msg::WiseCameraMTIC_Msg(const char *name, int kind) : ::WiseApplicationPacket(name,kind)
{
    this->pktType = 0;
    this->trackingCount = 0;
    this->iterationStep = 0;
    this->targetID = 0;
    this->TypeNeighbour = 0;
}

WiseCameraMTIC_Msg::WiseCameraMTIC_Msg(const WiseCameraMTIC_Msg& other) : ::WiseApplicationPacket(other)
{
    copy(other);
}

WiseCameraMTIC_Msg::~WiseCameraMTIC_Msg()
{
}

WiseCameraMTIC_Msg& WiseCameraMTIC_Msg::operator=(const WiseCameraMTIC_Msg& other)
{
    if (this==&other) return *this;
    ::WiseApplicationPacket::operator=(other);
    copy(other);
    return *this;
}

void WiseCameraMTIC_Msg::copy(const WiseCameraMTIC_Msg& other)
{
    this->pktType = other.pktType;
    this->trackingCount = other.trackingCount;
    this->iterationStep = other.iterationStep;
    this->targetID = other.targetID;
    this->TypeNeighbour = other.TypeNeighbour;
    this->ICFv = other.ICFv;
    this->ICFV = other.ICFV;
    this->ICFW = other.ICFW;
}

void WiseCameraMTIC_Msg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WiseApplicationPacket::parsimPack(b);
    doParsimPacking(b,this->pktType);
    doParsimPacking(b,this->trackingCount);
    doParsimPacking(b,this->iterationStep);
    doParsimPacking(b,this->targetID);
    doParsimPacking(b,this->TypeNeighbour);
    doParsimPacking(b,this->ICFv);
    doParsimPacking(b,this->ICFV);
    doParsimPacking(b,this->ICFW);
}

void WiseCameraMTIC_Msg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WiseApplicationPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->pktType);
    doParsimUnpacking(b,this->trackingCount);
    doParsimUnpacking(b,this->iterationStep);
    doParsimUnpacking(b,this->targetID);
    doParsimUnpacking(b,this->TypeNeighbour);
    doParsimUnpacking(b,this->ICFv);
    doParsimUnpacking(b,this->ICFV);
    doParsimUnpacking(b,this->ICFW);
}

unsigned int WiseCameraMTIC_Msg::getPktType() const
{
    return this->pktType;
}

void WiseCameraMTIC_Msg::setPktType(unsigned int pktType)
{
    this->pktType = pktType;
}

unsigned long WiseCameraMTIC_Msg::getTrackingCount() const
{
    return this->trackingCount;
}

void WiseCameraMTIC_Msg::setTrackingCount(unsigned long trackingCount)
{
    this->trackingCount = trackingCount;
}

unsigned long WiseCameraMTIC_Msg::getIterationStep() const
{
    return this->iterationStep;
}

void WiseCameraMTIC_Msg::setIterationStep(unsigned long iterationStep)
{
    this->iterationStep = iterationStep;
}

unsigned int WiseCameraMTIC_Msg::getTargetID() const
{
    return this->targetID;
}

void WiseCameraMTIC_Msg::setTargetID(unsigned int targetID)
{
    this->targetID = targetID;
}

unsigned int WiseCameraMTIC_Msg::getTypeNeighbour() const
{
    return this->TypeNeighbour;
}

void WiseCameraMTIC_Msg::setTypeNeighbour(unsigned int TypeNeighbour)
{
    this->TypeNeighbour = TypeNeighbour;
}

cv::Mat& WiseCameraMTIC_Msg::getICFv()
{
    return this->ICFv;
}

void WiseCameraMTIC_Msg::setICFv(const cv::Mat& ICFv)
{
    this->ICFv = ICFv;
}

cv::Mat& WiseCameraMTIC_Msg::getICFV()
{
    return this->ICFV;
}

void WiseCameraMTIC_Msg::setICFV(const cv::Mat& ICFV)
{
    this->ICFV = ICFV;
}

cv::Mat& WiseCameraMTIC_Msg::getICFW()
{
    return this->ICFW;
}

void WiseCameraMTIC_Msg::setICFW(const cv::Mat& ICFW)
{
    this->ICFW = ICFW;
}

class WiseCameraMTIC_MsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WiseCameraMTIC_MsgDescriptor();
    virtual ~WiseCameraMTIC_MsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WiseCameraMTIC_MsgDescriptor);

WiseCameraMTIC_MsgDescriptor::WiseCameraMTIC_MsgDescriptor() : omnetpp::cClassDescriptor("WiseCameraMTIC_Msg", "WiseApplicationPacket")
{
    propertynames = nullptr;
}

WiseCameraMTIC_MsgDescriptor::~WiseCameraMTIC_MsgDescriptor()
{
    delete[] propertynames;
}

bool WiseCameraMTIC_MsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WiseCameraMTIC_Msg *>(obj)!=nullptr;
}

const char **WiseCameraMTIC_MsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WiseCameraMTIC_MsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WiseCameraMTIC_MsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int WiseCameraMTIC_MsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *WiseCameraMTIC_MsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "pktType",
        "trackingCount",
        "iterationStep",
        "targetID",
        "TypeNeighbour",
        "ICFv",
        "ICFV",
        "ICFW",
    };
    return (field>=0 && field<8) ? fieldNames[field] : nullptr;
}

int WiseCameraMTIC_MsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktType")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "trackingCount")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "iterationStep")==0) return base+2;
    if (fieldName[0]=='t' && strcmp(fieldName, "targetID")==0) return base+3;
    if (fieldName[0]=='T' && strcmp(fieldName, "TypeNeighbour")==0) return base+4;
    if (fieldName[0]=='I' && strcmp(fieldName, "ICFv")==0) return base+5;
    if (fieldName[0]=='I' && strcmp(fieldName, "ICFV")==0) return base+6;
    if (fieldName[0]=='I' && strcmp(fieldName, "ICFW")==0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WiseCameraMTIC_MsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "unsigned long",
        "unsigned long",
        "unsigned int",
        "unsigned int",
        "cv::Mat",
        "cv::Mat",
        "cv::Mat",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : nullptr;
}

const char **WiseCameraMTIC_MsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WiseCameraMTIC_MsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WiseCameraMTIC_MsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WiseCameraMTIC_Msg *pp = (WiseCameraMTIC_Msg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WiseCameraMTIC_MsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WiseCameraMTIC_Msg *pp = (WiseCameraMTIC_Msg *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getPktType());
        case 1: return ulong2string(pp->getTrackingCount());
        case 2: return ulong2string(pp->getIterationStep());
        case 3: return ulong2string(pp->getTargetID());
        case 4: return ulong2string(pp->getTypeNeighbour());
        case 5: {std::stringstream out; out << pp->getICFv(); return out.str();}
        case 6: {std::stringstream out; out << pp->getICFV(); return out.str();}
        case 7: {std::stringstream out; out << pp->getICFW(); return out.str();}
        default: return "";
    }
}

bool WiseCameraMTIC_MsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WiseCameraMTIC_Msg *pp = (WiseCameraMTIC_Msg *)object; (void)pp;
    switch (field) {
        case 0: pp->setPktType(string2ulong(value)); return true;
        case 1: pp->setTrackingCount(string2ulong(value)); return true;
        case 2: pp->setIterationStep(string2ulong(value)); return true;
        case 3: pp->setTargetID(string2ulong(value)); return true;
        case 4: pp->setTypeNeighbour(string2ulong(value)); return true;
        default: return false;
    }
}

const char *WiseCameraMTIC_MsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 5: return omnetpp::opp_typename(typeid(cv::Mat));
        case 6: return omnetpp::opp_typename(typeid(cv::Mat));
        case 7: return omnetpp::opp_typename(typeid(cv::Mat));
        default: return nullptr;
    };
}

void *WiseCameraMTIC_MsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WiseCameraMTIC_Msg *pp = (WiseCameraMTIC_Msg *)object; (void)pp;
    switch (field) {
        case 5: return (void *)(&pp->getICFv()); break;
        case 6: return (void *)(&pp->getICFV()); break;
        case 7: return (void *)(&pp->getICFW()); break;
        default: return nullptr;
    }
}

