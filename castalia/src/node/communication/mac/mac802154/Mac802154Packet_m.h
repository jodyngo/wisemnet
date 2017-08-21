//
// Generated file, do not edit! Created by nedtool 5.0 from castalia/src/node/communication/mac/mac802154/Mac802154Packet.msg.
//

#ifndef __MAC802154PACKET_M_H
#define __MAC802154PACKET_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0500
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "MacPacket_m.h"
// }}

/**
 * Enum generated from <tt>castalia/src/node/communication/mac/mac802154/Mac802154Packet.msg:19</tt> by nedtool.
 * <pre>
 * enum MAC802154Packet_type
 * {
 * 
 *     MAC_802154_BEACON_PACKET = 1001;
 *     MAC_802154_ASSOCIATE_PACKET = 1002;
 *     MAC_802154_DATA_PACKET = 1003;
 *     MAC_802154_ACK_PACKET = 1004;
 *     MAC_802154_GTS_REQUEST_PACKET = 1005;
 * }
 * </pre>
 */
enum MAC802154Packet_type {
    MAC_802154_BEACON_PACKET = 1001,
    MAC_802154_ASSOCIATE_PACKET = 1002,
    MAC_802154_DATA_PACKET = 1003,
    MAC_802154_ACK_PACKET = 1004,
    MAC_802154_GTS_REQUEST_PACKET = 1005
};

/**
 * Struct generated from castalia/src/node/communication/mac/mac802154/Mac802154Packet.msg:27 by nedtool.
 */
struct GTSspec
{
    GTSspec();
    int owner;
    int start;
    int length;
};

// helpers for local use
void __doPacking(omnetpp::cCommBuffer *b, const GTSspec& a);
void __doUnpacking(omnetpp::cCommBuffer *b, GTSspec& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const GTSspec& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, GTSspec& obj) { __doUnpacking(b, obj); }

/**
 * Class generated from <tt>castalia/src/node/communication/mac/mac802154/Mac802154Packet.msg:33</tt> by nedtool.
 * <pre>
 * packet Mac802154Packet extends MacPacket
 * {
 *     int Mac802154PacketType @enum(MAC802154Packet_type);
 *     int PANid;
 *     int srcID;
 *     int dstID;
 * 
 *     // those fields belong to beacon packet (MAC_802154_BEACON_PACKET)
 *     int beaconOrder;
 *     int frameOrder;
 *     int BSN;
 *     int CAPlength;
 *     int GTSlength;
 *     GTSspec GTSlist[];
 * }
 * </pre>
 */
class Mac802154Packet : public ::MacPacket
{
  protected:
    int Mac802154PacketType;
    int PANid;
    int srcID;
    int dstID;
    int beaconOrder;
    int frameOrder;
    int BSN;
    int CAPlength;
    int GTSlength;
    GTSspec *GTSlist; // array ptr
    unsigned int GTSlist_arraysize;

  private:
    void copy(const Mac802154Packet& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Mac802154Packet&);

  public:
    Mac802154Packet(const char *name=nullptr, int kind=0);
    Mac802154Packet(const Mac802154Packet& other);
    virtual ~Mac802154Packet();
    Mac802154Packet& operator=(const Mac802154Packet& other);
    virtual Mac802154Packet *dup() const {return new Mac802154Packet(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b);

    // field getter/setter methods
    virtual int getMac802154PacketType() const;
    virtual void setMac802154PacketType(int Mac802154PacketType);
    virtual int getPANid() const;
    virtual void setPANid(int PANid);
    virtual int getSrcID() const;
    virtual void setSrcID(int srcID);
    virtual int getDstID() const;
    virtual void setDstID(int dstID);
    virtual int getBeaconOrder() const;
    virtual void setBeaconOrder(int beaconOrder);
    virtual int getFrameOrder() const;
    virtual void setFrameOrder(int frameOrder);
    virtual int getBSN() const;
    virtual void setBSN(int BSN);
    virtual int getCAPlength() const;
    virtual void setCAPlength(int CAPlength);
    virtual int getGTSlength() const;
    virtual void setGTSlength(int GTSlength);
    virtual void setGTSlistArraySize(unsigned int size);
    virtual unsigned int getGTSlistArraySize() const;
    virtual GTSspec& getGTSlist(unsigned int k);
    virtual const GTSspec& getGTSlist(unsigned int k) const {return const_cast<Mac802154Packet*>(this)->getGTSlist(k);}
    virtual void setGTSlist(unsigned int k, const GTSspec& GTSlist);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Mac802154Packet& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Mac802154Packet& obj) {obj.parsimUnpack(b);}


#endif // ifndef __MAC802154PACKET_M_H

