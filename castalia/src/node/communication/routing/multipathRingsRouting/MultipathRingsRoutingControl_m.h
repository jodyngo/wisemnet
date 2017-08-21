//
// Generated file, do not edit! Created by nedtool 5.0 from castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingControl.msg.
//

#ifndef __MULTIPATHRINGSROUTINGCONTROL_M_H
#define __MULTIPATHRINGSROUTINGCONTROL_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0500
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Enum generated from <tt>castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingControl.msg:13</tt> by nedtool.
 * <pre>
 * enum multipathRingsRoutingControlDef
 * {
 * 
 *     MPRINGS_NOT_CONNECTED = 1;
 *     MPRINGS_CONNECTED_TO_TREE = 2;
 *     MPRINGS_TREE_LEVEL_UPDATED = 3;
 * }
 * </pre>
 */
enum multipathRingsRoutingControlDef {
    MPRINGS_NOT_CONNECTED = 1,
    MPRINGS_CONNECTED_TO_TREE = 2,
    MPRINGS_TREE_LEVEL_UPDATED = 3
};

/**
 * Class generated from <tt>castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingControl.msg:19</tt> by nedtool.
 * <pre>
 * message MultipathRingsRoutingControlMessage
 * {
 *     int multipathRingsRoutingControlMessageKind @enum(multipathRingsRoutingControlDef);
 *     int sinkID;
 *     int level;
 * }
 * </pre>
 */
class MultipathRingsRoutingControlMessage : public ::omnetpp::cMessage
{
  protected:
    int multipathRingsRoutingControlMessageKind;
    int sinkID;
    int level;

  private:
    void copy(const MultipathRingsRoutingControlMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MultipathRingsRoutingControlMessage&);

  public:
    MultipathRingsRoutingControlMessage(const char *name=nullptr, int kind=0);
    MultipathRingsRoutingControlMessage(const MultipathRingsRoutingControlMessage& other);
    virtual ~MultipathRingsRoutingControlMessage();
    MultipathRingsRoutingControlMessage& operator=(const MultipathRingsRoutingControlMessage& other);
    virtual MultipathRingsRoutingControlMessage *dup() const {return new MultipathRingsRoutingControlMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b);

    // field getter/setter methods
    virtual int getMultipathRingsRoutingControlMessageKind() const;
    virtual void setMultipathRingsRoutingControlMessageKind(int multipathRingsRoutingControlMessageKind);
    virtual int getSinkID() const;
    virtual void setSinkID(int sinkID);
    virtual int getLevel() const;
    virtual void setLevel(int level);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const MultipathRingsRoutingControlMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, MultipathRingsRoutingControlMessage& obj) {obj.parsimUnpack(b);}


#endif // ifndef __MULTIPATHRINGSROUTINGCONTROL_M_H

