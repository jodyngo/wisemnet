//
// Generated file, do not edit! Created by nedtool 5.0 from castalia/src/node/communication/mac/MacPacket.msg.
//

#ifndef __MACPACKET_M_H
#define __MACPACKET_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0500
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Enum generated from <tt>castalia/src/node/communication/mac/MacPacket.msg:12</tt> by nedtool.
 * <pre>
 * // ********************************************************************************
 * // *  Copyright: National ICT Australia,  2007 - 2010                             *
 * // *  Developed at the ATP lab, Networked Systems research theme                  *
 * // *  Author(s): Yuriy Tselishchev                                                *
 * // *  This file is distributed under the terms in the attached LICENSE file.      *
 * // *  If you do not find this file, copies can be found by writing to:            *
 * // *                                                                              *
 * // *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia                 *
 * // *      Attention:  License Inquiry.                                            *
 * // *                                                                              *
 * // ******************************************************************************  
 * enum MacControlMessage_type
 * {
 * 
 *     MAC_BUFFER_FULL = 1;
 * }
 * </pre>
 */
enum MacControlMessage_type {
    MAC_BUFFER_FULL = 1
};

/**
 * Struct generated from castalia/src/node/communication/mac/MacPacket.msg:16 by nedtool.
 */
struct MacInteractionControl_type
{
    MacInteractionControl_type();
    double RSSI;
    double LQI;
    int source;
    unsigned int sequenceNumber;
};

// helpers for local use
void __doPacking(omnetpp::cCommBuffer *b, const MacInteractionControl_type& a);
void __doUnpacking(omnetpp::cCommBuffer *b, MacInteractionControl_type& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const MacInteractionControl_type& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, MacInteractionControl_type& obj) { __doUnpacking(b, obj); }

/**
 * Class generated from <tt>castalia/src/node/communication/mac/MacPacket.msg:23</tt> by nedtool.
 * <pre>
 * packet MacPacket
 * {
 *     MacInteractionControl_type MacInteractionControl;
 * }
 * </pre>
 */
class MacPacket : public ::omnetpp::cPacket
{
  protected:
    MacInteractionControl_type MacInteractionControl;

  private:
    void copy(const MacPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MacPacket&);

  public:
    MacPacket(const char *name=nullptr, int kind=0);
    MacPacket(const MacPacket& other);
    virtual ~MacPacket();
    MacPacket& operator=(const MacPacket& other);
    virtual MacPacket *dup() const {return new MacPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b);

    // field getter/setter methods
    virtual MacInteractionControl_type& getMacInteractionControl();
    virtual const MacInteractionControl_type& getMacInteractionControl() const {return const_cast<MacPacket*>(this)->getMacInteractionControl();}
    virtual void setMacInteractionControl(const MacInteractionControl_type& MacInteractionControl);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const MacPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, MacPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>castalia/src/node/communication/mac/MacPacket.msg:27</tt> by nedtool.
 * <pre>
 * message MacControlMessage
 * {
 *     int macControlMessageKind @enum(MacControlMessage_type);
 * }
 * </pre>
 */
class MacControlMessage : public ::omnetpp::cMessage
{
  protected:
    int macControlMessageKind;

  private:
    void copy(const MacControlMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MacControlMessage&);

  public:
    MacControlMessage(const char *name=nullptr, int kind=0);
    MacControlMessage(const MacControlMessage& other);
    virtual ~MacControlMessage();
    MacControlMessage& operator=(const MacControlMessage& other);
    virtual MacControlMessage *dup() const {return new MacControlMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b);

    // field getter/setter methods
    virtual int getMacControlMessageKind() const;
    virtual void setMacControlMessageKind(int macControlMessageKind);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const MacControlMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, MacControlMessage& obj) {obj.parsimUnpack(b);}


#endif // ifndef __MACPACKET_M_H

